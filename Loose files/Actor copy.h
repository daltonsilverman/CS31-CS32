#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <string>

class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor: public GraphObject {
public:
    Actor(int imageID, int startX, int startY, int state = 1, int dir = right, int depth = 0, double size = 1.0): GraphObject(imageID, startX, startY, dir, depth, size)  {m_state = state;};
    virtual void doSomething();
    int state(){return Actor::m_state;}
    bool isAlive(){if(state() == -1) return false; else return true;
        return true;
    }
    void changeState(int n){m_state = n;}
private:
    int m_state;
};

class CoinSquare: public Actor {
public:
    CoinSquare(int x, int y): Actor(IID_BLUE_COIN_SQUARE, x, y, 1, 0, 0, 1.0) {m_coin_change = 3; std::cout << "CoinSquare loaded at: (" << x/16 << ", " << y/16 << ")" << std::endl; };
    void doSomething();
private:
    int m_coin_change;
};

class PlayerAvatar: public Actor {
public:
    PlayerAvatar(int x, int y, StudentWorld* world): Actor(IID_PEACH, x, y, 1, 0, 0, 1.0) {playerNum = 1; ticks_to_move = 0; m_walkingDirection = right; m_world = world; die_roll = 0; std::cout << "Peach loaded at: (" << x/16 << ", " << y/16 << ")" << std::endl;}
    void doSomething();
private:
    int m_walkingDirection;
    int ticks_to_move;
    int playerNum;
    int die_roll;
    StudentWorld* m_world;
    };
#endif // ACTOR_H_
