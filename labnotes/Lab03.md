# Lab 03
## Scenario
**Real-Time Online Auction System**

This application simulates an online auction platform, where users can place bids on items in real-time. Auctions have time limits, and bids need to be processed, displayed, and updated live for all users participating in each auction.

Auctions are fast-paced and highly interactive.  It is import to handle concurrency as the system must handle multiple bids arriving at the same time.

## Requirements
1. Use threads to manage multiple auctions running concurrently. Each auction can be handled by a separate thread to simulate real-world concurrent bidding.  
2. Synchronize with `std::mutex` and `std::lock_guard`to protect the shared bid data for each auction to ensure consistency when multiple users place bids simultaneously.  
3. Use condition variables to manage the auction end times, notifying threads when an auction is complete.