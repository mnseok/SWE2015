#include <stdio.h>
#include <stdlib.h>

typedef struct Customer {
    int id;
    int time;
    int counterId;
    struct  Customer* next;
} Customer;

typedef struct {
    Customer* data;
    int size;
} CustomerPriorityQueue;

// 우선순위 큐 초기화
CustomerPriorityQueue* initCustomerPriorityQueue(int capacity) {
    CustomerPriorityQueue* pq = (CustomerPriorityQueue*)malloc(sizeof(CustomerPriorityQueue));
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
    if (pq->size == 0) {
        Customer* newNode = (Customer*)malloc(sizeof(Customer));
        newNode->id = id;
        newNode->time = time;
        newNode->counterId = counterId;
        newNode->next = NULL;
        pq->data = newNode;
        pq->size++;
    }

    Customer* newNode = (Customer*)malloc(sizeof(Customer));
    newNode->id = id;
    newNode->time = time;
    newNode->counterId = counterId;
    newNode->next = NULL;

    Customer* cur = pq->data;
    while (cur->next != NULL && customer_compareNodes(cur, newNode) < 0) {
        cur = cur->next;
    }

    newNode->next = cur->next;
    cur->next = newNode;
    pq->size++;
}

// 우선순위 큐에서 원소를 삭제하고 반환
Customer customer_dequeue(CustomerPriorityQueue* pq) {
    if (pq->size == 0) {
        // 큐가 비어있을 경우 예외 처리
        printf("CustomerPriorityQueue is empty.\n");
        exit(-1);
    }

    Customer ret = *(pq->data);
    if (pq->data->next != NULL) {
        pq->data = pq->data->next;
    } else {
        pq->data = NULL;
    }
    pq->size--;

    return ret;
}