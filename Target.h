#ifndef _INCLUDED_TARGET_
#define _INCLUDED_TARGET_

#include "Location.h"

class Target
{
	public:
		enum Type 
		{
			NONE = 0,
			FOOD,
			HILL,
			ANT,
			DEFEND
		};
	
	private:
		Type d_type;
		Location d_location;
		int d_ants;
		
	public:
		Target()
		:
			d_type(NONE),
			d_ants(0)
		{
		};
		
		Target(Type type, Location loc)
		:
			d_type(type),
			d_location(loc),
			d_ants(0)
		{
		};
		
		inline Type &getType()
		{
			return d_type;
		};
		
		inline Location &getLocation()
		{
			return d_location;
		};
		
		inline void reset()
		{
			d_type = NONE;
		};
		
		bool operator==(Target &other)
		{
			return (other.getType() == d_type && other.getLocation() == d_location);
		}
		
		inline int ants()
		{
			return d_ants;
		}
		
		inline void setAnts(int n)
		{
			d_ants = n;
		}
};

#endif //STATE_H_
