#pragma once

#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;

//快速排序
//时间复杂度 Ｏ(Ｎ*lgN)
//2 5 4 9 3 6 8 7 1 0

//三数取中法
int TakeAFewFrench(int *a, int left, int right)
{
	assert(a);

	int mid = left + (right - left) / 2;

	//如果左边小于中间
	if (a[left] < a[mid])
	{
		//中间小于右边 && 左边小于中间
		if (a[mid] < a[right])
			return mid;
		//中间大于右边 && 左边小于中间 && 左边小于右边
		else if (a[left] < a[right])
			return right;
		else
			return left;
	}
	else
	{
		// && a[mid] <= a[left]
		if (a[left] < a[right])
			return left;
		// && a[mid] <= a[left] && a[left] >= a[right]
		else if (a[mid] < a[right])
			return right;
		else
			return mid;
	}
}

int PartSort(int *a, int left, int right)//单趟排序
{
	assert(a);

	//三数取中法
	int num = TakeAFewFrench(a, left, right);
	swap(a[num], a[right]);
	
	//找到key在数组中的位置
	int key = a[right];
	int begin = left;
	int end = right - 1;

	while (begin < end)
	{
		while (begin < end && a[begin] <= key)
		{
			begin++;
		}
		while (begin < end && a[end] >= key)
		{
			end--;
		}

		if (begin < end)
			swap(a[begin], a[end]);
	}

	if (a[begin] > a[right])
	{
		swap(a[begin], a[right]);
		return begin;
	}
	else
		return right;
}

//挖坑法
int PartSort1(int *a, int left, int right)
{
	assert(a);

	//三数取中法
	int num = TakeAFewFrench(a, left, right);
	swap(a[num], a[right]);

	int key = a[right];
	while (left < right)
	{
		while (left < right && a[left] <= key)
			++left;
		if (left < right)
			a[right--] = a[left];

		while (left < right && a[right] >= key)
			--right;
		if (left < right)
			a[left++] = a[right];
	}

	a[left] = key;
	return left;
}

//
int PartSort2(int *a, int left, int right)
{
	assert(a);

	//三数取中法
	int num = TakeAFewFrench(a, left, right);
	swap(a[num], a[right]);

	int key = a[right];
	int prev = left - 1;
	int cur = left;

	while (cur < right)
	{
		if (a[cur] < key && ++prev != cur)
			swap(a[prev], a[cur]);

		++cur;
	}

	swap(a[++prev], a[right]);
	return prev;
}

//void QuickSort(int *a, int left, int right)
//{
//	assert(a);
//	if (left >= right)
//		return;
//
//	int div = PartSort2(a, left, right);
//	QuickSort(a, left, div - 1);
//	QuickSort(a, div + 1, right);
//}

//非递归
void QuickSort(int *a, int left, int right)
{
	assert(a);

	stack<int> s;

	if (left < right)
	{
		s.push(right);
		s.push(left);
	}

	while (!s.empty())
	{
		left = s.top();
		s.pop();
		right = s.top();
		s.pop();

		//if (right - left < 13)
		//{
		//	InsertSort(a + left, right - left + 1);
		//}
		//else
		{
			int div = PartSort2(a, left, right);
			if (left < div - 1)
			{
				s.push(div - 1);
				s.push(left);
			}
			if (right > div + 1)
			{
				s.push(right);
				s.push(div + 1);
			}
		}
	}
}

void TestQuickSort()
{
	int arr[] = { 2, 5, 4, 9, 3, 6, 8, 7, 5, 5 };

	//快速排序
	QuickSort(arr, 0, 9);

	//打印数组
	for (size_t i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}
