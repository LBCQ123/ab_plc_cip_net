## 程序整体介绍

- 项目名称：ab_plc_cip_net
- 开发语言：C语言
- 支持操作系统：windows/linux
- 测试设备：模拟AB-CIP

目前实现功能，实现罗克韦尔AB-PLC通讯类，采用CIP(EtherNet/IP)协议实现，需要在PLC侧先的以太网模块先进行配置。

#### 头文件

```c
#include "ab_cip.h" 	//协议提供方法接口
#include "typedef.h" 		//部分类型宏定义
```

## 西门子PLC地址说明
####  连接属性
- port 端口号，通常为44818
- plc_type plc 型号，适用1756 ControlLogix, 1756 GuardLogix, 1769 CompactLogix, 1769 Compact GuardLogix, 1789SoftLogix, 5069 CompactLogix, 5069 Compact GuardLogix, Studio 5000 Logix Emulate等型号
#### PLC地址分类
支持使用标签的形式进行读写操作


## 实现方法

#### 1.连接PLC设备

```c
byte get_plc_slot();
void set_plc_slot(byte slot);

bool ab_cip_connect(char* ip_addr, int port, int slot, int* fd);
bool ab_cip_disconnect(int fd);
```

#### 2.读取数据
```c
cip_error_code_e ab_cip_read_bool(int fd, const char* address, bool* val);
cip_error_code_e ab_cip_read_short(int fd, const char* address, short* val);
cip_error_code_e ab_cip_read_ushort(int fd, const char* address, ushort* val);
cip_error_code_e ab_cip_read_int32(int fd, const char* address, int32* val);
cip_error_code_e ab_cip_read_uint32(int fd, const char* address, uint32* val);
cip_error_code_e ab_cip_read_int64(int fd, const char* address, int64* val);
cip_error_code_e ab_cip_read_uint64(int fd, const char* address, uint64* val);
cip_error_code_e ab_cip_read_float(int fd, const char* address, float* val);
cip_error_code_e ab_cip_read_double(int fd, const char* address, double* val);
cip_error_code_e ab_cip_read_string(int fd, const char* address, int* length, char** val); //need free val
```

#### 3.写入数据

```c
cip_error_code_e ab_cip_write_bool(int fd, const char* address, bool val);
cip_error_code_e ab_cip_write_short(int fd, const char* address, short val);
cip_error_code_e ab_cip_write_ushort(int fd, const char* address, ushort val);
cip_error_code_e ab_cip_write_int32(int fd, const char* address, int32 val);
cip_error_code_e ab_cip_write_uint32(int fd, const char* address, uint32 val);
cip_error_code_e ab_cip_write_int64(int fd, const char* address, int64 val);
cip_error_code_e ab_cip_write_uint64(int fd, const char* address, uint64 val);
cip_error_code_e ab_cip_write_float(int fd, const char* address, float val);
cip_error_code_e ab_cip_write_double(int fd, const char* address, double val);
cip_error_code_e ab_cip_write_string(int fd, const char* address, int length, const char* val);
```

## 使用样例
完整样例参见代码中**main.c**文件，如下提供主要代码和使用方法：

*读取地址，格式为"**F**","**D**"

```c
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
```

