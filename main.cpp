#include <iostream>
#include <fstream>
#include "Threes.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


using	namespace	std	;


typedef	struct Game_record Game_record	;


struct Game_record{

int	Max_point	;
int	All_point	;
int	Max_number	;
};

inline	bool	Does_block_exist( const int , const int )	;

int	get_Merge_point( Grid , const dir_e )	;


int	get_Is_Merge_point( Grid )	;


int	get_Max_number_in_Grid( Grid& )	;


int	get_Max_number( int* , int )	;

/* test whether the row would be moved with left or right */
bool row_full(Grid info,int row);

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





			for( ; i < 100 ; i++ )
				{


					game.reset()	;


					for( ; !game.isGameOver( score ) ; )
						{

						/*

						Threes BOt main part
				
						*/


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


			All_play_number	=	i + 1			;
			
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
