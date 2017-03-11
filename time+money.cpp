#include"time+money.h"
using namespace std;
int matrix[10][10];
int visited[11];
int count[11];

extern int system_time;
extern int LocateVex(string city,ALGraph *g);
extern void citypenxy(int cityname, int &x, int &y);
void transfer( ALGraph *g )
{
	int i, k;
	ANode* t;
	for( k=0; k<MAXSIZE; k++){
		t=g->adjlist[k].Tfirstarc;
		while(t){
			i=t->adjvex;
			matrix[k][i]=1;
			t=t->nextarc;
		}
		t=g->adjlist[k].Pfirstarc;
		while(t){
			i=t->adjvex;
			matrix[k][i]=1;
			t=t->nextarc;
		}
		t=g->adjlist[k].Bfirstarc;
		while(t){
			i=t->adjvex;
			matrix[k][i]=1;
			t=t->nextarc;
		}
	}
}
void init( int a[], int n )
{
	for( int i=0; i<n; i++ ){
		a[i]=0;
	}
}

void initm( ALGraph *g )
{
	ANode* w;
	for( int i=0; i<10; i++ ){
		if( g->adjlist[i].Tfirstarc ){
			w=g->adjlist[i].Tfirstarc;
			while( w ){
				for( int x=0; x<CHANCE; x++ )
					w->mark[x]=0;
				w=w->nextarc;
			}
		}
		if( g->adjlist[i].Pfirstarc ){
			w=g->adjlist[i].Pfirstarc;
			while( w ){
				for( int x=0; x<CHANCE; x++ )
					w->mark[x]=0;
				w=w->nextarc;
			}
		}
		if( g->adjlist[i].Bfirstarc ){
			w=g->adjlist[i].Bfirstarc;
			while( w ){
				for( int x=0; x<CHANCE; x++ )
					w->mark[x]=0;
				w=w->nextarc;
			}
		}
	}
}
int first( int v )
{
	for( int i=0; i<=9; i++ ){
		if( matrix[v][i]==1 )  return i;
	}
	return -1;
}

int next( int v, int w )
{
	if( first(v)==-1)  return -1;
	for( int i=w+1; i<=9; i++ ){
		if( matrix[v][i]==1 ){
			return i;
		}
	}
	return -1;
}

void printpath( vector<vector<int> >& path )
{
	for( int i=0; i<path.size(); i++ ){
		for( int j=0; j<path[i].size(); j++ ){
			cout<< path[i][j];
			cout<<"->";
		}
		cout<<endl;
	}
	
}


int check( vector<int> temp, vector<passing1> array )
{
	int count=0;
	for( int i=0; i<temp.size(); i++ ){
		if( temp[i]==array[count].adjvex ) count++;
	}
	if( count==array.size() )  return 1;
	else return 0;
}

ANode* GetEdge( ALGraph*g, int a, int b, int &i, int &flag, vector<int> temp)
{
	ANode* x;
	if( g->adjlist[temp[a-1]].Tfirstarc ){
		x=g->adjlist[temp[a-1]].Tfirstarc;
		while( x!=NULL ){
			if( x->adjvex == temp[b-1] ){
				for( i=0; i<CHANCE; i++){
					if( x->mark[i]!=1 && x->way[i].number!="" ){
						flag=1;
						x->mark[i]=1;
						return x;
					}
				}
			}
			x=x->nextarc;
		}
	}
	if( g->adjlist[temp[a-1]].Pfirstarc ){
		x=g->adjlist[temp[a-1]].Pfirstarc;
		while( x!=NULL ){
			if( x->adjvex == temp[b-1] ){
				for( i=0; i<CHANCE; i++){
					if( x->mark[i]!=1 && x->way[i].number!="" ){
						flag=2;
						x->mark[i]=1;
						return x;
					}
				}
			}
			x=x->nextarc;
		}
	}
	if( g->adjlist[temp[a-1]].Bfirstarc ){
		x=g->adjlist[temp[a-1]].Bfirstarc;
		while( x!=NULL ){
			if( x->adjvex == temp[b-1] ){
				for( i=0; i<CHANCE; i++){
					if( x->mark[i]!=1 && x->way[i].number!="" ){
						flag=3;
						x->mark[i]=1;
						return x;
					}
				}
			}
			x=x->nextarc;
		}
	}
	return NULL;	
}

void refresh( ALGraph*g, int a, int b, int &i, int &flag, vector<int> temp )
{
	ANode* x;
	if( g->adjlist[temp[a-1]].Tfirstarc ){
		x=g->adjlist[temp[a-1]].Tfirstarc;
		while( x!=NULL ){
			if( x->adjvex == temp[b-1] ){
				for( i=0; i<CHANCE; i++){
					x->mark[i]=0;
				}
			}
			x=x->nextarc;
		}
	}
	if( g->adjlist[temp[a-1]].Pfirstarc ){
		x=g->adjlist[temp[a-1]].Pfirstarc;
		while( x!=NULL ){
			if( x->adjvex == temp[b-1] ){
				for( i=0; i<CHANCE; i++){
					x->mark[i]=0;
				}
			}
			x=x->nextarc;
		}
		
	}
	if( g->adjlist[temp[a-1]].Bfirstarc ){
		x=g->adjlist[temp[a-1]].Bfirstarc;
		while( x!=NULL ){
			if( x->adjvex == temp[b-1] ){
				for( i=0; i<CHANCE; i++){
					x->mark[i]=0;
				}
			}
			x=x->nextarc;
		}
	}	
}
vector< road > result( ALGraph* g, vector<int> temp, int a, int b, int MAX)
{
	int t, j, k, d, i=0, flag=0;
	ANode* x;
	char m[SIZE];
	road thr;
	vector< road > th;
	vector< road > re;
	int min_exp=999999;
	int sum=0;
	int q;
	int count=0;
	
	if( a==1 ){
		d=0;
		t=system_time;
	}
	x=GetEdge(g, a, b, i, flag, temp); 
	while( a>0 ){
		if( x ){
			for( j=0, k=0; j<SIZE && k<SIZE; k++){
				if( x->way[i].arrival_time[k]<='9' && x->way[i].arrival_time[k]>='0'){
					m[j]=x->way[i].arrival_time[k];
					j++;
				}	
			}
			if( b!=temp.size()){
				if( atoi(x->way[i].start_time)-t<0 )	d++;
				if( x->way[i].tag==1 )	d++; 
				else if( x->way[i].tag==2 )  d+=2;
		
				t=atoi(m);
				if( 24*d+t<=MAX ){
					if( flag == 1) thr.type='T';
					else if ( flag==2 ) thr.type='P';
					else thr.type='B';
					strcpy( thr.number, x->way[i].number );
					thr.expense=atoi( x->way[i].expense);
					thr.from=temp[a-1];
					thr.to=temp[b-1];
					strcpy( thr.start_time, x->way[i].start_time );
					strcpy( thr.arrive_time, x->way[i].arrival_time );
					th.push_back(thr);
					a++;
					b++;
					x=GetEdge(g, a, b, i, flag, temp);
				}
				else{

					if( atoi(x->way[i].start_time)-t<0 ) d--; 
					if( x->way[i].tag==1 )	d--; 
					else if( x->way[i].tag==2 )  d-=2;
					x=GetEdge(g, a, b, i, flag, temp);
				} 
			}
			if( b==temp.size()){
				if( atoi(x->way[i].start_time)-t<0 )	d++;
				if( x->way[i].tag==1 )	d++; 
				else if( x->way[i].tag==2 )  d+=2;
		
				t=atoi(m);
				if( 24*d+t<=MAX ) {
					if( flag == 1) thr.type='T';
					else if ( flag==2 ) thr.type='P';
					else thr.type='B';
					strcpy( thr.number, x->way[i].number );
					thr.expense=atoi( x->way[i].expense);
					thr.from=temp[a-1];
					thr.to=temp[b-1];
					strcpy( thr.start_time, x->way[i].start_time );
					strcpy( thr.arrive_time, x->way[i].arrival_time );
					th.push_back(thr);
					 for( q=0; q<th.size(); q++){
					 	sum=sum+th[q].expense;
					 }
					 if(sum < min_exp){
					 	min_exp=sum;
					 	re=th;
					 }
					 sum=0;
				  	 if( atoi(x->way[i].start_time)-t<0 ) d--; 
					 if( x->way[i].tag==1 )	d--; 
					 else if( x->way[i].tag==2 )  d-=2;
					 x=GetEdge(g, a, b, i, flag, temp);
				}
				else{
					if( atoi(x->way[i].start_time)-t<0 ) d--; 
					if( x->way[i].tag==1 )	d--; 
					else if( x->way[i].tag==2 )  d-=2;
					x=GetEdge( g, a, b, i, flag, temp );
				}
			}
		}
		else{	
			refresh(g, a, b, i, flag, temp );
			a=a-1;
			b=b-1;
			if( a<=0 )  break;
			x=GetEdge( g, a, b, i, flag, temp );
		}
	}
	return  re;
} 

void dfs( int v, int end, vector<int> temp, vector<vector<int> >& path, vector< passing1 > array, int pass)
{
	int w;
	visited[v]=1;
	temp.push_back(v);
	if( temp[temp.size()-1]==end && temp.size()>1){
		if( pass==1 ){
			if( check ( temp, array ) )path.push_back(temp);
		}
		else{
			path.push_back(temp);
		}
	}
	else{
		for( w=first(v); w>=0; w=next(v,w)){
			if(!visited[w]){
				dfs(w, end, temp, path, array, pass);
				visited[w]=0;
			}
		}
	}
}

void LTLE( vector< road > &re , ALGraph* travel, int system_time)
{
	vector<int> temp;
	vector< vector<int> > path;
	vector< road > th;
	vector< passing1 > array;
	passing1 n;
	int a, b;
	int sum;
	int u=0;
	int min_exp=9999999;
	int pass;
	int st;
	int en;
	int city_number; 
	int stay_t;
	int MAX_TIME;
	string start;
	string end;
	string interv;
	
	init( visited, 10 );
	for( int y=0; y<11; y++ ){
		count[y]=0;
	}
	for( int i=0; i<MAXSIZE; i++ ){
		for( int j=0; j<MAXSIZE; j++ ){
			matrix[i][j]=0;
		}
	}
	initm( travel );
	transfer( travel );

	cout<<"输入始发站和终点站\n";
	cin>>start;
	cin>>end;
	st=LocateVex(start, travel);
	en=LocateVex(end, travel);
	while( st==-1 || en==-1 ){
		cout<<"无效的站点输入, 请重新输入\n" ; 
		cin>>start;
		cin>>end;
		st=LocateVex(start, travel);
		en=LocateVex(end, travel);
	}
	cout<<"是否需要经过其他站点，0表示不经过，1表示经过\n" ;
	cin>>pass;
	cout<<"请输入最晚时间\n";
	cin>>MAX_TIME; 
	if( pass==1 ){
		cout<<"请先输入经过其他站点的数量，再输入经过序列\n";
		cin>> city_number;
		for( int i=0; i<city_number; i++ ){
			cin>>interv;
			n.adjvex=LocateVex(interv, travel);
			array.push_back(n);
		} 
	}
	dfs(st, en, temp, path, array, pass);

	for( int i=0; i<path.size(); i++ ){
		th = result( travel, path[i], 1, 2, 2000);
		for( int q=0; q<th.size(); q++){
			sum=sum+th[q].expense;
		}
		if( sum < min_exp ){
			min_exp=sum;
			re=th;
			u=i;
		}
		sum=0;
	}
	if( re.size()==0 ){
		cout<<"无符合要求时间的路线\n"; 
	}
	else{
		for( int j=0; j<re.size(); j++ )
		{
			cout<<"type"<<" "<< re[j].type<<endl;
			cout<<"vehicle number"<<" " <<re[j].number<<endl;
			cout<<"expense"<<" " <<re[j].expense<<endl;
			cout<<"from"<<" "<< re[j].from<<" ";
			cout<< "to"<<" "<<re[j].to<<endl;
			cout<<"start time"<<" "<< re[j].start_time<<endl;
			cout<< "arrive time"<<" "<<re[j].arrive_time<<endl;
			cout<< endl;
		}
		for( int i=0; i<path[u].size(); i++ ){
			cout<< path[u][i]<<"->";
		}
	}
}
void egg_LTLE( vector< road >& re , ALGraph* travel, int system_time ,int pass,string city[],int m)
{
	vector<int> temp;
	vector< vector<int> > path;
	vector< road > th;
	vector< passing1 > array;
	passing1 n;
	int a, b;
	int sum;
	int u=0;
	int k=0;
	int min_exp=9999999;
	int st;
	int en;
	int city_number; 
	int stay_t;
	int MAX_TIME;
	string start;
	string end;
	string interv;
	char chexpense[5];
	int x1,x2,y1,y2;
	
	init( visited, 10 );
	for( int y=0; y<11; y++ ){
		count[y]=0;
	}
	for( int i=0; i<MAXSIZE; i++ ){
		for( int j=0; j<MAXSIZE; j++ ){
			matrix[i][j]=0;
		}
	}
	initm( travel );
	transfer( travel );

	start=city[0];
	end=city[m];
	st=LocateVex(start, travel);
	en=LocateVex(end, travel);

	cout<<"请输入最晚时间\n";
	cin>>MAX_TIME; 
	if( pass==1 ){
		for( int i=1; i<=m-1; i++ ){
			n.adjvex=LocateVex(city[i], travel);
			array.push_back(n);
		} 
	}
	dfs(st, en, temp, path, array, pass);

	for( int i=0; i<path.size(); i++ ){
		th = result( travel, path[i], 1, 2, 2000);
		for( int q=0; q<th.size(); q++){
			sum=sum+th[q].expense;
		}
		if( sum < min_exp ){
			min_exp=sum;
			re=th;
			u=i;
		}
		sum=0;
	}
	if( re.size()==0 ){
		cout<<"无符合要求时间的路线\n"; 
	}
	else{
		for( int j=0; j<re.size(); j++ )
		{
			cout<< re[j].type<<" ";
			cout<< re[j].number<<" ";
			cout<< re[j].expense<<" ";
			cout<< re[j].from<<" ";
			cout<< re[j].to<<" ";
			cout<< re[j].start_time<<" ";
			cout<< re[j].arrive_time<<" ";
			cout<< endl;
		}
		for( int i=0; i<path[u].size(); i++ ){
			cout<< path[u][i]<<"->";
		}
	}
	MovePen(620, 620);
	DrawString("所乘坐车次为:"); 
	for(  k=0; k<re.size(); k++ ){
		DrawString(re[k].number);
		DrawString(" "); 
	}
	MovePen(600, 600);
	DrawString("始发站   到达站   车次   开始时间   到达时间   费用");
	for(  k=0; k<re.size(); k++ ){
		MovePen(600,600-(k+1)*20);
		DrawString((char*)(travel->adjlist[re[k].from].city_name).data());
		citypenxy(re[k].from, x1, y1);
    	DrawString(" ");
 		DrawString((char*)(travel->adjlist[re[k].to].city_name).data());
 		citypenxy(re[k].to, x2, y2);
        DrawString("    ");
    	DrawString(re[k].number);
    	DrawString("     ");
    	DrawString(re[k].start_time);
        DrawString("      ");
        DrawString(re[k].arrive_time);
        DrawString("      ");
        itoa(re[k].expense,chexpense,10);
        DrawString(chexpense);
        MovePen(x1,y1);
        DrawLine(x2-x1,y2-y1);
        MovePen(600,600-(k+1)*20);
	}
	MovePen(600,600-(k+1)*20);
}


