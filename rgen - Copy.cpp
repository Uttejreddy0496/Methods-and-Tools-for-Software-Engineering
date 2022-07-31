#include <iostream>
#include <getopt.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>
using namespace std;
void error_out(string line)
{
    cerr << "Error: "<<line<<endl;
}
int rand_gen(int min, int max)
{
  ifstream urandom("/dev/urandom");
  if (urandom.fail()) {
    cerr << "Error: cannot open /dev/urandom\n";
    return 1;
  }
  int v=0;     
  while(1)
  {       
    urandom.read((char*)&v,1);
    v= v % ((max - min)+1) + min;
    //cout<<"RandGen: "<<v<<endl;
    if(v <= max && v >= min)
      {
	urandom.close();
	break;
        }
    } 
  return v;
}

vector<string> street_name_gen(int count)
{
 string street_name;
 vector<string> street_list;
  for(char i='a';i<='z';i++)
  {
    for(char j='a';j<='z';j++){
    street_name="\"Street ";
    string b(1,j);
    string c(1,i);
    string d = c+b;
    street_name.append(d);
    street_name =street_name + "\" ";
    street_list.push_back(street_name);
    count--;
    if(count<= 0)
    {
      break;
    }
    }
   if(count<= 0)
    {
      break;
    }
  }
  return street_list;
}
struct coordinates
{
    int x;    int y;
};
struct line_seg
{ 
    coordinates source; 
    coordinates destination;
};
bool collinear_check(coordinates p1, coordinates q1, coordinates r1) 
{ 
    if (q1.x <= max(p1.x, r1.x) && q1.x >= min(p1.x, r1.x) && 
        q1.y <= max(p1.y, r1.y) && q1.y >= min(p1.y, r1.y)) 
       return true; 

    return false; 
} 
int orient_check(coordinates p2, coordinates q2, coordinates r2) 
{ 
    int m = (q2.y - p2.y) * (r2.x - q2.x) - 
              (q2.x - p2.x) * (r2.y - q2.y); 
  
    if (m == 0) return 0;  
    return (m > 0)? 1: 2; 
}   
bool intercection(coordinates p1, coordinates q1, coordinates p2, coordinates q2) 
{ 

    int o1 = orient_check(p1, q1, p2); 
    int o2 = orient_check(p1, q1, q2); 
    int o3 = orient_check(p2, q2, p1); 
    int o4 = orient_check(p2, q2, q1); 
  
    if (o1 != o2 && o3 != o4) 
        return true; 
  
    if (o1 == 0 && collinear_check(p1, p2, q1)) return true; 
    if (o2 == 0 && collinear_check(p1, q2, q1)) return true; 
    if (o3 == 0 && collinear_check(p2, p1, q2)) return true; 
    if (o4 == 0 && collinear_check(p2, q1, q2)) return true; 
    return false;
}
int duplicate_coor_check(vector<coordinates> cod)
{
  int r=0;
  int size2=cod.size();
  for (int i = 0; i < size2; i++)
{
    for(int j=i+1;j<size2;j++)
{
if(cod[i].x == cod[j].x && cod[i].y == cod[j].y)
{r=1;}
}}
return r;
}
bool same_st_inter(vector<coordinates> streetseg,int n)
{
	bool oput;
	coordinates x1,y1,x2,y2;
	//cout<<"entered"<<endl;
	int size3=streetseg.size();
	for(int i=(size3-n-1);i<(size3-1);i++)
	{
		x1 = streetseg[i];
		y1 = streetseg[i+1];
		for(int j=i+2;j< (size3-1);j++)
		{

				x2 = streetseg[j];
				y2 = streetseg[j+1];
				/*cout<<x1.x<<" ";cout<<x1.y<<" "; cout<<y1.x<<" "; cout<<y1.y<<" ";cout<<x2.x<<" "; cout<<x2.y<<" ";cout<<y2.x<<" ";cout<<y2.y<<" ";*/
				oput = intercection(x1,y1,x2,y2);
                //cout<<oput<<endl;
				if(oput == true)
				{
					return true;
				}

			}}

return false;
}

bool collinear_area(coordinates p1,coordinates p2,coordinates p3)
{
int area = abs(p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) +  p3.x * (p1.y - p2.y));
//cout<<area<<endl;
if(area==0)
{return true;}    
return false;
}

bool collinear_four(coordinates p1,coordinates p2,coordinates p3,coordinates p4)
{
if(collinear_area(p1,p2,p3)&&collinear_area(p2,p3,p4)&&collinear_area(p1,p3,p4)&&collinear_area(p1,p2,p4))
{return true;}    
return false;
}
bool street_overlap(vector<vector<line_seg>> line_seg_vector)
{
vector<line_seg> line_seg_over;
int size_k,size_i;
size_k=line_seg_vector.size();
for (int k = 0; k < size_k ; k++){
size_i=line_seg_vector[k].size();
for (int i = 0; i < size_i; i++){
line_seg_over.push_back({line_seg_vector[k][i].source.x,line_seg_vector[k][i].source.y,line_seg_vector[k][i].destination.x,line_seg_vector[k][i].destination.y});
}}
int size_k1,size_i1;
size_k1=line_seg_over.size()-1;
for (int k = 0; k < size_k1; k++){
size_i1= line_seg_over.size();
for (int i = k+1; i < size_i1; i++){
  /*  cout<<line_seg_over[k].source.x<<line_seg_over[k].source.y<<" "
        <<line_seg_over[k].destination.x<<line_seg_over[k].destination.y<<" "
        <<line_seg_over[i].source.x<<line_seg_over[i].source.y<<" "
        <<line_seg_over[i].destination.x<<line_seg_over[i].destination.y<<endl;*/
if (collinear_four({line_seg_over[k].source.x,line_seg_over[k].source.y},
        {line_seg_over[k].destination.x,line_seg_over[k].destination.y},
        {line_seg_over[i].source.x,line_seg_over[i].source.y},
        {line_seg_over[i].destination.x,line_seg_over[i].destination.y}
        )){
return true;}}}
return false;
}
int s_min=2, s_max=10, n_min=1, n_max=5, l_min=5, l_max=5, c_min=-20, c_max=20; 
  
int main(int argc, char* argv[]) {
  int option;  char* sval;  char* nval;  char* lval;  char* cval;   
  while( (option = getopt(argc, argv, ":s:n:l:c:")) != -1 ) {
      switch(option) {
      case 's':
            sval=optarg;
            s_max=atoi(sval);
            break;
        case 'n':
            nval=optarg;
            n_max=atoi(nval);
            break;
        case 'l':
            lval=optarg;
            l_max=atoi(lval);
            break;
        case 'c':
            cval=optarg;
            c_min=-atoi(cval);
            c_max=atoi(cval);
            break;
        case ':':
            break;
        case '?':
            error_out("Invalid Input");
            return 1;
        default:
	  break;
        }
      }
  //cout<<"min values: " <<s_min<<" "<< n_min<<" "<< l_min<<" "<<c_min<<endl;
//cout<<"max values: " <<s_max<<" "<< n_max<<" "<< l_max<<" "<<c_max<<endl;
  vector<string> street_list;
  int  limit_max=0;
//for(int i=0;i<2;i++)
  int l= rand_gen(l_min,l_max);
  while(1)
    {
  int s= rand_gen(s_min,s_max);
  // cout<<"s value is "<<s<<endl;
  // cout<<"l value is "<<l<<endl;
  int size4 = street_list.size();
   if(size4>0)
    {
      int size1=street_list.size();
        for (int j=0; j<size1; j++)
        {
           cout<<"r "<<street_list[j]<<endl;  
        }
    }
  street_list=street_name_gen(s);
  //  for (int i = 0; i < street_list.size(); i++)
  //cout << street_list[i] << " ";
  vector<coordinates> cod;
  vector<line_seg> line_seg_store;
  vector<vector<line_seg>> line_seg_vector;
  vector<vector<coordinates>> coord_vector;
  coord_vector.clear();
  line_seg_vector.clear();  
  vector<string> coordinates_store;
  string coordinates_string;
  int ncoord,flag,n;
  for(int i=0;i<s;i++){
   flag=0;
   coordinates_string="";
   n= rand_gen(n_min,n_max);
  ncoord=n + 1;
  //cout<<ncoord<<endl;
  while(flag==0){
  cod.clear();
  line_seg_store.clear();
  for(int j=0;j<ncoord;j++)
    {
      int c_x=rand_gen(c_min,c_max);
      int c_y=rand_gen(c_min,c_max);
      coordinates p={c_x,c_y};
      cod.push_back(p);
    }
  //  for (int i = 0; i < cod.size(); i++)
  //cout << cod[i].x << " "<<cod[i].y << " ";
  
  if(duplicate_coor_check(cod)==1){
   limit_max++;
   if(limit_max>25)
     {error_out("failed to generate valid input for 25 simultaneous attempts");
       exit(0);}
  }
  if(same_st_inter(cod, n))
    {
         limit_max++;
     if(limit_max>25)
     {error_out("failed to generate valid input for 25 simultaneous attempts");
      exit(0);}
    }
int sizei_cod=cod.size()-1;
  for(int i=0;i<sizei_cod;i++)
 {
   for(int j = i+1;j<=i+1;j++){
     line_seg_store.push_back({cod[i].x,cod[i].y,cod[j].x,cod[j].y});
   }}
 line_seg_vector.push_back(line_seg_store);
   if(street_overlap(line_seg_vector))
    {
     limit_max++;
     if(limit_max>25)
     {error_out("failed to generate valid input for 25 simultaneous attempts");
      exit(0);}
    }
   //cout<<"limit"<<limit_max<<endl;
 if(duplicate_coor_check(cod)!=1 && same_st_inter(cod,n)!=true && street_overlap(line_seg_vector)!=true)
    {
      flag=1;
 }
  }
  int size5=cod.size();
   if(size5==ncoord)
        {
            for (int i=0;i<size5;i++)
            {
                coordinates_string+="("+to_string(cod[i].x)+","+to_string(cod[i].y)+") ";
            }
            coordinates_store.push_back(coordinates_string);     
        }
    coord_vector.push_back(cod);
  }
  //  for (int i = 0; i < coord_vector.size(); i++){
    //for (int j = 0; j < coord_vector[i].size(); j++){
  //    cout << coord_vector[i][j].x << " "<<coord_vector[i][j].y << " ";}
// cout<<endl;}
  int size6=coordinates_store.size();
  for (int i=0; i<size6; i++)     
   {
     cout <<"a "<<street_list[i]<<coordinates_store[i] << "\n";        
   }
 cout<<"g"<<endl;
 

 // cout<<"check"<<i<<endl;
 sleep(l);
    }
  return 0;
}

