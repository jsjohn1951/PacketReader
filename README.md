## Packet Reader

![](https://i.pinimg.com/originals/a1/77/df/a177dfc84703c31afa0d501ccf43fe4f.gif)


Packet Reader is a c program designed to extract certain information from packets stored within a .pcap file. The information extracted include the following:

1. Transmission protocol (TCP, UDP) from the transport layer.
2. Internet Protocol addresses (ips of source and destination).
3. As well as ports and Mac addresses.

Packet Reader will also count the number of incoming and outgoing packets per connection, store the result within an unbalanced binary tree using a hash value as the key, and prints out the result to the stdout.

The information extracted is placed inside a queue by thread 1 and written to a file by thread 2.

### Queue

The queue was designed as a linked list with first in / first out in mind, as a result there are push front, pop back functions related.

### binary tree

The binary tree uses the hash value as the key to each node. The hash is generated using string hashing formula that can be found here: 
https://www.geeksforgeeks.org/string-hashing-using-polynomial-rolling-hash-function/


### requirements:
    ensure that libpcap library is install on your system, as well as cc 
    c-compiler and make for Makefiles

### Makefile rules:
	make - compiles the PackReader
	make all - compiles the PackReader
	make clean - removes object files and object directory
	make fclean - removes object files and executable
	make re - invokes rules fclean and all in that order

### Use:
	Execute as follows:
		./PackReader <.pcap file> <output file name>
	Packet Reader will append .output to <output file name>