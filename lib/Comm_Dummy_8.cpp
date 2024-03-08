#include "Comm_Dummy_8.h"

COMM::Comm_Dummy::Comm_Dummy() : Comm_Base() {

}

int8_t COMM::Comm_Dummy::init(){
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) {
		return 1;
	}
	return 0;
}

int8_t COMM::Comm_Dummy::begin(string _ip_addr_str, string _ip_port_str){
	struct sockaddr_in sa;
	int result = inet_pton(AF_INET, _ip_addr_str.c_str(), &(sa.sin_addr));
	if ( result && (_ip_port_str.length() == 4) ) {
		ip_address = _ip_addr_str.c_str();
		ip_port = static_cast<uint16_t>(stoi(_ip_port_str));

		//Socket initialization
		addr.sin_addr.s_addr = inet_addr(ip_address);
		addr.sin_port = htons(ip_port);
		addr.sin_family = AF_INET;
		return 0;
	}else {
		//Socket initialization
		addr.sin_addr.s_addr = inet_addr(ip_address);
		addr.sin_port = htons(ip_port);
		addr.sin_family = AF_INET;
		return 1;
	}
}

int8_t COMM::Comm_Dummy::connect() {
	connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (::connect(connection, (SOCKADDR*)&addr, addrLen) == 0) {
		comm_recv_enable = true;
		return 0;
	}
	else {
		ip_address = "192.168.56.101";
		return 1;
	}
}

int8_t COMM::Comm_Dummy::shutdown() {
	// shutdown the socket
	int iResult = ::shutdown(connection, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		WSACleanup();
	}
	return iResult;
}

int8_t COMM::Comm_Dummy::close() {
	// close the socket
	int iResult = closesocket(connection);
	if (iResult == SOCKET_ERROR) {
		WSACleanup();
	}
	return iResult;
}


int8_t COMM::Comm_Dummy::send(uint8_t*& _ptr_buf, uint16_t& _buf_len) {

	// Send an initial buffer
	int iResult;
	/*unique_lock<mutex> send_mtx(m, defer_lock);
	if (send_mtx.try_lock()) {*/
		iResult = ::send(connection, (const char*)_ptr_buf, (int)_buf_len, 0);
		if (iResult == SOCKET_ERROR) {
			closesocket(connection);
			WSACleanup();
			return 1;
		}
		return 0;
	//}
	
}


int8_t COMM::Comm_Dummy::receive(uint8_t*& _ptr_buf, uint16_t& _buf_len) {
		
	int8_t iResult = 0;
	iResult = recv(connection, (char*)_ptr_buf, (int)_buf_len, 0);

	if (iResult > 0) {
		//wprintf(L"Bytes received: %d\n", iResult);
		
		//printf("--------------------------------------------------");
		//for (uint8_t i = 0; i < iResult; i++) {
		//	printf("Bytes [%d]: %x \n", i, recvbuf[i]);
		//}
		//printf("--------------------------------------------------");			
	}
	else if (iResult == 0) {
		//wprintf(L"Connection closed\n");
	}
	else {
		//wprintf(L"recv failed with error: %d\n", WSAGetLastError());
	}

	return iResult;

}
//std::this_thread::sleep_for(std::chrono::milliseconds(10));

