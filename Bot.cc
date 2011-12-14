#include "Bot.h"

using namespace std;

//constructor
Bot::Bot()
{

};

//plays a single game of Ants.
void Bot::playGame()
{
    //reads the game parameters and sets up
    cin >> d_state;
    d_map = d_state.getMap();
    d_map->setup();
    endTurn();

    //continues making moves while the game is not over
    while(cin >> d_state)
    {
        d_state.updateVisionInformation();
        getPersistentObjectInformation<Ant>(d_map->myAnts, &d_ants);
        getPersistentObjectInformation<Food>(d_map->food, &d_food);
        getPersistentObjectInformation<Hill>(d_map->enemyHills, &d_hills);
        makeMoves();
        endTurn();
    }
};

template<typename T> int Bot::getPersistentObjectInformation(vector<Location> visibleStateVector, vector<T> *objectVector)
{
	vector<T> newList;
	
	//Add the unseen objects to make sure thay are remembered
	for (size_t i = 0; i < objectVector->size(); ++i)
		if (!d_map->getSquare(objectVector->at(i).getLocation())->isVisible)
			newList.push_back(objectVector->at(i));
	
	//Add new objects
    for (size_t i = 0; i < visibleStateVector.size(); ++i)
		newList.push_back(getObjectByLocation<T>(visibleStateVector[i], *objectVector));
		
	int ret = visibleStateVector.size() - objectVector->size();
	objectVector->clear();
	*objectVector = newList;
	
	return ret;
}

//Picks an arbitrary object which supports getLocation() from a vector
template<typename T> T Bot::getObjectByLocation(Location &loc, vector<T> vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
		if (vec[i].getLocation() == loc)
			return vec[i];
		
	//Create a new object
	T ret = T(loc, d_map);
	return ret;
}

//makes the bots moves for the turn
void Bot::makeMoves()
{
    d_state.bug << "turn " << d_state.turn << ":" << endl;
    //d_state.bug << d_state << endl;
	
	resolveAntsTargets();
	d_state.bug << "time to resolve targets: " << d_state.timer.getTime() << "ms" << endl << endl;
		
    //picks out moves for each ant
    for (vector<Ant>::iterator iter = d_ants.begin(); iter != d_ants.end(); iter++)
    	iter->act();

    d_state.bug << "time taken: " << d_state.timer.getTime() << "ms" << endl << endl;
};

void Bot::resolveAntsTargets()
{
	int maxAntsOnHill = 1; //Just to initialize, will be conditionally fixed
	double hillWeight = 8; //How much more the ants should want to go to hills instead of food

	vector<Target> targets;
	multimap<double, pair<Ant *, Target *> > distMap;

	if (!d_hills.empty())
	{
		maxAntsOnHill = floor(d_ants.size() / (2 * d_hills.size())); //Maximally have half of all ants chase hills
		for (size_t hill = 0; hill < d_hills.size(); ++hill)
			targets.push_back(Target(Target::HILL, d_hills[hill].getLocation()));
	}
	
	for (size_t food = 0; food < d_food.size(); ++food)
		targets.push_back(Target(Target::FOOD, d_food[food].getLocation()));
		
	Ant *tmpAnt;
	Target *tmpTarget;
	pair<Ant *, Target *> combo;
	
	for (size_t t = 0; t < targets.size(); ++t)
	{
		tmpTarget = &targets[t];
		
		for (size_t ant = 0; ant < d_ants.size(); ++ant)
		{
			tmpAnt = &d_ants[ant];
			
			combo = pair<Ant *, Target *>(tmpAnt, tmpTarget);
			double distance = d_map->distance(tmpAnt->getLocation(), tmpTarget->getLocation());
			if (tmpTarget->getType() == Target::HILL) distance /= hillWeight;
			
			distMap.insert(pair<double, pair<Ant *, Target *> >(distance, combo));
		}
	}
	
	int cnt = 0;
	int maxAnts = 0;
	while (!distMap.empty())
	{
		if (cnt++ > MAXITER) break;
	
		combo = distMap.begin()->second;
		combo.first->setTarget(*combo.second);
		combo.second->setAnts(combo.second->ants() + 1);
		
		maxAnts = (combo.second->getType() == Target::HILL ? maxAntsOnHill : 1);
		
		for (map<double, pair<Ant *, Target *> >::iterator iter = distMap.begin(); iter != distMap.end(); ++iter)
			if (iter->second.first->getLocation() == combo.first->getLocation() || iter->second.second->ants() >= maxAnts)
				distMap.erase(iter);
	}
}

//finishes the turn
void Bot::endTurn()
{
    if(d_state.turn > 0)
        d_map->reset();
    d_state.turn++;

    cout << "go" << endl;
};
