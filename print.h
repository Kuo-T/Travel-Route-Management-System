#include"define.h"
using namespace std;
void print_out_state( vector<road> &f, int Day, int time, int number, int type, FILE* file);
void egg_print_out_state( vector<road> &f, int Day, int time, int number, int type, FILE* file );
DWORD WINAPI passenger_request(LPVOID IpParameter);
void egg_time( int keydown );
void egg_passenger_request();
void initegg(); 
