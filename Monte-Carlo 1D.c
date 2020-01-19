#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define K 10000						//K: So diem gieo tren toan mien.
#define N 100						//N: So diem gieo trong mot doan.
#define tiny 1e-6

/*_____ TÍCH PHÂN MONTE - CARLO 1 CHIÊU _____*/
/*===========================================*/
/*========= Lây diem ngâu nhiên ============*/
double ran(double t, double b)
{
	double c;
    c=t+(b-t)*rand()/RAND_MAX;
    return c;
}
/*====== Nhap vao ham tinh tich phan ======*/
double f(double x)
{	
	double 
	//		ham=x*x+3;	//N5	3.3333333333	4.6diem
	//		ham=1/(x*x+2*x+2);	//N3	0.321751
	//		ham=1/(cos(x)+sin(x)+1); //N4	0.435866590692474
	//		ham=(1/((x-0.5)*(x-0.5)+tiny));
	//		ham=(1/((x-0.5)*(x-0.5)+tiny)) + (1/((x-0.75)*(x-0.75)+tiny));
	//		ham=(1/((x-0.5)*(x-0.5)+tiny)) + (1/((y-0.75)*(y-0.75)+tiny));
	//		ham=1/((x-0.5)*(x-0.5) + (y-0.75)*(y-0.75)+tiny);
	return ham;
}
/*== Chia doan (Chia mien lay tich phan) ==*/
void chiadoan(double a,double b, double n,double h, double xi[])
{	int i;
	for (i=0;i<n;i++)
	xi[i+1]=xi[i]+h;
}
/*========== Tính toán trong sô ===========*/
void tinhtrongso(double n,double ts[], double c[],double G)
{
	int i;
	for (i=0;i<n;i++) 
	{
	ts[i]=K*c[i]/G*10;
	}
}
/*======= Chia cac doan nho (mini) ========*/
void chiadoanmini(double n, double ts[],double z[],double xi[])
{ 
int v,i,j;
double h;
v=1;
for (i=0;i<n;i++)
	{
	h=0;
	if (ts[i]-(int)ts[i]>0.5) ts[i]=(int)ts[i]+1;
//	printf(" %d ",(int)ts[i]);
	h=(xi[i+1]-xi[i])/(int)ts[i];
	for (j=0;j<(int)ts[i];j++)
		{
		z[j+v]=z[j+v-1]+h;	
		}
		v=v+(int)ts[i];
	}
}
/*========== Chia lai doan các doan ===========*/
void chialaidoan(double n, double xi[], double z[])
{
	int i;
	for (i=1;i<n;i++)
	{
	xi[i]=z[i*1000-1];
	}
}

/*================= HÀM CHÍNH =================*/
void main ()
{
	double x[100][100],z[100000]; 			//Mien lay tich phan x[so doan][so diem gieo trong tung doan].
											//z: So diem cua 10.000 doan mini.
	double xi[101];  						//gia tri cua x thu i.
	double c[100], ts[100]; 				//c: (tong tich phan)*delta(x) cua doan nho.
											//ts: Mang chua cac gia tri cua trong so.
	int tam3,i,j,l,u,v,p,q;   
	double G,h,tam2,tam,n;
	double a=0,		b=1;					//Can cua tich phan
	srand(time(0));

xi[0]=a;
h=(b-a)/(K/N);
n=K/N;
chiadoan(a,b,n,h,xi);

for (l=0;l<20;l++)
{	G=0;
	for (i=0;i<n;i++)
	{	c[i]=0; 
		for(j=0;j<N;j++)
			{
				x[i][j]=ran(xi[i],xi[i+1]);	//Gieo ngau nhien tren tung doan.
				c[i]=c[i]+f(x[i][j]);		//Cong don gia tri tich phan tren doan nho.
			}  
		c[i]=c[i]*(xi[i+1]-xi[i]);
//			printf(" %f ",c[i]); 
	G=G+c[i]; 								 //Tong gia tri C[i] toan mien.
	}
tinhtrongso(n,ts,c,G);
xi[0]=a;
z[0]=a;
chiadoanmini(n,ts,z,xi);
chialaidoan(n,xi,z);
xi[100]=b;
}
printf("\n----- Ket qua la: %f\n",G/N);
}
