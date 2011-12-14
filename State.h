#ifndef STATE_H_
#define STATE_H_

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <stdint.h>

#include "Timer.h"
#include "Bug.h"
#include "Square.h"
#include "Location.h"
#include "Antmap.h"

/*
    struct to store current state information
*/
class State
{
    Antmap d_map;
    
    public:
	    // int rows, cols;
		int turn, turns, noPlayers;
		double attackradius, spawnradius, viewradius;
		double loadtime, turntime;
		std::vector<double> scores;
		bool gameover;
		int64_t seed;
	
		Timer timer;
		Bug bug;
	
		/*
			Functions
		*/
		State();
		~State();
	
		//void makeMove(const Location &loc, int direction);
	
		Square *getSquare(const size_t row, const size_t col);
		Square *getSquare(const Location loc);
		Antmap *getMap();
		
		Square const *getSquare(const size_t row, const size_t col) const;
		Square const *getSquare(const Location loc) const;
		Antmap const *getMap() const;
	
		void updateVisionInformation();
};

std::ostream& operator<<(std::ostream &os, const State &state);
std::istream& operator>>(std::istream &is, State &state);

#endif //STATE_H_
