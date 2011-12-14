#include "Location.h"

using namespace std;

ostream& operator<<(ostream &os, const Location &loc)
{
	return os << "[" << loc.row << "; " << loc.col << "]";
}
