#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <assert.h>
using namespace std;
#include<string>

template<class K,class V>
struct BinarySearchTreeNode
{
	BinarySearchTreeNode()
	:_left(NULL)
	, _right(NULL)
	{}
	BinarySearchTreeNode(const K& key,const V& value)
		:_key(key)
		, _left(NULL)
		, _right(NULL)
		, _value(value)
	{}
	BinarySearchTreeNode<K,V>* _left;
	BinarySearchTreeNode<K,V>* _right;
	K _key;
	V _value;
};

template<class K,class V>
class BinarySearchTree
{
	typedef BinarySearchTreeNode<K,V> Node;
public:
	BinarySearchTree()
		:_root(NULL)
	{}
	BinarySearchTree(Node* node)
		:_root(node)
	{}


	bool Insert(const K& key,const V& value)
	{
		if (NULL == _root)
		{
			_root = new Node(key,value);
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
			parent->_right = new Node(key,value);
		}
		else
		{
			parent->_left = new Node(key,value);
		}
		return true;
	}

	 Node* Find(const K& key)
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
