#pragma once

//分别是 两个层高，挤出机
extern double H1;
extern double H2;
extern const double E;
extern  double sumOfE;
extern const char* myFile;
extern double raiseZ;

bool initPrinter();
bool endPrinter();
bool printWireframe(const double PointA[2],double a,double b,double c);

//打印单一竖条纹需要起始点，长度，高度Z，喷嘴直径N，数量M，挤出机E E还可能与Z有关
bool tiaoWen(const double PointA[2], int length, double Z, double N, int M, double E1);
//打印横条纹需要起点，长度，高度Z，喷嘴直径N，数量M，挤出机E
bool tiaoWen2(const double PointA[2], int length, double Z, double N, int M, double E1);
//打印波浪竖纹      起点               低的长度            高的长度      低的层高     高的层高    波浪数目         几道波浪
bool waves(const double PointA[2], double lengthOflow, double lengthOfhigh, double Z1, double Z2, int numberOfwaves, int M, double N, double E1);
//波浪横纹
bool waves2(const double PointA[2], double lengthOflow, double lengthOfhigh, double Z1, double Z2, int numberOfwaves, int M, double N, double E1);
//用编织填充任意长宽高的立方体
void cube(const double PointA[2], double a,double b, double c, int M, double N);