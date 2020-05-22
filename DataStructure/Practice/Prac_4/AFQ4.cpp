#include <iostream>
#include <vector>
#include <queue>
#include <limits.h> 
#include <stdio.h>
#include <string.h>

#define N 34

bool vis[N];

using namespace std;

void bfs(vector< pair<int, int> > adj_l[], int startNode, int n, int h)
{
  queue<int> q;
  bool visited[n];
  int dist[n];
  int height[n];
  int temp_d;

  memset(dist, -1, n * sizeof(dist[0]));
  memset(height, 0, n * sizeof(height[0]));
  q.push(startNode);

  dist[startNode] = 0;
  height[startNode] = 0;
  visited[startNode] = true;

  while (!q.empty())
  {
    int curNode = q.front();
    q.pop();

    if (height[curNode] < h)
    {
      for (size_t i = 0 ; i < adj_l[curNode].size() ; i++)
      {
        int nextNode = adj_l[curNode][i].first;

        height[nextNode] = height[curNode] + 1;
        temp_d = dist[curNode] + adj_l[curNode][i].second;

        if (!visited[nextNode])
        {
          dist[nextNode] = temp_d;
          adj_l[curNode][i].second = dist[nextNode];
          q.push(nextNode);
          visited[nextNode] = true;
        }
        else
        {
          if (temp_d < dist[nextNode])
          {
            dist[nextNode] = temp_d;
            adj_l[curNode][i].second = dist[nextNode];
          }
        }
      }
    }
  }

  int i = 0;
  for (auto s : dist)
  {
    if (s != -1)
      printf("%d %d\n", i++, s);
    else
      printf("%d INFINITY\n", i++);
  }
}

void way_adj(
    vector< pair<int, int> > adj[],
    int index, int w, int p, int h,
    int way[]
  )
{
  int i;

  if (h == -1)
  {
    
    return;
  }

  if (!vis[index])
  {
    if (way[index] > (way[p] + w))
      way[index] = way[p] + w;

    vis[index] = true;
  }
  else if (vis[index])
  {
    if (way[index] > (way[p] + w))
      way[index] = way[p] + w;

    vis[index] = false;
    return;
  }

  for (size_t i = 0 ; i < adj[index].size() ; i++)
  {
    way_adj(
      adj, adj[index][i].first,
      adj[index][i].second,
      index, h - 1, way
    );
  }

  vis[index] = false;
}

void printGraph(vector< pair<int, int> > adj[], int V) 
{ 
	for (int v = 0; v < V; ++v) 
	{ 
		cout << "\n Adjacency list of vertex "
			<< v << "\n head "; 
		for (auto x : adj[v]) 
		  cout << "-> " << x.first << ": " << x.second << " "; 
		printf("\n"); 
	} 
} 

void pushAdj_list(vector< pair<int, int> > adj_l[], int u, int v, int w) 
{ 
	adj_l[u].push_back(make_pair(v, w)); 
	adj_l[v].push_back(make_pair(u, w)); 
}

void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
void bubbleSort(int arr[], int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)
    for (j = 0; j < n-i-1; j++)
      if (arr[j] > arr[j+1]) 
        swap(&arr[j], &arr[j+1]); 
}

int main() 
{
  int T;
  int n = 0;
  int input[3];
  int i = 0;
  int k;
  int marker;
  int nver;
  int X;
  int L;
  int way[N];

  scanf("%d %d", &nver, &T);

  for (i = 0; i < nver; i++)
    way[i] = INT_MAX;

  int ver[nver];
  vector< pair<int, int> > adj[nver];

  while (T--)
  {
    scanf("%d %d %d", &input[0], &input[1], &input[2]);

    pushAdj_list(adj, input[0], input[1], input[2]);
  }

  scanf("%d %d", &X, &L);

  way[X] = 0;
  // printGraph(adj, nver);
  way_adj(adj, X, 0, X, L, way);
  // bfs(adj, X, nver, L);

  for (i = 0; i < nver; i++)
  {
    if (way[i] != INT_MAX)
      printf("%d %d\n", i, way[i]);
    else
      printf("%d INFINITY\n", i);
  }

	return 0; 
} 
