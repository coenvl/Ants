#include "Antmap.h"

using namespace std;

//constructor
Antmap::Antmap()
{
    
};

//sets up the map size
void Antmap::setup()
{
	d_grid = vector<vector<Square> >(rows, vector<Square>(cols, Square()));
};

//resets all non-water squares to land and clears the bots ant vector
void Antmap::reset()
{
    myAnts.clear();
    enemyAnts.clear();
    myHills.clear();
    enemyHills.clear();
    food.clear();
    
    for(int row = 0; row < rows; row++)
        for(int col = 0; col < cols; col++)
            if(!d_grid[row][col].isWater)
                d_grid[row][col].reset();
};

//returns the euclidean distance between two locations with the edges wrapped
double Antmap::distance(const Location &loc1, const Location &loc2)
{
    int d1 = abs(loc1.row-loc2.row),
        d2 = abs(loc1.col-loc2.col),
        dr = min(d1, rows-d1),
        dc = min(d2, cols-d2);
    return sqrt(dr*dr + dc*dc);
};

int Antmap::squaredDistance(const Location &loc1, const Location &loc2)
{
    int d1 = abs(loc1.row-loc2.row),
        d2 = abs(loc1.col-loc2.col),
        dr = min(d1, rows-d1),
        dc = min(d2, cols-d2);
    return dr*dr + dc*dc;
};

int Antmap::manhattanDistance(const Location &loc1, const Location &loc2)
{
    int d1 = abs(loc1.row-loc2.row),
        d2 = abs(loc1.col-loc2.col),
        dr = min(d1, rows-d1),
        dc = min(d2, cols-d2);
    return dr + dc;
};

//returns the A* walking distance from one point to another
Route Antmap::bestRoute(const Location &src, const Location &dst)
{
	Route bestRoute;
	
	bestRoute.firstDirection = -1;
	bestRoute.remainingDistance = distance(src, dst);
	bestRoute.distance = bestRoute.remainingDistance;
	bestRoute.previousDistance = 0.0;
	bestRoute.intermediateLocation = src;
	
	//Can't go into the water
	if (getSquare(src)->isWater || getSquare(dst)->isWater)
	{
		bestRoute.distance = MAXDISTANCE;
		return bestRoute;
	}
		
	multimap<double, Route> routes;
	routes.clear();
	
	set<Location> visited;
	visited.clear();
	visited.insert(src);
	pair<set<Location>::iterator, bool> t;
	
	int iterations = 0;
	while (bestRoute.intermediateLocation != dst)
	{
		if (++iterations > MAXITER) break;
		
		for(int d = 0; d < TDIRECTIONS; d++)
		{
			Location tmp = getLocation(bestRoute.intermediateLocation, d);
			
			//if (visited.find(tmp) != visited.end())	continue; //Don't add locations where we've already checked
			t = visited.insert(tmp);
			
			if (!t.second) continue; //Because it shouldn't be checked again...
			if (getSquare(tmp)->isWater) continue;
			
			//Create child node
			Route newRoute;
			newRoute.previousDistance = bestRoute.previousDistance + 1;
			newRoute.intermediateLocation = tmp;
			newRoute.remainingDistance = distance(tmp, dst); //euclidean wrapped around borders
			newRoute.distance = newRoute.previousDistance + newRoute.remainingDistance;
			newRoute.firstDirection = (bestRoute.firstDirection == -1 ? d : bestRoute.firstDirection);

			routes.insert(pair<double, Route>(newRoute.distance, newRoute));
		}
		
		if (routes.empty())
		{
			bestRoute.distance = MAXDISTANCE;
			bestRoute.firstDirection = -1;
			return bestRoute;	
		}
		
		//Because of the ordering of the map, the first location should be the one with the shortest distance
		bestRoute = routes.begin()->second;
		routes.erase(routes.begin());
	}
	
	if (iterations > MAXITER) bestRoute.distance = MAXDISTANCE;
	
	return bestRoute;
};

//returns the new location from moving in a given direction with the edges wrapped
Location Antmap::getLocation(const Location &loc, int direction)
{
    return Location( (loc.row + DIRECTIONS[direction][0] + rows) % rows,
                     (loc.col + DIRECTIONS[direction][1] + cols) % cols );
};

Location Antmap::randomLocation()
{
	return Location(rand() % rows, rand() % cols);
}

void Antmap::setWater(const size_t row, const size_t col)
{
	getSquare(row, col)->isWater = true;
}

void Antmap::setFood(const size_t row, const size_t col)
{
	getSquare(row, col)->isFood = true;
	food.push_back(Location(row, col));
}

void Antmap::setAnt(const size_t row, const size_t col, int player)
{
	getSquare(row, col)->ant = player;
    if(player == 0)
        myAnts.push_back(Location(row, col));
    else
        enemyAnts.push_back(Location(row, col));
}

void Antmap::setDeadAnt(const size_t row, const size_t col, int player)
{
	getSquare(row, col)->deadAnts.push_back(player);
}

void Antmap::setHill(const size_t row, const size_t col, int player)
{
	getSquare(row, col)->isHill = true;
	getSquare(row, col)->hillPlayer = player;
	
    if(player == 0)
        myHills.push_back(Location(row, col));
    else
        enemyHills.push_back(Location(row, col));
	
}

//Get functions...
Square *Antmap::getSquare(const size_t row, const size_t col)
{
	return &d_grid[row][col];
};

Square *Antmap::getSquare(const Location &loc)
{
	return &d_grid[loc.row][loc.col];
};

Square const *Antmap::getSquare(const size_t row, const size_t col) const
{
	return &d_grid[row][col];
};

Square const *Antmap::getSquare(const Location &loc) const
{
	return &d_grid[loc.row][loc.col];
};

