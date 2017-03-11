#include<iostream>
#include<fstream> 
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<iomanip>
#include<vector>
#include<windows.h>
#include<conio.h>
#include"egg.h"

using namespace std;
#define MAXSIZE 10
#define SIZE 5
#define CHANCE 2
#define INFINITY 200000
typedef struct BNode{//每种车次的信息。。。。。 
	char number[SIZE];//汽车/飞机/火车车次 ............
	char start_time[SIZE];//始发时间......... 
	int tag;//标志位，0代表当日到达，1代表次日到达， 
	char arrival_time[SIZE];//到达时间 ..........
	char expense[SIZE];//花费 ..........
	//struct BNode* nextnode;
}BNode;

typedef BNode Way[CHANCE];

typedef struct ANode{
	int adjvex;//........
	Way way;//车次种类。。。。。。。。
	int mark[CHANCE]; 
	struct ANode* nextarc;
}ArcNode; 

typedef struct Vnode{
	string city_name;//城市名称 
	ArcNode* Tfirstarc;//.........
	ArcNode* Pfirstarc;
	ArcNode* Bfirstarc;
}VNode;

typedef VNode AdjList[MAXSIZE];

typedef struct{
	AdjList adjlist;
	int n, e;
}ALGraph;

typedef struct passing_city{
	string city_name;
	struct passing_city* nextcity;
}passing;

typedef struct road{
	char type;
	char number[SIZE];
	int from;
	int to;
	int expense;
	char start_time[SIZE];
	char arrive_time[SIZE];
}road;

typedef struct plan{
	int passenger_name;
	//int plan_start_time;//增加一个预计出发时间。。。。。。。。。。。。 
	string departure_station;
	string destination_station;
	passing passing_city; 
	char strategy;
}passenger_plan;

typedef struct passing1{
	int adjvex;
}passing1;



