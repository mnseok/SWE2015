#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int time;
    int counterId;
} Customer;

typedef struct {
    Customer* array;
    int capacity;
    int size;
} CustomerPriorityQueue;

// 우선순위 큐 초기화
CustomerPriorityQueue* initCustomerPriorityQueue(int capacity) {
    CustomerPriorityQueue* pq = (CustomerPriorityQueue*)malloc(sizeof(CustomerPriorityQueue));
    pq->array = (Customer*)malloc(capacity * sizeof(Customer));
    pq->capacity = capacity;
    pq->size = 0;
    return pq;
}

// 두 원소의 우선순위를 비교하는 함수
int customer_compareNodes(Customer* a, Customer* b) {
    // time가 우선
    if (a->time < b->time) {
        return -1;
    } else if (a->time > b->time) {
        return 1;
    } else {
        // time가 같으면 counterId로 비교
        if (a->counterId > b->counterId) {
            // counterId가 클수록 우선순위가 높음
            return -1;
        } else if (a->counterId < b->counterId) {
            // counterId가 작을수록 우선순위가 낮음
            return 1;
        } else {
            return 0; // 두 기준이 모두 같을 경우
        }
    }
}

// 원소를 우선순위 큐에 삽입
void customer_enqueue(CustomerPriorityQueue* pq, int id, int time, int counterId) {
    if (pq->size == pq->capacity) {
        // 큐가 꽉 찼을 경우 예외 처리 (크기를 동적으로 늘리거나 예외 처리 방법을 선택)
        printf("CustomerPriorityQueue is full.\n");
        return;
    }

    Customer newNode = {id, time, counterId};
    int index = pq->size;
    pq->array[index] = newNode;
    pq->size++;

    // 삽입한 원소를 우선순위에 따라 재배열
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (customer_compareNodes(&pq->array[index], &pq->array[parentIndex]) < 0) {
            // 부모와 비교하여 우선순위가 더 높다면 교환
            Customer temp = pq->array[index];
            pq->array[index] = pq->array[parentIndex];
            pq->array[parentIndex] = temp;
            index = parentIndex;
        } else {
            break; // 우선순위가 올바르게 정렬되었으면 종료
        }
    }
}

// 우선순위 큐에서 원소를 추출
Customer customer_dequeue(CustomerPriorityQueue* pq) {
    if (pq->size == 0) {
        // 큐가 비어있을 경우 예외 처리
        printf("CustomerPriorityQueue is empty.\n");
        Customer emptyNode = {0, 0, 0};
        return emptyNode;
    }

    Customer removedNode = pq->array[0];
    pq->size--;

    // 마지막 원소를 루트로 이동하고 우선순위에 따라 재배열
    pq->array[0] = pq->array[pq->size];
    int index = 0;
    while (1) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int minIndex = index;

        if (leftChild < pq->size && customer_compareNodes(&pq->array[leftChild], &pq->array[minIndex]) < 0) {
            minIndex = leftChild;
        }
        if (rightChild < pq->size && customer_compareNodes(&pq->array[rightChild], &pq->array[minIndex]) < 0) {
            minIndex = rightChild;
        }

        if (minIndex != index) {
            // 자식 중 우선순위가 더 높다면 교환
            Customer temp = pq->array[index];
            pq->array[index] = pq->array[minIndex];
            pq->array[minIndex] = temp;
            index = minIndex;
        } else {
            break; // 우선순위가 올바르게 정렬되었으면 종료
        }
    }

    return removedNode;
}


void printCustomerPriorityQueue(CustomerPriorityQueue* pq) {
    printf("\n-----------------------------------------\n");
    // printf("size: %d\n", pq->size);
    for (int i = 0; i < pq->size; i++) {
        printf("id: %4d | time: %4d | counter id: %4d\n", pq->array[i].id, pq->array[i].time, pq->array[i].counterId);
    }
    printf("-----------------------------------------\n");
    printf("\n");
}