#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "shell_array.h"

long *Array_Load_From_File(char *filename, int *size)
{
	FILE *fp;
	long *arr;
	fp = fopen(filename, "rb");
	if(fp == NULL) return NULL;

	fseek(fp,0,SEEK_END);
	//find the size of the file
	*size = ftell(fp);
	fseek(fp,0,SEEK_SET);
	*size = *size/sizeof(long);

	//alloc space for array
	arr = malloc(*size * sizeof(long));
	if(*size == 0)
	{
		fclose(fp);
		return arr;
	}

	fread(arr, sizeof(long), *size, fp);
	//for(int i =0;i<1000;i++)
	//	{printf("%ld\n", arr[i]);}
	fclose(fp);
	return arr;

}

void comp_swap(long *a, long *b, long temp)
{
	//if(*b>*a)
	//{
		//*n_comp++;
		temp = *a;
		*a = *b;
		*b = temp;
	//}
	
}

void Array_Shellsort(long *array, int size, long *n_comp)
{
	int gap = 1;
	int i;
	int j;
	long temp = 0;//this is to reduce run time
	do{
		gap = gap * 3 + 1;
	}while(gap < size);
	//printf("%d", gap);
	gap = (gap - 1) / 3;

	for(; gap >= 1; gap = (gap - 1)/3)
	{
		for(i = gap; i<size; i++)
		{
			for(j = i - gap; j >= 0; j=j-gap)
			{
				if(array[j]<=array[j+gap])//optimize inner loop
				{
					*n_comp = *n_comp + 1;
					break;
				}
				comp_swap(&array[j+gap],&array[j], temp);
			}
		}
	}


}

int Array_Save_To_File(char *filename, long *array, int size)
{
	FILE *fp = fopen(filename, "wb");
	int count = 0;

	for(int indx = 0; indx < size; indx++)
	{
		//printf("%ld\n", array[indx]);
		count++;
		fwrite(&array[indx], sizeof(long), 1, fp);
	}

	fclose(fp);

	return count;
}


