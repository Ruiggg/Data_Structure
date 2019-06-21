#ifndef DEF_H_INCLUDED
#define DEF_H_INCLUDED

#define OK 1
#define ERROR -1
#define OVERFLOW -2
#define MAX_CMD_LEN 100
#define MAX_CITY_SIZE 20
typedef int Status;

Status UserInterface(void);
Status consultPath(char *dest,char *start,int type);
int addCity(char *dest);
int addPlaneRoute(char *dest,char *start);
int addTrainRoute(char *dest,char *start);
int deleteCity(char *dest);
int deleteTrainRoute(char *dest,char *start);
int deletePlaneRoute(char *dest,char *start);
int changeTrain(char *dest,char *start);
int changePlane(char *dest,char *start);


#endif // DEF_H_INCLUDED
