#include "player.h"

#include <string>
using std::string;

Player::Player(string name) : name(name), score(0){};

string Player::get_name() const {
    return name;
}

int Player::get_score() const {
    return score;
}

int Player::set_score(const int score_in) {
    this->score = score_in;
    return this->score;
}

int Player::add_score(const int score_in) {
    this->score += score_in;
    return this->score;
}

