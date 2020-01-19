#include<stdio.h>
#include<math.h>
#define pi 3.14
double r=12345;
double a=9999, M =1 << 30;
double hamtichphan(double x,double y,double z,double t)
{
	double f=(z+x+y+t);// f=3*x^2+2*x;
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
double bonlop(double a1,double b1,double a2,double b2,double a3,double b3,double a4, double b4, int n)
{
	double kq=0;
	int i;
	for (i=0;i<n;i++)
	{
		double  tam1=ran(a1,b1);
		double tam2=ran(a2,b2);
		double tam3=ran(a3,b3);
		double tam4=ran(a4,b4);
		kq+=(b1-a1)*(b2-a2)*(b3-a3)*(b4-a4)*hamtichphan(tam1,tam2,tam3,tam4)/n;
		
	}
	return kq;
	
}
void main()
{
	double a1,b1,a2,b2,a3,b3,a4,b4;
	int n1=1000,m=100;// n1 la so doan ,m la so daon trong tuong doan nho
	int i,j,k;
	int n=n1*100;// so khoang chia tren toan mien tich phan
	int m1[n],tam2=0;
	double I=0,I1=0,I2=0,I3,I4=0,I5=0,tam1=0,tam3=0;
	// can 1
	printf("nhap vao can duoi: ");
	scanf("%lf",&a1);
	printf("nhap vao can tren: ");
	scanf("%lf",&b1);
	// can 2
	printf("nhap vao can duoi: ");
	scanf("%lf",&a2);
	printf("nhap vao can tren: ");
	scanf("%lf",&b2);
	//can 3
	printf("nhap vao can duoi: ");
	scanf("%lf",&a3);
	printf("nhap vao can tren: ");
	scanf("%lf",&b3);
	// can 4
	printf("nhap vao can duoi: ");
	scanf("%lf",&a4);
	printf("nhap vao can tren: ");
	scanf("%lf",&b4);
	
	double h1=(b1-a1)/n1;// h1 be rong cua khoang nho can 1
	double h2=(b2-a2)/n1;// h2 be rong cua khoang nho can 2
	double h3=(b3-a3)/n1;// h3 be rong cua khoang nho can 3
	double h4=(b4-a4)/n1;// h3 be rong cua khoang nho can 4
    //printf("%f\n",a1);
    //printf("%f",a2);
	for( i=0;i<n1;i++)
	{
		I1=bonlop(a1+i*h1,a1+(i+1)*h1,a2,b2,a3,b3,a4,b4,m);
		I2=bonlop(a1,b1,a2+i*h2,a2+(i+1)*h2,a3,b3,a4,b4,m);
		I4=bonlop(a1,b1,a2,b2,a3+i*h3,a3+(i+1)*h3,a4,b4,m);
		I5=bonlop(a1,b1,a2,b2,a3,b3,a4+i*h4,a4+(i+1)*h4,m);
		//printf("%f\n",hailop(a1+i*h1,a1+(i+1)*h1,a2+i*h2,a2+(i+1)*h2,m));
		I+=(I1+I2+I4+I5)/4;
		m1[i]=m;
	}
	
	printf("k=%13.9f",I);
	for (j=1; j<5;j++)
	{
		for (k=0;k<n1;k++)
		{
			I1=bonlop(a1+k*h1,a1+(k+1)*h1,a2,b2,a3,b3,a4,b4,m1[k]);
			I2=bonlop(a1,b1,a2+k*h2,a2+(k+1)*h2,a3,b3,a4,b4,m1[k]);
			I4=bonlop(a1,b1,a2,b2,a3+k*h3,a3+(k+1)*h3,a4,b4,m1[k]);
			I5=bonlop(a1,b1,a2,b2,a3,b3,a4+k*h4,a4+(k+1)*h4,m1[k]);
		    I3=(I1+I2+I4+I5)/4;
			m1[k]=n*I3/I;
			tam1+=(bonlop(a1+k*h1,a1+(k+1)*h1,a2,b2,a3,b3,a4,b4,m1[k])+bonlop(a1,b1,a2+k*h2,a2+(k+1)*h2,a3,b3,a4,b4,m1[k])+bonlop(a1,b1,a2,b2,a3+k*h3,a3+(k+1)*h3,a4,b4,m1[k])+bonlop(a1,b1,a2,b2,a3,b3,a4+k*h4,a4+(k+1)*h4,m1[k]))/4;
		    tam2+=m1[k];
		}
	
		I=tam1;
		tam1=0;
		n=tam2;
		tam2=0;
	}
	printf("kp=%13.9f",I);
	
	


	
}
