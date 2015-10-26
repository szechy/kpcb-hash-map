#kpcb-hash-map
My response to the KPCB Engineering Fellows' application's challenge question: build a fixed-size hash map (see original problem in the last section below).

##Dependencies
* All dependencies (besides a `gcc` compiler - or modify the `Makefile` to use a different C compiler) are self-contained inside of this repository.

##Building:
* Use `make` to build a copy of `shell` and `test`.
* Use `make shell` to build a copy of `shell`.
* Use `make test` to build a copy of `test`, a binary that runs unit tests.

##Usage in other projects:
* To include `kpcb-hash-map` for use in a C project:
	* Copy `hash.h`, `hash.c`, `cfarmhash.h`, `cfarmhash.c` to new location
	* `#include 'hash.h'`

##Shell/Demo usage:
* `shell` is given as a fun command-line utility to play with `kpcb-hash-map`
* To use: Fire up `./shell -s x` with `x` as the desired hash-map size to open a shell to play with `kpcb-hash-map`
* Use `./shell -h` to view available commands, which alias to `get()`, `set()`, `delete()`, and `load()` 

##Test usage:
* Testing loosely uses the Michigan Hackers' unit test framework for pretty printing and keeping track of results.
	* This framework was likely overkill for this project, but hadn't used it before and wanted to give it a shot.
* Run `./test` to run and view unit tests results.

##Stretch goals (if project is revisited):
* Figure out some sort of profiling to perform performance testing (used gprof in EECS 281, should look into whether that's C-compatible and not just C++)
* Use profiling to determine efficiency of various collision resolution schemes and probing algorithms
* Automatically size-adjusting hash map (ideally along prime numbers, like the Java implemntation).

##Original KPCB application problem
(Copied from the [application](http://kpcbfellows.com/engineering/apply))

Using only primitive types, implement a fixed-size hash map that associates string keys with arbitrary data object references (you don't need to copy the object). Your data structure should be optimized for algorithmic runtime and memory usage. You should not import any external libraries, and may not use primitive hash map or dictionary types in languages like Python or Ruby.

The solution should be delivered in one class (or your language's equivalent) that provides the following functions:

**constructor(size):** return an instance of the class with pre-allocated space for the given number of objects.

**boolean set(key, value):** stores the given key/value pair in the hash map. Returns a boolean value indicating success / failure of the operation.

**get(key):** return the value associated with the given key, or null if no value is set.
delete(key): delete the value associated with the given key, returning the value on success or null if the key has no value.

**float load():** return a float value representing the load factor (\`(items in hash map)/(size of hash map)\`) of the data structure. Since the size of the dat structure is fixed, this should never be greater than 1.

If your language provides a built-in hashing function for strings (ex. `hashCode` in Java or `__hash__` in Python) you are welcome to use that. If not, you are welcome to do something naive, or use something you find online with proper attribution.

###Instructions
Please provide the source, tests, runnable command-line function and all the resources required to compile (if necessary) and run the following program. You are free to use any coding language that compiles/runs on *nix operating systems and requires no licensed software.
