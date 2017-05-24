#include"Heap1.h"

template<class W>
struct HuffmanTreeNode
{
	HuffmanTreeNode()
	{}
	HuffmanTreeNode(const W& w)
		:_left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _w(w)
	{}

	HuffmanTreeNode<W>* _left;
	HuffmanTreeNode<W>* _right;
	HuffmanTreeNode<W>* _parent;
	W _w;
};

template<class W>
class HuffmanTree
{
	typedef HuffmanTreeNode<W> Node;
	struct CompareNode
	{
		bool operator()(Node* left, Node* right)
		{
			return left->_w < right->_w;//应该使用堆内的权值进行比较
		}
	};

public:
	HuffmanTree()
		:_root(NULL)
	{}
	HuffmanTree(const W* a,size_t n,const W& invalid)
	{	
		Heap<Node*,CompareNode> minHeap;
		for (size_t index = 0; index < n; ++index)
		{
			if (a[index] != invalid)
			{
				minHeap.Push(new Node(a[index]));
			}
		}

		while (minHeap.Size() > 1)
		{
			Node* left = minHeap.Top();
			minHeap.Pop();
			Node* right = minHeap.Top();
			minHeap.Pop();

			Node* parent = new Node(left->_w + right->_w);
			left->_parent = parent;
			right->_parent = parent;
			parent->_left = left;
			parent->_right = right;
			minHeap.Push(parent);
		}
		_root = minHeap.Top();
	}

	Node* GetRoot()
	{
		return _root;
	}

private:
	Node* _root;//根节点的权值为所有叶子节点的权值之和
};
