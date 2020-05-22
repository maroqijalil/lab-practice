#include <iostream>
#include <vector>
#include <queue>
#include <limits.h> 
#include <stdio.h>
#include <string.h>

#define N 34

using namespace std;

int vis[N];
vector< pair<int, pair<int, int>> > l_way[N];

void bfs(vector< pair<int, int> > adj_l[], int startNode, int n, int h)
{
  queue<int> q;
  bool visited[n];
  pair<int, pair<int, int> > dist[n];
  int height[n];
  int temp_d;
  int i;
  int j;
  vector< pair<int, pair<int, int>> > l_way[n];

  for (i = 0; i < n; i++)
  {
    dist[i].first = INT_MAX;
    dist[i].second.second = 0; 
    dist[i].second.first = 
    height[i] = -1;
  }

  memset(height, -1, n * sizeof(height[0]));
  q.push(startNode);
  l_way[startNode].push_back(make_pair(0, make_pair(0, 0)));

  dist[startNode].first = 0;
  height[startNode] = 0;
  visited[startNode] = true;

  while (!q.empty())
  {
    int curNode = q.front();
    q.pop();

    // printf("%d..\n", curNode);

    for (size_t i = 0 ; i < adj_l[curNode].size() ; i++)
    {
      int nextNode = adj_l[curNode][i].first;
      
      temp_d = dist[curNode].first + adj_l[curNode][i].second;

      // printf("%d-%d ", nextNode, temp_d);

      if (height[nextNode] != -1)
      {
        if (height[nextNode] > (height[curNode] + 1))
          height[nextNode] = height[curNode] + 1;
      }
      else
        height[nextNode] = height[curNode] + 1;
      // printf("%d %d, ", nextNode, dist[nextNode].second.second);

      if (!visited[nextNode])
      {
        dist[nextNode].second.first = curNode;
        dist[nextNode].second.second = dist[curNode].second.second + 1;
        dist[nextNode].first = temp_d;

        q.push(nextNode);

        visited[nextNode] = true;
      }
      else
      {
        if (temp_d < dist[nextNode].first)
        {
          dist[nextNode].first = temp_d;
          dist[nextNode].second.first = curNode;
          dist[nextNode].second.second = dist[curNode].second.second + 1;

          q.push(nextNode);
          // printf("{ %d } ", nextNode);
        }
        else if (dist[nextNode].second.first == curNode)
        {
          dist[nextNode].first = temp_d;
          dist[nextNode].second.second = dist[curNode].second.second + 1;

          if (adj_l[nextNode].size() > 1)
            q.push(nextNode);
        }
      }
      // printf("%d -> ", dist[nextNode].second.second);
      l_way[nextNode].push_back(make_pair(temp_d, make_pair(curNode, dist[curNode].second.second + 1)));
    }
    // printf("\n");
  }

  // cout << "\n";
  // for (i = 0; i < n; i++)
  // {
  //   if (dist[i].first != INT_MAX)
  //     printf("%d %d\n", i, dist[i].first);
  //   else
  //     printf("%d INFINITY\n", i);
  // }

  // cout << endl;
  // for (i = 0; i < n; i++)
  // {
  //   printf("%d: ", i);
  //   for (j = 0; j < l_way[i].size(); j++)
  //     printf("%d-%d-%d ", l_way[i][j].first, l_way[i][j].second.first, l_way[i][j].second.second);
  //   printf("\n");
  // }

  // cout << endl;
  for (i = 0; i < n; i++)
  {
    int c_way = INT_MAX;
    printf("%d ", i);
    for (j = 0; j < l_way[i].size(); j++)
    {
      if (l_way[i][j].second.second <= h)
      {
        if (c_way > l_way[i][j].first)
          c_way = l_way[i][j].first;
      }
      // printf("%d-%d-%d ", l_way[i][j].first, l_way[i][j].second.first, l_way[i][j].second.second);
    }
    if (c_way != INT_MAX)
      printf("%d\n", c_way);
    else
      printf("INFINITY\n");
  }
}

void way_adj(
    vector< pair<int, int> > adj[],
    int index, int w, int p, int h
    // vector< pair<int, pair<int, int>> > *l_way[]
  )
{
  int i;

  // printf("%d\n", index);

  if (vis[index])
    return;

  if (!vis[index])
    l_way[index].push_back(make_pair(w, make_pair(h, p)));
  
  vis[index] = 1;

  for (i = 0 ; i < adj[index].size() ; i++)
  {
    if (vis[adj[index][i].first])
      continue;

    way_adj(
      adj, adj[index][i].first,
      adj[index][i].second + w,
      index, h + 1
    );
  }

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
  int j;
  int k;
  int index;
  int marker;
  int nver;
  int max_way;
  int X;
  int L;
  pair<int, pair<int, int>> way[N];

  scanf("%d %d", &nver, &T);

  for (i = 0; i < nver; i++)
    way[i].first = INT_MAX;

  int ver[nver];
  vector< pair<int, int> > adj[N];

  while (T--)
  {
    scanf("%d %d %d", &input[0], &input[1], &input[2]);

    pushAdj_list(adj, input[0], input[1], input[2]);
  }

  scanf("%d %d", &X, &L);

  // printGraph(adj, nver);
  way_adj(adj, X, 0, X, 0);
  // bfs(adj, X, nver, L);

  // for (i = 0; i < nver; i++)
  // {
  //   printf("%d: ", i);
  //   for (j = 0; j < l_way[i].size(); j++)
  //   {
  //     printf("%d-%d-%d ", l_way[i][j].first, l_way[i][j].second.first, l_way[i][j].second.second);
  //   }
  //   printf("\n");
  // }


  for (i = 0; i < nver; i++)
  {
    max_way = INT_MAX;
    
    for (j = 0; j < l_way[i].size(); j++)
    {
      int tot_w = l_way[i][j].first;
      int h_w = l_way[i][j].second.first;
      int p_w = l_way[i][j].second.second;

      if (max_way > tot_w)
      {
        if (h_w <= L)
        {
          // if (way[p_w].second.first + 1)
        }
      }
    }
  }

  for (i = 0; i < nver; i++)
  {
    printf("%d %d\n", i, way[i].first);
  }

	return 0; 
} 
