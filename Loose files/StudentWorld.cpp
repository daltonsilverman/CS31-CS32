#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include "Board.h"
#include <string>
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
	startCountdownTimer(5);  // this placeholder causes timeout after 5 seconds
    m_board = new Board;
    if(m_board->loadBoard(assetPath())){
        for(int r = 0; r < BOARD_HEIGHT; r++){
            for(int c = 0; c < BOARD_WIDTH; c++){
                Board::GridEntry entry = m_board->getContentsOf(c, r);
                switch(entry){
                    case Board::player:
                        m_array[n+1] = new PlayerAvatar(SPRITE_HEIGHT * c, SPRITE_WIDTH * r, this);
                        CoinSquare(SPRITE_HEIGHT * c, SPRITE_WIDTH * r);
                        break;
                    case Board::blue_coin_square:
                        CoinSquare(SPRITE_HEIGHT * c, SPRITE_HEIGHT * r);
                        break;
                    case Board::red_coin_square:
                        CoinSquare(SPRITE_HEIGHT * c, SPRITE_HEIGHT * r);
                        break;
                    default:
                        break;
                }
            }
        }
        return GWSTATUS_CONTINUE_GAME;
    }
    return GWSTATUS_BOARD_ERROR;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit ESC.
    // Notice that the return value GWSTATUS_NOT_IMPLEMENTED will cause our framework to end the game.
    
    for(int i = 0; i < n; i++){
        if(m_array[i]->isAlive()){
            m_array[i]->doSomething();
        }
        else{
            delete m_array[i];
            for(int j = i; j < n-1; j++){
                m_array[j] = m_array[j+1];
            }
            n--;
        }
    }

    setGameStatText("Game will end in a few seconds");
    
    if (timeRemaining() <= 0){
        playSound(SOUND_GAME_FINISHED);
        return GWSTATUS_PEACH_WON;
    }
    
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for(int i = 0; i < n; i++){
        delete m_array[i];
    }
}

StudentWorld::~StudentWorld(){
    cleanUp();
}
