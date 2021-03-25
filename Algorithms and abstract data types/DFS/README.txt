README.txt
David Grim
dgrim


List.c: Same old List ADT we've been using the with all assignments. Same as in PA1 and PA4. 
This is the implementation file.

List.h: The header file for the List ADT. Nothing has changed since PA4

Graph.h: Graph ADT header file. pretty much copy and pasted from the assignment description page.
Declares each of the functions

Graph.c: Implementation file for the graph ADT. Very similar to PA4 except this time around we 
are utilizing DFS instead of BFS, thus a few data members needed to be changed to reflect this. 
along with a few new functions

GraphTest.c: a program that simply tests some of the Graph ADTs functions to ensure they work
before diving into the grading script.

FindComponents.c: The client code of the graph ADT. It uses DFS to find components of the graph.

Makefile: basic make file used to compile on the unix server. Copied and pasted from class webpage.

README.txt: the text file youre reading now. describes each of my files i submitted