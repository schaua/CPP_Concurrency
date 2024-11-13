To use `std::jthread` instead of `std::thread`, we'll need to make a few adjustments to the code. Here's the modified code:

```cpp
#include <iostream>
#include <chrono>
#include <random>
#include <array>
#include <thread>
#include <future>

int sum = 0; // Shared variable to store the total sum

void calculate_sum(int start, int end, const std::array<int, 1000000>& numbers, std::promise<int>& promise) {
    int local_sum = 0;
    for (int i = start; i < end; ++i) {
        local_sum += numbers[i];
    }
    promise.set_value(local_sum);
}

int main() {
    std::array<int, 1000000> numbers;

    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100);

    // Fill the array with random numbers
    for (int& num : numbers) {
        num = distrib(gen);
    }

    // Measure the start time
    auto start = std::chrono::high_resolution_clock::now();

    // Divide the work into 4 parts
    int chunk_size = numbers.size() / 4;

    // Create promises and futures
    std::promise<int> p1, p2, p3, p4;
    std::future<int> f1 = p1.get_future(), f2 = p2.get_future(), f3 = p3.get_future(), f4 = p4.get_future();

    // Create threads
    std::jthread t1(calculate_sum, 0, chunk_size, numbers, std::ref(p1));
    std::jthread t2(calculate_sum, chunk_size, chunk_size * 2, numbers, std::ref(p2));
    std::jthread t3(calculate_sum, chunk_size * 2, chunk_size * 3, numbers, std::ref(p3));
    std::jthread t4(calculate_sum, chunk_size * 3, numbers.size(), numbers, std::ref(p4));

    // Get the results from futures
    sum = f1.get() + f2.get() + f3.get() + f4.get();

    // Measure the end time
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}
```

**Key Changes:**

1. **Include `future` header:** This header provides the necessary classes for working with promises and futures.
2. **Promise and Future:** A `std::promise` object is created for each thread to send the calculated sum back to the main thread. A corresponding `std::future` object is created to receive the result.
3. **Thread Function:** The `calculate_sum` function now takes a `std::promise` object as an additional argument. It calculates the local sum and sets the value of the promise using `promise.set_value()`.
4. **Thread Creation:** `std::jthread` is used to create the threads, and the `std::ref()` function is used to pass the `std::promise` objects by reference.
5. **Getting Results:** The `get()` method is called on each `std::future` object to retrieve the calculated sum from the corresponding thread.

By using `std::jthread` and promises/futures, we achieve a more elegant and efficient solution. The main thread doesn't need to explicitly wait for each thread to finish using `join()`. Instead, it can directly retrieve the results from the futures as soon as they are available. This can lead to better performance and resource utilization in certain scenarios.
