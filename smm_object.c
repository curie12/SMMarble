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

typedef enum smmObjGrade {
    smmObjGrade_Ap = 0,
    smmObjGrade_A0,
    smmObjGrade_Am,
    smmObjGrade_Bp,
    smmObjGrade_B0,
    smmObjGrade_Bm,
    smmObjGrade_Cp,
    smmObjGrade_C0,
    smmObjGrade_Cm
} smmObjGrade_e;


//1. 구조체 형식 정의 
typedef struct smmObject
{
      char name[MAX_CHARNAME];
      int type;
      int credit;
      int energy;
} smmObject_t;   
//2. 구조체 배열 변수 정의
static smmObject_t smm_node[MAX_NODE];

static int smmObj_noNode=0;

//3. 관련 함수 변경 
//object generation-구조체 정의 
void smmObj_genNode(char* name, int type, int credit, int energy)//이름, 강의, 학점, 에너지 구조체 
{
    strcpy(smm_node[smmObj_noNode].name, name);//pointer라서 strcpy 
    smm_node[smmObj_noNode].type = type;
    smm_node[smmObj_noNode].credit = credit;
    smm_node[smmObj_noNode].energy = energy;
    
    smmObj_noNode++;
}

char* smmObj_getNodeName(int node_nr) //smmObj_name주소에 접근해서 해당하는 문자열에 접근 ㄹㄹ  
{
    return smm_node[node_nr].name;
}
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

#if 0
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

