#include <stdio.h>
#include <string.h>
#include <stdlib.h>



char* modify_multsq(char* result,int minus,int control,int lgh)
{
	// if(control==1)
	// {
	// 	int kj=lgh-1;
	// 	while(result[kj]!='.')
	// 	{
	// 		if(result[kj]=='0')
	// 			result[kj]='\0';
	// 		else
	// 			break;
	// 		kj--;
	// 	}
	// 	if (result[kj]=='.')
	// 	{
	// 		result[kj]='\0';
	// 	}
	// }
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

char* modify_sqrt(char* result,int minus,int control,int lgh)
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



void muldigitsq(char *num1,int minus1,int m1,int digit,char *adder,int shift,int adderlgh)
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




char* mullargesq(char *num1,char *num2,int minus1,int minus2)
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
			muldigitsq(num1,minus1,m1,digit,adder,shift,adderlgh);
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
			if(dcount==41)
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
	return modify_multsq(finalresult,minus,control,ij);

}



//--------------------------------------------------------Multiplication----------------------------------------------------------------------


















int finaldecision(char *num1,char *num2)
{

	int ld1=0,sd1=0,ij1=0;
	int control1=0;
	while(num1[ij1]!='.')
	{
		if(num1[ij1]!='0' && control1==0)
		{
			control1=1;
			sd1=ij1;
		}
		ij1++;
	}
	ld1=ij1;

	int ld2=0,sd2=0,ij2=0;
	int control2=0;
	while(num2[ij2]!='.')
	{
		if(num2[ij1]!='0' && control2==0)
		{
			control2=1;
			sd2=ij2;
		}
		ij2++;
	}
	ld2=ij2;


	

	if((ld1-sd1)>(ld2-sd2))
		return 1;
	else if((ld1-sd1)<(ld2-sd2))
		return 2;
	else
	{
		ij1=sd1;
		ij2=sd2;
		while(ij1<ld1)
		{
			if(num1[ij1]>num2[ij2])
				return 1;
			else if(num1[ij1]<num2[ij2])
				return 2;
			ij1++;
			ij2++;
		}

		int k=1;
		while(k<=41)
		{
			if(num1[ld1+k]>num2[ld2+k])
				return 1;
			else if(num1[ld1+k]<num2[ld2+k])
				return 2;
			k++;
		}
		return 0;
	}
}














int chklh(char *num1,char *num2,int bd)
{
	// int ij=0;
	// while(ij<=(bd+20))
	// {
	// 	if(num1[ij]!=num2[ij])
	// 		return 0;
	// 	ij++;
	// }
	// return 1;


int borrow=0;
	if(num1[bd+21]<num2[bd+21])
		borrow=1;
	int result=0;
// printf("%s n2  %s\n", num1,num2);
	for(int m=(bd+20);m>=0;m--)
	{
		if(num1[m]!='.')
		{
			int k1=(num1[m]-'0')-borrow;
			int k2=(num2[m]-'0');
			// printf("%d k2 %d\n", k1,k2);
			if(k1<k2)
			{
				result=(10+k1-k2);
				borrow=1;
			}
			else
			{
				result=(k1-k2);
				borrow=0;
			}
			// printf("rr%d\n", result);
			if(result!=0)
			return 0;
			
		}
		

	}
	return 1;



}

char *addhalfl(char* num1, char* num2,char *num3,int lgh)
{
	char *half1=(char*)malloc(lgh);
	char *half2=(char*)malloc(lgh);
	int ij=0;
	int carry1=0;
	int carry2=0;
	while(num1[ij]!='\0')
	{
		if(num1[ij]=='.')
		{
			half1[ij]='.';
			half2[ij]='.';
		}
		else
		{
			half1[ij]=(((num1[ij]-'0')+10*carry1)/2) + '0';
			carry1=((num1[ij]-'0')+10*carry1)%2;

			half2[ij]=(((num2[ij]-'0')+10*carry2)/2) + '0';
			carry2=((num2[ij]-'0')+10*carry2)%2;
		}
		ij++;
	}
	half1[ij]='\0';
	half2[ij]='\0';
	int carry=0;
	ij=lgh-2;
	while(ij>=0)
	{
		if(half1[ij]!='.')
		{
			num3[ij]=((half1[ij] - '0')+(half2[ij] - '0')+carry)%10 +'0';
			carry=((half1[ij] - '0')+(half2[ij] - '0')+carry)/10;
		}
		else
			num3[ij]='.';
		ij--;
	}
	num3[lgh-1]='\0';
	free(half1);
	free(half2);
}


int chklarge(char *num1,char *num2)
{
	int ij=0;
	while(num1[ij]!='\0')
	{
		if(num1[ij]>num2[ij]) return 1;
		else if(num1[ij]<num2[ij]) return 2;
		ij++;
	}
	return 0;
}


char* sqrtlarge(char *num)
{
	int control=0;
	int dc=0;
	int bd=0;
	int ij=0;
	while(num[ij]!='\0')
	{
		if(num[ij]=='.')
			control=1;
		else if(control==0)
			bd++;
		else if (control==1)
			dc++;

		ij++;
	}
	char *a=(char*)malloc(bd+43);
	// printf("only %d\n", bd+43);
	control=0;
	ij=0;
	while(ij<(bd+42))
	{
		// printf("%d\n", ij);
		if(ij==bd)
			a[ij]='.';
		else if(ij>=(bd+dc+1))
			a[ij]='0';
		else
			a[ij]=num[ij];
		ij++;
		
	}
	a[bd+42]='\0';
	//printf("%s\n", a);


	
	char *one=(char*)malloc(bd+43);
	ij=0;
	while(ij<(bd+42))
	{
		if(ij==bd)
			one[ij]='.';
		else if(ij==(bd-1))
			one[ij]='1';
		else
			one[ij]='0';
		ij++;
	}
	one[bd+42]='\0';
	// printf("%s\n", one);

	int k=chklarge(a,one);
	

	if(k==0)
		{char* on=(char *)malloc(2);
		on[0]='1';
		on[1]='\0';
		free(a);
		free(one);
		return on;
		}
	else
	{
		char *low=(char*)malloc(bd+23);
		char *high=(char*)malloc(bd+23);
		if(k==1)
		{
			int ijk=0;
			while(ijk<(bd+22))
			{
				low[ijk]=one[ijk];
				high[ijk]=a[ijk];
				ijk++;
			}
			low[ijk]='\0';
			high[ijk]='\0';
		}
		else
		{
			int ijk=0;
			while(ijk<(bd+22))
			{
				high[ijk]=one[ijk];
				low[ijk]=a[ijk];
				ijk++;
			}
			low[ijk]='\0';
			high[ijk]='\0';
		}
		char *hlh=(char *)(malloc(bd+23));
		while(1)
		{
				int chker=chklh(high,low,bd);
				addhalfl(high,low,hlh,(bd+23));
				//printf("half %s\n", hlh);
				if(chker==1){
				int ij1234=0;
				int control1234=0;
				int dcount1234=0;
				while(hlh[ij1234]!='\0')
				{
					if(control1234==0)
					{
						if(hlh[ij1234]=='.')
							control1234=1;

					}
					else
					{
						if(dcount1234==20)
						{
							hlh[ij1234]='\0';
							break;
						}
						dcount1234++;
					}
					ij1234++;
				}
				free(a);
				free(one);
				free(low);
				free(high);
				return modify_sqrt(hlh,0,control1234,ij1234);

				}
				else
				{
					char *hlhsq=mullargesq(hlh,hlh,0,0);
					int chka=finaldecision(hlhsq,a);
					//printf("halfsq %s once %d\n", hlhsq,chka);

					if(chka==0)
						{
						int ij1234=0;
						int control1234=0;
						int dcount1234=0;
						while(hlh[ij1234]!='\0')
						{
							if(control1234==0)
							{
								if(hlh[ij1234]=='.')
									control1234=1;

							}
							else
							{
								if(dcount1234==20)
								{
									hlh[ij1234]='\0';
									break;
								}
								dcount1234++;
							}
							ij1234++;
				}

				free(a);
				free(one);
				free(low);
				free(high);

				return modify_sqrt(hlh,0,control1234,ij1234);
						}
					else if(chka==1)
					{
						int ijk0=0;
						while(hlh[ijk0]!='\0')
						{
							high[ijk0]=hlh[ijk0];
							ijk0++;
						}
					}
					else
					{
						int ijk0=0;
						while(hlh[ijk0]!='\0')
						{
							low[ijk0]=hlh[ijk0];
							ijk0++;
						}
					}

					//printf("high%s low%s \n", high,low);
					// printf("reacherd\n");
					free(hlhsq);
					// printf("again reacherd\n");
				}
		}


	}






}
// int main()
// {
// 	char str1[]={'1','2','3','4','5','6','7','8','9','0','8','7','6','5','4','3','4','5','6','7','7','6','5','4','5','6','7','8','9','0','9','8','7','6','5','4','5','6','7','8','9','0','9','8','7','2','6','5','2','3','5','1','2','3','7','9','8','1','2','3','5','1','2','7','8','3','5','1','8','2','5','3','8','7','1','2','6','7','8','1','2','9','6','1','2','9','6','7','8','3','2','7','0','1','8','2','7','3','8','1','7','2','9','3','6','1','8','5','3','1','7','8','5','4','7','8','6','1','4','9','8','6','7','3','1','9','7','8','4','9','8','2','3','7','1','9','\0'};
// 	char *res=sqrtlarge(str1);
//    	printf("%s\n", res);
//    	free(res);
// 	return 0;
// }