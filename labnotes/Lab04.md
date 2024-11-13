# Lab 04
## Scenario
**Real-Time Online Auction System**
Add support for `std::future` and `std::promise` for handling asynchronous tasks such as updating the highest bid and sending bid confirmations.

## Requirements
1. Modify the `Auction` class to use `std::promise` to set the result when a new highest bid is placed.  
2. Use `std::future` to retrieve the bid updates and confirmations asynchronously.  
3. See bid confirmations and notifications asynchronously for each bidder, providing a realistic simulation of bid placement and result retrieval.  