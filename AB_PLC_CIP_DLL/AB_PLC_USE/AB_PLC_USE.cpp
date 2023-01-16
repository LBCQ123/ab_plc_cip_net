// AB_PLC_USE.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "ab_cip.h"
#ifdef _WIN32
#include <WinSock2.h>
#endif
#include <stdlib.h>
#pragma warning(disable : 4996)

#pragma comment(lib,"AB_PLC_CIP.lib")

int main()
{
    //std::cout << "Hello World!\n";

	char plc_ip[] = "192.168.11.110";	int plc_port = 44818;


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
			ret = ab_cip_read_string(fd, address, &length, tab);
			printf("Read\t %s \tstring:%s, ret = %d\n", address, tab, ret);

			strcpy(tab, "hahahha");
			ret = ab_cip_write_string(fd, "Test5", strlen(tab), tab);
			printf("Write\t %s \tstring:%s, \tret: %d\n", address, tab, ret);

			length = 1;
			strcpy(tab, "");
			ret = ab_cip_read_string(fd, address, &length, tab);
			printf("Read\t %s \tstring:%s, ret = %d\n", address, tab, ret);


		}

		ab_cip_disconnect(fd);
		//system("pause");
	}
	else
	{
		printf("通讯失败");
	}

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
