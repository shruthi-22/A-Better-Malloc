#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include "linkedList.h"

int no_pages(int bytes)    //when bytes required by a process is passed, no_pages() returns the no. of pages to be allocated for that process.
{
	 if(bytes % getpagesize()==0)
        	return bytes/getpagesize();
    	else
        	return bytes/getpagesize()+1;

}

/*int bytes_allocated(int bytes)   // returns the total number of bytes allocated
{
	int page_size,size_alloc;

	page_size = getpagesize();

        if((bytes%page_size)!=0)
        {
                size_alloc = bytes - (bytes%page_size) + page_size;
        }
        else
        {
                size_alloc = bytes;
        }
	return size_alloc;
}*/

void *ptr=NULL;
int allocated = 0;
int allotted = 0;

int Mem_Init(int sizeOfRegion)			// function to initialise memory to the process
{
        if(sizeOfRegion < 0)
        {
                printf("size of the Region passed to Mem_Init should be positive");
                return 0;
        }
        int n=no_pages(sizeOfRegion);
	int PAGESIZE = getpagesize();
        ptr = mmap(NULL,n*PAGESIZE,PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        allotted=sizeOfRegion;
        if(ptr == MAP_FAILED)
        {
                printf("Error in mmap");
                return 0;
        }
        return 1;
}

void *Mem_Alloc(int size)		//allocates the desirered amout of memory from the total available
{
	int req=allotted,flag=0;
	if(size > 0)
	{
		if(head==NULL)          //if head is NULL,simply insert
                {
                        insert(ptr,size);
			allocated += size;
                        return head->start;
		}
		else
		{
			if(allocated+size <= allotted)			
			{
				struct Node* temp=head,*prevNode;
				while(temp!=NULL)				// find the best-fit size for the memory asked
				{
					if(temp->status == 0 )
					{
						if(temp->size >= size && temp->size <= req)
						{
							req = temp->size;
				//			printf("\n\t %d",req);
							flag = 1;
						}
					}
					prevNode=temp;
					temp=temp->link;
				}
				if(temp==NULL && flag == 0)           //insert node at last
                                {
					
                                        insert(prevNode->start + prevNode->size, size);
					allocated +=size;
					return (prevNode->start + prevNode->size);
                                }
				else							// if a free memory satisfies the best fit costraint
				{
					struct Node* temp = head;
					while(temp!=NULL)
					{
						if(temp->link->size == req)
						{
							temp->link->start = temp->start + temp->size;
							temp->link->status = 1;
							allocated += temp->link->size;
							return temp->start + temp->size;
						}
						temp = temp->link;
					}
				}
			}
			else
			{
				printf("\n\t Not enough space available");
			}
		}

	}
	else
	{
		printf("\n Bytes requested hould be positive ");
	}
}

int Mem_Free(void *ptr)
{
	struct Node* temp = head;
	while(temp!=NULL)
	{
		if( temp->start <= ptr && temp->link->start > ptr)			//locates the pointer in the list
		{
			if(temp->status != 0)						//checks if the given pointer is allocted
			{
				int s1= (unsigned int*)ptr;
				int s2= (unsigned int*)temp->start;
				int size_free= s1-s2;
				//printf("%d  %u  %u",size_free,ptr,temp->start);
				if(size_free != 0)					//checks if the given pointer points to base addr or intermedite address
				{
					struct Node* N = New();
					temp->size = temp->size - size_free;
					N->size = size_free;
					N->link = temp->link;
					temp->link = N;
					allocated -= size_free;
				}
				else
				{
					temp->start = NULL;
					temp->status = 0;
					allocated -= size_free;
				}
				return 0;
			}
			else
			{
				return -1;
			}
		}
		temp = temp->link;
	}
	return 1;

}

int Mem_IsValid(void *p)
{
	void *last = ptr+allotted;
	if( p >= ptr && p <= last)
	{
		return 1;
	}
	return 0;
}

int Mem_GetSize(void *p)
{
	if ( Mem_IsValid(p) )
	{
		struct Node *temp = head;
		while(temp!=NULL)
		{
			if(temp->start == p)
				return temp->size;
			temp = temp->link;
		}
	}
	else
	{
		return -1;
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
        printf("\n Initial linked list : ");
        traverse(head);
	int ret = Mem_Free(b+18);
	if (ret == 0 )
		printf("\n Memory Freed successfully ");
	else if(ret == 1)
		printf("\n No operation occurred ");
	else 
		printf("\n Memory is already free ");
	printf("\n Freeing 20 linked list : ");
        traverse(head);
	b = Mem_Alloc(18);
	printf("\n Allotting 20 linked list : ");
        traverse(head);
	printf("\n\t Total allocated memory :  %d and total allotted : %d unused : %d ",allocated,allotted,allotted - allocated);
	int valid = Mem_IsValid(f);
	if( valid == 1 )
		printf("\n\t Memory is valid ");
	else
		printf("\n\t Memory is invalid ");
	int size = Mem_GetSize(d);
	if(size == -1)
		printf("\n Not a valid memory ");
	else
		printf("\n Size is : %d ",size);

}
