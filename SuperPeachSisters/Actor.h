#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;

class Actor : public GraphObject{
public:
    Actor(int x, int y, int imageID, StudentWorld* world, bool status, int startDirection, int depth, double size, bool solid);
   virtual ~Actor();
    virtual void doSomething() = 0;
    virtual void damage() = 0;
    virtual void bonk() = 0;
    StudentWorld* getWorld(){return m_world;};
    void setStatus(bool status){m_status = status;}
    bool getStatus() const{return m_status;}
    bool isSolid() const{return m_solid;}
private:
    bool m_status;
    bool m_solid;
    StudentWorld* m_world;
};


class Block : public Actor{
public:
    Block(int x, int y, StudentWorld* world, char type );
    virtual ~Block();
    virtual void doSomething(){return;}
    virtual void bonk();
    //virtual bool isDamagable();
    void damage(){return;}
private:
    char m_goodie;
    bool bonked;
};

class Pipe: public Actor{
public:
    Pipe(int x, int y, StudentWorld* world);
    virtual ~Pipe();
    virtual void doSomething(){return;}
    virtual void bonk(){return;}
    void damage(){return;}
};

class Peach: public Actor{
public:
    Peach(int x, int y, StudentWorld* world);
    virtual ~Peach();
    virtual void doSomething();
    void setFlower(bool power){flower = power;}
    bool getFlowerStatus(){return flower;}
    void setShroom(bool power){shroom = power;}
    bool getShroomStatus(){return shroom;}
    void setInvicible(int power){star = power;}
    int getInvicibleStatus(){return star;}
    void setHitpoints(int hp){hitPoints = hp;}
    int getHP(){return hitPoints;}
    bool isComplete(){return finishedLevel;}
    void finishLevel(){finishedLevel = true;}
    virtual void bonk();
    void damage(){return;}
private:
    int hitPoints;
    int jumpDistance;
    bool flower;
    int star;
    bool shroom;
    int rechargeTime;
    int tempIn;
    bool finishedLevel;
};

class Goomba: public Actor{
public:
    Goomba(int x, int y, StudentWorld* world, int startDirection);
    virtual ~Goomba();
    virtual void doSomething();
    virtual void bonk();
    void damage(){return;}
private:
};

class Piranha: public Actor{
public:
    Piranha(int x, int y, StudentWorld* world, int startDirection);
    virtual ~Piranha();
    virtual void doSomething();
    virtual void bonk();
    void damage(){return;}
private:
    int firingDelay;
};

class Koopa: public Actor{
public:
    Koopa(int x, int y, StudentWorld* world, int startDirection);
    virtual ~Koopa();
    virtual void doSomething();
    virtual void bonk();
    void damage(){return;}
private:
    bool bonked;

    
};



class Flag: public Actor{
public:
    Flag(int x, int y, StudentWorld* world);
    virtual ~Flag();
    virtual void doSomething();
    virtual void bonk(){return;}
    void damage(){return;}
private:
};

class Mario: public Actor{
public:
    Mario(int x, int y, StudentWorld* world);
    virtual ~Mario();
    virtual void doSomething();
    virtual void bonk(){return;}
    void damage(){return;}
private:
};


class Flower: public Actor{
public:
    Flower(int x, int y, StudentWorld* world);
    virtual ~Flower();
    virtual void doSomething();
    virtual void bonk(){return;}
    void damage(){return;}

};


class Shroom: public Actor{
public:
    Shroom(int x, int y, StudentWorld* world);
    virtual ~Shroom();
    virtual void doSomething();
    virtual void bonk(){return;}
    void damage(){return;}

};


class Star: public Actor{
public:
    Star(int x, int y, StudentWorld* world);
    virtual ~Star();
    virtual void doSomething();
    virtual void bonk(){return;}
    void damage(){return;}

};


class pFireball: public Actor{
public:
    pFireball(int x, int y, int direction,StudentWorld* world);
    virtual ~pFireball();
    virtual void doSomething();
    virtual void bonk(){return;}
    void damage(){return;}
};


class piranhaFireball: public Actor{
public:
    piranhaFireball(int x, int y, int direction,StudentWorld* world);
    virtual ~piranhaFireball();
    virtual void doSomething();
    virtual void bonk(){return;}
    void damage(){return;}
};

class shell: public Actor{
public:
    shell(int x, int y, int direction,StudentWorld* world);
    virtual ~shell();
    virtual void doSomething();
    virtual void bonk(){return;}
    void damage(){return;}
};




#endif // ACTOR_H_
