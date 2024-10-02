//
//  History.cpp
//  Rabbit
//
//  Created by Dalton Silverman on 1/18/23.
//

#include "History.h"
#include <iostream>
#include "Arena.h"
#include "globals.h"
using namespace std;

History::History(int nRows, int nCols)
{
    m_arena = new Arena(nRows, nCols);
}

bool History::record(int r, int c) {
    if(r < MAXROWS && r > 0 && c < MAXCOLS && c > 0){
        m_arena->setCellStatus(r, c, HAS_POISON);
        return true;
    }
    return false;
}

void History::display() const {
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;
    
      // Fill displayGrid with dots (empty) and stars (poisoned carrots)
    for (r = 1; r <= m_arena->rows(); r++)
        for (c = 1; c <= m_arena->cols(); c++)
            displayGrid[r-1][c-1] = (m_arena->getCellStatus(r,c) == EMPTY ? '.' : '*');
    
    // Draw the grid
  clearScreen();
  for (r = 1; r <= m_arena->rows(); r++)
  {
      for (c = 1; c <= m_arena->cols(); c++)
          cout << displayGrid[r-1][c-1];
      cout << endl;
  }
  cout << endl;
}
