#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <regex>

int main() {
    std::ifstream f("C:\\Users\\kenwe\\Desktop\\AoC2023\\day2.txt");
    std::string l;
    std::map<int, bool> gs1;
    std::map<std::string, int> c = {{"red", 12}, {"green", 13}, {"blue", 14}};
    std::vector<std::string> tokens;
    int id = 1;
    int sum1 = 0;
    int sum2 = 0;
    while (std::getline(f, l)) {

        /*Throw out the initial part of the String 'Game ID:' don't need it.*/
        std::string o;
        std::stringstream ss(l);
        std::getline(ss, o, ':');

        /*For the remaining interesting game data: collect tokens of digits and colors in the order in which they appear in the game.*/
        while (std::getline(ss, o, ';')) {
            std::regex e("[0-9]+|red|green|blue");
            for (std::sregex_iterator it(o.begin(), o.end(), e); it != std::sregex_iterator(); ++it) {
                tokens.push_back(it->str());
            }
        }
        /*Part 1*/
        /*Because we collected the game data in the order it appears, we know this sequence happens: digit - color - ... etc, we can take advantage of that by
        storing the digit. Then at the next token (a color) we will decide if a game is valid or not.*/
        int currentNum;
        for (auto e : tokens) {
            if (e.size() < 3) { // digits are at most length 2 so if it is a string of length 2 or less its a digit.
                currentNum = std::stoi(e);
            }
            else{
                if (c[e] < currentNum) { //chek game is not valid, mark it as false in the games map
                    gs1[id] = false;
                    goto exitForLoop; //DO NOT critique my use of goto statements, they are mostly safe to move only forward in a sequence and very convenient in this case.
                }
            }
        }
        gs1[id] = true; //game is valid, all the colors were either under or equal to the amount of cubes available.
        exitForLoop:

        /*Part 2*/
        /*Logic follows exactly the same as Part 1 except this time we build a map for each game that holds the minimum amount of cubes of each time needed to play a game.
        Which is just a fancy way of saying, what is largest amount of cubes, by color, that appeared in any round of a game?*/
        std::map<std::string, int> m;
        for (auto e : tokens) {
            if (e.size() < 3) {
                currentNum = std::stoi(e);
            }
            else{
                if (!m.contains(e)) { //if we havent encountered the color yet, add it.
                    m[e] = currentNum;
                }
                else {
                    if (m[e] < currentNum) { //otherwise check if the quantity of cubes is more than encountered before.
                        m[e] = currentNum;
                    }
                }
            }
        }
        int total = 1;
        for (auto e : m) { //collect the sum of the multiplications of min cubes for part 2
            total *= e.second;
        }
        sum2 += total;
        ++id;
        tokens.clear();
    }
    for (auto e : gs1) { //collect the sum of Game IDs for part 1
        if (e.second) {
            sum1 += e.first;
        }
    }
    std::cout << sum1 << std::endl;
    std::cout << sum2 << std::endl;
    return 0;
}
