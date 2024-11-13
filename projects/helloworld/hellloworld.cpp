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

