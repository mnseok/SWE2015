#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int time;
    int id;
} Counter;

typedef struct {
    Counter* array;
    int capacity;
    int size;
} CounterPriorityQueue;

// 우선순위 큐 초기화
CounterPriorityQueue* initCounterPriorityQueue(int capacity) {
    CounterPriorityQueue* pq = (CounterPriorityQueue*)malloc(sizeof(CounterPriorityQueue));
    pq->array = (Counter*)malloc(capacity * sizeof(Counter));
    pq->capacity = capacity;
    pq->size = 0;

    for (int i = 0; i < capacity; i++) {
        pq->array[i].id = i + 1;
        pq->array[i].time = 0;
        pq->size++;
    }
    return pq;
}

// 두 원소의 우선순위를 비교하는 함수
int counter_compareNodes(Counter* a, Counter* b) {
    // time가 우선
    if (a->time < b->time) {
        return -1;
    } else if (a->time > b->time) {
        return 1;
    } else {
        // time가 같으면 id로 비교
        if (a->id < b->id) {
            // id가 작을수록 우선순위가 높음
            return -1;
        } else if (a->id > b->id) {
            // id가 클수록 우선순위가 낮음
            return 1;
        } else {
            return 0; // 두 기준이 모두 같을 경우
        }
    }
}

// 원소를 우선순위 큐에 삽입
void counter_enqueue(CounterPriorityQueue* pq, int time, int id) {
    if (pq->size == pq->capacity) {
        // 큐가 꽉 찼을 경우 예외 처리 (크기를 동적으로 늘리거나 예외 처리 방법을 선택)
        printf("CounterPriorityQueue is full.\n");
        return;
    }

    Counter newNode = {time, id};
    int index = pq->size;
    pq->array[index] = newNode;
    pq->size++;

    // 삽입한 원소를 우선순위에 따라 재배열
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (counter_compareNodes(&pq->array[index], &pq->array[parentIndex]) < 0) {
            // 부모와 비교하여 우선순위가 더 높다면 교환
            Counter temp = pq->array[index];
            pq->array[index] = pq->array[parentIndex];
            pq->array[parentIndex] = temp;
            index = parentIndex;
        } else {
            break; // 우선순위가 올바르게 정렬되었으면 종료
        }
    }
}

// 우선순위 큐에서 원소를 추출
Counter counter_dequeue(CounterPriorityQueue* pq) {
    if (pq->size == 0) {
        // 큐가 비어있을 경우 예외 처리
        printf("CounterPriorityQueue is empty.\n");
        Counter emptyNode = {0, 0};
        return emptyNode;
    }

    Counter removedNode = pq->array[0];
    pq->size--;

    // 마지막 원소를 루트로 이동하고 우선순위에 따라 재배열
    pq->array[0] = pq->array[pq->size];
    int index = 0;
    while (1) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int minIndex = index;

        if (leftChild < pq->size && counter_compareNodes(&pq->array[leftChild], &pq->array[minIndex]) < 0) {
            minIndex = leftChild;
        }
        if (rightChild < pq->size && counter_compareNodes(&pq->array[rightChild], &pq->array[minIndex]) < 0) {
            minIndex = rightChild;
        }

        if (minIndex != index) {
            // 자식 중 우선순위가 더 높다면 교환
            Counter temp = pq->array[index];
            pq->array[index] = pq->array[minIndex];
            pq->array[minIndex] = temp;
            index = minIndex;
        } else {
            break; // 우선순위가 올바르게 정렬되었으면 종료
        }
    }

    return removedNode;
}


void printCounterPriorityQueue(CounterPriorityQueue* pq) {
    printf("\nㄷ----------------------\n");
    // printf("size: %d\n", pq->size);
    for (int i = 0; i < pq->size; i++) {
        printf("id: %4d | time: %4d\n", pq->array[i].id, pq->array[i].time);
    }
    printf("----------------------\n");
    printf("\n");
}