#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <assert.h>
using namespace std;

template<class K>
struct BinarySearchTreeNode
{
	BinarySearchTreeNode()
	:_left(NULL)
	, _right(NULL)
	{}
	BinarySearchTreeNode(const K& key)
		:_key(key)
		, _left(NULL)
		, _right(NULL)
	{}
	BinarySearchTreeNode<K>* _left;
	BinarySearchTreeNode<K>* _right;
	K _key;
};


template<class K>
class BinarySearchTree
{
	typedef BinarySearchTreeNode<K> Node;
public:
	BinarySearchTree()
		:_root(NULL)
	{}
	BinarySearchTree(Node* node)
		:_root(node)
	{}

	//递归查找
	Node* FindR(const K& key)
	{
		return _FindR(_root, key);
	}

	//递归插入
	bool InsertR(const K& key)
	{
		return _InsertR(, _root, key);
	}

	bool Insert(const K& key)
	{
		if (NULL == _root)
		{
			_root = new Node(key);
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (key > cur->_key)//需要向右子树查找
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (key < cur->_key)//需要向左子树查找
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
	  		}
		}
		//注意：需要判断cur是parent的左孩子还是右孩子
		if (key > parent->_key)
		{
			parent->_right = new Node(key);
		}
		else
		{
			parent->_left = new Node(key);
		}
		return true;
	}

	const Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else
			{
				return cur;
			}
		}
		return NULL;
	}

	bool Remove(const K& key)
	{
		Node* cur = _root;
		Node* parent = NULL;
		Node* del = NULL;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				//1.cur的左为空
				if (NULL == cur->_left)
				{
					del = cur;
					if (NULL == parent)//当此时的cur为根节点
					{
						_root = cur->_right;
					}
					else if (parent->_left == cur)//cur为parent的左孩子
					{
						parent->_left = cur->_right;
					}
					else //cur为parent的右孩子
					{
						parent->_right = cur->_right;
					}
				}//2.cur的右为空
				else if (NULL == cur->_right)
				{
					del = cur;
					if (NULL == parent)
					{
						_root = cur->_left;
					}
					else if (parent->_left == cur)
					{
						parent->_left = cur->_left;
					}
					else
					{
						parent->_right = cur->_left;
					}
				}//3.cur的左右都不为空（替换法删除）
				else
				{
					//①找右子树的最左节点并删除
					Node* subRight = cur->_right;
					Node* parent = cur;//注意这里的parent不能是NULL(如果右子树的最左节点是根节点循环进去)
					while (subRight->_left)
					{
						parent = subRight;
						subRight = subRight->_left;
					}
					del = subRight;//需要删除的节点
					cur->_key = subRight->_key;
					//还需判断subRight是parent的左节点还是右节点
					if (parent->_left == subRight)
					{
						parent->_left = subRight->_right;
					}
					else
					{
						parent->_right = subRight->_right;
					}

				}
				delete del;
				return true;
			}
		}
		return false;
	}

	bool RemoveR(const K& key)
	{
		return _RemoveR(_root, key);
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	~BinarySearchTree()
	{
		_destory(_root);
	}
private:
	bool _RemoveR(Node*& root, const K& key)
	{
		if (NULL == root)
		{
			return false;
		}
		if (root->_key < key)
		{
			return _RemoveR(root->_right, key);
		}
		else if (root->_key > key)
		{
			return _RemoveR(root->_left, key);
		}
		else
		{
			Node* del = root;
			//1.root的左节点为空
			if (NULL == root->_left)
			{
				root = root->_right;
				delete del;
			}//2.root的右节点为空
			else if (NULL == root->_right)
			{
				root = root->_left;
				delete del;
			}
			else
			{
				//3.root的左右节点都不为空
				Node* left = root->_right;
				//方法①：
				//Node* parent = root;
				//while (left->_left)
				//{
				//	parent = left;
				//	left = left->_left;
				//}
				//del = left;
				//root->_key = left->_key;//替换法删除
				//
				//if (left == parent->_left)
				//{
				//	parent->_left = left->_right;
				//}
				//else
				//{
				//	parent->_right = left->_right;
				//}
				//delete del;

				//方法②:
				while (left->_left)
				{
					left = left->_left;
				}
				root->_key = left->_key;
				_RemoveR(root->_right, left->_key);
			}
		}
	}

	bool _InsertR(Node*& root, const K& key)
	{
		if (NULL == root)
		{
			root = new Node(key);
			return true;
		}
		if (root->_key > key)
		{
			return _Insert(root->_left, key);
		}
		else if (root->_key < key)
		{
			return _Insert(root->_right, key);
		}
		else
		{
			return false;
		}
	}

	Node* _FindR(Node* root, const K& key)
	{
		if (NULL == root)
		{
			return NULL;
		}
		if (root->_key > key)
		{
			return _FindR(root->_left, key);
		}
		else if (root->_key < key)
		{
			return _FindR(root->_right, key);
		}
		else
		{
			return root;
		}
	}

	void _destory(Node* root)
	{
		if (NULL == root)
		{
			return;
		}
		_destory(root->_left);
		_destory(root->_right);
		delete root;
	}

	void _InOrder(Node* root)
	{
		if (NULL == root)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

	Node* _root;
};








