
/*******************************************************************************************
*                                title:【剑指offer】之每日六题								*
*                                date : 2018.9.15                                           *
*                                By   : Hunter												*
********************************************************************************************/
//1.公司年龄排序
//【分析】利用辅助空间计算出每个年龄段的人数，然后重置原年龄数组

void AgeSort(int* age,int len)
{
	assert(age&&len>0);
	const int oldAge = 100;
	int ageTmp[oldAge+1];
	memset(ageTmp,0,sizeof(ageTmp));

	for (int i = 0; i < len; ++i)
	{
		if (age[i]<0 || age[i]>oldAge)
		{
			printf("年龄有误\n");
			exit(1);
		}
		++ageTmp[age[i]];
	}

	int index = 0;
	for (int i = 0; i <= oldAge; ++i)
	{
		for (int j = 0; j < ageTmp[i]; ++j)
		{
			age[index] = i;
			index++;

		}
	}

}
//2.旋转数组中最小数字
//【题目】例如{3,4,5,1,2}是{1,2,3,4,5}的一个旋转，求返回值为1
//【分析】把一个数组中最开始的几个元素搬到数组尾部，我们称之为数组的旋转，
//首先我们将数组数组遍历就可以找到最小数字，复杂度为o（n），没有利用旋转数组的特性，显然是不符合要求的，
// 所以选用二分方法，p1，p2分别指向首尾，判断中间与之的关系，特例只能顺序查找

int Min(int* number, int len)
{
	assert(number&&len>0);
	int p1 = 0;
	int p2 = len - 1;
	int mid = p1;
	while (number[p1] >= number[p2])
	{
		if (p2 - p1 == 1)
		{
			mid = p2;
			break;
		}
		mid = p1 + ((p2 - p1) >> 1);
		//如果p1,p2,mid对应三个数相等，则采用顺序查找
		if (number[p1] == number[p2]
			&& number[p2] == number[mid])
			return OrderSearch(number, p1,p2);
		if (number[mid] >= number[p1])
			p1 = mid;
		else if (number[mid] <= number[p2])
			p2 = mid;

	}
	return number[mid];
}

int OrderSearch(int* number, int p1, int p2)
{
	int result = number[p1];
	for (int i = p1 + 1; i <= p2; ++i)
	{
		if (number[i] < result)
		{
			result = number[i];
		}

	}
	return result;
}

//3.斐波那契数列
//递归：效率低下

long long fib(size_t n)
{
	return n < 2 ? n : (fib(n - 1) + fib(n - 2));
}
//尾递归
long long fib(long long first, long long second, size_t n)
{
	if (n < 2)
		return n;
	if (n == 2)
		return 1;
	return fib(second, first + second, n - 1);
}


//迭代
long long fib(size_t n)
{
	/*if (n < 2)
		return n;
	int fibone = 0;
	int fibtwo = 1;
	int fib = 0;
	for (size_t i = 2; i <= n; ++i)
	{
		fib = fibone + fibtwo;
		fibone = fibtwo;
		fibtwo = fib;

	}*/
	if (n == 0)
		return 0;
	int fib = 0;
	int tmp = 1;
	for (size_t i = 1; i <= n; ++i)
	{
		fib += tmp;
		tmp = fib - tmp;
	}
	return fib;
}
//最佳解法：o(nlogn)解法（矩阵乘法加快速幂即可）；

//应用1：小矩形覆盖矩形

//应用2：青蛙跳台阶变形1：青蛙可以跳一节，可以跳两节，求该青蛙到n总共跳法
//解法同斐波那契数列；

//应用3：青蛙跳台接变形2：青蛙可以跳一节，也可以跳两节或n节，求到n接总共跳法
//数学归纳法为 2^(n-1),即f(n) = f(n-1)+f(n-2)...+f（1）+1,为了更好服从递推，令f(0) = 1;
//则有：	f(n) = f(n-1)+f(n-2)...+f（1）+f(0);
long long fib(size_t n)
{	 
	if (n == 0)
		return 0;
	int fib = 0;
	int tmp = 1;
	for (size_t i = 1; i <= n; ++i)
	{
		fib += tmp;
		tmp = fib;
	}
	return fib;
}

//4.一个数二进制中1的个数
int NumberOf1(int n)
{
	int count = 0;
	for (int i = 0; i < 32; ++i)
	{
		if (((1 << i)&n) == 1)
			count++;
	}
	return count;
}
//优化
//对于一个数按位与这个数减一，所得结果会将这个数的最右边的一置为零，也就是每操作一次，1的个数减1
int NumberOf1(int n)
{
	int count = 0;
	while (n)
	{
		count++;
		n = n&(n - 1);
	}
	return count;
}

//链表
class Solution
{
private:
	typedef struct ListNode
	{
		int value;
		struct ListNode* pNext;
	}ListNode;
	
public:
	//5.O(1)删除链表节点
	void DeleteNode(ListNode** pplist, ListNode* pos)
	{
		assert(pplist && (*pplist) && pos)

		//非尾结点
		if (pos->pNext != NULL)
		{
			ListNode* pDel = pos->pNext;
			pos->value = pDel->value;
			pos->pNext = pDel->pNext;
			free(pDel);
			pDel = NULL;
		}
		//尾节点
		//1.仅有一个结点
		else if ((*pplist) == pos)
		{
			free((*pplist));
			(*pplist) == NULL;
			pos = NULL;
		}
		//2.多个节点
		else
		{
			ListNode* pDel = (*pplist);
			while (pDel->pNext != pos)
			{
				pDel = pDel->pNext;
			}
			pDel->pNext = NULL;
			free(pos);
			pos = NULL;
		}
	}

	//6.链表中第k个节点
	ListNode* FindKthNode(ListNode* plist, size_t k)
	{
		assert(plist);
		ListNode* pFast = plist;
		ListNode* pSlow = plist;
		while (k--)	 //while(--k)
		{
			pFast = pFast->pNext;
			//如果k>链表长度，退出
			if (pFast == NULL)
				return NULL;
		}

		while (pFast) //while(pFast->pNext)
		{
			pFast = pFast->pNext;
			pSlow = pSlow->pNext;
		}
		return pSlow;
	}

};
