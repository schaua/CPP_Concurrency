# Walkthrough Threading Example
The basic thread class in C++ is `std::thread` defined in the `<thread>` header file.  To define a thread, provide it with the code that it should execute and any, optional, arguments that that code required.

## One approach
The first approach is to define the code for the thread is a function.  
1. Define the function
```cpp
void thread_start_function()
{
    std::cout << "The thread is doing something." << std::endl;
}
```
This will require `#include <iostream>` to be added at the top of the file.  

2. In `main` create the thread as pass the function name as the argument for the constructor.
```cpp
int main(int argc, char const *argv[])
{
    std::cout << "Main process is starting..." << std::endl;
    
    // Create a new thread object
    std::thread worker_thread(thread_start_function);
    
    // It is important to join or detatch the worker_thread
    // before it is destroyed.
    worker_thread.join();
    
    std::cout << "Main process is finished" << std::endl;
    return 0;
}
```
This will required `#include <thread> to be added to the top of the file.

3. Demonstrate what happens if the thread is allowed to go out of scope without a join call.
```cmd
Main process is starting...
Main process is finished
terminate called without an active exception
```
## Lambda approach
Another approach is to define the thread logic using a lambda expression instead of a named function.
```cpp
int main(int argc, char const *argv[])
{
    std::cout << "Main process is starting..." << std::endl;
    
    // Create a new thread object
    std::thread worker_thread([]{    std::cout << "The thread is doing something." << std::endl;
    });
    
    // It is important to join or detatch the worker_thread
    // before it is destroyed.
    worker_thread.join();
    
    std::cout << "Main process is finished" << std::endl;
    return 0;
}
```