#include <iostream>
#include "player_stats.hpp"
using namespace std;


int main(int argc, char *argv[]) {

	// find arguments and execute
	if ( argc > 1 ) {
		std::vector<std::string> args = parse_arguments(argc, argv);
		std::cout << args.size() << std::endl;

	} 
	else {
		std::cout << argc;
		// show menu and allow user to pick a task.
	}
	return 0;

}
