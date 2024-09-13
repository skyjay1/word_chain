#include "redis/redisclient.h"
#include <hiredis/hiredis.h>
#include <iostream>

int ping() {
    // Create a Redis context
    redisContext *c = redisConnect("127.0.0.1", 6379);

    if (c == nullptr || c->err) {
        if (c) {
            std::cerr << "Error: " << c->errstr << std::endl;
            redisFree(c);
        } else {
            std::cerr << "Can't allocate redis context" << std::endl;
        }
        return 1;
    }

    // Send a command to Redis
    redisReply *reply = (redisReply *)redisCommand(c, "PING");

    // Check the reply
    if (reply == nullptr) {
        std::cerr << "Error sending command" << std::endl;
        redisFree(c);
        return 1;
    }

    std::cout << "Received: " << reply->str << std::endl;

    // Free the reply object
    freeReplyObject(reply);

    // Disconnect from Redis
    redisFree(c);

    return 0;
}