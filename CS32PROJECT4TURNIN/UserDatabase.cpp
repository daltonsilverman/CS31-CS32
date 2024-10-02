#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <fstream>
using namespace std;

UserDatabase::UserDatabase()
:m_database()
{
}

bool UserDatabase::load(const string& filename)
{   fstream file;
    file.open(filename, fstream::out);
    if(file.fail())
        return false;
    while(!file.eof()){
        char input[256];
        if(!file.getline(input, 256))
            return false;
        string name(input);
        if(name == "")
            break;
        if(!file.getline(input, 256))
            return false;
        string email(input);
        if(!file.getline(input, 256))
            return false;
        string numString(input);
        int num = stoi(numString);
        vector<std::string> container;
        for(int i = 0; i < num; i++){
            if(!file.getline(input, 256))
                return false;
            container.push_back(input);
        }
        User userInput(name, email, container);
        m_database.insert(email, userInput);
        if(file.eof())
            break;
        file.getline(input, 256);
    }
    file.close();
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    User* returnValue;
    TreeMultimap<std::string, User>::Iterator it = m_database.find(email);
    returnValue = &(it.get_value());
    return returnValue;
}

