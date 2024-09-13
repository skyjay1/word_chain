#pragma once

#include <string>
using std::string;
#include <memory>
using std::unique_ptr;
#include <sw/redis++/redis++.h>
using sw::redis::Redis;

namespace chain_game {    
    class Connection {
        private:
        unique_ptr<Redis> redis;

        public:
        Connection();
        ~Connection();
        /** Redis is not copyable **/
        Connection(const Connection &) = delete;
        /** Redis is not copyable **/
        Connection& operator=(const Connection &) = delete;
        /** Redis is movable **/
        Connection(Connection &&) = default;
        /** Redis is movable **/
        Connection& operator=(Connection &&) = default;
        /**
         * Sends a ping
         * @return the result of the ping
         **/
        string ping();
    };
}