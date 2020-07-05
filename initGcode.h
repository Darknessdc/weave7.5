#pragma once

//�ֱ��� ������ߣ�������
extern double H1;
extern double H2;
extern const double E;
extern  double sumOfE;
extern const char* myFile;
extern double raiseZ;

bool initPrinter();
bool endPrinter();
bool printWireframe(const double PointA[2],double a,double b,double c);

//��ӡ��һ��������Ҫ��ʼ�㣬���ȣ��߶�Z������ֱ��N������M��������E E��������Z�й�
bool tiaoWen(const double PointA[2], int length, double Z, double N, int M, double E1);
//��ӡ��������Ҫ��㣬���ȣ��߶�Z������ֱ��N������M��������E
bool tiaoWen2(const double PointA[2], int length, double Z, double N, int M, double E1);
//��ӡ��������      ���               �͵ĳ���            �ߵĳ���      �͵Ĳ��     �ߵĲ��    ������Ŀ         ��������
bool waves(const double PointA[2], double lengthOflow, double lengthOfhigh, double Z1, double Z2, int numberOfwaves, int M, double N, double E1);
//���˺���
bool waves2(const double PointA[2], double lengthOflow, double lengthOfhigh, double Z1, double Z2, int numberOfwaves, int M, double N, double E1);
//�ñ�֯������ⳤ��ߵ�������
void cube(const double PointA[2], double a,double b, double c, int M, double N);