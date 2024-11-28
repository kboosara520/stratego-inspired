#include "graphicDisp.h"

GraphicDisp::GraphicDisp(Board *board, std::vector<Player *> players): board{board}, players{players} {
    window = std::make_unique<Xwindow>(500, 500);
    board->attach(this);
}

GraphicDisp::~GraphicDisp() {
    board->detach(this);
}

void GraphicDisp::displayBoard(int turn, const std::vector<std::pair<int, int>> &changes) {
    int leftPadding = 30;
    int topPadding = 50;
    window->fillRectangle(leftPadding, 50, 150, 80, 0);
    const int increment = 15;
    auto &p1Links = players[0]->getLinks(); //std::map<char,std::unique_ptr<Link>> links;
    auto &p2Links = players[1]->getLinks();
    int offset = topPadding + increment;
    window->drawString(leftPadding, offset, "Player 1");
    offset += increment;
    window->drawString(leftPadding, offset, "Downloaded: " + std::to_string(players[0]->getData()) + "D, " + std::to_string(players[0]->getVirus()) + "V");
    offset += increment;
    window->drawString(leftPadding, offset, "Abilities: " + std::to_string(players[0]->getAbilityCount()));
    offset += increment;
    for (int i = 0; i < BOARDSIZE / 4; i++) {
        std::string str;
        for (int j = 0; j < BOARDSIZE / 2; j++) {
            char index = 'a' + (i * 4) + j;
            Link *link = p1Links.at(index).get();
            str.append(std::string(1, link->getName()) + " ");
            if (turn % 2 == 0) {
                str.append(std::string(1, link->getType()) + std::to_string(link->getStrength()) + " ");

            }
            else if (link->getIsVisble()) {
                str.append(std::string(1, link->getAppearsAs()) + std::to_string(link->getStrength()) + " "); 
            }
            else {
                str.append("?  ");
            }
        }
        window->drawString(leftPadding, offset, str);
        offset += increment;
    }
    window->drawString(leftPadding, offset, "====================");
    // draw board
    for (auto &change: changes) {
        char symbol = board->getState(change.first, change.second);
        int colour = 0;
        if (('a' <= symbol  && symbol <= 'h') || ('A' <= symbol && symbol <= 'H')) {
            Link *link = nullptr;
            if ('a' <= symbol  && symbol <= 'h') {
                link = p1Links.at(symbol).get();
            }
            else {
                link = p2Links.at(symbol).get();
            }
            colour = getColour(link, turn);
        }
        else if (symbol == 'S') colour = 4;
        else if (symbol == FIREWALLNAMES[0] || symbol == FIREWALLNAMES[1]) colour = 5;
        window->fillRectangle((change.first * 15) + leftPadding, (change.second * 15) + offset, 15, 15, colour);
    }
    for (int x = 0; x < BOARDSIZE; ++x) {
        for (int y = 0; y < BOARDSIZE; ++y) {
            char symbol = board->getState(x, y);
            if (symbol != '.' && symbol != 'S' && symbol != FIREWALLNAMES[0] && symbol != FIREWALLNAMES[1]) {
                int colour = 0;
                Link *link;
                if ('a' <= symbol  && symbol <= 'h') {
                    link = p1Links.at(symbol).get();
                }
                else {
                    link = p2Links.at(symbol).get();
                }
                colour = getColour(link, turn);
                window->fillRectangle((x * 15) + leftPadding, (y * 15) + offset, 15, 15, colour); 
            }
        }
    }
    offset += increment * 9;
    window->drawString(leftPadding, offset, "====================");
    window->fillRectangle(leftPadding, offset, 150, 80, 0);
    offset += increment;
    window->drawString(leftPadding, offset, "Player 2");
    offset += increment;
    window->drawString(leftPadding, offset, "Downloaded: " + std::to_string(players[1]->getData()) + "D, " + std::to_string(players[1]->getVirus()) + "V");
    offset += increment;
    window->drawString(leftPadding, offset, "Abilities: " + std::to_string(players[1]->getAbilityCount()));
    offset += increment;
    for (int i = 0; i < BOARDSIZE / 4; i++) {
        std::string str;
        for (int j = 0; j < BOARDSIZE / 2; j++) {
            char index = 'A' + (i * 4) + j;
            Link *link = p2Links.at(index).get();
            str.append(std::string(1, link->getName()) + " ");
            if (turn % 2 == 1) {
                str.append(std::string(1, link->getType()) + std::to_string(link->getStrength()) + " ");
            }
            else if (link->getIsVisble()) {
                str.append(std::string(1, link->getAppearsAs()) + std::to_string(link->getStrength()) + " "); 
            }
            else {
                str.append("?  ");
            }
        }
        window->drawString(leftPadding, offset, str);
        offset += increment;
    }
}

int GraphicDisp::getColour(Link *link, int turn) {
    int colour = 0;
    if (turn == link->getOwner()) {
        if (link->getType() == DATA) colour = 3;
        else colour = 2;
    }
    else if (link->getIsVisble()) {
        if (link->getAppearsAs() == DATA) colour = 3;
        else colour = 2;
    }
    else {
        colour = 1;
    } 
    return colour;
}
