#include <iostream>

using namespace std;

template <typename T>
class DynamicArray
{
private:

	T* A;
	int size;
	int length;

	void CheckSize();
	void IncreaseSize();
	void DecreaseSize();

	void Merge(int left, int mid, int rigth);
	bool CheckSort();

	T Binary(int left, int right, T x);
	T Linear(T x);

public:

	DynamicArray();
	DynamicArray(int n);
	DynamicArray(const DynamicArray& arr);

	int GetLength() { return length; }
	int GetSize() { return size; }

	void Display();
	void Append(T n);
	void Insert(int index, T n);
	void Delete(int index);
	T Find(T n);
	int Get(int index);
	void Set(int index, T n);
	T Max();
	T Min();
	void Sort(int first, int last);
	void Reverse();

	DynamicArray Merge(const DynamicArray& arr);
	DynamicArray Union(const DynamicArray& arr);
	DynamicArray Intersection(const DynamicArray& arr);
	DynamicArray Difference(const DynamicArray& arr);

	const DynamicArray& operator=(const DynamicArray& rhs);

	~DynamicArray();
};

int main()
{
	DynamicArray<int> arr1;
	DynamicArray<int> arr2;

	arr1.Append(4);
	arr1.Append(3);
	arr1.Append(2);
	arr1.Append(1);
	arr1.Append(9);
	arr1.Append(8);
	arr1.Append(8);
	arr1.Append(7);
	arr1.Append(6);
	arr1.Append(5);
	arr1.Append(9);

	arr2.Append(1);
	arr2.Append(6);
	arr2.Append(6);
	arr2.Append(8);
	arr2.Append(8);
	arr2.Append(1);
	arr2.Append(0);
	arr2.Append(2);
	arr2.Append(3);
	arr2.Append(4);
	arr2.Append(5);

	arr1.Sort(0, arr1.GetLength() - 1);
	arr2.Sort(0, arr2.GetLength() - 1);

	arr1.Display();
	cout << endl;
	arr2.Display();
	cout << endl;

	DynamicArray<int> arr3 = arr1.Union(arr2);

	arr3.Display();

	return 0;
}

template <typename T>
void DynamicArray<T>::CheckSize()
{
	if (length == size)
		IncreaseSize();
	else if (length < size / 2)
		DecreaseSize();

	return;
}

template <typename T>
void DynamicArray<T>::IncreaseSize()
{
	size = size * 2;
	T* temp = new T[size];

	for (int i = 0; i < length; ++i)
	{
		temp[i] = A[i];
	}

	delete[] A;
	A = temp;
}

template <typename T>
void DynamicArray<T>::DecreaseSize()
{
	size = size / 2;
	T* temp = new T[size];

	for (int i = 0; i < size; ++i)
	{
		temp[i] = A[i];
	}

	delete[] A;
	A = temp;
}

template <typename T>
DynamicArray<T>::DynamicArray()
{
	size = 20;
	length = 0;
	A = new T[size];
}

template <typename T>
DynamicArray<T>::DynamicArray(int n)
{
	size = n;
	length = 0;
	A = new T[size];
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& arr)
{
	size = arr.size;
	length = arr.length;
	A = new T[size];

	for (int i = 0; i < size; ++i)
		A[i] = arr.A[i];
}

template <typename T>
void DynamicArray<T>::Display()
{
	for (int i = 0; i < length; ++i)
		cout << A[i] << " ";
	cout << endl;

	cout << "Number of Items: " << length << endl;
}

template <typename T>
void DynamicArray<T>::Append(T n)
{
	CheckSize();
	A[length++] = n;
}

template <typename T>
void DynamicArray<T>::Insert(int index, T n)
{
	if (index < 0 || index > length - 1)
		return;

	CheckSize();

	for (int i = length; i > index; --i)
	{
		A[i] = A[i - 1];
	}

	A[index] = n;
	length++;
}

template <typename T>
void DynamicArray<T>::Delete(int index)
{
	if (index < 0 || index > length - 1)
		return;

	for (int i = index; i < length - 1; ++i)
	{
		A[i] = A[i + 1];
	}

	length--;
	CheckSize();
}

template <typename T>
T DynamicArray<T>::Find(T n)
{
	int index;

	if (CheckSort())
		index = Binary(0, length - 1, n);
	else
		index = Linear(n);

	return index;
}

template <typename T>
T DynamicArray<T>::Binary(int left, int right, T x)
{
	while (left <= right)
	{
		int mid = right + (right - left) / 2;

		if (A[mid] == x)
			return mid;

		if (x < A[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}

	return -1;
}

template <typename T>
T DynamicArray<T>::Linear(T x)
{
	for (int i = 0; i < length; ++i)
	{
		if (A[i] == x)
			return i;
	}

	return -1;
}

template <typename T>
int DynamicArray<T>::Get(int index)
{
	if (index < 0 || index >= length)
		return;

	return A[index];
}

template <typename T>
void DynamicArray<T>::Set(int index, T n)
{
	if (index < 0 || index >= length)
		return;

	A[index] = n;
}

template <typename T>
T DynamicArray<T>::Max()
{
	if (CheckSort())
		return A[length - 1];
	else
	{
		T max = A[0];

		for (int i = 1; i < length; ++i)
		{
			if (A[i] > max)
				max = A[i];
		}

		return max;
	}
}

template <typename T>
T DynamicArray<T>::Min()
{
	if (CheckSort())
		return A[0];
	else
	{
		T min = A[0];

		for (int i = 1; i < length; ++i)
		{
			if (A[i] < min)
				min = A[i];
		}

		return min;
	}
}

template <typename T>
bool DynamicArray<T>::CheckSort()
{
	for (int i = 0; i < length; ++i)
	{
		if (A[i] > A[i + 1])
			return false;
	}

	return true;
}

template <typename T>
void DynamicArray<T>::Sort(int left, int right)
{
	if (left < right)
	{
		int mid = left + (right - left) / 2;

		Sort(left, mid);
		Sort(mid + 1, right);

		Merge(left, mid, right);
	}
}

template <typename T>
void DynamicArray<T>::Merge(int left, int mid, int right)
{
	int ln, rn;

	ln = mid - left + 1;
	rn = right - mid;

	T* leftArr = new T[ln];
	T* rightArr = new T[rn];

	for (int i = 0; i < ln; ++i)
		leftArr[i] = A[left + i];

	for (int i = 0; i < rn; ++i)
		rightArr[i] = A[mid + 1 + i];

	int i = 0, j = 0, k = left;

	while (i < ln && j < rn)
	{
		if (leftArr[i] < rightArr[j])
			A[k++] = leftArr[i++];
		else
			A[k++] = rightArr[j++];
	}

	while (i < ln)
		A[k++] = leftArr[i++];

	while (j < rn)
		A[k++] = rightArr[j++];

	delete[] leftArr;
	delete[] rightArr;
}

template <typename T>
void DynamicArray<T>::Reverse()
{
	for (int i = 0; i < length / 2; ++i)
	{
		T temp = A[i];
		A[i] = A[length - 1 - i];
		A[length - 1 - i] = temp;
	}
}

template <typename T>
DynamicArray<T> DynamicArray<T>::Merge(const DynamicArray<T>& arr)
{
	DynamicArray<T> N(size + arr.size);

	int i = 0, j = 0;

	while (i < length && j < arr.length)
	{
		if (A[i] < arr.A[j])
			N.Append(A[i++]);
		else
			N.Append(arr.A[j++]);
	}

	while (i < length)
		N.Append(A[i++]);

	while (j < arr.length)
		N.Append(arr.A[j++]);

	return N;
}

template <typename T>
DynamicArray<T> DynamicArray<T>::Union(const DynamicArray<T>& arr)
{
	DynamicArray<T> N(length + arr.length);

	if (CheckSort())
	{
		int i = 0, j = 0;

		while (i < length && j < arr.length)
		{
			if (A[i] < arr.A[j])
				N.Append(A[i++]);
			else if (arr.A[j] < A[i])
				N.Append(arr.A[j++]);
			else
			{
				i++;
				j++;
			}
		}

		while (i < length)
			N.Append(A[i++]);

		while (j < arr.length)
			N.Append(arr.A[j++]);
	}
	else
	{
		for (int i = 0; i < length; ++i)
			N.Append(A[i]);

		for (int i = 0; i < arr.length; ++i)
		{
			bool found = false;

			for (int j = 0; j < N.length; ++j)
			{
				if (arr.A[i] == N.A[j])
					found = true;
			}

			if (!found)
				N.Append(arr.A[i]);
		}
	}

	return N;
}

template <typename T>
DynamicArray<T> DynamicArray<T>::Intersection(const DynamicArray<T>& arr)
{
	DynamicArray<T> N(length + arr.length);

	if (CheckSort())
	{
		int i = 0, j = 0;

		while (i < length && j < arr.length)
		{
			if (A[i] < arr.A[j])
				i++;
			else if (arr.A[j] < A[i])
				j++;
			else
			{
				N.Append(A[i]);
				i++;
				j++;
			}
		}
	}
	else
	{
		DynamicArray<T> copy = arr;

		for (int i = 0; i < length; ++i)
		{
			bool found = false;
			for (int j = 0; j < copy.length; ++i)
			{
				if (A[i] == copy.A[j] && copy.A[j] != -1)
				{
					found = true;
					copy.A[j] = -1;
				}
			}

			if (found)
				N.Append(A[i]);
		}
	}

	return N;
}

template <typename T>
DynamicArray<T> DynamicArray<T>::Difference(const DynamicArray<T>& arr)
{
	DynamicArray<T> N(length + arr.length);

	if (CheckSort())
	{
		int i = 0; int j = 0;

		while (i < length && j < arr.length)
		{
			if (A[i] < arr.A[j])
				N.Append(A[i++]);
			else if (arr.A[j] < A[i])
				j++;
			else
			{
				i++;
				j++;
			}
		}

		while (i < length)
			N.Append(A[i++]);
	}
	else
	{
		for (int i = 0; i < length; ++i)
		{
			int found = false;
			for (int j = 0; j < arr.length; ++j)
			{
				if (A[i] == arr.A[j])
					found = true;
			}

			if (!found)
				N.Append(A[i]);
		}
	}

	return N;
}

template <typename T>
const DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& rhs)
{
	delete[] A;

	size = rhs.size;
	length = rhs.length;
	A = new T[size];

	for (int i = 0; i < length; ++i)
		A[i] = rhs.A[i];
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
	delete[] A;
}