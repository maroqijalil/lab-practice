#include <iostream>
#include <vector>
#include <queue>
#include <limits.h> 
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stack>

#define N 26

int vis[N];
int num[N];

using namespace std;

int solvePath(
    vector<int> adj[],
    int index, int target,
    stack <int> *stac, int puz[]
  )
{
  int i;
  int key = 0;
  int marker = 0;
  int n = adj[index].size();
  int s_way = INT_MAX;
  stack <int> way_st[n];

  if (index == target)
  {
    stac->push(index);
    return 1;
  }
  
  vis[index] = 1;

  for (i = 0; i < adj[index].size(); i++)
  {
    int next = adj[index][i];
    key = 0;

    if (vis[next])
      continue;
    
    if (puz[next])
      if (puz[next] != puz[target])
        continue;

    key = solvePath(adj, next, target, &way_st[i], puz);

    way_st[i].push(index);

    if (s_way > way_st[i].size() && key)
    {
      s_way  = way_st[i].size();
      marker = i;
    }
  }

  vis[index] = 0;

  if (s_way != INT_MAX)
  {
    for (i = 0; i < s_way; i++)
    {
      stac->push(way_st[marker].top());
      way_st[marker].pop();
    }
    key = 1;
  }

  return key;
}

void pushAdj_list(vector<int> adj_l[], int u, int v) 
{ 
	adj_l[u].push_back(v);
}

int main() 
{
  int T = 5;
  int n = 5;
  int i;
  int j;
  int k;
  int l;
  int num;
  int key = 0;
  int counter = 0;
  int matrix[25];
  int matrix2[25];
  char input[6];
  int index[6] = {0};
  int place[6][2];
  vector<int> dist[6][6];
  vector<int> prev_ind;
  vector<int> adj[N];
  queue<int> q;
  queue<int> prev_q;
  stack<int> s[6];

  while (counter < 5)
  {
    scanf("%s", input);

    for (i = 0; i < n; i++)
    {
      num = counter*5 + i;

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
      {
        matrix[num] = 0;
        matrix2[num] = 0;
      }
      else
      {
        matrix[num] = input[i] - '0';
        matrix2[num] = input[i] - '0';

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

          dist[div][min2].push_back(matrix[num]);
        }
      }
    }
    counter++;
  }

  for (i = 0; i < 5; i++)
    for (j = 0; j < 5; j++)
      if (dist[i][j].size() > 0)
        for (k = 0; k < dist[i][j].size(); k++)
        {
          int ind = dist[i][j][k];
          q.push(ind);
        }

  while (true)
  {
    int marker = 0;

    while (!q.empty())
    {
      int ind = q.front();
      q.pop();

      key = solvePath(adj, place[ind][0], place[ind][1], &s[ind], matrix2);

      if (key)
      {        
        while (!s[ind].empty())
        {
          matrix2[s[ind].top()] = ind;
          s[ind].pop();
        }
      }
      else
      {
        for (l = 0; l < 25; l++)
          matrix2[l] = matrix[l];
        
        q.push(ind);

        while (!prev_q.empty())
        {
          q.push(prev_q.front());
          prev_q.pop();
        }
      }

      prev_q.push(ind);
    }

    for (i = 0; i < 25; i++)
    {
      if (matrix2[i] == 0)
      {
        for (j = 0; j < adj[i].size(); j++)
          if (matrix2[adj[i][j]])
            break;

        matrix2[i] = matrix2[adj[i][j]];
        marker = 1;
      }
    }

    if (!marker)
      break;
  }

  for (i = 0; i < 25; i++)
  {
    printf("%d", matrix2[i]);
    if (i%5 == 4)
      printf("\n");
  }

	return 0; 
} 
