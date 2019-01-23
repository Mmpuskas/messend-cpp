#include "messend.hpp"


using namespace messend;

int main(int argc, char** argv) {

    messend::startup();

    Acceptor acceptor(9001);

    PeerResult result = acceptor.accept();

    while (!result.success) {
        result = acceptor.accept();
    }

    Peer peer = result.peer;

    Message message((uint8_t*)"Hi there", 8);

    peer.sendMessage(message);

    //result.success = false;
    //while (!result.success) {
    //    result = acceptor.accept();
    //}

    messend::shutdown();

    return 0;
}
