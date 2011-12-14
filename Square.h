#ifndef SQUARE_H_
#define SQUARE_H_

#include <vector>

/*
    struct for representing a square in the grid.
*/
struct Square
{
    bool isVisible, isWater, isHill, isFood, isTaken, isExplored;
    int ant, hillPlayer;
    std::vector<int> deadAnts;

    Square()
    {
        isExplored = isTaken = isVisible = isWater = isHill = isFood = false;
        ant = hillPlayer = -1;
    };

    //resets the information for the square except water information
    void reset()
    {
    	//Only isWater and isExplored are persistent....
    	isTaken = isVisible = isHill = isFood = false;
        ant = hillPlayer = -1;
        deadAnts.clear();
    };
};

#endif //SQUARE_H_
