An example to use four threads to divide the work. Here's the code:

```cpp
#include <iostream>
#include <chrono>
#include <random>
#include <array>
#include <thread>

int sum = 0; // Shared variable to store the total sum

void calculate_sum(int start, int end, const std::array<int, 1000000>& numbers) {
    for (int i = start; i < end; ++i) {
        sum += numbers[i];
    }
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

    // Create threads
    std::thread t1(calculate_sum, 0, chunk_size, numbers);
    std::thread t2(calculate_sum, chunk_size, chunk_size * 2, numbers);
    std::thread t3(calculate_sum, chunk_size * 2, chunk_size * 3, numbers);
    std::thread t4(calculate_sum, chunk_size * 3, numbers.size(), numbers);

    // Wait for all threads to finish
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    // Measure the end time
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}
```

**Explanation:**

1. **Shared Variable:** A global `sum` variable is declared to store the total sum, which will be accessed and modified by all threads.
2. **Thread Function:** The `calculate_sum` function takes the start and end indices of the array portion to be summed and the array itself as arguments. It iterates over the specified range and adds the values to the shared `sum` variable.
3. **Thread Creation:** Four threads are created, each responsible for calculating the sum of a quarter of the array. The `std::thread` constructor is used to create each thread, and the `calculate_sum` function is passed as the target function with appropriate arguments.
4. **Thread Joining:** After creating the threads, the `join()` method is called on each thread to wait for it to finish execution. This ensures that the main thread waits for all worker threads to complete before proceeding.
5. **Time Measurement:** The start and end times are measured using `std::chrono::high_resolution_clock`, and the duration is calculated in milliseconds.

By dividing the work among four threads, we can potentially improve the overall execution time, especially on multi-core systems. However, the actual performance improvement will depend on various factors, such as the number of cores, the overhead of thread creation and synchronization, and the specific workload.
