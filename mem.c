#include <stdio.h>
#include <stdlib.h>                                                                                                                                                                  
#include <unistd.h>                                                                                                                                                                                                     
#include <sys/mman.h>                                                                                                                                                                                              
#include "linkedList.h"                                                                                                                                                                                                                                                                                                                                                                                                               

#define PAGESIZE 4096                                                                                                                                                                                                                                                                                                                                                                                                                 

int no_pages(int bytes)     //when bytes required by a process is passed, no_pages() returns the no. of pages to be allocated for that process.                                                                    
{                                                                                                                                                                                                                      
    if(bytes % getpagesize()==0)                                                                                                                                                                                           
        return bytes/getpagesize();                                                                                                                                                                                    
    else                                                                                                                                                                                                                   
        return bytes/getpagesize()+1;                                                                                                                                                                              
}      
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
int Mem_Init(int sizeOfRegion)                                                                                                                                                                                     
{                                                                                                                                                                                                                          
    if(sizeOfRegion < 0)                                                                                                                                                                                               
    {                                                                                                                                                                                                                          
        printf("size of the Region passed to Mem_Init is negative");                                                                                                                                                       
        return 0;                                                                                                                                                                                                  
    }                                                                                                                                                                                                                  
    int n=no_pages(sizeOfRegion);                                                                                                                                                                                      
    void* ptr = mmap(NULL,n*PAGESIZE,PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);                                                                                                                      
    if(ptr == MAP_FAILED)                                                                                                                                                                                              
    {                                                                                                                                                                                                                          
        printf("Error in mmap");                                                                                                                                                                                           
        return 0;                                                                                                                                                                                                  
    }                                                                                                                                                                                                                  
    //a linked list for that process                                                                                                                                                                                   
    head = (struct Node*)ptr;                                                                                                                                                                                                  
    return 1;                                                                                                                                                                                                  
}                                                                                                                                                                                                                                                                                                                                                                                                                                     

int main()                                                                                                                                                                                                         
{                                                                                                                                                                                                                                                                                                                                                                                                                                    
    if ( Mem_Init(1000) ) //process requests for 1000 bytes                                                                                                                                                            
    {                                                                                                                                                                                                                          
        printf("Mem_Init successful"); 
    }                                                                                                                                                                                                                  
    else                                                                                                                                                                                                               
    {                                                                                                                                                                                                                          
        printf("Mem_Init failed");                                                                                                                                                                                 
    }                                                                                                                                                                                                          
} 
                