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

    auto peer = messend::initiate("127.0.0.1", 9001);

    if (!peer) {
        return 1;
    }

    const uint64_t SIZE = 128;
    uint8_t data[SIZE];
    for (int i = 0; i < SIZE; i += 4) {
        data[i] = 'A';
        data[i+1] = 'C';
        data[i+2] = 'G';
        data[i+3] = 'T';
    }

    Message message(data, SIZE);

    while (1) {
    
        peer->sendMessage(message);

        auto recvMessage = peer->receiveMessageWait();

        if (!recvMessage) {
            if (!peer->isConnected()) {
                cout << "Disconnected" << endl;
                break;
            }
        }
        else {
            for (int i = 0; i < recvMessage->size; i++) {
                cout << recvMessage->data[i];
            }
            cout << endl;
        }
    }

    messend::shutdown();

    return 0;
}
