import sys
import re
from math import sqrt
from itertools import combinations
import copy

def Exception1(y):
            print('Error: ' + str(y), file=sys.stderr)
def coor_check1(coordinates):
    coordinates=coordinates.replace(" ","")
    space=[]
    for x in range(0,len(coordinates)):
        if coordinates[x].strip()==")":
            space.append(x)
    else:
        None
    if len(coordinates)-1 == space[-1]:
        space.pop()
    else:
        None
    for x in space:  
        if coordinates[x+1] != "(":
            r=1
            break
        else:
            r=0
    return r
def coor_check2(coordinates):
    coordinates=coordinates.replace(" ","")
    space=[]
    for x in range(0,len(coordinates)):
        if coordinates[x].strip()=="(":
            space.append(x)
    else:
        None
    for x in space[1:]:  
        if coordinates[x-1] != ")":
            r=1
            break
        else:
            r=0
    return r
def charactercheck(coordinates):
            for x in range(0,len(coordinates)):
                        if coordinates[x] not in ['0','1','2','3','4','5','6','7','8','9','(',')',',','-',' ']:
                                    r=1
                                    break
                        else:
                                    r=0
            return r
def coor_check(coordinates):
            if charactercheck(coordinates)==1:
                        Exception1('Unexpected characters present in the given list of cartesian coordinates.')
            elif coor_check1(coordinates)==1 or coor_check2(coordinates)==1:
                        Exception1('There are characters present before or after the paranthesis.')            
            elif coordinates.find(',)') !=-1 or coordinates.find('(,') !=-1 or coordinates.find('(,)') !=-1 or coordinates.find('),') !=-1 or coordinates.find('),(') !=-1 or coordinates.find(',(') != -1 or coordinates.find('( ,') !=-1 or coordinates.find(', )') !=-1 or coordinates.find('()') !=-1 or coordinates.find('-)') !=-1 or coordinates.find('-,') !=-1:
                        Exception1('The given coordinates are invalid. Use the characters "(", ")", "," and "-" approriately.')
            elif coordinates.count(')') != coordinates.count('('):
                        Exception1('There is an imbalance in the number of open and close paranthesis.')
            else:
                        return coordinates            
def input_cmd(l):
            l=l.strip()
            cmd = l[0]
            return cmd
def input_street(l):
            l=l.strip()
            if l.find('" ')!=-1:
                        street=l[l.index('"')+1:l.index('" ')].upper()
            else:
                        street=l[l.index('"')+1:-1].upper()
            return street
def input_coordinates(l):
            l=l.strip()            
            coordinates = l[l.index('('):]
            return coordinates
def addition(line,d):
            cmd = input_cmd(line)            
            street=input_street(line)
            coordinates=input_coordinates(line)
            coordinates=coor_check(coordinates)
            if coordinates != None:
                        # print('addding')
                        #print(cmd,street,coordinates)
                        if street not in d.keys():
                                    d[street]= coordinates
                                    d1=copy.deepcopy(d)
                                    for i in d1.keys():
                                                d1[i]=get_cord(d1[i])
                                    if dup_coor_check(d1)==1:
                                                Exception1('Duplicate coordinates present in the street')
                                                d.pop(street)
                        else:
                                                Exception1('Street already exists.')
                        #print(d)
            else:
                        None
            return d
def change(line,d):
            cmd = input_cmd(line)            
            street=input_street(line)
            coordinates=input_coordinates(line)
            coordinates=coor_check(coordinates)
            if coordinates != None:
                       # print('change')            
                       #print(cmd,street,coordinates)
                       if street in d.keys():
                                   dc={}
                                   dc[street]= coordinates
                                   for i in dc.keys():
                                               dc[i]=get_cord(dc[i])
                                   if dup_coor_check(dc)==1:
                                                Exception1('Duplicate coordinates present in the street')
                                   else:
                                            d[street]= coordinates
                       else:
                                   Exception1("'c' or 'r' specified for a street that does not exist.")
                       #print(d)
            else:
                        None
            return d

def remove(line,d):
            cmd = input_cmd(line)            
            street=input_street(line)
            #print('remove')
            #print(cmd,street)
            if street in d.keys():
                        d.pop(street)
            else:
                        Exception1("'c' or 'r' specified for a street that does not exist.")
            #print(d)
            return d

def intercection(p1,q1,p2,q2): 
    oc1 = orient_check(p1, q1, p2) 
    oc2 = orient_check(p1, q1, q2)
    oc3 = orient_check(p2, q2, p1)
    oc4 = orient_check(p2, q2, q1) 

    if ((oc1 != oc2) and (oc3 != oc4)): 
        return True
    if ((oc1 == 0) and collinear_check(p1, p2, q1)): 
        return True
    if ((oc2 == 0) and collinear_check(p1, q2, q1)):
        return True
    if ((oc3 == 0) and collinear_check(p2, p1, q2)): 
        return True
    if ((oc4 == 0) and collinear_check(p2, q1, q2)): 
        return True
    return False    


def get_distance(a,b):
    return sqrt((a[0]-b[0])**2 + (a[1]-b[1])**2)

def get_colll(x1,y1,z1):
    if round(get_distance(x1,y1) + get_distance(y1,z1),1) == round(get_distance(x1,z1),1):
        r=1
    else:
        r=0
    return r

class Coordinates: 
    def __init__(self, x, y): 
        self.x = x 
        self.y = y 
        
def collinear_check(p1, q1, r1): 
    if ( (q1.x <= max(p1.x, r1.x)) and (q1.x >= min(p1.x, r1.x)) and
        (q1.y <= max(p1.y, r1.y)) and (q1.y >= min(p1.y, r1.y))): 
        return True
    return False

def orient_check(p2, q2, r2): 
    m = (float(q2.y - p2.y) * (r2.x - q2.x)) - (float(q2.x - p2.x) * (r2.y - q2.y)) 
    if (m > 0): 
        return 1
    elif (m < 0): 
        return 2
    else:  
        return 0

def get_cord(beta):
    beta=beta.replace(" ","")
    beta=beta.replace(")(",",")
    beta=beta.replace("(","")
    beta=beta.replace(")","")
    alpha = beta.split(",")
    coor=[];
    for i in range(len(alpha)-1):    
        coordinates = (int(alpha[i]), int(alpha[i+1]))
        coor.append(coordinates)
    del coor[1::2]
    return coor

def dup_coor_check(z):
            for i in z.keys():
                        c=len(z[i])-len(list(set(map(tuple,z[i]))))
                        if c!=0:
                                    r=1
                                    break
                        else:
                                    r=0
            return r

def dup_street_check(graph):
    reverse = {} 
    graph1={}
    for i in graph.keys():
        graph1[i]=tuple(graph[i])

    for key, value in graph1.items(): 
        if value not in reverse: 
            reverse[value] = [key] 
        else: 
            reverse[value].append(key) 
    for i in reverse.keys():
        if len(reverse[i])!=1:
            r=1
        else:
            r=0
    return r

def dup_street_check1(graph):
    reverse = {} 
    graph1={}
    for i in graph.keys():
        graph1[i]=tuple(graph[i])

    for key, value in graph1.items(): 
        if value not in reverse: 
            reverse[value[::-1]] = [key] 
        else: 
            reverse[value].append(key) 
    for i in reverse.keys():
        if len(reverse[i])!=1:
            r=1
        else:
            r=0
    return r

def line_inter(a,b,c,d):
    p1=b.y-a.y
    q1=a.x-b.x
    r1=p1*a.x+q1*a.y
    
    p2=d.y-c.y
    q2=c.x-d.x
    r2=p2*c.x+q2*c.y        
    
    d = p1*q2-p2*q1
    
    if d==0:
         #Exception1('Duplicate Streets are present or overlapping coordinates are present')
         x='*'
         y='*'
    else:
        x = (q2*r1 - q1*r2)/d
        y = (p1*r2 - p2*r1)/d  
    return x,y

def find_sublists(mylst, myval):
    for sub, sublist in enumerate(mylst):
        try:
            return (sub, sublist.index(myval))
        except ValueError:
            pass
        
def edge_check1(e1,inter_p):
    r=0
    for i in range(len(e1)):
        for j in range(len(inter_p)):
            if e1[i]==inter_p[j]:
                r=1
            else:
                pass
    return r    

def edge_check2(e1,vertex_p1): 
    if vertex_p1==[]:
        ec2=0
    else:
        for j in range(len(vertex_p1)):
            ec2=get_colll(e1[0],vertex_p1[j],e1[1])
            if ec2==1:
                break
            else:
                pass
    return ec2

def collinear_check1(a1,b1,a2,b2,a3,b3):
    area = a1 * (b2 - b3) + a2 * (b3 - b1) +  a3 * (b1 - b2); 
    if int(area)==0:
        return True
    return False

def inter_colcheck(a):
    acomb =list(combinations(a, 3))
    for i in range(len(acomb)):
        (a1,b1),(a2,b2),(a3,b3) = acomb[i]
        if collinear_check1(a1,b1,a2,b2,a3,b3)==False:
            r=1
            break
        else:
            r=0
    return r

def vertex_edge(graph):
    graph2=copy.deepcopy(graph)
    if graph=={}:
        Exception1('Please add the streets before printing the edges and vertices.')
    else:
        for i in graph.keys():
            graph[i]=get_cord(graph[i])

        v=[]
        for i in graph.keys():
            v.append(graph[i])
       
        if dup_coor_check(graph)==1:
            Exception1('Duplicate coordinates present in the street')
        elif dup_street_check(graph)==1:
            Exception1('Duplicate streets are present')
       # elif dup_street_check1(graph)==1:
            #Exception1('One street is similar to other in reverse order.')
        else:
            res=[]
            for i in range(len(v)):
                b = list(zip(v[i], v[i][1:]))
                res.append(b)

            r1=[]
            for i in range(len(res)):
                j=0
                while(j<len(res[i])):
                    for k in range(i+1,len(res)):
                        l=0
                        while(l<len(res[k])):
                            r2 = res[i][j],res[k][l]
                            r1.append(r2)
                            l=l+1                
                    j=j+1
                    
            vertex_p=[]
            inter_p=[]
            edge=[]
            edge1=()
            edge2=()
            edge3=()
            edge4=()
            for i in range(len(r1)):
                (((a1, a2), (b1, b2)), ((c1, c2), (d1, d2)))=r1[i]
                #print(a1,a2,b1,b2,c1,c2,d1,d2)
                a = Coordinates(a1,a2)
                b = Coordinates(b1,b2)
                c = Coordinates(c1,c2)
                d = Coordinates(d1,d2)
                if intercection(a, b, c, d):
                            (x,y)=line_inter(a,b,c,d)
                            if x!="*" and y !="*":
                                        x = round(x,2)
                                        y = round(y,2)
                                        vertex_p.append((a1,a2))
                                        vertex_p.append((b1,b2))
                                        vertex_p.append((x,y))
                                        if float(a1)==float(x) and float(a2)==float(y):
                                                    edge1=()
                                        else:
                                                    edge1=((a1,a2),(x,y))
                                        if float(b1)==float(x) and float(b2)==float(y):
                                                    edge2=()
                                        else:
                                                    edge2=((b1,b2),(x,y))
                                        edge.append(edge1)
                                        edge.append(edge2)
                                        vertex_p.append((c1,c2))
                                        vertex_p.append((d1,d2))
                                        if float(c1)==float(x) and float(c2)==float(y):
                                                    edge3=()
                                        else:
                                                    edge3=((c1,c2),(x,y))
                                        if float(d1)==float(x) and float(d2)==float(y):
                                                    edge4=()
                                        else:
                                                    edge4=((d1,d2),(x,y))
                                        edge.append(edge3)
                                        edge.append(edge4)
                                        if (x,y) not in inter_p:
                                                    inter_p.append((round(x,2),round(y,2)))
                                        p1=find_sublists(v,(a1,a2))[0]
                                        if (x,y) not in v[p1]:
                                                    v[p1].append((x,y))
                                        q1=find_sublists(v,(c1,c2))[0]
                                        if (x,y) not in v[q1]:
                                                    v[q1].append((x,y))
                                                    #print((round(x,2),round(y,2)))
            else:
                        pass

                
            vertex_p1 = list(set(map(tuple,vertex_p)))
            v_p={}
            for i in range(len(vertex_p1)):    
                v_p[i+1] = vertex_p1[i]
            print('V = {')
            for i in v_p.keys():  
                print('  {}:  {}'.format(i,v_p[i]))
            print('}')
            
            inter_combnation =list(combinations(inter_p, 2))
            inter_list_final=[]
            for k in range(len(inter_combnation)):
                        for i in range(len(res)):
                                    for j in range(len(res[i])):
                                                a = [res[i][j][0],res[i][j][1],inter_combnation[k][0],inter_combnation[k][1]]
                                                if inter_colcheck(a)==0:
                                                            inter_list_final.append(inter_combnation[k])
                                                            break
                                                else:
                                                            pass

            edge_new=[]
            for i in range(len(edge)):
                        if len(edge[i])!=0:
                                    edge_new.append(edge[i])
            edge_final=[]
            edge_final=edge_new+list(set(map(tuple,inter_list_final)))
            
            e_p = []
            for i in range(len(edge_final)):
                e1 = edge_final[i]
                s1,s2=e1
                a1=edge_check1(e1,inter_p)
                vertex_p1 = list(set(set(tuple(list(set(map(tuple,vertex_p))))))^set(set(tuple(list(set(map(tuple,vertex_p))))).intersection(set(e1))))
                a2=edge_check2(e1,vertex_p1)
                a3=int(bool([i for i in v if s1 in i and s2 in i]))
                if a1==1 and a2==0 and a3==1:
                    e_p.append(edge_final[i])
                    #print(e1)
                    #print(a1,a2,a3)
                else:
                    pass
            e_p1 = list(set(map(tuple,e_p)))
            e_dict = {}   
            for i, edge in enumerate(e_p1):
                for index, value in v_p.items():
                    if value == edge[0]:
                        index1 = index
                    if value == edge[1]:
                        index2 = index
                e_dict[i] = (index1, index2)
            
            print('E = {')
            for i in e_dict.keys(): 
                if list(e_dict.keys()).pop()==i:
                    print('  <{},{}>'.format(e_dict[i][0],e_dict[i][1])) 
                else:
                    print('  <{},{}>,'.format(e_dict[i][0],e_dict[i][1]))
            print('}')
            graph=copy.deepcopy(graph2)
    return graph
