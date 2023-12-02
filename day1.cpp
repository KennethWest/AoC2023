#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <map>

int main() {
    std::ifstream f("C:\\Users\\kenwe\\Desktop\\AoC2023\\day1.txt");
    std::string l;
    std::map<std::string, int> v = {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};
    std::vector<std::string> tokens;
    int sum1 = 0;
    int sum2 = 0;
    while (std::getline(f, l)) {
        /*Part 1*/
        std::regex const e1("\\d");
        for (std::sregex_iterator it = std::sregex_iterator(l.begin(), l.end(), e1); it != std::sregex_iterator(); ++it) {
            tokens.push_back(it->str());
        }
        tokens.size() == 1 ? sum1 += (std::stoi(tokens[0]) * 10) + std::stoi(tokens[0]) : sum1 += (std::stoi(tokens[0]) * 10) + std::stoi(tokens.back());
        tokens.clear();
        
        /*Part 2*/
        std::regex const e2{"(?=(\\d|one|two|three|four|five|six|seven|eight|nine))"};
        for (std::sregex_iterator it = std::sregex_iterator(l.begin(), l.end(), e2); it != std::sregex_iterator(); ++it) {
            tokens.push_back(it->str(1));
        }
        if (tokens.size() == 1) {
            sum2 += (std::stoi(tokens[0]) * 10) + std::stoi(tokens[0]);
        }
        else {
            tokens[0].size() > 1 ? sum2 += v[tokens[0]] * 10 : sum2 += std::stoi(tokens[0]) * 10;
            tokens.back().size() > 1 ? sum2 += v[tokens.back()] : sum2 += std::stoi(tokens.back());
        }
        tokens.clear();
    }
    std::cout << sum1 << std::endl;
    std::cout << sum2 << std::endl;
    return 0;
}
