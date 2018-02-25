#include "GameWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <utility>
#include <algorithm>
#include <cstdlib>
using namespace std;

GameWorld* createStudentWorld(string);

void die(string msg)
{
	cout << msg << endl;
	cout << "****** FAILED the sanity check! ******" << endl;
	exit(1);
}

int main()
{
	GameWorld* gw = createStudentWorld("dummyAssets");

	cout << "About to call init for the StudentWorld" << endl;
	if (gw->init() != GWSTATUS_CONTINUE_GAME)
		die("StudentWorld::init did not return GWSTATUS_CONTINUE_GAME");

	  // The only GraphObjects at depth 3 are supposed to be stars
	  // Check that init produced 30 good stars and save their
	  // inital positions in starMap
	set<GraphObject*>& depth3 = GraphObject::getGraphObjects(3);
	if (depth3.size() != 30)
		die("StudentWorld::init did not create 30 stars at depth 3");
	using StarMap = map<GraphObject*, pair<double,double>>;
	StarMap starMap;
	for (auto go : depth3)
	{
		if (go->getSize() < .05  ||  go->getSize() > .50)
			die("A star has the wrong size");
		if (go->getX() < 0  ||  go->getX() >= VIEW_WIDTH  ||
		    go->getY() < 0  ||  go->getY() >= VIEW_HEIGHT)
			die("A star was created at bad coordinates");
		starMap[go] = make_pair(go->getX(), go->getY());
	}

	  // The only GraphObject at depth 0 must be the NachenBlaster
	set<GraphObject*>& depth0 = GraphObject::getGraphObjects(0);
	if (depth0.size() != 1)
		die("StudentWorld::init did not create a Nachenblaster at depth 0");
	GraphObject* player = *(depth0.begin());
	if (player->getX() != 0  ||  player->getY() != 128)
		die("NachenBlaster created in wrong place");
	if (player->getSize() != 1)
		die("NachenBlaster has the wrong size");

	  // Move.  Act as if an up-arrow was pressed.
	cout << "About to call move for the StudentWorld with simulated up arrow key press" << endl;
	gw->setKey(KEY_PRESS_UP);
    if (gw->move() != GWSTATUS_CONTINUE_GAME)
		die("StudentWorld::move did not return GWSTATUS_CONTINUE_GAME");

      // 30 stars must have moved left by 1.  Any that moved off screen might
	  // be gone.  New stars might have been created.
	for (auto go : depth3)
	{
		StarMap::iterator p = starMap.find(go);
		if (p == starMap.end())  //  newly-created star
		{
			if (go->getSize() < .05  ||  go->getSize() > .50)
				die("A newly-created star has the wrong size");
			if (go->getX() != VIEW_WIDTH-1  ||
		    	go->getY() < 0  ||  go->getY() >= VIEW_HEIGHT)
				die("A newly-created star was created at wrong coordinates");
		}
		else
		{
			int xold = p->second.first;
			int yold = p->second.second;
			if (go->getX() != xold-1  ||  go->getY() != yold)
				die("A star moved incorrectly");
			starMap.erase(p);
		}
	}
	  // starMap may still have stars that moved off screen
	for (auto& pr : starMap)
	{
		if (pr.second.first > 0)  // x > 0 should not have moved off screen
			die("A star with x coordinate > 0 was destroyed");
	}

	  // The player must have moved up.  An alien may have been added to depth 0.
	for (auto go : depth0)
	{
		if (go != player)
			continue;
		if (player->getX() != 0  ||  player->getY() != 128+6)
			die("NachenBlaster did not move up six pixels");
	}

	  // Cleanup.
	cout << "About to call cleanup for the StudentWorld" << endl;
    gw->cleanUp();
	for (int depth = 3; depth >= 0; depth--)
	{
		if (!GraphObject::getGraphObjects(depth).empty())
		{
			string d = to_string(depth);
			die("Memory leak:  Not all GraphObjects at depth " + d + " were destroyed");
		}
	}

	  // Destroy StudentWorld object
	cout << "About to destroy StudentWorld object" << endl;
	delete gw;

	cout << "****** SUCCESS! Passed the sanity check. ******" << endl;
}
