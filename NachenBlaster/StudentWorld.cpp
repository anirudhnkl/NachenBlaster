#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir)
{
    //initialize data members
}

StudentWorld::~StudentWorld()
{
    //free data remaining
    cleanUp();
}

int StudentWorld::init()
{
    nachenBlaster = new NachenBlaster();
    nachenBlaster->setWorld(this);
    actors.push_back(nachenBlaster);
    
    for(int i = 0; i < 30; i++)
        actors.push_back(new Star(randInt(0, VIEW_WIDTH-1),randInt(0, VIEW_HEIGHT-1)));
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //decLives();
    
    if(randInt(1, 15) == 3)
        actors.push_back(new Star(VIEW_WIDTH-1,randInt(0, VIEW_HEIGHT-1)));
    for(vector<Actor *>::iterator iter = actors.begin(); iter != actors.end(); iter++)
    {
        if((*iter)->getState())
        {
            (*iter)->doSomething();
        
            if(!nachenBlaster->getState())
            {
                //decLives(); do i do this??
                return GWSTATUS_PLAYER_DIED;
            }
            //if # of alien ships destoryed is enough increaseScore()    return GWSTATUS_FINISHED_LEVEL;
        }
    }
    
    for(vector<Actor *>::iterator iter = actors.begin(); iter != actors.end(); )
    {
        if(!(*iter)->getState())
        {
            delete *iter;
            iter = actors.erase(iter);
        }
        else
            iter++;
    }
    
    //update status test on the top screen
    
    return GWSTATUS_CONTINUE_GAME;
    //return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
//    for(int i = 0; i < actors.size(); i++)
//    {
//        delete actors[i];
//    }
    
    for(vector<Actor *>::iterator iter = actors.begin(); iter != actors.end();)
    {
        delete *iter;
        iter = actors.erase(iter);
    }
}

void StudentWorld::addActor(Actor &actor)
{
    actors.push_back(&actor);
}
