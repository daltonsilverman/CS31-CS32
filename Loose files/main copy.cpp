  #include <iostream>
using namespace std;

int main()
{
    const char* str = "C+ B+ B- A C A- B C- B+ D B";
    int count = 0;
    const char* p;
    for (p = str; *p != '\0'  &&  count < 6; p++)
        if (*p == ' ')
            count++;
    for ( ; *p != '\0'  &&  *p != ' '; p++)
        cout << *p;
    cout << '\n';
}

class A {
public:
    A(int sz) {
        b = new b();
        
    }
    
    A(const A& other) {
        
    }
    
    A& operator= (const A& other) {
        
    }
    
    ~A() {
        
    }
private:
    B* b;
     //One dynamically allocated B obkect; Assume b
    // default constructor, a copy constructor, and
    //assignment operator
    int* arr;
     //size of arr (determined by a constructor
    int n;
    string str;
    
};

