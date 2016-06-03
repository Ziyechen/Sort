#pragma once

#include <iostream>
#include <assert.h>
using namespace std;

//插入排序
//时间复杂度 Ｏ(Ｎ*Ｎ)
// 2 5 4 9 3 6 8 7 1 0
void InsertSort(int *a, size_t size)
{
	assert(a);

	size_t index = 0;
	while (index < size-1)
	{
		int tmp = a[index + 1];
		int end = index;

		while (end >= 0 && a[end] > tmp)
		{
			a[end + 1] = a[end];
			end--;
		}

		a[end + 1] = tmp;
		index++;
	}
}

//希尔排序
//		gap = size;
//		gap = (gap/3)+1;
void ShellSort(int *a, size_t size)
{
	assert(a);

	int gap = size;
	while (gap > 1)
	{
		gap = gap / 3 + 1;

		for (size_t index = 0; index < size - gap; index++)
		{
			int end = index;
			int tmp = a[end + gap];

			while (end >= 0 && a[end] > tmp)
			{
				a[end + gap] = a[end];
				end -= gap;
			}

			a[end + gap] = tmp;
		}
	}
}

//堆排序
//时间复杂度 Ｏ(Ｎ*lgN)
void AdJustDown(int *a, int parent, size_t size)//向下调整
{
	int child = parent * 2 + 1;

	while (child < size)
	{
		//找出左右孩子中较大的一个
		if (child + 1 < size && a[child + 1] > a[child])
			child++;
		
		if (a[parent] < a[child])
		{
			swap(a[parent], a[child]);

			parent = child;
			child = parent * 2 + 1;
		}
		else
			break;
	}
}
void Heap(int *a, size_t size)
{
	assert(a);

	//建堆
	for (int i = (size - 2) / 2; i >= 0; i--)
	{
		AdJustDown(a, i, size);
	}

	//选出最大的数放到最后一位
	for (size_t j = 0; j < size - 1; j++)
	{
		swap(a[0], a[size - 1 - j]);
		AdJustDown(a, 0, size - 1 - j);
	}
}

//归并排序
//2 5 4 9 3 6 8 7 1 0
void _Merge(int *a, int *tmp, int left1, int right1, int left2, int right2)
{
	assert(a);

	int index = left1;
	while (left1 <= right1 && left2 <= right2)
	{
		if (a[left1] > a[left2])
		{
			tmp[index++] = a[left2++];
		}
		else
		{
			tmp[index++] = a[left1++];
		}
	}

	while (left1 <= right1)
	{
		tmp[index++] = a[left1++];
	}
	while (left2 <= right2)
	{
		tmp[index++] = a[left2++];
	}
}

void _MergeSort(int *a, int *tmp, int left, int right)
{
	assert(a);

	//if (right - left < 13)
	//{
	//	InsertSort(a + left, right - left + 1);
	//}
	//else
	if (left < right)
	{
		int mid = left + (right - left) / 2;
		_MergeSort(a, tmp, left, mid);
		_MergeSort(a, tmp, mid + 1, right);

		_Merge(a, tmp, left, mid, mid + 1, right);

		for (int i = left; i <= right; i++)
			a[i] = tmp[i];
	}
}

void MergeSort(int *a, size_t size)
{
	assert(a);

	int *tmp = new int[size];
	_MergeSort(a, tmp, 0, size - 1);
	delete tmp;
}

void test()
{
	int arr[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	int arr1[] = { 2, 5, 4, 9, 3, 6, 8, 7, 5, 5 };

	size_t size = sizeof(arr1) / sizeof(arr1[0]);

	//插入排序
	//InsertSort(arr, size);
	
	//希尔排序
	//ShellSort(arr, size);

	//堆排序
	//Heap(arr, size);

	//归并排序
	MergeSort(arr1, size);
	//打印数组
	for (size_t i = 0; i < size; i++)
	{
		cout << arr1[i] << " ";
	}
	cout << endl;
}
