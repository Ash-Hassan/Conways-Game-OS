# HCI 104475: Conway Game of Life - An OS course project #
### PROJECT MEMBERS ###
StdID | Name
------------ | -------------
**64156** | **Hassan Zaheer** <!--this is the group leader in bold.-->
64160 | Shahmeer khan
<!-- Replace name and student ids with acutally group member names and ids-->
## Approach ##
### Approach 1: ###
I got the user input for num of threads that is divisible by 2 and max 10.
I implement the switch case for 2,4,6,8,10 threads.
the i started coding of case 2: but soon i ran into problem because i was making the two outer loops into two threads but because they were nested i wasn't able to give the value from one thread to another as i have very little knowledge of mutex and semaphore and pthread conditions.
So I thought of making a fixed 8 multithread program.

### Approach 2: ###
I started to make the isLiving function the thread function and i made a structure for passing multiple threads after that i converted the function into a thread but then the problem occurred as i wasn't able to return the False ot in[x][x] value from the threads...

## Problems Facing ##

### Problem 1: Couldnt able to convert loops to threads ###

### Problem 2: Couldnt able to return false or true from a thread function ###

### Problem 3: Time Constarint and lack of sources on internet ###

## References ##
- Basic code of game in single thread : Got it from Sir Faooq
- How to pass Multiple arguments in a thread function: https://cboard.cprogramming.com/c-programming/123969-help-pthread-multiple-arguments.html
- Many other website for sytax checking and eleminating errors.
