#include <iostream>
#include "client.h"

int main() {
    try {
        Client client;
        std::thread clientThread{&Client::run, &client};
        if (clientThread.joinable()) clientThread.join();
    }
    catch (const ClientInitException &e) {
        std::cout << e.what() << std::endl;
    }
}
