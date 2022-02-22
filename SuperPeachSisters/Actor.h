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
    virtual void bonk(){return;}
    void damage(){return;}
private:
    int hitPoints;
    int jumpDistance;
};

class Goomba: public Actor{
public:
    Goomba(int x, int y, StudentWorld* world, int startDirection);
    virtual ~Goomba();
    virtual void doSomething();
    virtual void bonk(){return;}
    void damage(){return;}
private:
};


class Flag: public Actor{
public:
    Flag(int x, int y, StudentWorld* world, int startDirection);
    virtual ~Flag();
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
private:
    char type;
    
};



#endif // ACTOR_H_
