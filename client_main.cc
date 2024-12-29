#include "client.h"

int main() {
    Client client;
    std::thread clientThread{&Client::run, &client};
    if (clientThread.joinable()) clientThread.join();
}
