#include <iostream>
#include <fstream>
#include "Threes.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define Max_times 100


using	namespace	std	;


typedef	struct Game_record Game_record	;


struct Game_record{

int	Max_point	;
int	All_point	;
int	Max_number	;
};


dir_e	get_next_dir( Grid )	;

inline	bool	Does_block_exist( const int , const int )	;

int	get_Merge_point( Grid , const dir_e )	;


int	get_Is_Merge_point( Grid )	;


int	get_Max_number_in_Grid( Grid& )	;


int	get_Max_number( int* , int )	;

bool	Does_move_dir( Grid , dir_e )	;


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
};
/* check 1, 2 pairs */
struct direction_1_2 red_blue(Grid info, int next_hint);
/* return 1 : pair, 0 : not pair */
int pairBFS(char maps[GRID_LENGTH][GRID_LENGTH], int x, int y);


int	main()
		{
			/*

			record init.


			*/
			
			
			FILE*	file	;

			Game_record	result	;

			int	Max_number[100]	;

			int	score		;

			int	Avg_point	=	0	;

			int	All_play_number	=	0	;

			int	i		=	0	;

			result.Max_point	=	0	;

			result.All_point	=	0	;

			result.Max_number	=	0	;

			
			Game	game	;

			Grid	need_info	;

			/*



			Run BOT 


			will work


			*/





			for( ; i < Max_times ; i++ )
				{


					game.reset()	;


					for( ; !game.isGameOver( score ) ; )
						{

						/*

						Threes BOt main part
				
						*/

						
						game.getCurrentGrid( need_info )	;

						game.insertDirection( get_next_dir( need_info ) )	;

						//cout << "ok  " << i  <<  " "  <<  score  << "\n"  << endl	;

						need_info.print( 30 , 20 )	;

						}

				
					result.All_point	=	result.All_point + score	;

					if( score > result.Max_point )
						{

							result.Max_point	=	score	;

						}
					

					Max_number[ i ]	=	get_Max_number_in_Grid( need_info )	;	


				}
		
			result.Max_number	=	get_Max_number( Max_number , 100 )	;



			





			/*


			Output result file


			*/


			All_play_number	=	i  			;
			
			Avg_point	=	result.All_point / All_play_number	;

			file	=	fopen( "./Game_end_result" , "w" )	;

			fclose( file )	;

			fstream	 result_file	;

			result_file.open( "./Game_end_result" )	;

			result_file << "All playing game number is " << All_play_number << " ." << endl	;

			result_file << "Max point is " << result.Max_point << " ." << endl	;

			result_file << "Average point is " << Avg_point << " ." << endl		;

			result_file << "Max number is " << result.Max_number << " ." << endl	;


			return	0	;

		}




int	get_Max_number_in_Grid( Grid&	info )
		{


			int	Max_number	=	0	;

			int	i				;


			for( i = 0 ; i < 16 ; i++ )
				{

					if( info[ i ] > Max_number )
						{

							Max_number	=	info[ i ]	;

						}

				}	


			return	Max_number	;

		}



int	get_Max_number( int* number_array , int Max )
		{


			int	Max_number	=	0	;

			int	i				;


			for( i = 0 ; i < Max ; i++ )
				{

					if( number_array[ i ] > Max_number )
						{

							Max_number	=	number_array[ i ]	;

						}

				}


			return	Max_number	;


		}



int	get_Merge_point( Grid now_stat , const dir_e dir )
		{


			int	row	;

			int	col	;


			int	Merge_point	=	0	;


			switch( dir )
				{

					case LEFT :

						for( col = 0 ; col < 3 ; col++ )
							{

							for( row = 0 ; row < 4 ; row++ )
								{

									if( now_stat.canMerge( now_stat( row , col ) , now_stat( row  , col + 1 ) ) )
										{

											Merge_point	=	Merge_point + 1	;
										
										}
								
								}	
							

							}
		
						return	Merge_point	;

					case RIGHT :

						for( col = 3 ; col > 0 ; col-- )
							{

								for( row = 0 ; row < 4 ; row++ )
									{

										if( now_stat.canMerge( now_stat( row , col ) , now_stat( row , col - 1 ) ) )
											{

												Merge_point	=	Merge_point + 1	;

											}

									}

							}

						return	Merge_point	;

					case UP :

						for( row = 0 ; row < 3 ; row++ )
							{

								for( col = 0 ; col < 4 ; col++ )
									{

										if( now_stat.canMerge( now_stat( row , col ) , now_stat( row + 1 , col ) ) )
											{

												Merge_point	=	Merge_point + 1 ;

											}

									}

							}
						
						return	Merge_point	;

					case DOWN :

						for( row = 3 ; row > 0 ; row-- )
							{

								for( col = 0 ; col < 4 ; col++ )
									{

										if( now_stat.canMerge( now_stat( row , col ) , now_stat( row - 1 , col ) ) )
											{

												Merge_point	=	Merge_point + 1	;

											}

									}

							}

						return	Merge_point	;

					default :
			
						return	0	;

				}	

		}




int	get_Is_Merge_point( Grid now_stat )
		{
		
			int	Is_Merge_point	=	0	;

			int	row	;

			int	col	;

			


			for( row = 0 ; row < 4 ; row++ )
				{

					for( col = 0 ; col < 4 ; col++ )
						{

							if( Does_block_exist( row + 1 , col ) )
								{
								
									if( now_stat.canMerge( now_stat( row , col ) , now_stat( row + 1 , col ) ) )
										{

											Is_Merge_point	=	Is_Merge_point + 1	;

										}

								}


							if( Does_block_exist( row - 1 , col ) )
								{

									if( now_stat.canMerge( now_stat( row , col ) , now_stat( row - 1 , col ) ) )
										{

											Is_Merge_point	=	Is_Merge_point + 1	;

										}

								}

							
							if( Does_block_exist( row , col + 1 ) )
								{

									if( now_stat.canMerge( now_stat( row , col ) , now_stat( row , col + 1 ) ) )
										{

											Is_Merge_point	=	Is_Merge_point + 1	;

										}

								}

							
							if( Does_block_exist( row , col - 1 ) )
								{

									if( now_stat.canMerge( now_stat( row , col ) , now_stat( row , col - 1 ) ) )
										{

											Is_Merge_point	=	Is_Merge_point + 1	;

										}

								}

						}

				}


			return	Is_Merge_point	;

		}

inline	bool	Does_block_exist( const int n1 , const int n2 )
		{
		
			if( ( ( n1 > -1 ) && ( n1 < 4 ) ) && ( ( n2 > -1 ) && ( n2 < 4 ) ) )
				{

					return	true	;	

				}

			return	false	;
		
		}

dir_e	get_next_dir( Grid now_stat )
		{

			int	LEFT_point	=	0	;

			int	RIGHT_point	=	0	;

			int	UP_point	=	0	;

			int	DOWN_point	=	0	;

			int	Max_L_or_R			;

			int	Max_U_or_D			;

			int	Max_point			;

			Grid	test				;

	

			test	=	now_stat	;

			if( Does_move_dir( test , LEFT ) )
				{

					LEFT_point	=	get_Merge_point( test , LEFT )	;

					test.shift( LEFT )	;

					LEFT_point	=	LEFT_point + get_Is_Merge_point( test )		;

				}
			


			test	=	now_stat	;



			if( Does_move_dir( test , RIGHT ) )
				{

					RIGHT_point	=	get_Merge_point( test , RIGHT )	;

					test.shift( RIGHT )	;

					RIGHT_point	=	RIGHT_point + get_Is_Merge_point( test )	;

				}



			
			test	=	now_stat	;

			if( Does_move_dir( test , UP ) )
				{

					UP_point	=	get_Merge_point( test , UP )	;

					test.shift( UP )	;

					UP_point	=	UP_point + get_Is_Merge_point( test )		;

				}




			test	=	now_stat	;

			if( Does_move_dir( test , DOWN ) )
				{

					DOWN_point	=	get_Merge_point( test , DOWN )	;

					test.shift( DOWN )	;

					DOWN_point	=	DOWN_point + get_Is_Merge_point( test )	;

				}






			/*


				determine   directy


			*/




			if( RIGHT_point > LEFT_point )
				{

					if( UP_point > RIGHT_point )
						{

							if( DOWN_point > UP_point )
								{

									return	DOWN	;

								}

							if( DOWN_point == UP_point )
								{

									if( ( int )( random() % 2 ) == 1 )
										{

											return	DOWN	;

										}

									return	UP	;

								}

							//	DOWN_point < UP_point

							return	UP	;

						}

					if( UP_point == RIGHT_point )
						{

							if( DOWN_point > UP_point )
								{

									return	DOWN	;

								}

							if( DOWN_point == UP_point )
								{

									switch( ( int )( random() % 3 ) )
										{

											case 0 :
												return	RIGHT	;
											case 1 :
												return	UP	;
											default :
												return	DOWN	;

										}

								}

							//	DOWN_point < UP_point
							

							if( ( int )( random() % 2 ) == 0 )
								{

									return	UP	;

								}

							return	RIGHT	;

						}

					
					//  UP_point  <  RIGHT_point


					if( DOWN_point > RIGHT_point )
						{
					
							return	DOWN	;

						}

					if( DOWN_point == RIGHT_point )
						{

							if( ( int )( random() % 2 ) == 0 )
								{

									return	DOWN	;

								}

							return	RIGHT	;

						}

					//	DOWN_point < RIGHT_point

					return	RIGHT	;

				}


			if( RIGHT_point == LEFT_point )
				{

					if( UP_point > RIGHT_point )
						{

							if( DOWN_point > UP_point )
								{

									return	DOWN	;

								}

							if( DOWN_point == UP_point )
								{
								
									if( ( int )( random() % 2 ) == 0 )
										{

											return	DOWN	;

										}

									return	UP	;

								}

							//	DOWN_point < UP_point

							return	UP	;

						}

					if( UP_point == RIGHT_point )
						{
						
							if( DOWN_point > UP_point )
								{

									return	DOWN	;

								}

							if( DOWN_point == UP_point )
								{

									switch( ( int )( random() % 4 ) )
										{

											case 0 :
												return	DOWN	;
											case 1 :
												return	UP	;
											case 2 :
												return	RIGHT	;
											default :
												return	LEFT	;

										}

								}

							//	DOWN_point < UP_point

							switch( ( int )( random() % 3 ) )
								{

									case 0 :
										return	UP	;
									case 1 :
										return	RIGHT	;
									default :
										return	LEFT	;

								}

						}

					//	UP_point < RIGHT_point

					if( DOWN_point > RIGHT_point )
						{

							return	DOWN	;

						}

					if( DOWN_point == RIGHT_point )
						{

							switch( ( int )( random() % 3 ) )
								{

									case 0 :
										return	DOWN	;
									case 1 :
										return	RIGHT	;
									default :
										return	LEFT	;

								}

						}

					//	DOWN_point < RIGHT_point

					if( ( int )( random() % 2 ) == 0 )
						{

							return	RIGHT	;

						}

					return	LEFT	;

				}
				
			//	RIGHT_point < LEFT_point

				if( UP_point > LEFT_point )
					{

						if( DOWN_point > UP_point )
							{

								return	DOWN	;

							}
						
						if( DOWN_point == UP_point )
							{

								if( ( int )( random() % 2 ) == 0 )
									{

										return	DOWN	;

									}

								return	UP	;

							}

						//	DOWN_point < UP_point

						return	UP	;
					}	
		
				if( UP_point == LEFT_point )
					{

						if( DOWN_point > UP_point )
							{

								return	DOWN	;

							}

						if( DOWN_point == UP_point )
							{

								switch( ( int )( random() % 3 ) )
									{

										case 0 :
											return	DOWN	;
										case 1 :
											return	UP	;
										default :
											return	LEFT	;

									}

							}

						//	DOWN_point < UP_point

						if( ( int )( random() % 2 ) == 0 )
							{

								return	UP	;

							}

						return	LEFT	;

					}

				//	UP_point < LEFT_point

				if( DOWN_point > LEFT_point )
					{

						return	DOWN	;

					}

				if( DOWN_point == LEFT_point )
					{

						if( ( int )( random() % 2 ) == 0 )
							{

								return	DOWN	;

							}

						return	LEFT	;

					}

				//	DOWN_point < LEFT_point

				return	LEFT	;

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



bool	Does_move_dir( Grid now_stat , dir_e dir )
		{

			Grid	dir_now_stat	=	now_stat	;

			int	i		=	0		;

			dir_now_stat.shift( dir )	;

			for( ; i < 16 ; i++ )
				{

					if( now_stat[ i ] != dir_now_stat[ i ] )
						{

							return	true	;

						}

				}

			return	false	;

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

struct direction_1_2 red_blue(Grid info,int next_hint){
    struct node not_pair[GRID_LENGTH*GRID_LENGTH],extract;
    int top;
    char maps[GRID_LENGTH][GRID_LENGTH]={0};
    struct direction_1_2 information;
    int outcome;

    information.down=0;
    information.left=0;
    information.up=0;
    information.right=0;
    information.one=0;
    information.two=0;

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
