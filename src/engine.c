#include "engine.h"

#define ENGINE_ID   "srndengine"
#define ENGINE_NAME "Simple RND OpenSSL Engine"

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

    rc = srnd_ssl_rand_setup(e);
    if (!rc) {
        LOG_SEVERE("srnd_ssl_rand_setup failed");
        goto cleanup;
    }

cleanup:
    return rc;
}

IMPLEMENT_DYNAMIC_BIND_FN(bind)
IMPLEMENT_DYNAMIC_CHECK_FN()
