#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define K 10000						//K: So diem gieo tren toan mien.
#define N 100						//N: So diem gieo trong mot doan.
#define tiny 1e-6
#define sll 13

/*_____ TÍCH PHÂN MONTE - CARLO 2 CHIÊU _____*/
/*===========================================*/
/*========= Lây diem ngâu nhiên ============*/
double ran(double t, double b)
{
	double c;
    c=t+(b-t)*rand()/RAND_MAX;
    return c;
}
/*====== Nhap vao ham tinh tich phan ======*/
double f(double x, double y)
{	
	double 
	//	ham=(x+y)*(x+y);	//N1	1.166666667		19
	//	ham=1/(x*x+y*y+2);  //N2	0.384236		18
	//	ham=1/(x*x+2*x+2);	//N3	0.321751		16
	//	ham=1/(cos(x)+sin(x)+1); //N4	0.4358665	13
	//	ham=x*x+3;		//N5	3.3333333333		16
	
	
	//		ham=1/((x-0.5)*(x-0.5)+tiny);		//3137.58	1e-6	19		//314153	1e-10	199		//3.141458e+08		1e-16
	
	//		ham=(1/((x-0.5)*(x-0.5)) + (1/((x-0.75)*(x-0.75)+tiny)));		//6273.85	1e-6	!!!!		//628309.19		1e-10		//6.28318x10^8	1e-16
	
	//		ham=(1/((x-0.5)*(x-0.5)+tiny)) + (1/((y-0.75)*(y-0.75)+tiny));		//6273.85	1e-6	5	//628309	1e-10	2	//1e-16	
	
	//		ham=1/((x-0.5)*(x-0.5) + (y-0.75)*(y-0.75)+tiny);		//38.97365		1e-6	9	//67.90724	1e-10	 2	//111.3065		1e-16
	return ham;
}
/*== Chia doan (Chia mien lay tich phan) ==*/
void chiadoan(double a,double b, double n,double h, double xi[])
{	int i;
	for (i=0;i<n;i++)
	xi[i+1]=xi[i]+h;
}
/*========== Tính toán trong sô ===========*/
void tinhtrongso(double n, double ts[], double c[], double G)
{
	int i;
	for (i=0;i<n;i++) 
	{
	ts[i]=c[i]/G*100000;
	}
}
/*======= Chia cac doan nho (mini) ========*/
void chiadoanmini(double n, double ts[], double z[], double xi[])
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
/*========== Chia lai các doan nho ===========*/
void chialaidoan(double n, double xi[], double z[])
{
	int i;
	for (i=1;i<n;i++)
	{
	xi[i]=z[i*1000-1];
//	printf("%f ",xi[i]);
	}
}
/*========== Xuat kiem tra thu ===========*/
void xuat(double a[])
{ 
	int i;
	printf("\nGia tri:\n");
	for (i=0;i<101;i++) printf("%f ",a[i]);
}

/*================= HÀM CHÍNH =================*/
main ()
{

	double x[100][100],xi[101],z1[100000]; 			//Mien lay tich phan x[so doan][so diem gieo trong tung doan].
													//xi: gia tri cua x thu i; z1: So diem cua 10.000 doan mini.
	double y[100][100],yi[101],z2[100000]; 			//Tuong tu nhu tren doi voi chieu y.
	double c1[100],c2[100], tsx[100],tsy[100]; 		//c1: (tong tich phan)*delta(x) cua doan nho; c2 theo chieu y.
													//tsx: Mang chua cac gia tri cua trong so theo chieu x; tsy theo chieu y.
	int tam3,i,j,k,l,u,v,p,q,so;   
	double I,G1,G2,h1,h2,tamx,tamy,n;

	double a1=0,b1=1,								//Khoi gan các cân theo chieu x
		   a2=0,b2=1;								//Khoi gan cac can theo chieu y

xi[0]=a1;  yi[0]=a2;
n=K/N;
h1=(b1-a1)/n; h2=(b2-a2)/n;

chiadoan(a1,b1,n,h1,xi);
chiadoan(a2,b2,n,h2,yi);
for (l=0;l<sll;l++)
{
printf("\n lan thu: %d\n",l+1);
a1=0,	b1=1,	a2=0,	b2=1;

/*====== Xet theo chieu X =======*/
G1=0;							
	for (i=0;i<n;i++)
	{
		c1[i]=0;
		for(j=0;j<N;j++)
			{
			x[i][j]=ran(xi[i],xi[i+1]);			//Gieo ngau nhien tren tung doan mien X
			for (k=0;k<100;k++)
				{
				so=(int)ran(1,99.999);
				tamy=ran(yi[so],yi[so+1]);
//				printf("%f ",tamy);
				c1[i]=c1[i]+f(x[i][j],tamy);	//Cong don gia tri tich phan tung doan nho
				}  
			}	
		c1[i]=c1[i]*(xi[i+1]-xi[i]);
//			printf(" %f ",c[i]); 
	G1=G1+c1[i];  								//tong C1 toan mien (a1;b1)
	}
tinhtrongso(n,tsx,c1,G1);
xi[0]=a1;
z1[0]=a1;						
chiadoanmini(n,tsx,z1,xi);
xi[0]=a1;
z1[0]=a1;
chialaidoan(n,xi,z1);
xi[100]=b1;

/*====== Xet theo chieu Y =======*/
G2=0;
	for (i=0;i<n;i++)
	{
		c2[i]=0; 
		for(j=0;j<N;j++)
			{
			y[i][j]=ran(yi[i],yi[i+1]);			//Gieo ngau nhien tren tung doan mien X
			for (k=0;k<100;k++)
				{
				so=(int)ran(1,99.999);
				tamx=ran(xi[so],xi[so+1]);
//				printf("%f ",tamy);
				c2[i]=c2[i]+f(tamx,y[i][j]);	//Cong don gia tri tich phan tung doan nho
				}  
			}
		c2[i]=c2[i]*(yi[i+1]-yi[i]);			
//			printf(" %f ",c[i]); 

	G2=G2+c2[i];  								//tong C2 toan mien (a2;b2)
	}
tinhtrongso(n,tsy,c2,G2);
yi[0]=a2;
z2[0]=a2;
chiadoanmini(n,tsy,z2,yi);
yi[0]=a2;
z2[0]=a2;
chialaidoan(n,yi,z2);
yi[100]=b2;

I=0;
for (i=0;i<n;i++)
	{
		for (j=0;j<100;j++)
			{
			tamx=ran(xi[i],xi[i+1]);
			for (k=0;k<100;k++)
				{
				tamy=ran(yi[k],yi[k+1]);
				I=I+f(tamx,tamy)*(xi[i+1]-xi[i])*(yi[k+1]-yi[k])/100;
				}		
//			printf("\n%f",n);
			}
	}
printf("\n----Ket qua la: %f\n",I);
}
printf("\n----Ket qua la: %f\n",I);
/*========== Tính gia tri tich phan ==========*/

}
