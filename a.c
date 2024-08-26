#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include"Booking.h"

// Function to display the introductory opening page
void ticket_view_pnr(long long int pnr);
void ticket_view_usn(char* usn);
void ticket_del_pnr(int pnr);
void intro()
{
    system("cls");
    system("color 30");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t  MINI PROJECT\n");
    printf("\n\t\t\t\t\t\t\t\t\t\t  Airplane Reservation System");
    printf("\n\n\n\t\t\t\t\t\t\t\t\t\tMADE BY: Prasad Ishwar \n \t\t\t\t\t\t\t\t\t\t\t Praneel Patel\n\t\t\t\t\t\t\t\t\t\t\t Priyanshu Chaudhary\n\t\t\t\t\t\t\t\t\t\t\t Pranav Surya\n\n\t\t\t\t");
    printf("\t\t\t\t\t\t\tBRANCH : CSE H\n");
    printf("\n\t\t\t\t\t\t\t\t\t\tCOLLEGE: PES\n");
    getchar();
}

char* getfield(char* line, int num)
{
    char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ","))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

void ticket_enquiry()
{
    system("cls");
    char ch;

    printf("\n\n\n\tBOOKED TICKET ENQUIRY");
    printf("\n\n\tTICKET OPTIONS");
    printf("\n\n\t\t1. View Particular Flight Ticket based on PNR");
    printf("\n\n\t\t2. View All Flight Tickets for username");
    printf("\n\n\t\t3. Cancel Ticket");
    // printf("\n\n\tBILL OPTIONS");
    // printf("\n\n\t\t3. View A Particular Bill");
    // printf("\n\n\t\t4. View All Bills");
    printf("\n\n\tEXIT OPTION");
    printf("\n\n\t\t4. BACK TO USER MENU");

    printf("\n\n\n\n\tEnter choice: ");
    scanf(" %c", &ch);
    char usn[25];
    long long int pnr;
    switch(ch)
    {
        case '1':	system("cls");
                    long long int pnr;
                    printf("Enter pnr:");
                    scanf("%lld",&pnr);
					ticket_view_pnr(pnr);
					break;

        case '2':   system("cls");
                    printf("Enter username:");
                    scanf("%s",usn);
					ticket_view_usn(usn);
					break;
        case '3':
                    system("cls");
                    printf("Enter pnr:");
                    scanf("%lld",&pnr);
                    ticket_del_pnr(pnr);
                    break;
        // case '3':   system("clear");
		// 			getch();
		// 			ticket_enquiry();
		// 			break;

        // case '4':   system("clear");
		// 			getch();
		// 			ticket_enquiry();
		// 			break;

        case '4':   system("cls");
					break;

        default:    ticket_enquiry();
    }
}

int read_count_users(struct user_details* all_users)
{
    int count=0;
    FILE* fptr=fopen("user.csv", "r");
    char buffer[256];
    int row=0;
    int column = 0;
    while(fgets(buffer,256,fptr)){
            column = 0;
            char* value = strtok(buffer, ",");
            while(value != NULL){
                if(column == 0){
                    strcpy(all_users[row].username,value);
                }
                else if(column == 1){
                    strcpy(all_users[row].password,value);
                }
                else if(column == 2){
                    strcpy(all_users[row].name,value);
                }
                column++;
                value = strtok(NULL, ",");
            }
            row++;
    }
    count = row;
    fclose(fptr);
    return count;
}

int search_users(int count,struct user_details* all_users)
{
    char searchu[40];
    printf("\n\tCURRENT Username:");
    scanf("%s",searchu);
    getchar();
    for (int i=0; i<count; i++){
        if(strcmp(all_users[i].username,searchu)==0){
                return i;
        }
    }
    return -1;
}

void user_det_update(int count,struct user_details* all_users,int index)
{
    //struct user_details all_users[100];
    //int count=0, index=-1;

    //count=read_count_users(all_users);

    printf("\n\n\n\tUPDATE USER ACCOUNT PROFILE\n");

    //index=search_users(count, all_users);


    if(index!=-1)
    {
        char ch;
        FILE *fptr=fopen("user.csv", "w");
        do
        {   system("cls");
            system("color 30");
            printf("\n\n\n\tUPDATE USER ACCOUNT PROFILE\n");

            printf("\n\n\t0. Username");
            printf("\n\n\t1. Password");
            printf("\n\n\t2. Name");
            // printf("\n\n\t3. Address");
            // printf("\n\n\t4. Nationality");
            // printf("\n\n\t5. Mobile Number");
            // printf("\n\n\t6. Email ID");
            // printf("\n\n\t7. Date Of Birth");
            // printf("\n\n\t8. Age");
            // printf("\n\n\t9. Gender");
            printf("\n\n\te. BACK TO USER MENU");

            printf("\n\n\n\n\tEnter choice: ");
            scanf("%c", &ch);
            getchar();
            switch(ch)
            {
                case '0':   system("cls");
							printf("\n\n\n\tUPDATE USER ACCOUNT PROFILE\n");
							printf("\n\n\tEnter the NEW Details\n\n");
							printf("\tUSERNAME: ");
							scanf(" %[^\n]", all_users[index].username);
                            getchar();
							break;

                case '1':    system("cls");
							printf("\n\n\n\tUPDATE USER ACCOUNT PROFILE\n");
							printf("\n\n\tEnter the NEW Details\n\n");
							printf("\tPASSWORD: ");
							scanf(" %[^\n]", all_users[index].password);
                            getchar();
							break;

                case '2':   system("cls");
							printf("\n\n\n\tUPDATE USER ACCOUNT PROFILE\n");
							printf("\n\n\tEnter the NEW Details\n\n");
							printf("\n\tName: ");
							scanf(" %[^\n]", all_users[index].name);
                            getchar();
							break;

                // case '3':   system("clear");
				// 			printf("\n\n\n\tUPDATE USER ACCOUNT PROFILE\n");
				// 			printf("\n\n\tEnter the NEW Details\n\n");
				// 			printf("\n\tAddress:\n");
				// 			printf("\tStreet: ");
				// 			scanf(" %[^\n]", all_users[index].address.street);

				// 			printf("\tCity: ");
				// 			scanf(" %[^\n]", all_users[index].address.city);

				// 			printf("\tPincode: ");
				// 			scanf(" %[^\n]", all_users[index].address.pincode);

				// 			printf("\tState: ");
				// 			scanf(" %[^\n]", all_users[index].address.state);
				// 			break;

                // case '4':   system("clear");
				// 			printf("\n\n\n\tUPDATE USER ACCOUNT PROFILE\n");
				// 			printf("\n\n\tEnter the NEW Details\n\n");
				// 			printf("\n\tNationality: ");
				// 			scanf(" %[^\n]", all_users[index].nationality);
				// 			break;

                // case '5':   system("clear");
				// 			printf("\n\n\n\tUPDATE USER ACCOUNT PROFILE\n");
				// 			printf("\n\n\tEnter the NEW Details\n\n");
				// 			printf("\tMobile: ");
				// 			scanf(" %[^\n]", all_users[index].mobile);
				// 			break;

                // case '6':   system("clear");
				// 			printf("\n\n\n\tUPDATE USER ACCOUNT PROFILE\n");
				// 			printf("\n\n\tEnter the NEW Details\n\n");
				// 			printf("\tEmail ID: ");
				// 			scanf(" %[^\n]", all_users[index].email);
				// 			break;

                // case '7':   system("clear");
				// 			printf("\n\n\n\tUPDATE USER ACCOUNT PROFILE\n");
				// 			printf("\n\n\tEnter the NEW Details\n\n");
				// 			printf("\n\tEnter DATE in dd mm yyyy FORMAT\n");
				// 			printf("\tDate of birth: ");
				// 			scanf("%d %d %d", &all_users[index].dob.day, &all_users[index].dob.month, &all_users[index].dob.year);
				// 			break;

                // case '8':   system("clear");
				// 			printf("\n\n\n\tUPDATE USER ACCOUNT PROFILE\n");
				// 			printf("\n\n\tEnter the NEW Details\n\n");
				// 			printf("\n\tAge: ");
				// 			scanf("%d", &all_users[index].age);
				// 			break;

                // case '9':   system("clear");
				// 			printf("\n\n\n\tUPDATE USER ACCOUNT PROFILE\n");
				// 			printf("\n\n\tEnter the NEW Details\n\n");
				// 			printf("\n\tF: Female M: Male T:Transgender O:Other\n");
				// 			printf("\tGender: ");
				// 			scanf(" %c", &all_users[index].gender);
				// 			break;

                case 'e':   printf("\n\n\n\tUPDATED USER ACCOUNT PROFILE SUCCESSFULLY...!!!\n");
							getchar();
							break;

                default:    system("cls");
							printf("\n\n\n\tUPDATE USER ACCOUNT PROFILE\n");
							printf("\n\nINVALID CHOICE\n");
							getchar();
            }
        }while(ch!='e');

        for(int i=0;i<count;i++){
            fprintf(fptr,"%s,%s,%s\n",all_users[i].username,all_users[i].password,all_users[i].name);
        }
        fclose(fptr);

    }

    else
    {
        printf("\n\n\n\tUSER NOT FOUND...!!!");
        printf("\n\n\tINVALID USERNAME/DOESN'T EXIST...!!!\n");
    }

}

void user_det_delete(int count,struct user_details* all_users,int index)
{
    //struct user_details all_users[100];
    //int count=0, index=-1;

    printf("\n\n\n\tDELETE USER PROFILE\n\n");

    //count=read_count_users(all_users);

    //index=search_users(count, all_users);


    if(index!=-1)
    {
        FILE *fptr=fopen("user.csv", "w");
        for(int i=index; i<(count-1); i++)
            all_users[i]=all_users[i+1];
        


        for(int i=0; i<(count-1); i++){
            fprintf(fptr,"%s,%s,%s\n",all_users[i].username,all_users[i].password,all_users[i].name);
        }
        fclose(fptr);
        printf("\n\n\n\tDELETED USER ACCOUNT PROFILE SUCCESSFULLY...!!!\n");
    }

    else
    {
        printf("\n\n\n\tUSER NOT FOUND...!!!");
        printf("\n\n\tINVALID USERNAME/DOESN'T EXIST...!!!\n");
    }


    getchar();
}

void user_det_view_particular(struct user_details* all_users,int index)
{
    //struct user_details all_users[100];
    // int count=0, index=-1;

    // printf("\n\n\n\tVIEW A PARTICULAR USER ACCOUNT PROFILE\n\n");

    //count=read_count_users(all_users);

    // index=search_users(count, all_users);

    if(index!=-1)
    {
        system("cls");

        printf("\n\n\n\tVIEW USER ACCOUNT PROFILE\n\n");

        printf("\tUSERNAME: %s\n", all_users[index].username);

        printf("\tPASSWORD: %s\n", all_users[index].password);

        printf("\n\tName: %s\n", all_users[index].name);

        // printf("\n\tAddress:\n");
        // printf("\t%s\n\t%s - %s\n\t%s\n", all_users[index].address.street, all_users[index].address.city, all_users[index].address.pincode, all_users[index].address.state);

        // printf("\n\tNationality: %s\n", all_users[index].nationality);

        // printf("\tMobile: %s\n", all_users[index].mobile);

        // printf("\tEmail ID: %s\n", all_users[index].email);

        // printf("\tDate of birth: %d-%d-%d\n", all_users[index].dob.day, all_users[index].dob.month, all_users[index].dob.year);

        // printf("\n\tAge: %d\n", all_users[index].age);

        // printf("\n\tF: Female M: Male T:Transgender O:Other\n");
        // printf("\tGender: %c\n", all_users[index].gender);
    }

    else
    {
        printf("\n\n\n\tUSER NOT FOUND...!!!");
        printf("\n\n\tINVALID USERNAME/DOESN'T EXIST...!!!\n");
    }

    getchar();

}


void user_det_view_all()
{
    struct user_details all_users[100];
    int count=-1;
    int i = 0;

    printf("\n\n\n\tVIEW All USER ACCOUNT PROFILE");

    count=read_count_users(all_users);
    printf("%d",count);

    while(i<count)
    {
        printf("\n\n\tACCOUNT PROFILE DETAILS\n\n");

        printf("\tUSERNAME: %s\n", all_users[i].username);

        printf("\tPASSWORD: %s\n", all_users[i].password);

        printf("\tName: %s\n", all_users[i].name);

        // printf("\n\tAddress:\n");
        // printf("\t%s\n\t%s - %s\n\t%s\n", all_users[i].address.street, all_users[i].address.city, all_users[i].address.pincode, all_users[i].address.state);

        // printf("\n\tNationality: %s\n", all_users[i].nationality);

        // printf("\tMobile: %s\n", all_users[i].mobile);

        // printf("\tEmail ID: %s\n", all_users[i].email);

        // printf("\tDate of birth: %d-%d-%d\n", all_users[i].dob.day, all_users[i].dob.month, all_users[i].dob.year);

        // printf("\n\tAge: %d\n", all_users[i].age);

        // printf("\n\tF: Female M: Male T:Transgender O:Other\n");
        // printf("\tGender: %c\n", all_users[i].gender);
        i++;
    }
    getchar();
    getchar();
}


void user_menu(int count,struct user_details* all_users,int index)
{
    system("cls");
    char ch;

    printf("\n\n\n\tUSER OPTIONS");
    printf("\n\n\tTICKET OPTIONS");
    printf("\n\n\t\t1. Book Flight Ticket");
    //printf("\n\n\t\t2. Current Flight Ticket Bookings");
    //printf("\n\n\t\t3. Cancel Flight Ticket");
    printf("\n\n\tACCOUNT OPTIONS");
    printf("\n\n\t\t2. View Account Profile");
    printf("\n\n\t\t3. Update Account Profile");
    printf("\n\n\t\t4. Delete Account");
    printf("\n\n\t\t5. View Ticket | Cancel Ticket");
    printf("\n\n\tEXIT OPTION");
    printf("\n\n\t\t6. BACK TO MAIN MENU");
    printf("\n\n\n\n\tEnter choice: ");
    scanf("%c", &ch);
    getchar();
    switch(ch)

    {
        case '1':
                system("cls");
                book(all_users[index].username);
                getchar();
                user_menu(count,all_users,index);
                break;

       /* case '2':    system("clear");
                ticket_enquiry();
                user_menu();
                break;

        case '3':    system("clear");
                getch();
                user_menu();
                break;
        */

        case '2':    
                system("cls");
                user_det_view_particular(all_users,index);
                user_menu(count,all_users,index);
                break;

        case '3':    
                system("cls");
                user_det_update(count,all_users,index);
                user_menu(count,all_users,index);
                break;

        case '4':    
                system("cls");
                user_det_delete(count,all_users,index);
                break;
        case '5':
                ticket_enquiry();
                user_menu(count,all_users,index);

        case '6':    
                system("cls");
                break;

                
        default:
                user_menu(count,all_users,index);  
    }
}

void add_flights(int num,int* n,struct flight_det* allflight)
{
    FILE* fptr=fopen("fldata.csv","a");
	int day;
    int index = *n;

for (int i=0;i<num;i++)
{
printf("\nEnter flight code: ");
scanf("%s",allflight[index].fcode);
getchar();
do
{
printf("Source Options:\n\t0. CHENNAI\n\t1. BANGALORE\n\t2. PUNE\n\t3. DELHI\n\t4. KOCHI\n\t5. MUMBAI\n\t6. HYDERABAD\n\t7. SINGAPORE\n\t8. LONDON\n\t9. DUBAI\n");
printf("Enter option: ");
scanf("%u",&allflight[*n].source);
}while(allflight[*n].source<0 || allflight[*n].source>9);
do
{
printf("Destination Options:\n\t0. CHENNAI\n\t1. BANGALORE\n\t2. PUNE\n\t3. DELHI\n\t4. KOCHI\n\t5. MUMBAI\n\t6. HYDERABAD\n\t7. SINGAPORE\n\t8. LONDON\n\t9. DUBAI\n");
printf("Enter option: ");
scanf(" %u",&allflight[*n].dest);
}while(allflight[*n].dest<0 || allflight[*n].dest>9);
do
{
printf("Enter departure time(hh:mm) : ");
scanf("%d:%d",&allflight[*n].deptime.hh,&allflight[*n].deptime.mm);
getchar();
}while(allflight[*n].deptime.hh<0 || allflight[*n].deptime.hh>24 || allflight[*n].deptime.mm<0 || allflight[*n].deptime.mm>60);
do
{
printf("Enter arrival time(hh:mm)   : ");
scanf("%d:%d",&allflight[*n].arrtime.hh,&allflight[*n].arrtime.mm);
}while(allflight[*n].arrtime.hh<0 || allflight[*n].arrtime.hh>24 || allflight[*n].arrtime.mm<0 || allflight[*n].arrtime.mm>60);
do
{
printf("Day of operation of flight option:\n\t1. Sundays\n\t2. Mondays\n\t3. Tuesdays\n\t4. Wednesdays\n\t5. Thursdays\n\t6. Fridays\n\t7. Saturdays\nEnter choice: ");
scanf("%d",&day);
switch (day)
{
case 1: allflight[*n].day=SUNDAY;
break;
case 2: allflight[*n].day=MONDAY;
break;
case 3: allflight[*n].day=TUESDAY;
break;
case 4: allflight[*n].day=WEDNESDAY;
break;
case 5: allflight[*n].day=THURSDAY;
break;
case 6: allflight[*n].day=FRIDAY;
break;
case 7: allflight[*n].day=SATURDAY;
break;
}
}while(day<1 || day>7);
printf("Ticket prices\n");
printf("\tEnter for first class    : ");
scanf("%d",&allflight[*n].first);
printf("\tEnter for business class : ");
scanf("%d",&allflight[*n].business);
printf("\tEnter for economy class  : ");
scanf("%d",&allflight[*n].economy);

fprintf(fptr,"%s,%u,%u,%d:%d,%d:%d,%d,%d,%d,%u\n",allflight[*n].fcode,allflight[*n].source,allflight[*n].dest,allflight[*n].deptime.hh,allflight[*n].deptime.mm,allflight[*n].arrtime.hh,allflight[*n].arrtime.mm,allflight[*n].first,allflight[*n].business,allflight[*n].economy,allflight[*n].day);
*n = *n+1;
}
fclose(fptr);
}


int read_det(struct flight_det* flights)
{
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
                }
                value = strtok(NULL,",");
                column++;
            }
            row++;
        }
        fclose(f);
        return --row;
}


void disp(int i,struct flight_det* allflight)
{
printf("%s    %s    %s    %d:%d    %d:%d    %s    %d  %d  %d\n",allflight[i].fcode, place[allflight[i].source],place[allflight[i].dest], allflight[i].deptime.hh, allflight[i].deptime.mm, allflight[i].arrtime.hh, allflight[i].arrtime.mm,day[allflight[i].day], allflight[i].first, allflight[i].business, allflight[i].economy);
}


int search(int n, struct flight_det* allflight)
{
    char search[20];
    printf("Enter flight code: ");
    scanf("%s",search);
    for (int i=0;i<n;i++)
    {
        if(strcmp(allflight[i].fcode,search)==0)
            return i;
    }
    return -1;
}


void modify(int index,int n,struct flight_det* allflight)
{

FILE* f=fopen("fldata.csv","w");
int day;
printf("Source Options:\n\t0. CHENNAI\n\t1. BANGALORE\n\t2. PUNE\n\t3. DELHI\n\t4. KOCHI\n\t5. MUMBAI\n\t6. HYDERABAD\n\t7. SINGAPORE\n\t8. LONDON\n\t9. DUBAI\n");
printf("Enter new option: ");
scanf(" %u",&allflight[index].source);
printf("Destination Options:\n\t0. CHENNAI\n\t1. BANGALORE\n\t2. PUNE\n\t3. DELHI\n\t4. KOCHI\n\t5. MUMBAI\n\t6. HYDERABAD\n\t7. SINGAPORE\n\t8. LONDON\n\t9. DUBAI\n");
printf("Enter new option: ");
scanf(" %u",&allflight[index].dest);
printf("Enter new departure time(hh/mm) : ");
scanf("%d/%d",&allflight[index].deptime.hh,&allflight[index].deptime.mm);
printf("Enter new arrival time(hh/mm)   : ");
scanf("%d/%d",&allflight[index].arrtime.hh,&allflight[index].arrtime.mm);
printf("Day of operation of flight option:\n\t1. Sundays\n\t2. Mondays\n\t3. Tuesdays\n\t4. Wednesdays\n\t5. Thursdays\n\t6. Fridays\n\t7. Saturdays\nEnter new choice: ");
scanf("%d",&day);
switch (day)
    {
    case 1: allflight[index].day=SUNDAY;
    break;
    case 2: allflight[index].day=MONDAY;
    break;
    case 3: allflight[index].day=TUESDAY;
    break;
    case 4: allflight[index].day=WEDNESDAY;
    break;
    case 5: allflight[index].day=THURSDAY;
    break;
    case 6: allflight[index].day=FRIDAY;
    break;
    case 7: allflight[index].day=SATURDAY;
    break;
    }
printf("New ticket prices\n");
printf("\tEnter for first class    : ");
scanf("%d",&allflight[index].first);
printf("\tEnter for business class : ");
scanf("%d",&allflight[index].business);
printf("\tEnter for economy class  : ");
scanf("%d",&allflight[index].economy);
for(int i=0;i<n;i++){
fprintf(f,"%s,%u,%u,%d:%d,%d:%d,%d,%d,%d,%u\n",allflight[i].fcode,allflight[i].source,allflight[i].dest,allflight[i].deptime.hh,allflight[i].deptime.mm,allflight[i].arrtime.hh,allflight[i].arrtime.mm,allflight[i].first,allflight[i].business,allflight[i].economy,allflight[i].day);
}
fclose(f);
}


void delete(int index,int* n,struct flight_det* allflight)
{
FILE* f=fopen("fldata.csv","w");
*n = *n-1;
for (int i=index;i<*n;i++)
    allflight[i]=allflight[i+1];
for(int i=0;i<*n;i++){
fprintf(f,"%s,%u,%u,%d:%d,%d:%d,%d,%d,%d,%u\n",allflight[i].fcode,allflight[i].source,allflight[i].dest,allflight[i].deptime.hh,allflight[i].deptime.mm,allflight[i].arrtime.hh,allflight[i].arrtime.mm,allflight[i].first,allflight[i].business,allflight[i].economy,allflight[i].day);
}
printf("Flight Record Deleted!!\n");
fclose(f);
}


void admin_menu(int n,struct flight_det* allflight)
{
    system("cls");
    char ch;
    int num;
    int index;

    printf("\n\n\n\tADMINISTRATOR OPTIONS");
    printf("\n\n\tFLIGHT OPTIONS");
    printf("\n\n\t\t1. Add New Flight");
    printf("\n\n\t\t2. Update Existing Flight");
    printf("\n\n\t\t3. Delete A Particular Flight");
    printf("\n\n\t\t4. Display A Particular Flight");
    printf("\n\n\t\t5. Display All Flights");
    printf("\n\n\tCUSTOMER OPTIONS");
    //printf("\n\n\t\t6. View A Particular User Account Profile");
    printf("\n\n\t\t6. View All User Account Profiles");
    printf("\n\n\tEXIT OPTION");
    printf("\n\n\t\t7. BACK TO MAIN MENU");

    printf("\n\n\n\n\tEnter choice: ");
    scanf("%c", &ch);
    switch(ch)

    {
        case '1':    system("cls");
        printf("Enter number of flights to be added: ");
        scanf("%d",&num);
        add_flights(num,&n,allflight);
                admin_menu(n,allflight);
                break;

        case '2':    system("cls");
        index=search(n, allflight);
        if (index==-1){
            printf("\nFlight details not found!!\n");
        }
        else{
            modify(index,n,allflight);
        }                
            admin_menu(n,allflight);
            break;
        case '3':    system("cls");
        index=search(n, allflight);
        if (index==-1){
            printf("\nFlight details not found!!\n");
            getchar();
            getchar();
            admin_menu(n,allflight);
            break;
        }
        else{
            delete(index,&n,allflight);
            getchar();
            getchar();
            admin_menu(n,allflight);
            break;
        }
        case '4':    system("cls");
        index=search(n, allflight);
        if (index==-1)
            printf("\nFlight code does not exist!!\n");
        else
        {
printf("FCODE    SOURCE    DESTINATION    DEPARTURE    ARRIVAL    DAY    FARES \n");
printf("                                                                    FIRST    BUSINESS  ECONOMY\n");
            disp(index, allflight);
        }
        getchar();
        getchar();
        admin_menu(n,allflight);
            break;

        case '5':    
                system("cls");
                printf("FCODE    SOURCE    DESTINATION    DEPARTURE    ARRIVAL    DAY    FARES\n");
                printf("                                                  FIRST    BUSINESS  ECONOMY\n");
                for (int i=0;i<n;i++)
                {
                    disp(i,allflight);
                }
                getchar();
                getchar();
                admin_menu(n,allflight);
                break;

        // case '6':    system("clear");
        //     user_det_view_particular();
        //     admin_menu();
        //     break;


        case '6':    system("cls");
            user_det_view_all();
            admin_menu(n,allflight);
            break;


        case '7':    
                system("cls");
                break;

        default:    admin_menu(n,allflight);
    }
}

/*  To get the password from the keyboard.
Uses pass by reference to get the entered password
via parameter to function  */

void getPassword(char *pass)
{
    char ch;
      int len=0;

    while((ch=getchar())!='\n')
      {
        printf("*");

        pass[len]=ch;
        len++;
      }

    pass[len]='\0';
}


// void admin_add()
// {
// a=fopen("admin_det.bin","wb");
// admin alldet[3];
// alldet[0].code=123;
// strcpy(alldet[0].pw,"abc");
// alldet[1].code=456;
// strcpy(alldet[1].pw,"def");
// alldet[2].code=789;
// strcpy(alldet[2].pw,"ghi");
// fwrite(alldet, sizeof(admin), 3, a);
// fclose(a);
// }


int check(admin det)
{
// int count;
// a=fopen("admin_det.bin","rb");
// fseek(a, 0, SEEK_END);
// count=ftell(a)/sizeof(admin);
// admin alldet[count];
// fseek(a, 0, SEEK_SET);
// fread(alldet, sizeof(admin), count, a);
// for(int i=0;i<count;i++)
//     if (det.code==alldet[i].code && strcmp(det.pw,alldet[i].pw)==0)
//         return det.code;
    char usn[15]="ad";
    char pw[15]="ad";
    if(strcmp(det.code,usn)==0 && strcmp(det.pw,pw)==0){
        return 1;
    }
    return 0;
}


void admin_login()
{
    system("cls");
    admin det;

    char user[15];
    char pass[30];

    printf("\n\n\n\t\tADMIN LOGIN");
    printf("\n\n\n\t\tUsername: ");
    scanf("%s",det.code);
    getchar();
    printf("\t\tPassword: ");
    getPassword(det.pw);
    if (check(det)){
        struct flight_det allflight[450];
        int n=read_det(allflight);
        admin_menu(n,allflight);
    }
    else
    {
        printf("\n\n\n\t\tLOGIN FAILED....!!!!");
        getchar();
    }
}

void user_det_input()
{
    FILE *fptr= fopen("user.csv", "a");
    struct user_details user;

    printf("\n\n\n\tSIGNUP\n\n");
    printf("\tNEW USER ACCOUNT ENTRY\n\n");
    getchar();
    printf("\tUSERNAME: ");
    scanf("%[^\n]", user.username);
    getchar();
    printf("\tPASSWORD: ");
    scanf("%[^\n]", user.password);
    getchar();
    printf("\n\tName: ");
    scanf("%[^\n]", user.name);
    getchar();
    // printf("\n\tAddress:\n");
    // printf("\tStreet: ");
    // scanf(" %[^\n]", user.address.street);

    // printf("\tCity: ");
    // scanf(" %[^\n]", user.address.city);

    // printf("\tPincode: ");
    // scanf(" %[^\n]", user.address.pincode);

    // printf("\tState: ");
    // scanf(" %[^\n]", user.address.state);

    // printf("\n\tNationality: ");
    // scanf(" %[^\n]", user.nationality);

    // printf("\tMobile: ");
    // scanf(" %[^\n]", user.mobile);

    // printf("\tEmail ID: ");
    // scanf(" %[^\n]", user.email);

    // printf("\n\tEnter DATE in dd mm yyyy FORMAT\n");
    // printf("\tDate of birth: ");
    // scanf("%d %d %d", &user.dob.day, &user.dob.month, &user.dob.year);

    // printf("\n\tAge: ");
    // scanf("%d", &user.age);

    // printf("\n\tF: Female M: Male T:Transgender O:Other\n");
    // printf("\tGender: ");
    // scanf(" %c", &user.gender);
    
    fprintf(fptr,"%s,%s,%s\n",user.username,user.password,user.name);

    fclose(fptr);


    printf("\n\n\n\tNEW USER ACCOUNT ENTRY SUCCESSFULL......!!!!!\n");

    getchar();

}

void user_login()
{
    system("cls");
    char pass[30];
    struct user_details all_users[100];
    int count=0, index=-1;

    printf("\n\n\tUSER LOGIN");

    count=read_count_users(all_users);
    index=search_users(count, all_users);

    if(index==-1)
    {
        printf("\n\n\n\tUSERNAME INVALID....!!!!");
        getchar();
    }

    else
    {
        printf("\n\tPassword: ");
        getPassword(pass);

        if(strcmp(all_users[index].password, pass)==0)
            user_menu(count,all_users,index);

        else
        {
            printf("\n\n\n\tLOGIN FAILED....!!!!");
            getchar();
        }

    }

}

void user_terminal()
{
    char ch;

    system("cls");

    do
    {    
        system("cls");
        printf("\n\n\n\tSNL AIRLINE BOOKING");
        printf("\n\n\t1. LOGIN");
        printf("\n\n\t2. SIGNUP");
        printf("\n\n\t3. BACK TO MAIN MENU ");

        printf("\n\n\tEnter choice: ");
        scanf("%c",&ch);

        switch(ch)
        {
            case '1':    system("cls");
                    user_login();
                    break;

            case '2':    system("cls");
                    user_det_input();
                    break;

            case '3':    system("cls");
                    break;
        }
    }while(ch!='3');

}

void ticket_view_pnr(long long int pnr)
{
    printf("TICKET DETAILS");
    ticket tickets[150];
    FILE *fptr= fopen("bookings.csv", "r");
    char buffer[1024];
    
    int row = 0;
    int column = 0;
 
    while (!feof(fptr)){
        fgets(buffer,1024,fptr);
        column = 0;
        char* tmp = strdup(buffer);
        long long int val = (long long int) *getfield(tmp,2);
        if(val != pnr){
            free(tmp);
            row++;
            continue;
        }
        free(tmp);
        char* value = strtok(buffer, ",");
        while(value != NULL){
            if (column == 0) {
                    printf("Username: %s\n",value);
                }
            else if (column == 1) {
                    printf("PNR: %s\n",value);
            }
            else if (column == 2) {
                    printf("Source: %s\n",place[(enum places) convertstf(value)]);
            }
            else if (column == 3) {
                    printf("Destination: %s\n",place[(enum places) convertstf(value)]);
            }
            else if (column == 4) {
                    printf("FCode: %s\n",value);

            }
            else if (column == 5) {
                printf("Date: %s",value);
            }
            else if (column == 6) {
                printf("Class: %s",value);
            }
            value = strtok(NULL, ",");
            column++;
        }
        row++;
    }
    fclose(fptr);
}

void ticket_view_usn(char* usn)
{
    printf("TICKET DETAILS");
    ticket tickets[150];
    FILE *fptr= fopen("bookings.csv", "r");
    char buffer[1024];
    char* value;
    int row = 0;
    int column = 0;
    char *val,*tmp;
 
    while(!feof(fptr)){
        fgets(buffer,1024,fptr);
        column = 0;
        tmp = strdup(buffer);
        val = getfield(tmp,1);
        if(!(strcmp(val,usn)==0)){
            free(tmp);
            row++;
            continue;
        }
        free(tmp);
        value = strtok(buffer, ",");
        while(value != NULL){
            if (column == 0) {
                    printf("Username: %s\n",value);
                }
            else if (column == 1) {
                    printf("PNR: %s\n",value);
            }
            else if (column == 2) {
                    printf("Source: %s\n",place[(enum places) convertstf(value)]);
            }
            else if (column == 3) {
                    printf("Destination: %s\n",place[(enum places) convertstf(value)]);
            }
            else if (column == 4) {
                    printf("FCode: %s\n",value);

            }
            else if (column == 5) {
                printf("Date: %s\n",value);
            }
            else if (column == 6) {
                printf("Class: %s\n",value);
            }
            value = strtok(NULL, ",");
            column++;
        }
        row++;
    }
    getchar();
    getchar();
    fclose(fptr);
}
    
void ticket_del_pnr(int pnr)
{
    ticket tickets[150];

    printf("\n\n\n\tCancel Ticket\n\n");

    FILE *fptr= fopen("bookings.csv", "r");
    FILE *fptr1= fopen("bookings1.csv", "w");
    char buffer[1024];
    int row = 0;
    int column = 0;
    int flag = 0;

    while (!feof(fptr)){
        fgets(buffer,1024,fptr);
        column = 0;
        char* tmp = strdup(buffer);
        long long int val = (long long int) *getfield(tmp,2);
        if(val == pnr){
            flag = 1;
            free(tmp);
            continue;
        }
        free(tmp);
        char* value = strtok(buffer, ",");
        while(value != NULL){
            if (column == 0) {
                    strcpy(tickets[row].username,value);
                }
            else if (column == 1) {
                    tickets[row].pnr = (long long int) convertstf(value);
            }
            else if (column == 2) {
                    tickets[row].source = (enum places) convertstf(value);
            }
            else if (column == 3) {
                    tickets[row].dest = (enum places) convertstf(value);
            }
            else if (column == 4) {
                    strcpy(tickets[row].fcode,value);
            }
            else if (column == 5) {
                tickets[row].flight_date.day = ((int)value[0]-48)*10+(int)value[1]-48;
                tickets[row].flight_date.month = ((int)value[3]-48)*10+(int)value[4]-48;
                tickets[row].flight_date.day = ((int)value[6]-48)*10+(int)value[7]-48;
            }
            else if (column == 6) {
                tickets[row].tclass = convertstf(value);
            }
            value = strtok(NULL, ",");
            column++;
        }
        fprintf(fptr1,"%s,%lld,%u,%u,%s,%d/%d/%d,%d\n",tickets[row].username,tickets[row].pnr,tickets[row].source,tickets[row].dest,tickets[row].fcode,tickets[row].flight_date.day,tickets[row].flight_date.month,tickets[row].flight_date.year,tickets[row].tclass);
        row++;
    }
    
    fclose(fptr);
    fclose(fptr1);
    if(flag==0){
        printf("PNR Invalid\n");
        getchar();
        return;
    }
    if(remove("bookings.csv")){
        rename("bookings1.csv","bookings.csv");
    }
}


int main()
{
    char ch;
    intro();
    // admin_add();

    do
    {    
        system("cls");
        system("color 30");
        printf("\n\n\n\tMAIN MENU");
        printf("\n\n\t1. USER");
        printf("\n\n\t2. ADMINISTRATOR");
        printf("\n\n\t3. EXIT");

        printf("\n\n\n\n\tEnter choice: ");
        scanf("%c", &ch);
        switch(ch)
        {
            case '1':    system("cls");
                    user_terminal();
                    break;

            case '2':    system("cls");
                    admin_login();
                    break;

            case '3':    return 0;
        }
    }while(ch!='3');
}


