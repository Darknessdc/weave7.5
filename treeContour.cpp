#include"treeContour.h"

/*
1.�������������������ͣ������ںշ�����
2.���ⲿ�ļ���ȡ�㵽����
3.���������������������
4.�ж������Ƿ�պ�
*/

//��gcode�ļ���ȡ��,�µ������Կ�ͷ��000Ϊflag����������������������
bool readGcodefromFile(contourNode& CN, ifstream &myfile)
{
	float x = 0;
	float y = 0;
	float z = 0;
	float flag = 0;
	int i = 0;

	while ((myfile >> flag) && (i < 2))
	{
		
		if (0 == flag)//��flag���ڵ��У�һ������ֻ��һ��
		{
			i++;

			if (2 == i)
			{
				myfile.seekg(-3, ios::cur);//�ļ�ָ���λ���ص���ͷ
				break;
			}

			myfile >> x >> y >> z;
			Point tempPoint(x, y, z);
			(CN.contourVec).push_back(tempPoint);

		}
		else//����flag����
		{
			myfile >> y >> z;
			Point tempPoint(flag, y, z);
			(CN.contourVec).push_back(tempPoint);
		}

	}

	return true;
}

const contourNode* generateTree(int numFloor)
{

	ifstream myGcodefile(testFile, ios::in);
	if (!myGcodefile) { cout << "fail open file";  exit(1); }

	contourNode* tail;
	contourNode* floor0 = new contourNode;
	tail = floor0;

	floor0->sumFloor = numFloor;

	if (!floor0) { cout << "false generateTree";  exit(1); }
	
	for (int i = 0; i < numFloor; i++)
	{
		//������
		contourNode* floorTemp = new contourNode;
		if (!floorTemp) { cout << "false generateTree";  exit(1); }
		//������
		contourNode* insideTemp = new contourNode;
		if (!insideTemp) { cout << "false generateTree";  exit(1); }

		//�ֱ���ļ����õ�������������������
		readGcodefromFile(*floorTemp, myGcodefile);
		readGcodefromFile(*insideTemp, myGcodefile);

		//���������ҵ���������
		floorTemp->insideContour = insideTemp;

		tail->pNext = floorTemp;

		tail = floorTemp;

	}
	tail->pNext = NULL;

	return floor0;
}

//���ʵ�numfloor���������
vector<Point>& visitTreeoutside(const contourNode& node, int numfloor)
{
	if (0 == ((node.pNext->contourVec).size())) { cout << "false visitTreeoutside"; exit(1); }

	int j = 1;
	contourNode* p;
	p = node.pNext;

	while (p && (j < numfloor))
	{
		p = p->pNext;
		j++;
	}
	if(!p||j> numfloor) { cout << "false visitTreeoutside"; exit(1); }

	return p->contourVec;

}

vector<Point>& visitTreeinside(const contourNode& node, int numfloor)
{
	if (0 == ((node.pNext->contourVec).size())) { cout << "false visitTreeoutside"; exit(1); }

	int j = 1;
	contourNode* p;
	p = node.pNext;

	while (p && (j < numfloor))
	{
		p = p->pNext;
		j++;
	}

	if (!p || j > numfloor) { cout << "false visitTreeoutside"; exit(1); }

	return p->insideContour->contourVec;
}

bool judgeClose(vector<Point>& T)
{
	Point a = T[0];
	Point b = T[T.size() - 1];
	if (a.getX() == b.getX() && a.getY() == b.getY() && a.getZ() == b.getZ())
	{
		return true;
	}
	else return false;
}

void test()
{
	const contourNode *temp= generateTree(12);

	vector<Point> myVec;

	myVec= visitTreeinside(*temp,2);

	if (judgeClose(myVec))
	{
		cout << "close" << endl;
	}
	else 
	{ 
		cout << "open" << endl; 
	}

	for (Point tempPoint : myVec)
	{
		 tempPoint.printPoint();
	}
	cout << ((temp->pNext->pNext->pNext->pNext)->contourVec).size();
}

