//
//  main.cpp
//  CardSet
//
//  Created by Dalton Silverman on 1/24/23.
//
#include "CardSet.h"
#include <iostream>

int main(int argc, const char * argv[]) {
    CardSet test;
    for(int i = 0; i < DEFAULT_MAX_ITEMS; i++){
        test.add(i);
    }
    assert(!test.add(1000));
    assert(test.size() == DEFAULT_MAX_ITEMS);
    test.print();
}


