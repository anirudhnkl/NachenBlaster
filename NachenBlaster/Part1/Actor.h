#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor: public GraphObject
{
public:
    Actor(int imageID, double startX, double startY, int dir = 0, double size = 1.0, int depth = 0, int state = 1);
    virtual void doSomething();
    
protected:
    const int DEAD_STATE = 0;
    const int ALIVE_STATE = 1;
    void setState(int state);
    int getState() const;
    
private:
    int actorState;
};

class Star: public Actor
{
public:
    Star(double startX, double startY);
    virtual void doSomething();
private:
    
    
};

//class Character: public GraphObject
//{
//public:
//    Character();
//private:
//    virtual void doSomething();
//};

class NachenBlaster: public Actor //change to Character
{
public:
    NachenBlaster();
    virtual void doSomething();
    StudentWorld * getWorld();
    void setWorld(StudentWorld * world);
private:
    const int POS_MOVEMENT = 6;
    const int NEG_MOVEMENT = -6;
    int hp, cabbageEP;
    StudentWorld * world;
    void moveX(int movement);
    void moveY(int movement);
    
};

#endif // ACTOR_H_
