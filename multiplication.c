#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* modify_mult(char* result,int minus,int control,int lgh)
{
	if(control==1)
	{
		int kj=lgh-1;
		while(result[kj]!='.')
		{
			if(result[kj]=='0')
				result[kj]='\0';
			else
				break;
			kj--;
		}
		if (result[kj]=='.')
		{
			result[kj]='\0';
		}
	}
	int cnt=0;
	int ijk=0;
	while(result[ijk]!='\0')
	{
		 if(result[ijk]!='0' || (result[ijk]=='0' && result[ijk+1]=='.'))
		 	break;
		cnt++;
		ijk++;
	}


			char *e=(char *)malloc(lgh-cnt+2);
			int fgh=cnt;
			while(fgh<lgh+1)
			{
				e[fgh-cnt+1]=result[fgh];
				fgh++;
				
			}
			free(result);	

			result=e;


	if(minus==1)
		result[0]='-';
	else
		{
			// printf("asyags%s\n",result );
			char *e2=(char *)malloc(lgh-cnt+1);

			int fgh1=1;
			while(fgh1<(lgh-cnt+2))
			{
				e2[fgh1-1]=result[fgh1];
				fgh1++;
			}
			free(result);	

			result=e2;
		}
	return result;
}




void muldigit(char *num1,int minus1,int m1,int digit,char *adder,int shift,int adderlgh)
{
	int i=adderlgh-shift;
	int j=m1-1;
	int carry=0;
	while(j>=minus1)
	{
		if(num1[j]!='.')
		{
			adder[i]=((num1[j]-'0')*digit +carry)%10 + '0';
			carry=((num1[j]-'0')*digit +carry)/10 ;
			i--;
		}
		j--;
	}
	adder[i]=carry+'0';
}




char* mullarge(char *num1,char *num2,int minus1,int minus2,int precision)
{
	int m1=minus1;
	int count1=0;
	while(num1[m1]!='\0')
	{
		if(num1[m1]!='.')
			count1++;
		m1++;
	}

	int m2=minus2;
	int count2=0;
	while(num2[m2]!='\0')
	{
		if(num2[m2]!='.')
			count2++;
		m2++;
	}

	char *result =(char*)malloc((count1+count2+1));
	char *adder =(char*)malloc((count1+count2+1));

	for(int f=0;f<(count1+count2);f++)
	{
		result[f]='0';
		adder[f]='0';
	}

	int adderlgh=count1+count2-1;
	result[count1+count2]='\0';
	adder[count1+count2]='\0';

	int shift=0;
	int counter=m2-1;

	while(counter>=minus2)
	{
		if(num2[counter]!='.')
		{
			int digit=(num2[counter]-'0');
			muldigit(num1,minus1,m1,digit,adder,shift,adderlgh);
			shift++;
		}
		int cra=0;
		for(int f=count1+count2-1;f>=0;f--)
		{	
			int cra1=cra;
			cra=((adder[f]-'0') + (result[f] - '0') + cra1)/10;
			result[f]=((adder[f]-'0') + (result[f] - '0') + cra1)%10 + '0';
			adder[f]='0';
		}
		counter--;
	}
	
	int control1=0;
	int dc1=0;
	int f1=0;
	while(num1[f1]!='\0')
	{
		if(num1[f1]=='.')
			control1=1;
		else if (control1==1)
			dc1++;
		f1++;
	}


	int control2=0;
	int dc2=0;
	int f2=0;
	while(num2[f2]!='\0')
	{
		if(num2[f2]=='.')
			control2=1;
		else if (control2==1)
			dc2++;
		f2++;
	}


	int dc=dc1+dc2;
	int load;
	if(dc>0)
		load=1;
	else
		load=0;

	char *finalresult =(char*)malloc((count1+count2+1+load));
	int starter=count1+count2-1+load;
	int restarter=count1+count2-1;
	int dcountr=0;
	if(load==0)
	{
		while(starter>=0)
		{
		
		finalresult[starter]=result[starter];
		starter--;
		}
		finalresult[count1+count2+load]='\0';
	}
	else
	{

		while(starter>=0)
		{
			if(dcountr==dc)
			{
				finalresult[starter]='.';
				starter--;
			}
			else
			{
				finalresult[starter]=result[restarter];
				starter--;
				restarter--;
			}
			dcountr++;
	}

		finalresult[count1+count2+load]='\0';
	}
	free(result);
	free(adder);
	int minus;
	int finalminus=minus1+minus2;
	if(finalminus==1)
		minus=1;
	else
		minus=0;



	int ij=0;
	int control=0;
	int dcount=0;
	while(finalresult[ij]!='\0')
	{
		if(control==0)
		{
			if(finalresult[ij]=='.')
				control=1;

		}
		else
		{
			if(dcount==precision)
			{
				finalresult[ij]='\0';
				break;
			}
			dcount++;
		}
		ij++;
	}


	//if(finalminus==1)
	//	printf("%c\n", '-');
	// printf(" result %s\n", finalresult);
	return modify_mult(finalresult,minus,control,ij);

}

char* multiply(char* num1,char* num2,int precision)
{
	int minus1=0,minus2=0;
	if(num1[0]=='-')
		minus1=1;
	if(num2[0]=='-')
		minus2=1;	
	return mullarge(num1,num2,minus1,minus2,precision);
}

// int main()
// {
// 	char str1[]={'-','0','.','2','2','\0'};
// 	char str2[]={'9','8','.','9','9','8','\0'};
// 	char *res=multiply(str1,str2,20);
//    printf("%s\n", res);
//    free(res);
// 	return 0;
// }