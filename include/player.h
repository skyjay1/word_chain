#pragma once

#include <string>
using std::string;

class Player {
    private:
        const string name;
        int score;
    public:
        Player(string name);
        string get_name() const;
        int get_score() const;
        int set_score(const int score_in);
        int add_score(const int score_in);
};