/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * Ported to Arduino
 * by ValkaTR <valkur@gmail.com>
 * 24.01.2015
 */

#ifndef __G_STRING_H__
#define __G_STRING_H__

#include "gcommon.h"

G_BEGIN_DECLS

typedef struct _GString GString;

struct _GString
{
	char *str;
	gssize len;
	gssize allocated_len;
};

GString *g_string_new( const gchar *init );
GString *g_string_new_len( const gchar *init, gssize len );
GString *g_string_sized_new( gssize dfl_size );

char *g_string_free( GString *string, bool free_segment );

bool g_string_equal( GString *v, GString *v2 );
unsigned int g_string_hash( GString *str );

GString *g_string_assign( GString *string, const gchar *rval );

GString *g_string_truncate( GString *string, gssize len );
GString *g_string_set_size( GString *string, gssize len );

GString *g_string_append( GString *string, const gchar *val );
GString *g_string_append_len( GString *string, const gchar *val, gssize len );
GString *g_string_append_c( GString *string, gchar c );
GString *g_string_append_unichar( GString *string, word wc );

GString *g_string_prepend( GString *string, const gchar *val );
GString *g_string_prepend_c( GString *string, gchar c );
GString *g_string_prepend_unichar( GString *string, word wc );
GString *g_string_prepend_len( GString *string, const gchar *val, gssize len );

GString *g_string_insert( GString *string, gssize pos, const gchar *val );
GString *g_string_insert_c( GString *string, gssize pos, gchar c );
GString *g_string_insert_unichar( GString *string, gssize pos, word wc );
GString *g_string_insert_len( GString *string, gssize pos, const gchar *val, gssize len );

GString *g_string_overwrite( GString *string, gssize pos, const gchar *val );
GString *g_string_overwrite_len( GString *string, gssize pos, const gchar *val, gssize len );

GString *g_string_erase( GString *string, gssize pos, gssize len );

GString *g_string_ascii_down( GString *string );
GString *g_string_ascii_up( GString *string );

void g_string_vprintf( GString *string, const gchar *format, va_list args );
void g_string_printf( GString *string, const gchar *format, ... );
void g_string_append_vprintf( GString *string, const gchar *format, va_list args );
void g_string_append_printf( GString *string, const gchar *format, ... );

// #####################################################################

word g_utf8_get_char_validated( const gchar *p, gssize max_len );
static inline word g_utf8_get_char_extended( const gchar *p, gssize max_len );

char g_ascii_tolower( gchar c );
char g_ascii_toupper( gchar c );

gint g_vasprintf( char **string, const gchar *format, va_list args );
gssize g_printf_string_upper_bound( const gchar *format, va_list args );

// #####################################################################

G_END_DECLS

#endif /* __G_STRING_H__ */
