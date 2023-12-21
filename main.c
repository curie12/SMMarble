//
//  main.c
//  SMMarble
//
//  Created by Juyeop Kim on 2023/11/05.
//

#include <time.h>
#include <string.h>
#include "smm_object.h"
#include "smm_database.h"
#include "smm_common.h"

#define BOARDFILEPATH "marbleBoardConfig.txt"
#define FOODFILEPATH "marbleFoodConfig.txt"
#define FESTFILEPATH "marbleFestivalConfig.txt"


//board configuration parameters
static int board_nr;
static int food_nr;
static int festival_nr;

static int player_nr;

typedef struct player{
        int energy;
        int position;
        char name[MAX_CHARNAME];
        int accumCredit;//누적학점 
        int flag_graduate;//졸업여부:flag_graduate==1인학생이 1명이라도 있으면 종료 
} player_t;

static player_t *cur_player;
//static player_t cur_player[MAX_PLAYER];
#if 0
static int player_energy[MAX_PLAYER];
static int player_position[MAX_PLAYER];
static char player_name[MAX_PLAYER][MAX_CHARNAME];
#endif

//function prototypes
#if 0
//int isGraduated(void); //check if any player is graduated
//void generatePlayers(int n, int initEnergy); //generate a new player

//void printGrades(int player); //print grade history of the player
//void goForward(int player, int step); //make player go "step" steps on the board (check if player is graduated)

//void printPlayerStatus(void); //print all player status at the beginning of each turn
float calcAverageGrade(int player); //calculate average grade of the player
smmGrade_e takeLecture(int player, char *lectureName, int credit); //take the lecture (insert a grade of the player)
void* findGrade(int player, char *lectureName); //find the grade from the player's grade history
//void printGrades(int player); //print all the grade history of the player
#endif
int isGraduated(void)
{
     int i;
     for (i=0;i<player_nr;i++)
     {
         if ( cur_player[i].accumCredit >= GRADUATE_CREDIT )
         {
              cur_player[i].flag_graduate == 1;
              
              break;
         }
     }
     return cur_player[i].flag_graduate;//flag_graduate == 1 이면 게임 끝 
}     
   

int findGrade(int player)//이전 학점 합계?? 
{
      int i;
      int pvgrade_total;
      for (i=0;i<board_nr;i++)
         {
             void *board_Check = smmdb_getData(LISTNO_NODE, i);
             pvgrade_total += printGrades(player) * smmObj_getNodeCredit(board_Check);
         }
      return pvgrade_total;           
}

void takeLecture(int player, char *lectureName, int credit)
{
     char class_answer;
     int learnBefore(void)//이전수강경험 
     {
         int i;
         int LB;//LEARNBEFORE
         for (i=0;i<board_nr;i++)
         {
             void *boardCheck = smmdb_getData(LISTNO_NODE, i);
             if(strcmp(smmObj_getNodeName(boardCheck), smmObj_getNodeName(&cur_player[player].position)) == 0)
             {
              LB = 1;
              break;
             }
         }
         return LB;
     }
     //1. player's energy >= class energy
     if((cur_player[player].energy >= smmObj_getNodeEnergy( &cur_player[player].position )) &&
     //2. never heard before-db 
     (learnBefore()==0))
     {
          printf("Lecture %s(credit: %i, energy: %i) starts! Are you going to join? or drop?", smmObj_getNodeName(&cur_player[player].position), smmObj_getNodeCredit(&cur_player[player].position), smmObj_getNodeEnergy(&cur_player[player].position) );
          scanf("%s", class_answer);
          const char *join = "join";

          if (strcmp(class_answer, join) == 0)
          {
          
               srand((unsigned int)time(NULL));
               int randomIndex = rand() % 9; //등급: (smmObjGrade_e)randomIndex
               
               float gradeValueslist[] = {4.3, 4.0, 3.7, 3.3, 3.0, 2.7, 2.3, 2.0, 1.7};
               const char *gradeList[] = {"A+", "A0", "A-", "B+", "B0", "B-", "C+", "C0", "C-"};
               
               int total_grade = findGrade(player)+gradeValueslist[randomIndex]*smmObj_getNodeCredit(&cur_player[player].position);
               printf("Player %s successfully takes the lecture %s with grade %s.(average: %0.6f, remained energy: %i",
                              cur_player[player].name, smmObj_getNodeName(&cur_player[player].position), 
                              gradelist[randomIndex], calcAverageGrade평균학점-지금들은것도 포함,
                              cur_player[player].energy - smmObj_getNodeEnergy( cur_player[player].position )); 
          else
              printf("Player %s drops the lecture %s! ", cur_player[player].name, smmObj_getNodeName(cur_player[player].position));
          }
}smmGrade_e;

void printGrades(int player)
{
     int i;
     void *gradePtr;
     for (i=0;i<smmdb_len(LISTNO_OFFSET_GRADE + player);i++)
     {
         gradePtr = smmdb_getData(LISTNO_OFFSET_GRADE + player, i);//database
         printf("%s : %i\n", smmObj_getNodeName(gradePtr), smmObj_getNodeGrade(gradePtr));
         
     }
}

void printPlayerStatus(void)
{
     int i;
     printf("=================player status=================\n");
     for(i=0;i<player_nr;i++)
     {
         printf("%s at %i, credit %i, energy %i\n",
             cur_player[i].name,
             cur_player[i].position,
             cur_player[i].accumCredit,
             cur_player[i].energy);
     }
     printf("==============================================\n\n");
}

void generatePlayers(int n, int initEnergy)//generate new players<=n명
{
    int i;
    for(i=0;i<n;i++)
    {
        //input name
        printf("Input player %i's name: ", i+1);
        scanf("%s", cur_player[i].name);
        fflush(stdin);
        
        //set position to zerobase
        //player_position[i] = 0;
        cur_player[i].position = 0;
        
        //set energy
        //player_energy[i] = initEnergy;
        cur_player[i].energy = initEnergy;
        cur_player[i].accumCredit = 0;
        cur_player[i].flag_graduate = 0;
    }
}


int rolldie(int player)
{
    char c;
    printf(" Press any key to roll a die (press g to see grade): ");
    c = getchar();
    fflush(stdin);
    
#if 1
    if (c == 'g')
        printGrades(player);
#endif
    
    return (rand()%MAX_DIE + 1);
}


//action code when a player stays at a node
void actionNode(int player)
{
    void *boardPtr = smmdb_getData(LISTNO_NODE, cur_player[player].position);
    //int type = smmObj_getNodeType( cur_player[player].position );
    int type = smmObj_getNodeType( boardPtr );
    char *name = smmObj_getNodeName( boardPtr );
    void *gradePtr;

    switch(type)
    {
        //case lecture:
        case SMMNODE_TYPE_LECTURE:
            if (1) {
                cur_player[player].accumCredit += smmObj_getNodeCredit( boardPtr );
                cur_player[player].energy -= smmObj_getNodeEnergy( boardPtr );
                
                //grade generation
                //takeLecture 함수 
                //수정해야함 
                //void* smmObj_genObject(char* name, smmObjType_e objType??, int type, int credit, int energy, smmObjGrade_e grade)
                
                //gradePtr = smmObj_genObject(name, smmObjType_board, 0, smmObj_getNodeCredit( boardPtr ), 0, ??-학점계);//새로운 구조체 생성  
                smmdb_addTail(LISTNO_OFFSET_GRADE + player, gradePtr);
            }
            break;
             
        default:
            break;
    }
}

void goForward(int player, int step)//make player go "step" steps on the board (check if player is graduated)
{
      void *boardPtr;
      cur_player[player].position += step;
      boardPtr = smmdb_getData(LISTNO_NODE, cur_player[player].position );
      
     printf("%s go to node %i (name: %s)\n", 
                cur_player[player].name, cur_player[player].position,
                smmObj_getNodeName(boardPtr));
}


///-------------------------------------///
int main(int argc, const char * argv[]) {
    
    FILE* fp;
    char name[MAX_CHARNAME];
    int type;
    int credit;
    int energy;
    int i; 
    int initEnergy;
    int turn=0;
    
    board_nr = 0;
    food_nr = 0;
    festival_nr = 0;
    
    srand(time(NULL));
    
    
    //1. import parameters ---------------------------------------------------------------------------------
    //1-1. boardConfig 
    if ((fp = fopen(BOARDFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", BOARDFILEPATH);
        getchar();
        return -1;
    }
    
    printf("Reading board component......\n");
    while ( fscanf(fp, "%s %i %i %i", name, &type, &credit, &energy) == 4 )  //read a node parameter set
    {
        //store the parameter set
         //(char* name, smmObjType_e objType, int type, int credit, int energy, smmObjGrade_e grade)
        void *boardObj = smmObj_genObject(name, smmObjType_board, type, credit, energy, smmObjType_grade);
        smmdb_addTail(LISTNO_NODE, boardObj);
        if(type == SMMNODE_TYPE_HOME)
            initEnergy = energy;//(게임시작시 집에서 시작, 에너지 초기화) 
        board_nr++;
    }
    fclose(fp);
    printf("Total number of board nodes : %i\n", board_nr);
    
    for (i=0;i<board_nr;i++)
    {
        void *boardObj = smmdb_getData(LISTNO_NODE, i);
        //node 0: 우리집, 3(집) 형태로 출력 
        printf("node %i : %s, %i(%s), credit %i, energy %i\n", i, smmObj_getNodeName(boardObj), 
                     smmObj_getNodeType(boardObj), 
                     smmObj_getTypeName(smmObj_getNodeType(boardObj)),
                     smmObj_getNodeCredit(boardObj), smmObj_getNodeEnergy(boardObj));
    }
    //printf("(%s)", smmObj_getTypeName(SMMNODE_TYPE_LECTURE));
    
    #if 0 
    //2. food card config 
    if ((fp = fopen(FOODFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FOODFILEPATH);
        return -1;
    }
    
    printf("\n\nReading food card component......\n");
    while () //read a food parameter set
    {
        //store the parameter set
    }
    fclose(fp);
    printf("Total number of food cards : %i\n", food_nr);
    
    
    
    //3. festival card config 
    if ((fp = fopen(FESTFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FESTFILEPATH);
        return -1;
    }
    
    printf("\n\nReading festival card component......\n");
    while () //read a festival card string
    {
        //store the parameter set
    }
    fclose(fp);
    printf("Total number of festival cards : %i\n", festival_nr);
    #endif
    
    
    //2. Player configuration ---------------------------------------------------------------------------------
    
    do
    {
        //input player number to player_nr 
        printf("Please input number of players:"); 
        scanf("%d", &player_nr);
        fflush(stdin);
    }
    while (player_nr < 0 || player_nr > MAX_PLAYER);

    cur_player = (player_t*)malloc(player_nr*sizeof(player_t));
    
    generatePlayers(player_nr, initEnergy);
     

    //3. SM Marble game starts ---------------------------------------------------------------------------------
    while ( isGraduated(void) != 1) //is anybody graduated?
    {
        int die_result;
        
        //4-1. initial printing
        printPlayerStatus();
        
        //4-2. die rolling (if not in experiment)
        die_result = rolldie(turn);
        
        //4-3. go forward
        goForward(turn, die_result);

		//4-4. take action at the destination node of the board
        actionNode(turn);
        
        //4-5. next turn
        turn = (turn + 1)%player_nr;
        //지금 누구 차례인지출력
        printf("\n This is %s's turn : : : ", cur_player[turn].name); 
    }
    free(cur_player);
    //system("PAUSE");
    return 0;
}
