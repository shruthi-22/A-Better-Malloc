#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include "linkedList.h"


void *ptr=NULL;
int allocated = 0;
int allotted = 0;

int no_pages(int bytes)    //when bytes required by a process is passed, no_pages() returns the no. of pages to be allocated for that process.
{
         if(bytes % getpagesize()==0)
        return bytes/getpagesize();
    else
        return bytes/getpagesize()+1;

}

int Mem_Init(int sizeOfRegion)                  // function to initialise memory to the process
{
    if(sizeOfRegion < 0)
    {
        printf("Size of the Region passed to Mem_Init should be positive");
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

void *Mem_Alloc(int size)               //allocates the desirered amout of memory from the total available
{
	int req=allotted,flag=0;

	if(size > 0)
	{
		if(head==NULL)          //checks if any part of initialised memory is allocated
        	{
			insert(ptr,size);
			allocated += size;
            		return head->start;
		}


		else
		{
			if(allocated+size <= allotted)		//Space might be available
			{
				struct Node* temp=head,*prevNode;
				while(temp!=NULL)				// find the best-fit size for the memory asked
				{
					if(temp->status == 0 )		//if that area is free
					{
						if(temp->size >= size && temp->size <= req)
						{
							req = temp->size;
							flag = 1;
						}
					}
					prevNode=temp;
					temp=temp->link;
				}

				if(temp==NULL && flag == 0)           //insert node at last
                		{
					if ( size <= (allotted - allocated))
					{
						struct Node* temp = head;
						int size1;

						while(temp!=NULL)
						{
							printf("pass");
							size1 = 0;

							if(temp->status == 0)
							{
								printf("\n\t  %p",temp->start);
								struct Node* temp1 = temp,*prev1;
								while(temp1->status == 0 && temp1!=NULL)
								{
									size1 += temp1->size;
									prev1 = temp1;
									if(size1 >= size)
                                                                                break;
									temp1 = temp1->link;
								}
								if (size1 >= size)
								{
									temp->link = prev1->link;
									temp->size = size;
									temp->status = 1;
									allocated += size;
									return temp->start;
								}
							}
							temp = temp->link;
						}
					}

				        if (prevNode->start + prevNode->size + size <= head->start+allotted)
					{
						insert(prevNode->start + prevNode->size, size);
						allocated +=size;
						return (prevNode->start + prevNode->size);
					}

					else
					{
						printf("\n Not enough space available ");
						return NULL;
					}
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
				return NULL;
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
		if( temp->start <= ptr && temp->start + temp->size > ptr)			//locates the pointer in the list
		{
			if(temp->status != 0)						//checks if the given pointer is allocted
			{
				int s1= (unsigned int*)ptr;
				int s2= (unsigned int*)temp->start;
				int size_free= s1-s2;
				//printf("%d  %u  %u",size_free,ptr,temp->start);
				if(size_free != 0)					//checks if the given pointer points to base addr or intermedite address
				{
					struct Node* N = New(0);
					temp->size = temp->size - size_free;
					N->size = size_free;
					N->link = temp->link;
					temp->link = N;
					allocated -= size_free;
				}
				else
				{
					//temp->start = NULL;	//
					temp->status = 0;
					allocated -= temp->size;
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
	struct Node* temp=head;
	while(temp != NULL)
	{
		if ( p >= temp->start && p < temp->start + temp->size )
			break;
		temp = temp->link;
	}
	if(temp==NULL)
	{
		printf("\n\nInvalid pointer passed");
		return -1;
	}
	if(temp->status==1)
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
		return -1;
}


int main()
{
        if ( Mem_Init(100) ) //process requests for 1000 bytes
        {
                printf("\nMem_Init successful\n");
        }
        else
        {
                printf("\nMem_Init failed\n");
                return 1;
        }
	
	void *a = Mem_Alloc(30);
	void *f = Mem_Alloc(10);
	void *b = Mem_Alloc(30);
	void *c = Mem_Alloc(10);
	printf("\n\t Total allocated memory :  %d and total allotted : %d unused : %d ",allocated,allotted,allotted - allocated);

	traverse(head);
	printf("\n");

	int ret = Mem_Free(c);
        if (ret == 0 )
                printf("\n Memory Freed successfully ");
        else if(ret == 1)
                printf("\n No operation occurred ");
        else
                printf("\n Memory is already free ");

	traverse(head);
	printf("\n");

	ret = Mem_Free(b);
        if (ret == 0 )
                printf("\n Memory Freed successfully ");
        else if(ret == 1)
                printf("\n No operation occurred ");
        else
                printf("\n Memory is already free ");

        traverse(head);
        printf("\n");


	void *d = Mem_Alloc(40);
	traverse(head);

	int valid = Mem_IsValid(f+200);
	if( valid == 1 )
		printf("\n\t Memory is valid ");
	else
		printf("\n\t Memory is invalid ");

	int k=Mem_Free(f+198);
	printf("Freed");
	void *g;
	int size = Mem_GetSize(g);
	if(size == -1)
		printf("\n Not a valid memory ");
	else
		printf("\n Size is : %d ",size);

}
