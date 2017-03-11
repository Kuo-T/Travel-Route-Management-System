#include"print.h"
using namespace std;
extern ALGraph travel;
extern int system_time;
extern int system_date;
extern HANDLE hMutex;
extern HANDLE hThread;
extern FILE* file1;
extern FILE* file2;
extern vector< vector <road> > queue;
extern void citypenxy(int cityname, int &x, int &y);
extern void Least_Expense_Plan( ALGraph*g, road r[], int &N);
extern void egg_Least_Expense_Plan( ALGraph*g, road r[], int &N,int mind,string city[],int n);
extern void Least_Time_Plan( ALGraph* g, road roadtime[], road finalroad[], int&real);
extern void egg_Least_Time_Plan( ALGraph* g, road roadtime[], road finalroad[], int&real,int mind,string city[],int n);
extern void LTLE( vector< road > &re , ALGraph* travel, int system_time);
extern void egg_LTLE( vector< road >& re , ALGraph* travel, int system_time ,int pass,string city[],int m);
void print_out_state( vector<road> &f, int Day, int time, int number, int type, FILE* file)
{
	int T=0, D=0, t=0;
	int tag=0;
	int flag=0;
	int start_time=0;
	int arrive_time=0;
	int alt_start_time=0;
	int alt_arrive_time=0;
	char temp[SIZE];
	int i=0,j=0,k=0;
	
	while(i<f.size()&& flag==0){
		t=T;
		start_time=atoi(f[i].start_time);
		if( f[i].arrive_time[0]=='s')  tag=1;
		if( f[i].arrive_time[0]=='t')  tag=2;
		for( j=0, k=0; j<SIZE && k<SIZE; k++){
			if( f[i].arrive_time[k]<='9' && f[i].arrive_time[k]>='0'){
				temp[j]=f[i].arrive_time[k];
				j++;
			}
		}
		arrive_time=atoi(temp);
		if( start_time<T ){
			alt_start_time=start_time+24;
			if( tag==1 )  alt_arrive_time=arrive_time+24+24;
			else if (tag==2)  alt_arrive_time=arrive_time+48+24;
			else alt_arrive_time=arrive_time+24;
		}
		else if( start_time>=T ){
			alt_start_time=start_time;
			if( tag==1 )  alt_arrive_time=arrive_time+24;
			else if (tag==2)  alt_arrive_time=arrive_time+48;
			else alt_arrive_time=arrive_time;
		}	
		for(j=0; j<SIZE; j++)  temp[j]='\0';
			
		while( t<=alt_start_time ){
			if( D==Day && T==time ){
				if( type==1 )
					fprintf(file, "D=%d\tT=%d\n", D, T);
				fprintf(file, "Passenger %d stay at %s.\n", number, travel.adjlist[f[i].from].city_name.c_str() );
				cout<<"stay at "<< travel.adjlist[f[i].from].city_name<< endl;
				flag=1;
				break;
			}
			T++;
			if( T==24 ){
				D++;
				T=0;
			}
			t++;
			
		}
		if(flag==1)
		{
			break;
		}
		while( t<alt_arrive_time ){
			if( D==Day && T==time ){
				if(type==1)	fprintf(file, "D=%d\tT=%d\n", D, T);
				if( f[i].number[0]=='T'){
					fprintf(file, "Passenger %d takes train %s from %s to %s.\n", number, f[i].number, travel.adjlist[f[i].from].city_name.c_str(), travel.adjlist[f[i].to].city_name.c_str() );
					cout<<"Take train "<<f[i].number<<" from "<<travel.adjlist[f[i].from].city_name<<" to "<< travel.adjlist[f[i].to].city_name<< endl;
				}
				else if( f[i].number[0]=='P'){
					fprintf(file, "Passenger %d takes plane %s from %s to %s.\n", number, f[i].number, travel.adjlist[f[i].from].city_name.c_str(), travel.adjlist[f[i].to].city_name.c_str() );
					cout<<"Take Plane "<<f[i].number<<" from "<<travel.adjlist[f[i].from].city_name<<" to "<< travel.adjlist[f[i].to].city_name<< endl;
				}
				else{
					fprintf(file, "Passenger %d takes bus %s from %s to %s.\n", number, f[i].number, travel.adjlist[f[i].from].city_name.c_str(), travel.adjlist[f[i].to].city_name.c_str() );
					cout<<"Take Bus "<<f[i].number<<" from "<<travel.adjlist[f[i].from].city_name<<" to "<< travel.adjlist[f[i].to].city_name<< endl;
				}
				flag=1;
				break;
			}
			T++;
			if( T==24 ){
				T=0;
				D++;
			}
			t++;
		}
		if(flag==1)
		{
			break;
		}

		i++;
		
	}	
	if(i==f.size()){
		cout<<"Arrived at destination "<< travel.adjlist[f[i-1].to].city_name.c_str()<< endl;
		fprintf(file, "Passenger %d Arrived at destination %s .\n", number, travel.adjlist[f[i-1].to].city_name.c_str() );
	}
		
}
void egg_print_out_state( vector<road> &f, int Day, int time, int number, int type, FILE* file )
{
	int T=0, D=0, t=0;
	int tag=0;
	int flag=0;
	int start_time=0;
	int arrive_time=0;
	int alt_start_time=0;
	int alt_arrive_time=0;
	char temp[SIZE];
	char T1[5];
	int i=0,j=0,k=0;
	int M=0;
	int x1,y1,x2,y2;
	
	while(i<f.size()&& flag==0){
		t=T;
		start_time=atoi(f[i].start_time);
		if( f[i].arrive_time[0]=='s')  tag=1;
		if( f[i].arrive_time[0]=='t')  tag=2;
		for( j=0, k=0; j<SIZE && k<SIZE; k++){
			if( f[i].arrive_time[k]<='9' && f[i].arrive_time[k]>='0'){
				temp[j]=f[i].arrive_time[k];
				j++;
			}
		}
		arrive_time=atoi(temp);
		if( start_time<T ){
			alt_start_time=start_time+24;
			if( tag==1 )  alt_arrive_time=arrive_time+24+24;
			else if (tag==2)  alt_arrive_time=arrive_time+48+24;
			else alt_arrive_time=arrive_time+24;
		}
		else if( start_time>=T ){
			alt_start_time=start_time;
			if( tag==1 )  alt_arrive_time=arrive_time+24;
			else if (tag==2)  alt_arrive_time=arrive_time+48;
			else alt_arrive_time=arrive_time;
		}	
		for(j=0; j<SIZE; j++)  temp[j]='\0';
			
		while( t<=alt_start_time ){
			if( D==Day && T==time ){
				if( type==1 )
					fprintf(file, "D=%d\tT=%d\n", D, T);
				fprintf(file, "Passenger %d stay at %s.\n", number, travel.adjlist[f[i].from].city_name.c_str() );
				MovePen(600,240);
				DrawString("T= ");
				itoa(T,T1,10);
				DrawString(T1);
				DrawString("stay at ");
				DrawString((char*)(travel.adjlist[f[i].from].city_name).data());
				DrawString("                                          			     ");
				MovePen(600,150);
	            DrawBitmap("等待.BMP") ;
				SetPenColor(RED);
				citypenxy(f[i].from, x1, y1);
				MovePen(x1,y1);
				DrawArc(7.5, 0, 360);
			
				MovePen(600,240);
				SetPenColor(BLACK);
				flag=1;
				break;
			}
			T++;
			if( T==24 ){
				D++;
				T=0;
			}
			t++;
			
		}
		if(flag==1)
		{
			break;
		}
		while( t<alt_arrive_time ){
			if( D==Day && T==time ){
				if(type==1)	fprintf(file, "D=%d\tT=%d\n", D, T);
				if( f[i].number[0]=='T'){
					fprintf(file, "Passenger %d takes train %s from %s to %s.\n", number, f[i].number, travel.adjlist[f[i].from].city_name.c_str(), travel.adjlist[f[i].to].city_name.c_str() );
				}
				else if( f[i].number[0]=='P'){
					fprintf(file, "Passenger %d takes plane %s from %s to %s.\n", number, f[i].number, travel.adjlist[f[i].from].city_name.c_str(), travel.adjlist[f[i].to].city_name.c_str() );
				}
				else{
					fprintf(file, "Passenger %d takes bus %s from %s to %s.\n", number, f[i].number, travel.adjlist[f[i].from].city_name.c_str(), travel.adjlist[f[i].to].city_name.c_str() );
				}
				MovePen(600,240);
				DrawString("T= ");
				itoa(T,T1,10);
				DrawString(T1);
				DrawString(" ");
				if( f[i].number[0]=='T'){
				    DrawString("Take train ");
				    DrawString(f[i].number);
				    DrawString(" ");
				    DrawString("from");
				    DrawString((char*)(travel.adjlist[f[i].from].city_name).data());
				    citypenxy(f[i].from, x1, y1);
				    DrawString(" to");
				    DrawString((char*)(travel.adjlist[f[i].to].city_name).data());
				    citypenxy(f[i].to, x2, y2);
				    DrawString("                           			   ");
				    MovePen(600,150);
	                DrawBitmap("空白.BMP") ;
				    MovePen(800,150);
				    DrawBitmap("火车.BMP") ;
					SetPenColor(GREEN);
					MovePen(x1,y1);
                    DrawLine(x2-x1,y2-y1);
                    MovePen(600,240);
				    SetPenColor(BLACK);
				}
				else if( f[i].number[0]=='P'){
					DrawString("Take Plane ");
				    DrawString(f[i].number);
				    DrawString(" ");
				    DrawString("from");
				    DrawString((char*)(travel.adjlist[f[i].from].city_name).data());
				    citypenxy(f[i].from, x1, y1);
				    DrawString(" to");
				    DrawString((char*)(travel.adjlist[f[i].to].city_name).data());
				    citypenxy(f[i].to, x2, y2);
				    DrawString("                           			   ");
				    MovePen(600,150);
	                DrawBitmap("空白.BMP") ;
				    MovePen(800,150);
				    DrawBitmap("飞机.BMP") ;
				    SetPenColor(BLUE);
					MovePen(x1,y1);
                    DrawLine(x2-x1,y2-y1);
                    MovePen(600,240);
				    SetPenColor(BLACK);
				}
				else{
					DrawString("Take Bus ");
				    DrawString(f[i].number);
				    DrawString(" ");
				    DrawString("from");
				    DrawString((char*)(travel.adjlist[f[i].from].city_name).data());
				    citypenxy(f[i].from, x1, y1);
				    DrawString(" to");
				    DrawString((char*)(travel.adjlist[f[i].to].city_name).data());
				    citypenxy(f[i].to, x2, y2);
				    DrawString("                            			   ");
				    MovePen(600,150);
	                DrawBitmap("空白.BMP") ;
				    MovePen(800,150);
				    DrawBitmap("汽车.BMP") ;
				    SetPenColor(MAGENTA);
					MovePen(x1,y1);
                    DrawLine(x2-x1,y2-y1);
                    MovePen(600,240);
				    SetPenColor(BLACK);
				}
				flag=1;
				break;
			}
			T++;
			if( T==24 ){
				T=0;
				D++;
			}
			t++;
		}
		if(flag==1)
		{
			break;
		}

		i++;
		
	}	
	if(i==f.size()){
		MovePen(600,240);
		DrawString("Arrived at destination ");
		DrawString((char*)(travel.adjlist[f[i-1].to].city_name).data());
		DrawString("            			             ");
		MovePen(600,150);
	    DrawBitmap("等待.BMP") ;
	    fprintf(file, "Passenger %d Arrived at destination %s .\n", number, travel.adjlist[f[i-1].to].city_name.c_str() );
	}
}


DWORD WINAPI passenger_request(LPVOID IpParameter)
{
	char req;
	road r[10];
	road f[10];
	vector <road> rr;
	int N=0, real=0,i=0;
	int size=0;
	char choice='0';
	vector<road> temp;
	int number=0;
	while(1){
		WaitForSingleObject(hMutex, INFINITE);
		if(kbhit())
		{
			fflush(stdin);
			req=getchar();
			while(req!=EOF){
				if(req=='P'){
					cout<<"──────────────────────────────────"<<endl;			
					cout<<"请输入您要选择的策略："<<endl; 
					cout<<"按下1 选择最小费用策略"<<endl; 
					cout<<"按下2 选择最短时间策略："<<endl; 
					cout<<"按下3 选择限定时间内的最小费用策略："<<endl; 
					cin>>choice;
					
					while(choice != '1' && choice != '2' && choice != '3')
					{
						fflush(stdin);
						cout<<"──────────────────────────────────"<<endl;
						cout<<"请按照提示重新输入输入！< 1-最小费用；2-最短时间；3-限定时间的最小费用 >"<<endl;
						cin>>choice;
					} 
					
					switch(choice){
						case '1':
							fflush(stdin);
							Least_Expense_Plan(&travel, f, N);
							size=N;
							for( i=0; i<N; i++ ){
								temp.push_back(f[i]);
							}
							break;
						case '2':
							fflush(stdin);
							Least_Time_Plan(&travel, r,f,real);
							size=real;
							for( i=0; i<real; i++ ){
								temp.push_back(f[i]);
							}
							break;
						case '3':
							fflush(stdin);
							LTLE(rr, &travel, system_time);
							size=rr.size();
							for( i=0;i<rr.size();i++ ){
								temp.push_back(rr[i]);
							}
							break;
					}
					queue.push_back(temp);
					for(i=0; i<size; i++ )  temp.pop_back();
				}
				else if(req=='S'){
					cout<<"请输入查询的旅客编号"<< endl;
					cin>>number;
					print_out_state( queue[number], system_date, system_time, number, 1, file1);
				}
				else{
					cout<<"请按提示进行输入！< P-查询旅行计划;S-实时监控 >"<< endl;
				} 
				fflush(stdin);
				req=getchar();
			}
		}
		ReleaseMutex(hMutex);
	}
}


void egg_time( int keydown )
{
	char char_day[5];
	char char_hour[5];
		MovePen(820,790);
		DrawString("D ");
		itoa(system_date,char_day,10);
		itoa(system_time,char_hour,10);
		DrawString(char_day);
		DrawString("    T ");
		DrawString(char_hour);
		DrawString("    ");
		fprintf(file2, "D=%d\tT=%d\n", system_date, system_time);
		
		//cout<<queue.size()<< endl;
		for( int i=0; i<queue.size(); i++){
			print_out_state(queue[i], system_date, system_time, i, 0, file2);
		}
		system_time++;
		if(system_time==24){
			system_time=0;
			system_date=system_date+1;
		}
}
		

void egg_passenger_request()
{
	char req;
	road r[10];
	road f[10];
	vector <road> rr;
	int N=0, real=0,i=0,j=0;
	int size=0;
	int choice=0;
	vector<road> temp;
	char number[5];
	int number1=0;
	double X,Y;
	char char_day[5];
	char char_hour[5];
	EVENT_TYPE ev;
	system_time=0;
	system_date=0;
	int mind=0;
	int stra=0;
	int flag=0;
	int flaggg=0;
	int loc=0;
	string CityLine[10];
	int keydown=0;
	StartTimer(1000);
		while((ev=WaitForEvent())!=EXIT)
		{
			switch (ev)
			{
				
				case TIMER:
					if(keydown == 0)
					{
						egg_time(keydown);
					}
					break;
					
				case KEYDOWN:
					if(GetStruckKey() == VK_LBUTTON)
					{
						keydown=1;
						X = GetMouseX();
						Y = GetMouseY();
						if((X >= 0 && X <= 100) && (Y >= 180 && Y <= 233))
						{
							MovePen(200,200);
							DrawString(" 请选择策略^_^                                      ");
							MovePen(600,625);
							DrawBitmap("策略空白.BMP");
							flag=2;
						}
						if(flag==2)
						{
							if((X >= 600 && X <= 733) && (Y >= 700 && Y <= 750))
							{
								stra=1;
							}
							else if((X >= 734 && X <= 866) && (Y >= 700 && Y <= 750))
							{
								stra=2;
							}
							else if((X >= 867 && X <= 1000) && (Y >= 700 && Y <= 750))
							{
								stra=3;
							}
							if(stra == 1)
							{
								
								if((X >= 600 && X <= 1000) && (Y >= 670 && Y <= 700))
								{	
									StopTimer();
									if((X >= 600 && X <= 800) && (Y >= 670 && Y <= 700))
										mind=0;
									else if((X >= 801 && X <= 1000) && (Y >= 670 && Y <= 700))
										mind=1;
									flaggg=1; 
										MovePen(200,200);
						             	DrawString("                                            ");
									
								}
								
							}
							if(stra == 2)//下次初始化！！！！！ 
							{
								if((X >= 600 && X <= 1000) && (Y >= 670 && Y <= 700))
								{
									StopTimer();
									if((X >= 600 && X <= 800) && (Y >= 670 && Y <= 700))
										mind=0;
									else if((X >= 801 && X <= 1000) && (Y >= 670 && Y <= 700))
										mind=1;
									flaggg=1; 
									MovePen(200,200);
						            DrawString("                                                ");
									
								}
								
							}
							if(stra == 3)
							{
								
								if((X >= 600 && X <= 1000) && (Y >= 670 && Y <= 700))
								{
									StopTimer();
									if((X >= 600 && X <= 800) && (Y >= 670 && Y <= 700))
										mind=0;
									else if((X >= 801 && X <= 1000) && (Y >= 670 && Y <= 700))
										mind=1;
									flaggg=1; 
									MovePen(200,200);
						            DrawString("                                                ");
								}
								
							}
						}
						if(flaggg==1)
						{
							MovePen(200,233);
							DrawString("在地图处选中计划:(选择结束请按确认)");
						
							if(X>=403&&X<=418&&Y>=688.5&&Y<=703.5)
							{
								MovePen(200+loc*50,200);
						        DrawString("长春");
								CityLine[loc]="Changchun";
						        loc++;
							}
							if(X>=287&&X<=302&&Y>=600.5&&Y<=615.5)
							{
								MovePen(200+loc*50,200);
						        DrawString("北京");
								CityLine[loc]="Beijing";
						        loc++;
							}
							if(X>=249&&X<=264&&Y>=556.5&&Y<=571.5)
							{
								MovePen(200+loc*50,200);
						        DrawString("石家庄");
								CityLine[loc]="Shijiazhuang";
						        loc++;
							}
							if(X>=127&&X<=142&&Y>=512.5&&Y<=527.5)
							{
								MovePen(200+loc*50,200);
						        DrawString("西安");
								CityLine[loc]="Xi'an";
						        loc++;
							}
							if(X>=130&&X<=145&&Y>=432.5&&Y<=447.5)
							{
								MovePen(200+loc*50,200);
						        DrawString("成都");
								CityLine[loc]="Chengdu";
						        loc++;
							}
							if(X>=217&&X<=232&&Y>=396.5&&Y<=411.5)
							{
								MovePen(200+loc*50,200);
						        DrawString("重庆");
								CityLine[loc]="Chongqing";
						        loc++;
							}
						    if(X>=297&&X<=312&&Y>=326.5&&Y<=341.5)
							{
								MovePen(200+loc*50,200);
						        DrawString("广州");
								CityLine[loc]="Guangzhou";
						        loc++;
							}
                            if(X>=293&&X<=308&&Y>=436.5&&Y<=451.5)
							{
								MovePen(200+loc*50,200);
						        DrawString("长沙");
								CityLine[loc]="Changsha";
						        loc++;
							}
                            if(X>=350&&X<=365&&Y>=496.5&&Y<=511.5)
							{
								MovePen(200+loc*50,200);
						        DrawString("南京");
								CityLine[loc]="Nanjing";
						        loc++;
							}
	                        if(X>=417&&X<=432&&Y>=480.5&&Y<=495.5)
							{
								MovePen(200+loc*50,200);
						        DrawString("上海");
								CityLine[loc]="Shanghai";
						        loc++;
							}

						}
						if(flaggg==1&&(X >= 250 && X <= 500) && (Y >= 0 && Y <= 60))
						{
							
							if(stra==1)
							{
								egg_Least_Expense_Plan(&travel, f, N,mind,CityLine,loc-1);
							    flaggg=0;
								loc=0;
								size=N;
								for( i=0; i<N; i++ ){
									temp.push_back(f[i]);
								}
								for( i=0; i<real; i++ ){
									temp.push_back(f[i]);
								}
								queue.push_back(temp);
								for(i=0; i<size; i++ )  temp.pop_back();
								keydown=0;
								StartTimer(1000);
							}
						    else if(stra==2)
							{
							    egg_Least_Time_Plan(&travel, r,f,real,mind,CityLine,loc-1);
							    flaggg=0;
							    loc=0;
								size=real;
								for( i=0; i<real; i++ ){
									temp.push_back(f[i]);
								}
								queue.push_back(temp);
								for(i=0; i<size; i++ )  temp.pop_back();
								keydown=0;
								StartTimer(1000);
							}
							else if(stra==3)	
							{
								egg_LTLE(rr, &travel, system_time, mind,CityLine,loc-1);
								flaggg=0;
							    loc=0;
								size=rr.size();
								for( i=0;i<rr.size();i++ ){
									temp.push_back(rr[i]);
								}
								for( i=0; i<real; i++ ){
									temp.push_back(f[i]);
								}
								queue.push_back(temp);
								for(i=0; i<size; i++ )  temp.pop_back();
								keydown=0;
								StartTimer(1000);
							}
							MovePen(200,233);
							DrawString("                                                                            ");
						}
					   if((X >= 100 && X <= 200) && (Y >= 180 && Y <= 233))
						{
							MovePen(200,200);
							DrawString("   请输入查询的旅客编号^_^");
							flag=1;
						}
					    
						if(flag==1)
						{
								
								if((X >= 0 && X <= 100) && (Y >= 120 && Y <= 180))
								{
									MovePen(200+(j-1)*15,200);
								    DrawString("0                                                           ");
								    number[j-1]='0';
								}
								else if((X >= 100 && X <= 200) && (Y >= 120 && Y <= 180))
								{
									MovePen(200+(j-1)*15,200);
								    DrawString("1                                                           ");
								    number[j-1]='1';
								}
								else if((X >= 200 && X <= 300) && (Y >= 120 && Y <= 180))
								{
									MovePen(200+(j-1)*15,200);
								    DrawString("2                                                           ");
								    number[j-1]='2';
								}
								else if((X >= 300 && X <= 400) && (Y >= 120 && Y <= 180))
								{
									MovePen(200+(j-1)*15,200);
								    DrawString("3                                                           ");
								    number[j-1]='3';
								}
								else if((X >= 400 && X <= 500) && (Y >= 120 && Y <= 180))
								{
									MovePen(200+(j-1)*15,200);
								    DrawString("4                                                            ");
								    number[j-1]='4';
								}
								else if((X >= 0 && X <= 100) && (Y >= 60 && Y <= 120))
								{
									MovePen(200+(j-1)*15,200);
								    DrawString("5                                                           ");
								    number[j-1]='5';
								}
								else if((X >= 100 && X <= 200) && (Y >= 60 && Y <= 120))
								{
									MovePen(200+(j-1)*15,200);
								    DrawString("6                                                           ");
								    number[j-1]='6';
								}
								else if((X >= 200 && X <= 300) && (Y >= 60 && Y <= 120))
								{
									MovePen(200+(j-1)*15,200);
								    DrawString("7                                                           ");
								    number[j-1]='7';
								}
								else if((X >= 300 && X <= 400) && (Y >= 60 && Y <= 120))
								{
									MovePen(200+(j-1)*15,200);
								    DrawString("8                                                          ");
								    number[j-1]='8';
								}
								else if((X >= 400 && X <= 500) && (Y >= 60 && Y <= 120))
								{
									MovePen(200+(j-1)*15,200);
								    DrawString("9                                                          ");
								    number[j-1]='9';
								}
								j++;
								
							}
							if(flag==1&&(X >= 250 && X <= 500) && (Y >= 0 && Y <= 60))
						    {
							    flag=0;
							    j=0;
								number1=atoi(number);
								egg_print_out_state( queue[number1], system_date, system_time, number1, 1, file1);
								
								keydown=0;
						    }
								
					}
					break;
				case KEYUP:
					X = GetMouseX();
					Y = GetMouseY();
					break;
			} 
		}
		StopTimer();
		if(ev!=EXIT)
		{
			MovePen(0,700);

			WaitForExit();
		}	
}
	

void initegg()
{
	HEGG hEgg;
	EggStart(1000, 800);
	hEgg=LayEgg();
	DrawBitmap("背景.BMP");
	SetPenWidth(2); 
	MovePen(418,696);//长春
	DrawArc(7.5, 0, 360);
	MovePen(302,608);//北京 
	DrawArc(7.5, 0, 360);
	MovePen(264,564);//石家庄 
	DrawArc(7.5, 0, 360);
	MovePen(142,520);//西安 
	DrawArc(7.5, 0, 360);
	MovePen(145,440);//成都 
	DrawArc(7.5, 0, 360);
	MovePen(232,404);//重庆 
	DrawArc(7.5, 0, 360);
	MovePen(312,334);//广州 
	DrawArc(7.5, 0, 360);
	MovePen(308,444);//长沙 
	DrawArc(7.5, 0, 360);
	MovePen(365,504);//南京 
	DrawArc(7.5, 0, 360);
	MovePen(432,488);//上海 
	DrawArc(7.5, 0, 360);
}
