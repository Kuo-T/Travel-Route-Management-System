#include"define.h"
using namespace std;
void transfer( ALGraph *g );
void init( int a[], int n );
void initm( ALGraph *g );
int first( int v );
int next( int v, int w );
void printpath( vector<vector<int> >& path );
int check( vector<int> temp, vector<passing1> array );
ANode* GetEdge( ALGraph*g, int a, int b, int &i, int &flag, vector<int> temp);
void refresh( ALGraph*g, int a, int b, int &i, int &flag, vector<int> temp );
vector< road > result( ALGraph* g, vector<int> temp, int a, int b, int MAX);
void dfs( int v, int end, vector<int> temp, vector<vector<int> >& path, vector< passing1 > array, int pass);
void LTLE( vector< road > &re , ALGraph* travel, int system_time);
void egg_LTLE( vector< road >& re , ALGraph* travel, int system_time ,int pass,string city[],int m);
