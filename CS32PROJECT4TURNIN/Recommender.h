#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>
#include <unordered_map>
#include "Movie.h"

class UserDatabase;
class MovieDatabase;

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id;
    int compatibility_score;
};


class Recommender
{
  public:
    Recommender(const UserDatabase& user_database,
                const MovieDatabase& movie_database);
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
                                               int movie_count) const;

  private:
    const UserDatabase* m_user_database;
    const MovieDatabase* m_movie_database;
    static bool compare(std::pair<Movie, int>& pair, std::pair<Movie, int>& pair2){
        if(pair.second == pair2.second)
            return pair.first < pair2.first;
        return pair.second < pair2.second;
    }
};

#endif // RECOMMENDER_INCLUDED
