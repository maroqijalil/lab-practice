#include <iostream>
#include <vector>
#include <queue>
#include <limits.h> 
#include <stdio.h>
#include <string.h>

#define N 34

int way[33];

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
    vector< pair<int, int> > ad,
    int index, int n, int w, int p,
    int x, int h
  )
{
  int i;

  if (h == -1)
    return;

  // printf("%d %d %d masuk\n", index, w, x);

  if (w != 0)
  {
    if (way[index] == -1)
      way[index] = w;
    else if (way[index] > w)
      way[index] = w;
  }

  h--;

  for (auto v : adj[index])
  {
    if (v.first != x && v.first != p)
    {
      way_adj(
          adj, adj[v.first], v.first,
          adj[v.first].size(),
          w + v.second, index, x, h
        );
    }
  }
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
  int i;
  int k;
  int marker;
  int nver;
  int X;
  int L;

  scanf("%d %d", &nver, &T);

  int ver[nver];
  vector< pair<int, int> > adj[nver];

  while (T--)
  {
    scanf("%d %d %d", &input[0], &input[1], &input[2]);

    pushAdj_list(adj, input[0], input[1], input[2]);
  }

  scanf("%d %d", &X, &L);

  // printGraph(adj, nver);
  bfs(adj, X, nver, L);

	return 0; 
} 
