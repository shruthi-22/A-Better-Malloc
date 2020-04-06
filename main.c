#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <sys/mman.h>
#include "linkedList.h"

#define PAGESIZE 4096

int allotted = 0;
int allocated =0 ;
int no_pages(int bytes)     //when bytes required by a process is passed, no_pages() returns the no. of pages to be allocated for that process.
{
    if(bytes % getpagesize()==0)
        return bytes/getpagesize();
    else
        return bytes/getpagesize()+1;
}

void *ptr=NULL;

int Mem_Init(int sizeOfRegion)
{
	if(sizeOfRegion < 0)
	{
		printf("size of the Region passed to Mem_Init should be positive");
		return 0;
	}
	int n=no_pages(sizeOfRegion);
	ptr = mmap(NULL,n*PAGESIZE,PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	allotted=sizeOfRegion;
	if(ptr == MAP_FAILED)
	{
		printf("Error in mmap");
		return 0;
    	}
	return 1;
}
//address not correct
//allocation within range
void *Mem_Alloc(int size)
{
	if(size > 0)
	{
		if(head==NULL)		//if head is NULL,simply insert
		{
			insert(ptr,size);
			return (void*)head;
		}
		else			//if head is not null, implement best fit, do ptr arithmetic
		{
			int bestfit=-1;
			struct Node *nextNode=head,*prevNode;
			if(allocated + size <= allotted)	//space might be available
			{
				struct Node* ptr=head;
				while(ptr!=NULL)		//traverse full list
				{
					if(ptr->status==0)	//if free
					{
						if(ptr->size >= size )
						{
							if(ptr->size==size)	//best fit
							{
								ptr ->status=1;
								printf("\n ALLOCATED ");
								return (void *)ptr;
							}
							//if ptr->size > size
						}
					}
					prevNode=ptr;
					ptr=ptr->link;
				}
				if(ptr==NULL)		//insert node at last
				{

					insert(prevNode->start + prevNode->size, size);
				}
			}
			else
			{
				printf("Not enough space available");
			}
		}
	}
	else
	{
		printf("Bytes requested should be positive");
	}
}

int main()
{
	if ( Mem_Init(1000) ) //process requests for 1000 bytes
	{
		printf("\nMem_Init successful\n");
	}
	else
	{
		printf("\nMem_Init failed\n");
		return 1;
	}

	void *a = Mem_Alloc(100);
        void *b = Mem_Alloc(20);
        void *c = Mem_Alloc(40);
        void *d = Mem_Alloc(50);
	void *e = Mem_Alloc(70);
        void *f = Mem_Alloc(200);
	printf("Initial linked list : ");
	traverse(head);
	//free 20 and 50
	struct Node* N=head;
	while(N!=NULL)
	{
		if(N->size==20 || N->size==50)
			N->status=0;
		N=N->link;
	}
	printf("\n\nlinked list after 20 and 50 freed : ");
        traverse(head);

	Mem_Alloc(20);
	printf("\n\nlinked list after 18 allocated : ");
        traverse(head);
}
