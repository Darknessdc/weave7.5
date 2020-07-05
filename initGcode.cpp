#include"initGcode.h"
#include<fstream>

using namespace std;

bool initPrinter()
{
	ofstream myGcodefile(myFile);
	if (!myGcodefile) return false;

	myGcodefile << "G28" << endl;
	myGcodefile << "M104 S195" << endl;
	myGcodefile << "M140 S40" << endl;
	myGcodefile << "M190 S40" << endl;
	myGcodefile << "M109 S195" << endl;

	return true;
}

bool endPrinter()
{
	ofstream myGcodefile(myFile, ios_base::app);
	if (!myGcodefile) return false;

	myGcodefile<<";End GCode" << endl
		<<"M104 S0; extruder heater off" << endl
		<<"M140 S0; heated bed heater off(if you have it)" << endl
		<<"G91; relative positioning" << endl
		<<"G1 E - 1 F300; retract the filament a bit before lifting the nozzle, to release some of the pressure" << endl
		<<"G1 Z + 0.5 E - 5 X - 20 Y - 20 F2700; move Z up a bit and retract filament even more"<< endl
		<<"G28 X0 Y0; move X / Y to min endstops, so the head is out of the way"<< endl
		<<"M84; steppers off" << endl
		<<"G90"<< endl;
}

//A点是左下角 length是长度 N是喷嘴直径一般0.4mm M是数量,真实的小条纹数是M*2 E1挤出机比例系数的微调，可能与Z有关
bool tiaoWen(const double PointA[2],int length,double Z,double N, int M, double E1)
{
	ofstream myGcodefile(myFile,ios_base::app);
	if (!myGcodefile) return false;
	myGcodefile << "G0 F2000 " <<" Z" << Z << endl;

	double tempPoint[2] = { PointA[0],PointA[1] };
	double tempX = tempPoint[0];
	for (int i = 0; i < M; i++)
	{ 
		
		myGcodefile << "G1 X" << tempX << " Y" << tempPoint[1] << endl;
		sumOfE += E1*E*length;
		myGcodefile << "G1 X" << tempX << " Y" << tempPoint[1] + length << " E" << sumOfE << endl;
		tempX += N ;
		myGcodefile << "G1 X" << tempX << " Y" << tempPoint[1] + length << " E" << sumOfE << endl;
		sumOfE += E1*E*length;
		myGcodefile << "G1 X" << tempX << " Y"<< tempPoint[1] << " E" << sumOfE << endl;
		tempX += N ;
		myGcodefile << "G1 X" << tempX << " Y" << tempPoint[1] << " E" << sumOfE << endl;

	}
	//z偏移，防止磕碰
	myGcodefile<< "G1 Z" << Z+ raiseZ << endl;
	return true;
}

bool tiaoWen2(const double PointA[2], int length, double Z, double N, int M, double E1)
{
	ofstream myGcodefile(myFile, ios_base::app);
	if (!myGcodefile) return false;
	myGcodefile << "G0 F2000 " << " Z" << Z << endl;

	double tempPoint[2] = { PointA[0],PointA[1] };
	double tempY = tempPoint[1];
	for (int i = 0; i < M; i++)
	{
		myGcodefile << "G1 X" << tempPoint[0]  << " Y" << tempY << endl;
		sumOfE += E1 * E*length;
		myGcodefile << "G1 X" << tempPoint[0] + length << " Y" << tempY << " E" << sumOfE << endl;
		tempY += N;
		myGcodefile << "G1 X" << tempPoint[0] + length  << " Y" << tempY << " E" << sumOfE << endl;
		sumOfE += E1 * E*length;
		myGcodefile << "G1 X" << tempPoint[0]  << " Y" << tempY << " E" << sumOfE << endl;
		tempY += N;
		myGcodefile << "G1 X" << tempPoint[0] << " Y" << tempY << " E" << sumOfE << endl;
	}
	//z偏移，防止磕碰
	myGcodefile << "G1 Z" << Z + raiseZ << endl;
	return true;
}

bool waves(const double PointA[2], double lengthOflow, double lengthOfhigh, double Z1, double Z2, int numberOfwaves, int M, double N, double E1)
{
	ofstream myGcodefile(myFile, ios_base::app);
	if (!myGcodefile) return false;

	double tempPoint[2] = { PointA[0],PointA[1] };

	for (int j = 0; j < M; j++)
	{
		for (int i = 0; i < numberOfwaves; i++)
		{
			myGcodefile << "G1 X" << tempPoint[0] + N * j  << " Y" << tempPoint[1] + (lengthOflow + lengthOfhigh) * i << " Z" << Z1 << endl;
			sumOfE += E1 * E * lengthOflow * (i + 1);
			myGcodefile << "G1 X" << tempPoint[0] + N * j << " Y" << tempPoint[1] + (lengthOflow + lengthOfhigh) * i + lengthOflow << " E" << sumOfE << endl;

			myGcodefile << "G1 Z" << Z2 << endl;
			sumOfE += E1 * E * lengthOfhigh * (i + 1);
			myGcodefile << "G1 X" << tempPoint[0] + N * j << " Y" << tempPoint[1] + (lengthOflow + lengthOfhigh) * i + lengthOflow + lengthOfhigh << " E" << sumOfE << endl;
			myGcodefile << "G1 Z" << Z1 << endl;
		}
		//z偏移，防止磕碰
		myGcodefile << "G1 Z" << Z1 + raiseZ << endl;
	}
	return true;
}

bool waves2(const double PointA[2], double lengthOflow, double lengthOfhigh, double Z1, double Z2, int numberOfwaves, int M, double N, double E1)
{
	ofstream myGcodefile(myFile, ios_base::app);
	if (!myGcodefile) return false;

	double tempPoint[2] = { PointA[0],PointA[1] };

	for (int j = 0; j < M; j++)
	{
		for (int i = 0; i < numberOfwaves; i++)
		{
			myGcodefile << "G1 X" << tempPoint[0] + (lengthOflow + lengthOfhigh) * i << " Y" << tempPoint[1] + N * j << " Z" << Z1 << endl;
			sumOfE += E1 * E * lengthOflow * (i + 1);
			myGcodefile << "G1 X" << tempPoint[0] + (lengthOflow + lengthOfhigh) * i + lengthOflow << " Y" << tempPoint[1] + N * j << " E" << sumOfE << endl;

			myGcodefile << "G1 Z" << Z2 << endl;
			sumOfE += E1 * E * lengthOfhigh * (i + 1);
			myGcodefile << "G1 X" << tempPoint[0] + (lengthOflow + lengthOfhigh) * i + lengthOflow + lengthOfhigh << " Y" << tempPoint[1] + N * j << " E" << sumOfE << endl;
			myGcodefile << "G1 Z" << Z1 << endl;
		}
		//z偏移，防止磕碰
		myGcodefile << "G1 Z" << Z1 + raiseZ << endl;
	}
	return true;
}
//起点，长宽高abc，M是填充模式决定了tiaowen 和waves的小条纹数量，一个是2*M,另一个是M，喷嘴N
void cube(const double PointA[2], double a, double b, double c,int M, double N)
{
	double tempPoint[2] = { PointA[0],PointA[1] };
	double width = M * N * 2;
	//大竖条纹数量,长的等分
	int numOftiaowen = a / width / 2;
	//打印一次循环上升3H1个高度
	int numOfz = c / (3*H1);

	
	//第一道纹为空，参考论文，这是第二道纹，都是偶数纹,第一层
	printWireframe(tempPoint, a, b, H1);
	for (int i = 0; i < numOftiaowen; i++)
	{
		//最后+N为了让第一道和边框的距离合理
		double startPointx = tempPoint[0] + width * ((i * 2) + 1) + N;
		double startPointy = tempPoint[1];
		double startPoint[2] = { startPointx ,startPointy };

		tiaoWen(startPoint, b, H1, N, M, 1.1);
	}

	for (int ii = 0; ii < numOfz; ii++)
	{
		//第二层
		//大横条纹数量，宽的等分
		int numOftiaowen2 = b / width / 2;
		printWireframe(tempPoint, a, b, 2 * H1 + 3 * H1*ii);

		for (int i = 0; i < numOftiaowen2; i++)
		{
			double startPointx = tempPoint[0];
			double startPointy = tempPoint[1] + width * ((i * 2) + 1) + N;
			double startPoint[2] = { startPointx ,startPointy };
			//+N -N 进行微调
			waves2(startPoint, width + N, width - N, H1+3*H1*ii , 2*H1 + 3 * H1*ii, numOftiaowen, M * 2, N, 1);
		}

		//第三层
		//printWireframe(tempPoint, a, b, tempZ);
		for (int i = 0; i < numOftiaowen; i++)
		{
			double startPointx = tempPoint[0] + width * (i * 2) + N;
			double startPointy = tempPoint[1];
			double startPoint[2] = { startPointx ,startPointy };
			waves(startPoint, width + N, width - N, H1 + 3 * H1*ii, 2 * H1 + 3 * H1*ii, numOftiaowen2, M * 2, N, 1);
		}

		//第四层
		printWireframe(tempPoint, a, b, 3 * H1 + 3 * H1*ii);
		for (int i = 0; i < numOftiaowen2; i++)
		{
			double startPointx = tempPoint[0];
			double startPointy = tempPoint[1] + width * (i * 2) + N;
			double startPoint[2] = { startPointx ,startPointy };
			tiaoWen2(startPoint, a, 3*H1 + 3 * H1*ii, N, M, 1);
		}

		//第五层
		printWireframe(tempPoint, a, b, 4 * H1 + 3 * H1*ii);
		for (int i = 0; i < numOftiaowen; i++)
		{
			double startPointx = tempPoint[0] + width * ((i * 2) + 1) + N;
			double startPointy = tempPoint[1];
			double startPoint[2] = { startPointx ,startPointy };
			waves(startPoint, width, width, 4*H1 + 3 * H1*ii, 3*H1 + 3 * H1*ii, numOftiaowen2, M * 2, N, 1);
		}

		//第六层
		//printWireframe(tempPoint, a, b, tempZ + H1 * 2 + H2 + H1 + H1);
		for (int i = 0; i < numOftiaowen2; i++)
		{
			double startPointx = tempPoint[0];
			double startPointy = tempPoint[1] + width * ((i * 2) + 1) + N;
			double startPoint[2] = { startPointx ,startPointy };
			//+N -N 进行微调
			waves2(startPoint, width + N, width - N, 3 * H1 + 3 * H1*ii, 4 * H1 + 3 * H1*ii, numOftiaowen, M * 2, N, 1);
		}
	}
		
}

bool printWireframe(const double PointA[2], double a, double b, double Z)
{
	ofstream myGcodefile(myFile, ios_base::app);
	if (!myGcodefile) return false;

	double tempPoint[2] = { PointA[0],PointA[1] };
	myGcodefile << "G1 F2000 Z" << Z << endl;

	myGcodefile << "G1 X" << tempPoint[0] << " Y" << tempPoint[1] << endl;
	sumOfE += E * a;
	myGcodefile << "G1 X" << tempPoint[0]+a << " Y" << tempPoint[1] <<" E"<< sumOfE << endl;
	sumOfE += E * b;
	myGcodefile << "G1 X" << tempPoint[0] + a << " Y" << tempPoint[1]+b << " E" << sumOfE << endl;
	sumOfE += E * a;
	myGcodefile << "G1 X" << tempPoint[0] << " Y" << tempPoint[1] + b << " E" << sumOfE << endl;
	sumOfE += E * b;
	myGcodefile << "G1 X" << tempPoint[0] << " Y" << tempPoint[1] << " E" << sumOfE << endl;

	return true;
}