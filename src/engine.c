#include <stdio.h>
#include <openssl/engine.h>

#define ENGINE_ID   "srndengine"
#define ENGINE_NAME "Simple RND OpenSSL Engine"

#define LOG_SEVERE(msg) fprintf(stderr, "%s, err = 0x%lx\n", msg, ERR_get_error())

static
int
bind(
    ENGINE* e,
    const char* id
)
{
    int rc = ENGINE_set_id(e, ENGINE_ID);
    if (!rc) {
        LOG_SEVERE("ENGINE_set_id failed");
        goto cleanup;
    }

    rc = ENGINE_set_name(e, ENGINE_NAME);
    if (!rc) {
        LOG_SEVERE("ENGINE_set_name failed");
        goto cleanup;
    }

    rc = 1;

cleanup:
    return rc;
}

IMPLEMENT_DYNAMIC_BIND_FN(bind)
IMPLEMENT_DYNAMIC_CHECK_FN()
