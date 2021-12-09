#include <heapapi.h>
#include "mem.h"

static Header base;
static Header *freep = NULL;

static Header *morecore(unsigned);

void *_malloc(unsigned nbytes)
{
        Header *p, *prevp;        
        unsigned nunits;
        
        nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;
        if ((prevp = freep) == NULL) {
                base.s.ptr = freep = prevp = &base;
                base.s.size = 0;
        }
        
        for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
                if (p->s.size >= nunits) {
                        if (p->s.size == nunits)
                                prevp->s.ptr = p->s.ptr;
                        else {
                                p->s.size -= nunits;
                                p += p->s.size;
                                p->s.size = nunits;
                        }
                        freep = prevp;
                        return (void *)(p+1);
                }
                if (p == freep)
                        if ((p = morecore(nunits)) == NULL)
                                return NULL;
        }
        
}

void *_calloc(unsigned nmemb, size_t size)
{
        malloc(nmemb * size);
        memset()
}

#define NALLOC 1024

static Header *morecore(unsigned nu)
{
        char *cp;
        HANDLE hHeap = GetProcessHeap();
        Header *up;
        
        if (nu < NALLOC)
                nu = NALLOC;
        cp = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, nu * sizeof(Header));
        if (cp == NULL)
                return NULL;
        up = (Header *)  cp;
        up->s.size = nu;
        free((void *)(up+1));
        
        return freep;
}

void free(void *ap)
{
        Header *bp, *p;
        
        bp = (Header *)ap - 1;
        for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
                if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
                        break;
                
        if (bp + bp->s.size == p->s.ptr) {
                bp->s.size += p->s.ptr->s.size;
                bp->s.ptr = p->s.ptr->s.ptr;
        } else 
                bp->s.ptr = p->s.ptr;
        if (p + p->s.size == bp) {
                p->s.size += bp->s.size;
                p->s.ptr = bp->s.ptr;
        } else
                p->s.ptr = bp;
        freep = p;
}        