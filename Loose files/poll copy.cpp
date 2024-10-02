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

void testone(int n)
{
    int s = 666;
    switch (n)
    {
                     default: {
        cout << "Bad argument" << endl;
            } break; case  1: {
        assert(!isValidPollString("3"));
            } break; case  2: {
        assert(!isValidPollString("#"));
            } break; case  3: {
        assert(!isValidPollString("3A"));
            } break; case  4: {
        assert(!isValidPollString("#A"));
            } break; case  5: {
        assert(!isValidPollString("C"));
            } break; case  6: {
        assert(!isValidPollString("C3"));
            } break; case  7: {
        assert(!isValidPollString("C#"));
            } break; case  8: {
        assert(!isValidPollString("CA3"));
            } break; case  9: {
        assert(!isValidPollString("CA73"));
            } break; case 10: {
        assert(!isValidPollString("CAD"));
            } break; case 11: {
        assert(!isValidPollString("CA$"));
            } break; case 12: {
        assert(!isValidPollString("CA7%"));
            } break; case 13: {
        assert(!isValidPollString("CA73%"));
            } break; case 14: {
        assert(!isValidPollString("CA738"));
            } break; case 15: {
        assert(!isValidPollString("CA738D"));
            } break; case 16: {
        assert(!isValidPollString("CA006D"));
            } break; case 17: {
        assert(!isValidPollString("XU44D"));
            } break; case 18: {
        assert(!isValidPollString("Xu44D"));
            } break; case 19: {
        assert(!isValidPollString("xU44D"));
            } break; case 20: {
        assert(!isValidPollString("xu44D"));
            } break; case 21: {
        assert(!isValidPollString("CA 55D"));
            } break; case 22: {
        assert(!isValidPollString("CA55 D"));
            } break; case 23: {
        assert(!isValidPollString("AZ4DE5R"));
            } break; case 24: {
        assert(!isValidPollString("AZ4D#5R"));
            } break; case 25: {
        assert(!isValidPollString("AZ4D5"));
            } break; case 26: {
        assert(!isValidPollString("AZ4D5#5R"));
            } break; case 27: {
        assert(!isValidPollString("AZ4D5RI"));
            } break; case 28: {
        assert(!isValidPollString("FL15RI"));
            } break; case 29: {
        assert(!isValidPollString("FL15R@12D"));
            } break; case 30: {
        assert(!isValidPollString("FL15R1"));
            } break; case 31: {
        assert(!isValidPollString("FL15R1@12D"));
            } break; case 32: {
        assert(!isValidPollString("FL15R12DE"));
            } break; case 33: {
        assert(!isValidPollString("FL15R 12D"));
            } break; case 34: {
        assert(!isValidPollString("UT4RHI2D"));
            } break; case 35: {
        assert(!isValidPollString(","));
            } break; case 36: {
        assert(!isValidPollString(",WY1R"));
            } break; case 37: {
        assert(!isValidPollString("WY1R,"));
            } break; case 38: {
        assert(!isValidPollString("WY1R, MA8D,VT1D"));
            } break; case 39: {
        assert(!isValidPollString("WY1R,MA8D ,VT1D"));
            } break; case 40: {
        assert(!isValidPollString("WY1R,8D,VT1D"));
            } break; case 41: {
        assert(!isValidPollString("WY1R,MA8,VT1D"));
            } break; case 42: {
        assert(!isValidPollString("WY1R,GA10,VT1D"));
            } break; case 43: {
        assert(isValidPollString(""));
            } break; case 44: {
        assert(isValidPollString("CA"));
            } break; case 45: {
        assert(isValidPollString("Ca4D"));
            } break; case 46: {
        assert(isValidPollString("cA4D"));
            } break; case 47: {
        assert(isValidPollString("ca4D"));
            } break; case 48: {
        assert(isValidPollString("CA42D"));
            } break; case 49: {
        assert(isValidPollString("Ca42D"));
            } break; case 50: {
        assert(isValidPollString("cA42D"));
            } break; case 51: {
        assert(isValidPollString("ca42D"));
            } break; case 52: {
        assert(isValidPollString("CA9D"));
            } break; case 53: {
        assert(isValidPollString("CA4D"));
            } break; case 54: {
        assert(isValidPollString("CA0D"));
            } break; case 55: {
        assert(isValidPollString("CA89D"));
            } break; case 56: {
        assert(isValidPollString("CA09D"));
            } break; case 57: {
        assert(isValidPollString("CA00D"));
            } break; case 58: {
        assert(isValidPollString("CA4d"));
            } break; case 59: {
        assert(isValidPollString("CA42d"));
            } break; case 60: {
        assert(isValidPollString("CA4Z"));
            } break; case 61: {
        assert(isValidPollString("CA42Z"));
            } break; case 62: {
        assert(isValidPollString("KY5R1D"));
            } break; case 63: {
        assert(isValidPollString("FL15R12D"));
            } break; case 64: {
        assert(isValidPollString("GA10R4D"));
            } break; case 65: {
        assert(isValidPollString("GA4D10R"));
            } break; case 66: {
        assert(isValidPollString("CA11R22D3G1A7N"));
            } break; case 67: {
        assert(isValidPollString("LA2R1D3R"));
            } break; case 68: {
        assert(isValidPollString("WY1R,MA8D"));
            } break; case 69: {
        assert(isValidPollString("WY1R,MA8D,ID2R"));
            } break; case 70: {
        assert(isValidPollString("WY1R,MA,ID2R"));
            } break; case 71: {
        assert(isValidPollString("CA55D,KS10R,TX20R"));
            } break; case 72: {
        assert(isValidPollString("CA20D4R,KS4R,CA19D10R"));
            } break; case 73: {
        assert(isValidPollString("AL1D7R,AZ4D5R,AK4R,CA14R39D,CO3D4R"));
            } break; case 74: {
        assert(countSeats("3#QQ## QQ####", 'D', s) == 1);
            } break; case 75: {
        countSeats("3#QQ## QQ####", 'D', s);
        assert(s == 666);
            } break; case 76: {
        assert(countSeats("WV5R", '5', s) == 2);
            } break; case 77: {
        countSeats("WV5R", '5', s);
        assert(s == 666);
            } break; case 78: {
        assert(countSeats("TX38R", '5', s) == 2);
            } break; case 79: {
        countSeats("TX38R", '5', s);
        assert(s == 666);
            } break; case 80: {
        int r = countSeats("3#QQ## QQ####", '%', s);
        assert(r == 1  ||  r == 2);
            } break; case 81: {
        assert(countSeats("SD3R", 'R', s) == 0  &&  s == 3);
            } break; case 82: {
        assert(countSeats("SD3r", 'R', s) == 0  &&  s == 3);
            } break; case 83: {
        assert(countSeats("SD3R", 'r', s) == 0  &&  s == 3);
            } break; case 84: {
        assert(countSeats("SD3r", 'r', s) == 0  &&  s == 3);
            } break; case 85: {
        assert(countSeats("NY29D", 'D', s) == 0  &&  s == 29);
            } break; case 86: {
        assert(countSeats("NY29d", 'D', s) == 0  &&  s == 29);
            } break; case 87: {
        assert(countSeats("NY29D", 'd', s) == 0  &&  s == 29);
            } break; case 88: {
        assert(countSeats("NY29d", 'd', s) == 0  &&  s == 29);
            } break; case 89: {
        assert(countSeats("UT6L", 'D', s) == 0  &&  s == 0);
            } break; case 90: {
        assert(countSeats("WA11G", 'D', s) == 0  &&  s == 0);
            } break; case 91: {
        assert(countSeats("WA3G1D5L2R", 'L', s) == 0  &&  s == 5);
            } break; case 92: {
        assert(countSeats("WA03G01D05L12R", 'L', s) == 0  &&  s == 5);
            } break; case 93: {
        assert(countSeats("WA03G01D05L12R", 'R', s) == 0  &&  s == 12);
            } break; case 94: {
        assert(countSeats("LA2R6D3R", 'R', s) == 0  &&  s == 5);
            } break; case 95: {
        assert(countSeats("KS,WY,VT,HI", 'G', s) == 0  &&  s == 0);
            } break; case 96: {
        assert(countSeats("KS4R,WY3G,VT1I,HI2D", 'G', s) == 0  &&  s == 3);
            } break; case 97: {
        assert(countSeats("KS14R,WY13G,VT11I,HI12D", 'G', s) == 0  &&  s == 13);
            } break; case 98: {
        assert(countSeats("KS4R,WY3G,VT1I,HI2D", 'L', s) == 0  &&  s == 0);
            } break; case 99: {
        assert(countSeats("IL11R,DE5G,MD7D", 'D', s) == 0  &&  s == 7);
            } break; case 100: {
        assert(countSeats("KS4R,WY1R,MA9D,ID2R,HI2D", 'R', s) == 0  &&  s == 7);
            } break; case 101: {
        assert(countSeats("AL1D6R,CT5D,KY5R1D,MI9R4D,NJ7D5R", 'R', s) == 0  &&  s == 25);
            } break; case 102: {
        assert(countSeats("CA39D14R,FL15R11D,TX11D25R", 'R', s) == 0  &&  s == 54);
            } break; case 103: {
        assert(countSeats("MI4D4R5R,TN1D4R1D3R", 'R', s) == 0  &&  s == 16);
            } break; case 104: {
        assert(countSeats(
        "AL1D6R,AK1R,AZ4D5R,AR4R,CA39D14R,CO3D4R,CT5D,DE1D,FL11D16R,"
        "GA4D10R,HI2D,ID2R,IL11D7R,IN2D7R,IA1D3R,KS4R,KY1D5R,LA1D5R,"
        "ME1D1R,MD7D1R,MA9D,MI5D9R,MN5D3R,MS1D3R,MO2D6R,MT1R,NE3R,"
        "NV3D1R,NH2D,NJ7D5R,NM2D1R,NY18D9R,NC3D10R,ND1R,OH4D12R,"
        "OK5R,OR4D1R,PA1D11R,RI2D,SC1D6R,SD1R,TN2D7R,TX11D25R,UT4R,"
        "VT1D,VA4D7R,WA6D4R,WV3R,WI3D5R,WY1R", 'D', s) == 0  &&  s == 190);
            } break; case 105: {
        assert(countSeats(
        "AL1D6R,AK1R,AZ4D5R,AR4R,CA39D14R,CO3D4R,CT5D,DE1D,FL11D16R,"
        "GA4D10R,HI2D,ID2R,IL11D7R,IN2D7R,IA1D3R,KS4R,KY1D5R,LA1D5R,"
        "ME1D1R,MD7D1R,MA9D,MI5D9R,MN5D3R,MS1D3R,MO2D6R,MT1R,NE3R,"
        "NV3D1R,NH2D,NJ7D5R,NM2D1R,NY18D9R,NC3D10R,ND1R,OH4D12R,"
        "OK5R,OR4D1R,PA1D11R,RI2D,SC1D6R,SD1R,TN2D7R,TX11D25R,UT4R,"
        "VT1D,VA4D7R,WA6D4R,WV3R,WI3D5R,WY1R", 'R', s) == 0  &&  s == 239);
            } break; case 106: {
        assert(countSeats(
        "AL1D6R,AK1R,AZ4D5R,AR4R,CA39D14R,CO3D4R,CT5D,DE1D,FL11D16R,"
        "GA4D10R,HI2D,ID2R,IL11D7R,IN2D7R,IA1D3R,KS4R,KY1D5R,LA1D5R,"
        "ME1D1R,MD7D1R,MA9D,MI5D9R,MN5D3R,MS1D3R,MO2D6R,MT1R,NE3R,"
        "NV3D1R,NH2D,NJ7D5R,NM2D1R,NY18D9R,NC3D10R,ND1R,OH4D12R,"
        "OK5R,OR4D1R,PA1D11R,RI2D,SC1D6R,SD1R,TN2D7R,TX11D25R,UT4R,"
        "VT1D,VA4D7R,WA6D4R,WV3R,WI3D5R,WY1R", 'I', s) == 0  &&  s == 0);
            }
    }
}

int main()
{
    cout << "Enter test number: ";
    int n;
    cin >> n;
    testone(n);
    cout << "Passed if there was no undefined behavior." << endl;
}


