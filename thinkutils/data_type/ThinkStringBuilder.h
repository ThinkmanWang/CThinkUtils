
#ifndef CTHINKUTILS_THINKSTRINGBUILDER_H
#define CTHINKUTILS_THINKSTRINGBUILDER_H

//#include <lzma.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SB_FAILURE				-1
#define SB_MAX_FRAG_LENGTH		4096

typedef struct _StringFragment {
    struct _StringFragment	*next;
    int					length;
    char					*str;
} StringFragment;

typedef struct _ThinkStringBuilder {
    struct _StringFragment	*root;
    struct _StringFragment	*trunk;
    int					length;
} ThinkStringBuilder;

ThinkStringBuilder	*think_stringbuilder_create();
int				think_stringbuilder_empty(ThinkStringBuilder *sb);
int				think_stringbuilder_append(ThinkStringBuilder *sb, const char *str);
int				think_stringbuilder_appendf(ThinkStringBuilder *sb, const char *format, ...);
char*			think_stringbuilder_strdup(ThinkStringBuilder *sb);
void 			think_stringbuilder_reset(ThinkStringBuilder *sb);
void			think_stringbuilder_free(ThinkStringBuilder *sb);


#ifdef __cplusplus
}
#endif

#endif //CTHINKUTILS_THINKThinkStringBuilder_H
