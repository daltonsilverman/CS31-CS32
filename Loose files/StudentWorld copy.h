#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_
#include "Actor.h"
#include "GameWorld.h"
#include "Board.h"
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  ~StudentWorld();
  virtual int init();
  virtual int move();
  virtual void cleanUp();
    Board* getBoard(){return m_board;};

private:
    Actor* m_array[100];
    int n;
    Board* m_board;
    Actor* m_boardMembers[500];
    int n_board;
    
};

#endif // STUDENTWORLD_H_
