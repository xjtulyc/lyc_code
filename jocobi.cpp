//姓名：利友诚
//班级：人智91
//学号：2194411247
// Jocobi 迭代法
//----------------------------------------引用相关库---------------------------------- 
#include <iostream>
#include <math.h>
#include <stdio.h>
//----------------------------------------声明命名空间-------------------------------- 
using namespace std;
//----------------------------------------定义全局变量-------------------------------- 
const int N = 3;
const double PRECISION = 1e-4;
double A[N][N] = {0};
double b[N] = {0};
double x[N] = {0};
double e[N] = {1,1,1};
int count = 0;
//----------------------------------------定义 class---------------------------------- 
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
//---------------------------------------定义 class 的成员函数------------------------
// 初始化 
void jocobi::welcome()
{
	// 输入参数 
	cout << "雅可比迭代法-利友诚-人智91-2194411217" << endl;
	cout << "----------------------------" << endl;
	cout << "!数据准备!" << endl;
	cout << "请输入系数矩阵维数 n = ";
	//cin >> n;
	cout << N;
	cout << endl;
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			cout << "请输入系数矩阵A元素 a" << "[" << i+1 << "]" << "[" << j+1 << "] = ";
			cin >> A[i][j]; 
		}
	}
	for(int i=0; i<N; i++)
	{
		cout << "请输入系数矩阵b元素 b[" << i+1 << "]" << "[1] = ";
		cin >> b[i]; 
	}
	cout << "!输入结束，进行雅可比迭代法求解!" << endl;
}
// 打印方程组 
void jocobi::print()
{
	cout << "所求线性方程组为" << endl;
	for(int i=0; i<N; i++)
	{
		cout << A[i][0] << "X1 + " << A[i][1] << "X2 + " << A[i][2] << "X3 = " << b[i] << endl; 
	}
}
// 精度 
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
// 获得雅可比迭代矩阵 
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
// 矩阵乘法 
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
// 迭代并输出结果 
void jocobi::interation()
{
	while(1)
	{
		J.matrixMultiplication();
		count++;
		cout << "第" << count << "次迭代结果为";
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
//-------------------------------------------------------主函数--------------------------- 
int main()
{
	Jocobi.welcome();
	Jocobi.print();
	Jocobi.getBjFj();
	Jocobi.print();
	Jocobi.interation();
	return 0;
}
