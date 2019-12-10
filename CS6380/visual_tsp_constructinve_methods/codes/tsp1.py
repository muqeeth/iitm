import sys
from pprint import pprint
from PyQt5.QtWidgets import QMainWindow, QAction, qApp, QApplication, QPushButton
from PyQt5.QtGui import QIcon
import pickle
from PyQt5.QtWidgets import QWidget, QApplication, QLabel, QPlainTextEdit
from PyQt5.QtGui import QPainter, QPen
from PyQt5.QtCore import Qt
from PyQt5.QtCore import QSize
import sys, random
import pickle
import random
import numpy as np
import scipy.spatial
from PyQt5.QtCore import QPoint
import collections
import math
import time
import heapq
import tkinter as tk
import copy

root = tk.Tk()
screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()

global tri

open_sets = dict()
closed_sets = dict()
paths = dict()

iteration = 0
counter = 0

closed_set = set()
open_set = set()

points = []
dict_index_coord = {}
dict_coord_index = {}
edge_list = []
adjacency_list = []
node_colour = []
result_path = []

PRINT_RESULTS = False


## function to generate the next move
def movegen(adj, n_ind):
    return adj[n_ind]

#This is where you have to write you solution, according to the assignment which was given to you
#Points is list of structure which has x_coord, y_coord, isMax(if True then the node is Max node), level(Root at level 0)
#Edge List is the list of edges connecting the points mentioned above, you will need this when you have to color the edge for showing step by step representation
#Paths and open sets and closed_sets is a dictionary, after each iteration in Paths insert the edge from the edge_list which you want to colour
#open_sets and closed_sets is also a dictionary which will contain the index of the Point from list points

#Counter is the number of iterations it took, For eg: if counter is 5, you have to add your step by step solution in paths and visited_set as
#paths[0].....path[4] and open_sets[0]...open_sets[4] and closed_sets[0]...closed_sets[4]. This can be viewed as an animation in every mouse press event.

## If you are given a TSP algorithm, Please edit this function below to write your answer
def isCyclicUtil(v,newadj,visited,parent): 

    #Mark the current node as visited  
    visited[v]= True
    try:    
        for i in newadj[v]: 
            if  visited[i] == False :  
                if(isCyclicUtil(i,newadj,visited,v)): 
                    return True
            elif  parent != i: 
                return True
    except:
        pass
    return False

#Returns true if the graph contains a cycle, else false. 
def isCyclic(adj,i,j,n): 
    # Mark all the vertices as not visited 
    newadj = copy.deepcopy(adj)
    visited = [False]*(n+1)
    try:
        temp1 = newadj[i]
        newadj[i].append(j)
    except:
        newadj[i] = []
        newadj[i].append(j)
    try:
        temp2 = newadj[j]
        newadj[j].append(i)
    except:
        newadj[j] = []
        newadj[j].append(i)
    # Call the recursive helper function to detect cycle in different 
    #DFS trees 
    for k in range(1,n+1): 
        if visited[k] == False: #Don't recur for u if it is already visited 
            if(isCyclicUtil(k,newadj,visited,-1)) == True: 
                return True
    return False


def nearestNeighbour(start_node, n_node):
    # Write your TSP Code here
    global points
    global result_path
    global counter
    result_path= []
    # This is where you have to write you solution, according to the assignment which is given to you
    currentCity = start_node
    N = n_node
    ans = []
    visited = [0 for i in range(N)]
    ans.append(currentCity)
    count = 1
    visited[currentCity-1] = 1
    temp1 = [i for i in range(1,N+1)]
    temp1.remove(currentCity)
    while(count<N):
        neighbour = -1
        min_dis = 99999999999
        for i in range(1,N+1):
            dis = (points[currentCity-1][0] -points[i-1][0])**2 + (points[currentCity-1][1] -points[i-1][1])**2
            if(i!=currentCity and visited[i-1]==0 and min_dis>dis):
                min_dis = dis
                neighbour = i
        currentCity = neighbour
        temp1.remove(currentCity)
        ans.append(neighbour)
        temp = ans.copy()
        count+=1
        paths[count-1] = temp
        closed_sets[count-1] = temp
        open_sets[count-1] = temp1.copy()
        visited[neighbour-1] = 1
        
    counter = N-1
    # print(open_sets)
    # print(closed_sets)
    # print(paths)
    result_path = paths[N-1]
    
def greedyTSP(start_node, n_node):
    # Write your TSP Code here
    global points
    global result_path
    global counter
    global paths
    global open_sets
    global edge_list
    global closed_sets
    # This is where you have to write you solution, according to the assignment which is given to you
    counter = n_node-1
    curr = start_node
    N = n_node
    
    count = 0
    degree = [0 for i in range(N+1)]
    edges = []
    adj = {}
    opens = set()
    univ = set([i+1 for i in range(N)])
    
    
    #Create an edge list in sorted order
    distarr = []
    for i in range(1,N+1):
        for j in range(i+1,N+1):
            dis = (points[i-1][0]-points[j-1][0])**2 + (points[i-1][1]-points[j-1][1])**2
            distarr.append([dis,i,j])
    distarr = sorted(distarr)
    
    k = 0
    while(k < len(distarr)):
        i = distarr[k][1]
        j = distarr[k][2]
        if(degree[i]<2 and degree[j]<2 and isCyclic(adj,i,j,N) == False):
            degree[i] += 1
            degree[j] += 1
            try:
                temp1 = adj[i]
                adj[i].append(j)
            except:
                adj[i] = []
                adj[i].append(j)
            try:
                temp2 = adj[j]
                adj[j].append(i)
            except:
                adj[j] = []
                adj[j].append(i)
            opens.add(i)
            opens.add(j)
            edges.append([(points[i-1][0],points[i-1][1]),(points[j-1][0],points[j-1][1])])
            if(count == N):
                break
            count += 1
            paths[count] = edges.copy()
            closed_sets[count] = opens.copy()
            open_sets[count] = univ-closed_sets[count]
        k += 1
    edge_list = edges.copy()

def dis_calc(x,y):
    global points
    x = points[x-1]
    y = points[y-1]
    return (y[0]-x[0])**2 + (y[1]-x[1])**2

def savingsHeuristic(start_node, n_node):
    count = n_node - 2
    global counter
    global result_path
    result_path = []
    counter = n_node-2
    L = [[i+1] for i in range(n_node)]
    L.remove([start_node])
    while(count):
        s = -999999999
        l_i = 0
        l_j = 0
        a_i = 0
        a_j = 0
        l = len(L)
        count-=1
        for i in range(l):
            for j in range(i+1,l):
                a = L[i]
                b = L[j]
                temp = -dis_calc(a[0],b[0])+dis_calc(start_node,a[0])+dis_calc(start_node,b[0])
                if(temp>s):
                    s = temp
                    l_i = 1
                    l_j = 3
                    a_i = i
                    b_j = j
                temp = -dis_calc(a[0],b[-1])+dis_calc(start_node,a[0])+dis_calc(start_node,b[-1])
                if(temp>s):
                    s = temp
                    l_i = 1
                    l_j = 4
                    a_i = i
                    b_j = j
                temp = -dis_calc(a[-1],b[0])+dis_calc(start_node,a[-1])+dis_calc(start_node,b[0])
                if(temp>s):
                    s = temp
                    l_i = 2
                    l_j = 3
                    a_i = i
                    b_j = j
                temp = -dis_calc(a[-1],b[-1])+dis_calc(start_node,a[-1])+dis_calc(start_node,b[-1])
                if(temp>s):
                    s = temp
                    l_i = 2
                    l_j = 4
                    a_i = i
                    b_j = j
        if(l_i == 1 and l_j == 3):
            a = L[a_i]
            b = L[b_j]
            temp = a[::-1] + b
            paths[n_node-2-count] = [start_node] + temp
            closed_sets[n_node-2-count] = set(paths[n_node-2-count])
            open_sets[n_node-2-count] = set([i+1 for i in range(n_node)]) - closed_sets[n_node-2-count]
            L.remove(a)
            L.remove(b)
            L.append(temp)
        elif(l_i == 1 and l_j == 4):
            a = L[a_i]
            b = L[b_j]
            temp = a[::-1] + b[::-1]
            paths[n_node-2-count] = [start_node] + temp
            closed_sets[n_node-2-count] = set(paths[n_node-2-count])
            open_sets[n_node-2-count] = set([i+1 for i in range(n_node)]) - closed_sets[n_node-2-count]
            L.remove(a)
            L.remove(b)
            L.append(temp)
        elif(l_i == 2 and l_j == 3):
            a = L[a_i]
            b = L[b_j]
            temp = a + b
            paths[n_node-2-count] = [start_node] + temp
            closed_sets[n_node-2-count] = set(paths[n_node-2-count])
            open_sets[n_node-2-count] = set([i+1 for i in range(n_node)]) - closed_sets[n_node-2-count]
            L.remove(a)
            L.remove(b)
            L.append(temp)
        elif(l_i == 2 and l_j == 4):
            a = L[a_i]
            b = L[b_j]
            temp = a + b[::-1]
            paths[n_node-2-count] = [start_node] + temp
            closed_sets[n_node-2-count] = set(paths[n_node-2-count])
            open_sets[n_node-2-count] = set([i+1 for i in range(n_node)]) - closed_sets[n_node-2-count]
            L.remove(a)
            L.remove(b)
            L.append(temp)
        
    result_path = [start_node] + L[0]

def eval_rp(result_path):
    cost = 0
    l = len(result_path)
    for k in range(0,l):
        i = result_path[k]
        j = result_path[(k+1)%l]
        cost += (points[i-1][0]-points[j-1][0])**2 + (points[i-1][1]-points[j-1][1])**2
    return cost

def eval_el(edge_list):
    global dict_coord_index
    cost = 0
    l = len(edge_list)
    deg = [0 for i in range(l+2)]
    for e in edge_list:
        x1 = e[0][0]
        y1 = e[0][1]
        x2 = e[1][0]
        y2 = e[1][1]
        i = dict_coord_index[e[0]]
        j = dict_coord_index[e[1]]
        deg[i] += 1
        deg[j] += 1
        cost += (x1-x2)**2 + (y1-y2)**2
    close = []
    for k in range(1,l+2):
        if(deg[k] == 1):
            close.append(k)
    i = close[0]
    j = close[1]
    cost += (points[i-1][0]-points[j-1][0])**2 + (points[i-1][1]-points[j-1][1])**2
    return cost

def Algorithm_TSP(start_node,n_node,state):
    global result_path
    global edge_list
    if(state == 3):
        savingsHeuristic(start_node,n_node)
        print('Cost of Savings Heuristic = ',eval_rp(result_path))
    elif(state == 2):
        greedyTSP(start_node,n_node)
        print('Cost of Greedy TSP = ',eval_el(edge_list))
    else:
        nearestNeighbour(start_node,n_node)
        print('Cost of Nearest Neighbour = ',eval_rp(result_path))
        # ## If you are given a Search algorithm, Please edit this function below to write your answer
# def Algorithm(adjacency_list, start_node, goal_node, n_node):
#     global closed_set
#     global open_set
#     global node_colour
#     global result_path

#     global open_sets
#     global closed_sets
#     global paths
#     global counter

#     open_set.clear()
#     closed_set.clear()

#     # This is where you have to write you solution, according to the assignment which is given to you
#     return []


# generate points randomly for a graph
def generate_points(xl, yl, number=50):
    x_coordinates = np.random.randint(xl, size=number)
    y_coordinates = np.random.randint(yl, size=number)
    for i, j in zip(list(x_coordinates), list(y_coordinates)):
        points.append([i, j + 70])

    if PRINT_RESULTS:
        print("GENERATE POINTS \n", points)

    return points


## function to make adjacency list of given neighbors
def make_adj_list(a, d, n):
    t = [[] for i in range(n + 1)]
    tt = []
    for i in a:
        t[d[i[0]]].append(d[i[1]])
        t[d[i[1]]].append(d[i[0]])
    for i in t:
        tt.append(list(set(i)))
    return tt


## function to find neighbor used in triangulation
def find_neighbors(pindex, triang):
    if PRINT_RESULTS:
        print("Find Neigh", triang.vertex_neighbor_vertices[1][
                            triang.vertex_neighbor_vertices[0][pindex]:triang.vertex_neighbor_vertices[0][pindex + 1]])
    return triang.vertex_neighbor_vertices[1][
           triang.vertex_neighbor_vertices[0][pindex]:triang.vertex_neighbor_vertices[0][pindex + 1]]


def make_edge_list(points, tri, bf):
    global edge_list
    for pindex in range(len(points)):
        neighbor_indices = find_neighbors(pindex, tri)
        for i in range(len(neighbor_indices)):
            if i % bf != 0:
                edge_list.append([(points[pindex][0], points[pindex][1]),
                                  (points[neighbor_indices[i]][0], points[neighbor_indices[i]][1])])

    if PRINT_RESULTS:
        print("Edge List", edge_list)
    return edge_list


## function to make dictionary mapping indices to coordinate points
def make_dict_index_coord(points):
    global dict_index_coord
    idx = 1
    for point in points:
        dict_index_coord[idx] = (point[0], point[1])
        idx += 1

    if PRINT_RESULTS:
        print("Dict_index\n", dict_index_coord)
    return dict_index_coord


## function to make dictionary mapping coordinate points to indices
def make_dict_coord_index(points):
    global dict_coord_index
    cnt = 1
    for i in points:
        dict_coord_index[(i[0], i[1])] = cnt
        cnt += 1
    return dict_coord_index


## Below are class init definitions
class Graph(QMainWindow):

    def init_graph_paramaters(self):
        global points
        global dict_index_coord
        global edge_list
        global result_path
        points = []
        dict_index_coord = {}
        edge_list = []
        result_path = []
        self.nodes = int(self.nodeText.toPlainText())
        self.bf = int(self.bfText.toPlainText())
        self.algo = int(self.algoText.toPlainText())
        self.graph_node_colour = [0 for i in range(self.nodes + 1)]

    def generateTSP(self):
        global node_colour
        self.event = "Generate_TSP"
        self.init_graph_paramaters()
        x_dim = screen_width - 100
        y_dim = screen_height - 150
        generate_points(x_dim, y_dim, self.nodes)
        make_dict_index_coord(points)
        make_dict_coord_index(points)
        node_colour = [0 for i in range(self.nodes + 1)]
        self.update()

    def generateGraph(self):
        global tri
        global node_colour
        self.event = "Generate_Graph"
        self.init_graph_paramaters()
        x_dim = screen_width - 100
        y_dim = screen_height - 150
        generate_points(x_dim, y_dim, self.nodes)
        tri = scipy.spatial.Delaunay(np.array(points))
        make_edge_list(points, tri, self.bf)
        make_dict_index_coord(points)
        make_dict_coord_index(points)
        node_colour = [0 for i in range(self.nodes + 1)]
        self.update()

    def reset_screen(self):
        self.event = "Reset_Screen"
        self.delAct.setEnabled(False)
        self.startAct.setEnabled(False)
        self.goalAct.setEnabled(False)
        self.update()

    ## function to save the graph data structure as pickle files
    def saveGraph(self):
        global points
        global dict_coord_index
        global dict_index_coord
        global edge_list

        with open('points.pkl', 'wb') as f:
            pickle.dump(points, f)

        with open('dict_index_coord.pkl', 'wb') as f:
            pickle.dump(dict_index_coord, f)

        with open('dict_coord_index.pkl', 'wb') as f:
            pickle.dump(dict_coord_index, f)

        with open('edge_list.pkl', 'wb') as f:
            pickle.dump(edge_list, f)

    ## function to load the saved graph data structure from pickle files
    def loadGraph(self):
        global points
        global dict_coord_index
        global dict_index_coord
        global tri
        global edge_list
        global result_path
        global node_colour

        with open('points.pkl', 'rb') as f:
            points = pickle.load(f)

        with open('dict_index_coord.pkl', 'rb') as f:
            dict_index_coord = pickle.load(f)

        with open('dict_coord_index.pkl', 'rb') as f:
            dict_coord_index = pickle.load(f)

        with open('edge_list.pkl', 'rb') as f:
            edge_list = []

        tri = scipy.spatial.Delaunay(np.array(points))
        self.nodes = len(points)
        node_colour = [0 for i in range(self.nodes + 1)]
        result_path = []

        self.event = "Generate_TSP"
        self.delAct.setEnabled(False)
        self.startAct.setEnabled(False)
        self.goalAct.setEnabled(False)

    ## code for GUI
    def initUI(self):

        self.saveAct = QAction('&Save Graph', self)
        self.saveAct.setShortcut('Ctrl+S')
        self.saveAct.setStatusTip('Save Graph')
        self.saveAct.triggered.connect(self.saveGraph)

        self.loadAct = QAction('&Load Graph', self)
        self.loadAct.setShortcut('Ctrl+O')
        self.loadAct.setStatusTip('Load Graph')
        self.loadAct.triggered.connect(self.loadGraph)

        self.exitAct = QAction('&Exit', self)
        self.exitAct.setShortcut('Ctrl+Q')
        self.exitAct.setStatusTip('Exit application')
        self.exitAct.triggered.connect(qApp.quit)

        # Action of generating graphs, TSP
        self.genAct = QAction('&Generate Graph', self)
        self.genAct.triggered.connect(self.generateGraph)

        self.genTSPAct = QAction('&Generate TSP', self)
        self.genTSPAct.triggered.connect(self.generateTSP)

        # Text Mode on Screen
        self.nodeLabel = QLabel('Number of nodes:')
        self.nodeText = QPlainTextEdit('10')
        self.nodeText.setFixedSize(80, 28)

        self.bfLabel = QLabel('Branching Factor:')
        self.bfText = QPlainTextEdit('2')
        self.bfText.setFixedSize(80, 28)

        self.algoLabel = QLabel('Enter 1/2/3:')
        self.algoText = QPlainTextEdit('1')
        self.algoText.setFixedSize(80, 28)

        self.delAct = QAction('&Delete Node', self)
        self.startAct = QAction('&Start Node', self)
        self.goalAct = QAction('&Goal Node', self)

        self.resetAct = QAction('&Reset Screen', self)
        self.resetAct.triggered.connect(self.reset_screen)

        self.menubar = self.menuBar()
        self.fileMenu = self.menubar.addMenu('File')
        self.fileMenu.addAction(self.saveAct)
        self.fileMenu.addAction(self.loadAct)
        self.fileMenu.addAction(self.exitAct)

        self.toolbar = self.addToolBar('')
        self.toolbar.addWidget(self.nodeLabel)
        self.toolbar.addWidget(self.nodeText)
        self.toolbar.addWidget(self.algoLabel)
        self.toolbar.addWidget(self.algoText)

        # self.toolbar.addAction(self.genAct)
        self.toolbar.addAction(self.genTSPAct)
        self.toolbar.addAction(self.delAct)
        self.toolbar.addAction(self.startAct)
        self.toolbar.addAction(self.goalAct)

        self.toolbar.addAction(self.resetAct)
        self.setMouseTracking(True)
        self.delAct.setEnabled(False)
        self.startAct.setEnabled(False)
        self.goalAct.setEnabled(False)

    def __init__(self):
        super().__init__()

        self.nodes = -1
        self.bf = -1
        self.algo = 1
        self.dict_index_coord = {}
        self.dict_coord_index = {}
        self.open_sets = {}
        self.closed_sets = {}
        self.open_list = []
        self.closed_list = []
        self.init_phase = -1

        self.start_x = 0
        self.start_y = 0

        self.del_x = 0
        self.del_y = 0

        self.goal_x = 0
        self.goal_y = 0

        self.initUI()
        self.setMinimumSize(QSize(screen_width, screen_height))
        self.setWindowTitle("Alviz v1.0")

    ## function to detect closest node from your mouse click
    def findClosestCoordinate(self, min_x, min_y, x, y):
        min_dist = 99999999999
        global result_path
        global iteration
        global open_sets
        global closed_sets
        global open_set
        global closed_set
        global paths
        global edge_list

        for p in points:
            dist = (x - p[0]) ** 2 + (y - p[1]) ** 2
            if dist < min_dist:
                min_dist = dist
                min_x = p[0]
                min_y = p[1]

        if self.event == "Generate_Graph":
            self.del_x = min_x
            self.del_y = min_y
            self.event = "Del_Node"

        elif self.event == "Generate_TSP":
            self.start_x = min_x
            self.start_y = min_y
            self.algo = int(self.algoText.toPlainText())
            start_node = dict_coord_index[(self.start_x, self.start_y)]
            Algorithm_TSP(start_node, self.nodes,self.algo)
            self.event = "Display_Path"
            iteration = 0

        elif self.event == "Del_Node":
            self.start_x = min_x
            self.start_y = min_y
            self.event = "Start_Node"

        elif self.event == "Start_Node":
            self.goal_x = min_x
            self.goal_y = min_y
            self.event = "Goal_Node"

        elif self.event == "Goal_Node":
            print("Goal Node selected")
            start_node = dict_coord_index[(self.start_x, self.start_y)]
            goal_node = dict_coord_index[(self.goal_x, self.goal_y)]
            Algorithm(adjacency_list, start_node, goal_node, self.nodes)
            self.event = "Display_Path"
            iteration = 0

        elif self.event == "Display_Path":
            if iteration < counter:
                iteration += 1
				#If you need more data structures that has to be coloured add it here
                open_set = open_sets[iteration]
                closed_set = closed_sets[iteration]
                if(self.algo == 2):
                    edge_list = paths[iteration]
                else:
                    result_path = paths[iteration]
                for j in open_set:
                    node_colour[j] = 1  ##Magenta
                for j in closed_set:
                    node_colour[j] = 2  ##Blue
            else:
                print("Program Completed")

    # After every mouse press event on screen this function is called
    def mousePressEvent(self, canvas):
        x = canvas.x()
        y = canvas.y()

        min_x = 99999
        min_y = 99999
        self.findClosestCoordinate(min_x, min_y, x, y)

    # This function is called continously after some time intervals by python program
    # Understand this function for better understanding of your assignment and what is expected.
    def paintEvent(self, e):
        qp = QPainter()
        qp.begin(self)
        self.drawPoints(qp)
        qp.end()

    def drawPoints(self, qp):
        global tri
        global adjacency_list
        global node_colour

        qp.setPen(Qt.red)
        if self.event == "Generate_Graph" or self.event == "Generate_TSP":
            for point in points:
                center = QPoint(point[0], point[1])
                qp.setBrush(Qt.yellow)
                qp.drawEllipse(center, 5, 5)
            if self.event == "Generate_TSP":
                self.drawLine(qp)

        elif self.event == "Del_Node":
            if [self.del_x, self.del_y] in points:
                node_deleted = (self.del_x, self.del_y)
                temp = []
                for edge in edge_list:
                    if node_deleted in edge:
                        continue
                    temp.append(edge)

                edge_list = temp
                points.remove([self.del_x, self.del_y])
                self.nodes -= 1
                make_dict_index_coord(points)
                make_dict_coord_index(points)
                adjacency_list = make_adj_list(edge_list, dict_coord_index, self.nodes)
                node_colour = [0 for i in range(self.nodes + 1)]

            for point in points:
                center = QPoint(point[0], point[1])
                qp.setBrush(Qt.yellow)
                qp.drawEllipse(center, 5, 5)

            self.drawLine(qp)
            self.delAct.setEnabled(False)
            self.startAct.setEnabled(True)
            self.goalAct.setEnabled(False)

        elif self.event == "Start_Node":
            for point in points:
                center = QPoint(point[0], point[1])
                qp.setBrush(Qt.yellow)
                qp.drawEllipse(center, 5, 5)
            center = QPoint(self.start_x, self.start_y)
            qp.setBrush(Qt.green)
            qp.drawEllipse(center, 10, 10)
            self.drawLine(qp)
            self.startAct.setEnabled(False)
            self.delAct.setEnabled(False)
            self.goalAct.setEnabled(True)

        elif self.event == "Goal_Node":
            for point in points:
                center = QPoint(point[0], point[1])
                qp.setBrush(Qt.yellow)
                qp.drawEllipse(center, 5, 5)

            center = QPoint(self.start_x, self.start_y)
            qp.setBrush(Qt.green)
            qp.drawEllipse(center, 10, 10)
            self.drawLine(qp)

            center = QPoint(self.goal_x, self.goal_y)
            qp.setBrush(Qt.red)
            qp.drawEllipse(center, 10, 10)
            self.drawLine(qp)
            self.goalAct.setEnabled(False)

        elif self.event == "Display_Path":
            for i in range(1, len(node_colour)):
                point = dict_index_coord[i]
                e = node_colour[i]
                center = QPoint(point[0], point[1])
                if e == 0:
                    qp.setBrush(Qt.yellow)
                    qp.drawEllipse(center, 5, 5)
                elif e == 1:
                    qp.setBrush(Qt.magenta)
                    qp.drawEllipse(center, 5, 5)
                elif e == 2:
                    qp.setBrush(Qt.blue)
                    qp.drawEllipse(center, 5, 5)
                elif e == 3:
                    qp.setBrush(Qt.cyan)
                    qp.drawEllipse(center, 5, 5)
                elif e == 4:
                    qp.setBrush(Qt.red)
                    qp.drawEllipse(center, 5, 5)

            center = QPoint(self.start_x, self.start_y)
            qp.setBrush(Qt.green)
            qp.drawEllipse(center, 10, 10)
            self.drawLine(qp)
            center = QPoint(self.goal_x, self.goal_y)
            qp.setBrush(Qt.red)
            qp.drawEllipse(center, 10, 10)
            self.drawLine(qp)

        self.update()

    def drawLine(self, qp):
        global result_path
        global edge_list

        pen = QPen(Qt.black, 1, Qt.DashDotDotLine)
        qp.setPen(pen)
        for e in edge_list:
            qp.drawLine(e[0][0], e[0][1], e[1][0], e[1][1])

        if len(result_path) != 0:
            pen = QPen(Qt.red, 2, Qt.SolidLine)
            qp.setPen(pen)
            for i in range(0, len(result_path) - 1, 1):
                prev_point = dict_index_coord[result_path[i]]
                next_point = dict_index_coord[result_path[i + 1]]
                qp.drawLine(prev_point[0], prev_point[1], next_point[0], next_point[1])

        if self.event == "Generate_Graph":
            self.delAct.setEnabled(True)
            self.startAct.setEnabled(False)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    graph = Graph()
    graph.show()
    sys.exit(app.exec_())
