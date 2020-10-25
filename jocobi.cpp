//���������ѳ�
//�༶������91
//ѧ�ţ�2194411247
// Jocobi ������
//----------------------------------------������ؿ�---------------------------------- 
#include <iostream>
#include <math.h>
#include <stdio.h>
//----------------------------------------���������ռ�-------------------------------- 
using namespace std;
//----------------------------------------����ȫ�ֱ���-------------------------------- 
const int N = 3;
const double PRECISION = 1e-4;
double A[N][N] = {0};
double b[N] = {0};
double x[N] = {0};
double e[N] = {1,1,1};
int count = 0;
//----------------------------------------���� class---------------------------------- 
class jocobi{
	public:
		void interation();
		void matrixMultiplication();
		void getBjFj();
		bool precision();
		void welcome();
		void print();
}; 
jocobi Jocobi;
jocobi J;
//---------------------------------------���� class �ĳ�Ա����------------------------
// ��ʼ�� 
void jocobi::welcome()
{
	// ������� 
	cout << "�ſɱȵ�����-���ѳ�-����91-2194411217" << endl;
	cout << "----------------------------" << endl;
	cout << "!����׼��!" << endl;
	cout << "������ϵ������ά�� n = ";
	//cin >> n;
	cout << N;
	cout << endl;
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			cout << "������ϵ������AԪ�� a" << "[" << i+1 << "]" << "[" << j+1 << "] = ";
			cin >> A[i][j]; 
		}
	}
	for(int i=0; i<N; i++)
	{
		cout << "������ϵ������bԪ�� b[" << i+1 << "]" << "[1] = ";
		cin >> b[i]; 
	}
	cout << "!��������������ſɱȵ��������!" << endl;
}
// ��ӡ������ 
void jocobi::print()
{
	cout << "�������Է�����Ϊ" << endl;
	for(int i=0; i<N; i++)
	{
		cout << A[i][0] << "X1 + " << A[i][1] << "X2 + " << A[i][2] << "X3 = " << b[i] << endl; 
	}
}
// ���� 
bool jocobi::precision()
{
	double sum = 0;
	
	for(int i=0; i<N; i++)
	{
	    double temp;
		if(e[i]>0)
		{
			temp = e[i];
		}
		else
		{
			temp = -e[i];
		}
		sum = temp + sum;
	}
	if(sum<PRECISION)
	{
		return true;
	}
	else
	{
		return false;
	}
}
// ����ſɱȵ������� 
void jocobi::getBjFj()
{
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			if(i!=j)
			{
				A[i][j] = -A[i][j]/A[i][i];
            }           
		}
		b[i] = b[i]/A[i][i];
		A[i][i] = 0;
	}
}
// ����˷� 
void jocobi::matrixMultiplication()
{
	double temp[N] = {x[0], x[1], x[2]};
	for(int i=0; i<N; i++)
	{
		double sum = 0;
		for(int j=0; j<N; j++)
		{
			sum = temp[j]*A[i][j] + sum;
		}
		x[i] = sum + b[i];
	}
	for(int i=0; i<N; i++)
	{
		e[i] = temp[i]-x[i];
	}
}
// ������������ 
void jocobi::interation()
{
	while(1)
	{
		J.matrixMultiplication();
		count++;
		cout << "��" << count << "�ε������Ϊ";
		for(int i=0; i<N; i++)
		{
			printf("x%d = %.5f",i,x[i]);
			if(i+1!=N)
			{
				cout << ", ";
			}
			else 
			{
				cout << endl;
			}
	    } 
		if(J.precision())
		{
			break;
		}
	}
}
//-------------------------------------------------------������--------------------------- 
int main()
{
	Jocobi.welcome();
	Jocobi.print();
	Jocobi.getBjFj();
	Jocobi.print();
	Jocobi.interation();
	return 0;
}
