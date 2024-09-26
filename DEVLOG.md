# Redis Project Development Log

## 12 Sep

- Used Phind to come up with some possible project ideas, settled on this one:

> Multiplayer Word Chain Game
>
> Build a word chain game where players take turns entering words that start with the last letter of the previous word. Use Redis to store the current word and player turn.
>
> Key features:
>
> - Use Redis SET commands to store valid words
> - Implement a round-robin system for determining whose turn it is
> - Add functionality to validate entered words against the set of valid words
> - Create a scoring system based on successful word chains and challenges overcome

- Additional features that will be needed:
  - lobby system to start a game and let the other player join with a code
  - import a dictionary of valid words into Redis

Optional features:
  - allow players to set a "category" when starting a game 
  - find pre-categorized word lists somewhere, or if not possible, allow players to "challenge" invalid words

## 13 Sep

- Set up development environment:
  - Install g++, Make, VS Code, 
  - Set up GitHub repo [https://github.com/skyjay1/word_chain](https://github.com/skyjay1/word_chain)
- Set up file structure and write main and player C++/header files
  - just enough to verify the Makefile process works

---

- Start writing Makefile
  - [GNU make docs](https://www.gnu.org/software/make/manual/make.html)
  - ~~WIP~~ `make all` detects .cpp and .h files, build
  - ~~WIP~~ `make run` build *and* execute
  - ~~WIP~~ `make clean` remove object files and empty folders in the build directory. It would be easiest to delete the build folder entirely but it seems safer to delete the object files one at a time.

---

- Set up Redis cloud database (free)
    - endpoint: `redis-12678.c251.east-us-mz.azure.redns.redis-cloud.com` 
    - port: `12678`
    - username: `default`
    - password: in `redis_password.txt`
- Set up Redis client
  - NO OFFICIAL REDIS CLIENT FOR C++ ([Redis docs](https://redis.io/docs/latest/develop/connect/clients/))
  - Phind recommends Redis++ ([Docs](https://github.com/sewenew/redis-plus-plus/blob/master/README.md)) which is a wrapper for Hiredis ([Docs](https://github.com/redis/hiredis/blob/master/README.md))

---

- **WIP** find a way to inject the password into the executable at compile time to avoid having it on the GitHub repo

## 16 Sep

- After some research into the compiling/linking process of header files, it turns out that injecting the password at compile time is far too late
  - Since the password is a macro it has to be modified at preprocessor stage, before compile stage
  - g++ has a flag for this: `-D[name]=[value]` ([Docs](https://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html))
- ~~WIP~~ figure out why it gives warning and doesn't replace the placeholder
  - Phind suggested wrapping the `#define` in `ifndef`
  - Success! g++ arg applies without warnings
    - Verified by outputting the preprocessed file only: `g++ -Wall -Wextra -std=c++20 -g -pthread -DREDIS_PASSWORD=\"abcdefg\" -I./include -I/usr/local/include/hiredis -I/usr/local/include/sw/redis++ -E src/redis/connection.cpp -o build/output.o`
- ~~WIP~~ figure out how to make the Makefile add the `\"` instead of directly replacing `REDIS_PASSWORD` with text
  - `addprefix` and `addsuffix` Makefile functions (doesn't look like a varargs string concat function exists)

---

- **WIP** Figure out why Redis constructor always gives error:
```sh
Redis error: unknown error code: failed to connect to Redis (redis-12678.c251.east-us-mz.azure.redns.redis-cloud.com:12678): q, err: 950608800, errno: 115
```
- Similar error when running local redis server:
```sh
Redis error: unknown error code: failed to connect to Redis (127.0.0.1:6379): ^, err: -893934688, errno: 115
```
- Verify remote redis server running:
```sh
redis-cli ping
```
- Verify local redis server running:
```sh
sudo service redis-server status
sudo lsof -i :6379
```
- **Note**: replace `status` with `start`, `stop`, or `restart` as needed

- Checked the logs:
```sh
sudo tail -f /var/log/redis/redis-server.log
```
which say "Ready to accept connections tcp"

- Checked the Redis++ [Issues](https://github.com/sewenew/redis-plus-plus/issues) page
  - Issue [216](https://github.com/sewenew/redis-plus-plus/issues/216) which links to Issue [183](https://github.com/sewenew/redis-plus-plus/issues/183) says something about TLS certificates, I can't tell if that applies here, especially since the "failed to connect" error happens for both local and remote servers
  - Issue [69](https://github.com/sewenew/redis-plus-plus/issues/69) mentions a 2020 update that allowed Redis++ to connect with username and password, which is what I'm trying to do. It mentions something about Redis ACL.