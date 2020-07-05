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
		pLeft = NULL;//并不需要new，因为不需要开辟空间，如果是char*就要开辟空间，因为char*是对象的数据
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

	contourNode* pLeft; //这两个目前用不到
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
