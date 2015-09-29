/*
 * The C++ code implementing the binary search algorithm
 */

#include <cstdlib>
#include <iostream>

int binarySearch(int* array, int first, int last, int value);

int main()
{
	using namespace std;

	int list[10];
	int i = 0;
	for(i=0;i<10;++i)
		list[i] = 2*i+1;

	cout<<"Binary search results: "<<binarySearch(list, 0, 9, 11)<<endl;
	return 0;
}

int binarySearch(int* array, int first, int last, int search_key)
{
	int index;
	if(array[first] > array[last])
		index = -1;
	else
	{
		int mid = (first+last)/2;
		if(search_key == array[mid])
			index = mid;
		else
			if(search_key < array[mid])
				index = binarySearch(array, first, mid-1, search_key);
			else
				index = binarySearch(array, mid+1, last, search_key);
	}
	
	return index;
}
