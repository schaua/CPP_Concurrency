# Walkthrough return data

We have seen how data can be 'returned' by providing the thread with a reference to a memory location that it can update.  For any practical use this is going to require some control of which thread and access the data at which time.

A related option would be to provide reference arguments to the thread.  This is not really that different than any other references.  There will still need to be some controls added.

In a future section the use of `std::promise` and `std::future` will be used to better coordinate data coming back from the thread.

The simplest object to control access to shared resources is `std::mutex`

1. Consider the following multi-threaded access to the balance on a bank account.  This artificially adds some sleep to cause the functions to take some time.  It also sleeps between a read and a write operations, which is a terrible idea but helps prove a point.

```cpp
#include <chrono>
#include <iostream>
#include <thread>

double balance{1000};

void deposit_thread(const double amount)
{
    double startingBalance = balance;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    startingBalance += amount;
    balance = startingBalance;
}

void withdraw_thread(const double amount)
{
    double startingBalance = balance;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    startingBalance -= amount;
    balance = startingBalance;
}

int main(int argc, char const *argv[])
{
    std::thread w01{withdraw_thread, 15};
    std::thread w02{withdraw_thread, 15};
    std::thread d01{deposit_thread, 15};
    std::thread d02{deposit_thread, 15};

    d01.join();
    d02.join();
    w01.join();
    w02.join();

    std::cout << "The final balance should be 1000 is " << balance << std::endl;
}
```
The output should not match the expected, at least some of the time.

2. A solution is to not allow access to balance without first obtaining a lock on an object.  In this case `std::mutex` type object.

```cpp
#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>

double balance{1000};
std::mutex balance_mut;

void deposit_thread(const double amount)
{
    balance_mut.lock();
    double startingBalance = balance;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    startingBalance += amount;
    balance = startingBalance;
    balance_mut.unlock();
}

void withdraw_thread(const double amount)
{
    balance_mut.lock();
    double startingBalance = balance;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    startingBalance -= amount;
    balance = startingBalance;
    balance_mut.unlock();
}

int main(int argc, char const *argv[])
{
    std::thread w01{withdraw_thread, 15};
    std::thread w02{withdraw_thread, 15};
    std::thread d01{deposit_thread, 15};
    std::thread d02{deposit_thread, 15};

    d01.join();
    d02.join();
    w01.join();
    w02.join();

    balance_mut.lock();
    std::cout << "The final balance should be 1000 is " << balance << std::endl;
    balance_mut.unlock();
}
```

Notice that it takes considerable more time to run this example code, due to the sleep for a total of at least six seconds.  But now the balance resource is protected.

Point out that this is only true if everyone plays by the rules.

3. A potential problem is forgetting to unlock the mutex.  A `std::lock_guard` can provide RAII support to automatically unlock a proved mutex when the guard goes out of scope.
```cpp
#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>

double balance{1000};
std::mutex balance_mut;

void deposit_thread(const double amount)
{
    std::lock_guard deposit_guard(balance_mut);
    double startingBalance = balance;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    startingBalance += amount;
    balance = startingBalance;
}

void withdraw_thread(const double amount)
{
    std::lock_guard withdraw_guard(balance_mut);
    double startingBalance = balance;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    startingBalance -= amount;
    balance = startingBalance;
}

int main(int argc, char const *argv[])
{
    std::thread w01{withdraw_thread, 15};
    std::thread w02{withdraw_thread, 15};
    std::thread d01{deposit_thread, 15};
    std::thread d02{deposit_thread, 15};

    d01.join();
    d02.join();
    w01.join();
    w02.join();

    balance_mut.lock();
    std::cout << "The final balance should be 1000 is " << balance << std::endl;
    balance_mut.unlock();
}

```