#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <iostream>
using namespace std;
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cp

Actor::Actor(int x, int y, int imageID, StudentWorld* world, bool status, int startDirection, int depth, double size, bool solid) : GraphObject(imageID,x,y,startDirection,depth,size){
    m_status = status;
    m_world = world;
    m_solid = solid;
}

Actor::~Actor(){}

Block::Block(int x, int y, StudentWorld* world, char type): Actor(x, y, IID_BLOCK, world, true,0,2,1,true){
    m_goodie = type;
    bonked = false;
}

Block::~Block(){}

void Block::bonk(){
    if (m_goodie == 'n'){
        return;
    }
    else if (bonked == false && m_goodie == 'f'){
        getWorld()->createObject(getX(), getY() + 8, 'f');
        bonked = true;
    }
}

Pipe::Pipe(int x, int y, StudentWorld* world): Actor(x, y, IID_PIPE, world, true,0,2,1,true){}

Pipe::~Pipe(){}



Peach::Peach(int x, int y, StudentWorld* world): Actor(x, y, IID_PEACH, world, true,0,0,1,false){
    
    hitPoints = 1;
    jumpDistance = 0;
}



void Peach::doSomething(){
    bool isJumping = jumpDistance > 0;
    if(hitPoints == 0){
        return;
    }
        if( getWorld()->Overlap(this->getX() + SPRITE_WIDTH - 1, this->getY() + SPRITE_HEIGHT + 1,'u') == false && getWorld()->Overlap(this->getX(), this->getY() + SPRITE_HEIGHT + 1,'u') == false && jumpDistance > 0 && isJumping == true){
            this->moveTo(getX(),getY()+ 4);
            jumpDistance--;
        }
        else{
            jumpDistance = 0;
        }
    
    int ch;
    if(getWorld()->getKey(ch)){
        int curX = getX();
        int curY = getY();
        if (ch == KEY_PRESS_LEFT){
            setDirection(180);
            if(getWorld()->Overlap(this->getX(), this->getY() + SPRITE_HEIGHT/2,'l') == false){
                this->moveTo(curX-4, curY);
            }
        }
        if (ch == KEY_PRESS_RIGHT){
            setDirection(0);
            if(getWorld()->Overlap(this->getX() + SPRITE_WIDTH, this->getY() + SPRITE_HEIGHT/2,'r') == false){
                this->moveTo(curX+4, curY);
            }
        }
        if (ch == KEY_PRESS_UP){
            if (getWorld()->Overlap(getX(), getY() - 1,'d') == true || getWorld()-> Overlap(getX() + SPRITE_WIDTH - 1, getY() - 1,'d') == true){
                getWorld()->playSound(SOUND_PLAYER_JUMP);
                jumpDistance = 8;
            }
        }
    }
    else{
        if(getWorld()->Overlap(getX(), getY() - 1,'d') == false && getWorld()-> Overlap(getX() + SPRITE_WIDTH -1, getY() - 1,'d') == false && isJumping == false){
            this->moveTo(getX(), getY() - 4);
       }
    }
    
    
}

Peach::~Peach(){}



Goomba::Goomba(int x, int y, StudentWorld *world, int startDirection): Actor(x, y, IID_GOOMBA, world, true,startDirection,0,1,false){}

void Goomba::doSomething(){
    if(getStatus() == false){
        return;
    }
    if (getDirection() == 180){
        if(getWorld()->Overlap(this->getX() - 1, this->getY() + SPRITE_HEIGHT - 1,'l') == false &&
           getWorld()->Overlap(this->getX() -1 , this->getY(),'l') == true){
            this->moveTo(getX()- 1,getY());
        }
        else{
            setDirection(0);
        }
    }
    if (getDirection() == 0){
        if(getWorld()->Overlap(this->getX() + SPRITE_WIDTH + 1, this->getY(),'r') == true &&
           getWorld()->Overlap(this->getX() + SPRITE_WIDTH + 1, this->getY() + SPRITE_HEIGHT - 1,'r') == false){
            this->moveTo(getX()+ 1,getY());
        }
        else{
            setDirection(180);
        }
        
    }
}

Goomba::~Goomba(){}

Flower::Flower(int x, int y, StudentWorld* world) :Actor(x, y, IID_FLOWER, world, true,0,1,1,false) {}

void Flower::doSomething(){
    return;
}

Flower::~Flower(){}
