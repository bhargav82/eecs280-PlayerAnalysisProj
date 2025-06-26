#include <gtest/gtest.h>
#include "../src/player_stats.hpp"



int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}




TEST(parse_args_test, parse_args) {

    const char* fake_args[] = {"./soccer_players", "country", "--price"};
    std::vector<std::string> result = {"./soccer_players", "country", "--price"};
    EXPECT_EQ(parse_arguments(3, const_cast<char**>(fake_args)), result);


    const char* fake_args_2[] = {"\n"};
    std::vector<std::string> result2;
    EXPECT_EQ(parse_arguments(0, const_cast<char**>(fake_args_2)), result2);


    const char* fake_args_3[] = {"23", "./soccer_players", "#@$@{}"};
    std::vector<std::string> result3 = {"23", "./soccer_players", "#@$@{}"};
    EXPECT_EQ(parse_arguments(3, const_cast<char**>(fake_args_3)), result3);
    
}


TEST(find_filters_test, find_filters) {
    
    std::vector<std::string> input_1 = {"./soccer_players", "--age", "-price", "--club"};
    const std::vector<std::string> result_flags_1 = {"--age", "--club"};
    EXPECT_EQ(find_flags(input_1), result_flags_1);


    std::vector<std::string> input_2 = {"./soccer_players"};
    std::vector<std::string> result_2;
    EXPECT_EQ(find_flags(input_2), result_2);
    
}

TEST(find_non_flags_test, find_non_flags){

    std::vector<std::string> input_1 = {"./soccer_players", "--age", "-price", "--club", "player_stats.csv"};
    const std::vector<std::string> result_flags_1;
    EXPECT_EQ(non_flag_inputs(input_1), result_flags_1);


    std::vector<std::string> input_2 = {"./soccer_players", "age", "karim benzema"};
    std::vector<std::string> result_2 = {"age", "karim benzema"};
    EXPECT_EQ(non_flag_inputs(input_2), result_2);
}



TEST(find_csv_test, find_csv) {

    std::vector<std::string> input1 = {"./soccer_players", "--age", "-price", "--club", "player_stats.csv"};
    std::string output = "player_stats.csv";
    EXPECT_EQ(find_csv(input1), output);


    std::vector<std::string> input2 = {"./soccer_players", "--age", "-price", "--club"};
    std::string output2 = "No File Input";
    EXPECT_EQ(find_csv(input2), output2);

}




TEST(check_flags_test, check_flags) {

    const std::vector<std::string> input1 = {"--name"};
    EXPECT_EQ(check_flags(input1), true);


    const std::vector<std::string> input2 = {"Name"};
    EXPECT_EQ(check_flags(input2), false);


    const std::vector<std::string> input3 = {"--name, country, -club"};
    EXPECT_EQ(check_flags(input3), false);


    const std::vector<std::string> input4 = {"--msrking"};
    EXPECT_EQ(check_flags(input4), false);


    const std::vector<std::string> input5 = {"--12"};
    EXPECT_EQ(check_flags(input5), false);

    const std::vector<std::string> input6 = {"--name", "country", "-club"};
    EXPECT_EQ(check_flags(input6), true);

}

TEST(check_similarity_score, similarity_score) {

    Player a = {"John Doe", 23, "USA", 180, 90, "FC Barcalona", "$13,000,000", {12, 32, 543}};
    Player b = {"John Doe", 23, "USA", 180, 90, "FC Barcalona", "$13,000,000", {12, 32, 543}};
    EXPECT_EQ(similarity(a, b), 0);


    Player c = {"John Doe", 23, "USA", 180, 90, "FC Barcalona", "$13,000,000", {12, 32, 543, 323, 313}};
    Player d = {"John Doe", 23, "USA", 180, 90, "FC Barcalona", "$13,000,000", {12, 32, 543}};
    EXPECT_EQ(similarity(c, d), 0);


    Player e = {"John Doe", 23, "USA", 180, 90, "FC Barcalona", "$13,000,000", {12, 32, 543, 323, 313}};
    Player f = {"John Doe", 23, "USA", 180, 90, "FC Barcalona", "$13,000,000", {13, 32, 543}};
    EXPECT_EQ(similarity(e, f), 1);


    Player g = {"John Doe", 23, "USA", 180, 90, "FC Barcalona", "$13,000,000", {14, 32, 543}};
    Player h = {"John Doe", 23, "USA", 180, 90, "FC Barcalona", "$13,000,000", {12, 32, 543, 323, 313}};
    EXPECT_EQ(similarity(g, h), 2);

}


TEST(to_lower_test, to_lower){
    
    std::string word = "LOWERcase";
    EXPECT_EQ(to_lower(word), "lowercase");

    
    std::string word2 = "12lLO#";
    EXPECT_EQ(to_lower(word2), "12llo#");
}


TEST(max_num_test, max_num) {

    std::vector<int> input1 = {1, 2, 3};
    EXPECT_EQ(max(input1), 3);

    std::vector<int> input2 = {1, 2, -3};
    EXPECT_EQ(max(input2), 2);

    std::vector<int> input3 = {3, 4, 2};
    EXPECT_EQ(max(input3), 4);
}


