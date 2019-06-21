#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "DEF.h"
//all small write
Status consultPath(char *dest,char *start,int type){
    if(type==-1){
        printf("Path-0: %s->Beijing->%s\n",start,dest);
        printf("Path-1: %s->ZhengZhou->%s\n",start,dest);
        printf("Path-2: %s->XingCheng->%s\n",start,dest);
    }else{
        printf("Path: %s->Mars->Hell->%s\n",start,dest);
    }
    return OK;
}

int addCity(char *dest){
    printf("Hit add city\n");
    if(strcmp(dest,"beijing")==0) return 1;
    else return 0;
}

int addPlaneRoute(char *dest,char *start,int startTime,int endTime){
    printf("hit add plane route\n");
    printf("start time : %d\n",startTime);
    printf("end time: %d\n",endTime);
    return 0;
}

int addTrainRoute(char *dest,char *start,int startTime,int endTime){
    printf("hit add train route\n");
    return 0;
}

int deleteCity(char *dest){
    printf("hit add city\n");
    return addCity(dest);
}

int deleteTrainRoute(char *dest,char *start,int startTime,int endTime){
    printf("hit del train route\n");
    return 0;
}

int deletePlaneRoute(char *dest,char *start,int startTime,int endTime){
    printf("hit del plane route\n");
    return 0;
}

int changeTrain(char *dest,char *start,int startTime,int endTime){
    printf("hit change train\n");
    return 0;
}

int changePlane(char *dest,char *start,int startTime,int endTime){
        printf("hit change plane route\n");
return OK;}
