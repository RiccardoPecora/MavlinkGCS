

#ifndef COMM_DUMMY
#define COMM_DUMMY

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib, "Ws2_32.lib")

#include <iostream>
#include <sstream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include "Comm_Base.h"



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//MACROS
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define DEBUG
#define DEFAULT_BUFLEN 512


using namespace std;

namespace COMM {

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //CLASS
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    class Comm_Dummy : public Comm_Base {
    public:
        Comm_Dummy();
        int8_t init();
        int8_t begin(string _ip_addr_str, string _ip_port_str);
        int8_t connect();
        int8_t shutdown();
        int8_t close();
        int8_t send(uint8_t*& _ptr_buf, uint16_t& _buf_len);
        int8_t receive(uint8_t*& _ptr_buf, uint16_t& _buf_len);


    private:
        //Socket variables
        string getInput = "";
        SOCKADDR_IN addr;
        int addrLen = sizeof(addr);
        IN_ADDR ipvalue;
        SOCKET connection = NULL;
        const char* ip_address = "192.168.56.101";
        uint16_t ip_port = 5762;
        bool comm_recv_enable = false;
        bool task_kill = false;

    };

}//namespace COMM
#endif //COMM_DUMMY