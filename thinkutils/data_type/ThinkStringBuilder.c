//
// Created by 王晓丰 on 2018/10/14.
//

#include "ThinkStringBuilder.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

/*
 * sb_create returns a pointer to a new ThinkStringBuilder or NULL if memory is not
 * available.
 */
ThinkStringBuilder *think_stringbuilder_create()
{
    ThinkStringBuilder *sb = (ThinkStringBuilder*) calloc(sizeof(ThinkStringBuilder), 1);
    return sb;
}

/*
 * sb_empty returns non-zero if the given ThinkStringBuilder is empty.
 */
int think_stringbuilder_empty(ThinkStringBuilder *sb)
{
    return (sb->root == NULL);
}

/*
 * sb_append adds a copy of the given string to a ThinkStringBuilder.
 */
int think_stringbuilder_append(ThinkStringBuilder *sb, const char *str)
{
    int				length = 0;
    StringFragment	*frag = NULL;

    if (NULL == str || '\0' == *str)
        return sb->length;

    length = (int) strlen(str);
    frag = (StringFragment*) malloc(sizeof(StringFragment) + (sizeof(char) * length));
    if (NULL == frag)
        return SB_FAILURE;

    frag->next = NULL;
    frag->length = length;
    memcpy((void*) &frag->str, (const void*) str, sizeof(char) * (length + 1));

    sb->length += length;
    if (NULL == sb->root)
        sb->root = frag;
    else
        sb->trunk->next = frag;

    sb->trunk = frag;

    return sb->length;
}

/*
 * sb_appendf adds a copy of the given formatted string to a ThinkStringBuilder.
 */
int think_stringbuilder_appendf(ThinkStringBuilder *sb, const char *format, ...)
{
    int			rc = 0;
    char		buf[SB_MAX_FRAG_LENGTH];
    va_list		args;

    va_start (args, format);
    rc = vsnprintf(&buf[0], SB_MAX_FRAG_LENGTH, format, args);
    va_end(args);

    if (0 > rc)
        return SB_FAILURE;

    return think_stringbuilder_append(sb, buf);
}

/*
 * sb_concat returns a concatenation of strings that have been appended to the
 * ThinkStringBuilder. It is the callers responsibility to free the returned
 * reference.
 *
 * The ThinkStringBuilder is not modified by this function and can therefore continue
 * to be used.
 */
char* think_stringbuilder_strdup(ThinkStringBuilder *sb)
{
    char			*buf = NULL;
    char			*c = NULL;
    StringFragment	*frag = NULL;

    buf = (char *) malloc((sb->length + 1) * sizeof(char));
    if (NULL == buf)
        return NULL;

    c = buf;
    for (frag = sb->root; frag; frag = frag->next) {
        memcpy(c, &frag->str, sizeof(char) * frag->length);
        c += frag->length;
    }

    *c = '\0';

    return buf;
}

/*
 * sb_reset resets the given ThinkStringBuilder, freeing all previously appended
 * strings.
 */
void think_stringbuilder_reset(ThinkStringBuilder *sb)
{
    StringFragment *frag = NULL;
    StringFragment *next = NULL;

    frag = sb->root;
    while(frag) {
        next = frag->next;
        free(frag);
        frag = next;
    }

    sb->root = NULL;
    sb->trunk = NULL;
    sb->length = 0;
}

/*
 * sb_free frees the given ThinkStringBuilder and all of its appended strings.
 */
void think_stringbuilder_free(ThinkStringBuilder *sb)
{
    think_stringbuilder_reset(sb);
    free(sb);
}