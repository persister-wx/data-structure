#include"BinarySearchTree1.h"

void Test()
{
	int array[] = {5,3,4,1,7,8,2,6,0,9,};

	BinarySearchTree<int> tree;
	for (size_t index = 0; index < sizeof(array) / sizeof(int); ++index)
	{
		tree.Insert(array[index]);
	}
	tree.InOrder();
	if (tree.Find(7))
	{
		cout << tree.Find(7)->_key << endl;
	}

	tree.Remove(3);
	tree.Remove(5);
	tree.Remove(4);
	tree.InOrder();
	tree.Remove(1);
	tree.Remove(7);
	tree.Remove(8);
	tree.Remove(2);
	tree.InOrder();
	tree.Remove(0);
	tree.Remove(6);
	tree.InOrder();
	tree.Remove(9);
	tree.InOrder();
	tree.Remove(3);
	tree.InOrder();
	tree.Remove(5);
	tree.Remove(6);

}


void TestR()
{
	int array[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9, };
	BinarySearchTree<int> tree;
	for (size_t index = 0; index < sizeof(array) / sizeof(int); ++index)
	{
		tree.Insert(array[index]);
	}
	tree.InOrder();

	tree.RemoveR(3);
	tree.RemoveR(5);
	tree.RemoveR(4);
	tree.InOrder();
	tree.RemoveR(1);
	tree.RemoveR(7);
	tree.RemoveR(8);
	tree.RemoveR(2);
	tree.InOrder();
	tree.RemoveR(0);
	tree.RemoveR(6);
	tree.InOrder();
	tree.RemoveR(9);
	tree.InOrder();
	tree.RemoveR(3);
	tree.InOrder();
	tree.RemoveR(5);
	tree.RemoveR(6);
}

int main()
{
	//Test();
	TestR();
	return 0;
}
