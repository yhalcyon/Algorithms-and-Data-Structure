//the C/C++ program for Dijkstra's shortest path calculation
//Adjacency matrix representation of the graph

#include<iostream>
#include<stdio.h>
#include<limits.h>
#include<fstream>
#include<string>
#include<math.h>

//Number of vertices
#define V 200
#define MAX 1000000
void readGraph(int graph[V][V])
{
	using namespace std;
	ifstream file("./data/dijkstraData.txt");
	string str;
	int n = 0;
	int i,j,num,a,b;
	a=0;
	b=0;
	while (getline(file,str))
	{
		n++;
		if(n<=V)
		{	
			num=0;
			for(i=1;i<str.length();i++)
			{	
				if(str[i-1]=='\t'&&(str[i]>='0'&&str[i]<='9'))
					num++;
				else if((str[i]>='0' && str[i]<='9') && (num>0||str[i-1]==','))
					num++;
				else if(str[i]==',')
				{
					for(j=0;j<num;j++)
						a+=(str[i-j-1]-48)*pow(10,j);
					num=0;
				}	
				else if((str[i-1]!='\t' && str[i]=='\t' && num>0) || (i==str.length()-1))
				{
					for(j=0;j<num;j++)
						b+=(str[i-j-1]-48)*pow(10,j);
					if(a)
					graph[n-1][a-1]=b;
					//cout<<a<<','<<b<<endl;
					a=0;
					b=0;
					num=0;
				}
			}
		}
	}	
}	

int minDistance(int dist[], bool sptSet[])
{
	int min = MAX, min_index;
	int v;
	for(v=0;v<V;v++)
		if(sptSet[v]==false && dist[v]<=min)
		{
			min=dist[v];
			min_index=v;
		}
	return min_index;
}

void dijkstra(int graph[V][V], int src)
{
	int dist[V];
	bool sptSet[V];
	int i;
	
	for(i=0;i<V;i++)
	{
		dist[i]=MAX;
		sptSet[i]=false;
	}
	
	dist[src]=0;
	
	int j;
	for(j=0;j<V-1;j++)
	{
		int u = minDistance(dist,sptSet);
		sptSet[u]=true;
		for(int v=0;v<V;v++)
			if(!sptSet[v] && graph[u][v] && dist[u]!=MAX
					&& dist[u]+graph[u][v]<dist[v])
				dist[v]=dist[u]+graph[u][v];
	}
	std::cout<<dist[6]<<','<<dist[36]<<','<<dist[58]<<','<<dist[81]<<','<<dist[98]<<','<<std::endl;
	std::cout<<dist[114]<<','<<dist[132]<<','<<dist[164]<<','<<dist[187]<<','<<dist[196]<<std::endl;
}

int main()
{
	int graph[V][V];
	int i,j;
	for(i=0;i<V;i++)
		for(j=0;j<V;j++)
			graph[i][j]=0;

	readGraph(graph);
	
	for(i=0;i<V;i++)
		for(j=0;j<V;j++)
			if(graph[i][j]!=graph[j][i])
				std::cout<<"error!"<<std::endl;
	dijkstra(graph,0);	
	
	return 0;
}
