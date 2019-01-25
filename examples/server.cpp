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

    cout << "Wait for connection" << endl;
    auto peer = acceptor.acceptWait();
    cout << "Connected" << endl;

    while (1) {
        auto message = peer->receiveMessageWait();
        //cout << "receiveMessage" << endl;
        //auto message = peer->receiveMessage();

        if (!message) {
            if (!peer->isConnected()) {
                cout << "Disconnected" << endl;
                break;
            }
        }
        else {
            cout << "respond" << endl;

            for (int i = 0; i < message->size; i++) {
                cout << message->data[i];
            }
            cout << endl;

            peer->sendMessage(*message);
        }
    }

    messend::shutdown();

    return 0;
}
