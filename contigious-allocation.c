#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ENTRY (struct info *)malloc(sizeof(struct info))
// structure to store information of each file : filename,start block no,totalblocks required

struct info
{
    char filename[20];
    int start, length;
    struct info *next;
};
struct info *E = NULL, *lastentry = NULL;
int *D = NULL;
int dsize;    // total no. of blocks available on the disk
int used = 0; // used no. of blocks

// initialize the total disk space to 0
void initialize_disk()
{
    int i;
    D = (int *)malloc(sizeof(int) * dsize);
    for (i = 0; i < dsize; i++)
    {
        D[i] = 0;
    }
}

// search if the contiguous blocks are available for a file
// D[i]=0 free block
// D[i]=1 allocated block
int search(int length)
{
    int i, j, flag = 1, blknum;
    for (i = 0; i < dsize; i++)
    {
        if (D[i] == 0) // get the first free block in the total disk space
        {
            flag = 1;
            for (blknum = i, j = 0; j < length; j++) // from first fre block search for total required blocks are free or not
            {
                if (D[blknum++] == 0)
                    continue;
                else
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1) // return the first free block number
                return i;
        }
    }
    return -1;
}

// allocate if the contiguous blocks are available
void allocate()
{
    char filename[15];
    int length, blknum, i;
    struct info *t;
    printf("\nEnter file name : ");
    scanf("%s", filename);
    printf("\n Enter the length of file  :");
    scanf("%d", &length);
    if (length <= dsize - used) // check length of file is less than available
    {
        blknum = search(length); // blknum stores first free block number
    }
    else
    {
        blknum = -1;
    }
    if (blknum == -1)
    {
        printf("\nDisk space is not available for the file\n");
    }
    else
    {
        printf("\nDisk space is allocated for the first file\n");
        // allocate total blocks required to the file from blknum
        for (i = 0; i < length; i++)
        {
            D[blknum] = 1;
            blknum++;
        }
        used = used + length; // update the value of used blocks
        t = ENTRY;            // create a new block to store the details of the file
        strcpy(t->filename, filename);
        t->start = blknum;
        t->length = length;
        t->next = NULL;
        if (E == NULL)
        {
            E = lastentry = t;
        }
        else
        {
            lastentry->next = t;
            lastentry = lastentry->next;
        }
    }
    // display the space allocated and free on the disk
    for (i = 0; i < dsize; i++)
    {
        printf("%d", D[i]);
    }
}

// deallocate the blocks allocated by delete file by assigning D[i]=0
void deallocate()
{
    struct info *f, *s;
    char filename[10];
    int start, length, i, blknum, flag = 0;
    printf("\nEnter Filename to be deleted= ");
    scanf("%s", filename);
    // get the block where file details are stored
    for (s = E; s != NULL; s = s->next)
    {
        if (strcmp(s->filename, filename) == 0) // if file name matches
        {
            flag = 1;
            start = s->start;                            // get the starting block number
            length = s->length;                          // get the total number of blocks allocatedfor the file
            for (blknum = start, i = 0; i < length; i++) // free all allocated blocks
            {
                D[blknum++] = 0;
            }
            // display details of disk
            for (i = 0; i < dsize; i++)
            {
                printf("%d", D[i]);
            }
            if (s == E) // if s is the first block in the list
            {
                E = E->next;
                free(s);              // free the block allocated to store the information of the file
                used = used - length; // update the disk space
                break;
            }
            else
            {
                for (f = E; f->next != s; f = f->next) // move the next pointer unless we get block s
                {
                    f->next = s->next;
                    free(s);
                    used = used - length;
                    break;
                }
            }
        }
        if (flag == 0)
        {
            printf("\nInvalid filename given to delete\n");
        }
    }
}

// display the details of the total blocks allocated
void display()
{
    struct info *t;
    printf("\nFilename\tStart Block No.\tTotal Size\n");
    for (t = E; t != NULL; t = t->next)
    {
        printf("%s\t%d\t%d\n", t->filename, t->start, t->length);
    }
    printf("\nUsed Blocks:%d", used);
    printf("\nFree Blocks:%d", dsize - used);
}

void option()
{
    printf("\n1.Allocate Blocks for new File\n");
    printf("2.Deallocate Blocks used by Deleted File\n");
    printf("3.Display used and free blocks on disk\n");
    printf("4.Display bit vector\n");
    printf("5.exit");
}

void show_bitvector()
{
    int i;
    for (i = 0; i < dsize; i++)
        printf("%d ", D[i]);
    printf("\n");
}

int main()
{
    int opt;
    printf("\nEnter the total number of Block Size: ");
    scanf("%d", &dsize);
    initialize_disk();
    while (1)
    {
        option();
        printf("\nEnter the option: ");
        scanf("%d", &opt);
        switch (opt)
        {
        case 1:
            allocate();
            break;
        case 2:
            deallocate();
            break;
        case 3:
            display();
            break;
        case 4:
            show_bitvector();
            break;
        case 5:
            exit(0);
        }
    }
}
