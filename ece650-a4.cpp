#include <iostream>
#include <string>
#include <sstream> 
#include <regex> 
#include <vector>
#include <algorithm>
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
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

void vertexcover(vector<int>edge_src_dst, int v)
{    
    vector<int> vertex_solution;
    vertex_solution.clear();
    int k,low,high;
    high = v;
    int n = v;
    low = 0;
    
  while(low<=high)
 {
   k=int(low+high)/2;
     std::vector<std::vector<Minisat::Lit> > s(n);

        Minisat::Solver solver;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < k; j++)
            {
                Minisat::Lit li = Minisat::mkLit(solver.newVar());
                s[i].push_back(li);
            }
        }
       

        for(int i=0;i<k;i++)
        {
	  Minisat::vec<Minisat::Lit> t;
        	for(int j=0;j<n;j++)
        	{

        		t.push(s[j][i]);
        	}
        	solver.addClause(t);
        	t.clear();       
        }

        for(int m=0;m<n;m++)
        {
        	for(int p=0;p<k-1;p++)
        	{
        		for(int q=p+1;q<k;q++)
        		{
        			solver.addClause(~s[m][p],~s[m][q]);
        		}
        	}
        }

        for(int m=0;m<k;m++)
        {
        	for(int p=0;p<n-1;p++)
        	{
        		for(int q=p+1;q<n;q++)
        		{
        			solver.addClause(~s[p][m],~s[q][m]);
        		}
        	}
        }
	int check5 = edge_src_dst.size();
        for(int j=0;j<check5;j=j+2)
        {
	  int a1 = edge_src_dst[j];
	  int a2 = edge_src_dst[j+1];
	  Minisat::vec<Minisat::Lit> t1;
        	for(int j=0;j<k;j++)
        	{
        		t1.push(s[a1][j]);
        		t1.push(s[a2][j]);
        	}
        	solver.addClause(t1);
        	t1.clear();}

auto res = solver.solve();
     if (res) {
                       high = k-1;
                       vertex_solution.clear();
                       for(int i = 0; i < n; i++)
                        {
                            for(int j = 0; j < k; j++)
                            {
                              Minisat::lbool tf=solver.modelValue(s[i][j]);
                               if(tf==Minisat::l_True)
                            {   

                                vertex_solution.push_back(i);
                            }

                
     }}}
     else
     {
                    low = k+1;
        }

}
     int check6 =  vertex_solution.size();
     for (int i = 0;i<check6;i++)
       {
	 cout<<vertex_solution[i]<<" ";
       }
     cout<<endl; 
     vertex_solution.clear();
}

int main()
{  string line,cmd,vert_num,edge_part,src,dst,str_edge_part;
//cout<<"entering"<<endl;
                    vector<int> edge_src_dst;
vector<int> ad_vector[9000];
while (1)
{
getline(cin,line);
if (line.length()==0)
    {
        exit(0);
    }

cmd=line[0];
if (cmd=="V" || cmd=="E")
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
        //cout<<"V "<<vert_num<<endl;
        //cout<<"E "<<edge_part<<endl;
	cout<<endl;
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
                    }
                    else{
                    int check3;
                    check3 = vec_ed.size();
                    for (int i = 0; i < check3; i++)
                    {
                    edge_src_dst.push_back(vec_ed[i]);
                    edge_src_dst.push_back(vec_ed1[i]);
                    }
		    //int check4 = edge_src_dst.size();
                    //for (int i = 0; i < check4; i++){
		    //cout << edge_src_dst[i] << " ";}
                    }
		    vertexcover(edge_src_dst,v);
		    edge_src_dst.clear();
		    //cout<<"v is "<<v<<endl;
	}

        }  
        else
        {
            error_out("Invalid input");   
        } }        
     }
}
else
{
error_out("Invalid input");    
}
}
return 0;
}
