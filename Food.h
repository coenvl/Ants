#ifndef _INCLUDED_FOOD_
#define _INCLUDED_FOOD_

#include "Location.h"

class Food
{
	Location d_location;
	bool d_claimed;
	int d_claimDist;
	
	public:
		Food()
		:
			d_claimed(false)
		{
		};
		
		Food(Location &loc, Antmap * map)
		:
			d_location(loc),
			d_claimed(false)
		{
		};
		
		inline Location &getLocation()
		{
			return d_location;
		}
		
		inline bool isClaimed()
		{
			return d_claimed;
		}
		
		inline void claim()
		{
			d_claimed = true;
		}
};

#endif //BOT_H_
