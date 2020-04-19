#include <stdlib.h>
#include <stdio.h>
struct Node
{
    void* start;	//to point to memory allocated
    int size;
    int status;		//to indicate whether that block is free(0) or allocated(1)
    struct Node* link;
};

struct Node *head = NULL,*head1 = NULL;

struct Node* New()
{
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    temp->start=NULL;
//    temp->size=sz;
    temp->size=0;
    temp->status=0;
    temp->link=NULL;
    return temp;
}

struct Node* insert(void *p,int e)
{
   	struct Node* newNode= New();
	if(head==NULL)  //empty ll
    	{
		newNode -> start = p;	//here, p i the address returned by mmap
		newNode -> status = 1;
		newNode -> size = e;
		head=newNode;
		return head;
	}
	struct Node* temp = head;
	while( temp->link != NULL)
	{
		temp = temp->link;
	}

	newNode -> start = p;
	newNode -> status = 1;
	newNode ->size = e;
	temp -> link = newNode ;
	return head;
}

void traverse(struct Node *head)
{
    struct Node *temp= head;
    printf("\nSize Status\n");
    while(temp!=NULL)
    {
        printf("%p   %d   %d \n", temp->start , temp->size,temp->status);
        temp=temp->link;
    }
}

struct Node* insert_sorted(int sizeRequired)
{
   struct Node *N = New();
   N -> size = sizeRequired; 
   if(head1==NULL)  //empty ll
   {
        head1=N;
        return head1;

   }
   else
   {
	struct Node *temp = head1,*prevNode=NULL;
	while(temp->link != NULL)
	{
		if(temp-> size <= sizeRequired && temp->link->size > sizeRequired)
		{
			N->link = temp->link;
			temp->link = N;
			return head1;
		}
		else if(temp->size > sizeRequired)
		{
			N->link = temp->link;
			head1 = N;
			return head1;
		}
		prevNode = temp;
		temp = temp->link;
	}
	if(temp->link ==NULL)
	{
		if (sizeRequired > temp->size)
		{
			temp->link = N; 
			return head1;
		}
		else
		{
			if(prevNode == NULL)
			{
				N->link = temp;
				head1 = N;
				return head;
			}
			else
			{
				N->link = temp;
				prevNode->link = N;
				return head1;
			}
		}
	}
   }
}


int main()
{
	insert_sorted(10);
	insert_sorted(1);
	insert_sorted(7);
	insert_sorted(3);
	insert_sorted(9); 
	traverse(head1);
}
