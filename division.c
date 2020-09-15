#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* modify_div(char* result,int minus,int control,int lgh)
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


int chklrgdiv(char *rem,char *divs,int rc,int dc)
{
	int nr=0;
	while(rem[nr]=='0')
		nr++;

	int nd=0;
	while(divs[nd]=='0')
		nd++;

	int tcr=rc-nr;
	int tcd=dc-nd;
	if(tcr>tcd)
		return 1;
	else if(tcr<tcd)
		return 2;
	else
	{
		int i1=nr,i2=nd;
		while(i1<rc)
		{
			if(rem[i1]>divs[i2]) return 1;
			else if(rem[i1]<divs[i2]) return 2;


			i1++;
			i2++;
		}
		return 0;
	}
}

void subtractrd(char *rem,char *divs,int rc,int dc)
{
	int nr=0;
	while(rem[nr]=='0')
		nr++;

	int nd=0;
	while(divs[nd]=='0')
		nd++;

	int tcr=rc-nr;
	int tcd=dc-nd;
		int borrow=0;
		int i1=rc-1,j1=dc-1;
		while(j1>=nd)
		{
			int k1=(rem[i1]-'0')-borrow;
			int k2=(divs[j1]-'0');
			if(k1<k2)
			{
				rem[i1]=(10+k1-k2)+'0';
				borrow=1;
			}
			else
			{
				rem[i1]=(k1-k2)+'0';
				borrow=0;
			}
			i1--;
			j1--;
		}
		if(i1>(nr-1))
			rem[i1]=rem[i1]-borrow;
}



char* divlarge(char *num1,char *num2,int minus1, int minus2)
{
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


	int diffc=dc2;

	char *divd=(char*)malloc(count1+2+diffc);
	char *divs=(char*)malloc(count2+1);
	int l1=minus1;
	int k1=0;
	int kd=diffc;
	while(num1[l1]!='\0')
	{

		if(num1[l1]!='.')
		{divd[k1]=num1[l1];
		}
		else
		{
			if(kd>0)
			{
				if(num1[l1+1]=='\0')
					break;
				else
				{
					divd[k1]=num1[l1+1];
					num1[l1+1]='.';
				}
				kd--;
			}
			else
			{
				if(num1[l1+1]=='\0')
					break;
				divd[k1]=num1[l1];
			}
		}
		k1++;
		l1++;
	}
	while(kd>0)
	{
		divd[k1]='0';
		k1++;
		kd--;
	}
	divd[k1]='\0';
	divd[k1]='\0';
	
	int l2=minus2;
	int k2=0;
	while(num2[l2]!='\0')
	{
		if(num2[l2]!='.')
		{
			divs[k2]=num2[l2];
			k2++;
		}
		l2++;
	}
	divs[k2]='\0';

	int index=0;
	char *quo=(char*)malloc(count1+1+diffc+22);
	char *rem=(char*)malloc(count1+1+diffc+22);
	int pointa=0;
	int pointcnt=0;
	int rind=0,qind=0;
	int qcntrl=0;
	int temp=0;
	while(pointcnt<=21)
	{

		if(divd[index]=='.')
			qcntrl=1;
		else if(divd[index]=='\0')
			{qcntrl=2;
				temp=1;}
		else if(divd[index]!='\0' && divd[index]!='.')
			qcntrl=0;


		if(qcntrl==1)
		{
			quo[qind]='.';
			pointa=1;
			index++;
			qind++;
		}
		else if(qcntrl==2)
		{
			if(pointa==1)
			{
				rem[rind]='0';
				int q=0;
				int ans=0;
				while(q<9)
				{
					if(chklrgdiv(rem,divs,rind+1,count2)==2)
					{	
						break;
					}
					else
					{
						subtractrd(rem,divs,rind+1,count2);
					}
					q++;
				}
				quo[qind]=q+'0';
				rind++;
				pointcnt++;
				qind++;
				int zecn=0;
			int hn=0;
			while(hn<rind)
			{
				if (rem[hn]!='0')
				{
					zecn=1;
				}
				hn++;
			}
			if(zecn==0 && temp !=0)
				break;
			}
			else
			{
				quo[qind]='.';
				pointa=1;
				qind++;
			}
		}

		else if(qcntrl==0)
		{
			rem[rind]=divd[index];
			int q=0;
			int ans=0;
			while(q<9)
			{
				if(chklrgdiv(rem,divs,rind+1,count2)==2)
				{	

					break;
				}
				else
				{
					subtractrd(rem,divs,rind+1,count2);
				}
				q++;
			}
			quo[qind]=q+'0';
			rind++;
			index++;
			qind++;
			if(pointa==1)
				pointcnt++;

			int zecn=0;
			int hn=0;
			while(hn<rind)
			{
				if (rem[hn]!='0' )
				{
					zecn=1;
				}
				hn++;
			}
			if(zecn==0&&temp!=0)
				break;
		}


	}
	free(divs);
	free(divd);
	free(rem);
	quo[qind]='\0';
int minus;
int finalminus=minus1+minus2;
	if(finalminus==1)
		minus=1;
	else
		minus=0;



	int ij=0;
	int control1234=0;
	int dcount=0;
	while(quo[ij]!='\0')
	{
		if(control1234==0)
		{
			if(quo[ij]=='.')
				control1234=1;

		}
		else
		{
			if(dcount==20)
			{
				quo[ij]='\0';
				break;
			}
			dcount++;
		}
		ij++;
	}



return modify_div(quo,minus,control1234,ij);
}




char* quot(char* num1,char* num2)
{
	int minus1=0,minus2=0;
	if(num1[0]=='-')
		minus1=1;
	if(num2[0]=='-')
		minus2=1;	
	return divlarge(num1,num2,minus1,minus2);
}

// int main()
// {
// 	char str1[]={'1','8','\0'};
// 	char str2[]={'2','5','\0'};
// 	char *res=quot(str1,str2);
//    printf("%s\n", res);
//    free(res);
// 	return 0;
// }