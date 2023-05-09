#include <stdio.h>
#include <stdlib.h>
int allocation[10][10], max[10][10], available[10], work[10], need[10][10], finish[5], seq[10], scnt = 0, nop, nor, req_process, request[10];
void accept()
{
    int i, j;
    printf("\nEnter the Allocation Matrix:\n");
    for (i = 0; i < nop; i++)
    {
        for (j = 0; j < nor; j++)
        {
            printf("\nFor P%d Enter Resources for %c=", i, 65 + j);
            scanf("%d", &allocation[i][j]);
        }
    }
    printf("\nEnter the Max Matrix:\n");
    for (i = 0; i < nop; i++)
    {
        for (j = 0; j < nor; j++)
        {
            printf("\nFor P%d Enter Resources for %c=", i, 65 + j);
            scanf("%d", &max[i][j]);
        }
    }
    printf("\nEnter the Available Matrix:\n");

    for (j = 0; j < nor; j++)
    {
        printf("\nAvailable Resource for %c=", 65 + j);
        scanf("%d", &available[j]);
        work[j] = available[j];
    }
}

void calc_need()
{
    int i, j;
    for (i = 0; i < nop; i++)
    {
        for (j = 0; j < nor; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}
int check_need(int i)
{
    int j;
    for (j = 0; j < nor; j++)
    {
        if (need[i][j] > available[j])
            return 0;
    }
    return 1;
}
int check_request(int i)
{
    int j;
    for (j = 0; j < nor; j++)
    {
        if (need[i][j] > request[j] || available[j] > request[j])
            return 0;
    }
    return 1;
}
void banker()
{
    int cnt = 1, i = 0, j;
    while (cnt <= 2)
    {
        if (finish[i] == 0)
        {
            if (check_need(i))
            {
                finish[i] = 1;
                seq[scnt] = i;
                scnt++;

                for (j = 0; j < nor; j++)
                {
                    available[j] += allocation[i][j];
                }
            }
        }
        i = (i + 1) % nop;

        if (i == 0)
            cnt++;
    }
    if (scnt == nop)
    {
        printf("\nThe System is in Safe State");
        printf("\nSafe Sequence is : ");
        printf("<");
        for (i = 0; i < scnt; i++)
        {
            printf("P%d\t", seq[i]);
        }
        printf(">");
    }
    else
    {
        printf("\nThe System is not in a Safe State");
    }
}
void display()
{
    int i, j;
    printf("Allocation:\n");
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
    printf("Max:\n");
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
    printf("Need:\n");
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
    printf("Available:\n");
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
    printf("1:Accept");
    printf("\n2:Calculate Need");
    printf("\n3:Display");
    printf("\n4:Banker's Algorithm");
    printf("\n5:Read Request\n");
    printf("\n6:Exit\n");
}

void read_request()
{
    int i, j;
    printf("\nEnter the process number for Request");
    scanf("%d", &req_process);
    if (req_process > nop)
    {
        printf("\nError : Invalid Process Number\n");
        return;
    }

    for (j = 0; j < nor; j++)
    {
        printf("Enter request for P%d enter R%d=", req_process, j);
        scanf("%d", &request[j]);
    }

    if (check_request(req_process))
    {
        printf("\nRequest for Process P%d is granted\n", req_process);
        for (j = 0; j < nor; j++)
        {
            available[j] -= request[j];
            allocation[req_process][j] += request[j];
            need[req_process][j] -= request[j];
        }

        for (i = 0; i < 5; i++)
        {
            finish[i] = 0;
        }
        banker();
    }
    else
    {

        printf("\nRequest for Process P%d cannot be granted\n", req_process);
    }
}

int main()
{
    int i, j, opt;
    printf("\nEnter number of Processes: ");
    scanf("%d", &nop);
    printf("\nEnter number of Resources: ");
    scanf("%d", &nor);

    while (1)
    {
        option();
        printf("Enter the option: ");
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
            banker();
            break;
        case 5:
            read_request();
            break;
        case 6:
            exit(0);
        }
    }
}
