/* 
 * The C++ code implementing the quicksort algorithm
 */

#include <iostream>
#include <algorithm>

int partition(int* a, int low, int high);

int quickSort(int* a, int low, int high)
{
	int pivotElement;
	if(low < high)
	{
		pivotElement = partition(a, low, high);
		quickSort(a, low, pivotElement-1);
		quickSort(a, pivotElement+1,high);
	}	
	return 0;
}

int partition(int* a, int low, int high)
{
	using namespace std;

	int pivot = a[high];
	int i, j;
	
	i = low;
	for(j=i;j<=high;++j)
	{
		if(a[j]<pivot)
		{
			swap(a[i],a[j]);
			++i;
		}
	}
	swap(a[i],a[high]);
	
	return i;
}

int main()
{
	using namespace std;
	int a[15] = {1,3,7,9,4,6,8,2,0,5,14,13,11,12,10};
	quickSort(a,0,14);
	
	int i;
	for(i=0;i<15;++i)
		cout<<a[i]<<' ';
	cout<<endl;

	return 0;
}
