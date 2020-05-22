#include <iostream>
#include <vector>
#include <queue>
#include <limits.h> 
#include <stdio.h>
#include <string.h>

#define N 34

int vis[N];

using namespace std;

void bfs(vector< pair<int, int> > adj_l[], int startNode, int n, int h)
{
  queue<int> q;
  bool visited[n];
  pair<int, pair<int, int> > dist[n];
  int height[n];
  int temp_d;
  int i;

  for (i = 0; i < n; i++)
    dist[i].first = INT_MAX;

  memset(height, -1, n * sizeof(height[0]));
  q.push(startNode);

  dist[startNode].first =
  dist[startNode].second.second = 0; 
  dist[startNode].second.first = -1;
  height[startNode] = 0;
  visited[startNode] = true;

  while (!q.empty())
  {
    int curNode = q.front();
    q.pop();

    // printf("%d..\n", curNode);

    if (dist[curNode].second.second < h)
    {
      for (size_t i = 0 ; i < adj_l[curNode].size() ; i++)
      {
        int nextNode = adj_l[curNode][i].first;

        if (height[nextNode] != -1)
        {
          if (height[nextNode] > (height[curNode] + 1))
            height[nextNode] = height[curNode] + 1;
        }
        else
          height[nextNode] = height[curNode] + 1;
        
        temp_d = dist[curNode].first + adj_l[curNode][i].second;

        // printf("%d-%d ", nextNode, temp_d);
        // printf("%d %d, ", nextNode, dist[nextNode].second.second);

        if (!visited[nextNode])
        {
          dist[nextNode].second.second = dist[curNode].second.second + 1;
          dist[nextNode].second.first = curNode;

          if (dist[nextNode].second.second <= h)
            dist[nextNode].first = temp_d;

          // adj_l[curNode][i].second = dist[nextNode].first;
          q.push(nextNode);
          visited[nextNode] = true;
        }
        else
        {
          if (temp_d < dist[nextNode].first && dist[curNode].second.second < h)
          {
            q.push(nextNode);

            // printf("{ %d } ", nextNode);

            dist[nextNode].first = temp_d;
            dist[nextNode].second.second = dist[curNode].second.second + 1;
            dist[nextNode].second.first = curNode;
            // adj_l[curNode][i].second = dist[nextNode].first;
          }
        }

        // printf("%d -> ", dist[nextNode].second.second);
      }
      // printf("\n");
    }
    else
    {
      // printf("else\n");
      for (size_t i = 0; i < adj_l[curNode].size(); i++)
      {
        int nextNode = adj_l[curNode][i].first;
        // printf("%d %d, ", nextNode, dist[nextNode].second.first);
        if (!visited[nextNode] || dist[nextNode].second.first == curNode)
        {
          dist[nextNode].first = INT_MAX;
          dist[nextNode].second.second = dist[curNode].second.second + 1;
        }
        // printf("%d -> ", dist[nextNode].second.second);
      }
      // printf("\n");
    }
  }

  for (i = 0; i < n; i++)
  {
    if (dist[i].first != INT_MAX)
      printf("%d %d\n", i, dist[i].first);
    else
      printf("%d INFINITY\n", i);
  }
}

void way_adj(
    vector< pair<int, int> > adj[],
    int index, int w, int h, int p, int lim,
    pair<int, pair<int, int> > way[]
  )
{
  int i;
  pair<int, pair<int, int> > c_way;

  if (vis[index])
    return;
  
  vis[index] = 1;

  if (w < way[index].first)
  {
    if (h <= lim)
    {
      way[index].first = w;
      way[index].second.first = p;
      way[index].second.second = h;
    }
    else if (h > lim)
    {
      if (way[index].second.first == -1
          || way[index].second.first == p
        )
      {
        // printf("%d\n", index);
        way[index].first = INT_MAX;
        way[index].second.first = p;
        way[index].second.second = h;
      }
    }
  }

  for (i = 0; i < adj[index].size(); i++)
  {
    int next = adj[index][i].first;
    // int c_way = way[i].first;
    // printf("> %d --%d\n", index, next);
    way_adj(
      adj, next, way[index].first +
      adj[index][i].second, way[index].second.second + 1,
      index, lim, way
    );

    // printf("%d-%d ", adj[index][i].first, c_way);
  }
  // printf("\n");
  vis[index] = 0;
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
  pair<int, pair<int, int> > way[N];

  scanf("%d %d", &nver, &T);

  for (i = 0; i < nver; i++)
  {
    way[i].first = INT_MAX;
    way[i].second.first = -1;
    way[i].second.second = 0;
  }

  int ver[nver];
  vector< pair<int, int> > adj[nver + 1];

  while (T--)
  {
    scanf("%d %d %d", &input[0], &input[1], &input[2]);

    pushAdj_list(adj, input[0], input[1], input[2]);
  }

  scanf("%d %d", &X, &L);

  // printGraph(adj, nver);
  way_adj(adj, X, 0, 0, 0, L, way);
  // bfs(adj, X, nver, L);

  for (i = 0; i < nver; i++)
  {
    if (way[i].first != INT_MAX)
      printf("%d %d\n", i, way[i].first);
    else
      printf("%d INFINITY\n", i);
  }

	return 0; 
} 
