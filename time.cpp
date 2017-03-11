#include"time.h"
using namespace std;
int input_time=0;
int last_time[10][5]={0};
extern int system_time;
extern void citypenxy(int cityname, int &x, int &y);
extern int LocateVex(string city,ALGraph *g);
void initroad(road &storeroad)
{
	for(int arrt=0; arrt<3; arrt++)
	{
		storeroad.arrive_time[arrt]='\0';
		storeroad.start_time[arrt]='\0';
	}
	storeroad.expense=0;
	for(int numt=0; numt<5; numt++)
	{
		storeroad.number[numt]='\0';
	}
	storeroad.from=0;
	storeroad.to=0;
}

int find_single_min(ArcNode*p,int last_city,char vehicle[],int vtype,int tocity,road&passroad)//找到某种特定交通方式的最短时间 返回int小时数 
{
	int cur_cost_time;//当前花费时间
	int min=INFINITY; 
	int way;//两tiao路线 
	
	int last_arrive_time=last_time[last_city][4];
	int start;
	int temp;// 用于复制指针中的时间 
	int j;// 用于复制车次信息 
	int tempp=0;
	char arrive_time[3]={'\0'};
	char store_number[2][5]={'\0'}; 
	int store_time[2];
	int store_arrive[2];
	int intstart,intarrive;
	store_arrive[0]=0;
	store_arrive[1]=0;
	store_time[0]=INFINITY;
	store_time[1]=INFINITY;
	road storeroad[2];
	
	initroad(storeroad[0]);
	initroad(storeroad[1]);
	
	if(p != NULL)
	{
		for(way=0; way<2; way++)
		{
			for(int arrt=0; arrt<3; arrt++)
			{
				storeroad[way].arrive_time[arrt]=p->way[way].arrival_time[arrt];
				storeroad[way].start_time[arrt]=p->way[way].start_time[arrt];
			}
			storeroad[way].expense=atoi(p->way[way].expense);
			for(int numt=0; numt<5; numt++)
			{
				storeroad[way].number[numt]=p->way[way].number[numt];
			}
			storeroad[way].from=last_city;
			storeroad[way].to=tocity;
			
			intstart=atoi(p->way[way].start_time);
			if(intstart != 0)
			{
			 
				for(temp=0; temp<3; temp++)//完成复制数据 
				{
					arrive_time[temp]='\0';
				} 
				
				for(j=0;j<5;j++)
					store_number[way][j]=p->way[way].number[j];
				
				if(p->way[way].arrival_time[0] != 's' && p->way[way].arrival_time[0] != 't')
				{
					intarrive=atoi(p->way[way].arrival_time); 
					cur_cost_time=intarrive-intstart;
				}
				
				else if(p->way[way].arrival_time[0] == 's')
				{
					tempp=0;
					for(temp=1;temp<3;temp++)
					{
						arrive_time[tempp]=p->way[way].arrival_time[temp];
						tempp++;
					}
						
					intarrive=atoi(arrive_time); 
					cur_cost_time=24+intarrive-intstart;
				}
				else if(p->way[way].arrival_time[0] == 't')
				{
					tempp=0;
					for(temp=1;temp<3;temp++)
					{
						arrive_time[tempp]=p->way[way].arrival_time[temp];
						tempp++;
					}
	
					intarrive=atoi(arrive_time); 
					cur_cost_time=48+intarrive-intstart;
				}
			
				if((last_arrive_time < intstart) || (last_arrive_time == intstart))
				{
					cur_cost_time=cur_cost_time+intstart-last_arrive_time;
				}
				else
				{
					cur_cost_time=cur_cost_time+intstart+24-last_arrive_time;
				}
				store_time[way]=cur_cost_time;
				store_arrive[way]=intarrive;
			}
			
			
			if(cur_cost_time < min && cur_cost_time != 0)
				min=cur_cost_time;
		}	
		
		if(min==store_time[0])
		{
			for(j=0;j<5;j++)
				vehicle[j]=store_number[0][j];
			last_time[tocity][vtype]=store_arrive[0];
			passroad=storeroad[0];
		}
		else if(min==store_time[1])
		{
			for(j=0;j<5;j++)
				vehicle[j]=store_number[1][j];
			last_time[tocity][vtype]=store_arrive[1];
			passroad=storeroad[1];
		}
	}

	return min;
}

int find_all_min(ArcNode*p1,ArcNode*p2,ArcNode*p3,int last_city,char vehicle[],int tocity,road&roadtemp)//找到指针指向的那个地点的总的最小时间 
{
	int time[3];
	int arrive_time[3];
	char store_vehicle[3][5]={'\0'};
	char temp_vehicle1[5]={'\0'};
	char temp_vehicle2[5]={'\0'};
	char temp_vehicle0[5]={'\0'};

	int i;//vehicle循环 
	int min=INFINITY;
	road pass_para[3];

	for(int x=0; x<3; x++)
	{
		initroad(pass_para[x]);
	}
	
	time[0]=find_single_min(p1,last_city,temp_vehicle0,0,tocity,pass_para[0]);
	for(i=0; i<5; i++)
	{
		store_vehicle[0][i]=temp_vehicle0[i];
	}
	
	time[1]=find_single_min(p2,last_city,temp_vehicle1,1,tocity,pass_para[1]);
	for(i=0; i<5; i++)
	{
		store_vehicle[1][i]=temp_vehicle1[i];
	}
	
	
	time[2]=find_single_min(p3,last_city,temp_vehicle2,2,tocity,pass_para[2]);
	for(i=0; i<5; i++)
	{
		store_vehicle[2][i]=temp_vehicle2[i];
	}

	for(int i=0;i<3;i++)
	{
		if(time[i] < min)
		{
			min=time[i];
			last_time[tocity][3]=last_time[tocity][i];
			roadtemp=pass_para[i]; 
			for(int j=0;j<5;j++)
				vehicle[j]=store_vehicle[i][j];
		}
	}
	
	return min;
}



void shortest_time(ALGraph *G, int v0, int P[], int D[], char vehicle[][5],int endcity, road roadtime[])
{
	int i, j, w, cur_min_time;
	int cur_path=v0;
	int min_time;
	
	int m,v; 
	bool final[10];
	char temp_vehicle[5]={'\0'};
	int temp;
	int to;
	road roadtemp;
	
	ArcNode *p, *p1, *p2, *b, *b1, *b2,*t, *t1, *t2;
	
	for(i=0;i<10;i++)
	{
		P[i]=v0;
	}
	for(i=0; i<10; i++)
	{
		D[i]=INFINITY;
		final[i]=false;
	}//vehicle初始化 
	
	final[v0]=true;
	D[v0]=INFINITY;
	
	for(to=0; to<10; to++)
	{
		if(to != v0)
		{
			t=G->adjlist[v0].Tfirstarc;		//	t=t->nextarc;
			p=G->adjlist[v0].Pfirstarc;		//	p=p->nextarc;
			b=G->adjlist[v0].Bfirstarc;		//	b=b->nextarc;
			while(t!=NULL && t->adjvex!=to)
			{
				t=t->nextarc;
			}  
			while(p!=NULL && p->adjvex!=to)
			{
				p=p->nextarc;
			}  
			while(b!=NULL && b->adjvex!=to)
			{
				b=b->nextarc;
			}
			for(w=0;w<5;w++)
			{
				temp_vehicle[w]='\0';
			}
			initroad(roadtemp);
			D[to]=find_all_min(p, t, b, v0,temp_vehicle,to,roadtemp);
			roadtime[to]=roadtemp;
			last_time[to][4]=last_time[to][3];
			
			for(temp=0;temp<5;temp++)
			{
				vehicle[to][temp]=temp_vehicle[temp];
			}
			P[to]=v0;
			
		}
		
	}
	for(i=0; i<10; i++)
	{
		min_time=INFINITY;
		for(j=0; j<10; j++)
		{
			if(final[j] == false&&D[j]<min_time  )
			{
				min_time=D[j];
				cur_path=j;
			}
		}
		final[cur_path]=true;
		

		if(cur_path==endcity)
			break;
		for(w=0; w<10; w++) //更新路径 
		{
			if(final[w] == false)
			{		
				p1=G->adjlist[cur_path].Pfirstarc;
				t1=G->adjlist[cur_path].Tfirstarc;
				b1=G->adjlist[cur_path].Bfirstarc;
				while(t1!=NULL && t1->adjvex!=w)
				{
					t1=t1->nextarc;
				}  
				while(p1!=NULL && p1->adjvex!=w)
				{
					p1=p1->nextarc;
				}  
				while(b1!=NULL && b1->adjvex!=w)
				{
					b1=b1->nextarc;
				}

				int tttemp;
				for(tttemp=0; tttemp<5; tttemp++)
				{
					temp_vehicle[tttemp]='\0';
				}
				initroad(roadtemp);
				cur_min_time=find_all_min(p1, t1, b1,cur_path,temp_vehicle,w,roadtemp);//计算时间函数
				
				if(D[w] > (min_time + cur_min_time))
				{
					D[w] = min_time + cur_min_time;
					P[w] = cur_path;
					last_time[w][4]=last_time[w][3];
					for(temp=0;temp<5;temp++)
					{
						vehicle[w][temp]=temp_vehicle[temp];
					}
					roadtime[w]=roadtemp;
				} 		
			}	
		}
	}
	 
}

void strategy_time(passenger_plan plan,ALGraph *g, road roadtime[], road finalroad[], int&real)
{
	int P[10];//FATHER
	int D[10];//VALUE
	int city1,city2,i,j,m,k;
	int passing_city[10];
	char vehicle[10][5]={'\0'};
	int fromcity[10];
	int tocity[10];
	
	city1=LocateVex(plan.departure_station,g);
	city2=LocateVex(plan.destination_station,g);
	shortest_time(g, city1, P, D, vehicle,city2, roadtime );

    cout<<"所乘坐车次为:"<<endl;
    k=city2;
    passing_city[0]=city2;
    int count_city=1;
	while(k != city1)
	{
		k=P[k];
		passing_city[count_city]=k;
		count_city++;
	} 
	int tempp;
	int thiscount=0;
    for(k=count_city-2;k>=0;k--)//-2 
    {
    	tempp=passing_city[k];
    	cout<<vehicle[tempp]<<endl;
    	finalroad[real]=roadtime[tempp];
    	real++;
    	thiscount++;
    }
	cout<<"所花时间为:"<<endl;
	cout<<D[city2]<<endl; 
	cout<<"________"<<endl; 
	for(k=count_city-2;k>=0;k--)//-2 
    {
    	tempp=passing_city[k];
		cout<<"from "<<roadtime[tempp].from<<" to "<<roadtime[tempp].to<<endl;
		cout<<"vehicle number "<<roadtime[tempp].number<<endl;
		cout<<"start time "<<roadtime[tempp].start_time<<endl;
    	cout<<"arrive time "<<roadtime[tempp].arrive_time<<endl;
		cout<<"expense "<<roadtime[tempp].expense<<endl;;	
		cout<<endl;	
    }


}

void egg_strategy_time(passenger_plan plan,ALGraph *g, road roadtime[], road finalroad[], int&real,int &lasty)
{

	int P[10];//FATHER
	int D[10];//VALUE
	int city1,city2,i,j,m,k;
	int passing_city[10];
	char vehicle[10][5]={'\0'};
	int fromcity[10];
	int tocity[10];
	char chartime[5]; 
	char charexpense[5];
	int storefrom,storeto;
	int x1,x2,y1,y2;
	
	city1=LocateVex(plan.departure_station,g);
	city2=LocateVex(plan.destination_station,g);
	shortest_time(g, city1, P, D, vehicle,city2, roadtime );
	MovePen(600,lasty);
    k=city2;
    passing_city[0]=city2;
    int count_city=1;
	while(k != city1)
	{
		k=P[k];
		passing_city[count_city]=k;
		count_city++;
	} 
	int tempp;
	int citychange=1;
    for(k=count_city-2;k>=0;k--)//-2 
    {
    	tempp=passing_city[k];
		DrawString(vehicle[tempp]);
		DrawString("   ");
    	finalroad[real]=roadtime[tempp];
    	real++;
    }
    

	DrawString("所花总时间为：");
	itoa(D[city2],chartime,10);
	DrawString(chartime);
	DrawString("   ");
	int storeY;
	storeY=GetPenYPos();
	MovePen(600,storeY-20);
   	DrawString("车次   出发站   到达站   费用   出发时间   到达时间");
   	int z=0;
   	storeY=GetPenYPos();
	for(k=count_city-2;k>=0;k--)//-2 
    {	
    	tempp=passing_city[k];
		MovePen(600,storeY-20);
   		DrawString(roadtime[tempp].number);
   		DrawString("   ");
   		storefrom=roadtime[tempp].from;
   		DrawString((char*)(g->adjlist[storefrom].city_name).data());
   		citypenxy(storefrom, x1, y1);
   		DrawString("->");
   		storeto=roadtime[tempp].to;
  		DrawString((char*)(g->adjlist[storeto].city_name).data());
  		citypenxy(storeto, x2, y2);
   		DrawString("     ");
		itoa(roadtime[tempp].expense,charexpense,10);
		DrawString(charexpense);
   		DrawString("     ");
   		DrawString(roadtime[tempp].start_time);
   		DrawString("     ");
   		DrawString(roadtime[tempp].arrive_time);
   		DrawString("     ");
   		MovePen(x1,y1);
        DrawLine(x2-x1,y2-y1);
        storeY=storeY-20;
    }
    lasty=storeY-20;


}

void Least_Time_Plan( ALGraph* g, road roadtime[], road finalroad[], int&real)
{
	passenger_plan plan;
	int plan_start_time;
	int city1;
	int i=0,j;
	string city[10];
	input_time=system_time;
	int st=0,en=0;
	char mind; 
	 
	cout<<"是否要经过某些城市(否选择0，是选择1):"<<endl; 
	cin>>mind;
	while(mind != '0' && mind != '1')
	{
		fflush(stdin);
		cout<<"──────────────────────────────────"<<endl;
		cout<<"请按照提示重新输入！< 0-不途经城市；1-途经城市) >"<<endl;
		cin>>mind;
	} 
	if(mind=='0')
	{
		cout<<"请输入旅客的计划:"<<endl;
		cin>>plan.departure_station>>plan.destination_station; 
		
		st=LocateVex(plan.departure_station, g);
		en=LocateVex(plan.destination_station, g);
		while( st==-1 || en==-1 ){
			cout<<"无效的站点输入, 请重新输入\n" ; 
			cin>>plan.departure_station;
			cin>>plan.destination_station;
			st=LocateVex(plan.departure_station, g);
			en=LocateVex(plan.destination_station, g);
		}

		city1=LocateVex(plan.departure_station,g);
		last_time[city1][4]=input_time;
		for(int in=0;in<10;in++)
		{
			initroad(roadtime[in]);
		}
		strategy_time(plan,g, roadtime, finalroad, real);
	} 
	else if(mind == '1')
	{
		int flag=0;
		cout<<"请输入您想经过的城市:"<<endl;
        while(cin>>city[i])
		{
			st=LocateVex(city[i], g);
			while( st==-1){
				cout<<"无效的站点输入, 请重新输入\n" ; 
				fflush(stdin);
				cin>>city[i];
				st=LocateVex(city[i], g);
			}
			if(st != -1)
			{
				i++;
			} 
        }
            
		cout<<"最少时间策略："<<endl;
		for(j=0;j<i-1;j++)
		{
			for(int in=0;in<10;in++)
			{
				initroad(roadtime[in]);
			}
			
			plan.departure_station=city[j];
		    plan.destination_station=city[j+1];
		    if(flag==0)
			{
        		city1=LocateVex(plan.departure_station,g);
				last_time[city1][4]=input_time;
				flag=1;
        	}
        	else
        	{
        		city1=LocateVex(plan.departure_station,g);
        		for(int w=0;w<10;w++){
        			for(int k=0;k<5;k++)
        			{
        				if(w!=city1)
        				last_time[w][k]=0;
        			}
        		}
        	}
		    strategy_time(plan,g, roadtime, finalroad, real);
		}
		
	}		
}

void egg_Least_Time_Plan( ALGraph* g, road roadtime[], road finalroad[], int&real,int mind,string city[],int n)
{
	passenger_plan plan;
	int plan_start_time;
	int city1;
	int i=0,j;
	input_time=system_time;
	double X;
	double Y;
	char char_day[5];
	char char_hour[5];
	int lasty=620;


			if(mind==0)
			{
			    plan.departure_station=city[0];
			    plan.destination_station=city[1]; 
				city1=LocateVex(plan.departure_station,g);
				last_time[city1][4]=input_time;
				for(int in=0;in<10;in++)
				{
					initroad(roadtime[in]);
				}
				egg_strategy_time(plan,g, roadtime, finalroad, real,lasty);
			} 
			else
			{
				int citynum=0;
				int flag=0;
				MovePen(600,620);

				for(j=0;j<=n-1;j++)
				{
					for(int in=0;in<10;in++)
					{
						initroad(roadtime[in]);
					}
					
					plan.departure_station=city[j];
				    plan.destination_station=city[j+1];
				    if(flag==0)
					{
		        		city1=LocateVex(plan.departure_station,g);
						last_time[city1][4]=input_time;
						flag=1;
		        	}
		        	else
		        	{
		        		city1=LocateVex(plan.departure_station,g);
		        		for(int w=0;w<10;w++){
		        			for(int k=0;k<5;k++)
		        			{
		        				if(w!=city1)
		        				last_time[w][k]=0;
		        			}
		        		}
		        	}
				    egg_strategy_time(plan,g, roadtime, finalroad, real,lasty);
				    
				    
				}
			}
}

