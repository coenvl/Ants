#ifndef _INCLUDED_ANT_
#define _INCLUDED_ANT_

#include <vector>
#include <iostream>
#include "Location.h"
#include "Target.h"
#include "Antmap.h"
#include "Food.h"

class Ant
{
	
	Location d_location;
	Target d_target;
	Antmap *d_map;
	
	Location d_preferredLocation;
	Location d_previousLocation;

	//std::vector<Ant> *d_ants;
	int d_lastDirection;
	int d_nomove;
	
	public:
		Ant()
		:
			d_lastDirection(-1),
			d_nomove(0)
		{
		};
		
		Ant(Location loc, Antmap *map)
		:
			d_location(loc),
			d_map(map),
			d_lastDirection(-1),
			d_nomove(0)
		{
			d_preferredLocation = map->randomLocation();
		};
	
		void act();
		
		inline Location &getLocation()
		{
			return d_location;
		}
		
		inline Target getTarget()
		{
			return d_target;
		}
		
		inline Target setTarget(Target target)
		{
			return d_target = target;
		}
		
		bool operator==(Ant &other)
		{
			return (other.getLocation() == d_location);
		}
		
	private:
		bool approachTarget();
		bool explore();
		bool getAway();
		bool getCloser(Location &loc);
		
		bool tryMove(int direction);  
};

#endif //BOT_H_
