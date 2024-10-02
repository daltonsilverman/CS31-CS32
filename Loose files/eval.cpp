//
//  main.cpp
//  Homework2Part2
//
//  Created by Dalton Silverman on 2/8/23.
//
#include "Set.h"
#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool isOperator(char t);
int getPrecedence(char t);



int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result){
    
    int openCounter = 0;
    int closedCounter = 0;
    //postfix part
    postfix = "";
    stack<char>operators;
    for(int i = 0; i < infix.size(); i++){
        if(isalpha(infix.at(i)) && islower(infix.at(i)))
            postfix += infix.at(i);
        else if(infix.at(i) == '('){
            openCounter++;
            operators.push(infix.at(i));
        }
        else if(infix.at(i) == ')'){
            closedCounter++;
            while(operators.top() != '('){
                postfix += operators.top();
                operators.pop();
            }
            operators.pop();
        }
        else if(isOperator(infix.at(i))){
            while(!operators.empty() && operators.top() != '(' && getPrecedence(infix.at(i)) <= getPrecedence(operators.top())){
                postfix += operators.top();
                operators.pop();
            }
            operators.push(infix.at(i));
        }
        else if(!isalpha(infix.at(i)) || !islower(infix.at(i)))
            return 1;
    }
    if(openCounter != closedCounter)
        return 1;
    while(!operators.empty()){
        postfix += operators.top();
        operators.pop();
    }
    
        
        for(int i = 0; i < infix.size(); i++){
            if(isalpha(infix.at(i))){
                if(!trueValues.contains(infix.at(i)) && (!falseValues.contains(infix.at(i))))
                    return 2;
                if(trueValues.contains(infix.at(i)) && falseValues.contains(infix.at(i)))
                    return 3;
            }
        }
        
    stack<char>operands;

    
    bool operand2 = true;
    bool operand1 = false;
    
    for(int i = 0; i < postfix.length(); i++){
        if(isalpha(postfix.at(i)))
            operands.push(postfix.at(i));
        else{
            if(trueValues.contains(operands.top()))
                operand2 = true;
            else
                operand2 = false;
            operands.pop();
            if(trueValues.contains(operands.top()))
                operand1 = true;
            else
                operand1 = false;
            operands.pop();
            if(postfix.at(i) == '&')
                operands.push(operand1 && operand2);
            else if(postfix.at(i) == '|')
                operands.push(operand1 || operand2);
            else if(postfix.at(i) == '!')
                operands.push(!operand1 && !operand2);
        }
        result = operands.top();
        return 0;
    }
    return 0;
}


bool isOperator(char t){
    if(t == '&' || t == '|' || t == '!' || t == '(' || t == ')')
        return true;
    return false;
}

int getPrecedence(char t){
    if(t == '!')
        return 4;
    if(t == '&')
        return 3;
    if(t == '|' )
        return 2;
    if(t == '(' || t == ')')
        return 1;
    
    return 1;
}
