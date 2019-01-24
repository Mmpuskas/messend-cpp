#include <stdint.h>
#include <iostream>
#include <thread>
#include <chrono>

#include "messend.hpp"

using namespace std;
using namespace messend;

int main(int argc, char **argv) {

    messend::startup();

    Acceptor acceptor("127.0.0.1", 9001);

    Peer* peer = acceptor.acceptWait();

    while (1) {
        Message* message = peer->receiveMessageWait();

        if (!message) {
            if (!peer->isConnected()) {
                cout << "Disconnected" << endl;
                break;
            }
        }
        else {

            for (int i = 0; i < message->size; i++) {
                cout << message->data[i];
            }
            cout << endl;

            peer->sendMessage(*message);
        }
    }

    delete peer;

    messend::shutdown();

    return 0;
}
