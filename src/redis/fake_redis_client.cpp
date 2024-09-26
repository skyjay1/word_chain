#include "redis/redis_client.h"
using chain_game::RedisClient;
using chain_game::FakeRedisClient;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

namespace chain_game {

    FakeRedisClient::FakeRedisClient() : RedisClient() {}

    string FakeRedisClient::ping()
    {
        return "PONG";
    }

}
