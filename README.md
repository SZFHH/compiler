#compiler

#Lexical Analyzer

RE->NFA->DFA->MDFA

#待编译代码
#include<stdio.h>
int main()//这是一条注释
{
	int x,m,n,i,sum=0;
	scanf("%d%d%d",&x,&m,&n);
	sum=sum+x;
	for(i=1;i<n;i++)
	{
		x=x+m;
		sum=sum+x;
	}
	printf("%d",sum);
	return 0;
}

词法分析输出

