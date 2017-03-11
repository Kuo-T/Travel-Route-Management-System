#include"money.h"
using namespace std;
int FEE=0;
extern int LocateVex(string city,ALGraph *g);
void citypenxy(int cityname, int &x, int &y)
{
	if(cityname==0)
	{
		x=302;y=608;
	}
	if(cityname==1)
	{
		x=418;y=696;
	}
	if(cityname==2)
	{
		x=264;y=564;
	}
	if(cityname==3)
	{
		x=142;y=520;
	}
	if(cityname==4)
	{
		x=365;y=504;
	}
	if(cityname==5)
	{
		x=432;y=488;
	}
	if(cityname==6)
	{
		x=312;y=334;
	}
	if(cityname==7)
	{
		x=308;y=444;
	}
	if(cityname==8)
	{
		x=145;y=440;
	}
	if(cityname==9)
	{
		x=232;y=404;
	}
 
}
int convert_char_to_int(char a[SIZE])
{
	int i=0;
	int b=0;
	for(i=0;i<SIZE;i++)
	{
		if(a[i]>='0'&&a[i]<='9')
			b=(a[i]-'0')+10*b;
	}
	return b;
}
int findMin(ArcNode*p1,ArcNode*p2,ArcNode*p3)
{
	int min=INFINITY;
	int i;
	int exp;
	if(p1!=NULL) 
	{
		for(i=0;i<2;i++)
		{
			exp=convert_char_to_int(p1->way[i].expense);
			if(exp<min&&exp!=0)
			   min=exp;
		}
	}
	if(p2!=NULL)
	{
		for(i=0;i<2;i++)
		{
			exp=convert_char_to_int(p2->way[i].expense);
			if(exp<min&&exp!=0)
			   min=exp;
		}
		
	}
	if(p3!=NULL)
	{
		for(i=0;i<2;i++)
		{
			exp=convert_char_to_int(p3->way[i].expense);
			if(exp<min&&exp!=0)
			   min=exp;
		}
	}
	if(p1==NULL&&p2==NULL&&p3==NULL)
	   min=200000;
	return min;
}
void createVehicle(char vehicle[],char start[],char arrive[],int &Expense,ALGraph *g,int m,int n)
{
	int min=INFINITY;
	int i,j;
	int exp;
	ArcNode *p1,*p2,*p3;
	p1=g->adjlist[m].Pfirstarc;
	p2=g->adjlist[m].Tfirstarc;
	p3=g->adjlist[m].Bfirstarc;
	while(p1!=NULL)
	{
		if(p1->adjvex!=n)
		{
			p1=p1->nextarc;
		}
	    else
	        break;
	}
	
	while(p2!=NULL)
	{
		if(p2->adjvex!=n)
		{
			p2=p2->nextarc;
		}
		else
		    break;
	}
	while(p3!=NULL)
	{
		if(p3->adjvex!=n)
		{
			p3=p3->nextarc;
		}
		else
		    break;
	}
	for(i=0;i<2;i++)
	{
		if(p1!=NULL)
		{
			exp=convert_char_to_int(p1->way[i].expense);
			if(exp<min&&exp!=0)
			{
				min=exp;
				Expense=exp;
				for(j=0;j<SIZE;j++)
				{
					vehicle[j]=p1->way[i].number[j];
					start[j]=p1->way[i].start_time[j];
					arrive[j]=p1->way[i].arrival_time[j];
				}
			}
		} 
	}
	for(i=0;i<2;i++)
	{
		if(p2!=NULL) 
		{
			exp=convert_char_to_int(p2->way[i].expense);
			if(exp<min&&exp!=0)
			{
				min=exp;
				Expense=exp;
				for(j=0;j<SIZE;j++)
				{
					vehicle[j]=p2->way[i].number[j];
					start[j]=p2->way[i].start_time[j];
					arrive[j]=p2->way[i].arrival_time[j];
				}
			}
		}
	}
	for(i=0;i<2;i++)
	{
		if(p3!=NULL)
		{
			exp=convert_char_to_int(p3->way[i].expense);
			if(exp<min&&exp!=0)
			{
				min=exp;
				Expense=exp;
				for(j=0;j<SIZE;j++)
				{
					vehicle[j]=p3->way[i].number[j];
					start[j]=p3->way[i].start_time[j];
					arrive[j]=p3->way[i].arrival_time[j];
				}
			}
		}
	}
	
}
void shortFee(string cityA,ALGraph *g,int P[10],int D[],char V[][10][SIZE]) 
{
	int city1;
	int Expense;
	int Feearray[10][10]={INFINITY};
	int v,w,i,j,min,m=0;
	bool final[10];
	char vehicle[SIZE]={'0'};
	char start[SIZE]={'0'};
	char arrive[SIZE]={'0'};
	ArcNode *p1,*p2,*p3;
	
	city1=LocateVex(cityA,g);
	
	for(m=0;m<10;m++)
	{
		p1=g->adjlist[m].Pfirstarc;
		p2=g->adjlist[m].Tfirstarc;
		p3=g->adjlist[m].Bfirstarc;
		for(v=0;v<10;v++)
		{
			while(p1!=NULL)
			{
				if(p1->adjvex!=v)
				  p1=p1->nextarc;
				else
				  break;
			}  
			while(p2!=NULL)
			{
				if(p2->adjvex!=v)
				  p2=p2->nextarc;
				else
				  break;
			}
			while(p3!=NULL)
			{
				if(p3->adjvex!=v)
				  p3=p3->nextarc;
				else
				  break;
			}
			Feearray[m][v]=findMin(p1,p2,p3);//找到到某个城市6种方式中最小的一个作为这条边的权值,*****不要考虑符合相应的出发时间的最小费用
			createVehicle(vehicle,start,arrive,Expense,g,m,v);
			for(int k=0;k<SIZE;k++)
			    V[m][v][k]=vehicle[k];
			p1=g->adjlist[m].Pfirstarc;
		    p2=g->adjlist[m].Tfirstarc;
		    p3=g->adjlist[m].Bfirstarc;
		}
		
	}
	
    for(v=0;v<10;v++)
    {
        final[v]=FALSE;
        D[v]=Feearray[city1][v];
        P[v]=city1;
 
	}
	D[city1]=200000;
	final[city1]=TRUE;
	for(i=1;i<10;i++)
	{
		min=INFINITY;
		for(w=0;w<10;w++)
		{
			if(!final[w])
			{
				if(D[w]<min)
				{
					v=w; 
					min=D[w];
				} 
			}
		}
		final[v]=TRUE;
		
		for(w=0;w<10;w++)
		{
			if(!final[w]&&(min+Feearray[v][w])<D[w])
			{
				D[w]=min+Feearray[v][w];
				P[w]=v;

			}

		}
	}
}

void strategy_fee(passenger_plan plan,ALGraph *g,road r[],int &N)
{
	int city1,city2,i,j,k,m;
	ArcNode *p1,*p2,*p3;
	int P[10]={0},D[10];
	char V[10][10][SIZE]={0};
	int vc[10],vc1[10];
	char Veh[10][SIZE]={0};
	char vehicle[SIZE]={0};
	char start[SIZE]={0};
	char arrive[SIZE]={0};
	int Expense;
	city1=LocateVex(plan.departure_station,g);
	city2=LocateVex(plan.destination_station,g);
	shortFee(plan.departure_station,g,P,D,V);
	
	for( i=0; i<10; i++ ){
		vc[i]=-1;
		vc1[i]=-1;
	}
    cout<<"所乘坐车次为:"<<endl;
    vc[0]=city2;
    for(i=1;vc[i-1]!=city1;i++)
    {
    	vc[i]=P[vc[i-1]];
    }
    i=i-1;   
    m=i;
    for(j=0;i>=0;j++)
    {
    	vc1[j]=vc[i];
    	i--;
    }
   
    for(i=0;i<m;i++) 
    {
    	
    	cout<<V[vc1[i]][vc1[i+1]];
		cout<<" ";
    	r[N].from=vc1[i];
    	r[N].to=vc1[i+1];
        createVehicle(vehicle,start,arrive,Expense,g,vc1[i],vc1[i+1]);
    	for(k=0;k<SIZE;k++)
    	{
    		r[N].number[k]=V[vc1[i]][vc1[i+1]][k];
    		r[N].start_time[k]=start[k];
    		r[N].arrive_time[k]=arrive[k];
    		
    	}
    	r[N].expense=Expense;
    	N++;
    	
    } 
    cout<<endl;
    for(i=0;i<N;i++)
    { 
    	cout<<"from"<<" "<<r[i].from<<" "<<"to"<<r[i].to<<endl;
    	cout<<"vehile number"<<" "<<r[i].number;
    	cout<<endl;
    	cout<<"start tmie"<<" "<<r[i].start_time;
    	cout<<endl;
    	cout<<"arrive time"<<" "<<r[i].arrive_time;
    	cout<<endl;
    	cout<<"expense"<<" "<<r[i].expense;
	   	cout<<endl;
	   	cout<<endl;
    }
    cout<<endl;
	cout<<"该阶段所花费用为:"<<endl;
	cout<<D[city2]<<endl; 
	cout<<endl;
	FEE=FEE+D[city2];
	
}
void egg_strategy_fee(passenger_plan plan,ALGraph *g,road r[],int &N)
{
	int city1,city2,i,j,k,m;
	ArcNode *p1,*p2,*p3;
	int P[10]={0},D[10];
	char V[10][10][SIZE]={0};
	int vc[10],vc1[10];
	char Veh[10][SIZE]={0};
	char vehicle[SIZE]={0};
	char start[SIZE]={0};
	char arrive[SIZE]={0};
	int Expense;
	int x1,x2,y1,y2;
	char charexpense[5];
	city1=LocateVex(plan.departure_station,g);
	city2=LocateVex(plan.destination_station,g);
	shortFee(plan.departure_station,g,P,D,V);
	
	for( i=0; i<10; i++ ){
		vc[i]=-1;
		vc1[i]=-1;
	}
    vc[0]=city2;
    for(i=1;vc[i-1]!=city1;i++)
    {
    	vc[i]=P[vc[i-1]];
    }
    i=i-1;   
    m=i;
    for(j=0;i>=0;j++)
    {
    	vc1[j]=vc[i];
    	i--;
    }
   
    for(i=0;i<m;i++) 
    {
    	
    	//cout<<V[vc1[i]][vc1[i+1]];
    	r[N].from=vc1[i];
    	r[N].to=vc1[i+1];
        createVehicle(vehicle,start,arrive,Expense,g,vc1[i],vc1[i+1]);
    	for(k=0;k<SIZE;k++)
    	{
    		r[N].number[k]=V[vc1[i]][vc1[i+1]][k];
    		r[N].start_time[k]=start[k];
    		r[N].arrive_time[k]=arrive[k];
    		
    	}
    	r[N].expense=Expense;
    	N++;
    	
    } 
    MovePen(600,620);
    DrawString("所乘坐车次为:");
    for(i=0;i<N;i++)
    {
    	DrawString(r[i].number);
    	DrawString("  ");
    }
    
    MovePen(600,600) ;
    DrawString("始发站   到达站   车次   开始时间   到达时间   费用");
    for(i=0;i<N;i++)
    {
	    MovePen(600,600-(i+1)*20);
    	DrawString((char*)(g->adjlist[r[i].from].city_name).data());
    	citypenxy(r[i].from, x1, y1);
    	DrawString(" ");
        DrawString((char*)(g->adjlist[r[i].to].city_name).data());
        citypenxy(r[i].to, x2, y2);
        DrawString("    ");
    	DrawString(r[i].number);
    	DrawString("     ");
    	DrawString(r[i].start_time);
        DrawString("      ");
        DrawString(r[i].arrive_time);
        DrawString("      ");
        itoa(r[i].expense,charexpense,10);
        DrawString(charexpense);
        MovePen(x1,y1);
        DrawLine(x2-x1,y2-y1);
        MovePen(600,600-(i+1)*20);
    }
    MovePen(600,600-(i+1)*20);
	FEE=FEE+D[city2];
	
}


void Least_Expense_Plan( ALGraph*g, road r[], int &N)
{
	passenger_plan plan;
	int plan_start_time;
	int i,j,n;
	N=0;
	string city[10];
	char mind; 
	int st=0,en=0; 
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
		strategy_fee(plan,g,r,N);
		cout<<"总费用为："<<FEE<<endl;
	} 
	else if(mind == '1')
	{
		cout<<"请输入您要经过的城市数量："<<endl;
		cin>>n; 
		cout<<"请输入您想经过的城市:"<<endl;
		for(i=0;i<n+2;i++)
		{
			cin>>city[i];
			st=LocateVex(city[i], g);
			while( st==-1){
				cout<<"无效的站点输入, 请重新输入\n" ; 
				fflush(stdin);
				cin>>city[i];
				st=LocateVex(city[i], g);
			}
		}

		cout<<"为您安排的最少费用策略如下！"<<endl;
		cout<<"──────────────────────────────────"<<endl;
		for(j=0;j<i-1;j++)
		{
			plan.departure_station=city[j];
		    plan.destination_station=city[j+1];
		    strategy_fee(plan,g,r,N);
		} 
		cout<<"总费用为："<<FEE<<endl; 
	}
	
}

void egg_Least_Expense_Plan( ALGraph*g, road r[], int &N,int mind,string city[],int n)
{
	passenger_plan plan;
	int plan_start_time;
	int i,j;
	N=0;
	char charfee[5];
	if(mind==0)
	{
		plan.departure_station=city[0];
		plan.destination_station=city[1]; 
		egg_strategy_fee(plan,g,r,N);
		DrawString("          ");
	} 
	else
	{
		for(j=0;j<=n-1;j++)
		{
			plan.departure_station=city[j];
		    plan.destination_station=city[j+1];
		    egg_strategy_fee(plan,g,r,N);
		} 
	}
	
}

