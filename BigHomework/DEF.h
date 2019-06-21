#ifndef DEF_H_INCLUDED
#define DEF_H_INCLUDED

#define OK 1
#define ERROR -1
#define OVERFLOW -2
#define MAX_CMD_LEN 100
#define MAX_CITY_SIZE 20
typedef int Status;

int UserInterface(void);

int consultPath(char *dest,char *start,int type);
int addCity(char *dest);
int addPlaneRoute(char *dest,char *start,int startTime,int endTime);
int addTrainRoute(char *dest,char *start,int startTime,int endTime);
int deleteCity(char *dest);
int deleteTrainRoute(char *dest,char *start,int startTime,int endTime);
int deletePlaneRoute(char *dest,char *start,int startTime,int endTime);
int changeTrain(char *dest,char *start,int startTime,int endTime);
int changePlane(char *dest,char *start,int startTime,int endTime);


#endif // DEF_H_INCLUDED
