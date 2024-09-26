#pragma once

#include <string>
using std::string;
#include <sw/redis++/redis++.h>
using sw::redis::Redis;
using sw::redis::ConnectionOptions;
#include <optional>
using std::optional;

#include "config.h"

namespace chain_game {  

    class RedisClient {
        protected:
        optional<Redis> redis;
        RedisClient() = default;

        public:
        RedisClient(ConnectionOptions options);
        virtual ~RedisClient() = default;
        /**
         * Sends a ping
         * @return the result of redis->ping()
         **/
        virtual string ping();
    };

    class FakeRedisClient : public RedisClient {
        public:
        FakeRedisClient();
        virtual ~FakeRedisClient() = default;
        /**
         * Sends a ping
         * @return PONG
         **/
        string ping() override;
    };

    ConnectionOptions createLocalConnectionOptions();

    ConnectionOptions createRemoteConnectionOptions();
}