Requirements:

0. Read lines of user input, parse and execute commands by forking/creating new
processes.
1. Shell shall call `fork()` followed by `execvp()`.
2. Shell shall wait for child process to complete, then print child PID and the
   return result from the child process.
3. Shall specify command to execute by giving a path to executable file OR by
   using path expansion to locate the file (search each dir in the PATH env
   variable).  (`execvp()` function performs this automatically?).
4. Before shell forks to call `execvp()`, it shall parse the input string and
   separate it into a collection of substrings (executable file and command-line
   args).
5. Shell shall handle at least **4** command-line arguments (5+ args including
   executable file).
6. Shell shall store pointers to the substrings of the `arg` array which shall
   be passed to `execvp()`. (argument count is variable, hence a NULL pointer
   shall be placed in the array after the last substring. e.g. array must hold N
   \+ 1 pointers with last being NULL).
7. The **exit** command shall terminate the shell.
8. When starting the shell, the executable shall accept a command line argument
   that customizes the command line prompt.

Error handling:
1. If error is encountered while reading a line of input, the shell shall report
   the error and exit.
2. If EOF is encountered while reading a line of input, the shell shall exit
   gracefully without reporting an error.
3. Empty lines shall report an error and fetch a new line of input.

Limits:
1. Buffer size = 123 bytes: No error shall be reported; truncated input to be
   used if buffer is overrun.i

Submission:
1. Push source code files, Makefile, and PDF writeup to GitHub
2. PDF writeup shall be submitted on Canvas.
3. My shell shall match the output of main command-line interpreter.

Filenames:
Kim_Mark_HW3_main.c
Kim_Mark_HW3_writeup.pdf
Makefile


Execution Sample:
```
 student@student-VirtualBox:~/CSC415/assignment3$ ./assn3 prompt$
prompt$ ls -l
total 20
-rwxr-xr-x 1 student student 13216 Feb 23 13:44 assn3
-rw-r--r-- 1 student student  1583 Feb 23 13:44 assn3.c
Child 2124, exited with 0
prompt$ ls foo
ls: cannot access 'foo': No such file or directory
Child 2125, exited with 2
prompt$ exit
student@student-VirtualBox:~/CSC415/assignment3$
```
