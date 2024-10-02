//
//  main.cpp
//  CS31_Project4
//
//  Created by Dalton Silverman on 10/31/22.
//

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int appendToAll(string a[], int n, string value){
    if(n < 0){ // negative n check
        return -1;
    }
    for(int i = 0; i < n; i++){ //adds value to each string in "a" array
        a[i] += value;
    }
    return n;
}

int lookup(const string a[], int n, string target){
    if(n < 0){ //negative n check
        return -1;
    }
    for(int i = 0; i < n; i++){ //Traverses entire array, stops when finds a match
        if(a[i] == target){
            return i;
        }
    }
    return -1; //if no match, return -1
}

int positionOfMax(const string a[], int n){
    if(n <= 0 ){ //negative n check
        return -1;
    }
    int max = 0;
    for(int i = 0; i < n; i++) //if position in array is greater than previous max, update max
    {
        if(a[i] > a[max]){
            max = i;
        }
    }
    return max;
}

int rotateLeft(string a[], int n, int pos) {
    if(n < 0){ //negative n check
        return -1;
    }
    string temp = a[pos];
    for(int i = pos; i < n-1; i++){ //updates each position to contain the value of the next position
        a[i] = a[i + 1];
    }
    a[n-1] = temp; //updates final position with initial position
    return pos;
}

int rotateRight(string a[], int n, int pos) {
    if(n < 0){ //negative n check
        return -1;
    }
    string temp = a[pos];
    for(int i = pos; i > 0; i--){ //updates each position to contain the value of the next position
        a[i] = a[i - 1];
    }
    a[0] = temp; //updates final position with initial position
    return pos;
}

int countRuns(const string a[], int n){
    if(n < 0){ //negative n check
        return -1;
    }
    if(n == 0){ //empty string returns 0 runs
        return 0;
    }
    int runs = 1; //non-empty string must have at least one run
    for(int i = 0; i < n - 1; i++){ //checks for points where runs change and increments runs
        if(a[i] != a[i+1]){
            runs++;
        }
    }
    return runs;
}

int flip(string a[], int n){
    if(n < 0){ //negative n check
        return -1;
    }
    string temp;
    for(int i = 0; i < n/2; i++){ //breaks array into half and swaps outer most layer, 2nd outer most layer, etc. etc.
        temp = a[i];
        a[i] = a[n-1-i];
        a[n-1-i] = temp;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2){
    if(n1 < 0 || n2 < 0){ //negative n check
        return -1;
    }
    int target = n1;
    if(n2 <= n1){ //dictates which n value is shorter to avoid undefined behavior
        target = n2;
    }
    for(int i = 0; i < target; i++){ //locates where a1 differs from a2
        if(a1[i] != a2[i]){
            return i;
        }
    }
    return target; //if it doesn't differ return shorter n value
}

int subsequence(const string a1[], int n1, const string a2[], int n2){
    if(n1 < 0 || n2 < 0 || n2 > n1){
        return -1;
    }
    if(n2 == 0)
     return 0;
    bool match = false;
    for(int i = 0; i <= n1 - n2; i++){ //analyze every eligible position in a1 to see if it contains the sequence in order
        for(int j = 0; j < n2; j++){
            if(a1[i + j] != a2[j]){
                match = false; //if the sequence finds a non match, move on to next position
                break;
            }
            else
                match = true;
        }
        if(match == true) //if entire array is traversed and match is still true, return position where this occurred.
            return i;
    }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2){
    if(n1 < 0 || n2 < 0) //negative n check
        return -1;
    
    for(int i = 0; i < n1; i++){
        for(int j = 0; j < n2; j++){ //goes through each position in a2 and looks for match, if there is a match, return the position of a1 that contained match
            if(a1[i] == a2[j])
                return i;
        }
    }
    return -1;
}

int split(string a[], int n, string splitter){
    bool sorted = true;
    if(n < 0)
        return -1;
    int counter = 0;
    for(int i = 0; i < n; i++){
        sorted = true; //check whether the point prior to the current position is already sorted. If it is, this is important as not checking for this will lead to an infinite loop where I rotate right infinitely
        for(int j = 0; j < i; j ++){
            if(a[j] >= splitter)
                sorted = false;
        }
        if(a[i] > splitter){
            rotateLeft(a, n, i); //puts any string greater than splitter in the back of the array
            counter++;
            i--; //i decrement to avoid skipping values
        }
        else if(a[i] < splitter && !sorted){
            rotateRight(a, n, i); //puts any string less than splitter in the front of the array
            counter++;
            i--; //i decrement to avoid skipping values
        }
        if(counter > n + 1) //counter to avoid infinite loops when reaching end of array but ensuring that all values are checked
            break;
    }
    for(int i = 0; i < n; i++){ //locates first value greater than or equal to splitter and returns it
        if(a[i] >= splitter && a[i] != ""){
            return i;
        }
    }
    return n; //if no value meeting this defintion, return n
}

int main() {
    /**  string list[5] = {"dave", "joe", "banana", "hey", ""};
     // appendToAll(list, 5, "!!!!");
     // for(int i = 0; i < 5; i++){
     //    cout << list[i] << endl;
     //}
     
     //int n = lookup(list, 5, "banana");
     //cout << n << endl;
     
     string pm[6] = { "david", "liz", "margaret", "tony", "gordon", "boris" };
     int k = positionOfMax(pm, 6);   // returns 3, since  tony  is latest
     // in alphabetic order
     cout << k << endl;
     
     string mp[5] = { "john", "david", "liz", "theresa", "margaret" };
     int m = rotateRight(mp, 5, 2);  // returns 1
     
     for(int i = 0; i < 5; i++){
     cout << mp[i] << endl;
     }
     
     //string d[9] = {
     //    "tony", "boris", "rishi", "rishi", "gordon", "gordon", "gordon", "rishi", "rishi"
     //};
     //int p = countRuns(d, 9);  //  returns 5
     
     //cout << p << endl;
     
     string leader[6] = { "boris", "rishi", "", "tony", "theresa", "david" };
     int q = flip(leader, 4);  // returns 4
     for(int i = 0; i < 6; i++) {
     cout << leader[i] << endl;
     }
     
     //string names[10] = { "john", "margaret", "theresa", "rishi", "boris", "liz" };
     //string names1[10] = { "margaret", "theresa", "rishi" };
     //int t = subsequence(names, 6, names1, 3);  // returns 1
     //string names2[10] = { "john", "rishi" };
     //int u = subsequence(names, 5, names2, 2);  // returns -1
     //cout << "T: " << t << endl;
     
     string names[10] = { "john", "margaret", "theresa", "rishi", "boris", "liz" };
     string set1[10] = { "david", "boris", "rishi", "margaret" };
     int v = lookupAny(names, 6, set1, 4);  // returns 1 (a1 has "margaret" there)
     string set2[10] = { "tony", "gordon" };
     int w = lookupAny(names, 6, set2, 2);  // returns -1 (a1 has none)
     cout << v << endl << w << endl;
     
     string pm1[6] = { "david", "liz", "margaret", "tony", "gordon", "boris" };
     int x = split(pm1, 6, "john");  //  returns 3
     // pm must now be
     //      "david"  "gordon"  "boris"  "liz"  "tony"  "margaret"
     // or   "gordon"  "boris"  "david"  "margaret"  "liz"  "tony"
     // or one of several other orderings.
     // All elements < "john" (i.e., "gordon", "boris", and "david")
     //   come before all others
     // All elements > "john" (i.e., "tony", "liz", and "margaret")
     //   come after all others
     //string pm2[4] = { "margaret", "theresa", "liz", "rishi" };
     //int y = split(pm2, 4, "rishi");  //  returns 2
     // pm2 must now be either
     //      "margaret"  "liz"  "rishi"  "theresa"
     // or   "liz"  "margaret"  "rishi"  "theresa"
     // All elements < "rishi" (i.e., "liz" and "margaret") come
     // before all others.
     // All elements > "rishi" (i.e., "theresa") come after all others.
     
     for(int i = 0; i < 6; i++){
     cout << i << pm1[i] << endl;
     }
     **/
    
    string h[7] = { "rishi", "margaret", "gordon", "tony", "", "john", "liz" };
    assert(lookup(h, 7, "john") == 5); //checks normal lookup test
    assert(lookup(h, 7, "gordon") == 2);
    assert(lookup(h, 2, "gordon") == -1); //checks lookup when element not contained
    assert(lookup(h, -1, "margaret") == -1); //check lookup when n is negative
    assert(lookup(h, 7, "RISHI") == -1); //Checks lookup is case-sensitive
    
    string max1[6] = {"0", "1", "2", "3", "4", "5"};
    string max2[6] = {"0", "0", "0", "9", "9", "9"};
    string max3[0] = {};
    assert(positionOfMax(max1, 6) == 5); //Checks if function works with no special cases
    assert(positionOfMax(max2, 6) == 3); //Checks first instance of max is returned
    assert(positionOfMax(max3, 0) == -1); //Checks no interesting elements returns -1
    assert(positionOfMax(max2, -1) == -1); //Checks negative n returns -1
    
    string left1[4] = {"bill", "joey", "bob", "william"};
    string left2[4] = {"joey", "bob", "william", "bill"};
    string left3[4] = {"john", "paul", "ringo", "george"};
    string left4[4] = {"john", "paul", "ringo", "george"};
    assert(rotateLeft(left1, 4, 0) == 0); //Checks if function with no special cases returns properly
    assert (rotateLeft(left3, 4, 3) == 3); //Checks if function with pos at end of function returns properly
    for(int i = 0; i < 4; i++){
        assert(left1[i] == left2[i]); //Checks rotates left correctly with not special cases
        assert(left3[i] == left4[i]); //Ensures pos at end of string does not lead to undefined behavior
    }
    
    string runs[9] = {
        "tony", "boris", "rishi", "rishi", "gordon", "gordon", "gordon", "rishi", "rishi"
    };
    assert(countRuns(runs, 9) == 5); //Checks runs for whole array
    assert(countRuns(runs, 5) == 4);//Checks runs for part of an array
    assert(countRuns(runs, -1) == -1); //Checks negative n
    assert(countRuns(runs, 0) == 0); //Checks 0 elements checked
    
    string flipper[5] = {"harry", "ron", "hermione", "ginny", "snape"};
    string flipper2[5] = {"snape", "ginny", "hermione", "ron", "harry"};
    string flipper3[4] = {"gary", "george", "gus", "georgia"};
    string flipper4[4] = {"georgia", "gus", "george", "gary"};
    string flipper5[4] = {"john", "paul", "george", "ringo"};
    string flipper6[4] = {"george", "paul", "john", "ringo"};
    
    assert(flip(flipper, 5) == 5); //checks return works properly
    assert(flip(flipper3, 4) == 4);
    assert(flip(flipper5, 3) == 3);
    assert(flip(flipper, 0) == 0); //checks n = 0 has no effect
    assert(flip(flipper, -1) == -1); //checks negative n returns -1
    
    for(int i = 0; i < 5; i++){
        assert(flipper[i] == flipper2[i]); //checks odd n functions correctly
    }
    
    for(int i = 0; i < 4; i++){
        assert(flipper3[i] == flipper4[i]); //checks even n functions correctly
    }
    
    for(int i = 0; i < 4; i++){
        assert(flipper5[i] == flipper6[i]); //checks n less than full array functions correctly
    }
    
    
    string leader[6] = { "boris", "rishi", "", "tony", "theresa", "david" };
    string politician[5] = { "boris", "rishi", "david", "", "tony" };
    assert(differ(leader, 6, politician, 5) == 2) ; //  testing differ for full array
    assert(differ(leader, 2, politician, 1) == 1);  // testing differ for portion of array// n2 < n1
    assert(differ(leader, 1, politician, 2) == 1); //testing n1 < n2
    assert(differ(leader, 0, politician, 0) == 0); // testing differ when using 0's
    assert(differ(leader, -1, politician, 3) == -1); //testing negative n1
    assert(differ(leader, 3, politician, -4) == -1); //testing negative n2
    
    string names[10] = { "john", "margaret", "theresa", "rishi", "boris", "liz" };
    string names1[10] = { "margaret", "theresa", "rishi" };
    assert(subsequence(names, 6, names1, 3) == 1);  //Checks for when subsequence is present
    string names2[10] = { "john", "rishi" };
    assert(subsequence(names, 5, names2, 2) == -1); //Checks for when subsequence is not present
    assert(subsequence(names, 3, names1, 3) == -1); //Checks for when array's are shortened
    assert(subsequence(names, 3, names1, 2) == 1); //Checks for when array's are shortened and shroter sequence is present
    assert(subsequence(names, 2, names1, 4) == -1); //checks when n2 > n1 return -1
    assert(subsequence(names, -1, names1, 5) == -1); //checks when n1 is negative
    assert(subsequence(names, 4, names1, -5) == -1); //checks when n2 is negative
    assert(subsequence(names, 4, names1, 0) == 0); //checks when n2 is 0 (subsequence present)
    
    string names8[10] = { "john", "margaret", "theresa", "rishi", "boris", "liz" };
    string set1[10] = { "david", "boris", "rishi", "margaret" };
    assert(lookupAny(names8, 6, set1, 4) == 1);  // returns 1 (a1 has "margaret" there)
    assert(lookupAny(names8, 6, set1, -4) == -1);
    assert(lookupAny(names8, -4, set1, 4) == -1);
    string names9[10] = {"john", "margaret", "theresa", "rishi", "margaret", "liz"};
    assert(lookupAny(names9, 6, set1, 4) == 1);
    string set2[10] = { "tony", "gordon" };
    assert(lookupAny(names8, 6, set2, 2) == -1);  // returns -1 (a1 has none)
    
    string z[9] = {"0", "1", "2", "0", "1", "2", "0", "1", "2"};
    string z2[9] = {"0", "0", "0", "1", "1", "1", "2", "2", "2"};
    string z3[9] = {"2", "2", "2", "0","0", "0", "1", "1", "1"};
    string z4[9] = {"2", "0", "0", "0", "2", "2", "1", "1", "1"};
    string z5[6] = {"0", "2", "0", "2", "0", "2"};
    string z6[6] = {"0", "0", "0", "2", "2", "2"};
    string z7[9] = {"1", "2", "0", "2", "2", "1", "0", "0", "1"};
    string z8[9] = {"0", "1", "1", "2", "2", "2", "0", "0", "1"};
    string z9[9] = {"1", "1", "1", "2", "2", "2", "0", "0", "0"};
    string z10[9] = {"1", "1", "1", "0", "0", "0", "2", "2", "2"};
    assert(split(z, 9, "1") == 3); //testing out split with consecutive numbers
    assert(split(z3, 9, "1") == 3); //testing out split leading with >, then <, then =
    assert(split(z4, 9, "1") == 3); //testing out split when > is changed into a < in the same index
    assert(split(z5, 6, "1") == 3); //testing out split when no = involved
    assert(split(z6, 6, "1") == 3);//testing out split when no moves have to be made
    assert(split(z7, 6, "1") == 1); //testing out split when smaller portion is taken of larger array
    assert(split(z9, 9, "1") == 3); //testing out split starting with equals, then >, then <
    assert(split(z10, 9, "1") == 3); //testing out split starting with equals, then <, then >
    
    for(int i = 0; i < 9; i++){ //comparing sorted arrays to "keys"
        assert(z[i] == z2[i]);
        assert(z3[i] == z2[i]);
        assert(z4[i] == z2[i]);
        assert(z7[i] == z8[i]);
        assert(z9[i] == z2[i]);
        assert(z10[i] == z2[i]);
    }
    
    for(int i = 0; i < 6; i++){
       assert(z5[i] == z6[i]);
    }
       
    
    
    ///Using some of the tests provided in the spec because why not
    
    string g[4] = { "rishi", "margaret", "liz", "theresa" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "rishi?" && g[3] == "theresa?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "liz?" && g[3] == "margaret?");

    string e[4] = { "gordon", "tony", "", "john" };
    assert(subsequence(h, 7, e, 4) == 2);

    string d[5] = { "margaret", "margaret", "margaret", "tony", "tony" };
    assert(countRuns(d, 5) == 2);
       
    
    string f[3] = { "liz", "gordon", "tony" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "tony" && f[2] == "liz");
       
    
       
   
    
    string append1[4] = {"", "", "", ""};
    string append2[4] = {"!!!!", "!!!!", "!!!!", "!!!!"};
    assert(appendToAll(append1, 4, "!!!!") == 4);
    assert(appendToAll(append1, -1, "!!!!") == -1);
    for(int i = 0; i < 4; i++){
        assert(append1[i] == append2[i]);
    }
    
    cout << "All tests succeeded" << endl;
    
    
    
}
