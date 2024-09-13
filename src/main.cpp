#include <iostream>
using std::cout;
using std::endl;

#include "player.h"
#include <string>
using std::string;

#include "redis/redisclient.h"

int main()
{
    cout << "Hello out there" << endl;

    Player player1("Player 1");

    cout << player1.get_name() << " has score " << player1.get_score() << endl;

    ping();

    return 0;
}