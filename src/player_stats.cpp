#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>
#include "player_stats.hpp"


bool check_flags(const std::vector<std::string>& flags) {
	std::vector<std::string> available_flags = {"--name", "--country", "--club", "--vision", "--agility", "--marking", "--value"};

	for (std::string flag : flags){
		for (std::string available : available_flags){
			if (flag == available){
				return true;
			}
		}
	}

	return false;
}

std::vector<Player> filter_by_flag(const std::vector<Player>& all_players, const std::vector<std::string>& flags, const std::vector<std::string>& non_input_flags, const std::vector<std::string>& headers){
	
	std::vector<Player> players;

	for (std::string flag : flags){
		if (flag == "--chart"){
			std::string name = non_input_flags.at(0);

			for (Player p : all_players) {
				if (p.name.find(name) != std::string::npos) {
					print_histogram(p, headers);
					players.push_back(p);
					
				}
			}
		}
		
	}
	return players;
}

// stores command line inputs into vec
const std::vector<std::string> parse_arguments(int argc, char* argv[]) {
	

	// return vector of arguments
	std::vector<std::string> arguments; 
	int counter = 0;
	while (counter < argc) {
		arguments.push_back(argv[counter++]);
	}

	return arguments;
	

}

const std::string find_csv(const std::vector<std::string>& arguments) {
	
	for (std::string arg : arguments){
		if (arg.find(".csv") != std::string::npos) {
			return arg;
		}	
	}
	
	return "No File Input";
}


// finds flags/filters (inputs with "--")
const std::vector<std::string> find_flags(const std::vector<std::string>& arguments) {

	std::vector<std::string> flags;

	for (std::string arg : arguments)
	{
		std::string arg_string = arg;
		if (arg_string.find("--") != std::string::npos){
			flags.push_back(arg_string);
		}
	}
	return flags;
}


// store all inputs except flags and files
const std::vector<std::string> non_flag_inputs(const std::vector<std::string>& arguments) {

	std::vector<std::string> filters;

	for (std::string arg : arguments) {
		if (arg.find("-") == std::string::npos && arg.find(".csv") == std::string::npos && arg.find("./") == std::string::npos){
			filters.push_back(arg);
		}
	}
	
	return filters;
}


const std::vector<std::string> find_headers(const std::string &filename) {

	std::ifstream inputFile;
	inputFile.open(filename);

	if (!inputFile.is_open()) {
		std::cerr << "Error opening up file: " << filename << std::endl;
	}

	std::string first_line;
	getline(inputFile, first_line);
	std::stringstream columns(first_line);
	std::string data;
	std::vector<std::string> headers;

	while (getline(columns, data, ',')) {
		headers.push_back(data);
	}


	return headers;
}

// parse file and convert each line to Player (struct), store in a vector of Players
const std::vector<Player> create_player_vector(const std::string& fileName) {

	std::ifstream inputFile;

  	inputFile.open(fileName);

  	if (!inputFile.is_open()) {
     	std::cerr << "Error opening up file" << fileName << std::endl;

  	}

	std::string first_line;
	getline(inputFile, first_line);
	



	

	std::vector<Player> all_players;
	std::string line;

  	while (getline(inputFile, line)) {

		Player new_player;

		std::vector<std::string> player_info;
		std::vector<int> player_stats;

		std::stringstream line_stringstream(line);
		std::string token;

    	while (getline(line_stringstream, token, ',')) {
			player_info.push_back(token);
		}

		new_player.name = player_info.at(0);
		new_player.country = player_info.at(1);
		new_player.height_cm = std::stoi(player_info.at(2));
		new_player.weight_kg = std::stoi(player_info.at(3));
		new_player.age = std::stoi(player_info.at(4));
		new_player.club = player_info.at(5);

		
		size_t player_info_length = player_info.size();


		for (size_t i = 6; i < player_info_length - 1; i++) {

			try {
				new_player.stats.push_back(std::stoi(player_info.at(i)));
			}

			catch (const std::invalid_argument& error){
				new_player.stats.push_back(0);
			}
		}

		new_player.value = player_info.at(player_info_length - 1);
		all_players.push_back(new_player);

  	}



	inputFile.close();

	return all_players;
	
}




/* We will have to assume the player data is up-to-date */
/* Take in reference to player, returns year born */
int ageToYearBorn ( Player &p ) {
	std::cout << "Calculating what year " << p.name << " was born " << std::endl;
	int age = p.age;

	time_t today = time( NULL ); // gives me a timestape
	tm* local_time = localtime( &today ); // gives me a struct of time info
	/* from the documentation about localtime()  see https://cplusplus.com/reference/ctime/localtime/
	 * "The returned value points to an internal object whose validity or value may be altered 
	 * by any subsequent call to gmtime or localtime."
	 * Thus, we should copy the info out before we call the function again.
	 */
	int month = local_time->tm_mon + 1; // tm_mon is month 0-11 (so we add 1).
	int year = local_time->tm_year; // gives us the year from 1900
	year += 1900;
	std::cout << "Today is the " << month << " month of " << year << std::endl;
	int yearBorn = year - age; // calculate the year born by subtracting age
	std::cout << p.name << " was born in the year " << yearBorn << std::endl;
	return yearBorn;
}





// compares two players stats of equal length, returns [0, 100] similarity score

int similarity( Player &a, Player &b ){
	int similarity_percent = 0;

	std::vector<int> player_a_stats = a.stats;
	std::vector<int> player_b_stats = b.stats;

	int min = std::min(a.stats.size(), b.stats.size());
	double summation = 0;

	for (int i = 0; i < min; i++){
		summation += std::pow( a.stats.at(i) - b.stats.at(i), 2);
	}

	summation = std::sqrt(summation);
	similarity_percent = (1/(1 + summation)) * 100;

	return similarity_percent;
}



// only call when chart invoked 
void print_histogram(Player& p, const std::vector<std::string> &headers){
	int increment = 6;
	for (int stat : p.stats){
		int count = 0;
		
		std::cout << headers.at(increment++) << ": ";
		while (count < stat){
			std::cout << "-";
			count++;
		}
		std::cout << std::endl;
		
	}

}