#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include "linkedList.h"
#include "main_1.h"

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
	void *w = Mem_Alloc(30);
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
	
	ret = Mem_Free(a);
        if (ret == 0 )
                printf("\n Memory Freed successfully ");
        else if(ret == 1)
                printf("\n No operation occurred ");
        else
                printf("\n Memory is already free ");
	printf("\n\t Total allocated memory :  %d and total allotted : %d unused : %d ",allocated,allotted,allotted - allocated);
	traverse(head);
	traverse(head1);
	printf("\n");
	void *s = Mem_Check();
	traverse(head);
	traverse(head1);

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
	traverse(head1);
}