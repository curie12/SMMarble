//
//  smm_node.c
//  SMMarble
//
//  Created by Juyeop Kim on 2023/11/05.
//

#include "smm_common.h"
#include "smm_object.h"
#include <string.h>

#define MAX_NODETYPE    7
#define MAX_GRADE       9
#define MAX_NODE        100


static char smmNodeName[SMMNODE_TYPE_MAX][MAX_CHARNAME] = {
       "강의",
       "식당",
       "실험실",
       "집",
       "실험실로이동",
       "음식찬스",
       "축제시간"
};
char* smmObj_getTypeName(int type)
{
      return (char*)smmNodeName[type];
}
/* grade :
    A+,
    A0,
    A-,
    B+,
    B0,
    B-,
    C+,
    C0,
    C-
*/
/*typedef enum smmObjGrade {
    smmObjGrade_Ap = 0,
    smmObjGrade_A0,
    smmObjGrade_Am,
    smmObjGrade_Bp,
    smmObjGrade_B0,
    smmObjGrade_Bm,
    smmObjGrade_Cp,
    smmObjGrade_C0,
    smmObjGrade_Cm
} smmObjGrade_e;*/


//1. 구조체 형식 정의 
typedef struct smmObject
{
      char name[MAX_CHARNAME];
      smmObjType_e objType;
      int type;
      int credit;
      int energy;
      smmObjGrade_e grade;
} smmObject_t;   
//2. 구조체 배열 변수 정의
//static smmObject_t smm_node[MAX_NODE];
//static int smmObj_noNode=0;

//3. 관련 함수 변경 
//object generation
void* smmObj_genObject(char* name, smmObjType_e objType, int type, int credit, int energy, smmObjGrade_e grade)
{    
    smmObject_t* ptr;

    ptr = (smmObject_t*)malloc(sizeof(smmObject_t));

    strcpy(ptr->name, name);
    ptr->objType = objType;
    ptr->type = type;
    ptr->credit = credit;
    ptr->energy = energy;
    ptr->grade = grade;

    return ptr;
}

//3. 관련 함수 변경 
char* smmObj_getNodeName(void* obj)
{
    smmObject_t* ptr = (smmObject_t*)obj;

    return ptr->name;
}

//3. 관련 함수 변경 
int smmObj_getNodeType(void* obj)
{
    smmObject_t* ptr = (smmObject_t*)obj;

    return ptr->type;
}
int smmObj_getNodeCredit(void* obj)
{
    smmObject_t* ptr = (smmObject_t*)obj;

    return ptr->credit;
}
int smmObj_getNodeEnergy(void* obj)
{
    smmObject_t* ptr = (smmObject_t*)obj;
    
    return ptr->energy;
}

#if 0
int smmObj_getNodeType(int node_nr)
{
    return smm_node[node_nr].type;
}
int smmObj_getNodeCredit(int node_nr)
{
    return smm_node[node_nr].credit;
}
int smmObj_getNodeEnergy(int node_nr)
{
    return smm_node[node_nr].energy;
}


//member retrieving 검색중 

//element to string
char* smmObj_getNodeName(smmNode_e type)
{
    return smmNodeName[type];
}

char* smmObj_getGradeName(smmGrade_e grade)
{
    return smmGradeName[grade];
}

#endif

