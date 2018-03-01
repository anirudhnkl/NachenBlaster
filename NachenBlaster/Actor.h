#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor: public GraphObject
{
public:
    Actor(StudentWorld * world, int imageID, double startX, double startY, int dir = 0, double size = 1.0, int depth = 0, bool isAlive = true);
    StudentWorld * getWorld() const;
    virtual void setWorld(StudentWorld *world);
    virtual void doSomething();
    virtual bool isAlien() const;
    void setState(bool state);
    bool getState() const;
    
private:
    bool isActorAlive;
    StudentWorld * world;
protected:
    static const int HIT_BY_PROJECTILE = 2552, HIT_BY_CHARACTER = 1235;
};

class Star: public Actor
{
public:
    Star(StudentWorld * world, double startX, double startY);
    virtual void doSomething();
};

class Explosion: public Actor
{
public:
    Explosion(StudentWorld * world, double startX, double startY);
    virtual void doSomething();
private:
    int numOfTicks;
};

class FloatingObject: public Actor
{
public:
    FloatingObject(StudentWorld * world, int imageID, double startX, double startY, int dir = 0);
    virtual void doSomething();
    
private:
    virtual void doSpecialSomething()  = 0;
    virtual bool checkForCollision() = 0;
    virtual bool checkOffScreen() const;
};

class Projectile: public FloatingObject
{
public:
    Projectile(StudentWorld * world, int imageID, double startX, double startY, int damage, bool shotByVillain, int movement, int dir = 0);
    //virtual void doSomething();
protected:
    int getDamage() const;
    //void setDamage(int damage);
    void setMovement(int movement);
    bool getShotByVillain() const;
    void setShotByVillain(bool shotByVillain);
private:
    int damage, movement;
    bool shotByVillain;
    virtual void doSpecialSomething();
    virtual bool checkForCollision();
    virtual bool checkOffScreen() const;
    //bool checkOffScreen(bool shotByVillain) const;
};

class Cabbage: public Projectile
{
public:
    Cabbage(StudentWorld * world, double startX, double startY);
    //virtual void doSomething();
private:
    
};

class Turnip: public Projectile
{
public:
    Turnip(StudentWorld * world, double startX, double startY);
    //virtual void doSomething();
private:
    //virtual bool checkForCollision();
    
};

class FlatulenceTorpedo: public Projectile
{
public:
    FlatulenceTorpedo(StudentWorld * world, double startX, double startY, bool shotByVillain);
    //virtual void doSomething();
private:
    
};

class Character
{
public:
    Character(int ammoCount, int torpedoCount, int hp);
    void incTorpedoCount(int num);
    int getTorpedoCount() const;
    void setAmmoCount(int count);
    int getAmmoCount() const;
    void setHP(int hP);
    int getHP() const;
    void fire(Projectile * projectile, int type) const;
    virtual void damageCharacter(int damage);
    
protected:
    static const int CABBAGE = 1, TURNIP = 2, TORPEDO = 3;

private:
    int hp, ammoCount, torpedoCount;
};

class NachenBlaster: public Actor, public Character //change to Character
{
public:
    NachenBlaster(StudentWorld * world);
    virtual void doSomething();
    int getAmmoPercentage();
    int getHPPercentage();
    virtual void damageCharacter(int damage, int cause);
    //virtual void setWorld(StudentWorld * world);
//    StudentWorld * getWorld() const;
//    void setWorld(StudentWorld *world);
//    void setTorpedoCount(int num);
//    int getTorpedoCount() const;
    
private:
    static const int POS_MOVEMENT = 6, NEG_MOVEMENT = -6;//, CABBAGE = 1, TURNIP = 2, TORPEDO = 3;
    //int hp, cabbageEP, numTorpedoes;
    //StudentWorld * world;
    void moveX(int movement);
    void moveY(int movement);
    //void fire(Projectile *projectile, int type);
};

class Alien: public Character, public FloatingObject
{
public:
    Alien(StudentWorld * world, int imageID, int startX, int startY, int hp, double flightSpeed, int hpReduce, int pointIncrease);
    virtual void doSpecialSomething();
    virtual bool checkForCollision();
    virtual bool isAlien() const;
    //virtual bool checkOffScreen() const;
    virtual bool isNewPlanNeeded() const;
    virtual void selectNewPlan();
    virtual bool attack();
    virtual void move();
    virtual void damageCharacter(int damage, int cause);
    virtual void dropGoodie();
    void die();
    double getFlightSpeed() const;
    void setFlightSpeed(double speed);
    int getFlightDirection() const;
    void setFlightDirection(int direction);
    int getFlightPlanLength() const;
    void setFlightPlanLength(int length);
    int getHPReducer() const;
    void setHPReducer(int hpReducer);
    int getPointIncreaser() const;
    void setPointIncreaser(int pointIncreaser);
    
private:
    double flightSpeed;
    int flightPlan, flightDirection;
    int hpReduce, pointIncrease;
protected:
    static const int DOWNLEFT = 1, UPLEFT = 2, LEFT = 3;
    
};

class Smallgon: public Alien
{
public:
    Smallgon(StudentWorld * world, int startX, int startY);
};

class Smoregon: public Alien
{
public:
    Smoregon(StudentWorld * world, int startX, int startY);
    virtual void dropGoodie();
private:
    virtual bool attack();
};

class Snagglegon: public Alien
{
public:
    Snagglegon(StudentWorld * world, int startX, int startY);
    virtual void dropGoodie();
private:
    //dont need isNewPlanNeeded if u set flightplan to some non zero value
    virtual void setNewPlan();
    virtual bool attack();
    //move?
};

class Goodie: public FloatingObject
{
public:
    Goodie(StudentWorld * world, int imageID, double startX, double startY);
    virtual void doSpecialSomething();
    virtual bool checkForCollision();
    virtual void doGoodieAction(NachenBlaster * blaster) = 0;
    //virtual bool checkOffScreen() const;
};

class ExtraLifeGoodie: public Goodie
{
public:
    ExtraLifeGoodie(StudentWorld * world, double startX, double startY);
    virtual void doGoodieAction(NachenBlaster * blaster);
};

class RepairGoodie: public Goodie
{
public:
    RepairGoodie(StudentWorld * world, double startX, double startY);
    virtual void doGoodieAction(NachenBlaster * blaster);
};

class FlatulenceTorpedoGoodie: public Goodie
{
public:
    FlatulenceTorpedoGoodie(StudentWorld * world, double startX, double startY);
    virtual void doGoodieAction(NachenBlaster * blaster);
};

#endif // ACTOR_H_
