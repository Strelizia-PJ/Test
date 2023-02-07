#include <stdio.h>
#include <stdlib.h>

// 宏定义通用类型的deque 
#define DEQUE_TYPE(T) \
  typedef struct DequeNode_##T { \
    T data; \
    struct DequeNode_##T *prev; \
    struct DequeNode_##T *next; \
  } DequeNode_##T; \
  typedef struct Deque_##T { \
    DequeNode_##T *head; \
    DequeNode_##T *tail; \
    int size; \
  } Deque_##T; \
  Deque_##T *deque_create_##T() { \
    Deque_##T *deque = (Deque_##T *)malloc(sizeof(Deque_##T)); \
    deque->head = NULL; \
    deque->tail = NULL; \
    deque->size = 0; \
    return deque; \
  } \
  void deque_push_front_##T(Deque_##T *deque, T data) { \
    DequeNode_##T *node = (DequeNode_##T *)malloc(sizeof(DequeNode_##T)); \
    node->data = data; \
    node->prev = NULL; \
    node->next = deque->head; \
    if (deque->head) { \
      deque->head->prev = node; \
    } \
    deque->head = node; \
    if (!deque->tail) { \
      deque->tail = node; \
    } \
    deque->size++; \
  } \
  void deque_push_back_##T(Deque_##T *deque, T data) { \
    DequeNode_##T *node = (DequeNode_##T *)malloc(sizeof(DequeNode_##T)); \
    node->data = data; \
    node->prev = deque->tail; \
    node->next = NULL; \
    if (deque->tail) { \
      deque->tail->next = node; \
    } \
    deque->tail = node; \
    if (!deque->head) { \
      deque->head = node; \
    } \
    deque->size++; \
  } \
  T deque_pop_front_##T(Deque_##T *deque) { \
    if (!deque->head) { \
      return (T)0; \
    } \
    DequeNode_##T *node = deque->head; \
    deque->head = node->next; \
    if (deque->head) { \
      deque->head->prev = NULL; \
    } \
    if (node == deque->tail) { \
      deque->tail = NULL; \
    } \
    T data = node->data; \
    free(node); \
    deque->size--; \
    return data; \
  } \
  T deque_pop_back_##T(Deque_##T *deque) { \
    if (!deque->tail) { \
      return (T)0; \
    } \
    DequeNode_##T *node = deque->tail; \
    deque->tail = node->prev; \
    if (deque->tail) { \
      deque->tail->next = NULL; \
    } \
    if (node == deque->head) { \
      deque->head = NULL; \
    } \
    T data = node->data; \
    free(node); \
    deque->size--; \
    return data; \
  } \
  int deque_empty_##T(Deque_##T *deque) { \
    return deque->size == 0; \
  } \
  int deque_size_##T(Deque_##T *deque) { \
    return deque->size; \
  } \
  T deque_front_##T(Deque_##T *deque) { \
    if (!deque->head) { \
      return (T)0; \
    } \
    return deque->head->data; \
  } \
  T deque_back_##T(Deque_##T *deque) { \
    if (!deque->tail) { \
      return (T)0; \
    } \
    return deque->tail->data; \
  } \
  void deque_clear_##T(Deque_##T *deque) { \
    while (!deque_empty_##T(deque)) { \
      deque_pop_front_##T(deque); \
    } \
  } \
  void deque_destroy_##T(Deque_##T *deque) { \
    deque_clear_##T(deque); \
    free(deque); \
  }


#include <stdio.h>
#include <stdlib.h>

DEQUE_TYPE(int);
DEQUE_TYPE(float);

int main() {
  // 创建双端队列
  Deque_int *deque_int = deque_create_int();
  Deque_float *deque_float = deque_create_float();

  // 向队列中插入数据
  deque_push_front_int(deque_int, 123);
  deque_push_front_int(deque_int, 456);
  deque_push_back_float(deque_float, 3.14);
  deque_push_back_float(deque_float, 6.28);

  // 从队列中弹出数据
  int data_int = deque_pop_front_int(deque_int);
  float data_float = deque_pop_back_float(deque_float);
  printf("Popped data: %d, %f\n", data_int, data_float);

  // 判断队列是否为空
  if (deque_empty_int(deque_int)) {
    printf("Deque_int is empty!\n");
  }
  if (deque_empty_float(deque_float)) {
    printf("Deque_float is empty!\n");
  }

  // 获取队列的大小
  int size_int = deque_size_int(deque_int);
  int size_float = deque_size_float(deque_float);
  printf("Deque size: %d, %d\n", size_int, size_float);

  // 获取队列的队头和队尾元素
  int front_int = deque_front_int(deque_int);
  float front_float = deque_front_float(deque_float);
  int back_int = deque_back_int(deque_int);
  float back_float = deque_back_float(deque_float);
  printf("Deque_int front and back: %d, %d\n", front_int, back_int);
  printf("Deque_float front and back: %f, %f\n", front_float, back_float);
  
  // 清空队列
  deque_clear_int(deque_int);
  deque_clear_float(deque_float);

  // 销毁队列
  deque_destroy_int(deque_int);
  deque_destroy_float(deque_float);
  return 0;
}

/*
在插入和删除元素时，需要使用动态内存分配，因此时间复杂度是 O(1)，空间复杂度是 O(n)。

在遍历队列时，时间复杂度是 O(n)，空间复杂度是 O(1)。

在特殊情况下，可以考虑使用循环队列来优化时间复杂度。例如，在遍历队列时，时间复杂度可以降低到 O(1)。但是，这需要维护一个额外的数组来存储队列数据，因此空间复杂度也会变成 O(n)。

在实现双端队列时，也可以使用其他数据结构来优化性能，例如双向链表。双向链表可以在 O(1) 的时间内完成插入和删除操作，但是需要使用额外的指针来维护链表，因此空间复杂度会变成 O(n)。

*/

