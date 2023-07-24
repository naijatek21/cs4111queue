#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

/*
    This is your test file.
*/

// Test 1 is given to you
void test1()
{
  queue_t new = queue_new();
  if (new == NULL)
  {
    fprintf(stderr, "test1: queue_new failed\n");
    exit(1);
  }
  int r = queue_free(new);
  if (r != 0)
  {
    fprintf(stderr, "test1: queue_free() returned %d instead of 0\n", r);
    exit(1);
  }
}
void print_item(void *item, void *ctk)
{
  printf("%d\n", *(int *)item);
}
void print_q(queue_t q)
{
  queue_iterate(q, print_item, NULL);
}
void eq_test()
{
  queue_t q = queue_new();
  int *bin;
  int *one = malloc(sizeof(int));
  *one = 1;
  queue_enqueue(q, one);
  if (queue_length(q) != 1)
  {
    fprintf(stderr, " size doesn't update from empty to 1 \n");
    exit(1);
  }

  int i = (queue_dequeue(q, &bin));
  if (queue_length(q) != 0)
  {
    fprintf(stderr, " size doesn't update from 1 to empty \n");
    exit(1);
  }

  queue_enqueue(q, one);
  int *two = malloc(sizeof(int));
  *two = 2;
  queue_enqueue(q, two);
  if (queue_length(q) != 2)
  {
    fprintf(stderr, "eq_test: size doesn't update \n");
    exit(1);
  }
  int j = (queue_dequeue(q, &bin));
  // fprintf(stderr, "%d/n", *(int *)bin);
  // print_q(q);
  // fprintf(stdout, "binnnnn %d\n", *bin);
  if (bin != one)
  {

    fprintf(stderr, "First enque element doesn't matches \n");
    exit(1);
  }
  int k = (queue_dequeue(q, &bin));
  if (*(int *)(bin) != 2)
  {
    fprintf(stderr, "second enque element matches \n");
    exit(1);
  }
}
void dq_test()
{
  queue_t q = queue_new();
  int *bin;
  int r1 = queue_dequeue(q, &bin);
  if (r1 != -1)
  {
    fprintf(stderr, "DQ test : empty queue doesn't return -1");
    exit(1);
  }
  int *zero = (int *)malloc(sizeof(int));
  *zero = 0;
  queue_enqueue(q, zero);
  int *one = (int *)malloc(sizeof(int));
  *one = 1;
  queue_enqueue(q, one);
  int r2 = queue_dequeue(q, &bin);
  if (r2 != 0)
  {
    fprintf(stderr, "dq_test:Doesn't update result");
    exit(1);
  }
  if (bin != zero)
  {
    fprintf(stderr, "dq_test:Doesn't store dequed");
    exit(1);
  }
  if (queue_length(q) != 1)
  {
    fprintf(stderr, "dq_test: size doesn't decerement to 1 \n");
    exit(1);
  }
}

void inst_test()
{
  queue_t q = queue_new();
  int *zero = (int *)malloc(sizeof(int));
  *zero = 0;
  int *one = (int *)malloc(sizeof(int));
  *one = 1;
  int *bin;
  queue_enqueue(q, zero);
  queue_insert(q, one);
  int r1 = queue_dequeue(q, &bin);
  if (bin != one)
  {
    fprintf(stderr, "ins_test:element in wrong order\n");
    exit(1);
  }
}
void del_test()
{
  queue_t q = queue_new();
  int *zero = (int *)malloc(sizeof(int));
  *zero = 0;
  int *one = (int *)malloc(sizeof(int));
  *one = 1;
  int *two = (int *)malloc(sizeof(int));
  *two = 2;
  int *bin;

  queue_enqueue(q, zero);
  queue_insert(q, one);
  queue_insert(q, two);
  queue_delete(q, one);
  print_q(q);
  int r1 = queue_dequeue(q, &bin);

  if (bin != two)
  {
    fprintf(stderr, "didn't remove one \n");
    exit(1);
  }

  int r2 = queue_dequeue(q, &bin);

  if (bin != zero)
  {
    fprintf(stderr, "element in wrong order\n");
    exit(1);
  }
}

int main(void)
{
  test1();
  eq_test();
  dq_test();
  inst_test();
  del_test();
  return 0;
}
