//
//  main.cpp
//  CS_Project_3
//
//  Created by Dalton Silverman on 10/20/22.
//

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

//*************************************
//  isValidUppercaseStateCode
//*************************************

// Return true if the argument is a two-uppercase-letter state code, or
// false otherwise.

bool isValidUppercaseStateCode(string stateCode)
{
    if(stateCode.size() == 2){
        stateCode[0] = toupper(stateCode[0]);
        stateCode[1] = toupper(stateCode[1]);
    }
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
        "LA.ME.MA.MD.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
        "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

//*********************************
//isValidPartyResult
//*********************************

//Returns true if the partyResult argument follows the definition for a party result,
//either one or two digits followed by a letter. The second argument, pos, is an indexer
//to make this easy in string processing in combination with future methods
bool isValidPartyResult(string partyResult, int& pos){
    if(partyResult.size() == 2){ //Checks for case of one digit and one letter and advances pos indexer
        pos += 2;
        return (isdigit(partyResult.at(0)) && isalpha(partyResult.at(1)));
    }
    if(partyResult.size() == 3){ //Checks for case of two digits and one letter and advances pos indexer
        pos += 3;
        return(isdigit(partyResult.at(0)) && isdigit(partyResult.at(1)) && isalpha(partyResult.at(2)));
    }
    return false; //if neither of these cases are accurate, automatically returns false
}



//*******************************
//isValidStateForecast
//*******************************

//Returns true if argument meets definition of a state forecast, in which the string is a
//party code followed by one or more state forecasts.
bool isValidStateForecast(string stateForecast) {
    if(!isValidUppercaseStateCode(stateForecast.substr(0, 2))){ //Checks if first two characters are a state code, if not immediately fails test.
        return false;
    }
    int k = 2;
    while(k != stateForecast.size()) { //Goes through remaining text in string after first 2 charcters (k incremented in isValidPartyResult function)
        if(k == stateForecast.size() - 1){
            return false;
        }
        if(isdigit(stateForecast.at(k+1))) { //Locates digit and checks to see if next character is digit to determine how long string passed to isValidPartyResult should be
            if(!isValidPartyResult(stateForecast.substr(k, 3), k)){ //Checks if section is a valid party result, if not immediately returns false and stops testing
                return false;
            }
        }
        else{
            if(!isValidPartyResult(stateForecast.substr(k, 2), k)){ //Checks in cases wehere no digit detected/only one digit and one letter, if fails immediately returns false
                return false;
            }
        }
    }
    return true; //if passes through whole string with only state code followed by valid party results, returns true
}

//**************************
//isValidPollString
//**************************

//returns true if entered argument is a poll string, meeting the definition of one or more state forecasts separated by a comma, false if not

bool isValidPollString(string pollData){
    if(pollData == ""){ //returns true in case that there is an empty string
        return true;
    }
    int priorPosition = 0;
    for(int i = 0; i != pollData.size(); i++){
        //cerr << priorPosition << endl;
        if(i == pollData.size() - 1){ //checks in instance loop has reached end of string that the substring between the last instance of a command and the last character is a state forecast
            if(!isValidStateForecast(pollData.substr(priorPosition, pollData.size()))){
                return false; //if it isn't then imemdiately returns false
            }
        }
        else if(pollData[i] == ','){ //checks for instance of comma and tests if substring of last instance of comma/beginning to the current instance of a comma is a valid state forecast
            if(!isValidStateForecast(pollData.substr(priorPosition, (i-priorPosition)))){
                return false; //returns false if it isn't
            }
            priorPosition = i + 1; //records instance of comma to variable holding last instance of a comma
        }
    }
    return true; //if string passes through entirely without detecting an invalid state forecast, returns true
}

//*************************
//countSeats
//************************

//string pollData inputted string to be processed, char party inputted char to declare
//what party we are counting seats for, int& seatcount variable where number of seats
//is inputted. If given an invalid string then returns 1 and does not change seatcount argument.
//If given a non letter for party, returns 2 and does not change seatCount argument.
//Otherwise returns 0 and updates seatcount variable for number of seats earned in a given poll string.
int countSeats(string pollData, char party, int& seatcount){
    if(!isValidPollString(pollData)){ //if invalid poll string return 1 and no change to seatcount
        return 1;
    }
    if(!isalpha(party)){ //if non-letter party given, return 2 and no change to seat count
        return 2;
    }
    if(pollData == "") //if empty pollData, return 0 and set seatcount to 0
    {
        seatcount = 0;
        return 0;
    }
    int seatsSum = 0;
    int onesHolder;
    int tensHolder;
    int converter = '0';
    for(int i = 2; i != pollData.size(); i++) { //Search pollData for instances of char matching char given in party argument
        if(toupper(pollData.at(i)) == toupper(party)){
            if(isdigit(pollData.at(i-2))){ //Parse charcacters in string into an int using char-int rules.
                tensHolder = pollData.at(i-2); //In case of 2 back to back digits use tens and ones place
                onesHolder = pollData.at(i-1);
                seatsSum += (tensHolder - converter) * 10 + (onesHolder - converter);
            }
            else{
                onesHolder = pollData.at(i-1); //In case of 1 digit, simply use ones place
                seatsSum += onesHolder - converter;
            }
        }
    }
    seatcount = seatsSum; // set seatcount argument to whatever number of seats was summed
    
    return 0;
}

int main() {
    assert(isValidPollString("")); //Testing empty poll string
    assert(isValidPollString("CT")); //Testing only state code
    assert(isValidPollString("CT5D")); //Testing state forecast with one result
    assert(isValidPollString("CT5D4R")); //Testing state forecast with two results
    assert(!isValidPollString("5D")); //Testing only party result does not register false pass
    assert(isValidPollString("ne3r00d")); //testing all lowercase state forecast
    assert(isValidPollString("CT5D,NY9R16D1I,VT,ne3r00D")); //testing multiple state forecasts
    assert(!isValidPollString("C")); //testing single letter (aka just a party code)
    assert(!isValidPollString("CT5D,")); //testing edge case where k indexer in function previously led to index out of bounds error
    assert(!isValidPollString("CT%D")); //Testing inclusion of non-letters and no numbers
    int seats = -999;
    assert(countSeats("", 'D', seats) == 0 && seats == 0); //Check empty string sets seats to 0
    seats = -999;
    assert(countSeats("Q", 'D', seats) == 1 && seats == -999); //Checks invalid pollstring returns 1 and does not change seats
    seats = -999;
    assert(countSeats("NY9R16D1I,Vt,NJ3d5r4D,KS4R", '%', seats) == 2 && seats == -999); //Checks non-letter party code returns 2 and does not change seats
    seats = -999;
    assert(countSeats("CT", 'D', seats) == 0 && seats == 0); //Checks only statecode returns 0 seats
    seats = -999;
    assert(countSeats("CT5D4R", 'D', seats) == 0 && seats == 5); //Checks sole forecast works
    seats = -999;
    assert(countSeats("CT5D4r", 'R', seats) == 0 && seats == 4); //Checks mismatch in uppercaser and lowercase still functions properly
    seats = -999;
    assert(countSeats("NJ3D5r4D", 'D', seats) == 0 && seats == 7); //Checks if multiple occurence of some party in result functions properly
    seats = -999;
    assert(countSeats("NJ3D5r4d", 'd', seats) == 0 && seats == 7); //Checks if lowercase party code still functions
    assert(countSeats("NY9R16D1I,Vt,NJ3d5r4D,KS4R", 'D', seats) == 0 && seats == 23); //Checks full poll string with difference in capitalization and repeat parties
}


