#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

void CoinSquare::doSomething(){
    if(!state())
        return;
}

void Actor::doSomething(){
    return;
}

void PlayerAvatar::doSomething(){
    if(state() == 1){
        int action = m_world->getAction(playerNum);
        switch(action){
            case ACTION_ROLL:
                die_roll = randInt(1, 10);
                ticks_to_move = die_roll * 8;
                changeState(0);
                break;
            default:
                return;
                break;
        }
    }
}
