#include "StudentWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include "Level.h"
#include <string>
#include <vector>
#include <iterator>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), characters()
{
    m_player = nullptr;
}

int StudentWorld::init()
{

    Level lev(assetPath());
    string level_file = "level01.txt";
    Level::LoadResult result = lev.loadLevel(level_file);
    if (result == Level::load_fail_file_not_found)
        cerr << "Could not find level01.txt data file" << endl;
    else if (result == Level::load_fail_bad_format)
        cerr << "level01.txt is improperly formatted" << endl;
    else if (result == Level::load_success)
    {
        for (int x = 0; x < 32; x++){
            for (int y = 0; y < 32; y++){
                Level::GridEntry ge;
                ge = lev.getContentsOf(x, y); // x=5, y=10
                switch (ge)
                {
                    case Level::empty:{
                        break;
                    }
                    case Level::koopa:{
                        break;
                    }
                    case Level::goomba:{
       
                        int random = randInt(0, 1) * 180;
                        characters.push_back(new Goomba(x * SPRITE_WIDTH,y * SPRITE_HEIGHT,this,random));

                        break;
                    }
                    case Level::peach:{
                        m_player = new Peach(x * SPRITE_WIDTH,y * SPRITE_HEIGHT,this);

                        break;
                    }
                    case Level::flag:{
                        break;
                    }
                    case Level::block:{
                        characters.push_back(new Block(x * SPRITE_WIDTH,y * SPRITE_HEIGHT,this,'n'));
                        break;
                    }
                    case Level::piranha:{
                        int random = randInt(0, 1) * 180;
                        characters.push_back(new Piranha(x * SPRITE_WIDTH,y * SPRITE_HEIGHT,this,random));
                        break;
                    }
                    case Level::mushroom_goodie_block:{
                        characters.push_back(new Block(x * SPRITE_WIDTH,y * SPRITE_HEIGHT,this,'s'));
                        break;
                    }
                    case Level::flower_goodie_block:{
                        characters.push_back(new Block(x * SPRITE_WIDTH,y * SPRITE_HEIGHT,this,'f'));
                        break;
                    }
                    case Level::pipe:{
                        characters.push_back(new Pipe(x * SPRITE_WIDTH,y * SPRITE_HEIGHT,this));
                        break;
                    }
                    case Level::mario:{
                        
                        break;
                    }
                    case Level::star_goodie_block:
                    {
                        characters.push_back(new Block(x * SPRITE_WIDTH,y * SPRITE_HEIGHT,this,'i'));
                        break;
                    }
                }
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::createObject(int x, int y, char type, int direction){
    if (type == 'f'){
        characters.push_back(new Flower (x,y,this));
        cout << "object created" << endl;
    }
    if (type == 'b'){
        characters.push_back(new pFireball (x,y,direction,this));
        cout << "object created" << endl;
    }
    if (type == 's'){
        characters.push_back(new Shroom (x,y,this));
        cout << "object created" << endl;
    }
    if (type == 'i'){
        characters.push_back(new Star (x,y,this));
        cout << "object created" << endl;
    }
    if (type == 'p'){
        characters.push_back(new piranhaFireball (x,y,direction,this));
        cout << "object created" << endl;
    }
}


int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    

    
    list<Actor*>::iterator it;
    it = characters.begin();
    m_player->doSomething();
    
    if (m_player->getHP() == 0){
        playSound(GWSTATUS_PLAYER_DIED);
        return GWSTATUS_PLAYER_DIED;
    }
    
    while(it != characters.end()){
        if ((*it)->getStatus() == true){
        (*it)->doSomething();
        it++;
        }
        else{
            Actor* temp;
            temp = *it;
            it = characters.erase(it);
            delete temp;
            return GWSTATUS_CONTINUE_GAME;

        }
    }
    
    return GWSTATUS_CONTINUE_GAME;

}


void StudentWorld::cleanUp()
{
    list<Actor*>::iterator it;
    it = characters.begin();
    while(it != characters.end()){
        Actor* temp;
        temp = (*it);
        it = characters.erase(it);
        delete temp;
    }
    delete m_player;
}


// atempt to bonk parameter for overlap - if you want the thing to interact with the other object pass in true

// isSolid() variable of actor


bool StudentWorld::Overlap(int x,int y, char direction, bool isBonk){
    list<Actor*>::iterator it;
    it = characters.begin();
    switch(direction){
        case 'l':{
            while(it != characters.end()){
                if (x <= (*it)->getX() + SPRITE_WIDTH && x >= (*it)->getX() &&  y <= (*it)->getY() + SPRITE_HEIGHT  &&  y >= (*it)->getY()){
                    if(isBonk){(*it)->bonk();}
                    return (*it)->isSolid();
                }
                it++;
            }
            break;
        }
        case 'r':{
            while(it != characters.end()){
                if (x >= (*it)->getX() && x <= (*it)->getX() +SPRITE_WIDTH  && y <= (*it)->getY() + SPRITE_HEIGHT  && y >= (*it)->getY()) {
                    if(isBonk){(*it)->bonk();}
                    return (*it)->isSolid();
                }
                it++;
            }
            break;
        }
        case 'd': {
            while(it != characters.end()){
                if ((x <=(*it)->getX() + SPRITE_WIDTH - 1 && x >= (*it)->getX() + 1) && y <= (*it)->getY() + SPRITE_HEIGHT && y >= (*it)->getY()){
                    if(isBonk){(*it)->bonk();}
                    return (*it)->isSolid();
                }
                it++;
            }
            break;
        }
        case 'u': {
            while(it != characters.end()){
                if ((x <=(*it)->getX() + SPRITE_WIDTH - 1 && x >= (*it)->getX() + 1) &&  y <= (*it)->getY() + SPRITE_HEIGHT - 1  && y >= (*it)->getY()){
                    if(isBonk){(*it)->bonk();}
                    return (*it)->isSolid();
                }
                it++;
            }
            break;
        }
    }
    return false;
}







bool StudentWorld::atPeach(int x, int y, bool isBonk){
    if (x >= m_player->getX() && x <= m_player->getX() + SPRITE_WIDTH - 1 &&
        y >= m_player->getY() && y <= m_player->getY()+SPRITE_HEIGHT - 1){
        if(isBonk){
            m_player->bonk();
        }
        return true;
    }
    return false;
}

void StudentWorld::updatePeach(char powerUp){
    m_player->setHitpoints(2);
    switch (powerUp){
        case 'f':{
            m_player->setFlower(true);
            m_player->setHitpoints(2);
            break;
        }
        case 's':{
            m_player->setShroom(true);
            m_player->setHitpoints(2);
            break;
        }
        case 'i':{
            m_player->setInvicible(1000);
            break;
        }
    }
}



bool StudentWorld::getPeachStar(){
    return m_player->getInvicibleStatus() > 0;
}

int StudentWorld::getPeachX(){
    return m_player->getX();
}

int StudentWorld::getPeachY(){
    return m_player->getY();
}
















