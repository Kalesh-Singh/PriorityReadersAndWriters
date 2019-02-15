# Priority Readers and Writers #

A multi-threaded C++ program that gives readers priority over writers concerning a shared (global) variable. 

## Specifications ##
+ Multiple readers/writers are supported (5 of each)
+ Readers read the shared variable X number of times
+ Writers write the shared variable X number of times
+ *If any readers are waiting, then they have priority over writer threads -- writers can only write when there are no readers.*
+ Before a reader/writer attempts to access the shared variable it should wait some random amount of time
+ *Note:* This will help ensure that reads and writes do not occur all at once
+ pthreads, mutexes, and condition variables are used to synchronize access to the shared variable

### Readers ###
Readers print:
+ The value read
+ The number of readers present when value is read

### Writers ##
Writers print:
+ The written value
+ The number of readers present were when value is written (should be 0)

## Compiling the Program ##
The program can be complied by running the `make` command.
