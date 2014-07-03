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


int	get_Max_number_in_Grid( Grid& )	;


int	get_Max_number( int* , int )	;


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




