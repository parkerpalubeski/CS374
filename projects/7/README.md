# Project 7: Multithread Image "Grayscaler"



## Building

Command line:

* `make` will build all necessary object files and the executable, titled `grayscaler`
* `make clean` will remove the object files, executable, and any ppm files

## Files

_[List files here, even if you only have one. Headers are optional.]_

* `grayscaler.c`: The main source code file for the executable
* `ppm.c`: Code specific to Conway's Life
* `ppm.h`: Definitions for global variables, structs and prototyping of functions in `ppm.h`
* `Makefile`: Contains informations for building the project

## Data

The main data structure is the struct `slice`, which contains information for
each individual thread of the program: a pointer to the .ppm file, the row of
pixels which that thread is meant to start at, the "height" of that thread's 
slice, and information related to the calculation of the average rgb values.

## Functions

_[This is a tree of functions and their short descriptions]_

* `main()`
  * `ppm_read` : Load a ppm file into a struct in memory
  * `thread` : Thread handler for each thread to modify its "slice" of the ppm
    * `ppm_get_pixel`: Return the rgb value of a pixel on the ppm as an array of integers
    * `ppm_set_pixel`: Modify a pixel on the ppm by passing in coordinates and a rgb value
  * `ppm_write` : Write from a ppm struct in memory into a file\

## Notes

* Make clean will remove ppm files too (both input and output). Remove the *.ppm in the clean command if that isn't desired