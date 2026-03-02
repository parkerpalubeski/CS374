# Description

This program effectively acts as the `ls -a1` command in bash. 
It takes an argument from the command line as an initial argument 
for the directory to be listed (or no argument, in which case it 
defaults to the current directory). For any given directory, the 
program will list the name of the directory, the name of all 
subdirectories, and the combined size of all files within those 
directories. The program has two important cases: when reading a 
file, in which case the program will simply add the program's 
file size to the total of the parent directory; and when 
searching a file, in which case the program will call itself 
through recursion using the subdirectory as an argument. It will 
perform this action for all levels of subdirectories, and return 
the size of all files and subdirectories to be added to the total 
of the parent directory. Other file types are ignored.

# Function Calls
* `int main()` : Executes the program, parses the command line and calls print_dir()
*   `print_dir()` : Function that recursively prints the directories