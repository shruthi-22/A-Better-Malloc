struct Node 
{
    int start;
    int end;
    struct Node* link;
};

struct Node *head = NULL;

struct Node* New(int s,int e)
{
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    temp->start=s;
    temp->end=e;
    temp->link=NULL;
    return temp;
}

struct Node* insert(int s,int e)
{
    struct Node* newNode= New(s,e);
    if(head==NULL)  //empty ll
    {
        head = newNode;
        return head;
    }

    if(head->link==NULL)        //only one node in ll
    {
        if (newNode->start < head->start)
        {
            newNode->link=head;
            head=newNode;
        }
        else
        {
            head->link=newNode;
        }
        return head;
    }

    if(newNode->start < head->start) //if smaller number than head arrives
    {
        newNode->link=head;
        head=newNode;
        return newNode;
    }
    struct Node *temp = head;
    
    while( temp->link != NULL )
    {
        if((newNode->start > temp->start) && (temp->link->start > newNode->start))
        {
            newNode->link=temp->link;
            temp->link=newNode;
            return newNode;
        }
        temp = temp->link;
    }
    temp->link = newNode;
    return newNode;
}

void traverse(struct Node *head)
{
    struct Node *temp= head;
    while(temp!=NULL)
    {
        printf("%d %d \n",temp->start,temp->end);
        temp=temp->link;
    }
}
