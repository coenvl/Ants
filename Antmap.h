#ifndef _INCLUDED_ANTMAP_
#define _INCLUDED_ANTMAP_

#include <cstdlib>
#include <vector>
#include <cmath>
#include <map>
#include <set>
#include "Square.h"
#include "Location.h"

const int TDIRECTIONS = 4;
const char CDIRECTIONS[4] = {'N', 'E', 'S', 'W'};
const int DIRECTIONS[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };      //{N, E, S, W}

const int MAXDISTANCE = 9999;
const int MAXITER = 5000; //maximum number of iterations in A* to avoid too expensive computation

struct Route
{
	int firstDirection;
	double remainingDistance;
	double previousDistance;
	double distance;
	Location intermediateLocation;
};

class Antmap
{
    std::vector<std::vector<Square> > d_grid;
    
    public:
		int rows, cols;
		std::vector<Location> myAnts, enemyAnts, myHills, enemyHills, food;
		
		Antmap();
		
		void setup();
		void reset();

		double distance(const Location &loc1, const Location &loc2);
		int manhattanDistance(const Location &loc1, const Location &loc2);
		int squaredDistance(const Location &loc1, const Location &loc2);
		Route bestRoute(const Location &loc1, const Location &loc2);
		Location getLocation(const Location &startLoc, int direction);
		Location randomLocation();
	
		Square *getSquare(const Location &loc);
		Square *getSquare(const size_t row, const size_t col);

		Square const *getSquare(const Location &loc) const;
		Square const *getSquare(const size_t row, const size_t col) const;
		
		void setWater(const size_t row, const size_t col);
		void setFood(const size_t row, const size_t col);
		void setAnt(const size_t row, const size_t col, int player);
		void setDeadAnt(const size_t row, const size_t col, int player);
		void setHill(const size_t row, const size_t col, int player);
		
};

#endif //STATE_H_
