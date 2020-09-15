#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char *addlarge(char* num1,char* num2,int lgh,int minus)
{
	char *result = (char*)malloc(lgh+1);
	// printf("%d\n", &result);

	int carry=0;
	for(int m=lgh-2;m>=1;m--)
	{
		if(num1[m]!='.')
		{
			result[m+minus]=(((num1[m]-'0')+(num2[m]-'0')+carry)%10) + '0';
			carry=(((num1[m]-'0')+(num2[m]-'0')+carry)/10);
		}
		else
		{
			result[m+minus]='.';
		}
	}

	result[lgh-1+minus]='\0';
	if(carry==0)
		{	char *e=(char *)malloc(lgh);

			int fgh=1;
			while(fgh<=lgh)
			{
				e[fgh-1]=result[fgh];
				fgh++;
			}
			free(result);	

			result=e;

		}
	else
		result[minus]=carry+'0';
	
	
	if(minus==1)
		result[0]='-';

	//if(minus==1)
	//	printf("%c\n",'-' );
	//printf("%s\n", result);
	
	int ij=0;
	int control=0;
	int dcount=0;
	while(result[ij]!='\0')
	{
		if(control==0)
		{
			if(result[ij]=='.')
				control=1;

		}
		else
		{
			if(dcount==20)
			{
				result[ij]='\0';
				break;
			}
			dcount++;
		}
		ij++;
	}
	
	if(control==1)
	{
		int kj=ij-1;
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
free(num1);
free(num2);
	return result;
}






char* modify_sub(char* result,int minus,int control,int lgh)
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

int checklarger(char *num1,char *num2,int lgh)
{
	for(int m=1;m<lgh-1;m++)
	{
		if(num1[m]!='.'){
		if(num1[m]>num2[m])
			return 1;
		else if(num1[m]<num2[m])
			return 2;
	}
	}
	return 0;
}

char* sublarge(char *num1,char *num2,int lgh)
{
	char *result = (char*)malloc(lgh*sizeof(char));
	int k=checklarger(num1,num2,lgh);
	char *large,*small;
	int minus=0;
	
	if (k==0) {
		free(result);
		free(num1);
		free(num2);
		char* ze=(char *)malloc(2);
		ze[0]='0';
		ze[1]='\0';
		return ze;}
	else if(k==1)
	{
		large=num1;
		small=num2;
	}
	else
	{
		large=num2;
		small=num1;
		minus=1;
	}
	if(k!=0){
	int borrow=0;
	for(int m=lgh-2;m>=1;m--)
	{
		if(large[m]!='.')
		{
			int k1=(large[m]-'0')-borrow;
			int k2=(small[m]-'0');
			if(k1<k2)
			{
				result[m]=(10+k1-k2)+'0';
				borrow=1;
			}
			else
			{
				result[m]=(k1-k2)+'0';
				borrow=0;
			}
		}
		else
			result[m]='.';
	}



	result[0]='0';
	result[lgh-1]='\0';


	int ij=0;
	int control=0;
	int dcount=0;
	while(result[ij]!='\0')
	{
		if(control==0)
		{
			if(result[ij]=='.')
				control=1;

		}
		else
		{
			if(dcount==20)
			{
				result[ij]='\0';
				break;
			}
			dcount++;
		}
		ij++;
	}
	
	// if(minus==1)
	//	printf("%c\n",'-' );
	//printf("%s\n", result);
	free(num1);
	free(num2);

	return modify_sub(result,minus,control,ij);

	
}
}











int processnum(char *ch1)
{
	
	int x=0;
	while(ch1[x]!='\0' && ch1[x]!='.')
	{
			x++;}
	return x;
}



int checkminus(char *ch1)
{
	return (ch1[0]=='-');
}




char *addsublarge(char *num1,char *num2,char *str1)
{
			int l1=0;
			while(num1[l1]!='\0')
				l1++;
			int l2=0;
			while(num2[l2]!='\0')
				l2++;
			int bd1=processnum(num1);
			int bd2=processnum(num2);
			int ad1,ad2;
			int cm1=checkminus(num1);
			int cm2=checkminus(num2);
			bd1=bd1-cm1;
			bd2=bd2-cm2;
			l1=l1-cm1;
			l2=l2-cm2;
			if(l1>(bd1+1))
				ad1=l1-(bd1+1);
			else
				ad1=0;
			if(l2>(bd2+1))
				ad2=l2-(bd2+1);
			else
				ad2=0;
			int bd,ad;
			if(bd1>bd2)
				bd=bd1;
			else 
				bd =bd2;
			if(ad1>ad2)
				ad=ad1;
			else 
				ad=ad2;
			int finall;
			if(ad>0)
				finall=ad+bd+3;
			else
				finall=bd+2;

			char *finalnum1,*finalnum2;
			finalnum1=(char*)malloc(finall*(sizeof(char)));
			finalnum2=(char*)malloc(finall*(sizeof(char)));
			l1=0;
			int ij=0;
			int count=0;
			char ze='0';
			if(cm1==1)
				{finalnum1[ij]='-';
			count=1;}
			else
				finalnum1[ij]='+';
			ij++;
			

			for(;ij<(finall-1);ij++)
			{

				if((ij-1)<(bd-bd1))
					{
					finalnum1[ij]='0';
					}
				else if((ij-1)<bd)
				{

					finalnum1[ij]=num1[l1+count];
					l1++;
				}
				else if((ij-1)==bd)
				{
					finalnum1[ij]='.';
					l1++;
				}
				else if((ij-1)>bd && (ij-1)<=bd+ad1)
				{
					finalnum1[ij]=num1[l1+count];
					l1++;
				}
				else if((ij-1)>(bd+ad1))
					finalnum1[ij]='0';
			}
			finalnum1[ij]='\0';




			l2=0;
			ij=0;
			count=0;
			if(cm2==1)
				{finalnum2[ij]='-';
				count=1;}
			else
				finalnum2[ij]='+';
			ij++;
			for(;ij<(finall-1);ij++)
			{
				if((ij-1)<(bd-bd2))
					finalnum2[ij]='0';
				else if((ij-1)<bd)
				{
					finalnum2[ij]=num2[l2+count];
					l2++;
				}
				else if((ij-1)==bd)
				{
					finalnum2[ij]='.';
					l2++;
				}
				else if((ij-1)>bd && (ij-1)<=bd+ad2)
				{
					finalnum2[ij]=num2[l2+count];
					l2++;
				}
				else if((ij-1)>(bd+ad2))
					 {
						finalnum2[ij]='0';}
			}
			finalnum2[ij]='\0';
			char *result;
			if(strcmp(str1,"ADD")==0)
			{
				if(finalnum1[0]=='+'&&finalnum2[0]=='+')
				return addlarge(finalnum1,finalnum2,finall,0);
				else if(finalnum1[0]=='-'&&finalnum2[0]=='-')
				return addlarge(finalnum1,finalnum2,finall,1);
				else if(finalnum1[0]=='-'&&finalnum2[0]=='+')
				return sublarge(finalnum2,finalnum1,finall);
				else if(finalnum1[0]=='+'&&finalnum2[0]=='-')
				return sublarge(finalnum1,finalnum2,finall);
			}

			else if(strcmp(str1,"SUB")==0)
			{
				if(finalnum1[0]=='+'&&finalnum2[0]=='-')
				return addlarge(finalnum1,finalnum2,finall,0);
				else if(finalnum1[0]=='-'&&finalnum2[0]=='+')
				{return addlarge(finalnum1,finalnum2,finall,1);}
				else if(finalnum1[0]=='+'&&finalnum2[0]=='+')
				return sublarge(finalnum1,finalnum2,finall);
				else if(finalnum1[0]=='-'&&finalnum2[0]=='-')
				return sublarge(finalnum2,finalnum1,finall);
			}

			// printf("%d\n", &result);
			// free(result);
			// printf("jsdhvyc\n");
			// char *faltu=(char*)malloc(2);
			// faltu[0]='-';
			// faltu[1]='\0';
			// return faltu;
}

// int main()
// {
// 	char str1[]={'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','.','9','5','\0'};
// 	char str2[]={'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','.','9','5','\0'};
// 	char *result1=addsublarge(str1,str2,"SUB");
// 	printf("%s\n",result1 );
// 	free(result1);
   
// 	return 0;
// }