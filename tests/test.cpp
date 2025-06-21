#include <gtest/gtest.h>
#include "../src/player_stats.hpp"



int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// only return a vector of strings containing "--"
TEST(find_filters_test, find_filters) {
    
    std::vector<std::string> input_1 = {"./soccer_players", "--age", "-price", "--club"};
    const std::vector<std::string> result_flags_1 = {"--age", "--club"};
    EXPECT_EQ(find_flags(input_1), result_flags_1);


    std::vector<std::string> input_2 = {"./soccer_players"};
    std::vector<std::string> result_2;
    EXPECT_EQ(find_flags(input_2), result_2);
    
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


TEST(check_similarity_score, similarity_score) {

    Player a = {"John Doe", 23, "USA", 180, 90, "FC Barcalona", "$13,000,000", {12, 32, 543}};
    Player b = {"John Doe", 23, "USA", 180, 90, "FC Barcalona", "$13,000,000", {12, 32, 543}};
    EXPECT_EQ(similarity(a, b), 100);


    Player c = {"John Doe", 23, "USA", 180, 90, "FC Barcalona", "$13,000,000", {12, 32, 543, 323, 313}};
    Player d = {"John Doe", 23, "USA", 180, 90, "FC Barcalona", "$13,000,000", {12, 32, 543}};
    EXPECT_EQ(similarity(c, d), 100);


    Player e = {"John Doe", 23, "USA", 180, 90, "FC Barcalona", "$13,000,000", {12, 32, 543, 323, 313}};
    Player f = {"John Doe", 23, "USA", 180, 90, "FC Barcalona", "$13,000,000", {13, 32, 543}};
    EXPECT_EQ(similarity(e, f), 50);


    Player g = {"John Doe", 23, "USA", 180, 90, "FC Barcalona", "$13,000,000", {14, 32, 543}};
    Player h = {"John Doe", 23, "USA", 180, 90, "FC Barcalona", "$13,000,000", {12, 32, 543, 323, 313}};
    EXPECT_EQ(similarity(g, h), 33);

}