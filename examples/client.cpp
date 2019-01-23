#include <stdio.h>
#include <stdint.h>
#include "messend.hpp"

#include <iostream>
#include <thread>
#include <chrono>


using namespace std;
using namespace messend;


int main(int argc, char **argv) {

    messend::startup();

    PeerResult result = messend::initiate("127.0.0.1", 9001);

    if (!result.success) {
        return 1;
    }

    Peer* peer = result.peer;

    const uint64_t SIZE = 128;
    uint8_t data[SIZE];
    for (int i = 0; i < SIZE; i += 4) {
        data[i] = 'A';
        data[i+1] = 'C';
        data[i+2] = 'G';
        data[i+3] = 'T';
    }

    Message message(data, SIZE);
    
    peer->sendMessage(message);

    message = peer->receiveMessage();

    for (int i = 0; i < message.size; i++) {
        cout << message.data[i];
    }
    cout << endl;

    delete peer;

    messend::shutdown();

    return 0;
}
