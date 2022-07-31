#include <iostream>
#include <string>
#include <sstream> 
#include <regex> 
#include <bits/stdc++.h> 
using namespace std;
int find_val(int v[]={},int v_size=0, int s=0)
{
    int r=0;
    for(int i=0;i<v_size;i++)
    {
        if(s==v[i])
        {
            r=1;
            break;
        }
    }
return r;
}
void error_out(string line)
{
    cerr << "Error: "<<line<<endl;
}
string deletespaces(string edge_part)
{
	edge_part.erase(remove(edge_part.begin(), edge_part.end(), ' '), edge_part.end());
	return edge_part;
}
int charactercheck(string str)
{
    int r=0;
    int v_size = str.length();
    string check = "0123456789{}<>,";
    for(int i=0;i<v_size;i++)
    {
      int a=check.find(str[i]);
        if(a==-1)
        {
            r=1;
            //cout<<str[i]<<endl;
            break;
        }
    }
return r;
}
bool bfs_algo(vector<int> ad_vector[], int src, int dst, int v,
         int pred_path[], int distance[])
{    
    list<int> q_bfs;
    bool visit_bfs[v];
    for (int x = 0; x < v; x++) {
        visit_bfs[x] = false;
        distance[x] = INT_MAX;
        pred_path[x] = -1;
    }
    visit_bfs[src] = true;    distance[src] = 0;    q_bfs.push_back(src);
    while (!q_bfs.empty()) {
        int q = q_bfs.front();        q_bfs.pop_front();
	int check;
	check = ad_vector[q].size();
        for (int y = 0; y < check; y++) {
            if (visit_bfs[ad_vector[q][y]] == false) {
                visit_bfs[ad_vector[q][y]] = true;
                pred_path[ad_vector[q][y]] = q;
                distance[ad_vector[q][y]] = distance[q] + 1;
                q_bfs.push_back(ad_vector[q][y]);
                if (ad_vector[q][y] == dst)
                    return true;
            }
        }
    }
    return false;
}

int edge_check(string edge_part)
{
    string str1,str2,str3,str4,str5,str6;
    int r=0;
    str1="{<";    str2=">}";    str3="><";    str4="<,";    str5=",>";    str6="<>";
    string str = deletespaces(edge_part);
    int r1=charactercheck(str);
    int s1=count(str.begin(), str.end(), '<');
    int s2=count(str.begin(), str.end(), '>');
    int s3=count(str.begin(), str.end(), ',');
    int b1,b2,b3,b4,b5,b6;
    b1=str.find(str1);b2=str.find(str2);b3=str.find(str3);b4=str.find(str4);b5=str.find(str5);b6=str.find(str6);
    if (b1!=-1 && (s3==2*s1-1) && b2!=-1 && b3==-1 && b4==-1 && b5==-1 && b6==-1 && 
    (s1==s2) && r1!=1){
    //cout<<str<<endl;
    }
    else{r=1;}
    return r;
}

void add_edge(vector<int> ad_vector[], int src, int dst)
{
    ad_vector[src].push_back(dst);    ad_vector[dst].push_back(src);
}

void string_array(int* store_edge, string edge){
    string input (edge); 
    smatch match;
    regex exp1("(\\d+)");
    int x = 0;
    while(regex_search(input, match, exp1)){
        store_edge[x] = stoi(match.str());
        input = match.suffix().str();
        x++;
    }
}
void distance_short(vector<int> ad_vector[], int src,
                           int dst, int v)
{
    int pred_path[v], distance[v]; 
    if (bfs_algo(ad_vector, src, dst, v, pred_path, distance) == false) {
        error_out("Path does not exist");
        return;
    }
    vector<int> final_path;
    int find_dest = dst;
    final_path.push_back(find_dest);
    while (pred_path[find_dest] != -1) {
        final_path.push_back(pred_path[find_dest]);
        find_dest = pred_path[find_dest];
    } 
    for (int i = final_path.size() - 1; i >= 0; i--)
        if(i==0){
        cout << final_path[i] <<endl;}
        else{
        cout << final_path[i] <<"-";}
}
int main()
{  string line,cmd,vert_num,edge_part,src,dst,str_edge_part;
int src_r,dst_r,v_size;
vector<int> ad_vector[9000];
while (1)
{
getline(cin,line);
if (line.length()==0)
    {
        exit(0);
    }
cmd=line[0];
if (cmd=="V" || cmd=="E"|| cmd=="s")
{
        //cout<<"the line is "<<line<<endl;
    if (cmd=="V")
    {
        regex v("[A-Za-z] [0-9][[0-9]*"); 
        if ( regex_match(line, v))
        {
        vert_num=line.substr(2, line.length()-2);
        stringstream conv(vert_num); 
        int x = 1; conv >> x; 
        int vertex_values[x];
	memset(vertex_values, 0, x*sizeof(int) );
	    edge_part.clear();
        for (auto& a : ad_vector) {
        a.clear();
        }
        for(int i=0;i<x;i++)
            vertex_values[i]=i;
        //for(int i=0;i<(sizeof(vertex_values)/sizeof(vertex_values[0]));i++)
        //{
        //cout<<vertex_values[i]<<endl;}
        //cout<<cmd<<endl;
        }         
        else
        {
            error_out("Invalid input");   
        }
    }
    else if (cmd=="E")
    { 
        int vertex_length =  vert_num.length();
        if(vertex_length==0)
        {
            error_out("Please enter the no of vertices first");
        }
	else  if(line[2]=='{'&& line[3]=='}')
        {
        edge_part=line.substr(2, line.length()-2);
        }
        else{
        if (line[2]=='{')
        {
        edge_part=line.substr(2, line.length()-2);
        //cout<<cmd<<endl;        
        str_edge_part = deletespaces(edge_part);
        //cout<<str_edge_part<<endl;
        if(edge_check(edge_part)!=0)
        {
            error_out("Invalid input");   
        }
        else{  
                vector<int> vec_ed;
                vector<int> vec_ed1;
                int r=0;
                stringstream conv(vert_num); 
                int x = 0; conv >> x;
                int v=x;
                string input = str_edge_part;
                smatch match;
                regex exp1("(\\d+,\\d+)");
                while (regex_search(input, match, exp1))
                {        
		  int store_edge[2]={0,0}; 
                    string edge = match.str();
                    string_array(store_edge, edge);
                    add_edge(ad_vector, store_edge[0], store_edge[1]);
                    vec_ed.push_back(store_edge[0]);
                    vec_ed1.push_back(store_edge[1]);
                    //cout << store_edge[0] <<store_edge[1] <<endl;         
                    input = match.suffix().str();
                }
		int check2;
		check2 = vec_ed.size();
                 for (int i = 0; i < check2; i++)
                    {
                        if(vec_ed[i]==vec_ed1[i]||vec_ed1[i]>=v||vec_ed[i]>=v)
                        {
                            r=1;
                            break;
                        }        
                    }
		 // cout<<r<<endl;
                    if(r==1)
                    {
                    error_out("Invalid Edges");
                    }}

        }  
        else
        {
            error_out("Invalid input");   
        } }
    }
    else if (cmd=="s")
    {
        int vertex_length =  vert_num.length();
        int edge_length =  edge_part.length();
        if(vertex_length==0 || edge_length==0)
        {
            error_out("Please enter the vertices and edges first");
        }
        else{
        regex s("[A-Za-z] [0-9][[0-9]* [0-9][[0-9]*"); 
        if ( regex_match(line, s))
        {
        src=line.substr(2, line.find_last_of(" ")-1);
        dst=line.substr(line.find_last_of(" ")+1,line.length()-line.find_last_of(" "));
        stringstream conv(vert_num); 
        int x = 1; conv >> x; 
        int v=x;
        int vertex_values[x];
	memset(vertex_values, 0, x*sizeof(int) );
        for(int i=0;i<x;i++)
        vertex_values[i]=i;
        v_size=sizeof(vertex_values)/sizeof(vertex_values[0]); 
        stringstream conv1(src); 
        int x2 = 0; conv1 >> x2; 
        vector<int> vec_ed;
        vector<int> vec_ed1;     
        int src1=x2;
        src_r=find_val(vertex_values,v_size,src1);
        stringstream conv2(dst); 
        int x3 = 0; conv2 >> x3; 
        int dst1=x3;
        dst_r=find_val(vertex_values,v_size,dst1);
        if(src_r!=1 || dst_r!=1)
        {
        error_out("Either source or destination entered does not exist");
        }
	else if(src1==dst1)
        {
	  cout<<src1<<endl;
        }	
        else{      
            distance_short(ad_vector, src1, dst1, v);
        }                   
        }
        else
        {
        error_out("Invalid input");   
        }}
    }
}
else
{
error_out("Invalid input");    
}
}
return 0;
}

