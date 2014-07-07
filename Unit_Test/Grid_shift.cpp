#include <iostream>
#include "../Threes.h"



using	namespace	std	;






int	main()
		{

		
		Game t_game	;
	
		Grid	t_info	;


		dir_e	dir	=	LEFT	;

		t_game.getCurrentGrid( t_info )	;

		t_info.print()	;


		t_info.shift( dir )	;


		cout << "\n" << "\n" << "\n"  << "\n"  <<  "\n"  << endl	;

		t_info.print( 30 )		;


		return	0	;

		}

