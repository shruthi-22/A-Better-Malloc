
void *ptr=NULL;
int allocated = 0;
int allotted = 0;

int no_pages(int bytes);
int Mem_Init(int sizeOfRegion);
void *Mem_Alloc(int size);
int Mem_Free(void *ptr);
void *Mem_Check();
int Mem_IsValid(void *p);
int Mem_GetSize(void *p);
