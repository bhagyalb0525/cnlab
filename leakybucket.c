#include <stdio.h>

int main()
{
    int bucket_capacity, output_rate;
    int n, packets[100];

    int incoming;
    int received;
    int sent;
    int dropped;
    int remaining = 0;

    printf("Enter bucket capacity: ");
    scanf("%d", &bucket_capacity);

    printf("Enter output rate: ");
    scanf("%d", &output_rate);

    printf("Enter number of packets: ");
    scanf("%d", &n);

    printf("Enter packet sequence:\n");

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &packets[i]);
    }

    printf("\n");
    printf("INCOMING\tRECEIVED\tSENT\tDROPPED\tREMAINING\n");

    for(int i = 0; i < n; i++)
    {
        incoming = packets[i];

        received = 0;
        sent = 0;
        dropped = 0;

        /* CHECK WHETHER PACKET CAN ENTER BUCKET */

        if(remaining + incoming <= bucket_capacity)
        {
            remaining = remaining + incoming;
            received = incoming;
        }
        else
        {
            dropped = incoming;
        }

        /* SEND PACKETS */

        if(remaining >= output_rate)
        {
            remaining = remaining - output_rate;
            sent = output_rate;
        }
        else
        {
            sent = remaining;
            remaining = 0;
        }

        printf("%8d\t%8d\t%4d\t%8d\t%9d\n",
               incoming, received, sent, dropped, remaining);
    }

    return 0;
}
