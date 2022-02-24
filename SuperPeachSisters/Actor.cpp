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

void Block::bonk(){ // fix block so bonk sound plays on goodie blocks too
    
    if (getWorld()->atPeach(getX() + SPRITE_WIDTH/2, getY() - 1, false) == true || getWorld()->atPeach(getX() + SPRITE_WIDTH, getY() - 1, false) == true ||
        getWorld()->atPeach(getX(), getY() - 1, false) == true){
        
        if (m_goodie == 'n'){
            getWorld()->playSound(SOUND_PLAYER_BONK);
            return;
        }
        
        if (bonked == false && m_goodie == 'f'){
            getWorld()->playSound(SOUND_POWERUP_APPEARS);
            getWorld()->createObject(getX(), getY() + 8, 'f',0);
            bonked = true;
        }
        if (bonked == false && m_goodie == 's'){
            getWorld()->playSound(SOUND_POWERUP_APPEARS);
            getWorld()->createObject(getX(), getY() + 8, 's',0);
            bonked = true;
        }
        if (bonked == false && m_goodie == 'i'){
            getWorld()->playSound(SOUND_POWERUP_APPEARS);
            getWorld()->createObject(getX(), getY() + 8, 'i',0);
            bonked = true;
        }
        
    }
}



Pipe::Pipe(int x, int y, StudentWorld* world): Actor(x, y, IID_PIPE, world, true,0,2,1,true){}

Pipe::~Pipe(){}









Peach::Peach(int x, int y, StudentWorld* world): Actor(x, y, IID_PEACH, world, true,0,0,1,false){
    
    hitPoints = 1;
    jumpDistance = 0;
    rechargeTime = 0;
    flower = false;
    star = false;
    shroom = false;
    tempIn = 0;
}

void Peach::bonk(){
    if (star > 0 || tempIn > 0){
        return;
    }
    if (hitPoints == 2){
        getWorld()->playSound(SOUND_PLAYER_HURT);
        tempIn = 10;
        shroom = false;
        flower = false;
        hitPoints--;
        return;
    }
    else if (hitPoints == 1){
        hitPoints = 0;
        setStatus(false);
        return;
    }
}



void Peach::doSomething(){
    if(hitPoints == 0){return;}
    
    if (star > 0){star--;}
    if (tempIn > 0){tempIn--;}
    
    
    bool isJumping = jumpDistance > 0;
    
    if (rechargeTime > 0){rechargeTime--;}
    
    
    if( getWorld()->Overlap(this->getX() + SPRITE_WIDTH - 1, this->getY() + SPRITE_HEIGHT + 1,'u',true) == false && getWorld()->Overlap(this->getX(), this->getY() + SPRITE_HEIGHT + 1,'u',true) == false && jumpDistance > 0 && isJumping == true){
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
            if(getWorld()->Overlap(this->getX(), this->getY() + SPRITE_HEIGHT/2,'l',true) == false){
                this->moveTo(curX-4, curY);
            }
        }
        if (ch == KEY_PRESS_RIGHT){
            setDirection(0);
            if(getWorld()->Overlap(this->getX() + SPRITE_WIDTH, this->getY() + SPRITE_HEIGHT/2,'r',true) == false){
                this->moveTo(curX+4, curY);
            }
        }
        if (ch == KEY_PRESS_UP){
            if (getWorld()->Overlap(getX(), getY() - 1,'d',false) == true || getWorld()-> Overlap(getX() + SPRITE_WIDTH - 1, getY() - 1,'d',false) == true){
                getWorld()->playSound(SOUND_PLAYER_JUMP);
                if(shroom == true){
                    jumpDistance = 12;
                }
                else{jumpDistance = 8;}
            }
        }
        if (ch == KEY_PRESS_SPACE){
            if (flower == true && rechargeTime == 0){
                if (getDirection() == 0){
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                    getWorld()->createObject(getX() + SPRITE_WIDTH, getY(),'b', 0);
                    rechargeTime = 8;
                }
                if (getDirection() == 180){
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                    getWorld()->createObject(getX(), getY(),'b', 180);
                    rechargeTime = 8;
                }
            }
            
        }
    }
    else{
        if(getWorld()->Overlap(getX(), getY() - 1,'d',false) == false && getWorld()-> Overlap(getX() + SPRITE_WIDTH -1, getY() - 1,'d',false) == false && isJumping == false){
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
    if (getWorld()->atPeach(getX(), getY() + SPRITE_HEIGHT/2,true) == true ||
        getWorld()->atPeach(getX() + SPRITE_WIDTH - 1, getY() + SPRITE_HEIGHT/2,true) == true){
        if (getWorld()->getPeachStar()){
            this->bonk();
        }
    }
    if (getDirection() == 180){
        if(getWorld()->Overlap(this->getX() - 1, this->getY() + SPRITE_HEIGHT/2,'l',false) == false &&
           getWorld()->Overlap(this->getX() -1 , this->getY(),'l',false) == true){
            this->moveTo(getX()- 1,getY());
        }
        else{
            setDirection(0);
        }
    }
    if (getDirection() == 0){
        if(getWorld()->Overlap(this->getX() + SPRITE_WIDTH + 1, this->getY(),'r',false) == true &&
           getWorld()->Overlap(this->getX() + SPRITE_WIDTH + 1, this->getY() + SPRITE_HEIGHT/2,'r',false) == false){
            this->moveTo(getX() + 1,getY());
        }
        else{
            setDirection(180);
        }
    }
}

void Goomba::bonk(){
    
    if (getWorld()->atPeach(getX() + SPRITE_WIDTH/2, getY() + SPRITE_HEIGHT/2, false) == true ||
        getWorld()->atPeach(getX() + SPRITE_WIDTH, getY() + SPRITE_HEIGHT/2, false) == true ||
        getWorld()->atPeach(getX(), getY() + SPRITE_HEIGHT/2, false) == true){
        if (getWorld()->getPeachStar() >0){
        getWorld()->playSound(SOUND_PLAYER_KICK);
        setStatus(false);
        }
        return;
    }
    setStatus(false);
}

Goomba::~Goomba(){}





Piranha::Piranha(int x, int y, StudentWorld *world, int startDirection): Actor(x, y, IID_PIRANHA, world, true,startDirection,0,1,false){
    firingDelay = 0;
}

void Piranha::doSomething(){
    if(getStatus() == false){
        return;
    }
    this->increaseAnimationNumber();
    if (getWorld()->atPeach(getX(), getY() + SPRITE_HEIGHT/2,true) == true ||
        getWorld()->atPeach(getX() + SPRITE_WIDTH - 1, getY() + SPRITE_HEIGHT/2,true) == true){
        if (getWorld()->getPeachStar()){
            this->bonk();
        }
    }
    if (getWorld()->getPeachY() >= getY() && getWorld()->getPeachY() < getY()*SPRITE_HEIGHT*1.5){
        if (getWorld()->getPeachX() < getX()){
            setDirection(180);
        }
        else{
            setDirection(0);
        }
        if (firingDelay > 0){
            firingDelay--;
            return;
        }
        else{
            //fire
            firingDelay = 40;
            if (getDirection() == 0 && getWorld()->getPeachX() < 8 * SPRITE_WIDTH + getX()){
                getWorld()->playSound(SOUND_PIRANHA_FIRE);
               getWorld()->createObject(getX()+SPRITE_WIDTH, getY(), 'p', getDirection());

            }
            if (getDirection() == 180 && getWorld()->getPeachX() > getX() - 8 * SPRITE_WIDTH){
                getWorld()->playSound(SOUND_PIRANHA_FIRE);
               getWorld()->createObject(getX() - 1, getY(), 'p', getDirection());
            }
            
        }
    }
    else{
        return;
    }

}


void Piranha::bonk(){
    if (getWorld()->atPeach(getX() + SPRITE_WIDTH/2, getY() + SPRITE_HEIGHT/2, false) == true ||
        getWorld()->atPeach(getX() + SPRITE_WIDTH, getY() + SPRITE_HEIGHT/2, false) == true ||
        getWorld()->atPeach(getX(), getY() + SPRITE_HEIGHT/2, false) == true){
        if (getWorld()->getPeachStar() >0){
        getWorld()->playSound(SOUND_PLAYER_KICK);
        setStatus(false);
        }
        return;
    }
    setStatus(false);;
}

Piranha::~Piranha(){}







Flower::Flower(int x, int y, StudentWorld* world) :Actor(x, y, IID_FLOWER, world, true,0,1,1,false) {}

void Flower::doSomething(){
    if (getStatus() == false){
        return;
    }
    if (getWorld()->atPeach(getX(), getY() + SPRITE_HEIGHT/2,false) == true ||
        getWorld()->atPeach(getX() + SPRITE_WIDTH - 1, getY() + SPRITE_HEIGHT/2,false) == true){
        getWorld()->updatePeach('f');
        setStatus(false);
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    if(getWorld()->Overlap(getX(), getY() - 1,'d',false) == false && getWorld()-> Overlap(getX() + SPRITE_WIDTH -1, getY() - 1,'d',false) == false ){
        this->moveTo(getX(), getY() - 2);
    }
    if (getDirection() == 180){
        if(getWorld()->Overlap(this->getX(), this->getY() + SPRITE_HEIGHT/2,'l',false) == false && getWorld()->Overlap(this->getX(), this->getY() + 1,'l',false) == false){
            this->moveTo(getX()-2, getY());
        }
        else{
            setDirection(0);
        }
    }
    if (getDirection() == 0){
        if(getWorld()->Overlap(this->getX() + SPRITE_WIDTH, this->getY() + SPRITE_HEIGHT/2,'r',false) == false && getWorld()->Overlap(this->getX() + SPRITE_WIDTH, this->getY() + 1,'r',false) == false){
            this->moveTo(getX()+2, getY());
        }
        else{
            setDirection(180);
        }
    }
    
}

Flower::~Flower(){}






Shroom::Shroom(int x, int y, StudentWorld* world) :Actor(x, y, IID_MUSHROOM, world, true,0,1,1,false) {}

void Shroom::doSomething(){
    if (getStatus() == false){
        return;
    }
    if (getWorld()->atPeach(getX(), getY() + SPRITE_HEIGHT/2,false) == true ||
        getWorld()->atPeach(getX() + SPRITE_WIDTH - 1, getY() + SPRITE_HEIGHT/2,false) == true){
        getWorld()->updatePeach('s');
        setStatus(false);
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    if(getWorld()->Overlap(getX(), getY() - 1,'d',false) == false && getWorld()-> Overlap(getX() + SPRITE_WIDTH -1, getY() - 1,'d',false) == false ){
        this->moveTo(getX(), getY() - 2);
    }
    if (getDirection() == 180){
        if(getWorld()->Overlap(this->getX(), this->getY() + SPRITE_HEIGHT/2,'l',false) == false && getWorld()->Overlap(this->getX(), this->getY() + 1,'l',false) == false){
            this->moveTo(getX()-2, getY());
        }
        else{
            setDirection(0);
        }
    }
    if (getDirection() == 0){
        if(getWorld()->Overlap(this->getX() + SPRITE_WIDTH, this->getY() + SPRITE_HEIGHT/2,'r',false) == false && getWorld()->Overlap(this->getX() + SPRITE_WIDTH, this->getY() + 1,'r',false) == false){
            this->moveTo(getX()+2, getY());
        }
        else{
            setDirection(180);
        }
    }
    
}

Shroom::~Shroom(){}







Star::Star(int x, int y, StudentWorld* world) :Actor(x, y, IID_STAR, world, true,0,1,1,false) {}

void Star::doSomething(){
    if (getStatus() == false){
        return;
    }
    if (getWorld()->atPeach(getX(), getY() + SPRITE_HEIGHT/2,false) == true ||
        getWorld()->atPeach(getX() + SPRITE_WIDTH - 1, getY() + SPRITE_HEIGHT/2,false) == true){
        getWorld()->updatePeach('i');
        setStatus(false);
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    if(getWorld()->Overlap(getX(), getY() - 1,'d',false) == false && getWorld()-> Overlap(getX() + SPRITE_WIDTH -1, getY() - 1,'d',false) == false ){
        this->moveTo(getX(), getY() - 2);
    }
    if (getDirection() == 180){
        if(getWorld()->Overlap(this->getX(), this->getY() + SPRITE_HEIGHT/2,'l',false) == false && getWorld()->Overlap(this->getX(), this->getY() + 1,'l',false) == false){
            this->moveTo(getX()-2, getY());
        }
        else{
            setDirection(0);
        }
    }
    if (getDirection() == 0){
        if(getWorld()->Overlap(this->getX() + SPRITE_WIDTH, this->getY() + SPRITE_HEIGHT/2,'r',false) == false && getWorld()->Overlap(this->getX() + SPRITE_WIDTH, this->getY() + 1,'r',false) == false){
            this->moveTo(getX()+2, getY());
        }
        else{
            setDirection(180);
        }
    }
}

Star::~Star(){}











// fix fireball so it disappears when something disappears

pFireball::pFireball(int x, int y,int direction, StudentWorld* world):Actor(x, y, IID_PEACH_FIRE, world, true,direction,1,1,false){}

void pFireball::doSomething(){

    if(getWorld()->Overlap(getX(), getY() - 1,'d',false) == false && getWorld()-> Overlap(getX() + SPRITE_WIDTH -1, getY() - 1,'d',false) == false ){
        this->moveTo(getX(), getY() - 2);
    }
    if (getDirection() == 180){
        if(getWorld()->Overlap(this->getX(), this->getY() + SPRITE_HEIGHT/2,'l',true) == false && getWorld()->Overlap(this->getX(), this->getY() + 1,'l',true) == false){
            this->moveTo(getX()-2, getY());
        }
        else{
            setStatus(false);
        }
    }
    if (getDirection() == 0){
        if(getWorld()->Overlap(this->getX() + SPRITE_WIDTH, this->getY() + SPRITE_HEIGHT/2,'r',true) == false && getWorld()->Overlap(this->getX() + SPRITE_WIDTH, this->getY() + 1,'r',true) == false){
            this->moveTo(getX()+2, getY());
        }
        else{
            setStatus(false);
        }
    }
}

pFireball::~pFireball(){}







piranhaFireball::piranhaFireball(int x, int y,int direction, StudentWorld* world):Actor(x, y, IID_PIRANHA_FIRE, world, true,direction,1,1,false){}

void piranhaFireball::doSomething(){
    if (getWorld()->atPeach(getX(), getY() + SPRITE_HEIGHT/2,true) == true ||
        getWorld()->atPeach(getX() + SPRITE_WIDTH - 1, getY() + SPRITE_HEIGHT/2,true) == true){
        setStatus(false);

    }
    if(getWorld()->Overlap(getX(), getY() - 1,'d',false) == false && getWorld()-> Overlap(getX() + SPRITE_WIDTH -1, getY() - 1,'d',false) == false ){
        this->moveTo(getX(), getY() - 2);
    }
    if (getDirection() == 180){
        if(getWorld()->Overlap(this->getX(), this->getY() + SPRITE_HEIGHT/2,'l',true) == false && getWorld()->Overlap(this->getX(), this->getY() + 1,'l',true) == false){
            this->moveTo(getX()-2, getY());
        }
        else{
            setStatus(false);
        }
    }
    if (getDirection() == 0){
        if(getWorld()->Overlap(this->getX() + SPRITE_WIDTH, this->getY() + SPRITE_HEIGHT/2,'r',true) == false && getWorld()->Overlap(this->getX() + SPRITE_WIDTH, this->getY() + 1,'r',true) == false){
            this->moveTo(getX()+2, getY());
        }
        else{
            setStatus(false);
        }
    }
}

piranhaFireball::~piranhaFireball(){}
