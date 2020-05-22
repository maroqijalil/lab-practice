#include <iostream>
#include <vector>
#include <queue>
#include <limits.h> 
#include <stdio.h>
#include <string.h>

#define N 26

int vis[N];
int num[N];

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

int way_adj(
    vector<int> adj[],
    int index
  )
{
  int i;
  int way[adj[index].size()];
  int l_way = 0;

  if (vis[index])
    return -1;
  
  vis[index] = 1;

  // printf("%d> ", index);

  for (i = 0; i < adj[index].size(); i++)
  {
    int next = adj[index][i];
    // printf("{%lu} ", adj[index].size());
    way[i] = 0;
    way[i] = way_adj(adj, next) + 1;

    // printf("%d-%d ", adj[index][i], way[i]);

    if (l_way < way[i])
      l_way  = way[i];
  }

  vis[index] = 0;

  // printf("<%d ", l_way);

  return l_way;
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

void pushAdj_list(vector<int> adj_l[], int u, int v) 
{ 
	adj_l[u].push_back(v); 
	adj_l[v].push_back(u); 
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
  int T = 5;
  int n = 5;
  int i;
  int num;
  int counter = 0;
  int matrix[5][5];
  char input[6];
  vector<int> adj[N];

  while (T--)
  {
    scanf("%s", input);

    for (i = 0; i < n; i++)
    {
      if (input[i] == 'X')
        matrix[counter][i] = 0;
      else
        matrix[counter][i] = input[i] - '0';
      
      num = counter*5 + i;

      if ((num + 1) < 25)
        pushAdj_list(adj, num, num + 1);
      if ((num - 1) > -1)
        pushAdj_list(adj, num, num - 1);
      if ((num + 5) < 25)
        pushAdj_list(adj, num, num + 5);
      if ((num - 5) > -1)
        pushAdj_list(adj, num, num - 5);
    }

    counter++;
    printf("\n");
  }



	return 0; 
} 
