# SearchPath

This is example of a complex project where I make use of the folowing concepts:
  - Object Oriented Programming (defining classes, contructors, methods, atributes). The files are separate by headers and source. 
  - TAD (queue, vector, map, stack, others)
  - Sort and search algorithms 
  - Algorithm to find shortest path in a weighted graph (dijkstra and bfs)
  - Use of File I/O

Description of some files in the project:
 - Nos.h file repersent a node in a graph with its respective informations.
 - Arcos.h file have informations about the edge in the graph and its possible information (head, tail, cost, distance, time),
 - Network.h file have constructor to read a graph from a file, map the information, and construct the different dataset for node and edge of the graph, and at the end translate the information back to its original in the input file.
 - grafo.cpp file is where the main program exists. Start creating the network, reading from a file, ask for start and end of a path (the example values 1..17), and criteria of search (cost, time, distance). Test if the graph is connex, otherwise could not exist path between two elementes in a disconex graph. Then build the network and using dijkstra determine the shortest path according to the criteria of search. Finally get the optimal path and show it on screen with apropriate information.
