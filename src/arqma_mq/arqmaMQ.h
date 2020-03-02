#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <zmq.hpp>
#include "INotifier.h"

#include "cryptonote_basic/cryptonote_basic_impl.h"
//#include "cryptonote_basic/cryptonote_basic.h"
//#include "cryptonote_core/cryptonote_core.h"

#include "rpc/daemon_handler.h"

#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"


using namespace cryptonote;
using namespace rpc;


namespace arqmaMQ {

    class ArqmaNotifier: public INotifier {
        public:
            ArqmaNotifier(DaemonHandler& h);
            ~ArqmaNotifier();
            ArqmaNotifier(const ArqmaNotifier&) = delete;
            ArqmaNotifier& operator=(const ArqmaNotifier&) = delete;
            ArqmaNotifier(ArqmaNotifier&&) = delete;
            ArqmaNotifier& operator=(ArqmaNotifier&&) = delete;
            void notify(std::string &&data);
        private:
            std::thread proxy_thread;
			DaemonHandler& handler;
            zmq::context_t context;
            zmq::socket_t listener{context, ZMQ_ROUTER};
            zmq::socket_t producer{context, ZMQ_PAIR};
            zmq::socket_t subscriber{context, ZMQ_PAIR};
//            zmq::socket_t daemon{context, ZMQ_ROUTER};
            zmq::message_t create_message(std::string &&data);
            void proxy_loop();
    };
}

