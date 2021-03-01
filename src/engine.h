#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <openssl/engine.h>
//#include <openssl/rand.h>

//#if _WIN32
//#define SKB_LOG_SEVERE(format, ...) fprintf(stderr, format, __VA_ARGS__)
//#else
//#define DBG__INT(fmt, ...)  fprintf(stderr, fmt "%s", __VA_ARGS__)
//#define SKB_LOG_SEVERE(...) DBG__INT(__VA_ARGS__, "\n")
//#endif // _WIN32

#define LOG_SEVERE(msg) fprintf(stderr, "%s, err: 0x%lx\n", msg, ERR_get_error())

int srnd_ssl_rand_setup(ENGINE* e);
