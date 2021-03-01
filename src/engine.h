#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <openssl/engine.h>

#define LOG_SEVERE(msg) fprintf(stderr, "%s, err: 0x%lx\n", msg, ERR_get_error())

int srnd_ssl_rand_setup(ENGINE* e);
