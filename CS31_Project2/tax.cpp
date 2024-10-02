//
//  tax.cpp
//  CS31_2nd_Project
//
//  Created by Dalton Silverman on 10/10/22.
//

#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << "Name: ";  //Receives input for name
    string name;
    getline(cin, name);
    if(name == "") {
        cout << "---" << endl;
        cout << "You must enter a name" << endl;
        return 1;     //Checks input for error and terminates if error exists
    }
    
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "Taxable income: ";
    double income;
    cin >> income; //Receives input for income to the first 2 decimal places
    if(income < 0) {
        cout << "---" << endl;
        cout << "The taxable income must not be negative" << endl; //Checks input for error and terminates if error occurs
        return 2;
    }
    cin.ignore(10000, '\n');
    
    cout << "Occupation: ";
    string occupation;
    getline (cin, occupation); //Receives input for occupation
    if(occupation == "") {
        cout << "---" << endl;
        cout << "You must enter an occupation" << endl;
        return 3; //Checks input for error and terminates if error occurs
    }
    
    cout << "Number of children: ";
    int numChildren;
    cin >> numChildren; //Receives input for the number of children
    if (numChildren < 0) {
        cout << "---" << endl;
        cout << "The number of children must not be negative" << endl;
        return 4; //Checks input for error and terminates if error occurs
    }
    cout << "---" << endl;
    
    double totalTax = 0;
    double FIRST_TAX_BRACKET = 55000;
    double SECOND_TAX_BRACKET = 125000; //establishes constants and intializes other variables used in this function
    
    if(income < FIRST_TAX_BRACKET) { //Calculates the amount of income taxed for income that is within the first $55,000
        totalTax += 0.04 * income;
    }
    else {
        totalTax += 0.04 * FIRST_TAX_BRACKET;
    }
    if(occupation == "teacher" || occupation == "nurse") { //Calculates the amount of income taxed for nurses and teachers that is within the next $75,000
        if(income < SECOND_TAX_BRACKET && income > FIRST_TAX_BRACKET) {
            totalTax += 0.05 * (income - FIRST_TAX_BRACKET);
        }
        else if(income > FIRST_TAX_BRACKET) {
            totalTax += 0.05 * (SECOND_TAX_BRACKET - FIRST_TAX_BRACKET);
        }
    }
    else if(income < SECOND_TAX_BRACKET && income > FIRST_TAX_BRACKET) { //Calculates the amount of income taxed for non-nurses/teachers that is within the next $75,000
        totalTax += 0.07 * (income - FIRST_TAX_BRACKET);
    }
    else if(income > FIRST_TAX_BRACKET) {
        totalTax += 0.07 * (SECOND_TAX_BRACKET - FIRST_TAX_BRACKET);
    }
    if(income > SECOND_TAX_BRACKET){ //Calculates income taxed for income greater than $125,000
        cout << totalTax << endl;
        totalTax += 0.093 * (income - SECOND_TAX_BRACKET);
    }
    
    if(income < SECOND_TAX_BRACKET){ //Applies child credit discount to those eligible
        totalTax = totalTax - 200 * numChildren;
    }
    if(totalTax < 0){ //Ensures tax cannot be negative
        totalTax = 0;
    }
    
    cout << name << " would pay $" << totalTax << endl; //Returns total number of income tax that a person will owe.
    
    
}
