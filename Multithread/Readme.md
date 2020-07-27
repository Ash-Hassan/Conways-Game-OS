# HCI 104475: Conway Game of Life - An OS course project #
### PROJECT MEMBERS ###
StdID | Name
------------ | -------------
**64156** | **Hassan Zaheer** <!--this is the group leader in bold-->
64160 | Shahmeer khan
<!-- Replace name and student ids with acutally group member names and ids-->
## Approach ##
Converting from signle thread to multi thread was fairly easy.
Instead of calling loop in one thread i made multiple threads that was being created in a loop in main.
Time calculation is also done in main.
Rest is more or less same as single thread.

## Problems Faces ##

### Problem 1: I don't know how To create Threads in loop ###
Got the idea from Stackoverflow.

### Problem 2: Threadfunction was hard as it dosnt take multiple arguments ###
Made many variables gloabl so that they dosent required to be passed and passed the Needed one only.

### Problem 3: Time Constarint as i started the project a day before deadline ###
working late at night :)

## Time ##
- When 70 Threads Were Made: 0.015937 seconds
- When 50 Threads Were Made: 0.016937 seconds

## References ##
- Basic code of game: https://www.geeksforgeeks.org/program-for-conways-game-of-life/
- How to load 2d array from a file: https://www.reddit.com/r/C_Programming/comments/2nt9n4/reading_from_txt_file_into_2d_array_help_needed/
- Making multiple threads in a loop: Stackoverflow
- Many other website for sytax checking and eleminating errors.
