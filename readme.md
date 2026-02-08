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



<img width="1455" height="1033" alt="Screenshot 2026-02-08 164455" src="https://github.com/user-attachments/assets/60502c3c-63d0-4e69-8228-b70e2febed1a" />





Stage 2: Single, producer - Single, consumer.
•	Added FreeRTOS tasks
•	A consumer task and a producer task.
•	Noted simultaneous behavior.




<img width="1461" height="1037" alt="Screenshot 2026-02-08 164431" src="https://github.com/user-attachments/assets/0b00345a-4ba9-4af7-a119-c907b4201d18" />




Stage 3: Mutex Protection
•	Added mutex in protection of the ring buffer.
•	Concurrent access resulted in removed race conditions.




<img width="1325" height="1069" alt="Screenshot 2026-02-08 164357" src="https://github.com/user-attachments/assets/468f5ad2-ccf0-450b-93e6-cfc0f7c42a01" />





Stage 4: Multi Producer - Multi Consumer (Final)
•	Added counting semaphores
•	Producer stops in case of a full buffer.
•	Consumer waits when buffer is empty.
•	Expanded to various manufacturers and customers.





<img width="1079" height="1014" alt="Screenshot 2026-02-08 164334" src="https://github.com/user-attachments/assets/6327dbae-55d3-4721-8be0-e2d2d098ecba" />





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


