//姓名：利友诚
//班级：人智91
//学号：2194411247
//Gauss 消元法
//----------------------------------------引用相关库---------------------------------- 
#include <iostream>
#include <math.h>
#include <stdio.h>
//----------------------------------------声明命名空间-------------------------------- 
using namespace std;
//----------------------------------------定义 class---------------------------------- 
class gauss{
	public:
		void elimination();
		void bubbleSwap(); 
		void backSubstitution();
		void welcome();
		void print(); 
		bool check(); 
		void printResult(); 
	private:
			
}; 
//----------------------------------------创建全局变量--------------------------------
const int n = 3;
double A[n][n] = {0};
double b[n] = {0};
double x[n] = {0};
gauss Gauss;
gauss G;
//----------------------------------------定义 class 的成员函数----------------------- 
// 欢迎和输入参数 
void gauss::welcome()
{
	// 输入参数 
	cout << "列主元高斯消元法-利友诚-人智91-2194411217" << endl;
	cout << "----------------------------" << endl;
	cout << "!数据准备!" << endl;
	cout << "请输入系数矩阵维数 n = ";
	//cin >> n;
	cout << n;
	cout << endl;
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			cout << "请输入系数矩阵A元素 a" << "[" << i+1 << "]" << "[" << j+1 << "] = ";
			cin >> A[i][j]; 
		}
	}
	for(int i=0; i<n; i++)
	{
		cout << "请输入系数矩阵b元素 b[" << i+1 << "]" << "[1] = ";
		cin >> b[i]; 
	}
	cout << "!输入结束，进行列主元高斯消元求解!" << endl;
}
// 打印方程组 
void gauss::print()
{
	cout << "所求线性方程组为" << endl;
	for(int i=0; i<n; i++)
	{
		cout << A[i][0] << "X1 + " << A[i][1] << "X2 + " << A[i][2] << "X3 = " << b[i] << endl; 
	}
}
// 列主元交换 
void gauss::bubbleSwap()
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			if(abs(A[i][0]) > abs(A[j][0]))
			{
				// 交换行 i 和 j 
				double temp[n] = {0};
				for(int k=0; k<n; k++)
				{
					temp[k] = A[i][k];
					A[i][k] = A[j][k];
					A[j][k] = temp[k];
				}
				double t = b[j];
				b[j] = b[i];
				b[i] = t;
			}
		}
	}
}
// 消去步骤 
void gauss::elimination()
{
	G.bubbleSwap();
	G.print();
	double divide = 0;
   	for(int i=0; i<n; i++)
   	{
   		
   		for(int j=i+1; j<n; j++)
   		{
   			int count = 0;
   			while(1)
   			{
   				if(A[i][count] != 0 && count<n)
   				{
   					divide = -A[j][count]/A[i][count];
   					break;
			    }
			    else if(A[i][count] == 0 && count<n)
			    {
			    	count++;
				}
				else
				{
					cout << "!OUT OF RANGE!" << endl;
					break;
				}
		    }
   			for(int k=0; k<n; k++)
   			{
   				A[j][k] = A[i][k]*divide + A[j][k];
   				
		    }
		    b[j] = b[i]*divide + b[j];
	    }
    }
}
// 检查是否符合回代条件
bool gauss::check()
{
	bool corss = true;
	bool downTriangle = true;
	for(int i=0; i<n; i++)
	{
		corss = corss && (A[i][i] != 0);
	}
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			if(j<i)
			{
				downTriangle = downTriangle && (A[i][j] == 0);
			}
		}
	}
	return corss && downTriangle;
}
// 回代步骤 
void gauss::backSubstitution()
{
	G.print(); 
	if(G.check())
	{
		int j = 0;
		for(int i=0; i<n; i++)
		{
			j = n-i-1;
			double den = b[j];
			double num = A[j][j];
			for(int k=j+1; k<n; k++)
			{
				den = -A[j][k]*x[k] + den;
			}
			x[j] = den/num;
		}
		
	}
	else
	{
		cout << "!ERROR!CANNOT COUNT..." << endl;
	}
 }
// 输出结果
void gauss::printResult()
{
	cout << "输出线性方程组结果: " << endl; 
	for(int i=0; i<n; i++)
	{
		cout << "x1 = ";
		printf("%.4f",x[i]);
		if(i!=n-1)
		{
			cout << ", ";
		}
		else
		{
			cout << endl;
		}
	}
}
//----------------------------------------------主函数----------------------------- 
int main()
{
	Gauss.welcome();
	Gauss.print();
	Gauss.elimination();
	Gauss.backSubstitution();
	Gauss.printResult();
	return 0;
}
