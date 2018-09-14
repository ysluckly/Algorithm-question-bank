
【题目】
在与财务相关的应用中，经常会用到人民币金额的大写，比如发票的打印程序。
本题的任务是：从键盘输入一个十亿以内的正整数（int类型），把它转换为人民币金额大写（不考虑用户输入错误的情况）。
比如，用户输入：35201，程序输出：叁万伍仟贰佰零壹
用户输入：30201，程序输出：叁万零贰佰零壹
用户输入：30001，程序输出：叁万零壹
用户输入：31000，程序输出：叁万壹仟
用户输入：120023201，程序输出：壹亿贰仟零贰万叁仟贰佰零壹
用户输入：120020001，程序输出：壹亿贰仟零贰万零壹
用户输入：100000001，程序输出：壹亿零壹
可以看到，在万后满千位，则不加零，否则要补零，但不要出现类似“零零”的情况。
在亿后满千万位，则不加零，否则要补零，但整个“万档”没有数字时，“万”字省去。


【参考代码】
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 9 

//将数组逆序 
void reverseIntArr(int *arr,int n)
{
	int temp = 0;
	for(int i=0;i<n/2;++i)
	{
		temp = arr[i];
		arr[i] = arr[n-1-i];
		arr[n-1-i] = temp;
	} 
}

//汉字字符串逆序
void reverseStr(char *str)
{
	char temp = '\0';
	int len = strlen(str);
	for(int i=0;i<len/2;++i)
	{
		temp = str[i];
		str[i] = str[len-1-i];
		str[len-1-i] = temp;
	}
	for(int i=0;i<len;i+=2) 
	{
		temp = str[i];
		str[i] = str[i+1];
		str[i+1] = temp;
	}
}

//将一个整数的各位分离出来 
int resolve(int n,int *digit)
{
	int temp = n,top = -1;
	while(temp)
	{
		digit[++top] = temp%10;
		temp /= 10;
	}
//	reverse(digit,top+1);
	return top+1;
}

//将分离出来的整数各位转换为对应的汉字大写 
void convert(int *digit,int len)
{
	char num[10][3] = {"零","壹","贰","叁","肆","伍","陆","柒","捌","玖"};
	char unit[9][6] = {"","拾","佰","仟","","拾","佰","仟","亿"};//保持代码的一致性 
	char result[100] = {'\0'};//保存大写结果 
	int zeroCount = 0;//用来记录数字中连续的零的个数 
	for(int i=0;i<len;++i)
	{
		if(i<4)//处理万位以下的各位 
		{
			if(digit[0] == 0)
			{
				for(int j=1;j<4 && j<len;++j)
				{
					if(digit[j] == 0)++i;
					else
					{
						if(digit[i] == 0)++zeroCount; 
						else
						{
							strcat(result,unit[i]);//将单位与数字也应该倒序放置 
							strcat(result,num[digit[i]]);	
							zeroCount = 0;
						} 
						
						if(zeroCount == 1)
						{
							strcat(result,num[0]);
						} 
					}
				}
			} 
			else
			{
				if(digit[i] == 0)++zeroCount; 
				else
				{
					strcat(result,unit[i]);//将单位与数字也应该倒序放置 
					strcat(result,num[digit[i]]);	
					zeroCount = 0;
				} 
				
				if(zeroCount == 1)
				{
					strcat(result,num[0]);
				} 
			}
		}
		else//处理万位及以上各位 
		{
			if(i==4)
			{
				char *wan = "万";
				strcat(result,wan);		
			}
			
			if(digit[4] == 0)
			{
				for(int j=5;j<len;++j)
				{
					if(digit[j] == 0)++i;
					else
					{
						if(digit[i] == 0)++zeroCount; 
						else
						{
							strcat(result,unit[i]);//将单位与数字也应该倒序放置 
							strcat(result,num[digit[i]]);	
							zeroCount = 0;
						} 
						
						if(zeroCount == 1)
						{
							strcat(result,num[0]);
						} 
					}
				}
			}
			else
			{
				if(digit[i] == 0)++zeroCount;
				else
				{
					strcat(result,unit[i]);//将单位与数字也应该倒序放置 
					strcat(result,num[digit[i]]);	
					zeroCount = 0;
				} 
					
				if(zeroCount == 1)
				{
					strcat(result,num[0]);
				} 
			} 
		}
	}
	reverseStr(result);//对处理后的大写串进行逆序处理 
	printf("%s\n",result);
}

int main()
{
	int n,len;
	scanf("%d",&n);
	int digit[N] = {0}; 
	len = resolve(n,digit);
	convert(digit,len);
	return 0;
} 

/*

//将分离出来的整数各位转换为对应的汉字大写 
void convert(int *digit,int len)
{
	char num[10][3] = {"零","壹","贰","叁","肆","伍","陆","柒","捌","玖"};
	char unit[9][6] = {"","拾","佰","仟","","拾","佰","仟","亿"};//保持代码的一致性 
	char result[100] = {'\0'};//保存大写结果 
	int zeroCount = 0;//记录数字中连续出现的零的个数 
	for(int i=0;i<len;++i)
	{
		if(digit[i] == 0)
		{
			zeroCount++;
		}
		else
		{
			strcat(result,num[digit[i]]);//将数字转换为对应大写 
			strcat(result,unit[len-i-1]);//加上该数字的单位 
			zeroCount = 0;//清空连续零的个数 
		}
		//100000000 10000未处理成功 
		if(zeroCount == 1)//连续多个零时只显示一次零 
		{
			if(len-i<5)//表示万位以下加“零”的处理方法 
			{
				int zero = 0;
				for(int z=0;z<3;++z)
				{
					if(digit[len-z-1] == 0)zero++;
				} 
				printf("zero :%d\n",zero);
				if(zero != 3)
				{
					if(digit[len-1]==0)//排除特殊情况，大写中若最后几位连续为零则不用显示 
					{
						if(len-i>1)
							strcat(result,num[0]);
					}
					else
					{
						strcat(result,num[0]);
					}
				}
			}
			else//检测例子140204002   31020
			{
				if(digit[len-5]==0) 
				{
					if(len-i>5)
						strcat(result,num[0]);
				}
				else
				{
					strcat(result,num[0]);
				}
			}
		}	
		
		if(len-i == 5)
		{
			char *wan = "万";
			strcat(result,wan);//检测例子124020200
			zeroCount = 1;
			if(digit[len-4] == 0) 
				strcat(result,num[0]);
		}

	}
	//100200201  102011200
	printf("%s\n",result);
}

*/ 