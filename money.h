#include"define.h"
using namespace std;
void citypenxy(int cityname, int &x, int &y);
int convert_char_to_int(char a[SIZE]);
int findMin(ArcNode*p1,ArcNode*p2,ArcNode*p3);
void createVehicle(char vehicle[],char start[],char arrive[],int &Expense,ALGraph *g,int m,int n);
void shortFee(string cityA,ALGraph *g,int P[10],int D[],char V[][10][SIZE]);
void strategy_fee(passenger_plan plan,ALGraph *g,road r[],int &N);
void egg_strategy_fee(passenger_plan plan,ALGraph *g,road r[],int &N);
void Least_Expense_Plan( ALGraph*g, road r[], int &N);
void egg_Least_Expense_Plan( ALGraph*g, road r[], int &N,int mind,string city[],int n);

