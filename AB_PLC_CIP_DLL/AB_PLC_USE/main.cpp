// AB_PLC_USE.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "AbPlcUse.h"

int main()
{
    //std::cout << "Hello World!\n";

	char plc_ip[] = "192.168.11.110";	int plc_port = 44818;
	char plc_ip2[] = "192.168.11.110";	int plc_port2 = 44818;

	int slot = 0;
	printf("开始通讯\n");
	AbPlcUse user;
	bool ret = user.connect(plc_ip, plc_port, 0);

	AbPlcUse user2;
	bool ret2 = user2.connect(plc_ip2, plc_port2, 0);


	//测试
	char addr[30] = "E.5";
	short val = 3;
	ret = user.read_short(addr, &val);
	printf("Read\t %s \tshort:\t %d, \tret: %d\n", addr, val, ret);


	//测试2
	ret = user2.read_short(addr, &val);
	printf("Read2\t %s \tshort:\t %d, \tret: %d\n", addr, val, ret);



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
