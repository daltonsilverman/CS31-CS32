//
//  main.cpp
//  Homework2
//
//  Created by Dalton Silverman on 2/8/23.
//

#include <iostream>
#include <stack>
using namespace std;

class Coord
        {
          public:
            Coord(int r, int c) : m_row(r), m_col(c) {}
            int r() const { return m_row; }
            int c() const { return m_col; }
          private:
            int m_row;
            int m_col;
        };

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
          // Return true if there is a path from (sr,sc) to (er,ec)
          // through the maze; return false otherwise


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    stack<Coord> coordStack;
    Coord* transfer = nullptr;;
    coordStack.push(Coord(sr, sc));
    maze[sr][sc] = '/';
    while(!coordStack.empty()){
        if(transfer != nullptr)
            delete transfer;
        transfer = &coordStack.top();
        coordStack.pop();
        if(transfer->r() == er && transfer->c() == ec)
            return true;
        if(maze[transfer->r()][transfer->c()+1] == '.'){ //check east
            coordStack.push(Coord(transfer->r(), transfer->c() + 1));
            maze[transfer->r()][transfer->c()+1] = '/';
        }
        if(maze[transfer->r()-1][transfer->c()] == '.'){ //check north
            coordStack.push(Coord(transfer->r()-1, transfer->c()));
            maze[transfer->r()-1][transfer->c()] = '/';
        }
        if(maze[transfer->r()][transfer->c()-1] == '.'){ //Check west
            coordStack.push(Coord(transfer->r(), transfer->c()-1));
            maze[transfer->r()][transfer->c()-1] = '/';
        }
        if(maze[transfer->r()+1][transfer->c()] == '.'){ //check south
            coordStack.push(Coord(transfer->r()+1, transfer->c()));
            maze[transfer->r()+1][transfer->c()] = '/';
        }
    }
    return false;
}
