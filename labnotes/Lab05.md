# Lab05
## Scenario
Introduce a **thread pool** to improve the design of this auction application significantly by managing threads more efficiently. Instead of creating a new thread for each bidding or auction task, use a thread pool to reuse a fixed set of threads. This approach reduces the overhead of creating and destroying threads repeatedly, making the application more scalable and efficient, especially under high load with multiple concurrent auctions and bids.

The addition of a thread pool improves the efficiency and scalability of the auction application by:
- Reducing thread management overhead.
- Preventing the application from creating an excessive number of threads.
- Simplifying task submission, as tasks are now managed by the thread pool rather than individual threads.


## Requirements
1. Improved Resource Management with a thread pool to control the maximum number of threads, which helps prevent system overload from creating too many threads.
2. Reduced Overhead by reusing threads in the pool reduces the cost of repeatedly creating and destroying threads, improving performance.
3. Make the application more scalable with thread pool to make it easier to handle a large number of auctions and bids, as it limits the number of active threads and queues tasks, allowing the system to respond well under heavy load.