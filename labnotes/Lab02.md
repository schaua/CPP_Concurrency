# Lab 02
## Scenario
Consider the need to keep the main thread free to handle user interface and other application issues.  Divide up the summation work between two worker threads.  Each can be given half of the large array to work on, and should update a shared total variable when done.  Be sure to synchronize access to the total so that a lock is obtained before incrementing the value.
## Requirements
1. Write the solution using std::mutex and manage the shared data during the thread work.
2. Re-write the solution using std::lock_guard to ensure the release of the resource no matter what for each thread.