#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cp

Actor::Actor(int x, int y, int imageID, StudentWorld* world, bool status, int startDirection, int depth, double size) : GraphObject(imageID,x,y,startDirection,depth,size){
    m_status = status;
    m_world = world;
}

Actor::~Actor(){
    
}

Block::Block(int x, int y, StudentWorld* world, bool goodie): Actor(x, y, IID_BLOCK, world, true,0,2,1){
    hasGoodie = goodie;
}

Block::~Block(){
    
}

Peach::Peach(int x, int y, StudentWorld* world): Actor(x, y, IID_PEACH, world, true,0,0,1){
    
    hitPoints = 1;
}

void Peach::doSomething(){
    if(hitPoints == 0){
        return;
    }
    int ch;
    if(getWorld()->getKey(ch)){
        int curX = getX();
        int curY = getY();
        if (ch == KEY_PRESS_LEFT){
            setDirection(180);
            if(getWorld()->overlap(this->getX() - 1, this->getY() + SPRITE_HEIGHT - 1) == false ){
                this->moveTo(curX-4, curY);
            }
        }
        if(getWorld()->overlap(this->getX() + SPRITE_WIDTH - 1, this->getY() + SPRITE_HEIGHT - 1) == false ){
            if (ch == KEY_PRESS_RIGHT){
                setDirection(0);
                this->moveTo(curX+4, curY);
            }
        }
    }
    
}

Peach::~Peach(){}


