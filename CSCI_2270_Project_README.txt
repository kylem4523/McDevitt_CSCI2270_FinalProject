//Kyle McDevitt
//EDIT: 7/28/2017

For my data structures project, I will be implementing a friends you may know
recommender similar to the one that companies like Facebook use.  I will use an
undirected graph in order to represent connections, or friendships between people
where certain factors will affect what I call the suggested friend score.
Each person represents a vertex in the graph where each vertex will be a
a person struct that contains a linked list of all the most visited locations.
The suggested friend score will be  updated depending on the number of mutual
friends a person has along with how often different people visit similar
locations.  Some of the methods to be included within the classes used will
add or remove friends, find people with the highest number of mutual friends,
and update or remove locations from the most visited.  The main menu is where the 
user will be able to build the social network, add or remove friendships, find mutual friends
between people within the graph, and manipulate location information for any person in the 
graph.
