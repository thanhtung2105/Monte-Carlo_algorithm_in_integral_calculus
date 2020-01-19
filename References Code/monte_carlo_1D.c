#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
double ran(double t, double b)
{
	double c;
    c=t+(b-t)*rand()/RAND_MAX;
//    printf("%f ",c);
    return c;
}
double f(double x)
{	
	double ham=(x*x*x);
	return ham;
}
main ()
{

	double x[100][100]; //100 gia tri random cua moi 100 doan
	double xi[101]; //gia tri cua x thu i
	double c[100]; // tong f cua doan nho
	int i,j,l;
	double G,h,tam2,tam;
	
	float  N=100, K=10000;
	double a=0.00000000000000001,b=1; //can
	
	
	srand(time(0));
	xi[0]=a;   //so diem trong 1 doan 
	h=(b-a)/(K/100);
	for (i=0;i<K/100;i++)
	{xi[i+1]=xi[i]+h;	printf("%f  ",xi[i]);}
	printf("\n_________________________________________\n");


for (l=0;l<10;l++)
{	
	
G=0;
	for (i=0;i<(K/N);i++)
	{
		c[i]=0; 
		for(j=0;j<100;j++)
			{
				x[i][j]=ran(xi[i],xi[i+1]);
				c[i]=c[i]+f((x[i][j])/(K*(xi[i]-xi[i-1])/100));
				
			}   
	
	G=G+c[i];  //tong gia tri f toan mien
}


printf("%lf\n",G*(b-a)/K);
tam=0;
for (i=0;i<K/100;i++) tam=K*c[i]/G+tam;
K=tam;
printf("\n\t X %f \t %f X \n",K,tam);









xi[0]=a;

for (i=0;i<K/100;i++)
	{
		tam2=(b-a)/K;
		
		xi[i+1]=xi[i]+100*tam2;
		xi[100]=b;
		printf(" %f ",xi[i+1]);
	}
	printf("\n-----------------------------------------\n");
}


printf("\n %f ",G*(b-a)/tam);
}
