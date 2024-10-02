//
//  History.hpp
//  Rabbit
//
//  Created by Dalton Silverman on 1/18/23.
//

#ifndef History_hpp
#define History_hpp
class Arena;

class History
    {
      public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
    private:
        Arena* m_arena;
        
    };


#endif /* History_hpp */
