#pragma once
#include<ostream>
#include<vector>
#include <fstream>
#include <iostream>
using namespace std;

extern const char* testFile;

class Point
{
public:
	Point(float a, float b, float c) :x(a), y(b), z(c)
	{};
	void printPoint()
	{
		cout << x << " " << y << " " << z << endl;
	}

	float getX() const { return x; };
	float getY() const { return y; };
	float getZ() const { return z; };
private:
	float x,y,z;
	
};

class contourNode
{
public:

	contourNode()
	{
		pLeft = NULL;//������Ҫnew����Ϊ����Ҫ���ٿռ䣬�����char*��Ҫ���ٿռ䣬��Ϊchar*�Ƕ��������
		pRight = NULL;
		pNext = NULL;
		insideContour = NULL;
		sumFloor = 0;
	};

	~contourNode()
	{
		delete pLeft;
		delete pRight;
	};

	void printContour()
	{
		for (Point tempPoint : contourVec)
		{
			tempPoint.printPoint();
		}
	}

	int sumFloor;

	contourNode* pLeft; //������Ŀǰ�ò���
	contourNode* pRight;

	contourNode* pNext;
	contourNode* insideContour;

	vector<Point> contourVec;
};

bool readGcodefromFile(contourNode& CN, ifstream &myfile);

const contourNode* generateTree(int numFloor);

vector<Point>& visitTreeoutside(const contourNode&node,int numfloor);

vector<Point>& visitTreeinside(const contourNode& node, int numfloor);

bool judgeClose(vector<Point>&T);

void test();
