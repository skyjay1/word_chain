#include "redis/connection.h"
using chain_game::Connection;
#include "config.h"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <memory>
using std::make_unique;
#include <string>
using std::string;

#include <sw/redis++/redis++.h>
using sw::redis::Redis;
using sw::redis::ConnectionOptions;

Connection::Connection()
{
    try {
        // Set up the connection options
        ConnectionOptions connection_options;
        connection_options.host = "redis-12678.c251.east-us-mz.azure.redns.redis-cloud.com";
        connection_options.port = 12678;
        connection_options.password = REDIS_PASSWORD;
        //connection_options.socket_timeout = std::chrono::milliseconds(400);
        // Connect to Redis instance
        //this->redis = make_unique<Redis>(connection_options);
        this->redis = make_unique<Redis>("tcp://127.0.0.1:6379");
    } catch (const sw::redis::Error &e) {
        cerr << "Redis error: " << e.what() << endl;
    }
}

// TODO figure out if we need to close Redis
Connection::~Connection() = default;    

string Connection::ping()
{
    try {
        return redis->ping();
    } catch(const sw::redis::Error &e) {
        cerr << "Redis error: " << e.what() << endl;
    }
    return "ERR";
}