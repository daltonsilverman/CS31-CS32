//
//  Game.hpp
//  Rabbit
//
//  Created by Dalton Silverman on 1/18/23.
//


#ifndef Game_hpp
#define Game_hpp
#include <string>
class Arena;

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nRabbits);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    std::string takePlayerTurn();
};

#endif /* Arena_hpp */
