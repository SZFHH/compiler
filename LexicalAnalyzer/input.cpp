#include<stdio.h>
int main()//����һ��ע��
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
