#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


Actor::Actor(int imageID, double startX, double startY, int dir, double size, int depth, int state):
    GraphObject(imageID, startX, startY, dir, size, depth), actorState(state)
{
    
}

int Actor::getState() const
{
    return actorState;
}

void Actor::setState(int state)
{
    actorState = state;
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
        setState(DEAD_STATE);
}

NachenBlaster::NachenBlaster():
Actor(IID_NACHENBLASTER, 0, 128), hp(50), cabbageEP(30)
{
}

void NachenBlaster::doSomething()
{
    if(getState() == DEAD_STATE)
        return;
    
    cabbageEP++;
    int key;
    if(getWorld()->getKey(key))
    {
        switch (key)
        {
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

StudentWorld * NachenBlaster::getWorld()
{
    return world;
}
