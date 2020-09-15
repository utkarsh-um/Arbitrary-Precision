#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <complex.h>
#include "arbprecision.h"

#define MAX_LIMIT 100
char **oup;
double addtime_arb=0.0,subtime_arb=0.0,prodtime_arb=0.0,quottime_arb=0.0,abstime_arb=0.0;
double addtime_c=0.0,subtime_c=0.0,prodtime_c=0.0,quottime_c=0.0,abstime_c=0.0;

void write_output(char *realp, char *imagp)
{
	FILE *fptr = fopen(oup[2], "a");
 	fprintf(fptr, "(%s,%s)\n", realp,imagp);
 	fclose(fptr);
}
void processdata(char* str)
{
	int fsp=-1,fobr=-1,fcm=-1,fcbr=-1,sobr=-1,scm=-1,scbr=-1;
	int sp=0,obr=0,cbr=0,cm=0;
	int ij=0;
	while(str[ij]!='\0')
	{
		if(str[ij]==' ')
		{
			if(sp==0)
				fsp=ij;
			sp++;
		}
		else if(str[ij]=='(')
		{
			if(obr==0)
				fobr=ij;
			else if(obr==1)
				sobr=ij;
			obr++;
		}
		else if(str[ij]==')')
		{
			if(cbr==0)
				fcbr=ij;
			else if(cbr==1)
				scbr=ij;
			cbr++;
		}
		else if(str[ij]==',')
		{
			if(cm==0)
				fcm=ij;
			else if(cm==1)
				scm=ij;
			cm++;
		}
		ij++;
	}

	char* oprtr=(char*)(malloc(fsp+1));
	char* a=(char*)(malloc(fcm-fobr));
	char* b=(char*)(malloc(fcbr-fcm));
	char* c=(char*)(malloc(scm-sobr));
	char* d=(char*)(malloc(scbr-scm));
	ij=0;
	int opt1=0,a1=0,b1=0,c1=0,d1=0;
	while(str[ij]!='\0')
	{
		if(ij>=0 && ij<fsp)
		{
			oprtr[opt1]=str[ij];
			opt1++;
		}
		else if(ij>fobr && ij<fcm)
		{
			a[a1]=str[ij];
			a1++;
		}
		else if(ij>fcm && ij<fcbr)
		{
			b[b1]=str[ij];
			b1++;
		}
		else if(ij>sobr && ij<scm)
		{
			c[c1]=str[ij];
			c1++;
		}
		else if(ij>scm && ij<scbr)
		{
			d[d1]=str[ij];
			d1++;
		}
		ij++;
	}
	oprtr[opt1]='\0';
	a[a1]='\0';
	b[b1]='\0';
	if(c1>0)
		c[c1]='\0';
	if(d1>0)
		d[d1]='\0';



	double ad,bd,cd,dd;
			int ma=0,mb=0,mc=0,md=0;
			if(a[0]=='-')
			{
				ma=1;
			}
			if(b[0]=='-')
			{
				mb=1;
			}
			if(c1>0){
			if(c[0]=='-')
			{
				mc=1;
	
			}}
			if(d1>0){
			if(d[0]=='-')
			{
				md=1;
	
			}}
			sscanf(a+ma, "%lf", &ad);
			sscanf(b+mb, "%lf", &bd);
			if(c1>0)
			sscanf(c+mc, "%lf", &cd);
			if(d1>0)
			sscanf(d+md, "%lf", &dd);
			if(ma==1)
				{ad*=(-1.0);
					}
			if(mb==1)
				{bd*=(-1.0);
					}
			if(c1>0){
			if(mc==1)
				{cd*=(-1.0);
					}}
				if(d1>0){
			if(md==1)
				{dd*=(-1.0);
					}}

			double complex zd1 = ad+bd*I;
			double complex zd2 = cd+dd*I;
			// printf("The121314 sum: Z1 + Z2 = %.2f %+.2fi\n", creal(zd1), cimag(zd1));

			// printf("The sum: Z1 + Z2 = %.2f %+.2fi\n", creal(zd2), cimag(zd2));

	if(strcmp(oprtr,"ADD")==0 || strcmp(oprtr,"SUB")==0)
	{
			clock_t start, end;
			double cpu_time_used;
			start = clock();

			char *z1=addsublarge(a,c,oprtr);
			char *z2=addsublarge(b,d,oprtr);

			end = clock();
			cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
			
			

			if(strcmp(oprtr,"ADD")==0)
				addtime_arb+=cpu_time_used;
			else
				subtime_arb+=cpu_time_used;
			write_output(z1,z2);
			free(z1);
			free(z2);

				if(strcmp(oprtr,"ADD")==0)
				{
					double complex zre;
					double cpu_time_used1;
					start = clock();

					zre=zd1+zd2;

					end = clock();
					cpu_time_used1 = ((double) (end - start)) / CLOCKS_PER_SEC;

					addtime_c+=cpu_time_used1;
				}
				else
				{
					double complex zre;
					double cpu_time_used1;
					start = clock();

					zre=zd1-zd2;

					end = clock();
					cpu_time_used1 = ((double) (end - start)) / CLOCKS_PER_SEC;

				subtime_c+=cpu_time_used1;

			}
		
	}
	else if(strcmp(oprtr,"PROD")==0)
	{
			clock_t start, end;
			double cpu_time_used;
			start = clock();
			char *gh1=multiply(a,c,25);
			char *gh2=multiply(b,d,25);
			char *gh3=multiply(a,d,25);
			char *gh4=multiply(b,c,25);
			char* z1=addsublarge(gh1,gh2,"SUB");
			char* z2=addsublarge(gh3,gh4,"ADD");

			end = clock();
			cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

			prodtime_arb+=cpu_time_used;

			write_output(z1,z2);
			free(z1);
			free(z2);
			free(gh1);
			free(gh2);
			free(gh3);
			free(gh4);

			double complex zre;
					double cpu_time_used1;
					start = clock();

					zre=zd1*zd2;

					end = clock();
					cpu_time_used1 = ((double) (end - start)) / CLOCKS_PER_SEC;

					prodtime_c+=cpu_time_used1;
			

	}
	else if(strcmp(oprtr,"QUOT")==0)
	{	
			clock_t start, end;
			double cpu_time_used;
			start = clock();

			char *nr1=multiply(c,c,25);
			char *nr2=multiply(d,d,25);
			char *nr3=multiply(a,c,25);
			char *nr4=multiply(b,d,25);
			char *nr5=multiply(b,c,25);
			char *nr6=multiply(a,d,25);

			char *um1=addsublarge(nr3,nr4,"ADD");
			char *um2=addsublarge(nr5,nr6,"SUB");

			char *ab2=addsublarge(nr1,nr2,"ADD");

			char *z1=quot(um1,ab2);
			char *z2=quot(um2,ab2);

			end = clock();
			cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

			quottime_arb+=cpu_time_used;

			write_output(z1,z2);

			free(nr1);
			free(nr2);
			free(nr3);
			free(nr4);
			free(nr5);
			free(nr6);

			free(um1);
			free(um2);

			free(ab2);
			free(z1);
			free(z2);


			double complex zre;
					double cpu_time_used1;
					start = clock();

					zre=zd1/zd2;

					end = clock();
					cpu_time_used1 = ((double) (end - start)) / CLOCKS_PER_SEC;

					quottime_c+=cpu_time_used1;
			
	}
	else if(strcmp(oprtr,"ABS")==0)
	{	
		clock_t start, end;
			double cpu_time_used;
			start = clock();
			char *um1=multiply(a,a,25);
			char *um2=multiply(b,b,25);
		char *ab2=addsublarge(um1,um2,"ADD");
		char *absv=sqrtlarge(ab2);

		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

		abstime_arb+=cpu_time_used;
		char* ze=(char *)malloc(2);
		ze[0]='0';
		ze[1]='\0';
		write_output(absv,ze);

		free(um1);
		free(um2);
		free(ab2);
		free(absv);
		free(ze);

		double abs1234;
					double cpu_time_used1;
					start = clock();

					abs1234=cabs(zd1);

					end = clock();
					cpu_time_used1 = ((double) (end - start)) / CLOCKS_PER_SEC;

					abstime_c+=cpu_time_used1;

	}
	
free(oprtr);

free(a);
free(b);
free(c);
free(d);


		
}



int main(int argc, char const *argv[])
{
	FILE *inp=fopen(argv[1],"r");
	oup=argv;
	FILE *fptr = fopen(oup[2], "w");
 	fclose(fptr);
	char ch;
	char *str=(char*)malloc(MAX_LIMIT*sizeof(char));
	int size=MAX_LIMIT;
	int x=0;
	int control=0;
	while(1)
	{
		ch=fgetc(inp);
		if(ch==EOF)
			{
				str[x] = '\0';
				processdata(str);
				free(str);
				str=(char*)malloc(MAX_LIMIT*sizeof(char));
				size=MAX_LIMIT;
				x=0;
				break;
			}
		else if(ch=='\n')
			{	
				str[x] = '\0';
				processdata(str);
				free(str);
				str=(char*)malloc(MAX_LIMIT*sizeof(char));
				size=MAX_LIMIT;
				x=0;
			}
		else
			{

				if(x==size)
				{
					size+=50;
					str=(char*)realloc(str, size*sizeof(char));
					str[x]=ch;
					x++;
				}
				else
				{
					str[x]=ch;
					x++;

				}
				}
			}


	fclose(inp);
	// printf("%f\n", addtime_c);
	// 	printf("%f\n", subtime_c);
	// 	printf("%f\n", prodtime_c);
	// 	printf("%f\n", quottime_c);
	// 	printf("%f\n", abstime_c);
	int counter=0;
	while(oup[3][counter]!='\0')
		counter++;
	char *x1=(char*)malloc(14+counter);
		x1[0]='s';
		x1[1]='e';
		x1[2]='t';
		x1[3]=' ';
		x1[4]='o';
		x1[5]='u';
		x1[6]='t';
		x1[7]='p';
		x1[8]='u';
		x1[9]='t';
		x1[10]=' ';
		x1[11]='\'';
		int ijk=0;
		while(oup[3][ijk]!='\0')
		{
			x1[12+ijk]=oup[3][ijk];
			ijk++;
		}
		x1[12+counter]='\'';
		x1[13+counter]='\0';

		 	char * commands[] = {"set terminal pngcairo font \"arial,10\" size 1000,750", x1,"set title \"X_arb is for arbprecision and X_c is for C complex library\"","set boxwidth 0.9","set style fill solid","set ylabel \"Time (s)\"","plot 'data.temp' using 2:xtic(1) with boxes"};
    		FILE * temp_data = fopen("data.temp", "w");
    		FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");

    

    fprintf(temp_data, "ADD_arb %lf \n", addtime_arb);
    fprintf(temp_data, "ADD_c %lf \n", addtime_c);
    fprintf(temp_data, "SUB_arb %lf \n", subtime_arb);
    fprintf(temp_data, "SUB_c %lf \n", subtime_c);
    fprintf(temp_data, "PROD_arb  %lf \n", prodtime_arb);
    fprintf(temp_data, "PROD_c  %lf \n", prodtime_c);
    fprintf(temp_data, "QUOT_arb %lf \n", quottime_arb);
    fprintf(temp_data, "QUOT_c %lf \n", quottime_c);
    fprintf(temp_data, "ABS_arb %lf \n", abstime_arb);
    fprintf(temp_data, "ABS_c %lf \n", abstime_c);
    for (int i=0; i < 7; i++)
    {
    fprintf(gnuplotPipe, "%s \n", commands[i]);
    }

    fflush(gnuplotPipe);
	
	return 0;
}