//
//  CardSet.cpp
//  CardSet
//
//  Created by Dalton Silverman on 1/24/23.
//

#include "CardSet.h"
#include "iostream"

CardSet::CardSet(){
    
}

bool CardSet::add(unsigned long cardNumber){
    if(m_set.insert(cardNumber))
        return true;
    return false;
}
  // Add a card number to the CardSet.  Return true if and only if the
  // card number was actually added.

int CardSet::size() const{
    return m_set.size();
}  // Return the number of card numbers in the CardSet.

void CardSet::print() const{
    unsigned long temp;
    for(int i = 0; i < size(); i++){
        m_set.get(i, temp);
        std::cout << temp << std::endl;
    }
}
  // Write to cout every card number in the CardSet exactly once, one
  // per line.  Write no other text.

