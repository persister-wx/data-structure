#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <assert.h>
using namespace std;
#include<vector>
#include< algorithm>
#include<string>


template<class T>
struct Less
{
	bool operator()(T& left, T& right)
	{
		return left < right;
	}
};

template<class T>
struct Greater
{
	bool operator()(T& left, T& right)
	{
		return left > right;
	}
};

template<class T, class Compare = Greater<T> >
class Heap
{
public:
	Heap()
	{}

	Heap(const T* a, size_t n)
	{
		_v.reserve(n);//可以提高效率
		for (size_t i = 0; i < n; ++i)
		{
			_v.push_back(a[i]);
		}

		//建堆
		for (int i = ((int)_v.size() - 2) >> 1; i >= 0; --i)
		{
			AjustDown(i);
		}
	}

	void Push(const T& data)
	{
		_v.push_back(data);
		AdjustUp(_v.size() - 1);
	}

	void Pop()
	{
		//1。先将堆顶元素与堆的最后一个元素交换
		swap(_v[0], _v[_v.size() - 1]);
		//2.删除掉最后一个节点
		_v.pop_back();
		//3.向下调整
		AjustDown(0);
	}

	T& Top()
	{
		return _v[0];
	}

	size_t Size()
	{
		return _v.size();
	}

protected:
	//向上调整算法
	void AdjustUp(int index)
	{
		int child = index;
		int parent = (child - 1) >> 1;
		while (child > 0)
		{
			if (Compare()(_v[parent], _v[child]))
			{
				break;
			}
			else
			{
				swap(_v[child], _v[parent]);
				child = parent;
				parent = (child - 1) >> 1;
			}
		}

	}

	//向下调整
	void AjustDown(int root)
	{
		int parent = root;
		int child = parent * 2 + 1;//默认是左孩子
		while (child < _v.size())
		{
			if (child + 1 < _v.size() && Compare()(_v[child + 1], _v[child]))
			{
				child++;//保证child是最大的孩子节点
			}
			if (Compare()(_v[child], _v[parent]))
			{
				swap(_v[child], _v[parent]);//交换父节点和孩子节点
				parent = child;
				child = parent * 2 + 1;
			}
			else//不用交换：说明已经是最大的堆了
			{
				break;
			}
		}
	}

private:
	vector<T> _v;
};
