#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    m_user_database = &user_database;
    m_movie_database = &movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    std::vector<MovieAndRank> returnVector;
    std::unordered_map<Movie, int> scoreContainer;
    User* username = m_user_database->get_user_from_email(user_email); //Get user from email
    vector<string> watch_history = username->get_watch_history(); //Get watch history from user
    for(vector<string>::iterator it = watch_history.begin(); it != watch_history.end(); it++){ //For each movie the user has watched
        Movie* movieHolder = m_movie_database->get_movie_from_id(*it);
        vector<string> directors = movieHolder->get_directors();
        for(vector<string>::iterator it2 = directors.begin(); it2 != directors.end(); it++){ //for each director
            vector<Movie*> directorOverlap = m_movie_database->get_movies_with_director(*it2);
            for(vector<Movie*>::iterator it3 = directorOverlap.begin(); it3 != directorOverlap.end(); it++){
                std::pair<unordered_map<Movie, int>::iterator, bool> map_it = scoreContainer.insert_or_assign(*(*it3), 0); //store movies with same director in structure and update compatibility
                (map_it.first)->second += 20;
            }
                
        }
        vector<string> actors = movieHolder->get_actors();
        for(vector<string>::iterator it2 = actors.begin(); it2 != actors.end(); it2++){ //for each actor
            vector<Movie*> actorOverlap = m_movie_database->get_movies_with_director(*it);
            for(vector<Movie*>::iterator it3 = actorOverlap.begin(); it3 != actorOverlap.end(); it3++){
                std::pair<unordered_map<Movie, int>::iterator, bool> map_it = scoreContainer.insert_or_assign(*(*it3), 0); //store movies with same actor in structure and update compatibility
                (map_it.first)->second += 30;
            }
        }
        vector<string> genres = movieHolder->get_genres();
        for(vector<string>::iterator it2 = genres.begin(); it2 != genres.end(); it2++){
            vector<Movie*> genreOverlap = m_movie_database->get_movies_with_director(*it);
            for(vector<Movie*>::iterator it3 = genreOverlap.begin(); it3 != genreOverlap.end(); it3++){
                std::pair<unordered_map<Movie, int>::iterator, bool> map_it = scoreContainer.insert_or_assign(*(*it3), 0); //store movies with same genre in structure and update compatibility
                (map_it.first)->second ++;
            }
        }
    }
    std::vector<std::pair<Movie, int>> convertVector(scoreContainer.begin(), scoreContainer.end());
    sort(convertVector.begin(), convertVector.end(), compare); //convert map to vector and sort
    for(int i = 0; i < movie_count; i++){
        if(convertVector[i].second > 0)
            MovieAndRank transfer(convertVector[i].first.get_id(), convertVector[i].second); //place and convert into final vector
    }
        return returnVector;  // Replace this line with correct code.
}

