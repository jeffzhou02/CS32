#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <list>
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
    void createObject(int x, int y,char type, int direction);
    bool Overlap(int x, int y, char direction, bool isBonk);
    bool atPeach(int x, int y, bool isBonk);
    void updatePeach(char powerUp);
    bool getPeachStar();
    int getPeachX();
    int getPeachY();
    void finishLevel();
    void finishGame(){finishedGame = true;}
    bool ObjectOverlap(int x, int y, char direction, Actor* itself);


private:
    std::list <Actor*> characters;
    Peach* m_player;
    bool finishedGame;
};

#endif // STUDENTWORLD_H_

