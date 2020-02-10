#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "shell_array.h"
#include "shell_list.h"

int main(int argc, char** argv)
{
	if(argc != 4) // error check
	{
		return EXIT_FAILURE;
	}

	
	int count = 0;
	long n_comp = 0;

	

	if(!strcmp(argv[1],"-a"))
	{
		
		long *arr;
		int size;
		arr = Array_Load_From_File(argv[2], &size);

		if(arr == NULL) return EXIT_FAILURE; //fopen failed

		Array_Shellsort(arr, size, &n_comp);
		printf("%ld\n", n_comp);
		count = Array_Save_To_File(argv[3], arr, size);
		if(count != size)
		{
			free(arr);
			return EXIT_FAILURE;
		}
		free(arr);
		//printf("%ld\n", n_comp);
	}



	if(!strcmp(argv[1],"-l"))
	{
		Node *head = List_Load_From_File(argv[2]);
		/*Node *p = head;
		while(p != NULL)  //for debug
		{
			//printf("%d\n", count);
			printf("%ld\n", p->value);
			p = p->next;
			count++;
		}*/

		head = List_Shellsort(head, &n_comp);

		count = List_Save_To_File(argv[3], head);
		printf("%d\n", count);


		


	}


	

	return 0;
}
