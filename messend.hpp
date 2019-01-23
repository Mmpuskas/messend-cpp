#include "messend.h"
#include <iostream>

using namespace std;

namespace messend {

    void startup() {
        messend_startup();
    }

    void shutdown() {
        messend_shutdown();
    }

    class Message {
        public:
            Message(uint8_t* data, uint64_t size) : data(data), size(size) {
            }

            uint8_t* data;
            uint64_t size;
    };

    class Peer {
        public:

            Peer(MessendPeer peer) : peer(peer) {
            }

            ~Peer() {
                if (this->peer) {
                    messend_peer_free(this->peer);
                }
            }

            void sendMessage(Message mess) {
                MessendMessage message;

                message.data = (uint8_t*)"Hi from client aaaaaaaaa";
                message.size = 1;

                //message.data = mess.data;
                //message.size = mess.size;
                cout << message.size << endl;
                messend_peer_send_message(this->peer, message);
            }

        private:
            MessendPeer peer;
    };

    class PeerResult {
        public:
            PeerResult() : success(false), peer(NULL) {
            }

            PeerResult(bool success, Peer peer) : success(success), peer(peer) {
            }

            bool success;
            Peer peer;
    };


    class Acceptor {
        public:
            Acceptor(uint16_t port) : port(port) {
                this->acceptor = messend_acceptor_create(port);
                cout << this->acceptor << endl;
            }

            ~Acceptor() {
                messend_acceptor_free(this->acceptor);
            }

            PeerResult accept() {

                MessendPeer peer = messend_acceptor_accept(this->acceptor);

                if (peer) {
                    return PeerResult(true, peer);
                }
                else {
                    return PeerResult(false, NULL);
                }
            }

        private:
            uint16_t port;
            MessendAcceptor acceptor;
    };
}
