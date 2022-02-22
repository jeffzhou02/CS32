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
    srand(static_cast<unsigned int>(time(nullptr)));
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
                        int random = rand() % 2;
                        if (random == 1){random = 180;}
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
                        
                        break;
                    }
                    case Level::mushroom_goodie_block:{
                        
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
                        break;
                    }
                }
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::createObject(int x, int y, char type){
    if (type == 'f'){
        characters.push_back(new Flower (x,y,this));
        cout << "object created" << endl;
    }
}


int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    
    vector<Actor*>::iterator it;
    it = characters.begin();
    while(it != characters.end()){
        (*it)->doSomething();
        it++;
    }
    m_player->doSomething();
    
    return GWSTATUS_CONTINUE_GAME;

}


void StudentWorld::cleanUp()
{
    vector<Actor*>::iterator it;
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
    vector<Actor*>::iterator it;
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


bool StudentWorld::atPeach(int x, int y){
    if (x >= m_player->getX() && x <= m_player->getX() + SPRITE_WIDTH - 1 &&
        y >= m_player->getY() && y <= m_player->getY()+SPRITE_HEIGHT - 1){
        return true;
    }
    return false;
}

void StudentWorld::updatePeach(char powerUp){
    m_player->setHitpoints(2);
    switch (powerUp){
        case 'f':{
            m_player->setFlower(true);
        }
    }
}














