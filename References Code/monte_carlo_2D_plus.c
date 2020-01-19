#include<stdio.h>
#include<math.h>
#define pi 3.14
double r=12345;
double a=9999, M =1 << 30;
double hamtichphan(double x,double y)
{
	double f=(3*x*x+2*y);// f=3*x^2+2*x;
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

double hailop(double a1,double b1,double a2,double b2,int n)
{
	double kq=0;
	int i;
	for (i=0;i<n;i++)
	{
		double  tam1=ran(a1,b1);
		double  tam2=ran(a2,b2);
		
		kq+=(b1-a1)*(b2-a2)*hamtichphan(tam1,tam2)/n;
		
	}
	return kq;
	
}
void main()
{
	double a1,b1,a2,b2;
	int n1=1000,m=100;// n1 la so doan ,m la so doan trong tung doan nho
	int i,j,k;
	int n=n1*100;// so khoang chia tren toan mien tich phan
	int m1[n],tam2=0;
	double I=0,I1=0,I2=0,I3,tam1=0,tam3=0;
	printf("nhap vao can duoi: ");
	scanf("%lf",&a1);
	printf("nhap vao can tren: ");
	scanf("%lf",&b1);
	printf("nhap vao can duoi: ");
	scanf("%lf",&a2);
	printf("nhap vao can tren: ");
	scanf("%lf",&b2);
	double h1=(b1-a1)/n1;// h1 be rong cua khoang nho can 1
	double h2=(b2-a2)/n1;// h2 be rong cua khoang nho can 2
    //printf("%f\n",a1);
    //printf("%f",a2);
	for( i=0;i<n1;i++)
	{
		I1=hailop(a1+i*h1,a1+(i+1)*h1,a2,b2,m);
		I2=hailop(a1,b1,a2+i*h2,a2+(i+1)*h2,m);
		//printf("%f\n",hailop(a1+i*h1,a1+(i+1)*h1,a2+i*h2,a2+(i+1)*h2,m));
		I+=(I1+I2)/2;
		m1[i]=m;
	}
	
	printf("socap=%13.9f\n",I);
	for (j=1; j<4;j++)
	{
		for (k=0;k<n1;k++)
		{
			I1=hailop(a1+k*h1,a1+(k+1)*h1,a2,b2,m1[k]);
		    I2=hailop(a1,b1,a2+k*h2,a2+(k+1)*h2,m1[k]);
		    I3=(I1+I2)/2;
			m1[k]=n*I3/I;
			tam1+=(hailop(a1+k*h1,a1+(k+1)*h1,a2,b2,m1[k])+hailop(a1,b1,a2+k*h2,a2+(k+1)*h2,m1[k]))/2;
		    tam2+=m1[k];
		}
	
		I=tam1;
		tam1=0;
		n=tam2;
		tam2=0;
		printf("kp=%13.9f\n",I);
	}
	printf("kp=%13.9f",I);
}
