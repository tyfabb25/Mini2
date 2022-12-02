#include <stdio.h>
#include <string.h>
#include <math.h>
FILE *std;
struct user_t
{
    double latitude;
    double longtitude;
    double altitude;
    double time;
    char name[20];
};
struct userdistance{
    double distance;
    char name[20];
};

struct user_t scan_data(struct user_t person){
    printf("enter the users data, (lat long alt time name)");
    scanf("%ld %ld %ld %ld %s", &person.latitude, &person.longtitude, &person.altitude, &person.time, &person.name);
    return person;
}
struct userdistance distance_data(struct user_t ourperson, struct user_t otherperson){
    struct userdistance distancestuff;
    strcpy(distancestuff.name, otherperson.name);
    distancestuff.distance = (((ourperson.latitude - otherperson.latitude)*(ourperson.latitude - otherperson.latitude)) + ((ourperson.longtitude - otherperson.longtitude)*(ourperson.longtitude - otherperson.longtitude)) + ((ourperson.altitude - otherperson.altitude)*(ourperson.altitude - otherperson.altitude)));
    printf("%lf", distancestuff.distance);
    return distancestuff;
}
struct userdistance closestuser(struct userdistance usercloser, struct userdistance userchallenge[], int i, int max){
    //printf("%s", usercloser.name);
    //printf("%ld %ld", usercloser.distance, userchallenge[i].distance);
    if(i != max - 1){
    if(usercloser.distance < userchallenge[i].distance){
        closestuser(usercloser, userchallenge, i+1, max);
    }
    else{
        closestuser(userchallenge[i], userchallenge, i+1, max);
    }
    }
    else{
    if(usercloser.distance < userchallenge[i].distance){
        return(usercloser);
    }
    else{
        return(userchallenge[i]);
    }
    }
}

void fileReader(FILE *readFile, struct user_t user_o[], struct user_t* use_1){
    int x; fscanf(readFile,"%i", &x);
    char name[10];
    int time;
    double lng, lat, alt;
    fscanf(readFile,"%s", name);
    fscanf(readFile,"%i", &time);
    fscanf(readFile,"%lf", &lng);
    fscanf(readFile,"%lf", &lat);
    fscanf(readFile,"%lf", &alt);
    strcpy((*use_1).name, name);
    (*use_1).time=time;
    (*use_1).longtitude = lng;
    (*use_1).latitude = lat;
    (*use_1).altitude = alt;

    for(int y=0;y<x;y++){
        fscanf(readFile,"%s", name);
        fscanf(readFile,"%i", &time);
        fscanf(readFile,"%lf", &lng);
        fscanf(readFile,"%lf", &lat);
        fscanf(readFile,"%lf", &alt);
        strcpy(user_o[y].name, name);
        user_o[y].time=time;
        user_o[y].longtitude = lng;
        user_o[y].latitude = lat;
        user_o[y].altitude = alt;
    }

}

void difference(struct user_t user_o[], struct user_t use_1, double array[],int size){
    for(int y=0;y<size;y++){
        array[y]=sqrt(((use_1.altitude-user_o[y].altitude)*(use_1.altitude-user_o[y].altitude))+((use_1.latitude-user_o[y].latitude)*(use_1.latitude-user_o[y].latitude))+((use_1.longtitude-user_o[y].longtitude)*(use_1.longtitude-user_o[y].longtitude)));
    }
    printf("%lf %lf %lf", array[0], array[1], array[2]);
}

int main(void){
    char txt; //user input for text or manual input
    int othernum; //user input for otheruser count
        int size; fscanf(std,"%i",&size);
        fclose(std);
        struct user_t arr[size];
        double arrdis[size];
        fileReader(fopen("file.txt", "r"),arr,&our_user);
       
        printf("%s %s %s %s", our_user.name,arr[0].name, arr[1].name,arr[2].name);
        difference(arr,our_user,arrdis,size);
    }
    if (txt == 'n' || txt == 'N')
    {
        printf("Our_user: ");
        our_user = scan_data(our_user);
        printf("How many other users are you inputting?");
        scanf(" %d", &othernum);
        struct user_t other_users[othernum];
        struct userdistance distanceothers[othernum];
        for(int i = 0; i < othernum; i++){
            printf("user %d: ", (i+1));
            other_users[i] = scan_data(other_users[i]);
            distanceothers[i] = distance_data(our_user, other_users[i]);
        }
        struct userdistance nearestuser = closestuser(distanceothers[0],distanceothers,1,othernum);
    }

