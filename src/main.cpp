#include <iostream>
#include "player_stats.hpp"
using namespace std;


int main(int argc, char *argv[]) {



	if (argc <= 1) {
		std::cout << "Please enter a filename, filter, and flag" << std::endl;
		std::cout << "Flags include: age, country, or any of the stats" << std::endl;
		return 1;
	}

	


	
	const std::vector<std::string> arguments = parse_arguments(argc, argv);

	const std::vector<std::string> flags = find_flags(arguments);
	const std::vector<std::string> filters = non_flag_inputs(arguments);
	const std::string fileName = find_csv(arguments);


	const std::vector<std::string> headers = find_headers(fileName);
	const std::vector<Player> players = create_player_vector(fileName);
	

	std::vector<Player> filtered = filter_by_flag(players, flags, filters, headers);





	return 0;

}
