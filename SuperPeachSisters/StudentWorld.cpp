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
: GameWorld(assetPath)
{
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
                cerr << "Successfully loaded level" << endl;
                Level::GridEntry ge;
                ge = lev.getContentsOf(x, y); // x=5, y=10
                switch (ge)
                {
                    case Level::empty:{
                        cout << "Location 5,10 is empty" << endl;
                        break;
                    }
                    case Level::koopa:{
                        cout << "Location 5,10 starts with a koopa" << endl;
                        break;
                    }
                    case Level::goomba:{
                        cout << "Location 5,10 starts with a goomba" << endl;
                        break;
                    }
                    case Level::peach:{
                        m_player = new Peach(x * SPRITE_WIDTH,y * SPRITE_HEIGHT,this);

                        break;
                    }
                    case Level::flag:{
                        cout << "Location 5,10 is where a flag is" << endl;
                        break;
                    }
                    case Level::block:{
                        characters.push_back(new Block(x * SPRITE_WIDTH,y * SPRITE_HEIGHT,this,false));
                        break;
                    }
                    case Level::piranha:{
                        
                        break;
                    }
                    case Level::mushroom_goodie_block:{
                        
                        break;
                    }
                    case Level::flower_goodie_block:{
                        
                        break;
                    }
                    case Level::pipe:{
                        
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
}

bool StudentWorld::overlap(int x,int y){
    vector<Actor*>::iterator it;
    it = characters.begin();
    while(it != characters.end()){
        if (x == (*it)->getX() + SPRITE_WIDTH -1 && y == (*it)->getY() + SPRITE_HEIGHT - 1){
            return true;
        }
        if (x == (*it)->getX() - 1 && y == (*it)->getY() + SPRITE_HEIGHT -1) {
            return true;
        }
        it++;
    }
    return false;
}



