//���������ѳ�
//�༶������91
//ѧ�ţ�2194411247
//Gauss ��Ԫ��
//----------------------------------------������ؿ�---------------------------------- 
#include <iostream>
#include <math.h>
#include <stdio.h>
//----------------------------------------���������ռ�-------------------------------- 
using namespace std;
//----------------------------------------���� class---------------------------------- 
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
//----------------------------------------����ȫ�ֱ���--------------------------------
const int n = 3;
double A[n][n] = {0};
double b[n] = {0};
double x[n] = {0};
gauss Gauss;
gauss G;
//----------------------------------------���� class �ĳ�Ա����----------------------- 
// ��ӭ��������� 
void gauss::welcome()
{
	// ������� 
	cout << "����Ԫ��˹��Ԫ��-���ѳ�-����91-2194411217" << endl;
	cout << "----------------------------" << endl;
	cout << "!����׼��!" << endl;
	cout << "������ϵ������ά�� n = ";
	//cin >> n;
	cout << n;
	cout << endl;
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			cout << "������ϵ������AԪ�� a" << "[" << i+1 << "]" << "[" << j+1 << "] = ";
			cin >> A[i][j]; 
		}
	}
	for(int i=0; i<n; i++)
	{
		cout << "������ϵ������bԪ�� b[" << i+1 << "]" << "[1] = ";
		cin >> b[i]; 
	}
	cout << "!�����������������Ԫ��˹��Ԫ���!" << endl;
}
// ��ӡ������ 
void gauss::print()
{
	cout << "�������Է�����Ϊ" << endl;
	for(int i=0; i<n; i++)
	{
		cout << A[i][0] << "X1 + " << A[i][1] << "X2 + " << A[i][2] << "X3 = " << b[i] << endl; 
	}
}
// ����Ԫ���� 
void gauss::bubbleSwap()
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			if(abs(A[i][0]) > abs(A[j][0]))
			{
				// ������ i �� j 
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
// ��ȥ���� 
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
// ����Ƿ���ϻش�����
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
// �ش����� 
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
// ������
void gauss::printResult()
{
	cout << "������Է�������: " << endl; 
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
//----------------------------------------------������----------------------------- 
int main()
{
	Gauss.welcome();
	Gauss.print();
	Gauss.elimination();
	Gauss.backSubstitution();
	Gauss.printResult();
	return 0;
}
