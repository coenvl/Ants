#include "State.h"

using namespace std;

//constructor
State::State()
{
	d_map = Antmap();
    gameover = 0;
    turn = 0;
    bug.open("./debug.txt");
};

//deconstructor
State::~State()
{
    bug.close();
};

/*
    This function will update update the lastSeen value for any squares currently
    visible by one of your live ants.

    BE VERY CAREFUL IF YOU ARE GOING TO TRY AND MAKE THIS FUNCTION MORE EFFICIENT,
    THE OBVIOUS WAY OF TRYING TO IMPROVE IT BREAKS USING THE EUCLIDEAN METRIC, FOR
    A CORRECT MORE EFFICIENT IMPLEMENTATION, TAKE A LOOK AT THE GET_VISION FUNCTION
    IN ANTS.PY ON THE CONTESTS GITHUB PAGE.
*/
void State::updateVisionInformation()
{
    std::queue<Location> locQueue;
    Location sLoc, cLoc, nLoc;

    for(int a=0; a<(int) d_map.myAnts.size(); a++)
    {
        sLoc = d_map.myAnts[a];
        locQueue.push(sLoc);

        std::vector<std::vector<bool> > visited(d_map.rows, std::vector<bool>(d_map.cols, 0));
        d_map.getSquare(sLoc)->isVisible = 1;
        visited[sLoc.row][sLoc.col] = 1;

        while(!locQueue.empty())
        {
            cLoc = locQueue.front();
            locQueue.pop();

            for(int d=0; d<TDIRECTIONS; d++)
            {
                nLoc = d_map.getLocation(cLoc, d);

                if(!visited[nLoc.row][nLoc.col] && d_map.distance(sLoc, nLoc) <= viewradius)
                {
                    d_map.getSquare(nLoc)->isVisible = 1;
                    //d_map.getSquare(nLoc)->isExplored = true;
                    locQueue.push(nLoc);
                }
                visited[nLoc.row][nLoc.col] = 1;
            }
        }
    }
};

/*
    This is the output function for a state. It will add a char map
    representation of the state to the output stream passed to it.

    For example, you might call "cout << state << endl;"
*/
ostream& operator<<(ostream &os, const State &state)
{
    for(int row=0; row < state.getMap()->rows; row++)
    { 
        for(int col=0; col < state.getMap()->cols; col++)
        {
        	Square const *square = state.getSquare(row,col);
            if(square->isWater)
                os << '%';
            else if(square->isFood)
                os << '*';
            else if(square->isHill)
                os << (char)('A' + square->hillPlayer);
            else if(square->ant >= 0)
                os << (char)('a' + square->ant);
            else if(square->isTaken)
                os << ',';
            else if(square->isVisible)
                os << '.';
            else
                os << '?';
        }
        os << endl;
    }

    return os;
};

//input function
istream& operator>>(istream &is, State &state)
{
    int row, col, player;
    string inputType, junk;

    //finds out which turn it is
    while(is >> inputType)
    {
        if(inputType == "end")
        {
            state.gameover = 1;
            break;
        }
        else if(inputType == "turn")
        {
            is >> state.turn;
            break;
        }
        else //unknown line
            getline(is, junk);
    }

    if(state.turn == 0)
    {
        //reads game parameters
        while(is >> inputType)
        {
            if(inputType == "loadtime")
                is >> state.loadtime;
            else if(inputType == "turntime")
                is >> state.turntime;
            else if(inputType == "rows")
                is >> state.getMap()->rows;
            else if(inputType == "cols")
                is >> state.getMap()->cols;
            else if(inputType == "turns")
                is >> state.turns;
            else if(inputType == "player_seed")
                is >> state.seed;
            else if(inputType == "viewradius2")
            {
                is >> state.viewradius;
                state.viewradius = sqrt(state.viewradius);
            }
            else if(inputType == "attackradius2")
            {
                is >> state.attackradius;
                state.attackradius = sqrt(state.attackradius);
            }
            else if(inputType == "spawnradius2")
            {
                is >> state.spawnradius;
                state.spawnradius = sqrt(state.spawnradius);
            }
            else if(inputType == "ready") //end of parameter input
            {
                state.timer.start();
                break;
            }
            else    //unknown line
                getline(is, junk);
        }
    }
    else
    {
        //reads information about the current turn
        while(is >> inputType)
        {
            if(inputType == "w") //water square
            {
                is >> row >> col;
                state.getMap()->setWater(row, col);
            }
            else if(inputType == "f") //food square
            {
                is >> row >> col;
                state.getMap()->setFood(row, col);
            }
            else if(inputType == "a") //live ant square
            {
                is >> row >> col >> player;
				state.getMap()->setAnt(row, col, player);
            }
            else if(inputType == "d") //dead ant square
            {
                is >> row >> col >> player;
                state.getMap()->setDeadAnt(row, col, player);
            }
            else if(inputType == "h")
            {
                is >> row >> col >> player;
				state.getMap()->setHill(row, col, player);
            }
            else if(inputType == "players") //player information
                is >> state.noPlayers;
            else if(inputType == "scores") //score information
            {
                state.scores = vector<double>(state.noPlayers, 0.0);
                for(int p=0; p<state.noPlayers; p++)
                    is >> state.scores[p];
            }
            else if(inputType == "go") //end of turn input
            {
                if(state.gameover)
                    is.setstate(std::ios::failbit);
                else
                    state.timer.start();
                break;
            }
            else //unknown line
                getline(is, junk);
        }
    }

    return is;
};

//Stupid get functions....
Square *State::getSquare(const size_t row, const size_t col)
{
	return d_map.getSquare(row, col);
}

Square const *State::getSquare(const size_t row, const size_t col) const
{
	return d_map.getSquare(row, col);
}

Square *State::getSquare(const Location loc)
{
	return d_map.getSquare(loc);
}

Square const *State::getSquare(const Location loc) const
{
	return d_map.getSquare(loc);
}

Antmap *State::getMap()
{
	return &d_map;
}

Antmap const *State::getMap() const
{
	return &d_map;
}
