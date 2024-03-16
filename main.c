#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARRlength 10

//definition for struct and enum----------------------------------------------------------------------------------------------------------------------------------------------------------------------

    struct appointment{
    int type;
    int time;
    int duration;
    };

    enum type{
    friends,
    buisness,
    pause
    };


//function to print appointments ---------------------------------------------------------------------------------------------------------------------------------------------------------------------

void printAppointments(struct appointment * schedule, int length){

        for(int i = 0; i < length; i++){
            if(schedule[i].type == 0){
                printf("\n%d: Freunde: %d Uhr, Dauer %dh", i+1, schedule[i].time, schedule[i].duration);
            }else if(schedule[i].type == 1){
                printf("\n%d: Geschaeftlich: %d Uhr, Dauer %dh", i+1, schedule[i].time, schedule[i].duration);
            }else if(schedule[i].type == 2){
                printf("\n%d: Pause: %d Uhr, Dauer %dh", i+1, schedule[i].time, schedule[i].duration);
            }
        }
}


//function to create appointments (used in addAppointment) -------------------------------------------------------------------------------------------------------------------------------------------

struct appointment createAppointment(){

    struct appointment newInput;
    char appoType;
    int time = 0;
    int diffTime = 0;
    int duration = 0;

        while(appoType != 'f' || appoType != 'b' || appoType != 'p'){
            printf("\nGib einen Typen ein: Freunde (f), Geschaeftlich (b), Pause (p): ");
            scanf(" %c", &appoType);

                if(appoType == 'f'){
                    newInput.type = friends;
                    break;
                }else if(appoType == 'b'){
                    newInput.type = buisness;
                    break;
                }else if(appoType == 'p'){
                    newInput.type = pause;
                    break;
                }else{
                    printf("\nUngueltige Eingabe!");
                }
        }

        while(time < 8 || time > 21){
            printf("\nGib eine Uhrzeit ein (8-21): ");
            scanf(" %d", &time);

                if(time < 8 || time > 21){
                    printf("\nUngueltige Eingabe!");
                }else{
                    newInput.time = time;
                }
        }

        diffTime = 22 - time;

            while(duration < 1 || duration > diffTime){
                printf("\nGib eine Dauer ein (1-%d): ", diffTime);
                scanf(" %d", &duration);

                    if(duration < 1 || duration > diffTime){
                        printf("\nUngueltige Eingabe!");
                    }else{
                        newInput.duration = duration;
                    }
            }

return newInput;

}


//function to add an appointment----------------------------------------------------------------------------------------------------------------------------------------------------------------------

void addAppointment(struct appointment * schedule, int * length){



        if(schedule[*length].type == 0 && schedule[*length].time == 0 && schedule[*length].duration == 0){
            schedule[*length] = createAppointment(schedule);
        }else{
            printf("\nDer Kalender ist voll!");
        }

}


//function to print informations about the appointments (check duration, check breaks)----------------------------------------------------------------------------------------------------------------

void printInformation(struct appointment * schedule, int length){

    int endAppo = 0;
    int countFriends = 0;
    int countBuisness = 0;
    int countPause = 0;
    int breakCount = 0;

        //check duration and suggest cancellation
        for(int i = 0; i <= length; i++){
            endAppo = schedule[i].time + schedule[i].duration;

                if(schedule[i+1].time < endAppo && schedule[i+1].time != 0){
                    printf("\nEntweder Termin %d oder Termin %d sollte abgesagt werden.", i+1, i+2);
                    breakCount++;
                }else if(i == length && breakCount == 0){
                    printf("\nDer Kalender hat keine Kollisionen!");
                }
        }

        //check breaks and suggest one of them
        for(int i = 0; i <= length; i++){
            if(schedule[i].type == 0 && schedule[i+1].type != 2 && schedule[i+1].time != 0){
                printf("\nZwischen Termin %d und %d wird eine Pause benoetigt.", i+1, i+2);
            }else if(schedule[i].type == 1 && schedule[i+1].type != 2 && schedule[i+1].time != 0){
                printf("\nZwischen Termin %d und %d wird eine Pause benoetigt.", i+1, i+2);
            }
        }

        //counter for printf
        for(int i = 0; i < length; i++){
            if(schedule[i].type == friends){
                countFriends++;
            }else if(schedule[i].type == buisness){
                countBuisness++;
            }else if(schedule[i].type == pause){
                countPause++;
            }
        }

        printf("\nSie haben %d Geschaeftstermin(e), %d Termin(e) mit Freunden und %d Pause(n) in Ihrem Kalender.", countBuisness, countFriends, countPause);
}


//function to sort the appointments after their begining----------------------------------------------------------------------------------------------------------------------------------------------

struct appointment sortAppointment(struct appointment * appoArray){

    int tempSortTime = 0;
    int tempSortType = 0;
    int tempSortDuration = 0;

            for(int i = 0; i < ARRlength; i++){
                for(int z = 0; z < ARRlength; z++){
                    if((appoArray[z].time > appoArray[z+1].time) && (appoArray[z].time != 0) && (appoArray[z+1].time != 0)){
                        tempSortType = appoArray[z].type;
                        tempSortTime = appoArray[z].time;
                        tempSortDuration = appoArray[z].duration;
                        appoArray[z].type = appoArray[z+1].type;
                        appoArray[z].time = appoArray[z+1].time;
                        appoArray[z].duration = appoArray[z+1].duration;
                        appoArray[z+1].type = tempSortType;
                        appoArray[z+1].time = tempSortTime;
                        appoArray[z+1].duration = tempSortDuration;
                    }
                }
            }

return *appoArray;
}


//function to delete an appointment (if there is an appointment)--------------------------------------------------------------------------------------------------------------------------------------

void deleteAppointment(struct appointment * schedule, int * length){

    int deleteInput = 0;

            //check if appointments are empty
            if(schedule[0].time == 0 && schedule[1].time == 0){
                printf("\nDer Kalender ist leer!");
                return;
            }else{
                sortAppointment(schedule);
                printAppointments(schedule, *length);
            }

            //choose which appointment you want to delete
            printf("\nWelchen dieser Termine moechten Sie loeschen? (%d-%d): ", (*length / *length), *length);
                while(deleteInput < 1 || deleteInput > *length){
                    scanf("%d", &deleteInput);
                        if(deleteInput < 1 || deleteInput > *length){
                            printf("Ungueltige Eingabe!");
                        }
                }

            //delete the choosen appointment
            for(int i = 0; i < *length; i++){
                if(deleteInput == i+1){
                    schedule[i].type = schedule[*length-1].type;
                    schedule[i].time = schedule[*length-1].time;
                    schedule[i].duration = schedule[*length-1].duration;
                    schedule[*length-1].type = 0;
                    schedule[*length-1].time = 0;
                    schedule[*length-1].duration = 0;
                    *length = *length -1;
                    printf("\nTermin %d wurde geloescht!", deleteInput);
                    break;
                }

            }
}


//main function with menu options---------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
    char menuInput = ' ';
    int appoLength = 0;

    struct appointment appoArray [10] = {{0, 0, 0}};


        while(1){

        //choose a menu option
            printf("\nNeuen Termin (n), Termin loeschen (d), Termine auflisten (l), Informationen ausgeben (i), Programm beenden (x)");
            printf("\nAuswahl:");
            scanf(" %c", &menuInput);


                if(menuInput == 'n'){//add a new appointment (n)
                    addAppointment(appoArray, &appoLength);
                    appoLength++;
                }else if(menuInput == 'l'){ //list appointments (l)
                    sortAppointment(appoArray);
                    printAppointments(appoArray, appoLength);
                }else if(menuInput == 'i'){ //give some information about the appointments (i)
                    sortAppointment(appoArray);
                    printInformation(appoArray, appoLength);
                }else if(menuInput == 'd'){ //delete an appointment (d)
                    deleteAppointment(appoArray, &appoLength);
                }else if(menuInput == 'x'){//exit
                    break;
                }else{ //check the menuinput
                    printf("\nUngueltige Eingabe!");
                }
        }

    return 0;
}
