#ifndef __H_AB_CIP_H__
#define __H_AB_CIP_H__

#include "typedef.h"

/////////////////////////////////////////////////////////////

__C_EXPORT byte get_plc_slot();
__C_EXPORT void set_plc_slot(byte slot);

/////////////////////////////////////////////////////////////

__C_EXPORT bool ab_cip_connect(char *ip_addr, int port, int slot, int *fd);
__C_EXPORT bool ab_cip_disconnect(int fd);

// read
__C_EXPORT cip_error_code_e ab_cip_read_short(int fd, const char *address, short *val);
__C_EXPORT cip_error_code_e ab_cip_read_ushort(int fd, const char *address, ushort *val);
__C_EXPORT cip_error_code_e ab_cip_read_int32(int fd, const char *address, int32 *val);
__C_EXPORT cip_error_code_e ab_cip_read_bool(int fd, const char *address, bool *val);
__C_EXPORT cip_error_code_e ab_cip_read_uint32(int fd, const char *address, uint32 *val);
__C_EXPORT cip_error_code_e ab_cip_read_int64(int fd, const char *address, int64 *val);
__C_EXPORT cip_error_code_e ab_cip_read_uint64(int fd, const char *address, uint64 *val);
__C_EXPORT cip_error_code_e ab_cip_read_float(int fd, const char *address, float *val);
__C_EXPORT cip_error_code_e ab_cip_read_double(int fd, const char *address, double *val);
//length表示数组的元素个数，如果只有一条字符串就写1
__C_EXPORT cip_error_code_e ab_cip_read_string(int fd, const char *address, int *length, char *val); // need free val

// write
__C_EXPORT cip_error_code_e ab_cip_write_bool(int fd, const char *address, bool val);
__C_EXPORT cip_error_code_e ab_cip_write_short(int fd, const char *address, short val);
__C_EXPORT cip_error_code_e ab_cip_write_ushort(int fd, const char *address, ushort val);
__C_EXPORT cip_error_code_e ab_cip_write_int32(int fd, const char *address, int32 val);
__C_EXPORT cip_error_code_e ab_cip_write_uint32(int fd, const char *address, uint32 val);
__C_EXPORT cip_error_code_e ab_cip_write_int64(int fd, const char *address, int64 val);
__C_EXPORT cip_error_code_e ab_cip_write_uint64(int fd, const char *address, uint64 val);
__C_EXPORT cip_error_code_e ab_cip_write_float(int fd, const char *address, float val);
__C_EXPORT cip_error_code_e ab_cip_write_double(int fd, const char *address, double val);
__C_EXPORT cip_error_code_e ab_cip_write_string(int fd, const char* address, int length, const char* val);
//请勿调用
__C_EXPORT cip_error_code_e ab_cip_write_string_t(int fd, const char *address, int length, const char *val);

#endif //__H_AB_CIP_H__