#include"treeContour.h"

/*
1.定义内外轮廓数据类型，类似于赫夫曼树
2.从外部文件读取点到树中
3.随机访问任意层的内外轮廓
4.判断轮廓是否闭合
*/

//从gcode文件读取点,新的轮廓以开头是000为flag，先外轮廓，后内轮廓。
bool readGcodefromFile(contourNode& CN, ifstream &myfile)
{
	float x = 0;
	float y = 0;
	float z = 0;
	float flag = 0;
	int i = 0;

	while ((myfile >> flag) && (i < 2))
	{
		
		if (0 == flag)//读flag所在的行，一个轮廓只有一行
		{
			i++;

			if (2 == i)
			{
				myfile.seekg(-3, ios::cur);//文件指针归位，回到行头
				break;
			}

			myfile >> x >> y >> z;
			Point tempPoint(x, y, z);
			(CN.contourVec).push_back(tempPoint);

		}
		else//读非flag的行
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
		//外轮廓
		contourNode* floorTemp = new contourNode;
		if (!floorTemp) { cout << "false generateTree";  exit(1); }
		//内轮廓
		contourNode* insideTemp = new contourNode;
		if (!insideTemp) { cout << "false generateTree";  exit(1); }

		//分别从文件里拿到外轮廓和内轮廓数据
		readGcodefromFile(*floorTemp, myGcodefile);
		readGcodefromFile(*insideTemp, myGcodefile);

		//将内轮廓挂到外轮廓上
		floorTemp->insideContour = insideTemp;

		tail->pNext = floorTemp;

		tail = floorTemp;

	}
	tail->pNext = NULL;

	return floor0;
}

//访问第numfloor层的外轮廓
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

