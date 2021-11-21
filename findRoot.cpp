/*
���������ѳ�
�༶������91
ѧ�ţ�2194411247
*/ 
//-------------------------------------ͷ�ļ�׼��---------------------------------
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;
//-------------------------------------�ඨ��------------------------------------- 
class findRoot
{
	public:
		void Newton();
		void onePointRoot();
		void twoPointRoot();
		double f(double x);
		double daoshu(double x); 
};
//-------------------------------------��������---------------------------------
double findRoot::f(double x)
{
	double ans =  x*x*x+2*x*x+10*x-20;
    return ans;
}
void findRoot::onePointRoot()
{
	double x1,x2;
    cout << "�����ҽط�" << endl;
    cout << "���������ֵx0: ";
    cin >> x1;
    do
    {
    	cout << "���������ֵx2: ";
        cin >> x2; 
    }
    while(f(x1)*f(x2)>0);
    int count = 0;
	do
    {
    	count++;
        x2 = x1 - f(x1)*(x1-x2)/(f(x1)-f(x2));
		if(f(x2)==0)
		{
			cout << "x" << count << " = ";
            printf("%.7Lf\n",x2);
			break;
		}
		cout << "x" << count << " = ";
		printf("%.7Lf\n",x2);
    }
    while(fabs(f(x2))>=1e-6);
}
double findRoot::daoshu(double x)
 {
 	double ans;
 	ans = 10+4*x+3*x*x;
 	return ans;
 }
void findRoot::Newton()
{
	double x;
	cout << "ţ�ٷ�" << endl;
	cout << "�����ֵx0: ";
	cin >> x;
	double xS;
	int count=0;
	xS = x-f(x)/daoshu(x);
	do
	{
		count++;
		double temp = xS;
		xS = xS-f(xS)/daoshu(xS);
		cout << "x" << count << " = ";
		printf("%.7f\n",xS);
	}while(fabs(f(xS))>=1e-6);
}
 void findRoot::twoPointRoot()
{
	double x1,x2,xx;
    cout << "˫���ҽط�" << endl;
    do
    {
    	cout << "���������ֵx1, x2" << endl; 
        cin >> x1;
        cin >> x2; 
    }
    while(f(x1)*f(x2)>0);
    int count = 0;
	do
    {
    	count++;
        xx = x1 - f(x1)*(x1-x2)/(f(x1)-f(x2));
        if(f(xx)*f(x1)>0)
        {
        	x1=xx;
		}   
        else if(f(xx)*f(x2)>0)
        {
        	x2=xx;
		}
		else if(f(xx)==0)
		{
			cout << "x" << count << " = ";
            printf("%.7Lf\n",xx);
			break;
		}
		cout << "x" << count << " = ";
		printf("%.7Lf\n",xx);
    }
    while(fabs(f(xx))>=1e-6);
}
//--------------------------------------------������----------------------------- 
int main()
{
	findRoot findRoots;
	while(1)
	{
		cout << endl;
		cout << "ʹ��ţ�ٷ�, �����ҽط�, ˫���ҽط����" << endl;
	    cout << "��ѡ���������: " << endl;
	    cout << "ţ�ٷ�: 1" << endl;
	    cout << "�����ҽط�: 2" << endl;
	    cout << "˫���ҽط�: 3" << endl;
	    int choice;
	    cin >> choice;
	    if (choice==1)
	    {
		    findRoots.Newton();
	    }
	    else if (choice==2)
	    {
		    findRoots.onePointRoot();
	    }
	    else if (choice==3)
	    {
		    findRoots.twoPointRoot();
	    }
	    else
	    {
		    cout << "!DONE!" << endl;
		    break;
	    }
	}
	return 0;
}
