# ESP32 Multi Producer – Multi Consumer Ring Buffer (FreeRTOS)

## About this project
This project is about implementing a ring buffer on ESP32 and using it to solve the producer–consumer problem using FreeRTOS.

The main intention of doing this project was to understand how tasks in an RTOS environment can safely share data without race conditions, data corruption, or unnecessary CPU usage.

The project was implemented step by step and tested on a real ESP32 board using ESP-IDF.

---

## Why I chose this project
While learning FreeRTOS, I noticed that most examples directly use FreeRTOS queues.  
Although queues are useful, they hide a lot of internal working.

So I wanted to:
- understand how FIFO buffers work internally
- see how mutexes and semaphores are actually used
- handle producer–consumer synchronization manually
- gain confidence in writing concurrent embedded code

This project helped me understand how real firmware handles shared data.

---

## Problem statement
In embedded systems:
- one or more tasks may produce data
- one or more tasks may consume data
- producers and consumers often run at different speeds

If shared memory is accessed without protection:
- race conditions can occur
- data may be overwritten
- system behaviour becomes unpredictable

The problem was to design a system where:
- multiple producers and consumers can run together
- data order is preserved (FIFO)
- tasks block properly instead of busy waiting
- no data corruption occurs

---

## Solution overview
The solution consists of:
- a fixed-size ring buffer (FIFO)
- FreeRTOS producer and consumer tasks
- a mutex to protect shared buffer access
- counting semaphores to handle buffer full and empty conditions

This allows safe multi-producer multi-consumer communication.

---

## Implementation approach (how I built it)
I implemented the project in stages so that each concept was clear.

Stage 1:
- Implemented ring buffer logic using head, tail and count
- Tested push and pop operations without RTOS
  
<img width="1455" height="1033" alt="Screenshot 2026-02-08 164455" src="https://github.com/user-attachments/assets/c01d3e70-8770-4fad-abed-a35ff840b721" />

---
Stage 2:
- Added FreeRTOS
- Created one producer task and one consumer task
- Observed basic concurrent behaviour

<img width="1461" height="1037" alt="Screenshot 2026-02-08 164431" src="https://github.com/user-attachments/assets/3e2a32f6-d797-4d55-8ccb-185db9a2fea1" />

---


Stage 3:
- Added a mutex to protect the ring buffer
- Fixed race conditions caused by simultaneous access

  <img width="1325" height="1069" alt="Screenshot 2026-02-08 164357" src="https://github.com/user-attachments/assets/db15ad49-f878-4d6f-80ab-2fffb916433f" />

---

Stage 4 (final stage):
- Added counting semaphores
- Producer blocks when buffer is full
- Consumer blocks when buffer is empty
- Extended design to multiple producers and consumers

  
 <img width="1079" height="1014" alt="Screenshot 2026-02-08 164334" src="https://github.com/user-attachments/assets/968fb884-2c81-4929-aff7-781d1fbed42f" />

---

## How the system works
- Producer waits until there is space in the buffer
- Producer takes mutex and writes data
- Producer releases mutex and signals consumer
- Consumer waits until data is available
- Consumer takes mutex and reads data
- FIFO order is maintained
- Tasks block efficiently instead of polling

---

## Technologies used
- ESP32
- ESP-IDF
- FreeRTOS
- Embedded C

---

## Source files
The project contains:
- application logic with producer and consumer tasks
- ring buffer implementation
- ring buffer header definitions
- CMake configuration files

---

## How to build and run
Steps followed:
- Install ESP-IDF
- Connect ESP32 board
- Build the project using idf.py
- Flash the firmware
- Monitor serial output

Commands used:
- idf.py build
- idf.py flash
- idf.py monitor

---

## Sample output
Typical output looks like this:
Producer 1 pushed data  
Producer 2 pushed data  
Consumer 1 received data  
Consumer 2 received data  

This confirms:
- FIFO behaviour
- correct synchronization
- safe concurrent access

---

## What I learned from this project
- How ring buffers work internally
- Difference between mutex and semaphore
- How blocking works in FreeRTOS
- How RTOS scheduler interacts with synchronization
- Writing safe concurrent embedded firmware

---

## Possible improvements
- ISR to task communication
- Performance comparison with FreeRTOS queues
- Support for variable-sized data

---

## Author
Aryan Gagan  
Embedded systems | ESP32 | FreeRTOS
