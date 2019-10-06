import sys, random, time
import numpy as np

def main(argv):
    N = int(argv[0])
    command = argv[1]
    
    
    #create ages
    ages = random.sample(range(100), N)

    #create edges
    '''possiveis = np.array([
        np.array([(i, j) for j in range(i + 1, random.randint(i+1, N))])
        for i in range(N-1)
    ])'''
    possiveis = np.vstack([
        np.array([(i, j) for j in range(i + 1, N)])
        for i in range(N - 1)
    ])
    random.seed(time.time_ns())
    np.random.shuffle(possiveis)
    M = random.randint(N - 1, round(N * (N - 1) / 4))
    arestas = possiveis[:M]
    mapeamento = np.random.permutation(N)
    arestas = list(map(
        lambda x: (mapeamento[x[0]], mapeamento[x[1]]),
        arestas
    ))
    # M = len(arestas)

    if(command == 'C'): v = list(random.randint(1, N) for _ in range(1000))
    elif(command == 'S'): v = swap(5*M, arestas)
    elif(command == 'M'): v = list('' for _ in range(100))

    I = len(v)
    print(str(N)+' '+str(M)+' '+str(I))

    # for age in ages: print(age)
    print(" ".join(str(age) for age in ages))

    for a in arestas:
        print(a[0] + 1, a[1] + 1)

    for i in v:
        print(command+ ' ' + str(i))


def swap(I, edges):
    v = list()
    lenth_edges = len(edges)
    for _ in range(I):
        random.seed(time.time_ns())
        index = random.randint(0, lenth_edges-1)
        x = random.randint(0, 1)
        v.append(str(edges[index][x&1]+1)+' '+str(edges[index][(x+1)&1]+1))
    return v

if __name__ == "__main__":
   main(sys.argv[1:])
