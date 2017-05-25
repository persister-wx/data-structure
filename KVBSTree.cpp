#include"BinarySearchTree1.h"

//使用KV结构模拟一个简单的翻译工具
void Test()
{
	BinarySearchTree<string, string> dict;
	dict.Insert("tree","树");
	dict.Insert("hello","你好");
	BinarySearchTreeNode<string, string>* ret = dict.Find("tree");
	if (ret)
	{
		cout << ret->_value <<endl;
	}
	string tmp;
	while (1)
	{
		cin >> tmp;
		if (dict.Find(tmp))
		{
			cout << dict.Find(tmp)->_value << endl;
		}
	}
}

int main()
{
	Test();
	return 0;
}
