# Description: solution 프로그램을 실행시켜서 data 폴더에 있는 데이터를 처리하고, 소요 시간을 측정하는 코드입니다.
import os
import subprocess
import time
import matplotlib.pyplot as plt


UNIT_EXPONENT = 2
EXPONENT = 3
DATA_NUM = 5
tot_linked = []
tot_heap = []
tot_bst = []

n_time = []


for N in range(1, DATA_NUM + 1):
    f = open(f"./data/data_{N}.txt", "r")
    lines = []
    result_linked = []
    result_heap = []
    result_bst = []
    tot_start = time.time()
    
    for i in range(10 ** (EXPONENT - UNIT_EXPONENT + 1)):
        lines.append(f.readline())
    

    for p in range(0,int(0.25*((10 ** ((EXPONENT - UNIT_EXPONENT) + 1))))+1, 5):
        n = (10 ** UNIT_EXPONENT) * p
        lines[0] = f"{n} {lines[0].split()[1]}\n"
        input_data = "".join(lines[:n+1])

        command = ["/Users/minseok/Library/CloudStorage/OneDrive-성균관대학교/SKKU/2nd_semester/자료구조개론/Project/code/output/solution_array"]
        process = subprocess.Popen(command, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
        output, _ = process.communicate(input=input_data)
        result_linked.append(float(output))
        print(f"{n}개 데이터 Linked list로 처리 완료\n 프로세스 소요 시간: {float(output)} 초")
        
        command = ["/Users/minseok/Library/CloudStorage/OneDrive-성균관대학교/SKKU/2nd_semester/자료구조개론/Project/code/output/solution_heap"]
        process = subprocess.Popen(command, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
        output, _ = process.communicate(input=input_data)
        result_heap.append(float(output))
        print(f"{n}개 데이터 Heap으로 처리 완료\n 프로세스 소요 시간: {float(output)} 초")
        
        
        command = ["/Users/minseok/Library/CloudStorage/OneDrive-성균관대학교/SKKU/2nd_semester/자료구조개론/Project/code/output/solution_bst"]
        process = subprocess.Popen(command, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
        output, _ = process.communicate(input=input_data)
        result_bst.append(float(output))
        print(f"{n}개 데이터 BST로 처리 완료\n 프로세스 소요 시간: {float(output)} 초")
        



    tot_end = time.time()
    print("프로세스 소요 시간: {:.4f} 초".format(tot_end - tot_start))

    plt.plot([10 ** UNIT_EXPONENT * p for p in range(0,int(0.25*((10 ** ((EXPONENT - UNIT_EXPONENT) + 1))))+1, 5 )], result_linked,'ro-', label=f"data_{N} Linked List", )
    plt.plot([10 ** UNIT_EXPONENT * p for p in range(0,int(0.25*((10 ** ((EXPONENT - UNIT_EXPONENT) + 1))))+1, 5 )], result_heap,'bo-', label=f"data_{N} Heap", )
    plt.plot([10 ** UNIT_EXPONENT * p for p in range(0,int(0.25*((10 ** ((EXPONENT - UNIT_EXPONENT) + 1))))+1, 5 )], result_bst,'go-', label=f"data_{N} BST", )

    plt.legend()
    plt.xlabel("N")
    plt.ylabel("Time")
    plt.title("Time Complexity")
    plt.savefig(f"time_complexity_{N}.png")
    if len(tot_linked) == 0:
        tot_linked = result_linked
    else:
        for i in range(len(tot_linked)):
            tot_linked[i] += result_linked[i]

    if len(tot_heap) == 0:
        tot_heap = result_heap
    else:
        for i in range(len(tot_heap)):
            tot_heap[i] += result_heap[i]
    
    if len(tot_bst) == 0:
        tot_bst = result_bst
    else:
        for i in range(len(tot_bst)):
            tot_bst[i] += result_bst[i]

    plt.clf() 
    plt.cla()

    f.close()

for i in range(len(tot_linked)):
    tot_linked[i] /= DATA_NUM

for i in range(len(tot_heap)):
    tot_heap[i] /= DATA_NUM

for i in range(len(tot_bst)):
    tot_bst[i] /= DATA_NUM

plt.plot([10 ** UNIT_EXPONENT * p for p in range(0,int(0.25*((10 ** ((EXPONENT - UNIT_EXPONENT) + 1))))+1, 5)], tot_linked, 'ro-', label="total linked list")
plt.plot([10 ** UNIT_EXPONENT * p for p in range(0,int(0.25*((10 ** ((EXPONENT - UNIT_EXPONENT) + 1))))+1, 5)], tot_heap, 'bo-', label="total heap")
plt.plot([10 ** UNIT_EXPONENT * p for p in range(0,int(0.25*((10 ** ((EXPONENT - UNIT_EXPONENT) + 1))))+1, 5)], tot_bst, 'go-', label="total BST")

plt.xlabel("N")
plt.ylabel("Time")
plt.title("Time Complexity")


plt.legend()



plt.savefig(f"time_complexity_total.png")
plt.clf()
plt.cla()


