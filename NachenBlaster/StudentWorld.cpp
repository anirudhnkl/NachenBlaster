#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <math.h>
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
    nachenBlaster = new NachenBlaster(this);
    actors.push_back(nachenBlaster);
    
    numDestroyedAliens = 0;
    numCurrentAliens = 0;
    numAliensOnScreen = 0;
    
    
    for(int i = 0; i < 30; i++)
        actors.push_back(new Star(this, randInt(0, VIEW_WIDTH-1),randInt(0, VIEW_HEIGHT-1)));
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //decLives();
    
    
    if(randInt(1, 15) == 3)
        actors.push_back(new Star(this, VIEW_WIDTH-1,randInt(0, VIEW_HEIGHT-1)));
    addAlien();
    for(vector<Actor *>::iterator iter = actors.begin(); iter != actors.end(); iter++)
    {
        if((*iter)->getState())
        {
            (*iter)->doSomething();
        
            if(!nachenBlaster->getState())
            {
                decLives();
                return GWSTATUS_PLAYER_DIED;
            }
            
            if(numDestroyedAliens >= 6 + 4*getLevel())
                return GWSTATUS_FINISHED_LEVEL;
        }
    }
    
    for(vector<Actor *>::iterator iter = actors.begin(); iter != actors.end(); )
    {
        if(!(*iter)->getState())
        {
            if((*iter)->isAlien())
                numAliensOnScreen--;
            delete *iter;
            iter = actors.erase(iter);
        }
        else
            iter++;
    }
    
    updateDisplayText();
    
    return GWSTATUS_CONTINUE_GAME;
    //return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::addAlien()
{
    int r = (6 + 4 * getLevel()) - numDestroyedAliens;
    int m = 4 + (0.5 * getLevel());
    
    if(numAliensOnScreen < min(m, r))
    {
        int s1 = 60, s2 = 20 + getLevel()*5, s3 = 5 + getLevel()*10;
        int s = s1 + s2 + s3;
        int rand = randInt(1, s);
        
        if(rand >= 1 && rand <= s1)
            actors.push_back(new Smallgon(this, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1)));
        
        else if(rand > s1 && rand <= s1 + s2)
            actors.push_back(new Smoregon(this, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1)));
        
        else
            actors.push_back(new Snagglegon(this, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT - 1)));
        
        numCurrentAliens++;
        numAliensOnScreen++;
    }
}

Alien * StudentWorld::getOneCollidingAlien(const Actor* a) const
{
    double dis = 0;
    for(int i = 0; i < actors.size(); i++)
    {
        if(actors[i]->isAlien())
        {
            dis = sqrt( pow(actors[i]->getX() - a->getX(), 2) +  pow(actors[i]->getY() - a->getY(), 2));
            if(dis < 0.75 * (actors[i]->getRadius() + a->getRadius()))
                return dynamic_cast<Alien*>(actors[i]);
        }
    }
    
    return nullptr;
}

NachenBlaster * StudentWorld::getCollidingPlayer(const Actor* a) const
{
    double dis = sqrt( pow(nachenBlaster->getX() - a->getX(), 2) +  pow(nachenBlaster->getY() - a->getY(), 2));
    
    if(dis < 0.75 * (nachenBlaster->getRadius() + a->getRadius()))
        return nachenBlaster;
    
    return nullptr;
}

void StudentWorld::updateDisplayText()
{
    ostringstream oss;
    oss << "Lives: " << getLives() << "  Health: " << nachenBlaster->getHPPercentage() << "%  Score: " << getScore() << "  Level: " ;
    oss << getLevel() << "  Cabbages: " << nachenBlaster->getAmmoPercentage() <<"%  Torpedoes: " << nachenBlaster->getTorpedoCount();
    setGameStatText(oss.str());
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

void StudentWorld::addActor(Actor * actor)
{
    actors.push_back(actor);
}

bool StudentWorld::isNachenInLineOfFire(const Actor * a) const
{
    if(nachenBlaster->getX() < a->getX() && a->getY() <= nachenBlaster->getY() + 4 && a->getY() >= nachenBlaster->getY() - 4 )
        return true;
    return false;
}

void StudentWorld::recordAlienDying()
{
    numDestroyedAliens++;
}
