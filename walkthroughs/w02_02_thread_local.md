# Walkthrough Thread Local Storage

A bit of a hybrid around data for the thread is the idea of thread local storage.  This is a variable defined at the top level scope, but one that each thread will have its own memory allocated.

1.  Add thread_local to an integer variable, provide reference access to two different threads that increment it by some passed value.
```cpp
#include <iostream>
#include <thread>

thread_local int apparent_global_value{42};

int main(int argc, char const *argv[])
{
    int a{10};
    int b{12};
    std::cout << "Main process is starting..." << std::endl;
    std::cout << "apparent_global_value = " << apparent_global_value << std::endl;
    {   
        // Create a new thread object
        std::jthread worker_thread([&](const int increment){    
            std::cout << "The jthread is doing something." << std::endl;
            std::cout << "apparent_global_value = " << apparent_global_value << std::endl;
            apparent_global_value += increment;
            std::cout << "The jthread is done." << std::endl;
            std::cout << "apparent_global_value = " << apparent_global_value << std::endl;
        }, 20);
        
        std::jthread worker_thread2([&](const int increment){    
            std::cout << "The jthread is doing something." << std::endl;
            std::cout << "apparent_global_value = " << apparent_global_value << std::endl;
            apparent_global_value += increment;
            std::cout << "The jthread is done." << std::endl;
            std::cout << "apparent_global_value = " << apparent_global_value << std::endl;
        }, -20);
        // jthread manages the join() call
    }
    std::cout << "Main process is finished" << std::endl;
    std::cout << "apparent_global_value = " << apparent_global_value << std::endl;
    return 0;
}
```

In this example every thread has its own copy of the variable named apparent_global_variable.