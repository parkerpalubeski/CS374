Why have sleep() in the loop? Why not just continually check to see if the flag is set?

The sleep() is there so that the program is more CPU efficient. By having sleep() there, the program only checks once every 10 seconds, rather than thousands of times a second. Additionally, the sleep() is interruptable by signals, so it can still terminate the program instantly even though it only passively checks every 10 seconds if sigusr1_happened is still 0.

Research: what does the volatile keyword do? Speculate on why it is necessary to use with sig_atomic_t.

A volatile variable tells the compiler that a variable can be modified outside of the current instance of a program, which is very important for this program where it is changed by a signal interruption from another open instance of bash. It forces the compiler to read it from memory, and I would assume that means the compiler doesn't always precisely do that when it "reads" from a variable in a loop like this when the variable is not volatile.