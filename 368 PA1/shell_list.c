#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "shell_list.h"

typedef struct List {
	Node *node;
	struct List *next;
} List;

Node *nodebuilt(long val)
{
	Node *p = malloc(sizeof(Node));
	p->value = val;
	p->next = NULL;

	return p;
}

Node *nodeinsert(Node *a, long val)
{
	Node *p = nodebuilt(val);
	p->next = a;

	return p;
}

Node *List_Load_From_File(char *filename)
{
	FILE *fp;
	long temp = 0;
	int size = 0;
	fp = fopen(filename, "rb");
	if(fp == NULL) return NULL;

	fseek(fp,0,SEEK_END);
	//find the size of the file
	size = ftell(fp);
	fseek(fp,0,SEEK_SET);
	size = size/sizeof(long);


	Node *head = NULL;
	for(int i = 0; i < size; i++)
	{
		fread(&temp, sizeof(long), 1, fp);
		head = nodeinsert(head,temp);
	}
	
	fclose(fp);
	return head;

}

int List_Save_To_File(char *filename, Node *list)
{
	FILE *fp = fopen(filename, "wb");
	int count = 0;

	while(list != NULL)
	{
		count++;
		fwrite(&(list->value), sizeof(long), 1, fp);
		list = list->next;
	}

	fclose(fp);

	return count;
}

void swap_list(Node *head, Node *s1, Node *s2)
{
	//find s1
	Node *s1_prev = NULL;
	Node *s1_p = head;
	while(s1_p != s1)
	{
		s1_prev = s1_p;
		s1_p = s1_p->next;
	}

	//find s2
	Node *s2_prev = NULL;
	Node *s2_p = head;
	while(s2_p != s2)
	{
		s2_prev = s2_p;
		s2_p = s2_p->next;
	}

	//if not head situation
	if(s1_prev != NULL)
	{
		s1_prev->next = s2_p;
	}else
	{
		head = s2_p;
	}

	s2_prev->next = s1_p;

	Node *temp = s2_p->next;
	s2_p->next = s1_p->next;
	s1_p->next = temp;

}

/*void swap_head(Node *head, Node *target, Node *target_pre)
{
	if(head->value > target->value)
	{
		Node *temp = head;
		target_pre->next = head;
		head->next = target->next;
		target->next = temp->next;
	}
}*/

List *listbuilt(Node * val)
{
	List *p = malloc(sizeof(List));
	p->node = val;
	p->next = NULL;

	return p;
}

List *listinsert(List *a, Node * val)
{
	List *p = listbuilt(val);
	p->next = a;

	return p;
}

Node *subarray(Node *orig_head, int gap, int offset)
{
	Node *newHead = NULL;
	Node *p = orig_head;
	int i = 0;

	for(i = 0; i < offset; i++)
	{
		p = p->next;
	}

	while(p != NULL)
	{
		newHead = nodeinsert(newHead, p->value);
		for(i = 0; i < gap; i++)
		{
			p = p->next;
			if(p == NULL) break;
		}
	}
	return newHead;
}

int find_size(Node *list)
{
	Node *temp = list;
	int count = 0;

	while(temp!=NULL)
	{
		count++;
		temp = temp->next;
	}
	return count;
}

void list_bubble_sort(Node *head)
{
	int swapped;
	Node *ptr1;
	Node *lptr = NULL;

	do{
		swapped = 0;
		ptr1 = head;
		while(ptr1->next != lptr)
		{
			if(ptr1->value > ptr1->next->value)
			{
				swap_list(head, ptr1, ptr1->next);
				swapped = 1;
			}
		}
		lptr = ptr1;
	}while(swapped);
}

Node *mergelist(List *oldlist)
{
	Node *finalhead = oldlist->node;
	Node *temphead = oldlist->node;
	//Node *current = finalhead;
	List *listptr = oldlist;
	List *temp = oldlist->next;
	int isend = 1;

	while(isend)
	{
		isend = 0;
		//check if end
		if(temp == oldlist)
		{

			if(temp->node == NULL)
			{
				temp = temp->next;
			}else if(temp->node != NULL)
			{
				temp = temp->next;
				isend = 1;
			}
		}
		while(temp != oldlist)
		{
			if(temp->node == NULL)
			{
				temp = temp->next;
				continue;
			}
			if(temp->node != NULL)
			{
				temp = temp->next;
				isend = 1;
			}
		}
		if(isend == 0) break;
		if(listptr->node == NULL)
		{
			if(listptr->next == NULL) listptr->next = oldlist;
			listptr=listptr->next;
			continue;
		}
		if(listptr->next == NULL) listptr->next = oldlist;

		temphead->next = listptr->next->node;
		temphead = temphead->next;
		listptr->node = listptr->node->next;
		listptr = listptr->next;
	}

	return finalhead;

}

Node *List_Shellsort(Node *list, long *n_comp)
{
	int gap = 1;
	int size = find_size(list);
	int offset = 0;
	//int i = 0;
	Node *head = list;
	List *newlist = malloc(sizeof(List));
	List *listptr = NULL;

	do{
		gap = gap * 3 + 1;
	}while(gap < size);
	//printf("%d", gap);
	gap = (gap - 1) / 3;

	for(; gap >= 1; gap = (gap - 1)/3)
	{
		for(offset = 0; offset < gap; offset++)
		{
			newlist = listinsert(newlist, subarray(head, gap, offset));
		}
		listptr = newlist;
		while(listptr != NULL)
		{
			list_bubble_sort(listptr->node);
			listptr = listptr->next;
		}
		head = mergelist(newlist);
	}

	return head;
}







