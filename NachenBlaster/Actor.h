#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor: public GraphObject
{
public:
    Actor(int imageID, double startX, double startY, int dir = 0, double size = 1.0, int depth = 0, bool isAlive = true);
    virtual void doSomething();
    void setState(bool state);
    bool getState() const;
    
private:
    bool isActorAlive;
};

class Star: public Actor
{
public:
    Star(double startX, double startY);
    virtual void doSomething();
};

class Explosion: public Actor
{
public:
    Explosion(double startX, double startY);
    virtual void doSomething();
private:
    int numOfTicks;
};

class FloatingObject: public Actor
{
public:
    FloatingObject(int imageID, double startX, double startY, int dir = 0);
    virtual void doSomething();
    
private:
    virtual void doSpecialSomething()  = 0;
    virtual void checkForCollision() = 0;
    virtual bool checkOffScreen() const = 0;
};

class Projectile: public FloatingObject
{
public:
    Projectile(int imageID, double startX, double startY, int damage, bool shotByVillain, int movement, int dir = 0);
    //virtual void doSomething();
protected:
    int getDamage() const;
    void setDamage(int damage);
    void setMovement(int movement);
    bool getShotByVillain() const;
    void setShotByVillain(bool shotByVillain);
private:
    int damage, movement;
    bool shotByVillain;
    virtual void doSpecialSomething();
    virtual void checkForCollision();
    virtual bool checkOffScreen() const;
    //bool checkOffScreen(bool shotByVillain) const;
};

class Cabbage: public Projectile
{
public:
    Cabbage(double startX, double startY);
    //virtual void doSomething();
private:
    
};

class Turnip: public Projectile
{
public:
    Turnip(double startX, double startY);
    //virtual void doSomething();
private:
    
};

class FlatulenceTorpedo: public Projectile
{
public:
    FlatulenceTorpedo(double startX, double startY, bool shotByVillain);
    //virtual void doSomething();
private:
    
};

class Goodie: public FloatingObject
{
public:
    Goodie(int imageID, double startX, double startY);
private:
    virtual void doSpecialSomething();
    virtual void checkForCollision();
    virtual bool checkOffScreen() const;
};

class ExtraLifeGoodie: public Goodie
{
public:
    ExtraLifeGoodie(double startX, double startY);
};

//class Character: public Actor
//{
//public:
//    Character();
//    virtual void doSomething();
//    StudentWorld * getWorld() const;
//    void setWorld(StudentWorld *world);
//    void setTorpedoCount(int num);
//    int getTorpedoCount() const;
//    void setAmmoCount(int count);
//    int getAmmoCount() const;
//
//private:
//    static const int CABBAGE = 1, TURNIP = 2, TORPEDO = 3;
//    int hp, ammoCount, torpedoCount;
//    StudentWorld * world;
//    void fire(Projectile * projectile, int type);
//};

class NachenBlaster: public Actor //change to Character
{
public:
    NachenBlaster();
    virtual void doSomething();
    StudentWorld * getWorld() const;
    void setWorld(StudentWorld *world);
    void setTorpedoCount(int num);
    int getTorpedoCount() const;
    
private:
    static const int POS_MOVEMENT = 6, NEG_MOVEMENT = -6, CABBAGE = 1, TURNIP = 2, TORPEDO = 3;
    int hp, cabbageEP, numTorpedoes;
    StudentWorld * world;
    void moveX(int movement);
    void moveY(int movement);
    void fire(Projectile *projectile, int type);
};

#endif // ACTOR_H_
