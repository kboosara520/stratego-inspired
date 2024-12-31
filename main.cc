#include <iostream>
#include <string>
#include <vector>
#include "constants.h"
#include "gamecontroller.h"
#include "serverinitexception.h"

// for 4 players, turn abilities and links into vectors

int main(int argc, char* argv[]) {
    std::vector<std::string> playerAbilities(PLAYERCOUNT, defaultAbilities);
    std::vector<std::string> linkFiles(PLAYERCOUNT, "");

    for (int i = 0; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg[0] != '-') continue;
        else if (arg == "-ability1") playerAbilities[0] = argv[++i];
        else if (arg == "-ability2") playerAbilities[1] = argv[++i];
        else if (arg == "-link1") linkFiles[0] = argv[++i];
        else if (arg == "-link2") linkFiles[1] = argv[++i];
        // add extra features
    }
    std::stringstream from_server;
    try {
        GameController gc{playerAbilities, linkFiles, &from_server};
        gc.runGame();
    }
    catch (const ServerInitException &e) {
        std::cout << e.what() << std::endl;
    }
}
