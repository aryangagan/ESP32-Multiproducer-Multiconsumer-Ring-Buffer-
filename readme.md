ESP32 Multi Producer – Multi Consumer Ring Buffer (FreeRTOS)

About the Project
The project involves the application of a ring buffer on ESP32 and the application of the implementation to the producer-consumer issue with the help of FreeRTOS.

The overall aim was to learn how multiple tasks may safely communicate data in an embedded system without corrupting data, race or waiting around.

This project was rolled out progressively and tested with a real ESP board of ESP-IDF.

Why I Did This Project
During my work on FreeRTOS, I realized that there were numerous examples that refer to the FreeRTOS queues explicitly with no descriptions of the processes that occur internally.  
Therefore, I chose to put my own FIFO ring buffer and then combine it with RTOS concepts such as:
•	tasks
•	mutex
•	semaphores
•	blocking synchronization

This got me familiarized with the actual workings of RTOS in actual firmware.

Problem Statement
In embedded systems a single task can generate data (sensor, communication, etc.).
that data may be consumed by another task.
There is a tendency that producers and consumers do not run in the same speed.

In case shared memory is accessed unprotected:
race conditions occur
data can be erased or lost.

The difficulty was to come up with a system in which:
more than one producer and consumer can be run simultaneously.
data order is preserved (FIFO)
tasks are blocked in a good way and not wasted on the CPU.

Solution Overview
The solution consists of:
•	a predetermined size ring buffer
•	Producers and consumer tasks in FreeRTOS.
•	a mutual exclusion to share information.
•	using semaphores to implement buffer full/empty conditions.
This enables safe multi-producer, multi consumer communication.

Implementation Stages
I completed this project in four phases:

Stage 1: Single-Context Ring Buffer.
•	Applied a head, tail and count based using FIFO ring buffer.
•	No RTOS involved
•	Verified push and pop logic

Stage 2: Single, producer - Single, consumer.
•	Added FreeRTOS tasks
•	A consumer task and a producer task.
•	Noted simultaneous behavior.

Stage 3: Mutex Protection
•	Added mutex in protection of the ring buffer.
•	Concurrent access resulted in removed race conditions.

Stage 4: Multi Producer - Multi Consumer (Final)
•	Added counting semaphores
•	Producer stops in case of a full buffer.
•	Consumer waits when buffer is empty.
•	Expanded to various manufacturers and customers.

How the System Works
•	Manufacturers do not put products into the store until there is no space.
•	Before the access to the buffer, Mutex is acquired.
•	Writing of data is made to the ring buffer.
•	Consumers are waiting till the information appears.
•	FIFO order is preserved
•	Tasks are blocking rather than polling.

Technologies Used
•	ESP32
•	ESP-IDF
•	FreeRTOS
•	Embedded C

Project Structure
