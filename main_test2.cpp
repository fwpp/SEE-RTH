#include <iostream>
#include <fstream>
#include "Threes_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define Max_times 100
#define exist true
#define non_exist false

/*#include <ctime>
#ifdef _WIN32
#include <conio.h>
#elif defined(__linux__)
#include <termios.h>
#include <unistd.h>
int getch(void){
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
#endif*/

//#define Test_get_Merge_point

using   namespace       std     ;


typedef struct Game_record Game_record  ;


struct Game_record{

int     Max_point       ;
int     All_point       ;
int     Max_number      ;
};


dir_e   get_next_dir( Grid )    ;

inline  bool    Does_block_exist( const int , const int )       ;

int     get_Merge_point( Grid , const dir_e )   ;


int     get_all_dir_Merge_point( Grid ) ;


int     get_Max_number_in_Grid( Grid& ) ;


int     get_Max_number( int* , int )    ;

bool    Does_move_dir( Grid , dir_e )   ;


/* test whether the row would be moved with left or right */
bool row_full(Grid info,int row);
/* test whether the column or row can move with the direction */
bool can_move(Grid info,int index, const dir_e dir );
/* return some possible direction information */
struct direction_1_2{
    int left;
    int up;
    int right;
    int down;
    int one;
    int two;
};
/* coordination of number */
struct node{
    int x,y;
    int point;
};
/* check 1, 2 pairs */
struct direction_1_2 red_blue(Grid info, int next_hint, struct direction_1_2 information);
/* return 1 : pair, 0 : not pair */
int pairBFS(char maps[GRID_LENGTH][GRID_LENGTH], int x, int y);
/* check whether numbers could merge originally after another direction */
bool another_direction_no_affect(Grid info, const dir_e originalDir, const dir_e anotherDir);
/* count number of rows or columns would move on certain direction */
int row_column_move_amount(Grid info, const dir_e direction);
/* now and one depth estimation : the amount of merge */
struct direction_1_2 depth_estimation(struct direction_1_2 dir_info, Grid info);
/* get how many Max_number in grid */
int get_Max_number_in_Grid_Amount(Grid& info, int Max_number);
/* determine direction */
dir_e determine_direction(Grid info, struct direction_1_2 dir_info);

void PlayNRounds(int n){
    int score;
    Game myGame;
    bool isGameOver;
    
    if(myGame.isGameOver(score))  myGame.reset();

    Grid info;

    for(int i = 0;i < n;i++){
        isGameOver = false;
        while(!isGameOver){
            myGame.getCurrentGrid(info);
            struct direction_1_2 dir_info;
            dir_e outcome;
            dir_info.left=dir_info.up=dir_info.right=dir_info.down=0;
            dir_info.one=dir_info.two=0;

            if( (myGame.getHint()-'0') == 1 || (myGame.getHint()-'0') == 2){
                dir_info=red_blue(info,(myGame.getHint()-'0'), dir_info);
            }

            dir_info=depth_estimation(dir_info, info);

            outcome=determine_direction(info, dir_info);

            myGame.insertDirection(outcome);
            isGameOver = myGame.isGameOver(score);
       }
        
        if(i < n - 1)  myGame.reset();
    }
}

int main(int argc, char* argv[]){
    // Note: API function calls performed by any 'Game' object effects the same set of static class members,
    // so even through the 2 following function calls use different 'Game' objects, the same game continues
    PlayNRounds(50);
    PlayNRounds(50);
    return 0;
}


int     get_Max_number_in_Grid( Grid&   info )
                {


                        int     Max_number      =       0       ;

                        int     i                               ;


                        for( i = 0 ; i < 16 ; i++ )
                                {

                                        if( info[ i ] > Max_number )
                                                {

                                                        Max_number      =    info[ i ]        ;

                                                }

                                }


                        return  Max_number      ;

                }



int     get_Max_number( int* number_array , int Max )
                {


                        int     Max_number      =       0       ;

                        int     i                               ;


                        for( i = 0 ; i < Max ; i++ )
                                {

                                        if( number_array[ i ] > Max_number )
                                                {

                                                        Max_number      =    number_array[ i ]        ;

                                                }

                                }


                        return  Max_number      ;


                }



int     get_Merge_point( Grid now_stat , const dir_e dir )
                {


                        int     row     ;

                        int     col     ;

                        bool    Merge_exist     =       non_exist       ;


                        int     Merge_point     =       0       ;


                        switch( dir )
                                {

                                        case LEFT :

                                                for( row = 0 ; row < 4 ; row++ )
                                                        {

                                                                for( col = 0 ; ( col < 3 ) && ( Merge_exist == non_exist ) ; col++ )
                                                                        {

                                                                             if( now_stat.canMerge( now_stat( row , col ) , now_stat( row , col + 1 ) ) )
                                                                             {

                                                                             Merge_point      =       Merge_point + 1 ;

                                                                             Merge_exist      =       exist           ;

                                                                             }

                                                                             if( now_stat( row , col ) == 0  )
                                                                             {

                                                                             Merge_exist      =       exist   ;

                                                                             }

                                                                        }

                                                                Merge_exist  =non_exist       ;

                                                        }

                                                return  Merge_point     ;

                                        case RIGHT :

                                                for( row = 0 ; row < 4 ; row++ )
                                                        {

                                                                for( col = 3 ; ( col > 0 ) && ( Merge_exist == non_exist ) ; col-- )
                                                                        {

                                                                             if( now_stat.canMerge( now_stat( row , col ) , now_stat( row , col - 1 ) ) )
                                                                             {

                                                                             Merge_point      =       Merge_point + 1 ;

                                                                             Merge_exist      =       exist           ;

                                                                             }

                                                                             if( now_stat( row , col ) == 0 )
                                                                             {

                                                                             Merge_exist      =       exist   ;

                                                                             }

                                                                        }

                                                                Merge_exist  =non_exist       ;

                                                        }

                                                return  Merge_point     ;

                                        case UP :

                                                for( col = 0 ; col < 4 ; col++ )
                                                        {

                                                                for( row = 0 ; ( row < 3 ) && ( Merge_exist == non_exist ) ; row++ )
                                                                        {

                                                                             if( now_stat.canMerge( now_stat( row , col ) , now_stat( row + 1 , col ) ) )
                                                                             {

                                                                             Merge_point      =       Merge_point + 1 ;

                                                                             Merge_exist      =       exist           ;

                                                                             }

                                                                             if( now_stat( row , col ) == 0 )
                                                                             {

                                                                             Merge_exist      =       exist   ;

                                                                             }

                                                                        }

                                                                Merge_exist  =non_exist       ;

                                                        }

                                                return  Merge_point     ;

                                        case DOWN :

                                                for( col = 0 ; col < 4 ; col++ )
                                                        {

                                                                for( row = 3 ; ( row > 0 ) && ( Merge_exist == non_exist ) ; row-- )
                                                                        {

                                                                             if( now_stat.canMerge( now_stat( row , col ) , now_stat( row - 1 , col ) ) )
                                                                             {

                                                                             Merge_point      =       Merge_point + 1 ;

                                                                             Merge_exist      =       exist           ;

                                                                             }

                                                                             if( now_stat( row , col ) == 0 )
                                                                             {

                                                                             Merge_exist      =       exist   ;

                                                                             }

                                                                        }

                                                                Merge_exist  =non_exist       ;

                                                        }


                                                return  Merge_point     ;

                                        default :

                                                return  0       ;

                                }

                }




int     get_all_dir_Merge_point( Grid now_stat )
                {

                        return  get_Merge_point( now_stat , LEFT ) + get_Merge_point( now_stat , RIGHT ) + get_Merge_point( now_stat , UP ) + get_Merge_point( now_stat , DOWN )    ;

                }

inline  bool    Does_block_exist( const int n1 , const int n2 )
                {

                        if( ( ( n1 > -1 ) && ( n1 < 4 ) ) && ( ( n2 > -1 ) && ( n2 < 4 ) ) )
                                {

                                        return  true    ;

                                }

                        return  false   ;

                }

dir_e   get_next_dir( Grid now_stat )
                {

                        int     LEFT_point      =       0       ;

                        int     RIGHT_point     =       0       ;

                        int     UP_point        =       0       ;

                        int     DOWN_point      =       0       ;

                        int     Max_L_or_R                      ;

                        int     Max_U_or_D                      ;

                        int     Max_point                       ;

                        Grid    test                            ;









                        /*


                                determine   directy


                        */




                        if( RIGHT_point > LEFT_point )
                                {

                                        if( UP_point > RIGHT_point )
                                                {

                                                        if( DOWN_point > UP_point )
                                                                {

                                                                        return  DOWN    ;

                                                                }

                                                        if( DOWN_point == UP_point )
                                                                {

                                                                        if( ( int )( random() % 2 ) == 1 )
                                                                             {

                                                                             return   DOWN    ;

                                                                             }

                                                                        return UP      ;

                                                                }

                                                        //      DOWN_point < UP_point

                                                        return  UP      ;

                                                }

                                        if( UP_point == RIGHT_point )
                                                {

                                                        if( DOWN_point > UP_point )
                                                                {

                                                                        return  DOWN    ;

                                                                }

                                                        if( DOWN_point == UP_point )
                                                                {

                                                                        switch( ( int )( random() % 3 ) )
                                                                             {

                                                                             case 0 :
                                                                             return   RIGHT   ;
                                                                             case 1 :
                                                                             return   UP      ;
                                                                             default :
                                                                             return   DOWN    ;

                                                                             }

                                                                }

                                                        //      DOWN_point < UP_point


                                                        if( ( int )( random() % 2 ) == 0 )
                                                                {

                                                                        return UP      ;

                                                                }

                                                        return  RIGHT   ;

                                                }


                                        //  UP_point  <  RIGHT_point


                                        if( DOWN_point > RIGHT_point )
                                                {

                                                        return  DOWN    ;

                                                }

                                        if( DOWN_point == RIGHT_point )
                                                {

                                                        if( ( int )( random() % 2 ) == 0 )
                                                                {

                                                                        return DOWN    ;

                                                                }

                                                        return  RIGHT   ;

                                                }

                                        //      DOWN_point < RIGHT_point

                                        return  RIGHT   ;

                                }


                        if( RIGHT_point == LEFT_point )
                                {

                                        if( UP_point > RIGHT_point )
                                                {

                                                        if( DOWN_point > UP_point )
                                                                {

                                                                        return DOWN    ;

                                                                }

                                                        if( DOWN_point == UP_point )
                                                                {

                                                                        if( ( int )( random() % 2 ) == 0 )
                                                                             {

                                                                             return   DOWN    ;

                                                                             }

                                                                        return UP      ;

                                                                }

                                                        //      DOWN_point < UP_point

                                                        return  UP      ;

                                                }

                                        if( UP_point == RIGHT_point )
                                                {

                                                        if( DOWN_point > UP_point )
                                                                {

                                                                        return DOWN    ;

                                                                }

                                                        if( DOWN_point == UP_point )
                                                                {

                                                                        switch( ( int )( random() % 4 ) )
                                                                             {

                                                                             case 0 :
                                                                             return   DOWN    ;
                                                                             case 1 :
                                                                             return   UP      ;
                                                                             case 2 :
                                                                             return   RIGHT   ;
                                                                             default :
                                                                             return   LEFT    ;

                                                                             }

                                                                }

                                                        //      DOWN_point < UP_point

                                                        switch( ( int )( random() % 3 ) )
                                                                {

                                                                        case 0 :
                                                                             return   UP      ;
                                                                        case 1 :
                                                                             return   RIGHT   ;
                                                                        default :
                                                                             return   LEFT    ;

                                                                }

                                                }

                                        //      UP_point < RIGHT_point

                                        if( DOWN_point > RIGHT_point )
                                                {

                                                        return  DOWN    ;

                                                }

                                        if( DOWN_point == RIGHT_point )
                                                {

                                                        switch( ( int )( random() % 3 ) )
                                                                {

                                                                        case 0 :
                                                                             return   DOWN    ;
                                                                        case 1 :
                                                                             return   RIGHT   ;
                                                                        default :
                                                                             return   LEFT    ;

                                                                }

                                                }

                                        //      DOWN_point < RIGHT_point

                                        if( ( int )( random() % 2 ) == 0 )
                                                {

                                                        return  RIGHT   ;

                                                }

                                        return  LEFT    ;

                                }

                        //      RIGHT_point < LEFT_point

                                if( UP_point > LEFT_point )
                                        {

                                                if( DOWN_point > UP_point )
                                                        {

                                                                return  DOWN ;

                                                        }

                                                if( DOWN_point == UP_point )
                                                        {

                                                                if( ( int )( random() % 2 ) == 0 )
                                                                        {

                                                                             return   DOWN    ;

                                                                        }

                                                                return  UP   ;

                                                        }

                                                //      DOWN_point < UP_point

                                                return  UP      ;
                                        }

                                if( UP_point == LEFT_point )
                                        {

                                                if( DOWN_point > UP_point )
                                                        {

                                                                return  DOWN ;

                                                        }

                                                if( DOWN_point == UP_point )
                                                        {

                                                                switch( ( int )( random() % 3 ) )
                                                                        {

                                                                             case 0 :
                                                                             return   DOWN    ;
                                                                             case 1 :
                                                                             return   UP      ;
                                                                             default :
                                                                             return   LEFT    ;

                                                                        }

                                                        }

                                                //      DOWN_point < UP_point

                                                if( ( int )( random() % 2 ) == 0 )
                                                        {

                                                                return  UP   ;

                                                        }

                                                return  LEFT    ;

                                        }

                                //      UP_point < LEFT_point

                                if( DOWN_point > LEFT_point )
                                        {

                                                return  DOWN    ;

                                        }

                                if( DOWN_point == LEFT_point )
                                        {

                                                if( ( int )( random() % 2 ) == 0 )
                                                        {

                                                                return  DOWN ;

                                                        }

                                                return  LEFT    ;

                                        }

                                //      DOWN_point < LEFT_point

                                return  LEFT    ;

                }

bool row_full(Grid info,int row){
    bool full=true;
    for(int i=0;i<GRID_LENGTH;i++){
        if( info(row,i) == 0){
            full=false;
            break;
        }

        if( i < (GRID_LENGTH-1) ){
            if( info.canMerge(info(row,i),info(row,i+1)) ){
                full=false;
                break;
            }
        }
    }

    return full;
}



bool    Does_move_dir( Grid now_stat , dir_e dir )
                {

                        Grid    dir_now_stat    =       now_stat        ;

                        int     i               =       0               ;

                        dir_now_stat.shift( dir )       ;

                        for( ; i < 16 ; i++ )
                                {

                                        if( now_stat[ i ] != dir_now_stat[ i ] )
                                                {

                                                        return  true    ;

                                                }

                                }

                        return  false   ;

                }


bool can_move(Grid info,int index, const dir_e dir ){
    bool full=true;
    int i;

    switch(dir){
        case LEFT:
            for(i=1;i<GRID_LENGTH;i++){
                if( info(index,i)!=0 && info(index,i-1) == 0 )
                    break;
                if( info.canMerge( info(index,i) , info(index,i-1) ) )
                    break;
            }
            if(i>=GRID_LENGTH) full=false;
            break;
        case UP:
            for(i=1;i<GRID_LENGTH;i++){
                if( info(i,index)!=0 && info(i-1,index) == 0 )
                    break;
                if( info.canMerge( info(i,index) , info(i-1,index) ) )
                    break;
            }
            if(i>=GRID_LENGTH) full=false;
            break;
        case RIGHT:
            for(i=GRID_LENGTH-2;i>=0;i--){
                if( info(index,i)!=0 && info(index,i+1) == 0 )
                    break;
                if( info.canMerge( info(index,i) , info(index,i+1) ) )
                    break;
            }
            if(i<0) full=false;
            break;
        case DOWN:
            for(i=GRID_LENGTH-2;i>=0;i--){
                if( info(i,index)!=0 && info(i+1,index) == 0 )
                    break;
                if( info.canMerge( info(i,index) , info(i+1,index) ) )
                    break;
            }
            if(i<0) full=false;
            break;
    }

    return full;
}

struct direction_1_2 red_blue(Grid info,int next_hint, struct direction_1_2 information){
    struct node not_pair[GRID_LENGTH*GRID_LENGTH],extract;
    int top;
    char maps[GRID_LENGTH][GRID_LENGTH]={0};
    int outcome;


    /* create maps */
    for(int i=0;i<GRID_LENGTH;i++){
        for(int j=0;j<GRID_LENGTH;j++){
            maps[i][j]=info(i,j);
        }
    }

    top=-1;
    for(int i=0;i<GRID_LENGTH;i++){
        for(int j=0;j<GRID_LENGTH;j++){
            if(maps[i][j]==1 || maps[i][j]==2){
                outcome=pairBFS(maps,i,j);
                if(outcome==0){
                    not_pair[++top].x=i; not_pair[top].y=j;
                }
            }
        }
    }

    /*
     *     |
     *  A  |   B
     *-----|------
     *     |
     *  C  |   D
     */
    /* possible direction
       A : down , right
       B : down , left
       C : up , right
       D : up , left
     */
    /* number at edge => weight ++ */
    if(top>=0){
        for(int i=0;i<=top;i++){
            extract=not_pair[i];

            if(info(extract.x,extract.y)+next_hint!=3)
                continue;

            if(info(extract.x,extract.y)==1)
                ++information.one;
            if(info(extract.x,extract.y)==2)
                ++information.two;

            /* A */
            if(extract.x<=1 && extract.y <= 1){
                outcome=can_move(info, extract.x, RIGHT);
                if(extract.x!=1||extract.y!=1){
                    information.right+=2*outcome;
                }else if(info(0,0)==0){
                    information.right+=outcome;
                }

                outcome=can_move(info, extract.y, DOWN);
                if(extract.x!=1||extract.y!=1){
                    information.down+=2*outcome;
                }else if(info(0,0)==0){
                    information.down+=outcome;
                }
            }

            /* B */
            if(extract.x<=1 && extract.y >1){
                outcome=can_move(info, extract.x, LEFT);
                if(extract.x!=1||extract.y!=2){
                    information.left+=2*outcome;
                }else if(info(0,3)==0){
                    information.left+=outcome;
                }

                outcome=can_move(info, extract.y, DOWN);
                if(extract.x!=1||extract.y!=2){
                    information.down+=2*outcome;
                }else if(info(0,3)==0){
                    information.down+=outcome;
                }
            }

            /* C */
            if(extract.x>1 && extract.y <=1){
                outcome=can_move(info, extract.x, RIGHT);
                if(extract.x!=2||extract.y!=1){
                    information.right+=2*outcome;
                }else if(info(3,0)==0){
                    information.right+=outcome;
                }

                outcome=can_move(info, extract.y, UP);
                if(extract.x!=2||extract.y!=1){
                    information.up+=2*outcome;
                }else if(info(3,0)==0){
                    information.up+=outcome;
                }
            }

            /* D */
            if(extract.x>1 && extract.y >1){
                outcome=can_move(info, extract.x, LEFT);
                if(extract.x!=2||extract.y!=2){
                    information.left+=2*outcome;
                }else if(info(3,3)==0){
                    information.left+=outcome;
                }

                outcome=can_move(info, extract.y, UP);
                if(extract.x!=2||extract.y!=2){
                    information.up+=2*outcome;
                }else if(info(3,3)==0){
                    information.up+=outcome;
                }
            }
        }
    }

    return information;
}


int pairBFS(char maps[GRID_LENGTH][GRID_LENGTH], int x, int y){
    struct node queueList[GRID_LENGTH*GRID_LENGTH],cur;
    int head,tail;
    int original;

    /* number find pair */
    original=maps[x][y];
    maps[x][y]=3;

    tail=head=0;
    queueList[tail].x=x; queueList[tail].y=y;
    while(head<=tail){

        cur=queueList[head++];

        if(maps[cur.x][cur.y]+original==3){
            maps[cur.x][cur.y]=3;
            return 1;
        }

        if(maps[cur.x][cur.y]<=0)
            maps[cur.x][cur.y]=( (-1) * ( (10*x) + y ) );
        else if(cur.x!=x && cur.y!=y)
            continue;

        if(cur.y+1<GRID_LENGTH)
            if(maps[cur.x][cur.y+1] < 3 && maps[cur.x][cur.y+1]!=( (-1) * ( (10*x) + y ) )){
                queueList[++tail].x=cur.x; queueList[tail].y=cur.y+1;
            }


        if(cur.x+1<GRID_LENGTH){
            if(maps[cur.x+1][cur.y] < 3 && maps[cur.x+1][cur.y]!=( (-1) * ( (10*x) + y ) )){
                queueList[++tail].x=cur.x+1; queueList[tail].y=cur.y;
            }
        }

        if(cur.y-1>=0){
            if(maps[cur.x][cur.y-1] < 3 && maps[cur.x][cur.y-1]!=( (-1) * ( (10*x) + y ) )){
                queueList[++tail].x=cur.x; queueList[tail].y=cur.y-1;
            }
        }

        if(cur.x-1>=0){
            if(maps[cur.x-1][cur.y] < 3 && maps[cur.x-1][cur.y]!=( (-1) * ( (10*x) + y ) )){
                queueList[++tail].x=cur.x-1; queueList[tail].y=cur.y;
            }
        }
    }

    return 0;
}


bool another_direction_no_affect(Grid info, const dir_e originalDir, const dir_e anotherDir){
    struct node mergeList[32];
    struct node mergeList2[64];
    int top,top2;

    /* get numbers could merge originally */
    top=-1;
    switch(originalDir){
        case LEFT:
            for(int i=0;i<GRID_LENGTH;i++){
                for(int j=0;j<GRID_LENGTH-1;j++){
                    if( info.canMerge( info(i,j) , info(i,j+1) ) ){
                        mergeList[++top].x=i; mergeList[top].y=j; mergeList[top].point=info(i,j);
                        mergeList[++top].x=i; mergeList[top].y=j+1; mergeList[top].point=info(i,j+1);
                        j++;
                    }
                }
            }
            break;

        case UP:
            for(int j=0;j<GRID_LENGTH;j++){
                for(int i=0;i<GRID_LENGTH-1;i++){
                    if( info.canMerge( info(i,j) , info(i+1,j) ) ){
                        mergeList[++top].x=i; mergeList[top].y=j; mergeList[top].point=info(i,j);
                        mergeList[++top].x=i+1; mergeList[top].y=j; mergeList[top].point=info(i+1,j);
                        i++;
                    }
                }
            }

            break;

        case RIGHT:
            for(int i=0;i<GRID_LENGTH;i++){
                for(int j=GRID_LENGTH-1;j>0;j--){
                    if( info.canMerge( info(i,j) , info(i,j-1) ) ){
                        mergeList[++top].x=i; mergeList[top].y=j; mergeList[top].point=info(i,j);
                        mergeList[++top].x=i; mergeList[top].y=j-1; mergeList[top].point=info(i,j-1);
                        j--;
                    }
                }
            }
            break;

        case DOWN:
            for(int j=0;j<GRID_LENGTH;j++){
                for(int i=GRID_LENGTH-1;i>0;i--){
                    if( info.canMerge( info(i,j) , info(i-1,j) ) ){
                        mergeList[++top].x=i; mergeList[top].y=j; mergeList[top].point=info(i,j);
                        mergeList[++top].x=i-1; mergeList[top].y=j; mergeList[top].point=info(i-1,j);
                        i--;
                    }
                }
            }
            break;
    }


    /* check whether numbers could merge originally after another direction */
    top2=-1;
    switch(anotherDir){
        case LEFT:
            for(int i=0;i<GRID_LENGTH;i++){
                for(int j=0;j<GRID_LENGTH-1;j++){
                    if(info(i,j)==0)break;
                    if( info.canMerge( info(i,j) , info(i,j+1) ) ){
                        mergeList2[++top2].x=i; mergeList2[top2].y=j; mergeList2[top2].point=info(i,j);
                        mergeList2[++top2].x=i; mergeList2[top2].y=j+1; mergeList2[top2].point=info(i,j+1);
                        j++;
                        break;
                    }
                }
            }

            break;

        case UP:
            for(int j=0;j<GRID_LENGTH;j++){
                for(int i=0;i<GRID_LENGTH-1;i++){
                    if(info(i,j)==0)break;
                    if( info.canMerge( info(i,j) , info(i+1,j) ) ){
                        mergeList2[++top2].x=i; mergeList2[top2].y=j; mergeList2[top2].point=info(i,j);
                        mergeList2[++top2].x=i+1; mergeList2[top2].y=j; mergeList2[top2].point=info(i+1,j);
                        i++;
                        break;
                    }
                }
            }

            break;

        case RIGHT:
            for(int i=0;i<GRID_LENGTH;i++){
                for(int j=GRID_LENGTH-1;j>0;j--){
                    if(info(i,j)==0)break;
                    if( info.canMerge( info(i,j) , info(i,j-1) ) ){
                        mergeList2[++top2].x=i; mergeList2[top2].y=j; mergeList2[top2].point=info(i,j);
                        mergeList2[++top2].x=i; mergeList2[top2].y=j-1; mergeList2[top2].point=info(i,j-1);
                        j--;
                        break;
                    }
                }
            }
            break;

        case DOWN:
            for(int j=0;j<GRID_LENGTH;j++){
                for(int i=GRID_LENGTH-1;i>0;i--){
                    if(info(i,j)==0)break;
                    if( info.canMerge( info(i,j) , info(i-1,j) ) ){
                        mergeList2[++top2].x=i; mergeList2[top2].y=j; mergeList2[top2].point=info(i,j);
                        mergeList2[++top2].x=i-1; mergeList2[top2].y=j; mergeList2[top2].point=info(i-1,j);
                        i--;
                        break;
                    }
                }
            }
            break;
    }

    info.shift(anotherDir);
    switch(originalDir){
        case LEFT:
            for(int i=0;i<GRID_LENGTH;i++){
                for(int j=0;j<GRID_LENGTH-1;j++){
                    if( info.canMerge( info(i,j) , info(i,j+1) ) ){
                        mergeList2[++top2].x=i; mergeList2[top2].y=j; mergeList2[top2].point=info(i,j);
                        mergeList2[++top2].x=i; mergeList2[top2].y=j+1; mergeList2[top2].point=info(i,j+1);
                        j++;
                    }
                }
            }
            break;

        case UP:
            for(int j=0;j<GRID_LENGTH;j++){
                for(int i=0;i<GRID_LENGTH-1;i++){
                    if( info.canMerge( info(i,j) , info(i+1,j) ) ){
                        mergeList2[++top2].x=i; mergeList2[top2].y=j; mergeList2[top2].point=info(i,j);
                        mergeList2[++top2].x=i+1; mergeList2[top2].y=j; mergeList2[top2].point=info(i+1,j);
                        i++;
                    }
                }
            }

            break;

        case RIGHT:
            for(int i=0;i<GRID_LENGTH;i++){
                for(int j=GRID_LENGTH-1;j>0;j--){
                    if( info.canMerge( info(i,j) , info(i,j-1) ) ){
                        mergeList2[++top2].x=i; mergeList2[top2].y=j; mergeList2[top2].point=info(i,j);
                        mergeList2[++top2].x=i; mergeList2[top2].y=j-1; mergeList2[top2].point=info(i,j-1);
                        j--;
                    }
                }
            }
            break;

        case DOWN:
            for(int j=0;j<GRID_LENGTH;j++){
                for(int i=GRID_LENGTH-1;i>0;i--){
                    if( info.canMerge( info(i,j) , info(i-1,j) ) ){
                        mergeList2[++top2].x=i; mergeList2[top2].y=j; mergeList2[top2].point=info(i,j);
                        mergeList2[++top2].x=i-1; mergeList2[top2].y=j; mergeList2[top2].point=info(i-1,j);
                        i--;
                    }
                }
            }
            break;
    }

    for(int i=0;i<=top2;i++){
        for(int j=0;j<=top;j++){
            if(mergeList2[i].point==mergeList[j].point){
                mergeList[j].point=0;
            }
        }
    }

    for(int i=0;i<=top;i++){
        if(mergeList[i].point!=0){
            return false;
        }
    }

    return true;
}

int row_column_move_amount(Grid info, const dir_e direction){
    int counter=0;

    switch(direction){
        case LEFT:
            if(can_move(info,0,LEFT)) {++counter;}
            if(can_move(info,1,LEFT)) {++counter;}
            if(can_move(info,2,LEFT)) {++counter;}
            if(can_move(info,3,LEFT)) {++counter;}
            break;

        case UP:
            if(can_move(info,0,UP)) {++counter;}
            if(can_move(info,1,UP)) {++counter;}
            if(can_move(info,2,UP)) {++counter;}
            if(can_move(info,3,UP)) {++counter;}
            break;

        case RIGHT:
            if(can_move(info,0,RIGHT)) {++counter;}
            if(can_move(info,1,RIGHT)) {++counter;}
            if(can_move(info,2,RIGHT)) {++counter;}
            if(can_move(info,3,RIGHT)) {++counter;}
            break;

        case DOWN:
            if(can_move(info,0,DOWN)) {++counter;}
            if(can_move(info,1,DOWN)) {++counter;}
            if(can_move(info,2,DOWN)) {++counter;}
            if(can_move(info,3,DOWN)) {++counter;}
            break;
    }

    return counter;
}

struct direction_1_2 depth_estimation(struct direction_1_2 dir_info, Grid info){
    int maxPointNow, maxPointNowAmount;
    int maxPointShift;
    Grid tmp;

    maxPointNow = get_Max_number_in_Grid(info);
    maxPointNowAmount = get_Max_number_in_Grid_Amount(info,maxPointNow);

    /* left & left_depth */
    tmp=info;
    dir_info.left += get_Merge_point(tmp,LEFT);
    if(tmp.shift(LEFT)){
        dir_info.left += get_all_dir_Merge_point(tmp);

        if( (maxPointShift=get_Max_number_in_Grid(tmp)) > maxPointNow ){
            dir_info.left += 1;
        }else if( get_Max_number_in_Grid_Amount(tmp,maxPointShift) > maxPointNowAmount ){
            dir_info.left += 1;
        }
    }



    /* up & up_depth */
    tmp=info;
    dir_info.up += get_Merge_point(tmp,UP);
    if(tmp.shift(UP)){
        dir_info.up += get_all_dir_Merge_point(tmp);

        if( (maxPointShift=get_Max_number_in_Grid(tmp)) > maxPointNow ){
            dir_info.up += 1;
        }else if( get_Max_number_in_Grid_Amount(tmp,maxPointShift) > maxPointNowAmount ){
            dir_info.up += 1;
        }
    }

    /* right & right_depth */
    tmp=info;
    dir_info.right += get_Merge_point(tmp,RIGHT);
    if(tmp.shift(RIGHT)){
        dir_info.right += get_all_dir_Merge_point(tmp);

        if( (maxPointShift=get_Max_number_in_Grid(tmp)) > maxPointNow ){
            dir_info.right += 1;
        }else if( get_Max_number_in_Grid_Amount(tmp,maxPointShift) > maxPointNowAmount ){
            dir_info.right += 1;
        }
    }

    /* down & down_depth */
    tmp=info;
    dir_info.down += get_Merge_point(tmp,DOWN);
    if(tmp.shift(DOWN)){
        dir_info.down += get_all_dir_Merge_point(tmp);

        if( (maxPointShift=get_Max_number_in_Grid(tmp)) > maxPointNow ){
            dir_info.down += 1;
        }else if( get_Max_number_in_Grid_Amount(tmp,maxPointShift) > maxPointNowAmount ){
            dir_info.down += 1;
        }
    }


    return dir_info;
}

int get_Max_number_in_Grid_Amount(Grid& info, int Max_number){
    int counter=0;

    for(int i=0;i<16;i++){
        if(info[i]==Max_number){
            ++counter;
        }
    }

    return counter;
}

dir_e determine_direction(Grid info, struct direction_1_2 dir_info){
    dir_e first, second,third,fourth;
    dir_e tmp;
    int first_weight=0,second_weight=0,third_weight=0,fourth_weigth=0;

    if(row_column_move_amount(info,LEFT) == 0){
        dir_info.left=0;
    }
    if(row_column_move_amount(info,UP) == 0){
        dir_info.up=0;
    }
    if(row_column_move_amount(info,RIGHT) == 0){
        dir_info.right=0;
    }
    if(row_column_move_amount(info,DOWN) == 0){
        dir_info.down=0;
    }

    if(dir_info.left==0 && dir_info.up==0 && dir_info.right==0 && dir_info.down==0){
        if(row_column_move_amount(info,LEFT) != 0){
            return LEFT;
        }
        if(row_column_move_amount(info,UP) != 0){
            return UP;
        }
        if(row_column_move_amount(info,RIGHT) != 0){
            return RIGHT;
        }
        if(row_column_move_amount(info,DOWN) != 0){
            return DOWN;
        }
    }

    if(dir_info.left > first_weight){ first_weight=dir_info.left; first=LEFT; }
    if(dir_info.up > first_weight){ first_weight=dir_info.up; first=UP; }
    if(dir_info.right > first_weight){ first_weight=dir_info.right; first=RIGHT; }
    if(dir_info.down > first_weight){ first_weight=dir_info.down; first=DOWN; }

    if(dir_info.left > second_weight && first!=LEFT){ second_weight=dir_info.left; second=LEFT; }
    if(dir_info.up > second_weight && first!=UP){ second_weight=dir_info.up; second=UP; }
    if(dir_info.right > second_weight && first!=RIGHT){ second_weight=dir_info.right; second=RIGHT; }
    if(dir_info.down > second_weight && first!=DOWN){ second_weight=dir_info.down; second=DOWN; }

    if(dir_info.left > third_weight && first!=LEFT && second!=LEFT){ third_weight=dir_info.left; third=LEFT; }
    if(dir_info.up > third_weight && first!=UP && second!=UP){ third_weight=dir_info.up; third=UP; }
    if(dir_info.right > third_weight && first!=RIGHT && second!=RIGHT){ third_weight=dir_info.right; third=RIGHT; }
    if(dir_info.down > third_weight && first!=DOWN && second!=DOWN){ third_weight=dir_info.down; third=DOWN; }

    if(dir_info.left > fourth_weigth && first!=LEFT && second!=LEFT && third!=LEFT){ fourth_weigth=dir_info.left; fourth=LEFT; }
    if(dir_info.up > fourth_weigth && first!=UP && second!=UP && third!=UP){ fourth_weigth=dir_info.up; fourth=UP; }
    if(dir_info.right > fourth_weigth && first!=RIGHT && second!=RIGHT && third!=RIGHT){ fourth_weigth=dir_info.right; fourth=RIGHT; }
    if(dir_info.down > fourth_weigth && first!=DOWN && second!=DOWN && third!=DOWN){ fourth_weigth=dir_info.down; fourth=DOWN; }

    if( (first_weight == second_weight) && (first_weight == third_weight) && (first_weight == fourth_weigth) ){
        switch(rand()%4){
            case 0:
                break;
            case 1:
                tmp=first; first=second; second=tmp;
                break;
            case 2:
                tmp=first; first=third; third=tmp;
                break;
            case 3:
                tmp=first; first=fourth; fourth=tmp;
                break;
        }

        switch(rand()%3){
            case 0:
                break;
            case 1:
                tmp=second; second=third; third=tmp;
                break;
            case 2:
                tmp=second; second=fourth; fourth=tmp;
                break;
        }

        /*if(row_column_move_amount(info,second)!=0){
            if(another_direction_no_affect(info,first,second)){
                return second;
            }
        }*/
        return first;
    }else if( (first_weight == second_weight) && (first_weight==third_weight) ){
        switch(rand()%3){
            case 0:
                break;
            case 1:
                tmp=first; first=second; second=tmp;
                break;
            case 2:
                tmp=first; first=third; third=tmp;
                break;
        }

        switch(rand()%2){
            case 0:
                break;
            case 1:
                tmp=second; second=third; third=tmp;
                break;
        }

        /*if(row_column_move_amount(info,second)!=0){
            if(another_direction_no_affect(info,first,second)){
                return second;
            }
        }*/
        return first;
    }else if( (first_weight == second_weight) ){
        switch(rand()%2){
            case 0:
                break;
            case 1:
                tmp=first; first=second; second=tmp;
                break;
        }

        /*if(row_column_move_amount(info,second)!=0){
            if(another_direction_no_affect(info,first,second)){
                return second;
            }
        }*/
        return first;
    }else{
        /*if(row_column_move_amount(info,second)!=0){
            if(another_direction_no_affect(info,first,second)){
                return second;
            }
        }*/
        return first;
    }
}
