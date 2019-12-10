import numpy as np
import random
import matplotlib.pyplot as plt
import time
start_time = time.time()

run_type = input().strip()
N = int(input().strip())
nodes = {}
for i in range(N):
    temp = input().strip().split()
    nodes[i] = (float(temp[0]), float(temp[1]))
distance_matrix = np.zeros(shape=(N,N))
for i in range(N):
    temp = input().strip().split()
    for j in range(len(temp)):
        distance_matrix[i][j] = float(temp[j])

MAX_VAL = 1000000  
tree = np.zeros(shape=(N,N))
tree_generator = False
#MST Path from DFS
def DFS(i, visited,path):
    path.append(i)
    visited[i] = True
    for j in range(0,N):
        if visited[j]!= True and tree[i][j] == 1:
            DFS(j,visited,path)    

def MSTPath():
    global tree_generator
    if tree_generator == False:
        primMST()
        tree_generator = True
    visited = [False] * N
    start = random.randint(0,N-1)
    path = []
    DFS(start,visited,path)
    return path
   
def minKey(key, mstSet):
    minval = MAX_VAL
    for v in range(N):
        if key[v] < minval and mstSet[v] == False:
            minval = key[v]
            min_index = v
    return min_index

def primMST():
    key = [MAX_VAL] * N
    parent = [None] * N
    mstSet = [False] * N
    key[0] = 0
    parent[0] = -1
   
    for i in range(0,N-1):
        u = minKey(key,mstSet)
        mstSet[u] = True
        for v in range(0,N):
            if distance_matrix[u][v]>0 and mstSet[v] == False and key[v] > distance_matrix[u][v]:
                parent[v] = u
                key[v] = distance_matrix[u][v];
               
    for i in range(1,N):
        tree[parent[i]][i] = 1
        tree[i][parent[i]] = 1

#Greedy Algo
def greedy_algo():
    currentCity = random.randint(0,N-1)
    ans = [-1 for i in range(N)]
    visited = [0 for i in range(N)]
    ans[0] = currentCity
    count = 1
    visited[currentCity] = 1
    while(count<N):
        neighbour = -1
        min_dis = MAX_VAL
        for i in range(N):
            if(i!=currentCity and visited[i]==0 and min_dis>distance_matrix[currentCity][i]):
                min_dis = distance_matrix[currentCity][i]
                neighbour = i
        currentCity = neighbour
        ans[count] = neighbour
        visited[neighbour] = 1
        count+=1
    return ans

def Greedy_algo():
    currentCity = random.randint(0,N-1)
    ans = []
    ans.append(currentCity)
    count = 1
    visited = np.zeros(N)
    visited[currentCity] = 1
    min_dis = 1000000
    neighbour = -1
    for i in range(N):
        if(i!=currentCity and visited[i]==0 and min_dis>distance_matrix[currentCity][i]):
            min_dis = distance_matrix[currentCity][i]
            neighbour = i
    if(neighbour!=-1):
        ans.append(neighbour)
        visited[neighbour] = 1
        count+=1
    while(count<N):
        min_dis1 = 1000000
        neighbour = -1
        loc_index = -1
        for j in range(N):
            if(visited[j] == 0):
                min_dis2 = 1000000
                index = -1
                for i in range(len(ans)+1):
                    if(i==0):
                        if(min_dis2>distance_matrix[ans[0]][j]):
                            min_dis2  = distance_matrix[ans[0]][j]
                            index = 0
                    elif(i==len(ans)):
                        if(min_dis2>distance_matrix[ans[-1]][j]):
                            min_dis2 = distance_matrix[ans[-1]][j]
                            index = len(ans)
                    else:
                        temp = distance_matrix[ans[i-1]][j]+distance_matrix[j][ans[i]]-distance_matrix[ans[i]][ans[i-1]]
                        if(min_dis2>temp):
                            min_dis2 = temp
                            index = i
                if(min_dis1>min_dis2):
                    min_dis1 = min_dis2
                    neighbour = j
                    loc_index = index
        ans.insert(loc_index,neighbour)
        visited[neighbour] = 1
        count+=1
    return ans    

#Random Generator
def random_algo():
    ans = random.sample([i for i in range(N)],N)
    return ans

def evaluation(x):
    check = np.zeros(N)
    for i in range(len(x)):
        check[int(x[i])]+=1
    correct_path = True
    for i in range(N):
        if(check[i]!=1):
            correct_path = False
            break
    if(correct_path == False):
        print('Invalid Path')
        return -1
    else:
        dis = 0
        for i in range(len(x)-1):
            dis+=(distance_matrix[int(x[i])][int(x[i+1])])
        dis+=distance_matrix[int(x[-1])][int(x[0])]
        return dis

def best_of_two_edge_exchange(pop):
    temp2 = dist_of_route(pop)
    # print(temp2)
    temp3 = 1000000
    while(temp2 <temp3):
        temp3 = temp2 
        pop = two_edge_exchange(pop)
        # print(pop)
        temp2 = dist_of_route(pop)
        # print(temp2)
    return pop

#Initial Population
def init_pop(k):
    population = []
    #primemst
    for i in range(int((k)/5)):
        population.append(MSTPath())
    for i in range(int(k/5)):
        population.append(random_algo())
    for i in range(int(3*k/5)-2):
        population.append(greedy_algo())
    population.append(Greedy_algo())
    population.append(Greedy_algo())
    # for i in range(len(population)):
    #     population[i] = two_edge_exchange(population[i])
    return population

#Path_Distance    
def dist_of_route(route):
    ans = 0
    for i in range(len(route)-1):
        ans+=(distance_matrix[route[i]][route[i+1]])
    ans+=distance_matrix[route[-1]][route[0]]
    return ans
     
#Selection based on probab-Roulette Wheel
def selection(population):
    fitness = []
    for i in range(0,len(population)):
        fitness.append(1/dist_of_route(population[i]))
    fitness = (fitness/sum(fitness))
    fit_tuple = []
    for i in range(0,len(population)):
        fit_tuple.append([fitness[i],i])
    fit_tuple = sorted(fit_tuple,reverse = True)
    cumsum = 0
    for i in range(len(population)):
        cumsum += fit_tuple[i][0]
        fit_tuple[i][0] = cumsum
    for i in range(len(population)):
        fit_tuple[i][0] /= cumsum

    results = []
    for i in range(len(population)):
        pick = random.random()
        for j in range(len(population)):
            if pick <= fit_tuple[j][0]:
                results.append(population[fit_tuple[j][1]])
                break
    random.shuffle(results)      
    return results

#Crossovers
def pmx(parent1, parent2):
    child = []
    childP1 = []
    childP2 = []
   
    geneA = int(random.random() * len(parent1))
    geneB = int(random.random() * len(parent1))
   
    startGene = min(geneA, geneB)
    endGene = max(geneA, geneB)

    for i in range(startGene, endGene):
        childP1.append(parent1[i])
       
    childP2 = [item for item in parent2 if item not in childP1]

    child = childP1 + childP2
    return child  

def nwox(parent1, parent2):
    child1 = parent1.copy()
    child2 = parent2.copy()
   
    geneA = int(random.random() * len(parent1))
    geneB = int(random.random() * len(parent1))
   
    startGene = min(geneA, geneB)
    endGene = max(geneA, geneB)

    l1 = parent1[startGene:endGene+1]
    l2 = parent2[startGene:endGene+1]
    count = 0
    final1 = []
    final2 = []
    for i in range(len(parent1)):
        if(child1[i] not in l2):
            final1.append(child1[i])
    final1 = final1[:startGene]+l2+final1[startGene:]
    for i in range(len(parent2)):
        if(child2[i] not in l1):
            final2.append(child2[i])
    final2 = final2[:startGene]+l1+final2[startGene:]
    return final1,final2

#2-opt
def two_edge_exchange(route):
    dis = dist_of_route(route)
    min_dis = dis
    count = 0
    new_route = route.copy()
    for i in range(N-1):
        for j in range(i+1,N):
            if(i == 0  and j == N-1):
                continue
            temp = dis
            temp-=distance_matrix[route[i]][route[(i+N-1)%N]]
            temp-=distance_matrix[route[j]][route[(j+1)%N]]
            temp+=distance_matrix[route[j]][route[(i+N-1)%N]]
            temp+=distance_matrix[route[i]][route[(j+1)%N]]
            if(temp<min_dis):
                new_route = route.copy()
                new_route[i:j+1] = new_route[i:j+1][::-1]
                min_dis = temp
                # print(new_route,min_dis)
    return new_route

def dist_sort(population):
    fitness = []
    for i in range(0,len(population)):
        fitness.append(1/dist_of_route(population[i]))
    fitness = (fitness/sum(fitness))
    fit_tuple = []
    for i in range(0,len(population)):
        fit_tuple.append([fitness[i],i])
    fit_tuple = sorted(fit_tuple,reverse = True)

    results = []
    for x in fit_tuple:
        results.append(population[x[1]])
    return results


def mutate(path, mutationRate):
    for swapped in range(len(path)):
        if(random.random() < mutationRate):
            swapWith = int(random.random() * len(path))
           
            c1 = path[swapped]
            c2 = path[swapWith]
           
            path[swapped] = c2
            path[swapWith] = c1
    return path

def nextGen(results):
    next_gen = []

    #Crossover
    results = random.sample(results,len(results))
    for i in range(int(len(results)/2)):
        child1,child2 = nwox(results[2*i],results[(2*i)+1])
        next_gen.append(child1)

    #Elitism
    results = dist_sort(results)
    elite = len(results) // 2
    next_gen += results[:elite]

    #Mutation
    for i in range(elite):
        next_gen[i] = two_edge_exchange(next_gen[i])
    return next_gen

def min_dist(population):
    minval = MAX_VAL
    for path in population:
        t = dist_of_route(path)
        if(t < minval):
            minval = t
            ans = path
    return minval,ans


best_dist = MAX_VAL
for _ in range(5):
    t = best_of_two_edge_exchange(greedy_algo())
    d = dist_of_route(t)
    if(d < best_dist):
        print(*t)
        best_dist = d

for _ in range(100):
    gen = 30
    pop = init_pop(50)
    while(gen > 0):
        pop = nextGen(selection(pop))
        t,route = min_dist(pop)
        if(t < best_dist):
            best_dist = t
            print(*route)
        # print(t)
        gen -= 1

# print(best_dist)
#print("Best route eval ", evaluation(best_route))
# plt.plot(range(100),y)
# plt.xlabel("No. of Generations")
# plt.ylabel("Tour cost")
# plt.title("Non-Euclidean: 250 nodes")
# plt.show()



