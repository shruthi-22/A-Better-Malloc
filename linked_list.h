#include <string.h>

struct Node {
	int data;
	char str[100];
	struct Node *next;
}*start=NULL,*ptr,*temp;

/*void create(int ele)
{
	void *ptr;
	struct Node *N = (struct Node*) malloc(sizeof(struct Node));
//	struct Node *N = (struct Node*)ptr;
	N->data = ele;
	N->next = NULL;
	strcpy(N->str,"free");
	start = N;
}*/

void ins(int ele)
{
	if(start == NULL)
	{
		 struct Node *N = (struct Node*) malloc(sizeof(struct Node));
 	       	 N->data = ele;
        	 N->next = NULL;
                 strcpy(N->str,"free");
                 start = N;
	}
	else
	{
		ptr = start;
		struct Node *N = (struct Node*) malloc(sizeof(struct Node));
		N->data = ele;
		strcpy(N->str,"free");
		N->next = NULL;
		while(ptr->next!=NULL)
		{
			ptr=ptr->next;
		}
		ptr->next = N;
	}
}

void Display()
{
	ptr = start;
	printf("\n\t Elements in the linked list : ");
	while(ptr != NULL)
	{
		printf("%d&%s ",ptr->data,ptr->str);
		ptr = ptr->next;
	}
}


/*int main()
{

	int element,n,i,j=0;
        printf("\n\t Enter the total number of elements in the linked list : ");
        scanf("%d",&n);
        printf("\n\t Enter the elements of the linked list : ");
 //       scanf("%d",&element);
 //       create(element);
        for(i=0;i<n;i++)
        {
                scanf("%d",&element);
                ins(element);
        }
        printf("\n\t The element of the linked list are : ");
        Display();
}*/
