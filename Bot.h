#ifndef BOT_H_
#define BOT_H_

#include <vector>
#include <map>
#include "State.h"
#include "Antmap.h"
#include "Ant.h"
#include "Food.h"
#include "Hill.h"

/*
    This struct represents your bot in the game of Ants
*/
class Bot
{
	State d_state;
	Antmap *d_map;
	std::vector<Hill> d_hills;
	std::vector<Ant> d_ants;
	std::vector<Food> d_food;
	
	public:	
		Bot();
	
		void playGame();    //plays a single game of Ants
		void makeMoves();   //makes moves for a single turn
		void endTurn();     //indicates to the engine that it has made its moves
		
	private:
		//int getAntInformation();
		//int getFoodInformation();
		//int getHillInformation();
		template<class T> int getPersistentObjectInformation(std::vector<Location> visibleStateVector, std::vector<T> *objectVector);
				
		//Ant getAntByLocation(Location &loc);
		//Food getFoodByLocation(Location &loc);
		//Hill getHillByLocation(Location &loc);
		template<class T> T getObjectByLocation(Location &loc, std::vector<T> vec);
		//void resolveAntsFoods();
		//void resolveAntsHills();
		void resolveAntsTargets();
};

#endif //BOT_H_
