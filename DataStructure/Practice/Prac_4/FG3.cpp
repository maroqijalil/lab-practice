#include <iostream>
#include <vector>
#include <queue>
#include <limits.h> 
#include <stdio.h>
#include <string.h>
#include <math.h>

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

  printf("%d> ", index);

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

  printf("<%d ", l_way);

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
	// adj_l[v].push_back(u); 
}

int solvePath (
  vector<int> adj[], int puz[],
  int index, int target, int dir,
  queue<int> *path
  )
{
  int i;
  int left = -1;
  int right = -1;
  int top = -1;
  int bottom = -1;
  int way[4];
  int key = 0;
  int dir_dis = (index%5) - (target%5);

  printf("%d\n", index);

  if (index == target)
  {
    path->push(index);
    return 1;
  }
  
  path->push(index);
  vis[index] = 1;
  
  for (i = 0; i < adj[index].size(); i++)
  {
    if (adj[index][i] == index-1)
      left = adj[index][i];
    if (adj[index][i] == index-5)
      top = adj[index][i];
    if (adj[index][i] == index+1)
      right = adj[index][i];
    if (adj[index][i] == index+5)
      bottom = adj[index][i];
  }

  if (dir_dis < 0 || (dir < 0 && dir_dis == 0))
  {
    way[0] = left;
    way[1] = bottom;
    way[2] = right;
    way[3] = top;

    if (left != -1 && !puz[left] && !vis[left])
      key = solvePath(adj, puz, left, target, dir, path);
    if (key)
    {
      path->push(index);
      return 1;
    }

    if (bottom != -1 && !puz[bottom] && !vis[bottom])
      key = solvePath(adj, puz, bottom, target, dir, path);
    if (key)
    {
      path->push(index);
      return 1;
    }

    if (right != -1 && !puz[right] && !vis[right])
      key = solvePath(adj, puz, right, target, dir, path);
    if (key)
    {
      path->push(index);
      return 1;
    }
    
    if (top != -1 && !puz[top] && !vis[top])
      key = solvePath(adj, puz, top, target, dir, path);
    if (key)
    {
      path->push(index);
      return 1;
    }
    
  }
  else if (dir_dis > 0 || (dir > 0 && dir_dis == 0))
  {
    if (right != -1 && !puz[right] && !vis[right])
      key = solvePath(adj, puz, right, target, dir, path);
    if (key)
    {
      path->push(index);
      return 1;
    }
    
    if (bottom != -1 && !puz[bottom] && !vis[bottom])
      key = solvePath(adj, puz, bottom, target, dir, path);
    if (key)
    {
      path->push(index);
      return 1;
    }
    
    if (left != -1 && !puz[left] && !vis[left])
      key = solvePath(adj, puz, left, target, dir, path);
    if (key)
    {
      path->push(index);
      return 1;
    }
    
    if (top != -1 && !puz[top] && !vis[top])
      key = solvePath(adj, puz, top, target, dir, path);
    if (key)
    {
      path->push(index);
      return 1;
    }
    
  }

  for (i = 0; i < 4; i++)
  {
    if (way[i] != -1 && (!puz[way[i]] || puz[way[i]] == puz[target]) && !vis[way[i]])
      key = solvePath(adj, puz, way[i], target, dir, path);
    
    if (key)
    {
      path->push(index);
      return 1;
    }
  }

  return 0;
}

int main() 
{
  int T = 5;
  int n = 5;
  int i;
  int j;
  int k;
  int num;
  int counter = 0;
  int matrix[25];
  char input[6];
  int index[5] = {0};
  int place[5][2];
  vector< pair<int, int> > dist[5][5];
  vector<int> adj[N];
  queue<int> q[5];

  while (counter < 5)
  {
    scanf("%s", input);

    for (i = 0; i < n; i++)
    {
      num = counter*5 + i;
      // printf("%d\n", num);

      if ((num + 1) < 25)
        if (num % 5 != 4)
          pushAdj_list(adj, num, num + 1);
      if ((num - 1) > - 1)
        if (num % 5 != 0)
          pushAdj_list(adj, num, num - 1);
      if ((num + 5) < 25)
        pushAdj_list(adj, num, num + 5);
      if ((num - 5) > - 1)
        pushAdj_list(adj, num, num - 5);

      if (input[i] == 'X')
        matrix[num] = 0;
      else
      {
        matrix[num] = input[i] - '0';

        index[matrix[num]] += 1;
        place[matrix[num]][index[matrix[num]] - 1] = num;

        if (index[matrix[num]] == 2)
        {
          int div1 = place[matrix[num]][0]/5;
          int div2 = place[matrix[num]][1]/5;
          int div = abs(div1 - div2);
          int mod1 = place[matrix[num]][0]%5;
          int mod2 = place[matrix[num]][1]%5;
          int min1 = mod1 - mod2;
          int min2 = abs(min1);
          // printf("->%d %d\n", matrix[num], min + div);

          dist[div][min2].push_back(make_pair(matrix[num], min1));
        }
      }
    }
    counter++;
  }

  for (i = 0; i < 5; i++)
  {
    for (j = 0; j < 5; j++)
    {
      if (dist[i][j].size() > 0)
      {
        for (k = 0; k < dist[i][j].size(); k++)
        {
          int ind = dist[i][j][k].first;
          int dir = dist[i][j][k].second;
          solvePath(adj, matrix, place[ind][0], place[ind][1], dir, &q[ind]);
        }
      }
    }
  }

  // for (i = 0; i < 25; i++)
  // {
  //   printf("%d: ", i);
  //   for (j = 0; j < adj[i].size(); j++)
  //   {
  //     printf("%d ", adj[i][j]);
  //   }
  //   printf("\n");
  //   if (dist[i].size() > 0)
  //   {
  //     for (j = 0; j < dist[i].size(); j++)
  //       printf("%d--%d-%d ", dist[i][j], place[dist[i][j]][0], place[dist[i][j]][1]);
  //     printf("\n");
  //   }
  // }

	return 0; 
} 
