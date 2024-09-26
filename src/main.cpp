#include <iostream>
using std::cout;
using std::endl;

#include <memory>
using std::shared_ptr;
using std::make_shared;

#include "config.h"

#include "player.h"
#include <string>
using std::string;

#include "redis/redis_client.h"
using chain_game::RedisClient;
using chain_game::FakeRedisClient;
using chain_game::createLocalConnectionOptions;
using chain_game::createRemoteConnectionOptions;

int main()
{
    cout << "Hello out there" << endl;

    Player player1("Player 1");

    cout << player1.get_name() << " has score " << player1.get_score() << endl;

    shared_ptr<RedisClient> client = make_shared<FakeRedisClient>();
    string result;

    cout << "Constructed FakeRedisClient instance" << endl;
    cout << "ping:" << endl;
    result = client->ping();
    cout << result << endl;

    client.reset();
    client = make_shared<RedisClient>(createLocalConnectionOptions());
    cout << "Constructed local RedisClient instance" << endl;
    cout << "ping:" << endl;
    result = client->ping();
    cout << result << endl;
    
    client.reset();
    client = make_shared<RedisClient>(createRemoteConnectionOptions());
    cout << "Constructed remote RedisClient instance" << endl;
    cout << "ping:" << endl;
    result = client->ping();
    cout << result << endl;

    return 0;
}