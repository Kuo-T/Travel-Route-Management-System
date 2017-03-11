#include"define.h"
using namespace std;
ALGraph travel;
int system_time=0;
int system_date=0;
HANDLE hMutex;
HANDLE hThread;
FILE* file1;
FILE* file2;
vector< vector <road> > queue;

extern void CreateGraph(ALGraph *g);
extern void print_out_state( vector<road> &f, int Day, int time, int number, int type, FILE* file);
extern void egg_print_out_state( vector<road> &f, int Day, int time, int number, int type, FILE* file );
extern DWORD WINAPI passenger_request(LPVOID IpParameter);
extern void egg_time( int keydown );
extern void egg_passenger_request();
extern void initegg();  

int main()
{	
	char key;
	int number;
	char char_day[5];
	char char_hour[5];

	int flag=0;
	int state=0;
	char version='1';
	
	EVENT_TYPE ev;
	double X,Y;

	system_time=0;
	system_date=0;
	
	file1=fopen("Search.txt", "w");
	file2=fopen("Detail.txt", "w");
	cout<<"╭─────────────────────────────────╮"<<endl;
	cout<<"															"<<endl;
	cout<<"		  欢迎进入旅行线路查询系统 ~   ^_^		    "<<endl;
	cout<<"															"<<endl;
	cout<<"															"<<endl;
	cout<<"╰─────────────────────────────────╯"<<endl<<endl;
	CreateGraph(&travel);
	cout<<endl;
	cout<<"──────────────────────────────────"<<endl<<endl;
	cout<<"选择键盘版本请按1，选择图形化界面请按2"<<endl;
	cin>>version;
	int iferror=0;
	while(version != '1' && version != '2')
	{
		fflush(stdin);
		cout<<"──────────────────────────────────"<<endl;
		cout<<"请按照提示输入您要进入的版本！"<<endl;
		cout<<"选择键盘版本请按1，选择图形化界面请按2"<<endl;
		cin>>version;
	}
	if(version == '1')
	{
		cout<<"──────────────────────────────────"<<endl;
		cout<<"按下 P 进入查询"<<endl;
		hMutex=CreateMutex(NULL,FALSE,NULL);
		hThread=CreateThread(NULL, 0, passenger_request, NULL, 0, NULL);
		while(1)
		{
			WaitForSingleObject(hMutex, INFINITE);
			cout<<"D= "<<system_date<<" ";
			cout<<"T= "<<system_time<<endl;
			fprintf(file2, "D=%d\tT=%d\n", system_date, system_time);
			
			for( int i=0; i<queue.size(); i++){
				print_out_state(queue[i], system_date, system_time, i, 0, file2);
			}
			system_time++;
			if(system_time==24){
				system_time=0;
				system_date=system_date+1;
			}
		
			Sleep(1000);
			ReleaseMutex(hMutex);
		}
	}
	
	else if(version == '2')
	{
		initegg();
		egg_passenger_request();
	}
	return 0;
}

