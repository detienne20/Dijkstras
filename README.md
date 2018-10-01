# Dijkstras
                             Dania Etienne COP3530 Implement Dijkstras Algorithm 08/06/2018

For this project, I decided to implement the graph using an adjacency list. Considering that an adjacency list is the most common way to represent a graph in the industry I decided it was best to get some practice with it.

For this implementation, there are eight available operations. The first one insertVertex() just involves creating a node and pushing it into the vector. Hence it’s computational complexity of O (1). Checking if the node is a vertex in the method isVertex()  also runs in constant time. Inserting an edge in the method insertEdge() runs in O(V) time since we are traversing a list to add another node.  Same thing with the isEdge() and the getWeight() method we traverse a list to access an item ( either a node or the weight).  The getAdjacent() method follows a similar logic with a runtime of O(V): we traverse a list and add it to a vector then return.

In the PrintDijkstra() method we used a priority queue, two maps, and a stack to implement it. To set up the priority queue correctly we defined a pair type:  typedef pair<int, int> iPair. That way we can push this onto the priority queue. With the first int being the distance from the source and the second int being the vertex. The priority queue is sorted by the first int which is the distance in this case making it simple for us to find the shortest distance. The maps are used to hold the distances and previous vertex.

In our while (priority queue is not empty) loop we get the adjacency list of the current vertex (this is O(V)). Then we loop through the adjacency list (O(V)) with an iterator. While looping through the list we call getWeight each time. getWeight itself is O(V) making this method O(V^2).  When updating the distances and previous nodes we do it in the priority queue as well as updating the values in our map. After the while loop we loop through our vertices vector again. In this loop, we first find the distance to that vertex in our map holding the distance. Then we push the vertex onto the stack. We then have a while loop that finds the previous vertex in our map and updates the vertex (vertex=previous vertex) each time until we get to the source. We then pop each vertex off the stack if it is not empty to get the path. So in this case the PrintDijkstra() method  is O(V^2).

Our final method printGraph() is also O(V^2). We traverse the vertices list in a for loop then inside this loop vertex we call getAdjacent which is a O(V) method. Also in this for loop we go through the returned adjacency list but this is not nested or else it would be O(V^3)!


Overall this was a pretty challenging assignment that taught me a lot. It refreshed my understanding of constructors, pointers, and references. I was also able to learn a lot about working with maps, priority queues, and defining variables.  If I could do it differently I would try quick fixes to the problems I ran into instead of focusing on one rigid solution. For instance, instead of taking so much time on trying to work with the vector of VectorNodeList I implemented the graph with I would have tried just making another vector to hold just the vertices a lot sooner. I was focused on doing the “right” way versus going for the efficient method.


# Dijkstras
