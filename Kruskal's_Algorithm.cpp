/* Assignment -> Implement Kruskal's Algorithm using self-made Priority Queue 
and Union find or Disjoint set Union Algorithm to detect cycle. */

// Time Complexity of Kruskal's Algorithm using Union Find -> O(ElogE + EV)
// Time Complexity of Kruskal's Algorithm using Disjoint set Union by rank and Path compression -> O(ElogE + ElogV)


/*
    Test cases ->
    
    Test case 1 :                     
    3 3
    1 2 6
    2 0 2
    1 0 2
    
    Output : 
    0 1 2
    0 2 2
    
    
    
    Test case 2 : 
    4 4
    1 2 6
    2 3 2
    1 3 2
    1 0 2
    
    Output : 
    0 1 2
    1 3 2
    2 3 2
    
    
    
    Test case 3 :
    5 6
    0 1 2
    0 3 6
    1 3 8
    1 2 3
    1 4 5
    2 4 7
    
    Output : 
    0 1 2
    1 2 3
    1 4 5
    0 3 6
    
*/


#include<bits/stdc++.h>
using namespace std;

template <typename T>

// Generic Heap class 
class PQ
{
    private:
    vector<T>v;    //private dynamic array for storing elements.
    
    // private compare function to compare 2 objects of type T.
    int comp(T a , T b)
    {
        if(a.weight == b.weight)
        {
            if(a.source == b.source)
            {
                return a.destination - b.destination;
            }
            return a.source - b.source;
        }
        
        return a.weight - b.weight;
    }
    
    
    public:
    
    // function to push the elements in heap.
    void push(T ele)
    {
        v.push_back(ele);
        int childindex = v.size() - 1;
        int parentindex = (childindex - 1)/2;
        
        while((childindex != 0) && comp(v[parentindex] , v[childindex]) >= 1)
        {
            swap(v[childindex] , v[parentindex]);
            
             childindex = parentindex;
             parentindex = (childindex - 1)/2;
        }
    }
    
    // function to pop the elements from heap.
    void pop()
    {
        swap(v[0] , v[v.size() - 1]);
        v.pop_back();
        
        int parentindex = 0;
        int minindex = 0;
        
        while(true)
        {
            int lci = (2*parentindex + 1);
            int rci = (2*parentindex + 2);
            
            if((lci < v.size()) && comp(v[lci] , v[minindex]) <= 0)
            {
                minindex = lci;
            }
            if((rci < v.size()) && comp(v[rci] , v[minindex]) <= 0)
            {
                minindex = rci;
            }
            
            if(minindex == parentindex)
            break;
            
            swap(v[minindex] , v[parentindex]);
            parentindex = minindex;
        }
        
    }
    
    // function to know the top element in heap.
    T top()
    {
        return v[0];
    }
    
    // function to get size of heap.
    int getSize()
    {
        return v.size();
    }
    
};



// triplet class to store information of an edge of graph.
class triplet
{
   public:
   int source,destination,weight;
   
   triplet(int s,int d,int w)
   {
       this->source=s;
       this->destination=d;
       this->weight=w;
   }
};



// function to find parent of a vertex.
int findParent(int *parent , int vertex)
{
    if(parent[vertex] == vertex)
    {
        return vertex;
    }
    
    // doing path compression.
    return parent[vertex] = findParent(parent , parent[vertex]);
}


int main()
{
    int vertices,edges;
    cin>>vertices>>edges;
    
    // Min priority queue of class triplet.
    PQ<triplet>pq;
    
    // scanning the edges and putting inside heap.
    for(int i = 0 ; i < edges ; i++)
    {
        int s,d,w;
        cin>>s>>d>>w;
        
        triplet obj(s,d,w);
        
        pq.push(obj);
    }
    
    // parent array and rank array to help in cycle detection.
    int parent[vertices];
    int rank[vertices];
    
    for(int i = 0 ; i < vertices ; i++)
    {
        parent[i] = i;
        rank[i] = 0; 
    }
    

    // vector of triplet to store answer.
    vector<triplet>answer;
    
    // implementing kruskal's algorithm.
    while(pq.getSize() != 0 && answer.size() < (vertices - 1))
    {
        triplet top = pq.top();
        pq.pop();
        
        int source = top.source;
        int destination = top.destination;
        
        int sourceParent = findParent(parent , source);
        int destinationParent = findParent(parent , destination);
        
        // if this condition is true then its safe to add the current edge.
        if(sourceParent != destinationParent)
        {
            answer.push_back(top);
            
            // performing union by rank.
            if(rank[sourceParent] > rank[destinationParent])
            {
                parent[destinationParent] = sourceParent;
            }
            else if(rank[sourceParent] < rank[destinationParent])
            {
                 parent[sourceParent] = destinationParent;
            }
            else
            {
                parent[destinationParent] = sourceParent;
                rank[sourceParent]++;
            }
        }
    }
    
    
    // Printing the Minimum Spanning Tree.
    for(int i = 0 ; i < answer.size() ; i++)
    {
        cout<<min(answer[i].source , answer[i].destination)<<" "<<max(answer[i].source , answer[i].destination)<<" "<<answer[i].weight<<endl;
    }
    
}
