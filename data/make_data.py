import random
import time

SEED = 0

for (SEED) in range(5):
    f=open(f"./data/data_{SEED+1}.txt","w")

    random.seed(SEED)
    n = 100000
    k = random.randint(1,30)

    f.write(str(n)+" "+str(k)+"\n")

    start_time = time.time()
    data = []
    for i in range(n):
        data.append(str(i)+" "+str(random.randint(1,50))+"\n")

    end_time = time.time()
    print(f"{SEED+1}번째 데이터 생성 완료 ({n}개) 소요 시간: {end_time-start_time}")
    print("data assigned")
    print(data[:10])


    # random.shuffle(data)
    # print("data shuffled")
    # print(data[:10])
    for i in range(n):
        # print(data[i])
        f.write(data[i])

    f.close()