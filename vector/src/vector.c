#define VECTOR_INIT_CAPACITY 4
#include <malloc.h>
/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../vector.h"
void vector_cnets_osblinnikov_github_com_onCreate(vector_cnets_osblinnikov_github_com *that);
void vector_cnets_osblinnikov_github_com_onDestroy(vector_cnets_osblinnikov_github_com *that);
void vector_cnets_osblinnikov_github_com_init(struct vector_cnets_osblinnikov_github_com *that){
  
  vector_cnets_osblinnikov_github_com_onCreate(that);
}

void vector_cnets_osblinnikov_github_com_deinit(struct vector_cnets_osblinnikov_github_com *that){
  vector_cnets_osblinnikov_github_com_onDestroy(that);
  
}
/*[[[end]]] (checksum: b5f934e29007e64da83f9afb624e5d37)*/

void vector_cnets_osblinnikov_github_com_resize(vector_cnets_osblinnikov_github_com *v, int capacity);

void vector_cnets_osblinnikov_github_com_onCreate(vector_cnets_osblinnikov_github_com *v){
    v->capacity = VECTOR_INIT_CAPACITY;
    v->total = 0;
    v->items = (unsigned*)malloc(sizeof(unsigned) * v->capacity);
    return;
}

void vector_cnets_osblinnikov_github_com_onDestroy(vector_cnets_osblinnikov_github_com *v){
    free(v->items);
    return;
}


int vector_cnets_osblinnikov_github_com_total(vector_cnets_osblinnikov_github_com *v)
{
    return v->total;
}

void vector_cnets_osblinnikov_github_com_resize(vector_cnets_osblinnikov_github_com *v, int capacity)
{
#ifdef _DEBUG
//    printf("vector_resize: %d to %d\n", v->capacity, capacity);
#endif

    unsigned *items = (unsigned*)realloc(v->items, sizeof(unsigned) * capacity);
    if (items) {
        v->items = items;
        v->capacity = capacity;
    }
}

void vector_cnets_osblinnikov_github_com_add(vector_cnets_osblinnikov_github_com *v, unsigned item)
{
    if (v->capacity == v->total)
        vector_cnets_osblinnikov_github_com_resize(v, v->capacity * 2);
    v->items[v->total++] = item;
}

void vector_cnets_osblinnikov_github_com_set(vector_cnets_osblinnikov_github_com *v, int index, unsigned item)
{
    if (index >= 0 && index < v->total)
        v->items[index] = item;
}

unsigned vector_cnets_osblinnikov_github_com_get(vector_cnets_osblinnikov_github_com *v, int index)
{
    if (index >= 0 && index < v->total)
        return v->items[index];
    return (unsigned)-1;
}

void vector_cnets_osblinnikov_github_com_delete(vector_cnets_osblinnikov_github_com *v, int index)
{
    if (index < 0 || index >= v->total)
        return;

    v->items[index] = 0;
    int i;
    for (i = 0; i < v->total - 1; i++) {
        v->items[i] = v->items[i + 1];
        v->items[i + 1] = 0;
    }

    v->total--;

    if (v->total > 0 && v->total == v->capacity / 4)
        vector_cnets_osblinnikov_github_com_resize(v, v->capacity / 2);
}
