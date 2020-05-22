#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>

#define N 34

int way[33];

using namespace std;

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

    way[input[i]] = -1;
    pushAdj_list(adj, input[0], input[1], input[2]);
  }

  scanf("%d %d", &X, &L);

  way[X] = 0;

  // printGraph(adj, nver);
  way_adj(adj, adj[X], X, adj[X].size(), 0, X, X, L);

  for (i = 0; i < nver; i++)
  {
    if (way[i] != -1)
      printf("%d %d\n", i, way[i]);
    else
      printf("%d INFINITY\n", i);
  }

	return 0; 
} 
