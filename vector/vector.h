

#ifndef vector_cnets_osblinnikov_github_com_H
#define vector_cnets_osblinnikov_github_com_H

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/


#undef vector_cnets_osblinnikov_github_com_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(VECTOR_CNETS_OSBLINNIKOV_GITHUB_COM_STATIC)
  #ifdef vector_cnets_osblinnikov_github_com_EXPORT
    #define vector_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllexport)
  #else
    #define vector_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define vector_cnets_osblinnikov_github_com_EXPORT_API extern
#endif

struct vector_cnets_osblinnikov_github_com;

vector_cnets_osblinnikov_github_com_EXPORT_API
void vector_cnets_osblinnikov_github_com_init(struct vector_cnets_osblinnikov_github_com *that);

vector_cnets_osblinnikov_github_com_EXPORT_API
void vector_cnets_osblinnikov_github_com_deinit(struct vector_cnets_osblinnikov_github_com *that);

typedef struct vector_cnets_osblinnikov_github_com{
  
  
/*[[[end]]] (checksum: 1e061ff9863f38283fe621861258d75d)*/
  unsigned *items;
  int capacity;
  int total;
}vector_cnets_osblinnikov_github_com;

vector_cnets_osblinnikov_github_com_EXPORT_API
int vector_cnets_osblinnikov_github_com_total(vector_cnets_osblinnikov_github_com *v);
vector_cnets_osblinnikov_github_com_EXPORT_API
void vector_cnets_osblinnikov_github_com_resize(vector_cnets_osblinnikov_github_com *v, int capacity);
vector_cnets_osblinnikov_github_com_EXPORT_API
void vector_cnets_osblinnikov_github_com_add(vector_cnets_osblinnikov_github_com *v, unsigned item);
vector_cnets_osblinnikov_github_com_EXPORT_API
void vector_cnets_osblinnikov_github_com_set(vector_cnets_osblinnikov_github_com *v, int, unsigned item);
vector_cnets_osblinnikov_github_com_EXPORT_API
unsigned vector_cnets_osblinnikov_github_com_get(vector_cnets_osblinnikov_github_com *v, int index);
vector_cnets_osblinnikov_github_com_EXPORT_API
void vector_cnets_osblinnikov_github_com_delete(vector_cnets_osblinnikov_github_com *v, int index);

#endif /* vector_cnets_osblinnikov_github_com_H */
