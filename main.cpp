/*1.条纹的实现N*M				
  2.起点，终点
  3.层高H1，H2，奇偶控制
  4.挤出量控制
  4.遇到孔洞的实现 
  5.生成任意的凹凸形
  6.外壳的打印*/

/*
v1.0固定立方体编织生成
v1.1加入防磕碰
v1.2读外部点以及定义数据结构
*/

/*使用说明：
目前三个文件两个cpp,一个h，直接调试就能生成对应参数的编织立方体，下面的参数可以修改
1.H1为层高，两种层高H1和H2.其中H2=2*H1,该参数可以直接改，每次循环上升3*H1mm
2.temp为编织结构的左下角点，可以直接修改，这样在打印平面的位置就改变了
3.cube第一个参数是temp，接着是立方体的长宽高，接着是条纹的模式，
一般选1，2，3，4，5等，最后一个参数是打印机喷嘴直径，这边是0.4
4.立方体的高不一定刚好是3*H1的倍数，同理，长宽也不一定满足倍数，这边取整数部分，小数忽略
5.防磕碰加在initGcode.cpp中，每次打印一个条纹会拉高z，使用raiseZ参数控制
6.E是挤出机比例系数，层高不一样E也不一样
7.开头的初始化机器代码需要看情况改
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include"initGcode.h"
#include"treeContour.h"

using namespace std;

double sumOfE = 0.0;
double H1 = 0.2;
double H2 = 0.2;//没有实际用处
double raiseZ = 10;
extern const double E = 0.032;// 0.2是0.03256，其他层高得看切片软件
//生成的编织g代码
extern const char* myFile = "gcode/myGocde.gcode";

//读取的轮廓点
extern const char* testFile = "gcode/point.txt";

int main()
{
	initPrinter();

	double temp[2] = {20,20};

	//cube(temp,80,80,2,3,0.4);

	test();

	//最后加上去两句，不然切片软件显示都是黑色的线，软件simplify3d
	ofstream myGcodefile(myFile, ios_base::app);
	myGcodefile << "G0 F1000 X0 Y0 Z10"<<endl<<"G0 F9000 X0 Y0 Z0";

	endPrinter();
	system("pause");

}