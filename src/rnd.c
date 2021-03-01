#include "engine.h"

/* Based on: http://stackoverflow.com/a/7776146 */
static
void
hexdump(char* desc, void* addr, size_t len, FILE* fp)
{
    unsigned int i;
    unsigned char buf[17];
    unsigned char* pc = (unsigned char*)addr;

    /* Output description if given. */
    if (desc != NULL) fprintf(fp, "%s:\n", desc);

    for (i = 0; i < (unsigned int)len; i++) {

        if ((i % 16) == 0) {
            if (i != 0) fprintf(fp, "  |%s|\n", buf);
            fprintf(fp, "%08x ", i);
        }
        else if ((i % 8) == 0) {
            fprintf(fp, " ");
        }
        fprintf(fp, " %02x", pc[i]);
        if ((pc[i] < 0x20) || (pc[i] > 0x7e)) {
            buf[i % 16] = '.';
        }
        else {
            buf[i % 16] = pc[i];
        }
        buf[(i % 16) + 1] = '\0';
    }
    if (i % 16 <= 8 && i % 16 != 0) fprintf(fp, " ");
    while ((i % 16) != 0) {
        fprintf(fp, "   ");
        i++;
    }
    fprintf(fp, "  |%s|\n", buf);
}

static
int
rand_bytes(unsigned char* buf, int num)
{
    if (!buf || !num) return 0;

    for (int i = 0; i < num; i++) {
        *(buf + i) = (unsigned char)rand();
    }

    hexdump("srndengine", buf, num, stdout);

    return 1;
}

static
int
rand_status(void)
{
    return 1;
}

static RAND_METHOD s_rand = {
    NULL,       // seed()
    rand_bytes, // bytes()
    NULL,       // cleanup()
    NULL,       // add()
    rand_bytes, // pseudorand()
    rand_status //status()
};

int
srnd_ssl_rand_setup(ENGINE* e)
{
    time_t t;
    srand((unsigned)time(&t));
    return ENGINE_set_RAND(e, &s_rand);
}
