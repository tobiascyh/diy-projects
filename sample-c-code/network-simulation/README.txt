****************************************************
Yee Hong Chu               0773285
CIS*3210                   Assignment #2
11/09/2013
****************************************************


************
Compilation
************

how to compile:
    make
      or
    make all
      or
    make simulator

how to run:
    make run

how to clean:
    make clean


**************
The Simulator
**************

Usage: <filename> n<2-7> or <filename> N<2-7>

Node2 to Node7 will be running at the background until they receive the stop
signal from Node1, which is the character 'q' or 'Q'. Node1 will prompt the
user to enter an existing filename where the message is stored followed by a
space and the destination node. The character 'n' and 'N' is the abbreviation
for node and Node1 can only send message to Node2 to Node7. So, the user needs
to enter a number in the range from 2 to 7. Upon successfully sending the
message, Node1 will prompt the user if the user wants to continue or quit. By
entering the character 'q' or 'Q', Node1 will broadcast the stop signal to all
the connected nodes.

There is the verbose option that allows user to see the sending and receiving
process of the packets between Node1 and the receiving node.

When a receiving node received the message, it will display the message on the
screen and reply the sender an acknowledgement. Acknowledgement received will
also be displayed on the screen by Node1.

Nodes that receive the stop signal will not display what it received, instead
it will send a message to its sender that it will now stop and end its
process. When all the other nodes have its processes terminated, Node1 will be
notified and only then Node1 will terminate.
