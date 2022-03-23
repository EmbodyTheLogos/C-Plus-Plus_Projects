//---------------------------------------------------------------------
// Name: Long Nguyen
// Email: lhn5032@psu.edu
// Class: CMPSC 122, Section 1
// Program: dij.cpp
//
// Description: Dijkastra’s Shortest Path Algorithm between two vertices on a graph
//
// Acknowledgement: (1) Doctor Chang's Notes
//		    (2) Provided Resources
//		    (3) http://math.mit.edu/~rothvoss/18.304.3PM/Presentations/1-Melissa.pdf
//					
//
//---------------------------------------------------------------------


#include <iostream>
#include <string>
#include "graph.h"
#include "min_heap.h"
#include "set.h"
#include "stack.h"

using namespace std;
void dij(Graph, int, int);

int main()
{
    Graph g;
    string path;
    
    cout << "Please enter location of graph file to load: ";
    cin >> path;

	if (g.create_graph(path))
	{
		cout<<"Please enter the index of the starting vertex: ";
    	int start;
    	cin>>start;
    	while (start<0||start>=g.dimension())
    	{
    		cout<<"Invalid index.\n";
    		cout<<"Please enter the index of the starting vertex: ";
    		cin>>start;
		}
    	cout<<"Please enter the index of the target vertex: ";
    	int target;
    	cin>>target;
    	while (target<0||target>=g.dimension())
    	{
    		cout<<"Invalid index.\n";
    		cout<<"Please enter the index of the target vertex: ";
    		cin>>target;
		}
    	cout << g.dimension() << endl;
    	g.print_adj_matrix();
		dij(g,start,target);
	} else cout<<"Failed to generate graph from provided file.\n"; 
   return 0;
}


void dij(Graph g, int start, int target){
    int distance[g.dimension()];
    distance[start] = 0;
	int previous[g.dimension()];
    MinHeap Q;
    Set visited;
    Stack S;
	int edges[g.dimension()]; //store visited edges
    for(int v = 0; v<g.dimension(); v++){ //initiate values for distance[v]
        if (v!=start){
        distance[v] = 999;
        }
        previous[v]=-1;
        Q.insert(v,distance[v]); //insert index corresponding to cost
    }
	int u;
	visited.add(start); //make sure not to visit the starting index
    while (!Q.is_empty())
	 {
	 	u = Q.extract_min();//give the min distance index
		visited.add(u); //store visited nodes
		
        if (u == target){
            break;
        }   
	
		for(int v= 0;v<g.dimension();v++)
		{
			if (!(visited.contains(v)) && (g.get_weight(u,v)!=0) )
			{
				int alt = distance[u] + g.get_weight(u,v);
				if(alt<distance[v])
				{
					distance[v] = alt;
					previous[v] = u;
					Q.decrease_priority(v, alt);
				}
			}
		}
			
    }
    //pushing all the visited node in a stack  
    u = target;
    while (previous[u]!=-1){
    	S.push(u);
    	u=previous[u];
	}
	S.push(u);
	
	cout<<"\nThe shortest path from "<<start<<" to "<<target<<" is: \n";
	int index = 0;
	//initialize visted edges
	while(!S.isEmpty())
	{
		edges[index] = S.pop();
		index++;	
	}
	//printing the distance between each visited edge
	for(int i = 0; i<index-1; i++)
	{
		cout<<edges[i]<< " to "<<edges[i+1]<<": "<<distance[edges[i+1]] - distance[edges[i]]<<endl;
	}
	//cout<<"The shortest path from vertex "<<start<<" to vertex "<<target<<" is: "<<endl;
    cout<<"\nTotal path length is "<<distance[target]<<endl;
    exit(0);
}
