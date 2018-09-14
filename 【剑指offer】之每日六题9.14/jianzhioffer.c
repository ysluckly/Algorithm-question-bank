/*******************************************************************************************
*                                title:【剑指offer】之每日六题                                   *
*                                date : 2018.9.14                                                         *
*                                By   : Hunter                                                       *
********************************************************************************************/

//1.二维数组的查找
//【题目】在一个二维数组中，每一行每一列都是按照递增的顺序排序,请完成一个函数：输入一个数组和一个数字，判断该数组是否含有该数字
//【分析】从右上角开始每次判断一行或一列，时间复杂度o(m+n),m行数，n列数，空间复杂度o(1)
class Solution
{
public:
	bool Find(vector<vector<int>>array, int target)
	{
		int row = array.size();	  //行数
		int col = array[0].size(); //列数

		if (row == 0) return false;
		if (col == 0) return false;

		int x = 0, y = col - 1;
		while (x < row&&y >= 0)
		{
			if (array[x][y] == target)
				return true;
			else if (arar[x][y] > target)
				++x;
			else
				--y;
		}

		return true;
	}

};

//2.空格替换
//【题目】将一串字符串中的空格替换成为“20%”
//【思路】先根据空格数判断出替换后总共需要的空间，然后用两标记分别指向字符串与最大空间的末端，开始逐字符复制，遇到空格进行替换，时间复杂度o(n);
 
class Solution
{
public:
	void ReplaceSpace(char* str,int length)
	{
		assert(str&&length>0);

		int i = 0;
		int len = 0;  //字符串长度
		int count = 0; //空格个数

		while (str[i]!= '\0')
		{
			len++;
			if (str[i] == ' ')
				count++;
			++i;
		}

		if (0 == count) return; //无空格直接返回
		int newlen = count * 2 + len;
		if (newlen > length)
			return;
		int p1 = len;
		int p2 = newlen;

		while (len < newlen&&len >= 0)
		{
			if (str[p1] == ' ')
			{
				str[p2--] = '%';
				str[p2--] = '0';
				str[p2--] = '2';
			}
			else
			{
				str[p2--] = str[p1];
			}
			p1--;
		}

	}
};

//3.逆序打印单链表
class Solution
{
private:
	typedef struct ListNode
	{
		int value;
		struct ListNode* pNext;
	}ListNode, pListNode;

public:
	//【递归】
	void PrintListTailToHead(ListNode* plist)
	{
		assert(plist);

		if (plist->pNext != NULL)
		{
			PrintListTailToHead(plist->pNext);
		}
		printf("%d  ", plist->value);

	}

	//【非递归】
	void PrintListTailToHead(ListNode* plist)
	{
		//此处是链表结点进栈
		stack<ListNode*> node;

		ListNode* pCur = plist;

		while (pCur)
		{
			node.push(pCur);
			pCur = pCur->pNext;
		}
		while (!node.empty())
		{
			printf("%d  ",node.top()->value);
			node.pop();
		} 

		//此处链表结点值进栈
		/*stack<int> s;

		ListNode* pCur = plist;

		while (pCur)
		{
		s.push(pCur->value);
		pCur = pCur->pNext;
		}
		while (!node.empty())
		{
		printf("%d  ",s.top()) ;
		s.pop();
		}  */

	}

};
//【附加】
//在链表后面加一个结点
void AddNodeToTail(pListNode* pplist, int value)
{
	if (pplist == NULL)
		return;

	ListNode* pNewNode = new ListNode();
	pNewNode->value = value;
	pNewNode->pNext = NULL;

	if (*pplist == NULL)
		*pplist = pNewNode;
	else
	{
		ListNode* pCur = (*pplist);
		while (pCur->pNext)
		{
			pCur = pCur->pNext;
		}
		pCur->pNext = pNewNode;
	}

}
//删除值等于value的结点
void ReMovaValue(pListNode* pplist, int value)
{
	if (pplist == NULL || (*pplist) == NULL)
		return;
	ListNode* pCur = (*pplist);
	ListNode* pPre = NULL;
	while (pCur)
	{			  
		if (pCur->value == value)
		{
			ListNode* pDel = NULL;
			if ((*pplist)->value == value)
			{
				pDel = (*pplist);
				(*pplist) = pDel->pNext;
				free(pDel);
				pDel = NULL;
			}
			else
			{
				pDel = pCur;
				pPre->pNext = pCur->pNext;
				free(pDel);
				pDel = NULL;
			}
			return;
		}
		else
		{
			pPre = pCur;
			pCur = pCur->pNext;
		}

	}
}
//删除值等于value的所有结点
void ReMovaValue(pListNode* pplist, int value)
{
	if (pplist == NULL || (*pplist) == NULL)
		return;
	ListNode* pCur = (*pplist);
	ListNode* pPre = NULL;
	while (pCur)
	{
		if (pCur->value == value)
		{
			 
			if ((*pplist)->value == value)
			{
				(*pplist) = (*pplist)->pNext;
				free(pCur);
				pCur = (*pplist);
			}
			else
			{
				pPre->pNext = pCur->pNext;
				free(pCur);
				pCur = pPre->pNext;
			}
		}
		else
		{
			pPre = pCur;
			pCur = pCur->pNext;
		}

	}
}
//4.重建二叉树 
//【题目】已知某二叉树的前序中序，请重建二叉树
//【分析】先找到中序中的根节点，然后根据二叉树性质递归，时间复杂度o(nlogn),n为节点数
class Solution
{
private:
	typedef struct TreeNode
	{
		int value;
		struct TreeNode* pLeft;
		struct TreeNode* pRight;
	}TreeNode;

public:
	TreeNode* ReBuildBinaryTree(int* pre, int in, int len)
	{
		assert(pre&&in&&len > 0);

		return BuildBinaryTree(pre, pre + len - 1, in, in + len - 1);
	}

	TreeNode* BuildBinaryTree(int* startpre, int* endpre, int* startin, int* endin)
	{
		assert(startpre&&endpre&&startin&&endin);
		//前序遍历第一个是根值
		int rootvalue = startpre[0];

		//创建根节点
		TreeNode* root = new TreeNode();
		root->value = rootvalue;
		root->pLeft = root->pRight = NULL;

		//如果前序与中序都只有一个值，树就只有一个根节点
		if (startpre == endpre)
		{
			if ((startin == endin)&&(*startpre == *startin))
			{
				return root;
			}
			else
			{
				printf("前序与中序个数不否\n");
				return;
			}
		}

		//在中序遍历中找到节点的值
		int* rootIn = startin;

		while ((rootIn <= endin) && (*rootIn != rootvalue))
		{
			++rootIn;
		}
		//如果没找到，终止
		if ((rootIn == endin) && ((*rrotIn) != rootvalue))
		{
			printf("中序未找到根节点\n");
			return;
		}

		//计算中序左子树的长度
		int leftlenin = rootIn - startin;
		//计算前序左子树位置
		int* leftlenpre = startpre + leftlenin;

		//构建左子树
		if (leftlenin > 0)
		{
			root->pLeft = BuildBinaryTree(startpre+1,leftlenpre,startin,rootIn-1);
	
		}
		//构建右子树
		if ((endpre - startpre) > leftlenin)
		{
			root->pRight = BuildBinaryTree(leftlenpre+1,endpre,rootIn+1,endin);
		}

	}							  
};
//5.两个栈实现一个队列
class Queue
{
private:
		Stack<int> s1;
		Stack<int> s2;

public:
	void QueueByTwoStackPosh(int key)
	{

		s1.push(key);
	}
	void QueueByTwoStackPop()
	{
		if (s2.empty())
		{
			whlie(!s1.empty())
			{
				s2.push(s1.top());
				s1.pop();
			}
		}
		s2.pop();
	}
	int QueueByTwoStackFront()
	{
		if (s2.empty())
		{
			whlie(!s1.empty())
			{
				s2.push(s1.top());
				s1.pop();
			}
		}
		return s2.top();


	}

};
//【附加】
//两个队列实行按一个栈

class Solution
{
private:
	Queue <int> q1;
	Queue <int> q2;
public:
	void StackByTwoQueuePush(int key)
	{
		if (q1.empty())
		{
			q2.push(key);
		}
		else
			q1.push(key);

	}
	void StackByTwoQueuePop()
	{
		if (q1.empty())
		{
			while (q2.size() > 1)
			{
				q1.push(q2.top());
				q2.pop();
			}
			q2.pop();
		}
		else if (q2.empty())
		{
			while (q1.size() > 1)
			{
				q2.push(q1.top());
				q1.pop();
			}
			q1.pop();
			 
		}

	}
	int StackByTwoQueueTop()
	{
		if (q1.empty())
		{
			return q2.back();
		}
		else
			return q1.back();

	}
};
