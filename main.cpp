/*1.���Ƶ�ʵ��N*M				
  2.��㣬�յ�
  3.���H1��H2����ż����
  4.����������
  4.�����׶���ʵ�� 
  5.��������İ�͹��
  6.��ǵĴ�ӡ*/

/*
v1.0�̶��������֯����
v1.1���������
v1.2���ⲿ���Լ��������ݽṹ
*/

/*ʹ��˵����
Ŀǰ�����ļ�����cpp,һ��h��ֱ�ӵ��Ծ������ɶ�Ӧ�����ı�֯�����壬����Ĳ��������޸�
1.H1Ϊ��ߣ����ֲ��H1��H2.����H2=2*H1,�ò�������ֱ�Ӹģ�ÿ��ѭ������3*H1mm
2.tempΪ��֯�ṹ�����½ǵ㣬����ֱ���޸ģ������ڴ�ӡƽ���λ�þ͸ı���
3.cube��һ��������temp��������������ĳ���ߣ����������Ƶ�ģʽ��
һ��ѡ1��2��3��4��5�ȣ����һ�������Ǵ�ӡ������ֱ���������0.4
4.������ĸ߲�һ���պ���3*H1�ı�����ͬ������Ҳ��һ�����㱶�������ȡ�������֣�С������
5.����������initGcode.cpp�У�ÿ�δ�ӡһ�����ƻ�����z��ʹ��raiseZ��������
6.E�Ǽ���������ϵ������߲�һ��EҲ��һ��
7.��ͷ�ĳ�ʼ������������Ҫ�������
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include"initGcode.h"
#include"treeContour.h"

using namespace std;

double sumOfE = 0.0;
double H1 = 0.2;
double H2 = 0.2;//û��ʵ���ô�
double raiseZ = 10;
extern const double E = 0.032;// 0.2��0.03256��������ߵÿ���Ƭ���
//���ɵı�֯g����
extern const char* myFile = "gcode/myGocde.gcode";

//��ȡ��������
extern const char* testFile = "gcode/point.txt";

int main()
{
	initPrinter();

	double temp[2] = {20,20};

	//cube(temp,80,80,2,3,0.4);

	test();

	//������ȥ���䣬��Ȼ��Ƭ�����ʾ���Ǻ�ɫ���ߣ����simplify3d
	ofstream myGcodefile(myFile, ios_base::app);
	myGcodefile << "G0 F1000 X0 Y0 Z10"<<endl<<"G0 F9000 X0 Y0 Z0";

	endPrinter();
	system("pause");

}