#include<iostream>
#include<list>
#include <limits>
#include<vector>
#include <cstdlib>
#include <algorithm>
#include <map>
#include<queue>
#include<stack>

using namespace std;

typedef pair<int, int> iPair; // For Priority Queue

class VertexListNode{
    bool headNode;
public:
    VertexListNode *next;
    int name;
    int weight;
    VertexListNode(int name, bool isHead,int weight,VertexListNode* next){
        this->name = name;
        headNode = isHead;
        this->weight = weight;
        this->next = next;
    }
};

class Graphs_P3
{
    const static int MAXNUMVERTICES = 100;
    vector<VertexListNode> theVertices; //vector of vertices
    vector<int> Vertices;  //vector of vertices
    int numVertices;
    int * vertexConverter = new int[MAXNUMVERTICES]; //convert vertex  number into index in table
    bool undirected;
    
public:
    Graphs_P3(){
        numVertices = 0;
        undirected = false;
    }
    void insertVertex(int vertex){//inserts new vertex in graph
        VertexListNode *newVertex = new VertexListNode(vertex, true, -999, NULL);
        theVertices.push_back(*newVertex);
        Vertices.push_back(vertex);
        vertexConverter[vertex] = ++numVertices;
        return;
    }
    bool isVertex(int vertex) {
        int index = vertexConverter[vertex];
        if (index == 0)
            return false;
        else
            return true;
    }
    
    void insertEdge(int from, int to, int weight){//inserts new edge in graph
        if (!isVertex(from))
            insertVertex(from);
        if (!isVertex(to))
            insertVertex(to);
        
        int index = vertexConverter[from]-1;
        VertexListNode *theHead = &theVertices[index];
        VertexListNode *current = theHead;
        //now need to go to the end of this list, and add a new vertex;
        VertexListNode *newEdge = new VertexListNode(to, false, weight, NULL);
        while (current->next != NULL){
            current = current->next;
        }
        current->next = newEdge;
        return;
    }
    
    bool isEdge(int from, int to){   //returns true if there is an edge between the vertices from and to
        if (isVertex(from) && isVertex(to)){
            int index = vertexConverter[from]-1;
            VertexListNode *temp=&theVertices[index];
            while (temp->next != NULL){
                temp = temp->next;
                if (temp->name==to ){
                    return true;
                }
            }
        }
        return false;
    }
    int getWeight(int from, int to){  //returns the weight of the edge between the vertices from and to
        int weight=-999;
        if (isEdge(from,to)){//Check if both vertices exist.
            int index = vertexConverter[from]-1;
            VertexListNode *temp=&theVertices[index];
            while (temp->next != NULL){
                temp = temp->next;
                if (temp->name==to ){
                    weight=temp->weight;
                    return weight;
                }
            }
        }
        return weight; //default
        
    }
    
    vector<int> getAdjacent(int vertex){ //return an array of integers representing vertices adjacent to vertex
        vector<int> returnList;
        int number;
        if (isVertex(vertex)){
            int index = vertexConverter[vertex]-1;
            VertexListNode *adjacent=&theVertices[index];
            while (adjacent->next != NULL){
                adjacent = adjacent->next;
                number=adjacent->name;
                returnList.push_back(number);
            }
            std::sort (returnList.begin(), returnList.end());
            
        }
        return returnList;
    }
    
    void printDijkstra(int source){
        priority_queue< iPair, vector <iPair> , greater<iPair> > pq;//Create Priority Queue.
        std::map<int,int> Previous;
        std::map<int,int> Distance;
        
        
        int infinity=std::numeric_limits<int>::max();;
        int vertex;
        
        std::sort(Vertices.begin(),Vertices.end());
        for (int i=0; i<Vertices.size();i++){
            vertex=Vertices[i];
            Previous[vertex]=infinity;
            Distance[vertex]=infinity;
            //Previous.insert(pair<int,int>(vertex,NULL));
            //Distance.insert(pair<int,int>(vertex,infinity));
        }
        
        // Insert source itself in priority queue and initialize
        // its distance as 0.
        pq.push(make_pair(0, source));
        Distance[source] = 0;
        Previous[source]=0;
        
        /* Looping till priority queue becomes empty (or all
         distances are not finalized) */
        while (!pq.empty())
        {
            // The first vertex in pair is the minimum distance
            // vertex, extract it from priority queue.
            // vertex label is stored in second of pair (it
            // has to be done this way to keep the vertices
            // sorted distance (distance must be first item
            // in pair)
            int u = pq.top().second;
            pq.pop();
            
            vector<int> Adjacent=getAdjacent(u);//Store adjacency list(s)
            
            // 'i' is used to get all adjacent vertices of a vertex
            vector<int>::iterator it;
            for (it = Adjacent.begin(); it != Adjacent.end(); ++it)
            {
                // Get vertex label and weight of current adjacent
                // of u.
                int v = *it;
                int weight =getWeight(u, *it);
                
                //  If there is shorted path to v through u.
                if (Distance[v] > Distance[u] + weight)
                {
                    // Updating distance of v
                    Previous[v]=u;
                    Distance[v] = Distance[u] + weight;
                    pq.push(make_pair(Distance[v], v));
                }
            }
        }
        
        
        int previousTemp;
        stack<int> Path;
        std::cout<<"V D P"<<endl;
        
        for (int i = 0; i < Vertices.size(); ++i){
            vertex=Vertices[i];
            if (vertex!=source){
                std::cout<<vertex<<" "<<(Distance.find(vertex)->second)<<" ";
                Path.push(vertex);
                
                if (vertex!=source){
                    
                    
                    while ((Previous.find(vertex)->second)!=source){
                        previousTemp=(Previous.find(vertex)->second);
                        Path.push(previousTemp);
                        vertex=previousTemp;
                    }
                    
                }
                
                Path.push(source);
                
                while (!Path.empty()){
                    if (Path.size()==1){
                        std::cout<<Path.top();
                    }
                    else{
                        std::cout<<Path.top()<<"-";
                    }
                    Path.pop();
                }
                if (i!=(Vertices.size()-1)){
                    std::cout<<endl;
                }
                
            }
        }
        
        return;
    }
    
    void printGraph(){ //prints graph in a format sorted by ascending vertex and edge list}
        //Format: V EdgeList
        sort(Vertices.begin(),Vertices.end());
        for (int i=0;i<Vertices.size(); i++){
            cout<<Vertices[i];
            vector<int> temp=getAdjacent(Vertices[i]);
            if(!temp.empty()){
                cout<<" ";
                for (int j=0;j<temp.size();j++){
                    if (j==(temp.size()-1)){
                        cout<<temp[j];
                    }
                    else{
                        cout<<temp[j]<<" ";
                    }
                }
            }
            if(i==Vertices.size()){
            }
            else{
                cout<<endl;
            }
            
        }
        return;
    }
    
    
};


int main()
{
    //DO NOT CHANGE THIS FUNCTION. CHANGE YOUR IMPLEMENTATION CODE TO MAKE IT WORK
    int noOfLines, operation, vertex, to, fro, weight,source,j;
    vector<int> arr;
    int arrSize;
    Graphs_P3 g;
    cin>>noOfLines;
    for(int i=0;i<noOfLines;i++)
    {
        cin>>operation;
        switch(operation)
        {
            case 1:
                cin>>vertex;
                g.insertVertex(vertex);
                break;
            case 2:
                cin>>fro;
                cin>>to;
                cin>>weight;
                g.insertEdge(fro,to,weight);
                break;
            case 3:
                cin>>fro;
                cin>>to;
                cout<<g.isEdge(fro,to)<<"\n";
                break;
            case 4:
                cin>>fro;
                cin>>to;
                cout<<g.getWeight(fro,to)<<"\n";
                break;
            case 5:
                cin>>vertex;
                arr=g.getAdjacent(vertex);
                arrSize = arr.size();
                j=0;
                while(j<arrSize)
                {
                    cout<<arr[j]<<" ";
                    j++;
                }
                cout<<"\n";
                break;
            case 6:
                cin>>source;
                g.printDijkstra(source);
                cout<<"\n";
                break;
            case 7:
                g.printGraph();
                cout<<"\n";
                break;
        }
    }
}
