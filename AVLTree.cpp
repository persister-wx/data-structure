#include"AVLTree1.h"


int main()
{
	AVLTree<int, int> tree;
	int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		tree.Insert(arr[i],1);
		cout <<arr[i]<< "isBalance?" << tree.IsBalance() << endl;
	}
	tree.InOrder();
	return 0;
}
