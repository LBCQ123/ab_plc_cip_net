#pragma once

#include <iostream>
#include "ab_cip.h"
#ifdef _WIN32
#include <WinSock2.h>
#endif
#include <stdlib.h>
#pragma warning(disable : 4996)
#include <mutex>

#pragma comment(lib,"AB_PLC_CIP.lib")

class AbPlcUse
{
public:
	AbPlcUse();
	~AbPlcUse();
	bool connect(char* ip_addr, int port, int slot);
	bool disConnect();
	//��ȡ
	cip_error_code_e read_bool(const char* address, bool* val);
	cip_error_code_e read_short(const char* address, short* val);
	cip_error_code_e read_int32(const char* address, int32* val);
	//length���ض�ȡ�ַ�������
	cip_error_code_e read_string(const char* address, int* length, char* val);
	//д��
	cip_error_code_e write_bool(const char* address, bool val);
	cip_error_code_e write_short(const char* address, short val);
	cip_error_code_e write_int32(const char* address, int32 val);
	cip_error_code_e write_string(const char* address, int length, const char* val);

private:
	int fd;
	std::mutex MyMutex;
};

//simple mutex
class mutexLocal {
public:
	mutexLocal(std::mutex* mutex);
	~mutexLocal();
private:
	std::mutex* MyMutex;
};

