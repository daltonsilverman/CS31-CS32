#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

void CoinSquare::doSomething(){
    //if(!state())
        return;
}

void Actor::doSomething(){
    return;
}

void PlayerAvatar::doSomething(){
    //std::cout << "peach is in state" << state() << std::endl;
    if(state() == 1){
        int action = m_world->getAction(playerNum);
        //std::cout << action << std::endl;
        switch(action){
            case ACTION_ROLL:
                die_roll = randInt(1, 10);
                std::cout << die_roll << std::endl;
                ticks_to_move = die_roll * 8;
                changeState(0);
                break;
            default:
                return;
                break;
                }
        }
    if(state() == 0){
        int direction = getDirection();
        int walkingDirection = direction;
        switch(walkingDirection){
            case right:
                if(m_world->getBoard()->getContentsOf(getX()/16 + 1, getY()/16) == Board::empty){
                    if(m_world->getBoard()->getContentsOf(getX()/16, getY()/16+1) == Board::empty){
                        walkingDirection = down;
                        //setDirection(down);
                    }
                    else{
                        walkingDirection = up;
                        //setDirection(up);
                    }
                }
                break;
            case left:
                if(m_world->getBoard()->getContentsOf(getX()/16 - 1, getY()/16) == Board::empty){
                    if(m_world->getBoard()->getContentsOf(getX()/16, getY()/16+1) == Board::empty){
                        walkingDirection = down;
                        //setDirection(down);
                    }
                    else{
                        walkingDirection = up;
                        //setDirection(up);
                    }
                }
                break;
            case up:
                if(m_world->getBoard()->getContentsOf(getX()/16, getY()/16 + 1) == Board::empty){
                    if(m_world->getBoard()->getContentsOf(getX()/16 + 1, getY()/16) == Board::empty){
                        walkingDirection = left;
                        //setDirection(left);
                    }
                    else{
                        walkingDirection = right;
                        //setDirection(right);
                    }
                }
                break;
            case down:
                if(m_world->getBoard()->getContentsOf(getX()/16, getY()/16) == Board::empty){
                    
                    if(m_world->getBoard()->getContentsOf(getX()/16 + 1, getY()+5/16) == Board::empty){
                        walkingDirection = left;
                        setDirection(left);
                    }
                    else{
                        walkingDirection = right;
                        setDirection(right);
                    }
                        
                }
                break;
        }
        if(ticks_to_move > 0){
            int posX = 0;
            int posY = 0;
            getPositionInThisDirection(walkingDirection, 2, posX, posY);
            std::cout << walkingDirection << " " << posX << " " << posY << std::endl;
            moveTo(posX, posY);
            ticks_to_move--;
        }
        else
        changeState(1);
        
    }
     
    return;
}
