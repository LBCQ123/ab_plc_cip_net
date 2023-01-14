#ifdef _WIN32
#include <WinSock2.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

#define GET_RESULT(ret)    \
	{                      \
		if (ret != 0)      \
			faild_count++; \
	}

#include "ab_cip.h"

int main(int argc, char** argv)
{
#ifdef _WIN32
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return -1;
	}
#endif

	char* plc_ip = "192.168.11.110";	int plc_port = 44818;
	if (argc > 1)
	{
		plc_ip = argv[1];
		plc_port = atoi(argv[2]);
	}

	int fd = -1;
	int slot = 0;
	printf("开始通讯\n");
	bool ret = ab_cip_connect(plc_ip, plc_port, 0, &fd);

	if (ret && fd > 0)
	{
		cip_error_code_e ret = CIP_ERROR_CODE_FAILED;

		const int TEST_COUNT = 5000;
		const int TEST_SLEEP_TIME = 1000;
		int faild_count = 0;
		char address[50] = { 0 };
		int i = 0;
		{//read&write bool test
			bool val = true;
			strcpy(address, "Test");
			ret = ab_cip_write_bool(fd, address, val);
			printf("Write\t %s \tbool:\t %d, \tret: %d\n", address, val, ret);

			val = false;
			ret = ab_cip_read_bool(fd, address, &val);
			printf("Read\t %s \tbool:\t %d, \tret: %d\n", address, val, ret);

			val = false;
			ret = ab_cip_write_bool(fd, address, val);
			printf("Write\t %s \tbool:\t %d, \tret: %d\n", address, val, ret);

			val = true;
			ret = ab_cip_read_bool(fd, address, &val);
			printf("Read\t %s \tbool:\t %d, \tret: %d\n", address, val, ret);
		}
		//开始断网
		//Sleep(8000);

		{//read&write short test
			short val = 3;
			strcpy(address, "Test6.E[1]");
			ret = ab_cip_write_short(fd, address, val);
			printf("Write\t %s \tshort:\t %d, \tret: %d\n", address, val, ret);

			val = 0;
			ret = ab_cip_read_short(fd, address, &val);
			printf("Read\t %s \tshort:\t %d, \tret: %d\n", address, val, ret);

			val = 55;
			ret = ab_cip_write_short(fd, address, val);
			printf("Write\t %s \tshort:\t %d, \tret: %d\n", address, val, ret);

			val = 0;
			ret = ab_cip_read_short(fd, address, &val);
			printf("Read\t %s \tshort:\t %d, \tret: %d\n", address, val, ret);

		}

		//恢复网络
		//Sleep(8000);
		ab_cip_connect(plc_ip, plc_port, 0, &fd);

		{//read&write int test
			int val = 3;
			strcpy(address, "Test3");
			ret = ab_cip_write_int32(fd, address, val);
			printf("Write\t %s \tint32:\t %d, \tret: %d\n", address, val, ret);

			val = 0;
			ret = ab_cip_read_int32(fd, address, &val);
			printf("Read\t %s \tint32:\t %d, \tret: %d\n", address, val, ret);

			val = 4567;
			ret = ab_cip_write_int32(fd, address, val);
			printf("Write\t %s \tint32:\t %d, \tret: %d\n", address, val, ret);

			val = 0;
			ret = ab_cip_read_int32(fd, address, &val);
			printf("Read\t %s \tint32:\t %d, \tret: %d\n", address, val, ret);
		}

		{//read&write string test
			char tab[100];
			strcpy(address, "Test5");
			int length = 1;

			strcpy(tab, "helloworld");
			ret = ab_cip_write_string(fd, "Test5", strlen(tab), tab);
			printf("Write\t %s \tstring:%s, \tret: %d\n", address, tab, ret);


			strcpy(tab, "");
			ret = ab_cip_read_string(fd, address, &length, &tab);
			printf("Read\t %s \tstring:%s, ret = %d\n", address, tab, ret);

			strcpy(tab, "hahahha");
			ret = ab_cip_write_string(fd, "Test5", strlen(tab), tab);
			printf("Write\t %s \tstring:%s, \tret: %d\n", address, tab, ret);

			length = 1;
			strcpy(tab, "");
			ret = ab_cip_read_string(fd, address, &length, &tab);
			printf("Read\t %s \tstring:%s, ret = %d\n", address, tab, ret);


		}

		ab_cip_disconnect(fd);
		//system("pause");
	}

#ifdef _WIN32
	WSACleanup();
#endif
}