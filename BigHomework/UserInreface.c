#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "DEF.h"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

enum functions {Consult,AddCity,DeleteCity,AddTrainRoute,DeleteTrainRoute,AddPlaneRoute,DeletePlaneRoute,ChangeTrain,
                ChangePlane,Exit};

/*
功能：读一行命令
输入：一个字符数组
输出：把读到的这行命令存在这个字符数组里，以'\0'结尾
*/
Status ReadLine(char * command){
    char c;
    int i = 0;
    while((c=getchar())!='\n'){
        command[i++] = c|0x20; //转成小写
    }
    command[i] = '\0';
    return OK;
}

/*
功能：从command字符数组里读取 下标 从startIndex起(包括startIndex处的字符)的第一个单词
输入：Opcode --- 存放读到的单词；command --- 被读取的数组；startIndex --- 起始地址
输出：读取完后的第一个空格的下标
*/
int ReadWord(char * Opcode,char *command,int startIndex){
    int i = startIndex,j=0;
    while(command[i]==' ') i++;         //跳过开始的空格
    for(;command[i]!=' ' && command[i]!='\0' && command[i]!='\n';i++,j++) Opcode[j] = command[i];
    Opcode[j] = '\0';
    return i;
}

int OperationOfCommand(char * command){
    if(!command) return ERROR;
    char OpCode[MAX_CMD_LEN];
    int lenOfOpCode = ReadWord(OpCode,command,0);   //从command命令里读取第一个单词
    if(strcmp(OpCode,"find")==0){
        return Consult;
    }else if(strcmp(OpCode,"exit")==0 || strcmp(OpCode,"quit")==0 || strcmp(OpCode,"q")==0){
        return Exit;
    }else if(strcmp(OpCode,"add")==0){
        char OpFunct[MAX_CMD_LEN/2];
        int endIndexOfOpFunct = ReadWord(OpFunct,command,lenOfOpCode);
        //分析功能
        if(strcmp(OpFunct,"-t")==0) return AddTrainRoute;
        else if(strcmp(OpFunct,"-p")==0) return AddPlaneRoute;
        else if(strcmp(OpFunct,"-c")==0) return AddCity;
        else return ERROR;
        //else return ErrorHandle(command);
    }else if(strcmp(OpCode,"delete")==0){
        char OpFunct[MAX_CMD_LEN/2];
        int endIndexOfOpFunct = ReadWord(OpFunct,command,lenOfOpCode);
        //分析功能
        if(strcmp(OpFunct,"-t")==0) return DeleteTrainRoute;
        else if(strcmp(OpFunct,"-p")==0) return DeletePlaneRoute;
        else if(strcmp(OpFunct,"-c")==0) return DeleteCity;
        else return ERROR;
        //else return ErrorHandle(command);
    }else if(strcmp(OpCode,"change")==0){
        char OpFunct[MAX_CMD_LEN/2];
        int endIndexOfOpFunct = ReadWord(OpFunct,command,lenOfOpCode);
        //分析功能
        if(strcmp(OpFunct,"-t")==0) return ChangeTrain;
        else if(strcmp(OpFunct,"-p")==0) return ChangePlane;
        else return ERROR;
        //else return ErrorHandle(command);
    }else
        return ERROR;
        //else return ErrorHandle(command);
}

int ReadDest(char *dest,char *command){
    char tem[MAX_CMD_LEN];
    int index = ReadWord(tem,command,0);

    if(strcmp(tem,"find")==0){
        int lastIndexOfDestPlusOne = ReadWord(dest,command,index);
        return lastIndexOfDestPlusOne;
    }else{
        int nextWordStartPos = ReadWord(tem,command,index);
        int lastIndexOfDestPlusOne = ReadWord(dest,command,nextWordStartPos);
        return lastIndexOfDestPlusOne;
    }
}

int ReadFunct(char *command,int functPos){
    char funct[5];
    ReadWord(funct,command,functPos);
    if(funct[0]=='\0') return -1;
    else return funct[0]-'0';
}

int ReadTime(char *command,int pos,int *time){
    char T[10];
    int retpos = ReadWord(T,command,pos);
    printf("T = %s\n",T);
    int i = 0;
    int t = 0;
    for(;T[i]!='\0';i++){
        if(T[i]>='0'&&T[i]<='9'){
            t = t*10 + T[i]-'0';
        }
    }
    (*time) = t;
    return retpos;
}


Status UserInterface(void){
    printf(ANSI_COLOR_GREEN "Welcome to National Traffic Consult System\n" ANSI_COLOR_RESET);
    while (1){
        printf(ANSI_COLOR_GREEN "National Traffic Consult >> " ANSI_COLOR_RESET);

        char command[MAX_CMD_LEN];
        //读一行命令
        ReadLine(command);
        //得到指令的功能
        int OptOfCommand = OperationOfCommand(command);
        //根据功能的编号执行选中的功能
        switch (OptOfCommand){
        case Consult:{
            char dest[MAX_CITY_SIZE];
            char start[MAX_CITY_SIZE];
            int functOfConsult = -1; //-1:全部输出 0:输出最少时间的方案 1:输出最少中转次数的方案 2: 输出最少旅费的方案
            int startPos = ReadDest(dest,command);
            int functPos = ReadWord(start,command,startPos);
            functOfConsult = ReadFunct(command,functPos);
            int succ = consultPath(dest,start,functOfConsult); //输出由该函数内部处理
            if(!succ) printf(">> Failed to consult.\n");
            break;
        }
        case Exit: printf(">> Exiting National Traffic Consult ...\n"); return OK; break;
        case AddCity:{
            char dest[MAX_CITY_SIZE];
            int startPos = ReadDest(dest,command);

            int succ = addCity(dest);
            if(succ==0) printf(">> Add City failed.\n",dest);
            else printf(">> Add City successfully.\n");
            break;
        }
        case AddPlaneRoute:{
            char dest[MAX_CITY_SIZE];
            char start[MAX_CITY_SIZE];
            int startPos = ReadDest(dest,command);
            int startTimePos = ReadWord(start,command,startPos);

            int startTime;
            int endTimePos = ReadTime(command,startTimePos,&startTime);
            int endTime;
            ReadTime(command,endTimePos,&endTime);

            int succ = addPlaneRoute(dest,start,startTime,endTime);
            if(succ) printf(">> Add Plane Route successfully.\n");
            else printf(">> Add Plane Route failed.\n");
            break;
        }
        case AddTrainRoute:{
            char dest[MAX_CITY_SIZE];
            char start[MAX_CITY_SIZE];
            int startPos = ReadDest(dest,command);
            int startTimePos = ReadWord(start,command,startPos);

            int startTime;
            int endTimePos = ReadTime(command,startTimePos,&startTime);
            int endTime;
            ReadTime(command,endTimePos,&endTime);

            int succ = addTrainRoute(dest,start,startTime,endTime);
            if(succ) printf(">> Add Train Route successfully.\n");
            else printf(">> Add Train Route failed.\n");
            break;
        }
        case DeleteCity:{
            char dest[MAX_CITY_SIZE];
            int startPos = ReadDest(dest,command);
            int succ = deleteCity(dest);
            if(succ==0) printf(">> Delete City failed.\n",dest);
            else printf(">> Delete City successfully.\n");
            break;
        }
        case DeleteTrainRoute:{
            char dest[MAX_CITY_SIZE];
            char start[MAX_CITY_SIZE];
            int startPos = ReadDest(dest,command);
            int startTimePos = ReadWord(start,command,startPos);

            int startTime;
            int endTimePos = ReadTime(command,startTimePos,&startTime);
            int endTime;
            ReadTime(command,endTimePos,&endTime);

            int succ = deleteTrainRoute(dest,start,startTime,endTime);
            if(succ) printf(">> Delete Train Route successfully.\n");
            else printf(">> Delete Train Route failed.\n");
            break;
        }
        case DeletePlaneRoute:{
            char dest[MAX_CITY_SIZE];
            char start[MAX_CITY_SIZE];
            int startPos = ReadDest(dest,command);
            int startTimePos = ReadWord(start,command,startPos);

            int startTime;
            int endTimePos = ReadTime(command,startTimePos,&startTime);
            int endTime;
            ReadTime(command,endTimePos,&endTime);

            int succ = deletePlaneRoute(dest,start,startTime,endTime);
            if(succ) printf(">> Delete Plane Route successfully.\n");
            else printf(">> Delete Plane Route failed.\n");
            break;
        }
        case ChangeTrain:{
            char dest[MAX_CITY_SIZE];
            char start[MAX_CITY_SIZE];
            int startPos = ReadDest(dest,command);
            int startTimePos = ReadWord(start,command,startPos);

            int startTime;
            int endTimePos = ReadTime(command,startTimePos,&startTime);
            int endTime;
            ReadTime(command,endTimePos,&endTime);

            int succ = changeTrain(dest,start,startTime,endTime);    //该函数继续与用户交互询问具体信息
            if(succ) printf(">> Change Train successfully.\n");
            else printf(">> Change Train failed.\n");
            break;
        }
        case ChangePlane:{
            char dest[MAX_CITY_SIZE];
            char start[MAX_CITY_SIZE];
            int startPos = ReadDest(dest,command);
            int startTimePos = ReadWord(start,command,startPos);

            int startTime;
            int endTimePos = ReadTime(command,startTimePos,&startTime);
            int endTime;
            ReadTime(command,endTimePos,&endTime);

            int succ = changePlane(dest,start,startTime,endTime);    //该函数继续与用户交互询问具体信息
            if(succ) printf(">> Change Plane successfully.\n");
            else printf(">> Change Plane failed.\n");
            break;
        }
        default: continue; //break;
        }
    }
    return OK;
}

