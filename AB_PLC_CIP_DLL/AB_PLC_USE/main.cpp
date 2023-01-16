#include "AbPlcUse.h"






AbPlcUse::AbPlcUse()
{
	fd = -1;
}

AbPlcUse::~AbPlcUse()
{
	disConnect();
}

bool AbPlcUse::connect(char* ip_addr, int port, int slot)
{
	bool ret = false;
	int mfd = -1;

	disConnect();

	mutexLocal local(&MyMutex);
	ret = ab_cip_connect(ip_addr, port, slot, &mfd);
	if (mfd != -1)
	{
		fd = mfd;
		ret = true;
	}
	return ret;
}

bool AbPlcUse::disConnect()
{
	mutexLocal local(&MyMutex);
	bool ret = true;
	if (fd != -1)
	{
		ret = ab_cip_disconnect(fd);
		fd = -1;
	}
	return ret;
}

cip_error_code_e AbPlcUse::read_short(const char* address, short* val)
{
	mutexLocal local(&MyMutex);
	return ab_cip_read_short(fd, address, val);
}

cip_error_code_e AbPlcUse::read_int32(const char* address, int32* val)
{
	mutexLocal local(&MyMutex);
	return ab_cip_read_int32(fd, address, val);
}

cip_error_code_e AbPlcUse::read_bool(const char* address, bool* val)
{
	mutexLocal local(&MyMutex);
	return ab_cip_read_bool(fd, address, val);
}

cip_error_code_e AbPlcUse::read_string(const char* address, int* length, char* val)
{
	mutexLocal local(&MyMutex);
	return ab_cip_read_string(fd, address, length, val);
}

cip_error_code_e AbPlcUse::write_bool(const char* address, bool val)
{
	mutexLocal local(&MyMutex);
	return ab_cip_write_bool(fd, address, val);
}

cip_error_code_e AbPlcUse::write_short(const char* address, short val)
{
	mutexLocal local(&MyMutex);
	return ab_cip_write_short(fd, address, val);
}

cip_error_code_e AbPlcUse::write_int32(const char* address, int32 val)
{
	mutexLocal local(&MyMutex);
	return ab_cip_write_int32(fd, address, val);
}

cip_error_code_e AbPlcUse::write_string(const char* address, int length, const char* val)
{
	mutexLocal local(&MyMutex);
	return ab_cip_write_string(fd, address,length, val);
}


mutexLocal::mutexLocal(std::mutex* mutex)
{
	if (mutex != nullptr)
	{
		mutex->lock();
		MyMutex = mutex;
	}
	else
	{
		MyMutex = nullptr;
	}
}

mutexLocal::~mutexLocal()
{
	if (MyMutex != nullptr)
	{
		MyMutex->unlock();
	}
}
