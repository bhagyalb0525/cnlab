#include<stdio.h>
struct router{
    int distance[100];
    int via[100];
};

int main()
{
    struct router routing_table[100];
    int nodes;
    int cost_matrix[20][20];
    int minimum;
    printf("enter no.of nodes\n");
    scanf("%d",&nodes);

    printf("enter cost matrix:\n");
    int i,j,k;
    for(i=0;i<nodes;i++)
    {
        for(j=0;j<nodes;j++)
        {
            scanf("%d",&cost_matrix[i][j]);
            routing_table[i].distance[j]=cost_matrix[i][j];
            routing_table[i].via[j]=j;
        }
    }
    for(i=0;i<nodes;i++)
    {
        for(j=0;j<nodes;j++)
        {
            for(k=0;k<nodes;k++)
            {
                minimum=cost_matrix[i][k]+routing_table[k].distance[j];
                if(routing_table[i].distance[j]>minimum){
                    routing_table[i].distance[j]=minimum;
                    routing_table[i].via[j]=k;
                }
            }
        }
    }
    for(i=0;i<nodes;i++)
    {
        printf("for router %d\n",i+1);
        for(j=0;j<nodes;j++){
            printf("to node %d via %d distance %d\n",j+1,routing_table[i].via[j]+1,routing_table[i].distance[j]);
        }
    }

}
