#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include"definitions.h"

// void add_flights(int num,int* n,struct flight_det* allflight)
// {
//     FILE* fptr=fopen("fdata.csv","a");
// 	int day;
//     int index = *n;

// for (int i=0;i<num;i++)
// {
// printf("\nEnter flight code: ");
// scanf("%s",allflight[index].fcode);
// getchar();
// do
// {
// printf("Source Options:\n\t0. CHENNAI\n\t1. BANGALORE\n\t2. PUNE\n\t3. DELHI\n\t4. KOCHI\n\t5. MUMBAI\n\t6. HYDERABAD\n\t7. SINGAPORE\n\t8. LONDON\n\t9. DUBAI\n");
// printf("Enter option: ");
// scanf("%u",&allflight[*n].source);
// }while(allflight[*n].source<0 || allflight[*n].source>9);
// do
// {
// printf("Destination Options:\n\t0. CHENNAI\n\t1. BANGALORE\n\t2. PUNE\n\t3. DELHI\n\t4. KOCHI\n\t5. MUMBAI\n\t6. HYDERABAD\n\t7. SINGAPORE\n\t8. LONDON\n\t9. DUBAI\n");
// printf("Enter option: ");
// scanf(" %u",&allflight[*n].dest);
// }while(allflight[*n].dest<0 || allflight[*n].dest>9);
// do
// {
// printf("Enter departure time(hh:mm) : ");
// scanf("%d:%d",&allflight[*n].deptime.hh,&allflight[*n].deptime.mm);
// getchar();
// }while(allflight[*n].deptime.hh<0 || allflight[*n].deptime.hh>24 || allflight[*n].deptime.mm<0 || allflight[*n].deptime.mm>60);
// do
// {
// printf("Enter arrival time(hh:mm)   : ");
// scanf("%d:%d",&allflight[*n].arrtime.hh,&allflight[*n].arrtime.mm);
// }while(allflight[*n].arrtime.hh<0 || allflight[*n].arrtime.hh>24 || allflight[*n].arrtime.mm<0 || allflight[*n].arrtime.mm>60);
// do
// {
// printf("Day of operation of flight option:\n\t1. Sundays\n\t2. Mondays\n\t3. Tuesdays\n\t4. Wednesdays\n\t5. Thursdays\n\t6. Fridays\n\t7. Saturdays\nEnter choice: ");
// scanf("%d",&day);
// switch (day)
// {
// case 1: allflight[*n].day=SUNDAY;
// break;
// case 2: allflight[*n].day=MONDAY;
// break;
// case 3: allflight[*n].day=TUESDAY;
// break;
// case 4: allflight[*n].day=WEDNESDAY;
// break;
// case 5: allflight[*n].day=THURSDAY;
// break;
// case 6: allflight[*n].day=FRIDAY;
// break;
// case 7: allflight[*n].day=SATURDAY;
// break;
// }
// }while(day<1 || day>7);
// printf("Ticket prices\n");
// printf("\tEnter for first class    : ");
// scanf("%d",&allflight[*n].first);
// printf("\tEnter for business class : ");
// scanf("%d",&allflight[*n].business);
// printf("\tEnter for economy class  : ");
// scanf("%d",&allflight[*n].economy);

// fprintf(fptr,"%s,%u,%u,%d:%d,%d:%d,%d,%d,%d,%u\n",allflight[*n].fcode,allflight[*n].source,allflight[*n].dest,allflight[*n].deptime.hh,allflight[*n].deptime.mm,allflight[*n].arrtime.hh,allflight[*n].arrtime.mm,allflight[*n].first,allflight[*n].business,allflight[*n].economy,allflight[*n].day);
// *n = *n+1;
// }
// fclose(fptr);
// }


int genfl(){
    FILE* f=fopen("fldatacpy.csv","r");
    FILE* fptr=fopen("fldata.csv","w");
    char ac[][5] = {"6E","SG","AI","9W","G8","UK","I5"};
    // char num[][1] = {"0","1","2","3","4","5","6","7","8","9"};
    char fcode[8];
    struct flight_det det[1000];
    srand((unsigned) time(NULL));
    char buffer[1024];
    char* value;
    int row = 0;
    int column = 0;

    while(!feof(f)){
        fgets(buffer,1024,f);
        column = 0;
        value = strtok(buffer,",");
        while(value != NULL){
            if (column == 0) {
                strcpy(fcode,ac[rand()%7]);
                strcat(fcode,value);
                strcpy(det[row].fcode,fcode);
            }
            else if (column == 1) {
                det[row].source = (enum places) convertstf(value);
            }
            else if (column == 2) {
                det[row].dest = (enum places) convertstf(value);
            }
            else if (column == 3) {
                det[row].deptime.hh =  (strlen(value)==1) ? ((int)value[0]-48) : ((int)value[0]-48)*10+((int)value[1]-48);
            }
            else if (column == 4) {
                det[row].deptime.mm =  (strlen(value)==1) ? ((int)value[0]-48) : ((int)value[0]-48)*10+((int)value[1]-48);
            }
            else if (column == 5) {
                det[row].arrtime.hh =  (strlen(value)==1) ? ((int)value[0]-48) : ((int)value[0]-48)*10+((int)value[1]-48);
            }
            else if (column == 6) {
                det[row].arrtime.mm =  (strlen(value)==1) ? ((int)value[0]-48) : ((int)value[0]-48)*10+((int)value[1]-48);
            }
            else if (column == 7) {
                det[row].first = convertstf(value);
            }
            else if (column == 8) {
                det[row].business = convertstf(value);
            }
            else if (column == 9) {
                det[row].economy = convertstf(value);
            }
            else if (column == 10) {
                det[row].day = (enum days) ((int)*value-47);
            }
            value = strtok(NULL,",");
            column++;
        }
        if(det[row].source == det[row].dest) continue;
        fprintf(fptr,"%s,%u,%u,%d:%d,%d:%d,%d,%d,%d,%u\n",det[row].fcode,det[row].source,det[row].dest,det[row].deptime.hh,det[row].deptime.mm,det[row].arrtime.hh,det[row].arrtime.mm,det[row].first,det[row].business,det[row].economy,det[row].day);
        row++;
    }
    fclose(f);
    fclose(fptr);
    return --row;
}

int main(){
    int r = genfl();
    printf("%d",r);
    return 0;
}