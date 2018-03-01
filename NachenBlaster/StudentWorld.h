#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>

class Actor;
class Alien;
class Projectile;
class NachenBlaster;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void recordAlienDying();
    bool isNachenInLineOfFire(const Actor * a) const;
    Alien * getOneCollidingAlien(const Actor* a) const;
    //Projectile * getCollidingProjectile(const Actor* a) const;
    NachenBlaster * getCollidingPlayer(const Actor* a) const;
    void addActor(Actor * actor);
    void updateDisplayText();
    void addAlien();
    ~StudentWorld();

private:
    std::vector<Actor*> actors;
    NachenBlaster * nachenBlaster;
    int numDestroyedAliens;
    int numCurrentAliens;
    int numAliensOnScreen;
};

#endif // STUDENTWORLD_H_
