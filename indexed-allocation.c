#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bit_vec[20][20], pos, available, n;

struct file
{
    char file_name[20];
    int index, length;
} f[20];

void create_new_file()
{
    int i, count = 0;
    printf("\nEnter the name of the file :- ");
    scanf("%s", f[pos].file_name);
    printf("\nEnter the length of the file :- ");
    scanf("%d", &f[pos].length);

    if (f[pos].length < available)
    {
        for (i = 0; i < n; i++)
        {
            if (bit_vec[i][0] == 0)
            {
                bit_vec[i][0] = -1;
                available--;
                f[pos].index = i;
                break;
            }
        }
        i = 1;
        while (i <= f[pos].length)
        {
            if (bit_vec[count][0] == 0)
            {
                bit_vec[count][0] = 1;
                bit_vec[f[pos].index][i] = count;
                i++;
                if (i > f[pos].length)
                {
                    available -= f[pos].length;
                    printf("File is created successfully :)\n");
                    pos++;
                }
            }
            count++;
        }
    }
    else
    {
        printf("File cannot be stored :( \n");
    }
}

void show_directory()
{
    int i, j;

    if (pos == 0)
    {
        printf("\nDirectory is empty :(\n");
    }
    else
    {
        printf("\n------Directory------");
        for (i = 0; i < pos; i++)
        {
            printf("\nFile name: %s\tFile Index: %d\tFile Length : %d\n", f[i].file_name, f[i].index, f[i].length);
            printf("File %s is stored at indicies : \n ", f[i].file_name);
            for (j = 1; j <= f[i].length; j++)
            {
                printf("%d -> %d\n", j, bit_vec[f[i].index][j]);
            }
        }
        printf("\n");
    }
}
void delete_file()
{

    int i, position, flag = 0;
    if (pos == 0)
    {
        printf("\nDirectory is empty :(\n");
    }
    else
    {
        char file[20];
        printf("\nEnter the file name :- ");
        scanf("%s", file);

        for (i = 0; i < pos; i++)
        {
            if (strcmp(file, f[i].file_name) == 0)
            {
                position = i;
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            printf("File not found :(");
            return;
        }
        int j = f[position].index;
        int k = 1;
        while (k <= f[position].length)
        {
            int index = bit_vec[j][k];
            bit_vec[j][k] = 0;
            bit_vec[index][0] = 0;
            k++;
        }
        bit_vec[f[position].index][0] = 0;
        available += (f[position].length + 1);
        for (i = position; i < pos; i++)
        {
            f[i] = f[i + 1];
        }
        pos--;
        printf("%s deleted Successfully \n", file);
    }
}

void main()
{
    int choice, i;
    pos = 0;
    printf("enter the total number of blocks");
    scanf("%d", &n);
    available = n;
    for (i = 0; i < n; i++)
    {
        bit_vec[i][0] = 0;
    }
    while (1)
    {
        printf("\n\tMenu\n");
        printf("\n 1) Show Bit Vector \n 2) Create New File \n 3) Show Directory \n 4) Delete File \n5) Exit ");
        printf("\n Enter Your Choice :- ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            for (i = 0; i < n; i++)
            {
                printf("%d\t", bit_vec[i][0]);
            }
            break;
        case 2:
            create_new_file();
            break;
        case 3:
            show_directory();
            break;
        case 4:
            delete_file();
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("\n Invalid Choice :( \n");
        }
    }
}
