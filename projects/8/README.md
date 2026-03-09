# Project 8: Mutex reservation system



## Building

Command line:

* `make` will build all necessary object files and the executable, titled `reservations`
* `make clean` will remove the object files, executable, and any ppm files

## Files

* `reservations.c`: The main source code file for the executable
* `Makefile`: Contains informations for building the project

## Data

There are 5 global variables, including the array of int pointers
`seat_taken`, which stores the state of the seats as True (1) or
False (0). Additional global variables are `seat_count`, 
`broker_count`, `transaction_count` and `seat_taken_count`.

## Functions

* `main()`
  * `seat_broker` : Thread handler for brokers
    * `reserve_seat`: Change indicated slot in `seat_taken` to 1 if not already and increment `seat_taken_count`
    * `free_seat`: Change indicated slot in `seat_taken` to 0 if not already and decrement `seat_taken_count`
    * `verify_seat_count`: Verify that the number of `seat_taken` slots that are 1 is the same as `seat_taken_count`

## Notes

* Though not explicitly stated as necessary, some modification of verify_seat_count was required to ensure that the threads would not read `seat_taken_count` at the same time.