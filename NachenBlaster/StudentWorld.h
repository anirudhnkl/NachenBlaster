#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>

class Actor;
class NachenBlaster;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void addActor(Actor &actor);
    ~StudentWorld();

private:
    std::vector<Actor*> actors;
    NachenBlaster * nachenBlaster;
};

#endif // STUDENTWORLD_H_
