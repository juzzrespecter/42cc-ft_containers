#include "tester.hpp"

long get_time( void ) {

	struct timeval	time_s;
	long			time;

	gettimeofday( &time_s, NULL );
	time = time_s.tv_sec * 1000 + ( long )time_s.tv_usec / 1000;
	return ( time );
}

static void ( *test_table[ N_TEST ] )( void ) = {

	vector_tests,
	map_tests,
	stack_tests,
	set_tests
};

int main( int argc, char *argv[] ) {

	static std::string	buffer;
	char			*ptr;

	if ( argc != 2 ) { // test rand( ) seed
		
		std::cout << "at least one argument needed\n";
		std::cout << "usage: ./ft_containers_test seed\n";
		return EXIT_FAILURE;
	}
	srand( std::atoi( argv[1] ) );
	while ( 1 ) {

		system( "clear" );
		std::cout << "[ ft_containers tester ]\n\n"
			  << "\t " << ID( 0 ) << "  test vector container\n"
			  << "\t " << ID( 1 ) << "  test map container\n"
			  << "\t " << ID( 2 ) << "  test stack container\n"
			  << "\t " << ID( 3 ) << "  test set container\n"
			  << "\t  ---\n"
			  << "\t " << ID( 4 ) << "  exit\n";
		while ( 1 ) {
			
			std::cout << ">> ";
			getline( std::cin, buffer );

			int id = strtol( buffer.c_str( ), &ptr, 0 );
			if ( !*ptr && id >= 0 && id < N_TEST ) {

				system( "clear" );
				test_table[ id ]( );
				std::cout << "< press ENTER to continue... >";
				getline( std::cin, buffer );
				break ;
			}
			if ( id == 4 ) {

				std::cout << "bye\n";
				return EXIT_SUCCESS;
			}
		}
	}
	return EXIT_SUCCESS;
}
