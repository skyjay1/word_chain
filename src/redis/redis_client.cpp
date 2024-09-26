#include "redis/redis_client.h"
using chain_game::RedisClient;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

namespace chain_game {
        
    RedisClient::RedisClient(ConnectionOptions options) : redis(optional(Redis(options))) { }

    string RedisClient::ping()
    {
        try {
            if(redis->)
            return redis->ping();
        } catch(const sw::redis::Error &e) {
            cerr << "Redis error: " << e.what() << endl;
        }
        return "ERR";
    }

    ConnectionOptions createLocalConnectionOptions() {
        ConnectionOptions options;
        options.host = "127.0.0.1";
        options.port = 6379;
        options.type = sw::redis::ConnectionType::TCP;
        return options;
    }

    ConnectionOptions createRemoteConnectionOptions() {
        ConnectionOptions options;
        options.host = "redis-12678.c251.east-us-mz.azure.redns.redis-cloud.com";
        options.port = 12678;
        options.password = REDIS_PASSWORD;
        options.type = sw::redis::ConnectionType::UNIX;
        return options;
    }
}




ConnectionOptions createLocalConnectionOptions() {
    ConnectionOptions options;
    options.host = "127.0.0.1";
    options.port = 6379;
    options.type = sw::redis::ConnectionType::TCP;
    return options;
}

ConnectionOptions createRemoteConnectionOptions() {
    ConnectionOptions options;
    options.host = "redis-12678.c251.east-us-mz.azure.redns.redis-cloud.com";
    options.port = 12678;
    options.password = REDIS_PASSWORD;
    return options;
}