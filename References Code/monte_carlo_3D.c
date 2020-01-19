
#include<stdio.h>
#include<math.h>
#define pi 3.14195
double r=12345;
double a=9999, M =1 << 30;
double hamtichphan(double x,double y,double z)
{
	double f=z*z*sin(y);// f=3*x^2+2*x;
	return f;
}
double random()
{
	double res;
	r*=a;
	res=r/M; r-=floor(res)*M; res=r/M;
	return res;
}
double ran(double a,double b)
{
	return a+(b-a)*random();
}
double balop(double a1,double b1,double a2,double b2,double a3,double b3,int n)
{
	double kq=0;
	int i;
	for (i=0;i<n;i++)
	{
		double  tam1=ran(a1,b1);
		double tam2=ran(a2,b2);
		double tam3=ran(a3,b3);
		kq+=(b1-a1)*(b2-a2)*(b3-a3)*hamtichphan(tam1,tam2,tam3)/n;
		
	}
	return kq;
	
}
void main()
{
	double a1=0,b1=2*pi,a2=0,b2=pi,a3=0,b3=1;
	int n1=1000,m=100;// n1 la so doan ,m la so daon trong tuong doan nho
	int i,j,k;
	int n=n1*100;// so khoang chia tren toan mien tich phan
	int m1[n],tam2=0;
	double I=0,I1=0,I2=0,I3,I4=0,tam1=0,tam3=0;
/*	printf("nhap vao can duoi: ");
	scanf("%lf",&a1);
	printf("nhap vao can tren: ");
	scanf("%lf",&b1);
	printf("nhap vao can duoi: ");
	scanf("%lf",&a2);
	printf("nhap vao can tren: ");
	scanf("%lf",&b2);
	printf("nhap vao can duoi: ");
	scanf("%lf",&a3);
	printf("nhap vao can tren: ");
	scanf("%lf",&b3);*/
	double h1=(b1-a1)/n1;// h1 be rong cua khoang nho can 1
	double h2=(b2-a2)/n1;// h2 be rong cua khoang nho can 2
	double h3=(b3-a3)/n1;// h3 be rong cua khoang nho can 3
    //printf("%f\n",a1);
    //printf("%f",a2);
	for( i=0;i<n1;i++)
	{
		I1=balop(a1+i*h1,a1+(i+1)*h1,a2,b2,a3,b3,m);
		I2=balop(a1,b1,a2+i*h2,a2+(i+1)*h2,a3,b3,m);
		I4=balop(a1,b1,a2,b2,a3+i*h3,a3+(i+1)*h3,m);
		//printf("%f\n",hailop(a1+i*h1,a1+(i+1)*h1,a2+i*h2,a2+(i+1)*h2,m));
		I+=(I1+I2+I4)/3;
		m1[i]=m;
	}
	
	printf("k=%13.9f",I);
	for (j=1; j<15;j++)
	{
		for (k=0;k<n1;k++)
		{
			I1=balop(a1+k*h1,a1+(k+1)*h1,a2,b2,a3,b3,m1[k]);
		    I2=balop(a1,b1,a2+k*h2,a2+(k+1)*h2,a3,b3,m1[k]);
		    I4=balop(a1,b1,a2,b2,a3+k*h3,a3+(k+1)*h3,m1[k]);
		    I3=(I1+I2+I4)/3;
			m1[k]=n*I3/I;
			printf("m=%d\n",m1[k]);
			tam1+=(balop(a1+k*h1,a1+(k+1)*h1,a2,b2,a3,b3,m1[k])+balop(a1,b1,a2+k*h2,a2+(k+1)*h2,a3,b3,m1[k])+balop(a1,b1,a2,b2,a3+k*h3,a3+(k+1)*h3,m1[k]))/3;
		    tam2+=m1[k];
		}
	
		I=tam1;
		tam1=0;
		n=tam2;
		tam2=0;
	}
	printf("kp=%13.9f",I);
	
	


	
}
