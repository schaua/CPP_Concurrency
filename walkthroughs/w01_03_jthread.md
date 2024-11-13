# Walkthrough jthread example
C++20 has added a new thread class that automatically provides the same guard behavior without having to write a thread_guard class.  `std::jthread`.

1. Modify main to use jthread.
```cpp
#include <iostream>
#include <thread>

int main(int argc, char const *argv[])
{
    std::cout << "Main process is starting..." << std::endl;
    {   
        // Create a new thread object
        std::jthread worker_thread([]{    std::cout << "The jthread is doing something." << std::endl;
        });
        
        // jthread manages the join() call
    }
    std::cout << "Main process is finished" << std::endl;
    return 0;
}
```
Point out how much simpler this is that needing the thread_guard.  As before if the block scope were not there then the thread would not go out of scope until the closing brace of main.