#ifndef LOCATION_H_
#define LOCATION_H_

#include <iostream>

/*
    struct for representing locations in the grid.
*/
class Location
{
	public:
		int row, col;
	
		Location()
		{
			row = col = 0;
		};
	
		Location(int r, int c)
		{
			row = r;
			col = c;
		};
		
		bool operator==(const Location other) const
		{
			return (row == other.row && col == other.col);
		};
		
		bool operator!=(const Location other) const
		{
			return (row != other.row || col != other.col);
		};
		
		bool operator<(const Location other) const
		{
			return (row < other.row ? true : col < other.col);
		};
	
		bool operator>(const Location other) const
		{
			return (row > other.row ? true : col > other.col);
		};
		
		bool operator<=(const Location other) const
		{
			return (row > other.row ? false : col <= other.col);
		};
	
		bool operator>=(const Location other) const
		{
			return (row < other.row ? false : col <= other.col);
		}
};

std::ostream& operator<<(std::ostream &os, const Location &loc);

#endif //LOCATION_H_
