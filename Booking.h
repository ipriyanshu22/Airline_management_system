#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include"definitions.h"
#include "graphADT.h"


void printseats()
{
printf("\n                          _____");
printf("\n                         /  |  \\");
printf("\n                        /___|___\\");
printf("\n                      /           \\");
printf("\n                    /               \\");
printf("\n                   /                 \\");
printf("\n                  /                   \\");
printf("\n                 |   A B C     D E F   |");
printf("\n             <<  |  | | | | 1 | | | |  |  >>");
printf("\n                 |  | | | | 2 | | | |  |                        FIRST CLASS");
printf("\n                 |  | | | | 3 | | | |  |");
printf("\n                 |                     |");
printf("\n                /|  | | | | 4 | | | |  |\\");
printf("\n              /  |  | | | | 5 | | | |  |  \\                    BUSINESS CLASS");
printf("\n            /    |  | | | | 6 | | | |  |    \\");
printf("\n          /  <<  |                     |  >>  \\");
printf("\n        /        |  | | | | 7 | | | |  |        \\");
printf("\n      /          |  | | | | 8 | | | |  |          \\");
printf("\n    /            |  | | | | 9 | | | |  |            \\");
printf("\n  /           /  |  | | | |10 | | | |  |  \\          \\        ECONOMY CLASS");
printf("\n/          /     |  | | | |11 | | | |  |     \\         \\");
printf("\n|       /    <<  |  | | | |12 | | | |  |  >>    \\       |");
printf("\n|____/           |  | | | |13 | | | |  |           \\____|");
printf("\n                 |  | | | |14 | | | |  |");
printf("\n                 |  | | | |15 | | | |  |\n");
getchar();
getchar();


}

// const char* getfield(char* line, int num)
// {
//     const char* tok;
//     for (tok = strtok(line, ";");
//             tok && *tok;
//             tok = strtok(NULL, ";\n"))
//     {
//         if (!--num)
//             return tok;
//     }
//     return NULL;
// }


float path_cost(int p_array[3], struct path *trip, float per)
{
    float total=0;
    for (int i=0; i<trip->num; i++)
    {
        total+= p_array[0]*trip->route[i].details.first + p_array[1]*trip->route[i].details.business + p_array[2]*trip->route[i].details.economy;
    }

    trip->cost=total*per/100;
    return trip->cost;
}

void display(struct path pat)
{
    if( pat.num==0){
        printf("\nNO FLIGHTS AVAILABLE\n\n");
    }
    else

    {
        printf("\nFlIGHT ROUTES\n");

            for( int i=0; i<pat.num; i++)
            {
                printf("%s", place[pat.route[i].details.source]);
                printf("->");
                printf("%s", place[pat.route[i].details.dest]);
                printf("\n\tFlight code: %s\n\tDeparture time: %d:%d\n\tArrival time: %d:%d\n", pat.route[i].details.fcode, pat.route[i].details.deptime.hh, pat.route[i].details.deptime.mm, pat.route[i].details.arrtime.hh, pat.route[i].details.arrtime.mm);
                printf("\tDate: %d/%d/%d\n", pat.route[i].flight_date.day, pat.route[i].flight_date.month, pat.route[i].flight_date.year);
                printf("\n");
            }
        printf("Total cost of path: %.2f \n", pat.cost);
    }

}

int is_direct(struct path *trip)
{
    return trip->num==1;
}

int single(struct path *trip)
{
    return trip->num==2;
}

int multi(struct path *trip)
{
    return trip->num>=3;
}
int no_filter(struct path *trip)
{
    return 1;
}
void filter(struct path paths[], int (*f)(struct path*),  int* path_no)
{
    int count=0;
    for (int i=0; i<*path_no; i++)
    {
        if ((*f)(&paths[i]))
        {
            paths[count]=paths[i];
            count++;
        }


    }
    *path_no=count;

}



int lcost(struct path *trip1, struct path *trip2)
{
    return trip1->cost<trip2->cost;
}

int hcost(struct path *trip1, struct path *trip2)
{
    return trip1->cost>trip2->cost;
}

int stops(struct path *trip1, struct path *trip2)
{
    return trip1->num<trip2->num;
}

void sort(struct path paths[], int path_no, int (*f)(struct path*, struct path*))
{   int min_index;
    for (int i=0; i<path_no-1; i++)
    {
        min_index=i;
        for(int j=i+1; j<path_no; j++)
        {
            if ((*f)(&paths[j], &paths[min_index]))
                min_index=j;
        }

        struct path temp=paths[min_index];
        paths[min_index]=paths[i];
        paths[i]=temp;

    }
}



void book(char* username)
{
    //f=fopen("a.bin", "rb+");
    int n; //no. of passengers
    FILE *f;
    enum days day;
    float per;
    time_t timer;
    struct tm curr_time;
    int diff;
    struct date dep_date;
    while(1)
    {

        time(&timer);
        curr_time=*localtime(&timer);  //Current time
        printf("\nEnter date of departure as day/month/year: ");
        scanf(" %d/%d/%d", &dep_date.day, &dep_date.month, &dep_date.year);
        diff=convert(dep_date.month, dep_date.day,  dep_date.year)-convert(curr_time.tm_mon+1, curr_time.tm_mday, curr_time.tm_year+1900);
        if (diff<0)
            printf("\n\nEntered date is past current date.\nPlease re-enter.\n\n");
        else if (diff>30)
            printf("\n\nBooking is available only for uptil 30 days before the flight journey.\nPlease re-enter.\n\n");
        else
            break;
    }

    // struct tm curr=*localtime(&timer);
    // int d = curr.tm_mday+diff;
    // int m = curr.tm_mon+1;
    // int y = curr.tm_year+1900;
    // int weekday  = (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7;
    // weekday += 1;
    if (diff>20)
        per=90;
    else if(diff>10)
        per=95;
    else
        per=100;
    //Variation in price based on time of booking




    int p_arr[3]={0, 0, 0}; //Stores no. of passengers in each category
    enum places source;
    enum places dest;
    printf("\n\nSOURCE\n\nOptions:\n0.CHENNAI\n1.BANGALORE\n2.PUNE\n3.DELHI\n4.KOCHI\n5.MUMBAI\n6.HYDERABAD\n7.SINGAPORE\n8.LONDON\n9.DUBAI\n\n");
    printf("Enter option: ");
    scanf("%u",&source);
    printf("\n\nDESTINATION\nOptions:\n0.CHENNAI\n1.BANGALORE\n2.PUNE\n3.DELHI\n4.KOCHI\n5.MUMBAI\n6.HYDERABAD\n7.SINGAPORE\n8.LONDON\n9.DUBAI\n\n");
    printf("Enter option: ");
    scanf("%u",&dest);

    system("cls");

    int choice1, choice2;

    printf("Enter no. of passengers: ");
    scanf("%d", &n);
    ticket t[n];
    for (int i=0; i<n; i++)
    {   
        //memcpy((t+i).u,*(all_users+i),sizeof(struct user_details));
        strcpy(t[i].username,username);
        printf("Passenger : %d\n", i+1);
        while(1)
        {
            printf("\n\nChoose Class\n1. First Class\n2. Business Class\n3. Economy Class\n\nEnter: ");
            scanf("%d", &choice2);
            if (choice2!=1&&choice2!=2&&choice2!=3)
                printf("Invalid Choice.\nPlease Re-enter.\n");
            else
                t[i].tclass = choice2;
                break;

        }

        system("cls");

        p_arr[choice2-1]++;


    }





    struct path paths[100]; //Stores all possible paths from source to destination
    struct path trip1;
    struct path trip2;       //Stores a particular path       //Stores a particular path
    int path_no=0;          //No. of paths from source->destination
    trip1.num=0;  
    trip2.num=0;             //No. of flights taken in trip          //Total no. of paths from source->destination          //No. of flights taken in trip          //Total no. of paths from source->destination
    int visited[10];        //To keep track of visited places to avoid cycles in the graph
    for (int i=0; i<10; i++)
    {
        visited[i]=0;       //Marking all places as unvisited
    }

    struct flight flights[400];
    int num=0; //no. of available flights
    f=fopen("schedule.csv", "r");
    char buffer[1024];
    char* value;
 
        int row = 0;
        int column = 0;
 
        while (!feof(f)){
            fgets(buffer,1024,f);
            column = 0;
            // char* tmp = strdup(buffer);
            // int val = (int) *getfield(tmp,7+days);
            // if(!val){
            //     free(temp);
            //     row++;
            //     continue;
            // }
            // free(tmp);
            value = strtok(buffer, ",");
            while(value != NULL){
                if (column == 0) {
                    strcpy(flights[row].details.fcode,value);
                }
                else if (column == 1) {
                    flights[row].details.source = (enum places) convertstf(value);
                }
                else if (column == 2) {
                    flights[row].details.dest = (enum places) convertstf(value);
                }
                else if (column == 3) {
                    flights[row].details.deptime.hh = (value[1]==':') ? ((int)value[0]-48) : ((int)value[0]-48)*10+((int)value[1]-48);
                    flights[row].details.deptime.mm = (value[1]==':') ? ((strlen(value)==4) ? ((int)value[2]-48)*10+((int)value[3]-48) : ((int)value[2]-48)) : ((strlen(value)==5) ? ((int)value[3]-48)*10+((int)value[4]-48) : ((int)value[3]-48));
                }
                else if (column == 4) {
                    flights[row].details.arrtime.hh = (value[1]==':') ? ((int)value[0]-48) : ((int)value[0]-48)*10+((int)value[1]-48);
                    flights[row].details.arrtime.mm = (value[1]==':') ? ((strlen(value)==4) ? ((int)value[2]-48)*10+((int)value[3]-48) : ((int)value[2]-48)) : ((strlen(value)==5) ? ((int)value[3]-48)*10+((int)value[4]-48) : ((int)value[3]-48));
                }
                else if (column == 5) {
                    flights[row].details.first = convertstf(value);
                }
                else if (column == 6) {
                    flights[row].details.business = convertstf(value);
                }
                else if (column == 7) {
                    flights[row].details.economy = convertstf(value);
                }
                else if (column == 8) {
                    flights[row].details.day = (enum days) ((int)*value-48);
                }
                else if (column == 9) {
                    flights[row].flight_date.day = (value[1]=='/') ? ((int)value[0]-48) : ((int)value[0]-48)*10+((int)value[1]-48);
                    flights[row].flight_date.month = (value[1]=='/') ? ((value[3]=='/') ? ((int)value[2]-48) : ((int)value[2]-48)*10+((int)value[3]-48)) : ((value[4]=='/') ? ((int)value[3]-48) : ((int)value[3]-48)*10+((int)value[4]-48));
                    flights[row].flight_date.year = (value[1]=='/') ? ((value[3]=='/') ? ((int) convertstf(value+4)) :((int) convertstf(value+5))) : ((value[4]=='/') ? ((int) convertstf(value+5)) :((int) convertstf(value+6)));
                }
                value = strtok(NULL, ",");
                column++;
            }
            row++;
        }
        fclose(f);

    num = --row;
    int diff2;
    linkedList* adj_list[10]; //adjacency list
    createAdjList(adj_list, 10);
    for (int i=0; i<num; i++)
    {   
        diff2 = convert(flights[i].flight_date.month, flights[i].flight_date.day, flights[i].flight_date.year)-convert(dep_date.month, dep_date.day,  dep_date.year);
        if(diff2 < 0){
            continue;
        }
        ins_end(flights[i], adj_list[(int) flights[i].details.source]);
    }
    redo:
    day = (enum days) convert( dep_date.month, dep_date.day, dep_date.year)%7+1;
    printf("All is well\n");
    trip1 = dja(source,dest,day,adj_list);
    trip1.cost = path_cost(p_arr, &trip1, per);
    trip2 = dja_cost(source,dest,day,adj_list,p_arr);
    trip2.cost = path_cost(p_arr, &trip2, per);
    printf("Fastest Flight:\n");
    display(trip1);
    printf("Cheapest Flight:\n");
    display(trip2);
    getchar();
    getchar();


    if(trip1.num!=0 || trip2.num!=0)

    {
        printf("\n\n\n\n");
        // scanf("%d", &choice2);
        // int (*fil)(struct path*);
        // int (*s)(struct path*, struct path*);
        // switch(choice1)
        // {
        //     case 1: fil=&is_direct;break;
        //     case 2: fil=&single;break;
        //     case 3: fil=&multi;break;
        //     case 4: fil=&no_filter;break;
        // }

        // switch(choice2)
        // {
        //     case 1: s=&lcost;break;
        //     case 2: s=&hcost;break;
        //     case 3: s=&stops;break;

        // }


        // filter(paths, fil,  &path_no);
        // sort(paths, path_no, s);

        // display(paths[0]);

        FILE *file;

        char choice[10];
        char user[10];


        // printf("Enter username: ");
        // scanf("%s",user);

        printf("\nEnter flight code to be booked or x to exit: ");
        scanf("%s",choice);
        if(strcmp("x", choice)==0){
            printf("Booking Cancelled\n");
            return;
        }
        file=fopen("bookings.csv","a");
        struct flight final;
        for(int i=0;i<100;i++){
            if(strcmp(flights[i].details.fcode,choice)==0){
                final = flights[i];
                break;
            }
        }
        for(int i=0;i<n;i++)
        {
            strcpy(t[i].fcode,final.details.fcode);
            t[i].flight_date = final.flight_date;
            t[i].source = final.details.source;
            t[i].dest = final.details.dest;
            srand( (unsigned int) time(NULL));  
            float f1 = 10000000000000.0;  
            float f2 = ((float) rand()/ RAND_MAX) * f1;
            t[i].pnr = (long long int) f2;
            fprintf(file,"%s,%lld,%u,%u,%s,%d/%d/%d,%d\n",t[i].username,t[i].pnr,t[i].source,t[i].dest,t[i].fcode,t[i].flight_date.day,t[i].flight_date.month,t[i].flight_date.year,t[i].tclass);

        }
        fclose(file);

        system("cls");

        printf("\n\nSEATING ARRANGEMENT\n\n");

        printseats();

    }
    else{
        int ch;
        printf("Do you want to check availability for any other date? (0:No | 1:Yes):");
        scanf("%d",&ch);
        if(ch==0){
            return;
        }
        printf("\nEnter date of departure as day/month/year: ");
        scanf(" %d/%d/%d", &dep_date.day, &dep_date.month, &dep_date.year);
        for (int i=0; i<10; i++)
        {
            visited[i]=0;       //Marking all places as unvisited
        }
        goto redo;
    }
}