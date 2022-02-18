#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;

class Actor : public GraphObject{
public:
    Actor(int x, int y, int imageID, StudentWorld* world, bool status, int startDirection, int depth, double size);
   virtual ~Actor();
    virtual void doSomething() = 0;
    virtual void damage() = 0;
    virtual void bonk() = 0;
    StudentWorld* getWorld(){return m_world;};
    void setStatus(bool status){m_status = status;}
    bool getStatus() const{return m_status;}
private:
    bool m_status;
    StudentWorld* m_world;
};


class Block : public Actor{
public:
    Block(int x, int y, StudentWorld* world, bool hasGoodie);
    virtual ~Block();
    virtual void doSomething(){return;}
    virtual void bonk(){return;}
    //virtual bool isDamagable();
    void damage(){return;}
private:
    bool hasGoodie;
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



#endif // ACTOR_H_
