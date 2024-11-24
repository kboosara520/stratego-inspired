#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <unordered_map>
#include <vector>

const int PLAYERCOUNT = 2;
const int BOARDSIZE = 8;
const int LINKCOUNT = 8;
const std::unordered_map<char, std::string> CHAR2NAME{
    {'L', "Link boost"},
    {'F', "Firewall"},
    {'D', "Download"},
    {'P', "Polarize"},
    {'S', "Scan"},
    {'W', "Super firewall"},
    {'T', "Trojan"},
    {'A', "And one"}
};
const std::vector<char> LINKNAMES{'a', 'A'};
const char DATA = 'D';
const char VIRUS = 'V';

#endif
