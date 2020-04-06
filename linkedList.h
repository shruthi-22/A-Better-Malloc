struct Node
{
    void* start;	//to point to memory allocated
    int size;
    int status;		//to indicate whether that block is free(0) or allocated(1)
    struct Node* link;
};

struct Node *head = NULL;

struct Node* New(int sz)
{
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    temp->start=NULL;
    temp->size=sz;
    temp->status=0;
    temp->link=NULL;
    return temp;
}

struct Node* insert(void *p,int e)
{
   	struct Node* newNode= New(e);
	if(head==NULL)  //empty ll
    	{
		newNode -> start = p;	//here, p i the address returned by mmap
		newNode -> status = 1;
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

/*
int main()
{
	insert(2);
	insert(4);
	insert(7);
	insert(8);
	insert(9);
	traverse(head);
}

*/
