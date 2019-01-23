#include <stdio.h>
#include <stdint.h>
#include "messend.h"
#include "messend.hpp"

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace messend;

int main(int argc, char **argv) {

    messend::startup();

    Acceptor acceptor(9001);

    Peer* peer = 0;
    
    PeerResult result;
        
    while(!peer) {
        printf("loopy\n");

        result = acceptor.accept();
        if (result.success) {
            peer = result.peer;
        }

        std::this_thread::sleep_for (std::chrono::milliseconds(100));
    }

    Message message((uint8_t*)"Hi from server", 14);
    peer->sendMessage(message);

    messend::shutdown();

    return 0;
}
