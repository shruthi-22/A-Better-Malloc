#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include "linked_list.h"

int Mem_Init(int sizeofRegion);
void* Mem_Alloc(int size);

int main()
{
	int size_need,map;
        printf("\n\t Enter the size needed : ");
        scanf("%d",&size_need);
        map = Mem_Init(size_need);
        if(map == -1)
        {
                printf("\n\t. Memory allocation failed .");
        }
        else
        {
                printf("\n\t Memory allocation successful .");
        }

}

int Mem_Init(int sizeofRegion)
{
	int size_alloc,page_size,num_of_pages;

        page_size = getpagesize();

        if((sizeofRegion%page_size)!=0)
        {
                size_alloc = sizeofRegion - (sizeofRegion%page_size) + page_size;
        }
        else
        {
                size_alloc = sizeofRegion;
        }
	num_of_pages = size_alloc/page_size;
        char *ptr = mmap(NULL,size_alloc,PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE , 0 , 0);
        if(ptr == MAP_FAILED)
        {
                perror("mmap() failed");
                return -1;
        }

        printf("\n\t Address allocated %d ",size_alloc);

	int i = 1;
//	create(page_size);
	while(i<=num_of_pages)
	{
		ins(page_size);
		i = i+1;
	}
	Display();
	return 0;


}
