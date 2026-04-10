AVL Tree - Jason Holtman - February 26, 2026

------------------------------------------
Usage:
./main inputFile outputFile

Each line in the input file must adhere to this format:
"i" [data]
"r" [data] [data]

------------------------------------------
Description:
This program takes an input file and parses insert queries ("i")
as well as range queries ("r"). Insert queries are followed by
data that will be inserted into an AVL Tree. Range queries are followed
by two values which will be used to give a return value. These queries will
parse through the AVL Tree and output the number of values in range
of the two values into the output file. 

------------------------------------------
Sources:
All code is written by myself.

Much of the time invested went into understanding the recursive journey
of insertion and balancing. Testing came from tracing insertions and traversals 
by hand using drawn tree visualizations and verifying with known outcomes.
