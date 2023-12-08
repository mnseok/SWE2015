#include <stdlib.h>
#include <stdio.h>

typedef struct Customer {
    int id;
    int time;
    int counterId;

    struct  Customer* left;
    struct  Customer* right;

} Customer;

typedef struct {
    Customer* root;
    int size;
} CustomerPriorityQueue;

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

// 우선순위 큐 초기화
CustomerPriorityQueue* initCustomerPriorityQueue() {
    CustomerPriorityQueue* pq = (CustomerPriorityQueue*)malloc(sizeof(CustomerPriorityQueue));
    pq->root = NULL;
    pq->size = 0;
    return pq;
}

// 이진 탐색 트리에 노드 삽입
Customer* insert(Customer* root, Customer* newNode) {
    if (root == NULL) {
        return newNode;
    }

    if (customer_compareNodes(newNode, root) == -1) {
        root->left = insert(root->left, newNode);
    } else {
        root->right = insert(root->right, newNode);
    }

    return root;
}

// 원소를 우선순위 큐에 삽입
void customer_enqueue(CustomerPriorityQueue* pq, int id, int time, int counterId) {
    Customer* newNode = (Customer*)malloc(sizeof(Customer));
    newNode->id = id;
    newNode->time = time;
    newNode->counterId = counterId;
    newNode->left = NULL;
    newNode->right = NULL;

    pq->root = insert(pq->root, newNode);
    pq->size++;
}

// 가장 우선순위가 높은 노드 찾기
Customer* find_highest(Customer* root) {
    if (root == NULL) {
        return NULL;
    }

    while (root->right != NULL) {
        root = root->right;
    }

    return root;
}
// 가장 우선순위가 높은 원소를 큐에서 제거하고 반환
Customer customer_dequeue(CustomerPriorityQueue* pq) {
    if (pq->size == 0) {
        // 큐가 비어있을 경우 예외 처리
        printf("CustomerPriorityQueue is empty.\n");
        exit(-1);
    }

    // 가장 우선순위가 높은 원소를 찾음
    Customer* highestParent = NULL;
    Customer* highest = find_highest(pq->root);

    // 가장 우선순위가 높은 원소의 부모를 찾음
    if (highest != pq->root) {
        highestParent = pq->root;
        while (highestParent->right != highest) {
            highestParent = highestParent->right;
        }
    }

    // 찾은 노드를 삭제하고 해당 서브트리를 조정
    Customer highestCustomer;
    if (highest->right == NULL) {
        if (highestParent != NULL) {
            highestParent->right = highest->left;
        } else {
            pq->root = highest->left;
        }
        highestCustomer = *highest;
    } else {
        if (highestParent != NULL) {
            highestParent->right = highest->right;
        } else {
            pq->root = highest->right;
        }
        if (highest->left != NULL) {
            // 가장 우선순위가 높은 원소의 오른쪽 서브트리에 왼쪽 서브트리를 붙임
            Customer* temp = highest->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            temp->left = highest->left;
        }
        highestCustomer = *highest;
    }

    free(highest);
    pq->size--;

    return highestCustomer;
}
