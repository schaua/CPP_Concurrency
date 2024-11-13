# Walkthrough thread data
If a thread needs access to some data to complete its job, then there are several options available.  

1. Provide the data as thread function arguments and pass by value.
```cpp
#include <iostream>
#include <thread>

int main(int argc, char const *argv[])
{
    int a{10};
    int b{12};
    std::cout << "Main process is starting..." << std::endl;
    std::cout << "a = " << a << " b = " << b << std::endl;
    {   
        // Create a new thread object
        std::jthread worker_thread([](int x, int y){    
            std::cout << "The jthread is doing something." << std::endl;
            std::cout << "x = " << x << " y = " << y << std::endl;
            x += y;
            y = 42;
            std::cout << "The jthread is done." << std::endl;
            std::cout << "x = " << x << " y = " << y << std::endl;
        }, a, b);
        
        // jthread manages the join() call
    }
    std::cout << "Main process is finished" << std::endl;
    std::cout << "a = " << a << " b = " << b << std::endl;
    return 0;
}
```
2. Shared data is another option.  Pass the arguments as references.  This allows the thread to manipulate the original memory locations, and introduces plenty of problems that we'll look at later around protecting shared data.
```cpp
#include <iostream>
#include <thread>

int main(int argc, char const *argv[])
{
    int a{10};
    int b{12};
    std::cout << "Main process is starting..." << std::endl;
    std::cout << "a = " << a << " b = " << b << std::endl;
    {   
        // Create a new thread object
        std::jthread worker_thread([](int &x, int &y){    
            std::cout << "The jthread is doing something." << std::endl;
            std::cout << "x = " << x << " y = " << y << std::endl;
            x += y;
            y = 42;
            std::cout << "The jthread is done." << std::endl;
            std::cout << "x = " << x << " y = " << y << std::endl;
        }, std::ref(a), std::ref(b));
        
        // jthread manages the join() call
    }
    std::cout << "Main process is finished" << std::endl;
    std::cout << "a = " << a << " b = " << b << std::endl;
    return 0;
}
```
3. Another version of shared data is to pass `&` in the square brackets giving the thread reference access to any variables defined in the calling scope.
```cpp
#include <iostream>
#include <thread>

int main(int argc, char const *argv[])
{
    int a{10};
    int b{12};
    std::cout << "Main process is starting..." << std::endl;
    std::cout << "a = " << a << " b = " << b << std::endl;
    {   
        // Create a new thread object
        std::jthread worker_thread([&](){    
            std::cout << "The jthread is doing something." << std::endl;
            std::cout << "a = " << a << " a = " << a << std::endl;
            a += b;
            b = 42;
            std::cout << "The jthread is done." << std::endl;
            std::cout << "a = " << a << " a = " << a << std::endl;
        });
        
        // jthread manages the join() call
    }
    std::cout << "Main process is finished" << std::endl;
    std::cout << "a = " << a << " b = " << b << std::endl;
    return 0;
}
```
Point out the danger here in that multiple threads now have access to the same memory.