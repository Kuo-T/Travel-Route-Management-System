#include"define.h"
using namespace std;
void initroad(road &storeroad);
int find_single_min(ArcNode*p,int last_city,char vehicle[],int vtype,int tocity,road&passroad);
int find_all_min(ArcNode*p1,ArcNode*p2,ArcNode*p3,int last_city,char vehicle[],int tocity,road&roadtemp);
void shortest_time(ALGraph *G, int v0, int P[], int D[], char vehicle[][5],int endcity, road roadtime[]);
void strategy_time(passenger_plan plan,ALGraph *g, road roadtime[], road finalroad[], int&real);
void egg_strategy_time(passenger_plan plan,ALGraph *g, road roadtime[], road finalroad[], int&real,int &lasty);
void Least_Time_Plan( ALGraph* g, road roadtime[], road finalroad[], int&real);
void egg_Least_Time_Plan( ALGraph* g, road roadtime[], road finalroad[], int&real,int mind,string city[],int n);

