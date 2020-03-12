#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct pqueueNode_t {
  int _hp;
  int _atk;
  int _spd;
  int _bar;
  struct pqueueNode_t *next;
  struct pqueueNode_t *prev;
} PQueueNode;

typedef struct pqueue_t {
  PQueueNode *_top;
  PQueueNode *_down;
  unsigned _size;
} PriorityQueue;

void pqueue_init(PriorityQueue *pqueue)
{
  pqueue->_top = pqueue->_down = NULL;
  pqueue->_size = 0;
}

bool pqueue_isEmpty(PriorityQueue *pqueue) {
  return (pqueue->_top == NULL && pqueue->_down == NULL);
}

void pqueue_push(PriorityQueue *pqueue, int hp, int atk, int spd)
{
  PQueueNode *temp = pqueue->_top;
  PQueueNode *newNode = (PQueueNode*) malloc (sizeof(PQueueNode));

  pqueue->_size++;

  newNode->_hp = hp;
  newNode->_atk = atk;
  newNode->_spd = spd;
  newNode->_bar = 0;
  newNode->next = NULL;
  newNode->prev = NULL;

  if (pqueue_isEmpty(pqueue)) {
    pqueue->_top = pqueue->_down = newNode;
    return;
  }

  if (pqueue->_top == pqueue->_down)
  {
    if (spd > pqueue->_top->_spd) {
      newNode->next = pqueue->_top;
      pqueue->_top->prev = newNode;
      pqueue->_top = newNode;
    }
    else
    {
      pqueue->_top->next = newNode;
      newNode->prev = pqueue->_top;
      pqueue->_down = newNode;
    }
  }
  else
  {
    if (spd > pqueue->_top->_spd) {
      newNode->next = pqueue->_top;
      pqueue->_top->prev = newNode;
      pqueue->_top = newNode;
    }
    else {
      while ( temp->next != NULL && temp->next->_spd > spd)
        temp = temp->next;
      if (temp == pqueue->_down)
      {
        if (pqueue->_down->_spd > newNode->_spd)
        {
          // printf("flag 1\n");
          newNode->prev = pqueue->_down;
          pqueue->_down->next = newNode;
          pqueue->_down = newNode;
        }
        else
        {
          // printf("flag 2\n");
          newNode->prev = pqueue->_down->prev;
          pqueue->_down->prev->next = newNode;
          pqueue->_down->prev = newNode;
          newNode->next = pqueue->_down;
        }
      }
      else
      {
          // printf("flag 3\n");
        newNode->prev = temp;
        newNode->next = temp->next;
        temp->next->prev = newNode;
        temp->next = newNode; 
      }
    }
  }
}

void pqueue_popup(PriorityQueue *pqueue)
{
  if (!pqueue_isEmpty(pqueue)) {
    PQueueNode *temp = pqueue->_top;
    pqueue->_size--;

    if (pqueue->_top == pqueue->_down)
      pqueue->_top = pqueue->_down = NULL;
    else
    {
      pqueue->_top = pqueue->_top->next;
      pqueue->_top->prev = NULL;
    }
    free(temp);
  }
}

void pqueue_popdown(PriorityQueue *pqueue)
{
  if (!pqueue_isEmpty(pqueue)) {
    PQueueNode *temp;
    pqueue->_size--;

    if (pqueue->_top == pqueue->_down)
    {
      temp = pqueue->_top;
      pqueue->_top = pqueue->_down = NULL;
    }
    else
    {
      temp = pqueue->_down;
      pqueue->_down = pqueue->_down->prev;
      pqueue->_down->next = NULL;
    }
    free(temp);
  }
}

int pqueue_top(PriorityQueue *pqueue, int flag) {
  if (!pqueue_isEmpty(pqueue))
  {
    if (flag == 1)
      return pqueue->_top->_hp;
    else if (flag == 2)
      return pqueue->_top->_atk;
    else if (flag == 3)
      return pqueue->_top->_spd;
  }
  else return 0;
}

int pqueue_down(PriorityQueue *pqueue, int flag) {
  if (!pqueue_isEmpty(pqueue))
  {
    if (flag == 1)
      return pqueue->_down->_hp;
    else if (flag == 2)
      return pqueue->_down->_atk;
    else if (flag == 3)
      return pqueue->_down->_spd;
  }
  else return 0;
}

int main(int argc, char const *argv[])
{
  PriorityQueue player;
  PriorityQueue enemy;

  pqueue_init(&player);
  pqueue_init(&enemy);

  int jumlah_p;
  int jumlah_e;
  int jumlah;
  int i = 0;
  int hp, atk, spd;
  int j = 0;

  scanf("%d %d", &jumlah_p, &jumlah_e);

  jumlah = jumlah_e + jumlah_p;
  
  while (i < jumlah)
  {
    i++;

    scanf("%d %d %d", &hp, &atk, &spd);

    if (i <= jumlah_p)
      pqueue_push(&player, hp, atk, spd);
    else
      pqueue_push(&enemy, hp, atk, spd);
  }

  PQueueNode *en_player = player._top;
  PQueueNode *en_enemy = enemy._top;

  while (true)
  {
    ++j;

    if (player._size > enemy._size)
    {
      // printf("%d flag1\n", j);      
      if (j <= enemy._size)
      {
        // printf("..%d\n", j);
        en_enemy->_bar += en_enemy->_spd;
        
        if (en_enemy->_bar >= 100)
        {
          player._down->_hp -= en_enemy->_atk;

          if (player._down->_hp < 1)
            pqueue_popdown(&player);

          en_enemy->_bar -= 100;
        }

        if (en_enemy->next == NULL)
          en_enemy = enemy._top;
        else
          en_enemy = en_enemy->next;
      }
      // else if (j == player._size)
      //   j = 0;

      en_player->_bar += en_player->_spd;

      if (en_player->_bar >= 100)
      {
        enemy._down->_hp -= en_player->_atk;

        if (enemy._down->_hp < 1)
          pqueue_popdown(&enemy);
        
        en_player->_bar -= 100;
      }

      if (en_player->next == NULL)
      {
        j = 0;
        en_player = player._top;
      }
      else
        en_player = en_player->next;
    }
    else if (enemy._size > player._size)
    {
      // printf("%d flag2\n", j);      
      if (j <= player._size)
      {
        // printf(".... %d\n", j);
        en_player->_bar += en_player->_spd;

        if (en_player->_bar >= 100)
        {
          enemy._down->_hp -= en_player->_atk;

          if (enemy._down->_hp < 1)
            pqueue_popdown(&enemy);
          
          en_player->_bar -= 100;
        }

        if (en_player->next == NULL)
          en_player = player._top;
        else
          en_player = en_player->next;
      }
      // else if (j == enemy._size)
      //   j = 0;

      en_enemy->_bar += en_enemy->_spd;
      
      if (en_enemy->_bar >= 100)
      {
        player._down->_hp -= en_enemy->_atk;

        if (player._down->_hp < 1)
          pqueue_popdown(&player);

        en_enemy->_bar -= 100;
      }

      if (en_enemy->next == NULL)
      {
        j = 0;
        en_enemy = enemy._top;
      }
      else
        en_enemy = en_enemy->next;
    }
    else if (enemy._size == player._size)
    {
      // printf("%d flag3\n", j);
      en_enemy->_bar += en_enemy->_spd;
      en_player->_bar += en_player->_spd;

      if (en_player->_bar >= 100)
      {
        enemy._down->_hp -= en_player->_atk;

        if (enemy._down->_hp < 1)
          pqueue_popdown(&enemy);
        
        en_player->_bar -= 100;
      }
      
      if (en_enemy->_bar >= 100)
      {
        player._down->_hp -= en_enemy->_atk;

        if (player._down->_hp < 1)
          pqueue_popdown(&player);

        en_enemy->_bar -= 100;
      }

      if (en_player->next == NULL)
      {
        j = 0;
        en_player = player._top;
      }
      else
        en_player = en_player->next;

      if (en_enemy->next == NULL)
      {
        j = 0;
        en_enemy = enemy._top;
      }
      else
        en_enemy = en_enemy->next;
    }

    if (enemy._size < 1)
    {
      printf("You Won!\n");
      break;
    }
    if (player._size < 1)
    {
      printf("Game Over.\n");
      break;
    }
    
    // printf("%d \n",player._size);
    // printf("... %d\n", enemy._size);
  }

  return 0;
}
