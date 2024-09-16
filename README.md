## Step 1: Install hiredis
You can download hiredis from its GitHub repository or use a package manager if available.

To download and compile hiredis manually:

```sh
git clone https://github.com/redis/hiredis.git
cd hiredis
mkdir build
cd build
cmake ..
make
sudo make install
```

## Step 2. Install Redis++
To download and compile hiredis manually:
```sh
git clone https://github.com/sewenew/redis-plus-plus.git
cd redis-plus-plus
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
```

## Step 2. Set the Library Path

You need to ensure that the runtime linker can find the hiredis library. This is done by setting the `LD_LIBRARY_PATH` environment variable. Add this line to your `~/.bashrc`:

```sh
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
```
Then reload the file:

```sh
source ~/.bashrc
```