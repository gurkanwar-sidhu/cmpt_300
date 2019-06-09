# Assignment 2: Shell with History - CMPT 300

In this project we develop a simple UNIX shell. The shell accepts user commands.


## Additional files
   * discussion.txt used to communicate tasks and workload


## Design Decisions & Project Issues:

### 3. Creating Child Process

#### Design Decisions:
1. Forking child
    * return child pid in order to correctly

2. Running execvp commands
    * run inside of child (check if in child if childpid == 0)
    * only wait for child if not in background

### 4. Internal Commands

#### Design Decisions:

1. Implement exit, pwd, cd
    * run all these commands if they occur before execvp



### 5. Creating a History Feature

#### Design Decisions:
1. Add command to history
    * modulus current history count by 10, in order to overwrite correct part of history array
    
2. retrieve command (copy into buffer, likely)
    * Retrieve Previous Command :
        - use the current history count and modulus by 10 to find the command before current in history array
    * Retrieve nth Command in !n :
        - use atoi to extract the number from the input
        -modulus that number to find it in the array
    
3. printing the last ten commands to the screen.
    * find starting point by using modular division on current history number.
    * print next 10 numbers. modulus by 10 every loop incase exceeds by 10.

### 5.2 Signals

#### Design Decisions:
1. Add command to history
    * modulus current history count by 10, in order to overwrite correct part of history array
    
2. retrieve command (copy into buffer, likely)
    * Retrieve Previous Command :
        - use the current history count and modulus by 10 to find the command before current in history array
    * Retrieve nth Command in !n :
        - use atoi to extract the number from the input
        -modulus that number to find it in the array
    
3. printing the last ten commands to the screen.
    * find starting point by using modular division on current history number.
    * print next 10 numbers. modulus by 10 every loop incase exceeds by 10.
    
 

#### Project Issues:
   * Not too many issues. Used stack overflow when confused about dynamic memory allocation and pointers.  
   * Occasionally confused by sample output files, but clarified on google groups.
   * unfamiliarity with forks and child processes led to reviewing notes and youtube videos
   * merge conflicts resolved with some hassle


