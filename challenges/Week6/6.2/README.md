Did the program exit immediately when you hit ^C, or did it keep running to the end?
It exited immediately, because sleep is interrupted by SIGINT

What was the return value from sleep()?
The return value is the amount of time remaining on sleep() before it automatically returns (with 0 if it is left to run all the way through)