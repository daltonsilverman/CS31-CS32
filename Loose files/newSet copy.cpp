//
//  newSet.cpp
//  newSet
//
//  Created by Dalton Silverman on 1/24/23.
//

//
//  Set.cpp
//  SetProb3
//
//  Created by Dalton Silverman on 1/23/23.
//

#include "newSet.h"
#include <iostream>

Set::Set() {
    m_array = new ItemType[DEFAULT_MAX_ITEMS];
    m_size = 0;
    m_maxSize = DEFAULT_MAX_ITEMS;
}

Set::Set(int maxSize) {
    if(maxSize < 0){
        std::cout << "Argument most be positive" << std::endl;
        return;
    }
    m_array = new ItemType[maxSize];
    m_size = 0;
    m_maxSize = maxSize;
}

Set::~Set(){
    delete [] m_array;
}

Set::Set(const Set& other){
    m_size = other.m_size;
    m_maxSize = other.m_maxSize;
    m_array = new ItemType[m_maxSize];
    for(int i = 0; i < m_size; i++){
        m_array[i] = other.m_array[i];
    }
}

Set& Set::operator=(const Set& other) {
    if(this != &other){
        Set temp(other);
        swap(temp);
    }
    return *this;
}

int Set::size() const {
    return m_size;
}    // Return the number of items in the set.


bool Set::empty() const {
    return m_size == 0;
}// Return true if the set is empty, otherwise false.

bool Set::insert(const ItemType& value){
    if(m_size == m_maxSize){
        return false;
    }
    for(int i = 0; i < m_size; i++){
        if(value == m_array[i]){
            return false;
        }
        if(value < m_array[i]){
            for(int j= m_size-1; j >= i; j--)
            {
                m_array[j+1] = m_array[j];
            }
            m_array[i] = value;
            m_size++;
            return true;
        }
    }
    m_array[m_size] = value;
    m_size++;
    return true;
}
  // Insert value into the set if it is not already present.  Return
  // true if the value is actually inserted.  Leave the set unchanged
  // and return false if value is not inserted (perhaps because it
  // was already in the set or because the set has a fixed capacity and
  // is full).

bool Set::erase(const ItemType& value) {
    for(int i = 0; i < m_size; i++){
        if(value == m_array[i])
        {
            for(int j = i; j < m_size-1; j++){
                m_array[j] = m_array[j+1];
            }
            m_size--;
            return true;
        }
    }
    return false;
    
}
  // Remove the value from the set if it is present.  Return true if the
  // value was removed; otherwise, leave the set unchanged and
  // return false.

bool Set::contains(const ItemType& value) const {
    for(int i = 0; i < m_size; i++) {
        if(value == m_array[i])
            return true;
    }
    return false;
}
  // Return true if the value is in the set, otherwise false.

bool Set::get(int i, ItemType& value) const{
    if(0 <= i && i < m_size){
        value = m_array[i];
        return true;
    }
    return false;
}
  // If 0 <= i < size(), copy into value the item in the set that is
  // strictly greater than exactly i items in the set and return true.
  // Otherwise, leave value unchanged and return false.

void Set::swap(Set& other){
    ItemType* temp;
    temp = m_array;
    m_array = other.m_array;
    other.m_array = temp;
    
    int tempSize;
    tempSize = m_size;
    m_size = other.size();
    other.m_size = tempSize;
    
    tempSize = m_maxSize;
    m_maxSize = other.m_maxSize;
    other.m_maxSize = tempSize;

}
  // Exchange the contents of this set with the other one.

void Set::dump() const {
    for(int i = 0; i < m_size; i++)
    {
        std::cout << m_array[i] << std::endl;
    }
}
 


