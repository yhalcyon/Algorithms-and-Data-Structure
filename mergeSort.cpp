/*
 * The C++ code implementing the merge sort algorithm
 */

#include <iostream>
#include <stdio.h>

int merge(int*a, int low, int high, int mid);


int mergesort(int* a, int low, int high)
{
	int mid;
	if(low<high)
	{
		mid=(low+high)/2;
		mergesort(a,low,mid);
	    mergesort(a,mid+1,high);
	    merge(a,low,high,mid);
	}
	return 0;
}

int merge(int* a, int low, int high, int mid)
{
	int i, j, k, c[100000];
	i = low;
	k = low;
	j = mid+1;

	while(i<=mid && j<=high)
	{
		if(a[i]<a[j])
		{
			c[k] = a[i];
			++k;
			++i;
		}
		else
		{
			c[k] = a[j];
			++k;
			++j;
		}
	}
	
	while(i<=mid)
	{
		c[k] = a[i];
		++k;
		++i;
	}

	while(j<=high)
	{
		c[k] = a[j];
		++k;
		++j;
	}
	for(i=low;i<k;i++)
		a[i] = c[i];

	return 0;
}

int main()
{
	using namespace std;
	
	int a[100000];
	FILE *fp;

	fp = fopen("IntegerArray.txt","r");
	if(fp == NULL)
		{
			cout<<"Cannot find the file!"<<endl;
			fclose(fp);
		}

	int i;
	for(i=0;i<100000;++i)
		{
			fscanf(fp,"%d",&a[i]);
			fseek(fp,1,SEEK_CUR);
		}
	fclose(fp);

	for(i=0;i<10;++i)
		cout<<a[i]<<endl;

	mergesort(a, 0, 100000-1);
	
	for(i=0;i<30;++i)
		cout<<a[i]<<endl;
	
	return 0;
}

