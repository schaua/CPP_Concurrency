# Walkthrough Thread Guard
Prior to C++20 it would be a good practice to surround any thread with RAII (Resource Allocation Is Instantiation) logic.  A guard that would make sure to join the thread as it went out of scope and was destroyed.  

1. Define a new thread_guard type that takes a thread reference as an argument.  Make the thread_guard type non-copyable.

```cpp
class thread_guard
{
    public:
    // Provide a constructor to capture the thread
    explicit thread_guard(std::thread&t_): guarded_thread(t_){}
    // Provide a destructor to join the thread if necessary
    ~thread_guard()
    {
        if (guarded_thread.joinable())
        {
            guarded_thread.join();
        }
    }
    // Remove copy behavior
    thread_guard(thread_guard const&) = delete;
    thread_guard& operator=(thread_guard const &) = delete;

    private:
    std::thread& guarded_thread;

};
```
2. Now main can be rewritten.
```cpp
int main(int argc, char const *argv[])
{
    std::cout << "Main process is starting..." << std::endl;
    
    // Create a new thread object
    std::thread worker_thread([]{    std::cout << "The thread is doing something." << std::endl;
    });
    thread_guard guard(worker_thread);
    
    // guard manages the join() call

    std::cout << "Main process is finished" << std::endl;
    return 0;
}
```
3. Point out that the output is different.  The thread output will not always come before the finished.  To force the behavior back to the original, put a block around the thread and thread_guard so that they will go out of scope at the end of the block and not the end of the main function.
```cpp
int main(int argc, char const *argv[])
{
    std::cout << "Main process is starting..." << std::endl;
    {   
        // Create a new thread object
        std::thread worker_thread([]{    std::cout << "The thread is doing something." << std::endl;
        });
        thread_guard guard(worker_thread);
        
        // guard manages the join() call
    }
    std::cout << "Main process is finished" << std::endl;
    return 0;
}
```