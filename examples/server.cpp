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

    Acceptor acceptor("127.0.0.1", 9001);

    Peer* peer = acceptor.acceptWait();
    
    Message message = peer->receiveMessageWait();
    for (int i = 0; i < message.size; i++) {
        cout << message.data[i];
    }
    cout << endl;

    message = Message((uint8_t*)"Hi from server", 14);
    peer->sendMessage(message);

    delete peer;

    messend::shutdown();

    return 0;
}
