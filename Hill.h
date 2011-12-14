#ifndef _INCLUDED_HILL_
#define _INCLUDED_HILL_

#include "Location.h"

class Hill
{
	Location d_location;
	bool d_active;
	
	public:
		Hill(Location &loc, Antmap * map)
		:
			d_location(loc),
			d_active(false)
		{
		};
		
		inline Location &getLocation()
		{
			return d_location;
		}
		
		inline bool active()
		{
			return d_active;
		}
		
		inline bool setActive(bool a)
		{
			return d_active = a;
		}
		
		bool operator==(Hill &other) const
		{
			return d_location == other.getLocation();
		}
		
		bool operator<(Hill &other) const
		{
			return d_location < other.getLocation();
		}
};

#endif //_INCLUDED_HILL_
