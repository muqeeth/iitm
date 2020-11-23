##naive code May be subjected to change
import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.lines as mlines
import sys
from matplotlib import figure

def hierarchy_pos(G, root, width=1., vert_gap = 0.2, vert_loc = 0, xcenter = 0.5 ):
    def h_recur(G, root, width=1., vert_gap = 0.2, vert_loc = 0, xcenter = 0.5, 
                  pos = None, parent = None, parsed = [] ):
        if(root not in parsed):
            parsed.append(root)
            if pos == None:
                pos = {root:[xcenter,vert_loc]}
            else:
                pos[root] = [xcenter, vert_loc]
            neighbors = list(G.neighbors(root))
            if parent != None and parent in neighbors:
                neighbors.remove(parent)
            if len(neighbors)!=0:
                dx = width/len(neighbors) 
                nextx = xcenter - width/2 - dx/2
                for neighbor in neighbors:
                    nextx += dx
                    pos = h_recur(G,neighbor, width = dx, vert_gap = vert_gap, 
                                        vert_loc = vert_loc-vert_gap, xcenter=nextx, pos=pos, 
                                        parent = root, parsed = parsed)
        return pos

    return h_recur(G, root, width=1., vert_gap = 0.2, vert_loc = 0, xcenter = 0.5)

def show_graph(G,a,title,img_title):
    pos = hierarchy_pos(G,a)    
    for key in pos.keys():
        pos[key][1] = -pos[key][1]
    # nx.draw(G,pos = pos , with_labels = True)
    elarge = [(u, v) for (u, v, d) in G.edges(data=True) if d['weight'] == 1.0]
    esmall = [(u, v) for (u, v, d) in G.edges(data=True) if d['weight'] == -1.0]

    w,h = figure.figaspect(3.0)
    fig = plt.figure(figsize=(h,w))
    plt.title(title)

    blue_line = mlines.Line2D([], [], color='blue',label = 'Postive edge')
    red_line = mlines.Line2D([], [], color='red',label = 'Negative edge')
    plt.legend(handles=[blue_line,red_line])
    
    edge_labels = {}
    for (u,v,d) in G.edges(data = True):
        if d['weight'] == 1:
            edge_labels[(u,v)] = 'pos'
        else:
            edge_labels[(u,v)] = 'neg'
    nx.draw_networkx_edges(G, pos = pos,connectionstyle='arc3, rad = 0.05',edgelist=elarge,edge_color='b',edge_labels=edge_labels)
    nx.draw_networkx_edges(G, pos = pos,connectionstyle='arc3, rad = 0.05',edgelist=esmall,edge_color='r')
    # nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels) 
    nx.draw_networkx_nodes(G, pos)
    nx.draw_networkx_labels(G,pos)  
        
    #plt.show()
    fig.savefig(img_title+".png")
    plt.close(fig)


def readData(graph_info_file,a_x_info_file):
    f = open(graph_info_file,"r",encoding="utf-8")
    input = list(f.readlines())
    f.close()

    input = [k.split() for k in input]
    f = open(a_x_info_file,"r")
    input2 = list(f.readlines())
    f.close()

    a_list = []
    x_list = []
    for pair in input2:
        pair = pair.split()
        a_list.append(pair[0])
        x_list.append(pair[1])
    cleaned_input = []

    for statement in input:
        if("\n" in statement):
            cleaned_input.append(statement[:-1])
        else:
            cleaned_input.append(statement)

    tuple_input = []
    for statement in cleaned_input:
        if("NOT" in statement):
            tuple_input.append((statement[0],statement[3],-1.0))
        else:
            tuple_input.append((statement[0],statement[2],1.0))

    return (a_list,x_list,set(tuple_input))

def getGraph(tuple_input):
	G = nx.DiGraph()
	for i in tuple_input:
		G.add_edge(i[0],i[1],weight=i[2],adm=-1)
	return G

def Admpath(G,path,s):
    for edge in path:
        if G[edge[0]][edge[1]]['adm'] == -1:
            getAdm(G,edge[0],edge[1],s)
        if G[edge[0]][edge[1]]['adm'] == False:
            return False
    return True

def Redpath(G,path,s):
    for edge in path:
        if G[edge[0]][edge[1]]['red'] == -1:
            getRed(G,edge[0],edge[1],s)
        if G[edge[0]][edge[1]]['red'] == True:
            return True
    return False

def Postivepath(G,path):
    for edge in path:
        if G[edge[0]][edge[1]]['weight'] == -1:
            return False
    return True

def Preemption(G,path,v,x):
    nodes = []
    for edge in path:
        nodes.append(edge[0])
    if G[v][x]['weight'] == 1:
        for predecessor in list(G.predecessors(x)):
            if predecessor in nodes:
                if G[predecessor][x]['weight'] == -1:
                    return True
    else:
        for predecessor in list(G.predecessors(x)):
            if predecessor in nodes:
                if G[predecessor][x]['weight'] == 1:
                    return True
    return False

def Redundancy(G,path,s,pos):
    for edge in path:
        if G[edge[0]][edge[1]]['adm'] == -1:
            # print(G[edge[0]][edge[1]]['adm'])
            getAdm(G,edge[0],edge[1],s)
            # print(G[edge[0]][edge[1]]['adm'])
        if G[edge[0]][edge[1]]['adm'] == False:
            return False
    if pos == 1:
        nodes = []
        for edge in path:
            nodes.append(edge[0])
        nodes.append(path[-1][1])
        nodes = nodes[1:]
        for node in nodes:
            for predecessor in list(G.predecessors(node)):
                if G[predecessor][node]['weight'] == -1:
                    if G[predecessor][node]['adm'] == -1:
                        getAdm(G,predecessor,node,s)
                    if G[predecessor][node]['adm'] == True:
                        return False
        return True
    else:
        nodes = []
        for edge in path:
            nodes.append(edge[0])
        nodes.append(path[-1][1])
        nodes = nodes[1:]
        for node in nodes[:-1]:
            for predecessor in list(G.predecessors(node)):
                if G[predecessor][node]['weight'] == -1:
                    if G[predecessor][node]['adm'] == -1:
                        getAdm(G,predecessor,node,s)
                    if G[predecessor][node]['adm'] == True:
                        return False
        for predecessor in list(G.predecessors[nodes[-1]]):
            if G[predecessor][nodes[-1]]['weight'] == 1:
                if G[predecessor][nodes[-1]]['adm'] == -1:
                    getAdm(G,predecessor,nodes[-1],s)
                if G[predecessor][nodes[-1]]['adm'] == True:
                    return False
        return True

def getRed(G,v,x,s):
    if G[v][x]['red']!=-1:
        return
    tmp1 = (nx.all_simple_paths(G, source=v, target=x))
    if G[v][x]['weight'] == 1:
        paths = []
        #remove invalid paths
        for path in map(nx.utils.pairwise, tmp1):
            path = list(path)
            if Postivepath(G,path):
                paths.append(path)
        if len(paths)>1:
            for path in paths:
                if path != [(v,x)]:
                    if Redundancy(G,path,s,1):
                        G[v][x]['red'] = True
                        return
        G[v][x]['red'] = False
        return
        
    else:
        paths = []
        for path in map(nx.utils.pairwise, tmp1):
            path = list(path)
            if len(path[:-1])>0:
                if G[path[-1][0]][path[-1][1]]['weight'] == -1:
                    if Postivepath(G,path[:-1]):
                        paths.append(path)
        if len(paths)>1:
            for path in paths:
                if Redundancy(G,path,s,-1):
                    G[v][x]['red'] = True
                    return
        G[v][x]['red'] = False
        return

def getAdm(G,v,x,s):
    if G[v][x]['adm']!= -1:
        return 
    if s == v:
        G[v][x]['adm'] = True
        return
    tmp2 = (nx.all_simple_paths(G,source = s, target = v))
    paths = []
    for path in map(nx.utils.pairwise, tmp2):
        path = list(path)
        if Postivepath(G,path):
            paths.append(path)
    for path in paths:
        if Admpath(G,path,s):
            if not Redpath(G,path,s):
                if Preemption(G,path,v,x) == False:
                    G[v][x]['adm'] = True
                    return
    G[v][x]['adm'] = False
    return

def a_connected(G,s):
    stack = []
    stack.append((s,0))
    retained = []
    while len(stack)!=0:
        tmp = stack.pop()
        if tmp[1] == -1:
            continue
        for successor in list(G.successors(tmp[0])):
            if  G[tmp[0]][successor]['weight'] == 1:
                stack.append((successor,0))
                retained.append((tmp[0],successor))
            else:
                stack.append((successor,-1))
                retained.append((tmp[0],successor))
    edges = list(G.edges())
    for edge in edges:
        if edge not in retained:
            G.remove_edge(edge[0],edge[1])
    BarrenNodes = []

    for node in list(G.nodes()):
        if G.in_degree(node) == 0 and G.out_degree(node) == 0:
            BarrenNodes.append(node)
    for node in BarrenNodes:
        G.remove_node(node)
    return G
    

def level_prune(G,t):
    res = G.copy()
    for predecessor in list(G.predecessors(t)):
        if G[predecessor][t]['weight'] == 1:
            return res
    for successor in list(G.successors(t)):
        res.remove_edge(t,successor)
    return res


def Resolve(G,s):
    nodes = list(G.nodes)
    index = nodes.index(s)
    for i in range(index+1,len(nodes)):
        res1 = 0
        res2 = 0
        predecessors = list(G.predecessors(nodes[i]))
        for predecessor in predecessors:
            if G[predecessor][nodes[i]]['weight'] == 1:
                res1+=1
            elif G[predecessor][nodes[i]]['weight'] == -1:
                res2+=1
        if res1 == len(predecessors) or res2 == len(predecessors):
            continue
        else:
            res1 = G.copy()
            res2 = G.copy()
            for predecessor in predecessors:
                if G[predecessor][nodes[i]]['weight'] == 1:
                    res2.remove_edge(predecessor,nodes[i])
                else:
                    res1.remove_edge(predecessor,nodes[i])
            res1 = level_prune(res1,nodes[i])
            res2 = level_prune(res2,nodes[i])
            return (res1,res2,nodes[i])
    return 'done'

def MakeCredulousExtensions(G,s):
    #takes level ordered graph as a input
    stack = []
    ans = []
    stack.append((G,s))
    while len(stack)!=0:
        tmp1 = stack.pop()
        tmp2 = Resolve(tmp1[0],tmp1[1])
        if tmp2 == 'done':
            ans.append(tmp1[0])
        else:
            stack.append((tmp2[0],tmp2[2]))
            stack.append((tmp2[1],tmp2[2]))
    return ans

def checkSource(G,common_nodes,node):
    p = list(G.predecessors(node))
    for k in p:
        if k not in common_nodes:
            return False
    return True
    
def CompareEdges(G1,G2,s,node):
    tmp1 = list(nx.all_simple_paths(G1,source = s, target = node))
    tmp2 = list(nx.all_simple_paths(G2,source = s, target = node))
    for i in tmp1:
        if i in tmp2:
            tmp2.remove(i)
    if len(tmp2) == 0:
        return True
    return False

def preferredExternsionPair(G,G1,G2,nodes):
    common_nodes = []
    for node in nodes:
        if CompareEdges(G1,G2,nodes[0],node):
            common_nodes.append(node)
    checking_nodes = []
    for node in nodes:
        if node not in common_nodes:
            if checkSource(G,common_nodes,node):
                checking_nodes.append(node)
    path_1_inadm = 0
    path_2_inadm = 0
    for node in checking_nodes:  
        l1 = []
        l2 = []
        if G1.has_node(node):
            l1 = list(G1.predecessors(node))
        if G2.has_node(node):
            l2 = list(G2.predecessors(node))
        common = []
        for i in l1:
            if i in l2:
                common.append(i)
        for i in common:
            l1.remove(i)
            l2.remove(i)

        for k in l1:
            if(G1[k][node]['adm'] == False):
                path_1_inadm += 1
        for k in l2:
            if(G2[k][node]['adm'] == False):
                path_2_inadm += 1
    # print(path_1_inadm,path_2_inadm)
    if(path_1_inadm < path_2_inadm):
        return 1
    elif(path_2_inadm < path_1_inadm):
        return 2
    else:
        return 0

def getPreferredExtensionList(G,cred_ext,nodes):
    pref_list = []
    for i in range(len(cred_ext)):
        for j  in range(len(cred_ext)):
            if(i<j):
                G1 = cred_ext[i]
                G2 = cred_ext[j] 
                pref = preferredExternsionPair(G,G1,G2,nodes)
                if(pref==1):
                    # print(str(list(G1.edges()))+">>>>>>>>>>>>>>>>>>>>"+str(list(G2.edges())))
                    pref_list.append((G2,G1))
                elif(pref==2):
                    # print(str(list(G2.edges()))+">>>>>>>>>>>>>>>>>>>>"+str(list(G1.edges())))
                    pref_list.append((G1,G2))
    return set(pref_list)

def isPositivePath(G,path):
    for i in range(len(path)-1):
        if(G[path[i]][path[i+1]]['weight'] == -1.0):
            return False
    return True

def isNegativePath(G,path):
    for i in range(len(path)-2):
        if(G[path[i]][path[i+1]]['weight'] == -1.0):
            return False
    if(G[path[len(path)-2]][path[len(path)-1]]['weight'] == 1):
        return False
    return True

def existsPositivePath(G,paths):
    for path in paths:
        if(isPositivePath(G,path)):
            return 1
    return 0

def existsNegativePath(G,paths):
    for path in paths:
        if(isNegativePath(G,path)):
            return 1      
    return 0
    
def getPositivePaths(G,a,x):
    pos_paths = []
    for path in list(nx.all_simple_paths(G,source=a,target=x)):
        if(isPositivePath(G,path)):
            pos_paths.append(path)
    return pos_paths

def getNegativePaths(G,a,x):
    neg_paths = []
    for path in list(nx.all_simple_paths(G,source=a,target=x)):
        if(isNegativePath(G,path)):
            neg_paths.append(path)
    return neg_paths

def ideallyskepticalReasoning(a,x,preference_list,graphs):
    pos_ans = 1
    neg_ans = 1
    pos_paths = []
    neg_paths = []

    for i in preference_list:
        paths = list(nx.all_simple_paths(graphs[i],source=a,target=x))
        pos_ans = pos_ans*existsPositivePath(graphs[i],[paths[0]])
        for path in getPositivePaths(graphs[i],a,x):
            if(path not in pos_paths):
                pos_paths.append(path)
        neg_ans = neg_ans*existsNegativePath(graphs[i],[paths[0]])
        for path in getNegativePaths(graphs[i],a,x):
            if(path not in neg_paths):
                neg_paths.append(path)
    if(pos_ans==1):
        return (1,pos_paths)
    elif(neg_ans==1):
        return (-1,neg_paths)
    else:
        return (0,[])

def skepticalReasoning(a,x,preference_list,graphs):
	common_paths = list(nx.all_simple_paths(graphs[preference_list[0]],source=a,target=x))
	for i in preference_list:
	    for path in common_paths:
	        paths_new = list(nx.all_simple_paths(graphs[i],source=a,target=x))
	        if(path not in paths_new):
	            common_paths.remove(path)

	if(common_paths == []):
	    return (0,[])
	pos_verdict = 1
	neg_verdict = 1
	pos_paths = []
	neg_paths = []
	for path in common_paths:
	    pos_ans = 1
	    neg_ans = 1
	    for i in preference_list:
	        pos_ans = pos_ans*existsPositivePath(graphs[i],[path])
	        neg_ans = neg_ans*existsNegativePath(graphs[i],[path])
	    if(pos_ans==1 and neg_ans==0):
	        pos_verdict = pos_verdict*1
	        neg_verdict = 0
	        if(path not in pos_paths):
	            pos_paths.append(path)
	    elif(pos_ans==0 and neg_ans==1):
	        neg_verdict = neg_verdict*1
	        pos_verdict = 0
	        if(path not in neg_paths):
	            neg_paths.append(path)

	if(pos_verdict==1):
	    return (1,pos_paths)
	elif(neg_verdict==1):
	    return (-1,neg_paths)
	else:
	    return (0,[])

def reason(tuple_input,a,x):
    G = getGraph(tuple_input)

    if(not G.has_node(a)):
        sr  = "Invalid value of source provided !"
        isr = ""
        return (sr,isr)

    if(not G.has_node(x)):
        sr  = "Invalid value of target provided !"
        isr = ""
        return (sr,isr)

    if(not nx.has_path(G,source = a,target = x)):
        sr  = "Original graph has no path from source to target"
        isr = ""
        return (sr,isr)

    G = a_connected(G,a) 

    nodes = (list(nx.topological_sort(G)))
    print(nodes)
    DG = nx.DiGraph()
    for node1 in nodes:
        for node2 in nodes:
            if (node1,node2) in list(G.edges()):
                DG.add_edge(node1,node2,weight = G[node1][node2]['weight'], adm = -1,red = -1)
    
      
    for edge in list(DG.edges()):
        print(edge[0],edge[1],DG[edge[0]][edge[1]]['weight'])
        getRed(DG,edge[0],edge[1],a)
        getAdm(DG,edge[0],edge[1],a)
        print(DG[edge[0]][edge[1]]['adm'],DG[edge[0]][edge[1]]['red'])

    show_graph(DG,a, 'Original Hierarchy (for case : a = '+a+", x = "+x+") ","OH_a="+a+",x="+x)

    ans = MakeCredulousExtensions(DG,a)

    credulousExtensions = []
    count = 1
    print('credulous extensions are: ')
    for tmp in ans:
        tmp = a_connected(tmp,a)
        print(list(tmp.edges()))
        # print(tmp.nodes())
        credulousExtensions.append(tmp)
        show_graph(tmp,a, 'Credulous Extension (for case : a = '+a+", x = "+x+") "+str(count),"CE"+str(count)+"_a="+a+",x="+x)
        count+=1

    pref_list = list(getPreferredExtensionList(DG,credulousExtensions,nodes))
    preference_tuples = []
    # print(pref_list)
    for tup in pref_list:
        preference_tuples.append((credulousExtensions.index(tup[0]),credulousExtensions.index(tup[1])))

    adj = {}
    for i in range(len(credulousExtensions)):
        adj[i] = []

    for tup in preference_tuples:
        adj[tup[0]].append(tup[1])
    preference_list = []

    for i in range(len(credulousExtensions)):
        if len(adj[i]) == 0:
            preference_list.append(i)

    print('preferred ones are')
    count = 1
    for i in preference_list:
        print(list(credulousExtensions[i].edges()))
        show_graph(credulousExtensions[i],a, 'Preferred Extension (for case : a = '+a+", x = "+x+") "+str(count),"PE"+str(count)+"_a="+a+",x="+x)
        count+=1

    for i in preference_list:
        G = credulousExtensions[i]
        if(not G.has_node(x)):
            str_sr  = "According to Skeptical Reasoning, Nothing can be said since there is atleast one preferred extension which does not have x."
            str_isr = "According to Ideally Skeptical Reasoning, Nothing can be said since there is atleast one preferred extension which does not have x."
            return (str_sr,str_isr)

    sr_verdict,sr_paths = skepticalReasoning(a,x,preference_list,credulousExtensions)
    if(sr_verdict == 1):
        str_sr = "According to Skeptical Reasoning, "+str(a)+" isA/isInstance of "+str(x)+" via paths : "+str(sr_paths)
    elif(sr_verdict == -1):
        str_sr = "According to Skeptical Reasoning, "+str(a)+" isNOTA/isNOTInstance of "+str(x)+" via paths : "+str(sr_paths)
    else:
        str_sr = "According to Skeptical Reasoning, Nothing can be said."
    # print(str_sr)

    isr_verdict,isr_paths = ideallyskepticalReasoning(a,x,preference_list,credulousExtensions)
    if(isr_verdict == 1):
        str_isr = "According to Ideally Skeptical Reasoning, "+str(a)+" isA/isInstance of "+str(x)+" via paths : "+str(isr_paths)
    elif(isr_verdict == -1):
        str_isr = "According to Ideally Skeptical Reasoning, "+str(a)+" isNOTA/isNOTInstance of "+str(x)+" via paths : "+str(isr_paths)
    else:
        str_isr = "According to Ideally Skeptical Reasoning, Nothing can be said."
    # print(str_isr)

    return (str_sr,str_isr)

def main():
	graph_info_file = str(sys.argv[1])
	a_x_info_file   = str(sys.argv[2])
	a_list,x_list,tuple_input = readData(graph_info_file,a_x_info_file)

	result = ""
	for i in range(len(a_list)):
		if(a_list[i]==x_list[i]):
			sr  = "a and x are the same. We assume this to be true."
			isr = ""
		else:
			sr,isr = reason(tuple_input,a_list[i],x_list[i])
		result = result+"Solution for query "+str(i+1)+" "+str(a_list[i])+" "+str(x_list[i])+" :\n"+sr+"\n"+isr+"\n\n"

	f = open("solutions.txt","w+",encoding="utf-8")
	f.write(result)
	f.close()

	return 0

if __name__ == "__main__":
    main()
