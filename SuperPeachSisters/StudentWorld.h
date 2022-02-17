#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <vector>
#include "Actor.h"


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class Peach;
class Block;
class Actor;
class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
    ~StudentWorld(){this->cleanUp();};
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  void loadLevel();
    bool overlap(int x, int y);
private:
    std::vector <Actor*> characters;
    Peach* m_player;
};

#endif // STUDENTWORLD_H_

