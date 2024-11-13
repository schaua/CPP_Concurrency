**Here's a C++ code snippet that calculates the sum of 1 million random numbers and measures the execution time:**

```cpp
#include <iostream>
#include <chrono>
#include <random>
#include <array>

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

    // Calculate the sum
    int sum = 0;
    for (int num : numbers) {
        sum += num;
    }

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

1. **Include necessary headers:**
   - `iostream`: For input/output operations.
   - `chrono`: For measuring time.
   - `random`: For generating random numbers.
   - `array`: For creating a fixed-size array.

2. **Declare an array:**
   - `std::array<int, 1000000> numbers;` declares an array of 1 million integers.

3. **Seed the random number generator:**
   - `std::random_device rd;` creates a random device to seed the generator.
   - `std::mt19937 gen(rd());` creates a Mersenne Twister engine seeded with `rd()`.
   - `std::uniform_int_distribution<> distrib(1, 100);` creates a distribution to generate random numbers between 1 and 100.

4. **Fill the array with random numbers:**
   - A `for` loop iterates over each element of the array and assigns a random number using `distrib(gen)`.

5. **Measure the start time:**
   - `auto start = std::chrono::high_resolution_clock::now();` records the current time.

6. **Calculate the sum:**
   - A simple `for` loop iterates over the array and adds each element to the `sum` variable.

7. **Measure the end time:**
   - `auto end = std::chrono::high_resolution_clock::now();` records the current time after the calculation.

8. **Calculate the duration:**
   - `auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);` calculates the difference between the start and end times in milliseconds.

9. **Print the results:**
   - `std::cout` is used to print the calculated sum and the execution time.

**Note:**

- The actual execution time will vary depending on your system's hardware and software.
- You can optimize the code further by using more efficient algorithms or hardware acceleration techniques for large datasets.
- Consider using parallel programming techniques like OpenMP or C++17's parallel algorithms for significant performance improvements, especially for very large arrays.

By following these steps and incorporating the time measurement, you can efficiently calculate the sum of a large number of random integers and analyze the performance of your code.
