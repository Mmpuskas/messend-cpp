#ifndef __MESSEND_HPP__
#define __MESSEND_HPP__

#include <iostream>
#include <thread>
#include <chrono>

#include "messend.h"

//extern bool messend_peer_is_connected(MessendPeer peer);

namespace msnd {

    class Message {
        public:
            Message() :
                data(nullptr)
                , size(0)
            {
            }

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
                messend_peer_free(this->peer);
                this->peer = 0;
            }

            bool isConnected() {
                return messend_peer_is_connected(this->peer);
            }

            void sendMessage(Message mess) {
                MessendMessage message;

                message.data = mess.data;
                message.size = mess.size;

                messend_peer_send_message(this->peer, message);
            }

            std::unique_ptr<Message> receiveMessage() {
                MessendMessage* message = messend_peer_receive_message(this->peer);
                if (message) {
                    Message* mess = new Message(message->data, message->size);
                    // NOTE: don't want to free message here because mess is
                    // taking ownership. Might be a safer way to do this
                    return std::unique_ptr<Message>(mess);
                }
                else {
                    return nullptr;
                }
            }

            std::unique_ptr<Message> receiveMessageWait() {
                MessendMessage* message = messend_peer_receive_message_wait(this->peer);

                Message* mess = NULL;

                if (message) {
                    mess = new Message(message->data, message->size);
                }
                // NOTE: don't want to free message here because mess is
                // taking ownership. Might be a safer way to do this
                return std::unique_ptr<Message>(mess);
            }

        private:
            MessendPeer peer;
    };


    class Acceptor {
        public:
            Acceptor(std::string host, uint16_t port) : port(port) {
                this->acceptor = messend_acceptor_create(host.c_str(), port);
            }

            ~Acceptor() {
                messend_acceptor_free(this->acceptor);
                this->acceptor = 0;
            }

            std::unique_ptr<Peer> accept() {

                MessendPeer mpeer = messend_acceptor_accept(this->acceptor);

                if (mpeer) {
                    Peer* peer = new Peer(mpeer);
                    return std::unique_ptr<Peer>(peer);
                }
                else {
                    return nullptr;
                }
            }

            std::unique_ptr<Peer> acceptWait() {

                MessendPeer mpeer = messend_acceptor_accept_wait(this->acceptor);

                Peer* peer = new Peer(mpeer);
                return std::unique_ptr<Peer>(peer);
            }

        private:
            uint16_t port;
            MessendAcceptor acceptor;
    };


    inline void startup() {
        messend_startup();
    }

    inline void shutdown() {
        messend_shutdown();
    }

    inline std::unique_ptr<Peer> initiate(std::string addr, uint16_t port) {
        MessendPeer mpeer = messend_initiate((char *)addr.c_str(), port);

        if (mpeer) {
            Peer* peer = new Peer(mpeer);
            return std::unique_ptr<Peer>(peer);
        }
        else {
            return std::unique_ptr<Peer>(nullptr);
        }
    }
}

#endif //__MESSEND_HPP__
