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
typedef struct BNode{//ÿ�ֳ��ε���Ϣ���������� 
	char number[SIZE];//����/�ɻ�/�𳵳��� ............
	char start_time[SIZE];//ʼ��ʱ��......... 
	int tag;//��־λ��0�����յ��1������յ�� 
	char arrival_time[SIZE];//����ʱ�� ..........
	char expense[SIZE];//���� ..........
	//struct BNode* nextnode;
}BNode;

typedef BNode Way[CHANCE];

typedef struct ANode{
	int adjvex;//........
	Way way;//�������ࡣ��������������
	int mark[CHANCE]; 
	struct ANode* nextarc;
}ArcNode; 

typedef struct Vnode{
	string city_name;//�������� 
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
	//int plan_start_time;//����һ��Ԥ�Ƴ���ʱ�䡣���������������������� 
	string departure_station;
	string destination_station;
	passing passing_city; 
	char strategy;
}passenger_plan;

typedef struct passing1{
	int adjvex;
}passing1;



