#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include"definitions.h"
#include "dateADT.h"
#include "graphADT.h"

struct flight_det flights[500];

int main(){
        FILE* f=fopen("fldata.csv","r");
        if(!f){
            return 0;
        }
        char buffer[1024];
        char* value;
        int row = 0;
        int column = 0;
 
        while(!feof(f)){
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
            value = strtok(buffer,",");
            while(value != NULL){
                if (column == 0) {
                    strcpy(flights[row].fcode,value);
                }
                else if (column == 1) {
                    flights[row].source = (enum places) convertstf(value);
                }
                else if (column == 2) {
                    flights[row].dest = (enum places) convertstf(value);
                }
                else if (column == 3) {
                    flights[row].deptime.hh = (value[1]==':') ? ((int)value[0]-48) : ((int)value[0]-48)*10+((int)value[1]-48);
                    flights[row].deptime.mm = (value[1]==':') ? ((strlen(value)==4) ? ((int)value[2]-48)*10+((int)value[3]-48) : ((int)value[2]-48)) : ((strlen(value)==5) ? ((int)value[3]-48)*10+((int)value[4]-48) : ((int)value[3]-48));
                }
                else if (column == 4) {
                    flights[row].arrtime.hh = (value[1]==':') ? ((int)value[0]-48) : ((int)value[0]-48)*10+((int)value[1]-48);
                    flights[row].arrtime.mm = (value[1]==':') ? ((strlen(value)==4) ? ((int)value[2]-48)*10+((int)value[3]-48) : ((int)value[2]-48)) : ((strlen(value)==5) ? ((int)value[3]-48)*10+((int)value[4]-48) : ((int)value[3]-48));
                }
                else if (column == 5) {
                    flights[row].first = convertstf(value);
                }
                else if (column == 6) {
                    flights[row].business = convertstf(value);
                }
                else if (column == 7) {
                    flights[row].economy = convertstf(value);
                }
                else if (column == 8) {
                    flights[row].day = (enum days) ((int)*value-48);
                    //printf("%d",flights[row].day);
                }
                value = strtok(NULL,",");
                column++;
            }
            row++;
        }
        fclose(f);
        --row;

        int days = 0;
        time_t timer;
        time(&timer);
        struct tm curr=*localtime(&timer);
        struct date dep_date;
        dep_date.day = curr.tm_mday;
        dep_date.month = curr.tm_mon+1;
        dep_date.year = curr.tm_year+1900;
        //int d = dep_date.day;
        //int m = dep_date.month;
        //int y = dep_date.day;
        int diff=convert(dep_date.month, dep_date.day,  dep_date.year)-convert(curr.tm_mon+1, curr.tm_mday, curr.tm_year+1900);
        FILE* fp = fopen("schedule.csv","w");

        while(diff<=30){
            int d = dep_date.day;
            int m = dep_date.month;
            int y = dep_date.year;
            int weekday  = (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7+1;  
            enum days wday = (enum days) weekday;
            for(int i=0;i<row;i++){
                //printf("%d\n",flights[i].day);
                if(flights[i].day == weekday){
                    fprintf(fp,"%s,%u,%u,%d:%d,%d:%d,%d,%d,%d,%u,%d/%d/%d\n",flights[i].fcode,flights[i].source,flights[i].dest,flights[i].deptime.hh,flights[i].deptime.mm,flights[i].arrtime.hh,flights[i].arrtime.mm,flights[i].first,flights[i].business,flights[i].economy,flights[i].day,dep_date.day,dep_date.month,dep_date.year);
                }
            }
            addtodate(1,dep_date.day,dep_date.month,dep_date.year,&dep_date);
            diff=convert(dep_date.month, dep_date.day,  dep_date.year)-convert(curr.tm_mon+1, curr.tm_mday, curr.tm_year+1900);
        }
        
        fclose(fp);
    }



