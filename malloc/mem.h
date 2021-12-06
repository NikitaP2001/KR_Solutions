typedef long Align;

union header {
        struct {
                union header *ptr;
                unsigned size;
        } s;
        Align x;
};

typedef union header Header;

void *_malloc(unsigned nbytes);
void free(void *ap);