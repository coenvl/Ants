#include "Ant.h"

using namespace std;

void Ant::act()
{
	bool act = false;
	
	if (!act) act = approachTarget();
	
	if (!act) act = explore();
	
	//if (!act) act = tryMove(-1); //Try to just standstill
		
	if (!act) act = getAway(); //If this doesn't succeed, you WILL be trampled
		
	d_map->getSquare(d_location)->isTaken = true;

	d_nomove = (act ? 0 : d_nomove + 1);
};

//Output the ant's movement to the engine
bool Ant::tryMove(int direction)
{
	Location newLocation = (direction == -1 ? d_location : d_map->getLocation(d_location, direction));
	
	if (newLocation == d_previousLocation && d_nomove < 3) return false;
	
	//Update map
	Square *source = d_map->getSquare(d_location);
	Square *target = d_map->getSquare(newLocation);
	
	if (target->isTaken || target->isWater)
		return false;
	
	//target->isTaken = true; //<-- handled in Ant::act() now
    target->ant = source->ant;
    source->ant = -1;

	//Do move
	cout << "o " << d_location.row << " " << d_location.col << " " << CDIRECTIONS[direction] << endl;
	d_previousLocation = d_location;
	d_location = newLocation;
	d_lastDirection = direction;
	
	return true;
}

bool Ant::explore()
{
	Route preferredRoute = d_map->bestRoute(d_location, d_preferredLocation);
	if (preferredRoute.distance == MAXDISTANCE) return false;

	while (preferredRoute.distance <= 1 || preferredRoute.distance == MAXDISTANCE)
	{
		d_preferredLocation = d_map->randomLocation();
		preferredRoute = d_map->bestRoute(d_location, d_preferredLocation);
	}
	
	return (tryMove(preferredRoute.firstDirection) ? true : getCloser(d_preferredLocation));
};

//Simply try to reduce the manhattan distance to a location
bool Ant::getCloser(Location &loc)
{
	double tmp;
	map<double, int> dist;
	dist.clear();
	
	for (int d = 0; d < TDIRECTIONS; d++)
	{
		tmp = d_map->squaredDistance(d_location, loc);
		dist[tmp] = d;
	}
	
	//Try the directions in order in which they are nearer to the target
	for (map<double, int>::iterator iter = dist.begin(); iter != dist.end(); iter++)
		if (tryMove(iter->second)) return true;
		
	return false;
}

bool Ant::getAway()
{
	for(int d = 0; d < TDIRECTIONS; d++)
		if (tryMove(d)) return true;
		
	return false;
}

bool Ant::approachTarget()
{
	if (d_target.getType() == Target::NONE) return false;
	Location targetLocation = d_target.getLocation();
	
	if (!(d_map->getSquare(targetLocation)->isFood || d_map->getSquare(targetLocation)->isHill)) //Reset as soon as target has disappeared
	{
		d_target.reset();
		return false;
	}
	
	Route bestRoute = d_map->bestRoute(d_location, targetLocation);
	if (bestRoute.distance == MAXDISTANCE) return false;
		
	return (tryMove(bestRoute.firstDirection) ? true : getCloser(d_target.getLocation()));
}
