#include <stdio.h>
#include <string.h>
#include <openssl/engine.h>

#define LOG_SEVERE(msg) fprintf(stderr, "%s, err = 0x%lx\n", msg, ERR_get_error())

#ifdef _WIN32
#define SSL_ENGINE_PATH ".\\srnd\\Debug\\srndengine.dll"
#else
#define SSL_ENGINE_PATH "/usr/lib/x86_64-linux-gnu/engines-1.1/srndengine.so"
#endif

#define SSL_ENGINE_ID "srndengine"

static
ENGINE*
load_engine(const char* so_path, const char* id)
{
    int rc = 0;

    ENGINE_load_dynamic();
    ENGINE* de = ENGINE_by_id("dynamic");
    if (de == NULL) {
        LOG_SEVERE("ENGINE_by_id failed to load dynamic engine");
        goto cleanup;
    }

    rc = ENGINE_ctrl_cmd_string(de, "SO_PATH", so_path, 0);
    if (!rc) {
        LOG_SEVERE("Failed to set SO_PATH");
        goto cleanup;
    }

    rc = ENGINE_ctrl_cmd_string(de, "LIST_ADD", "2", 0);
    if (!rc) {
        LOG_SEVERE("Failed to set LIST_ADD");
        goto cleanup;
    }

    rc = ENGINE_ctrl_cmd_string(de, "LOAD", NULL, 0);
    if (!rc) {
        LOG_SEVERE("Failed to LOAD the engine");
        goto cleanup;
    }

cleanup:
    if (de) ENGINE_free(de);

    return rc ? ENGINE_by_id(id) : NULL;
}

int main() {
    int rc = 0;

    ENGINE* e = load_engine(SSL_ENGINE_PATH, SSL_ENGINE_ID);
    if (e == NULL) {
        LOG_SEVERE("load_engine failed");
        goto cleanup;
    }

    rc = ENGINE_init(e);
    if (!rc) {
        LOG_SEVERE("ENGINE_init failed");
        goto cleanup;
    }

    printf("SSL Engine: %s\n", ENGINE_get_name(e));

    /*
    rc = RAND_set_rand_engine(e);
    if (!rc) {
        SSL_LOG_SEVERE("RAND_set_rand_engine failed");
        goto cleanup;
    }

    unsigned char b[32];
    rc = RAND_bytes(b, 32);
    if (!rc) {
        SSL_LOG_SEVERE("RAND_bytes failed");
        goto cleanup;
    }

    hexdump(NULL, b, 32, stdout);
    */

cleanup:
    if (e) ENGINE_free(e);
    ENGINE_cleanup();

    return rc ? EXIT_SUCCESS : EXIT_FAILURE;
}
