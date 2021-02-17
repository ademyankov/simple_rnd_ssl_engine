#include <stdio.h>
#include <openssl/engine.h>

static const char* engine_id = "dummyengine";
static const char* engine_name = "Dummy OpenSSL Engine; Alex Demyankov. 2021, No rights reserved ;)";

#define ERROR(msg) fprintf(stderr, "%s, err = 0x%lx\n", msg, ERR_get_error())

static
int
bind(
    ENGINE* e,
    const char* id
)
{
    int rc = ENGINE_set_id(e, engine_id);
    if (!rc) {
        ERROR("ENGINE_set_id failed");
        goto error;
    }

    rc = ENGINE_set_name(e, engine_name);
    if (!rc) {
        ERROR("ENGINE_set_name failed");
        goto error;
    }

    rc = 1;

error:
    return rc;
}

IMPLEMENT_DYNAMIC_BIND_FN(bind)
IMPLEMENT_DYNAMIC_CHECK_FN()
