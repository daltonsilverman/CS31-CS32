//
//  main.cpp
//  LAPractice
//
//  Created by Dalton Silverman on 3/1/23.
//

#include <iostream>
using namespace std;



struct Node { int data;
Node* next; };
class LL {
public: // other functions such as insert not shown
void deleteList(); // implement this function private: // additional helper function allowed
Node* m_head; };

void LL::deleteList() {
    if(m_head->next == nullptr){
        delete m_head;
        return;
    }
    Node* temp = m_head->next;
    delete m_head;
    m_head = temp;
    deleteList();
}

bool isPalindrome(string foo){
    if(foo.size() == 1 || foo.size() == 0)
        return true;
    if(foo[0] == foo[foo.size()-1]){
        return isPalindrome(foo.substr(1, foo.size()-2));
    }
    return false;
}

bool dividedBy(int num, int divisor){
    if(num%divisor == 0)
        return false;
    if(divisor * divisor >= num)
        return true;
    return dividedBy(num, divisor+1);
}

bool isPrime(int num) {
    if(num == 2){
        return true;
    }
    if(num == 1)
        return false;
    if(num == 0)
        return false;
    return dividedBy(num, 2);
}



int main() {
    cout << isPalindrome("SttS") << endl;
}


