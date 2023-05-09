#include <stdio.h>
#include <stdlib.h>
int allocation[10][10], max[10][10], available[10], work[10], need[10][10], finish[5], seq[10], nor, nop, request[10];
void accept()
{
    int i, j;
    printf("\n Enter the Allocation Matrix:\n");
    for (i = 0; i < nop; i++)
    {
        for (j = 0; j < nor; j++)
        {
            printf("\nFor P %d enter resource for %c =", i, 65 + j);
            scanf("%d", &allocation[i][j]);
        }
    }
    printf("\nEnter the MAX Matrix :");
    for (i = 0; i < nop; i++)
    {
        for (j = 0; j < nor; j++)
        {
            printf("\nFor P %d enter Max for %c =", i, 65 + j);
            scanf("%d", &max[i][j]);
        }
    }
    printf("\nEnter the Available Matrix:");

    for (i = 0; i < nor; i++)
    {
        printf("\nEnter available for %c =", 65 + i);
        scanf("%d", &available[i]);
        work[i] = available[i];
    }
}

void calc_need()
{
    int i, j;
    for (i = 0; i < nop; i++)
    {
        for (j = 0; j < nop; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

void display()
{
    int i, j;
    printf("\nAllocation :\n");
    printf("\t");
    for (j = 0; j < nor; j++)
    {
        printf("R%d\t", j);
    }
    for (i = 0; i < nop; i++)
    {
        printf("\nP%d\t", i);
        for (j = 0; j < nor; j++)
        {
            printf("%d\t", allocation[i][j]);
        }
        printf("\n");
    }
    printf("MAX :\n");
    printf("\t");
    for (j = 0; j < nor; j++)
    {
        printf("R%d\t", j);
    }

    for (i = 0; i < nop; i++)
    {
        printf("\nP%d\t", i);
        for (j = 0; j < nor; j++)
        {
            printf("%d\t", max[i][j]);
        }
        printf("\n");
    }
    printf("Need :\n");
    printf("\t");
    for (j = 0; j < nor; j++)
    {
        printf("R%d\t", j);
    }
    for (i = 0; i < nop; i++)
    {
        printf("\nP%d\t", i);
        for (j = 0; j < nor; j++)
        {
            printf("%d\t", need[i][j]);
        }
        printf("\n");
    }
    printf("Available :\n");

    for (j = 0; j < nor; j++)
    {
        printf("R%d\t", j);
    }
    printf("\n");
    for (j = 0; j < nor; j++)
    {
        printf("%d\t", available[j]);
    }
    printf("\n");
}
void option()
{
    printf("1 :Accept\n");
    printf("2 :Calculate Need\n");
    printf("3 :Dispaly\n");
    printf("4 :Exit\n");
}
int main()
{
    int i, j, opt;
    printf("\nEnter the number of process :");
    scanf("%d", &nop);
    printf("Enter the numebr of resources :");
    scanf("%d", &nor);

    while (1)
    {
        option();
        printf("Enter the option :");
        scanf("%d", &opt);
        switch (opt)
        {
        case 1:
            accept();
            break;
        case 2:
            calc_need();
            break;
        case 3:
            display();
            break;
        case 4:
            exit(0);
        }
    }
}
