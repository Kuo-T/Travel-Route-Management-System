#include"graph.h" 
using namespace std;
extern ALGraph travel;
int LocateVex(string city,ALGraph *g)
{
	int i;
	for(i=0;i<10;i++)
	{
		if(city==g->adjlist[i].city_name)
		   return i;
	}
	return -1;
}
void evalution(char m[],string n)
{
	int i,j;
	//i=n.length();
	for(j=0;j<5;j++)
	{
		m[j]=n[j];
	}
}

void CreateGraph(ALGraph *g)
{
	ArcNode *hu;
	BNode *ways;
	int i=0,j=0,m,n,a,b,a1,b1=255;
	string cityname[10];
	string cityA,cityB,pnumber,pstart,parrive,pexpense;
    int flag=0;
    ifstream city("city.txt");
	if(city)
	{
		cout<<"城市文件打开成功"<<endl; 
		while(!city.eof())//创建图的头结点 
		{
			city>>cityname[i];
			g->adjlist[i].city_name=cityname[i];
			g->adjlist[i].Tfirstarc=NULL;
			g->adjlist[i].Pfirstarc=NULL;
			g->adjlist[i].Bfirstarc=NULL;
			i++;
		}
	}
	else
	{
		cout<<"城市文件无法打开"<<endl; 
	}
	city.close();
	ifstream plane("plane1.csv");
	int w=0;
	if(plane)
	{
		cout<<"飞机时刻表打开成功"<<endl;
		while(!plane.eof())
		{
			getline(plane,cityA,',');
			getline(plane,cityB,',');
			getline(plane,pnumber,',');
			getline(plane,pstart,',');
			getline(plane,parrive,',');
			getline(plane,pexpense);
			a=LocateVex(cityA,g);
			b=LocateVex(cityB,g);
			
			if(a==a1&&b==b1)
			{
				if(flag==1)//在第一条沪上
				{
					w++;
					evalution(g->adjlist[a].Pfirstarc->way[w].number,pnumber);
				    evalution(g->adjlist[a].Pfirstarc->way[w].start_time,pstart);
				    evalution(g->adjlist[a].Pfirstarc->way[w].arrival_time,parrive);
				    if(g->adjlist[a].Pfirstarc->way[w].arrival_time[0]=='s')
				    	g->adjlist[a].Pfirstarc->way[w].tag=1;
				    else if(g->adjlist[a].Pfirstarc->way[w].arrival_time[0]=='t')
				        g->adjlist[a].Pfirstarc->way[w].tag=2;
				    else
				        g->adjlist[a].Pfirstarc->way[w].tag=0;
				    evalution(g->adjlist[a].Pfirstarc->way[w].expense,pexpense);
				} 
				else
				{
					w++;
					evalution(hu->way[w].number,pnumber);
				    evalution(hu->way[w].start_time,pstart);
				    evalution(hu->way[w].arrival_time,parrive);
				    if(hu->way[w].arrival_time[0]=='s')
				    	hu->way[w].tag=1;
				    else if(hu->way[w].arrival_time[0]=='t')
				        hu->way[w].tag=2;
				    else
				        hu->way[w].tag=0;
				    evalution(hu->way[w].expense,pexpense);
				}
			}
			else
			{
				if(g->adjlist[a].Pfirstarc==NULL)
				{
					g->adjlist[a].Pfirstarc=(ArcNode*)malloc(sizeof(ArcNode));
					g->adjlist[a].Pfirstarc->nextarc=NULL;
					flag=1;
					w=0;
					g->adjlist[a].Pfirstarc->adjvex=b;
					evalution(g->adjlist[a].Pfirstarc->way[w].number,pnumber);
				    evalution(g->adjlist[a].Pfirstarc->way[w].start_time,pstart);
				    evalution(g->adjlist[a].Pfirstarc->way[w].arrival_time,parrive);
				    if(g->adjlist[a].Pfirstarc->way[w].arrival_time[0]=='s')
				    	g->adjlist[a].Pfirstarc->way[w].tag=1;
				    else if(g->adjlist[a].Pfirstarc->way[w].arrival_time[0]=='t')
				        g->adjlist[a].Pfirstarc->way[w].tag=2;
				    else
				        g->adjlist[a].Pfirstarc->way[w].tag=0;
				    evalution(g->adjlist[a].Pfirstarc->way[w].expense,pexpense);
				}
				else
				{
					hu=(ArcNode*)malloc(sizeof(ArcNode));
					hu->adjvex=b;
					w=0;
					for(m=0;m<2;m++) 
					{
						for(n=0;n<5;n++)
						{
							hu->way[m].number[n]={};
							hu->way[m].start_time[n]={};
							hu->way[m].arrival_time[n]={};
						    hu->way[m].expense[n]={};
						}
						
					}			
					evalution(hu->way[w].number,pnumber);
				    evalution(hu->way[w].start_time,pstart);
				    evalution(hu->way[w].arrival_time,parrive);
				    if(hu->way[w].arrival_time[0]=='s')
				    	hu->way[w].tag=1;
				    else if(hu->way[w].arrival_time[0]=='t')
				        hu->way[w].tag=2;
				    else
				        hu->way[w].tag=0;
				    evalution(hu->way[w].expense,pexpense);
			
				    hu->nextarc=g->adjlist[a].Pfirstarc;
				    g->adjlist[a].Pfirstarc=hu;
				    flag=0;
				}
			}
		    a1=a;
		    b1=b;
	    }
	}
	else
	{
		cout<<"飞机时刻表打开失败"<<endl; 
	} 
	plane.close(); 
	
	ifstream train("train1.csv");
	w=0;
	flag=0;
	if(train)
	{
		cout<<"火车时刻表打开成功"<<endl;
		while(!train.eof())
		{
			getline(train,cityA,',');
			getline(train,cityB,',');
			getline(train,pnumber,',');
			getline(train,pstart,',');
			getline(train,parrive,',');
			getline(train,pexpense);
			a=LocateVex(cityA,g);
			b=LocateVex(cityB,g);
			
			if(a==a1&&b==b1)
			{
				if(flag==1)//在第一条沪上
				{
					w++;
					evalution(g->adjlist[a].Tfirstarc->way[w].number,pnumber);
				    evalution(g->adjlist[a].Tfirstarc->way[w].start_time,pstart);
				    evalution(g->adjlist[a].Tfirstarc->way[w].arrival_time,parrive);
				    if(g->adjlist[a].Tfirstarc->way[w].arrival_time[0]=='s')
				    	g->adjlist[a].Tfirstarc->way[w].tag=1;
				    else if(g->adjlist[a].Tfirstarc->way[w].arrival_time[0]=='t')
				        g->adjlist[a].Tfirstarc->way[w].tag=2;
				    else
				        g->adjlist[a].Tfirstarc->way[w].tag=0;
				    evalution(g->adjlist[a].Tfirstarc->way[w].expense,pexpense);
	
				} 
				else
				{
					w++;
					evalution(hu->way[w].number,pnumber);
				    evalution(hu->way[w].start_time,pstart);
				    evalution(hu->way[w].arrival_time,parrive);
				    if(hu->way[w].arrival_time[0]=='s')
				    	hu->way[w].tag=1;
				    else if(hu->way[w].arrival_time[0]=='t')
				        hu->way[w].tag=2;
				    else
				        hu->way[w].tag=0;
				    evalution(hu->way[w].expense,pexpense);
		
				}
			}
			else
			{
				if(g->adjlist[a].Tfirstarc==NULL)
				{
					g->adjlist[a].Tfirstarc=(ArcNode*)malloc(sizeof(ArcNode));
					g->adjlist[a].Tfirstarc->nextarc=NULL;
					flag=1;
					w=0;
					g->adjlist[a].Tfirstarc->adjvex=b;
					evalution(g->adjlist[a].Tfirstarc->way[w].number,pnumber);
				    evalution(g->adjlist[a].Tfirstarc->way[w].start_time,pstart);
				    evalution(g->adjlist[a].Tfirstarc->way[w].arrival_time,parrive);
				    if(g->adjlist[a].Tfirstarc->way[w].arrival_time[0]=='s')
				    	g->adjlist[a].Tfirstarc->way[w].tag=1;
				    else if(g->adjlist[a].Tfirstarc->way[w].arrival_time[0]=='t')
				        g->adjlist[a].Tfirstarc->way[w].tag=2;
				    else
				        g->adjlist[a].Tfirstarc->way[w].tag=0;
				    evalution(g->adjlist[a].Tfirstarc->way[w].expense,pexpense);
				
				}
				else
				{
					hu=(ArcNode*)malloc(sizeof(ArcNode));
					hu->adjvex=b;
					w=0;
					for(m=0;m<2;m++) 
					{
						for(n=0;n<5;n++)
						{
							hu->way[m].number[n]={};
							hu->way[m].start_time[n]={};
							hu->way[m].arrival_time[n]={};
						    hu->way[m].expense[n]={};
						}
						
					}				
					evalution(hu->way[w].number,pnumber);
				    evalution(hu->way[w].start_time,pstart);
				    evalution(hu->way[w].arrival_time,parrive);
				    if(hu->way[w].arrival_time[0]=='s')
				    	hu->way[w].tag=1;
				    else if(hu->way[w].arrival_time[0]=='t')
				        hu->way[w].tag=2;
				    else
				        hu->way[w].tag=0;
				    evalution(hu->way[w].expense,pexpense);
				    
				    hu->nextarc=g->adjlist[a].Tfirstarc;
				    g->adjlist[a].Tfirstarc=hu;
				    flag=0;
				}
			}
		    a1=a;
		    b1=b;
	    }
	}
	else
	{
		cout<<"火车时刻表打开失败"<<endl; 
	} 
	train.close(); 
	
	ifstream bus("bus1.csv");
	w=0;
	flag=0;
	if(bus)
	{
		cout<<"汽车时刻表打开成功"<<endl;
		while(!bus.eof())
		{
			getline(bus,cityA,',');
			getline(bus,cityB,',');
			getline(bus,pnumber,',');
			getline(bus,pstart,',');
			getline(bus,parrive,',');
			getline(bus,pexpense);
			a=LocateVex(cityA,g);
			b=LocateVex(cityB,g);
			
			if(a==a1&&b==b1)
			{
				if(flag==1)//在第一条沪上
				{
					w++;
					evalution(g->adjlist[a].Bfirstarc->way[w].number,pnumber);
				    evalution(g->adjlist[a].Bfirstarc->way[w].start_time,pstart);
				    evalution(g->adjlist[a].Bfirstarc->way[w].arrival_time,parrive);
				    if(g->adjlist[a].Bfirstarc->way[w].arrival_time[0]=='s')
				    	g->adjlist[a].Bfirstarc->way[w].tag=1;
				    else if(g->adjlist[a].Bfirstarc->way[w].arrival_time[0]=='t')
				        g->adjlist[a].Bfirstarc->way[w].tag=2;
				    else
				        g->adjlist[a].Bfirstarc->way[w].tag=0;
				    evalution(g->adjlist[a].Bfirstarc->way[w].expense,pexpense);
				    
				} 
				else
				{
					w++;
					evalution(hu->way[w].number,pnumber);
				    evalution(hu->way[w].start_time,pstart);
				    evalution(hu->way[w].arrival_time,parrive);
				    if(hu->way[w].arrival_time[0]=='s')
				    	hu->way[w].tag=1;
				    else if(hu->way[w].arrival_time[0]=='t')
				        hu->way[w].tag=2;
				    else
				        hu->way[w].tag=0;
				    evalution(hu->way[w].expense,pexpense);
				}
			}
			else
			{
				if(g->adjlist[a].Bfirstarc==NULL)
				{
					g->adjlist[a].Bfirstarc=(ArcNode*)malloc(sizeof(ArcNode));
					g->adjlist[a].Bfirstarc->nextarc=NULL;
					flag=1;
					w=0;
					g->adjlist[a].Bfirstarc->adjvex=b;
					evalution(g->adjlist[a].Bfirstarc->way[w].number,pnumber);
				    evalution(g->adjlist[a].Bfirstarc->way[w].start_time,pstart);
				    evalution(g->adjlist[a].Bfirstarc->way[w].arrival_time,parrive);
				    if(g->adjlist[a].Bfirstarc->way[w].arrival_time[0]=='s')
				    	g->adjlist[a].Bfirstarc->way[w].tag=1;
				    else if(g->adjlist[a].Bfirstarc->way[w].arrival_time[0]=='t')
				        g->adjlist[a].Bfirstarc->way[w].tag=2;
				    else
				        g->adjlist[a].Bfirstarc->way[w].tag=0;
				    evalution(g->adjlist[a].Bfirstarc->way[w].expense,pexpense);
				    
				}
				else
				{
					hu=(ArcNode*)malloc(sizeof(ArcNode));
					hu->adjvex=b;
					w=0;
					for(m=0;m<2;m++) 
					{
						for(n=0;n<5;n++)
						{
							hu->way[m].number[n]={};
							hu->way[m].start_time[n]={};
							hu->way[m].arrival_time[n]={};
						    hu->way[m].expense[n]={};
						}
						
					}		
					evalution(hu->way[w].number,pnumber);
				    evalution(hu->way[w].start_time,pstart);
				    evalution(hu->way[w].arrival_time,parrive);
				    if(hu->way[w].arrival_time[0]=='s')
				    	hu->way[w].tag=1;
				    else if(hu->way[w].arrival_time[0]=='t')
				        hu->way[w].tag=2;
				    else
				        hu->way[w].tag=0;
				    evalution(hu->way[w].expense,pexpense);
				    
				    hu->nextarc=g->adjlist[a].Bfirstarc;
				    g->adjlist[a].Bfirstarc=hu;
				    flag=0;
				}
			}
		    a1=a;
		    b1=b;
	    }
	}
	else
	{
		cout<<"汽车时刻表打开失败"<<endl; 
	} 
	bus.close(); 
	 
}
