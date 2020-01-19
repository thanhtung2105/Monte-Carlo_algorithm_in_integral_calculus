#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define N 10000

double r=12345;
double a=9999, M =1 << 30;
double hamtichphan(double x,double y)
{
	double f=(x*x+y*y);// f=3*x^2+2*x;
	return f;
}


double ngaunhien(double t, double b)
{
	int kq;
    kq=t+(b-t)*rand()/RAND_MAX;
    return kq;
}


double hailop(double a1,double b1,double a2,double b2,int n)
{
	double kq=0; double x,y;
	int i;
	srand(time(0));
	for (i=0;i<n;i++)
	
	{
		x=ngaunhien(a1,b1);
		y=ngaunhien(a2,b2);
		kq+=(b1-a1)*(b2-a2)*hamtichphan(x,y)/n;
		
	}
	return kq;	
}


void main()
{
	srand(time(0));
	double a1=1,b1=2,a2=3,b2=5;
	
	int n1=1000,m=100;// n1 la so doan ,m la so daon trong tung doan nho
	int i,j,k;
	int n=n1*100;// so khoang chia tren toan mien tich phan
	int m1[n];
	double I=0,I1=0,I2=0,I3;
	double tam3,tam4;
	
	
	double h1=(b1-a1)/n1;// h1 be rong cua khoang nho can 1
	double h2=(b2-a2)/n1;// h2 be rong cua khoang nho can 2
 
	for( i=0;i<n1;i++)
	{
		I1=hailop(a1+i*h1,a1+(i+1)*h1,a2,b2,m);
		I2=hailop(a1,b1,a2+i*h2,a2+(i+1)*h2,m);
		I+=(I1+I2)/2;
		m1[i]=m;
	}
	
	printf("k=%13.9f",I);
	for (j=1; j<15;j++)
	{
		for (k=0;k<n1;k++)
		{
			I1=hailop(a1+k*h1,a1+(k+1)*h1,a2,b2,m1[k]);
		    I2=hailop(a1,b1,a2+k*h2,a2+(k+1)*h2,m1[k]);
		    I3=(I1+I2)/2;
			m1[k]=n*I3/I;
			tam3+=(hailop(a1+k*h1,a1+(k+1)*h1,a2,b2,m1[k])+hailop(a1,b1,a2+k*h2,a2+(k+1)*h2,m1[k]))/2;
		    tam4+=m1[k]; 
		}
	
		I=tam3;
			printf("\nkp=%13.9f",I);
		tam3=0;
			
		n=tam4;
		tam4=0;
	}
	printf("\nkp=%13.9f",I);
}
