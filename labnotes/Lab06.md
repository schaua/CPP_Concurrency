# Lab 06
## Scenario
It has been decided to add in a reporting feature to show the current status of the open auctions.  Add this using reader-writer locking logic so that reading the reports does not block the recoding of bidding action.

## Requirements
1. Add reader-writer locking to this design using `std::shared_mutex`, `std::unique_lock`, and `std::shared_lock` to improve the efficiency of concurrent reads and writes, especially for reporting the current status of active auctions. By allowing multiple threads to read data simultaneously (as long as no thread is writing), we can efficiently support a reporting feature that retrieves the current state of active auctions without blocking bidding or auction-ending updates.
