#include <stdio.h>
#include "HMM.h"
#include <time.h>

int main (void)
{
    void *pointer_saver[100];
    int i ,j=0, size=0;

    for( i = 0 ; i <=  100 ; i++)
    {
        size = rand()%4096+1;

        pointer_saver[i] = HmmAlloc(size);

        if (pointer_saver[i] == NULL)
        {
            printf("malloc returned  NULL at iteration %d\n",i);
            printf("where size where of allocation is : %d\n",size);
            return 1;
        }

    }

    for (i = 0 ; i <= 100 ; i++ )
    {
        j = rand()%100;
        if(pointer_saver[j] != NULL) {
            HmmFree(pointer_saver[j]);
            printf("freed memory at address = %p , with index %d  \n",pointer_saver[j],j);
            pointer_saver[j]=NULL;
        }
    }

}
