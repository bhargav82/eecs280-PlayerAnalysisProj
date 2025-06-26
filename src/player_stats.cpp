#include "player_stats.hpp"



/*
Requires: vector of string - pass in the flags (anything with --), take output vector from find_flags()
Effect: checks if user inputted available flags
Returns: True (if flag is available), False (otherwise)
*/
bool check_flags(const std::vector<std::string>& flags) 
{
	std::vector<std::string> available_flags = {"--name", "--country", "--club", "--vision", "--agility", "--marking", "--value"};

	for (std::string flag : flags)
	{
		for (std::string available : available_flags)
		{
			if (flag == available)
			{
				return true;
			}
		}
	}

	return false;

}


/*
Requires: vector of strings - pass in the arguments that aren't files or flags, take output vector from non_flag_inputs()
Effect: does not matter if user used " ", will create a string
Returns: a string that can be compared to strings in csv file
*/
const std::string fixUserInput(const std::vector<std::string>& non_flag_inputs)
{
	std::string userInput;
	for (std::string flag : non_flag_inputs)
	{
		userInput += flag + " ";
	}

	if (!userInput.empty())
	{	
		userInput.pop_back();
	}

	return userInput;
}


/*
Requires: arguments from terminal
Effect: parses through all arguments (starting with executable), allows for flexible inputs
Returns: vector of strings containing user inputted arguments
*/
const std::vector<std::string> parse_arguments(int argc, char* argv[])
{	
	std::vector<std::string> arguments; 
	int counter = 0;
	while (counter < argc) 
	{
		arguments.push_back(argv[counter++]);
	}

	return arguments;
}


/*
Requires: vector of strings -> pass in return vector from parse_arguments()
Effect: checks if the user inputted a csv file and stores it, if not can check in main and fail gracefully
Returns: string which is the filename
*/
const std::string find_csv(const std::vector<std::string>& arguments) 
{
	
	for (std::string arg : arguments){
		if (arg.find(".csv") != std::string::npos) 
		{
			return arg;
		}	
	}
	
	return "No File Input";
}

/*
Requires: vector of strings -> pass in return vector from parse_arguments()
Effect: checks if user inputted available flags, adds to vector
Returns: vector of strings containing flags (anything with --)
*/
const std::vector<std::string> find_flags(const std::vector<std::string>& arguments)
{
	std::vector<std::string> flags;

	for (std::string arg : arguments)
	{
		std::string arg_string = arg;
		if (arg_string.find("--") != std::string::npos)
		{
			flags.push_back(arg_string);
		}
	}
	return flags;
}


/*
Requires: vector of string - pass in the return flag from arguments
Effect: checks if user inputted anythig that is not a file or flag (--), adds to vector
Returns: returns vector of strings, which are non_flag_inputs
*/
const std::vector<std::string> non_flag_inputs(const std::vector<std::string>& arguments)
{

	std::vector<std::string> filters;

	for (std::string arg : arguments)
	{
		// only store arguments that aren't flags or files (absolute or relative paths)
		if (arg.find("-") == std::string::npos && arg.find(".") == std::string::npos && arg.find("/") == std::string::npos)
		{
			filters.push_back(arg);
		}
	}
	
	return filters;
}

/*
Requires: string containing filename - should only be called if find_csv was NOT "No File Input" in main
Effect: parses through csv, takes in the first line, splits by comma delimiter, and pushes each header into vector
Returns: vector of strings that contains each header of player info -> used when printing histogram
*/
const std::vector<std::string> find_headers(const std::string &filename) 
{
	std::ifstream inputFile;
	inputFile.open(filename);

	if (!inputFile.is_open()) 
	{
		std::cerr << "Error opening up file: " << filename << std::endl;
	}

	// only read in first line of csv
	std::string first_line;
	getline(inputFile, first_line);

	std::stringstream columns(first_line);
	std::string data;
	std::vector<std::string> headers;

	while (getline(columns, data, ',')) 
	{
		headers.push_back(data);
	}

	inputFile.close();
	return headers;
}

/*
Requires: string containing filename, same requirement as find_headers()
Effect: parse through csv, and convert each line into a player, using the Player struct
Returns: vector of players containing all players
*/
const std::vector<Player> create_player_vector(const std::string& fileName) 
{
	std::ifstream inputFile;
  	inputFile.open(fileName);

  	if (!inputFile.is_open()) 
	{
     	std::cerr << "Error opening up file: " << fileName << std::endl;
  	}

	// skip first line (headers)
	std::string first_line;
	getline(inputFile, first_line);

	std::vector<Player> all_players;
	std::string line;

  	while (getline(inputFile, line)) 
	{
		// new instance of player for each line
		Player new_player;

		std::vector<std::string> player_info;
		std::vector<int> player_stats;

		std::stringstream line_stringstream(line);
		std::string token;

		// split line by commas, store in a vector (we know what each index should be)
    	while (getline(line_stringstream, token, ',')) 
		{
			player_info.push_back(token);
		}

		// first six columns are known types
		new_player.name = to_lower(player_info.at(0));									// change name to lowercase, makes it easy to check against user input
		new_player.country = player_info.at(1);
		new_player.height_cm = std::stoi(player_info.at(2));
		new_player.weight_kg = std::stoi(player_info.at(3));
		new_player.age = std::stoi(player_info.at(4));
		new_player.club = player_info.at(5);

		
		// go through stats, try to convert to an int, if not must be "None" or "" -> change to 0
		size_t player_info_length = player_info.size();
		for (size_t i = 6; i < player_info_length - 1; i++) 
		{
			try 
			{
				new_player.stats.push_back(std::stoi(player_info.at(i)));
			}

			catch (const std::invalid_argument& error)
			{
				new_player.stats.push_back(0);
			}
		}

		new_player.value = player_info.at(player_info_length - 1);
		all_players.push_back(new_player);

  	}
	inputFile.close();

	return all_players;
}

/*
Requires: vector of all players, a string with user input, and vector of headers, 
			if --chart called, call create_chart (should also call fixUserInput() on the non_flag_inputs)
Effect: check user input against all player names (after converting both to lowercase), 
		keep filtering (calling function) until there is only 1 player, then print player's histogram 
Returns: vector of player, should only be only length 1, containing final filtered player
*/
std::vector<Player> create_chart(const std::vector<Player>& all_players, std::string& input, const std::vector<std::string>& headers)
{
	std::vector<Player> filtered_players;
	input = to_lower(input);															// change user input to lowercase to match name (already lowercase)

	for (Player p : all_players)
	{
		
		if (p.name.find(input) != std::string::npos)
		{
			filtered_players.push_back(p);
		}
	}

	size_t filtered_players_size = filtered_players.size();
	if (filtered_players_size < 1) 
	{
		std::cout << "No players available" << std::endl;
		return {};
	}

	else if (filtered_players_size == 1)
	{
		std::cout << "You choose : " << filtered_players.at(0).name << std::endl;
		print_histogram(filtered_players.at(0), headers);
		return filtered_players;
	}		
	// if there are more than 1 players, ask for new input and rerun filtering until 1 player, with new filtered vector and new input
	else
	{
		std::cout << "Choose one of the following players: " << std::endl;
		for (Player new_player : filtered_players)
		{
			std::cout << new_player.name << std::endl;
		}
		std::string new_name;
		std::getline(std::cin, new_name);
		new_name = to_lower(new_name);
		return create_chart(filtered_players, new_name, headers);
	}
	
}


/*
Requires: vector of players and user inputted country, does not matter if user capitalized country, but must be spelled right
Effect: go through all players and add only the players from the matching country to a vector
Returns: vector of players containing players from country
*/
std::vector<Player> country_filter(const std::vector<Player>& players, std::string country)
{
	std::vector<Player> players_from_country;
	country[0] = toupper(country[0]);														// in case user inputs lowercase country

	for (Player p : players)
	{
		if (p.country == country)
		{
			players_from_country.push_back(p);
		}
	}

	size_t filtered_players_size = players_from_country.size();
	if (filtered_players_size < 1)
	{
		std::cout << "No players from this country." << std::endl;
		return {};
	}
	else
	{
		for (Player filtered_player : players_from_country)
		{
			std::cout << filtered_player.name << std::endl;
		}
		return players_from_country;
	}
}

/*
Requires: vector of players and user inputted club, only call when --club flag is invoked, user does not need to put club in quotes
Effect: fix the club input (add a space) to match csv file, go through all players, add players with matching clubs to vector
Returns: vector of players containing players from club
*/
std::vector<Player> club_filter(const std::vector<Player>& all_players, std::string club_input)
{
	std::vector<Player> players_by_club;
	club_input += " ";																			// csv file has space after club

	for (Player p : all_players)
	{
		if (p.club == club_input)
		{
			players_by_club.push_back(p);
		}
	}

	size_t club_players_size = players_by_club.size();

	if (club_players_size < 1)
	{
		std::cout << "There are no players from this club." << std::endl;
		return {};
	}
	else 
	{
		for (Player p : players_by_club)
		{
			std::cout << p.name << std::endl;
		}
		return players_by_club;
	}
}

/*
Requires: vector of players and user inputted player, does not matter if user capitalized name, or put name in quotes, only invoke when --value
Effect: keeps filtering based on name until there is only 1 player, filtered result keeps being passed in, 
		so user doesn't have to type in full name and print value of player
Returns: vector of player with corresponding name, should only be length <= 1
*/
std::vector<Player> value_filter(const std::vector<Player>& all_players, std::string player_name)
{
	player_name = to_lower(player_name);
	std::vector<Player> players_with_name;
	std::vector<std::string> corresponding_values;

	for (Player p : all_players)
	{
		if (p.name.find(player_name) != std::string::npos)
		{
			players_with_name.push_back(p);
			corresponding_values.push_back(p.value);
		}
	}

	size_t player_with_name_size = players_with_name.size();
	if (player_with_name_size < 1)
	{
		std::cout << "There are no players with this name. " << std::endl;
		return {};
	}
	else if (player_with_name_size == 1) 
	{
		std::cout << corresponding_values.at(0) << std::endl;
		return players_with_name;
	}
	// keeps asking for new input and filters over and over, until there is 1 person
	else
	{
		std::cout << "Choose one of the following players: " << std::endl;
		for (Player& p : players_with_name)
		{
			std::cout << p.name << std::endl;
		}
		std::string new_player;
		std::getline(std::cin, new_player);
		return value_filter(players_with_name, new_player);
		
	}
}

/*
Requires: vector of players and user inputted filter, must be in quotes, but could be <, >, =, or nothing (which is equals)
Effect: for all players and given filters, only add players that fit requirement
Returns: vector of players with given attribute
*/
std::vector<Player> vision_filter(const std::vector<Player>& all_players, std::string filter)
{	
	std::vector<Player> vision_players;
	if (filter.at(0) == '<')
	{
		filter = filter.substr(1);
		int num_filter = stoi(filter);

		for (Player p : all_players)
		{
			if (p.stats.at(9) < num_filter)
			{
				vision_players.push_back(p);
			}
		}
	}
	else if (filter.at(0) == '>')
	{
		filter = filter.substr(1);
		int num_filter = stoi(filter);

		for (Player p : all_players)
		{
			if (p.stats.at(9) > num_filter)
			{
				vision_players.push_back(p);
			}
		}
	}
	// if not < or >, must be = or nothing which is =
	else 
	{	
		if (filter.at(0) == '=')
		{
			filter = filter.substr(1);
		}
		for (Player p : all_players)
		{
			int num_filter = stoi(filter);
			if (p.stats.at(9) == num_filter)
			{
				vision_players.push_back(p);
			}
		}
	}
	for (Player& p : vision_players)
	{
		std::cout << p.name << std::endl;
	}

	if (vision_players.size() < 1)
	{
		std::cout << "No player available." << std::endl;
	}
	return vision_players;
}


/*
Requires: vector of players and user inputted filter, must be in quotes, but could be <, >, =, or nothing (which is equals)
Effect: for all players and given filters, only add players that fit requirement
Returns: vector of players with given attribute
*/
std::vector<Player> agility_filter(const std::vector<Player>& all_players, std::string filter)
{	
	std::vector<Player> agility_players;
	if (filter.at(0) == '<')
	{
		filter = filter.substr(1);
		int num_filter = stoi(filter);

		for (Player p : all_players)
		{
			if (p.stats.at(19) < num_filter)
			{
				agility_players.push_back(p);
			}
		}
	}
	else if (filter.at(0) == '>')
	{
		filter = filter.substr(1);
		int num_filter = stoi(filter);

		for (Player p : all_players)
		{
			if (p.stats.at(19) > num_filter)
			{
				agility_players.push_back(p);
			}
		}
	}
	else 
	{	
		if (filter.at(0) == '=')
		{
			filter = filter.substr(1);
		}
		for (Player p : all_players)
		{
			int num_filter = stoi(filter);
			if (p.stats.at(19) == num_filter)
			{
				agility_players.push_back(p);
			}
		}
	}
	for (Player& p : agility_players)
	{
		std::cout << p.name << std::endl;
	}
	if (agility_players.size() < 1)
	{
		std::cout << "No player available." << std::endl;
	}
	return agility_players;
}

/*
Requires: vector of players and user inputted filter, must be in quotes, but could be <, >, =, or nothing (which is equals)
Effect: for all players and given filters, only add players that fit requirement
Returns: vector of players with given attribute
*/
std::vector<Player> marking_filter(const std::vector<Player>& all_players, std::string filter)
{	
	std::vector<Player> marking_players;
	if (filter.at(0) == '<')
	{
		filter = filter.substr(1);
		int num_filter = stoi(filter);
		for (Player p : all_players)
		{
			if (p.stats.at(2) < num_filter)
			{
				marking_players.push_back(p);
			}
		}
	}
	else if (filter.at(0) == '>')
	{
		filter = filter.substr(1);	
		int num_filter = stoi(filter);
		for (Player p : all_players)
		{
			if (p.stats.at(2) > num_filter)
			{
				marking_players.push_back(p);
			}
		}
	}
	else 
	{	
		if (filter.at(0) == '=')
		{
			filter = filter.substr(1);
		}
		for (Player p : all_players)
		{
			int num_filter = stoi(filter);
			if (p.stats.at(2) == num_filter)
			{
				marking_players.push_back(p);
			}
		}
	}
	for (Player& p : marking_players)
	{
		std::cout << p.name << std::endl;
	}
	if (marking_players.size() < 1)
	{
		std::cout << "No player available." << std::endl;
	}
	return marking_players;
}


/*
Requires: vector of all players, vector of strings containing flags, vector of strings containing inputs, and vector of strings containing headers
Effect: 
Returns: 
*/
std::vector<Player> filter_by_flag(const std::vector<Player>& all_players, const std::vector<std::string>& flags, const std::vector<std::string>& non_input_flags, const std::vector<std::string>& headers)
{
	std::vector<Player> players;
	std::string userInput = fixUserInput(non_input_flags);
	bool has_find_most_similiar = false;
	bool has_chart = false;

	for (std::string flag : flags)
	{
		if (flag == "--chart")
		{
			players = create_chart(all_players, userInput, headers);
			has_chart = true;
			return players;																	// could have --chart and --name, don't want infocard, just histogram, so return after
		}
		else if (flag == "--country")
		{	
			players = country_filter(all_players, userInput);
		}
		else if (flag == "--club")
		{
			players = club_filter(all_players, userInput);
		}
		else if (flag == "--value")
		{
			players = value_filter(all_players, userInput);								// same as --chart
			return players;
		}
		else if (flag == "--vision" || flag == "--agility" || flag == "--marking")
		{
			if (flag == "--vision")
			{
				players = vision_filter(all_players, userInput);
			}
			
			if (flag == "--agility")
			{
				players = agility_filter(all_players, userInput);
			}

			if (flag == "--marking")
			{
				players = marking_filter(all_players, userInput);
			}
		}
		else if (flag == "--name")
		{
			std::vector<Player> filtered_players = find_1_player(all_players, userInput);
			
			if (filtered_players.empty())
			{
				std::cout << "There are no players with this name." << std::endl;
				continue;
			}

			
			Player player_a = filtered_players.at(0);


			for (std::string new_flag : flags)
			{
				if (new_flag == "--findmostsimilar")										// don't want to print most similar player and infocard
				{
					has_find_most_similiar = true;
				}
			}
			if (has_find_most_similiar)
			{
				
				players = find_most_similar(all_players, player_a, player_a.name);
				
			}
			else if (!has_chart)
			{
				std::string new_name = player_a.name;
				players = create_chart(all_players, new_name, headers);
				return players;
				
			}
			else
			{
				print_player_infocard(player_a, all_players);
			}
		}
	}
	return players;
}




/*
Requires: vector of players, player a, and inputted name (should be same name as player a) 
		- only invoke when --find_most_similar and --name are called but order does not matter and also shouldn't print infocard
Effect: go through all players, skip over player a, and call similarities on player a stats and every other player stats, put similarties scores in vector,
		find minimum from similarty score (closest player stats-wise using Euclidean formula)
Returns: vector of players, should just be 1 player, who has the closest stats
*/
std::vector<Player> find_most_similar(const std::vector<Player>& players,  Player& a, std::string name_of_p1)
{
	std::vector<Player> all_other_players;
	std::vector<int> similarity_scores;

	for (Player p : players)
	{	
		if (p.name != name_of_p1)
		{
			all_other_players.push_back(p);
			similarity_scores.push_back(similarity(a, p));
		}
	}

	int most_similar = min(similarity_scores);
	for (Player player_b : all_other_players)
	{
		if (most_similar == similarity(a, player_b)){
			std::cout << player_b.name << std::endl;
		}
	}

	return all_other_players;
}



int similarity( Player &a, Player &b )
{
	int similarity_percent = 0;
	int min = std::min(a.stats.size(), b.stats.size());
	double summation = 0.0;

	for (int i = 0; i < min; i++){
		summation += std::pow( a.stats.at(i) - b.stats.at(i), 2);
	}
	similarity_percent = std::sqrt(summation);

	return similarity_percent;
}


/*
Requires: vector of players and user inputted name
Effect: keep calling find_1_player, using input (after lowercased) until the vector is only of length <= 1
Returns: vector of player, should only have length of 0 or 1
*/

std::vector<Player> find_1_player(const std::vector<Player>& multiple_players, std::string input)
{
	input = to_lower(input);
	std::vector<Player> one_player;
	for (Player p : multiple_players)
	{
		if (p.name.find(input) != std::string::npos)
		{
			one_player.push_back(p);
		}
	}
	
	if (one_player.size() <= 1)
	{
		return one_player;
	}
	else
	{
		std::cout << "Choose one of the following players: " << std::endl;
		for (Player p : one_player)
		{
			std::cout << p.name << std::endl;
		}
		std::string new_input;
		getline(std::cin, new_input);
		return find_1_player(one_player, new_input);
	}
}

const std::string to_lower(std::string& word)
{
	std::string lower;
	for (char &c : word){
		lower += std::towlower(c);
	}
	return lower;
}


void print_histogram(Player& p, const std::vector<std::string> &headers)
{
	size_t max_length = 0;
	for (std::string header : headers)
	{
		if (max_length < header.size())
		{
			max_length = header.size();
		}
	}

	int increment = 6;
	for (int stat : p.stats){
		int count = 0;
		std::cout << std::setw(max_length) << headers.at(increment++) << ": ";
		while (count < stat){
			std::cout << "-";
			count++;
		}
		std::cout << std::endl;
	}
}


int max(std::vector<int>& nums)
{
	int max = nums.at(0);
	for (int num : nums){
		if (num > max){
			max = num;
		}
	}
	return max;
}


int min(std::vector<int>& nums){
	int min = nums.at(0);
	for (int num : nums){
		if (num < min){
			min = num;
		}
	}
	return min;
}


void print_player_infocard(Player &p, std::vector<Player> all_players)
{
	bool does_player_exist = false;
	for (Player each_player : all_players)
	{	
		if (each_player.name == p.name)
		{
			does_player_exist = true;
		}
	}
	if (does_player_exist)
	{
		char buffer[100];
		std::cout << "####################################################" << std::endl;
		snprintf(buffer, sizeof(buffer), "## Name: %-40s ##", p.name.c_str() ); 								
		std::cout << buffer << std::endl;
		snprintf(buffer, sizeof(buffer), "## Nation: %-38s ##", p.country.c_str() );
		std::cout << buffer << std::endl;
		snprintf(buffer, sizeof(buffer),"## Age: %-41d ##", p.age);
		std::cout << buffer << std::endl;
		snprintf(buffer, sizeof(buffer), "## Height (cm): %-33d ##", p.height_cm);
		std::cout << buffer << std::endl;
		snprintf(buffer, sizeof(buffer), "## Weight (kg): %-32d  ##", p.weight_kg);
		std::cout << buffer << std::endl;
		std::cout << "####################################################" << std::endl;
	}
	else{
		std::cout << "No player available" << std::endl;
	}
}


/* We will have to assume the player data is up-to-date */
/* Take in reference to player, returns year born */
int ageToYearBorn ( Player &p ) 
{
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



// ADD tests.cpp and fix readme