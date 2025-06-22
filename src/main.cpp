#include <iostream>
#include "player_stats.hpp"
using namespace std;


int main(int argc, char *argv[]) {

	// find arguments and execute
	// if ( argc > 1 ) {
	// 	std::vector<std::string> args = parse_arguments(argc, argv);
		

	// } 
	// // show menu and allow user to pick a task.
	// else {
	// 	std::cout << argc;
		

	// }

	if (argc <= 1) {
		std::cout << "Please enter a filename, filter, and flag" << std::endl;
		std::cout << "Flags include: age, country, or any of the stats" << std::endl;
		return 1;
	}



	
	const std::vector<std::string> arguments = parse_arguments(argc, argv);

	const std::vector<std::string> flags = find_flags(arguments);
	const std::vector<std::string> filters = non_flag_inputs(arguments);
	const std::string fileName = find_csv(arguments);

	const std::vector<Player> players = create_player_vector(fileName);



	return 0;

}
