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
int	Stage_number	;
};


int	main()
		{
			/*

			record init.


			*/
			
			
			FILE*	file	;

			Game_record	result	;

			int	Avg_point	=	0	;

			int	All_play_number	=	0	;

			result.Max_point	=	0	;

			result.All_point	=	0	;

			result.Max_number	=	0	;

			result.Stage_number	=	0	;

			/*



			Run BOT 


			will work


			*/







			/*


			Output result file


			*/

			
			Avg_point	=	result.All_point / 100	;

			file	=	fopen( "./Game_end_result" , "w" )	;

			fclose( file )	;

			fstream	 result_file	;

			result_file.open( "./Game_end_result" )	;

			result_file << "All playing game number is " << All_play_number << " ." << endl	;

			result_file << "Max point is " << result.Max_point << " ." << endl	;

			result_file << "Average point is " << Avg_point << " ." << endl		;

			result_file << "Max number is " << result.Max_number << " ." << endl	;

			result_file << "Stage number is " << result.Stage_number << " ." << endl ;

			


			return	0	;

		}

