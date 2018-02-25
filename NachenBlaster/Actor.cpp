#include "Actor.h"
#include "StudentWorld.h"
//#include <iostream>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


Actor::Actor(int imageID, double startX, double startY, int dir, double size, int depth, bool isAlive):
    GraphObject(imageID, startX, startY, dir, size, depth), isActorAlive(isAlive)
{
    
}

bool Actor::getState() const
{
    return isActorAlive;
}

void Actor::setState(bool state)
{
    isActorAlive = state;
}

void Actor::doSomething()
{
}

Star::Star(double startX, double startY):
    Actor(IID_STAR, startX, startY, 0, .06, 3)
{
    setSize(((randInt(500, 5000))/10000.0));
}

void Star::doSomething()
{
    moveTo(getX()-1, getY());
    if(getX() <= -1)
        setState(false);
}

Explosion::Explosion(double startX, double startY):
Actor(IID_EXPLOSION, startX, startY, 0, 1), numOfTicks(0)
{
}

void Explosion::doSomething()
{
    if(numOfTicks == 4)
    {
        setState(false);
        return;
    }
    
    setSize(1.5*getSize());
    numOfTicks++;
}


NachenBlaster::NachenBlaster():
Actor(IID_NACHENBLASTER, 0, 128), hp(50), cabbageEP(30), numTorpedoes(0)
{
}

void NachenBlaster::doSomething()
{
    if(!getState())
        return;
    
    cabbageEP++;
    int key;
    if(getWorld()->getKey(key))
    {
        switch (key)
        {
            case KEY_PRESS_SPACE:
                fire(new Cabbage(getX() + 12, getY()), CABBAGE);
                cabbageEP -= 5;
                break;
            case KEY_PRESS_TAB:
                //fire a torpedo
                //reduce torpedo count by 1
                break;
            case KEY_PRESS_LEFT:
                moveX(NEG_MOVEMENT);
                break;
            case KEY_PRESS_RIGHT:
                moveX(POS_MOVEMENT);
                break;
            case KEY_PRESS_UP:
                moveY(POS_MOVEMENT);
                break;
            case KEY_PRESS_DOWN:
                moveY(NEG_MOVEMENT);
                break;
        }
    }
    if(cabbageEP < 30) cabbageEP++;
}

void NachenBlaster::moveX(int movement)
{
    if(getX() + movement < VIEW_WIDTH || getX() + movement >= 0)
        moveTo(getX() + movement, getY());
}

void NachenBlaster::moveY(int movement)
{
    if(getY() + movement < VIEW_HEIGHT || getY() + movement >= 0)
        moveTo(getX(), getY() + movement);
}

void NachenBlaster::setWorld(StudentWorld * world)
{
    this->world = world;
}

StudentWorld * NachenBlaster::getWorld() const
{
    return world;
}

void NachenBlaster::setTorpedoCount(int num)
{
    numTorpedoes = num;
}

int NachenBlaster::getTorpedoCount() const
{
    return numTorpedoes;
}

void NachenBlaster::fire(Projectile  * projectile, int type)
{
    StudentWorld * world = getWorld();
    world->addActor(*projectile);
    
    switch (type)
    {
        case CABBAGE:
            world->playSound(SOUND_PLAYER_SHOOT);
            break;
        case TURNIP:
            world->playSound(SOUND_ALIEN_SHOOT);
            break;
        case TORPEDO:
            world->playSound(SOUND_TORPEDO);
            break;
    }
}

FloatingObject::FloatingObject(int imageID, double startX, double startY, int dir):
    Actor(imageID, startX, startY, dir, 0.5, 1)
{
    
}

void FloatingObject::doSomething()
{
    if(!getState()) //do this either in Actor or character class
        return;
    if(checkOffScreen())
    {
        setState(false);
        return;
    }
    
    //checkCollision();
    doSpecialSomething();
    //checkCollision();
}

Projectile::Projectile(int imageID, double startX, double startY, int damage, bool shotByVillain, int movement, int dir):
    FloatingObject(imageID, startX, startY, dir), damage(damage), shotByVillain(shotByVillain), movement(movement)
{
    
}
//Projectile::Projectile(int imageID, double startX, double startY, int damage, bool shotByVillain, int movement, int dir):
//    Actor(imageID, startX, startY, dir, 0.5, 1), damage(damage), shotByVillain(shotByVillain), movement(movement)
//{
//}

//void Projectile::doSomething()
//{
//    if(!getState()) //do this either in Actor or character class
//        return;
//    checkOffScreen(shotByVillain);
//    //checkCollision(shotByVillain);
//    moveTo(getX() + movement, getY());
//    setDirection(20 + getDirection());
//    //checkCollision(shotByVillain);
//}

void Projectile::doSpecialSomething()
{
    moveTo(getX() + movement, getY());
    setDirection(20 + getDirection());
}

bool Projectile::checkOffScreen() const
{
    if(shotByVillain)
    {
        if(getX() < 0)
            return true;
    }
    
    else
    {
        if(getX() >= VIEW_WIDTH)
            return true;
    }
    
    return false;
}

void Projectile::checkForCollision()
{
    
}

void Projectile::setMovement(int movement)
{
    this->movement = movement;
}

Cabbage::Cabbage(double startX, double startY):
    Projectile(IID_CABBAGE, startX, startY, 2, false, 8)
{
    
}

//void Cabbage::doSomething()
//{
//    Projectile::doSomething();
//}

Turnip::Turnip(double startX, double startY):
Projectile(IID_TURNIP, startX, startY, 2, true, -6)
{
    
}

//void Turnip::doSomething()
//{
//    Projectile::doSomething();
//}

FlatulenceTorpedo::FlatulenceTorpedo(double startX, double startY, bool shotByVillain):
Projectile(IID_TORPEDO, startX, startY, 2, shotByVillain, 8)
{
    if(shotByVillain)
        setMovement(-8);
}

//void FlatulenceTorpedo::doSomething()
//{
//    Projectile::doSomething();
//}

Goodie::Goodie(int imageID, double startX, double startY):
    FloatingObject(imageID, startX, startY)
{
    
}

void Goodie::doSpecialSomething()
{
    moveTo(getX() - 0.75, getY() - 0.75);
}

void Goodie::checkForCollision()
{
    
}

bool Goodie::checkOffScreen() const
{
    if(getX() < 0)
        return true;
    return false;
}
