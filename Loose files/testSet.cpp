//
//  main.cpp
//  SetProb3
//
//  Created by Dalton Silverman on 1/23/23.
//

#include <iostream>
#include "Set.h"
#include <cassert>
using namespace std;

void test()
       {
           Set ss;
           assert(ss.insert("roti"));
           assert(ss.insert("pita"));
           assert(ss.size() == 2);
           assert(ss.contains("pita"));
           ItemType x = "laobing";
           assert(ss.get(0, x)  &&  x == "pita");
           assert(ss.get(1, x)  &&  x == "roti");
       }



int main(int argc, const char * argv[]) {
   /* Set mySet;
    mySet.insert(3);
    mySet.insert(6);
    mySet.insert(2);
    mySet.insert(1);
    mySet.insert(4);
    mySet.insert(5);
    Set newSet;
    newSet.insert(4);
    newSet.insert(2);
    newSet.insert(3);
    mySet.swap(newSet);
    
    Set s;
            assert(s.empty());
            ItemType x = 9876543;
            assert( !s.get(42, x)  &&  x == 9876543); // x unchanged by get failure
            s.insert(123456789);
            assert(s.size() == 1);
            assert(s.get(0, x)  &&  x == 123456789);
            
    Set n;
    assert(n.empty());
    n.insert(1);
    n.insert(3);
    n.insert(4);
    assert(!n.insert(4));
    n.erase(4);
    assert(!n.erase(4));
    assert(n.contains(1));
    assert(n.contains(3));
    assert(!n.contains(4));
    
    Set q;
    for(int i = 0; i < DEFAULT_MAX_ITEMS; i++){
        q.insert(i);
    }
    assert(!q.insert(1000));
    n = q;
    
    Set p = q;
    
    
    
            cout << "Passed all tests" << endl;
    
    return 0; */
    
    test();
                cout << "Passed all tests" << endl;
    return 0;
}
