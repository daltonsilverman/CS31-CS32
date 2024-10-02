#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <fstream>
#include <string.h>
using namespace std;

MovieDatabase::MovieDatabase()
:directorMap(), genreMap(), actorMap(), idMap()
{}

bool MovieDatabase::load(const string& filename)
{
    fstream file;
        file.open(filename, fstream::out);
        if(file.fail())
            return false;
        while(!file.eof()){
            char input[256];
            if(!file.getline(input, 256))
                return false;
            string idNum(input);
            if(idNum == "")
                break;
            if(!file.getline(input, 256))
                return false;
            string name(input);
            if(!file.getline(input, 256))
                return false;
            string year(input);
            vector<std::string> directors;
            if(!file.getline(input, 256))
                return false;
            const char s[2] = ",";
            char *nameHolder;                    //Code excerpt from https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
               /* get the first token */
               nameHolder = strtok(input, s);
               /* walk through other tokens */
               while( nameHolder != NULL ) {
                   string nameTransfer(nameHolder); //these segments break up the entire line separated by commas into each respective name
                   for(int i = 0; i < nameTransfer.size(); i++)
                       tolower(nameTransfer[i]);
                   directors.push_back(nameTransfer);
                   nameHolder = strtok(NULL, s);
               }
            vector<std::string> actors;
            if(!file.getline(input, 256))
                return false;
               /* get the first token */
               nameHolder = strtok(input, s); //these segments break up the entire line separated by commas into each respective name
               /* walk through other tokens */
               while( nameHolder != NULL ) {
                   string nameTransfer(nameHolder);
                   for(int i = 0; i < nameTransfer.size(); i++)
                       tolower(nameTransfer[i]);
                   actors.push_back(nameTransfer);
                   nameHolder = strtok(NULL, s);
               }
            vector<std::string> genres;
            if(!file.getline(input, 256))
                return false;
            /* get the first token */
            nameHolder = strtok(input, s);
            /* walk through other tokens */ //these segments break up the entire line separated by commas into each respective name
            while( nameHolder != NULL ) {
                string nameTransfer(nameHolder);
                for(int i = 0; i < nameTransfer.size(); i++)
                    tolower(nameTransfer[i]);
                genres.push_back(nameTransfer);
                nameHolder = strtok(NULL, s);
            }
            file.getline(input, 256);
            int rating = stoi(input);
            for(int i = 0; i < idNum.size(); i++)
                tolower(idNum[i]);
            for(int i = 0; i < name.size(); i++) //Lowercasing all for data storage purposes
                tolower(name[i]);
            for(int i = 0; i < idNum.size(); i++)
                tolower(year[i]);
            Movie userInput(idNum, name, year, directors, actors, genres, rating);
            idMap.insert(idNum, userInput);
            for(std::vector<string>::iterator it = directors.begin(); it != directors.end(); it++)
                directorMap.insert(*it, userInput);
            for(std::vector<string>::iterator it = actors.begin(); it != actors.end(); it++)
                actorMap.insert(*it, userInput);
            for(std::vector<string>::iterator it = genres.begin(); it != genres.end(); it++)
                genreMap.insert(*it, userInput);
            if(file.eof())
                break;
            if(!file.getline(input, 256))
                return false;
        }
        file.close();
    return true;
    //return false;  // Replace this line with correct code.
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    for(int i = 0; i < id.size(); i++)
        tolower(id[i]); //lowercasing for case insensitivty
    Movie* returnValue;
    TreeMultimap<std::string, Movie>::Iterator it = idMap.find(id);
    returnValue = &(it.get_value());
    return returnValue;
}


vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    for(int i = 0; i < director.size(); i++)
        tolower(director[i]); //lowercasing for case insensitivty
    TreeMultimap<std::string, Movie>::Iterator it = directorMap.find(director);
    vector<Movie*> returnVector;
    while(it.is_valid()){
        returnVector.push_back(&(it.get_value()));
        it.advance();
    }
    return returnVector;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    for(int i = 0; i < actor.size(); i++)
        tolower(actor[i]); //lowercasing for case insenstivity
    TreeMultimap<std::string, Movie>::Iterator it = actorMap.find(actor);
    vector<Movie*> returnVector;
    while(it.is_valid()){
        returnVector.push_back(&(it.get_value()));
        it.advance();
    }
    return returnVector;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    for(int i = 0; i < genre.size(); i++)
        tolower(genre[i]); //lowercasing for case insensitivty
    TreeMultimap<std::string, Movie>::Iterator it = genreMap.find(genre);
    vector<Movie*> returnVector;
    while(it.is_valid()){
        returnVector.push_back(&(it.get_value()));
        it.advance();
    }
    return returnVector;
}



