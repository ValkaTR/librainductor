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

typedef struct _GString GString;

struct _GString
{
	char *str;
	ssize_t len;
	ssize_t allocated_len;
};

GString* g_string_new (const char *init);
GString* g_string_new_len (const char *init, ssize_t len);
GString* g_string_sized_new (ssize_t dfl_size);

char* g_string_free (GString *string, bool free_segment);

bool g_string_equal (GString *v, GString *v2);
unsigned int g_string_hash (GString *str);

GString* g_string_assign (GString *string, const char *rval);

GString* g_string_truncate (GString *string, ssize_t len);
GString* g_string_set_size (GString *string, ssize_t len);

GString* g_string_append (GString *string, const char *val);
GString* g_string_append_len (GString *string, const char *val, ssize_t len);
GString* g_string_append_c (GString *string, char c);
GString* g_string_append_unichar (GString *string, word wc);

GString* g_string_prepend (GString *string, const char *val);
GString* g_string_prepend_c (GString *string, char c);
GString* g_string_prepend_unichar (GString *string, word wc);
GString* g_string_prepend_len (GString *string, const char *val, ssize_t len);

GString* g_string_insert (GString *string, ssize_t pos, const char *val);
GString* g_string_insert_c (GString *string, ssize_t pos, char c);
GString* g_string_insert_unichar (GString *string, ssize_t pos, word wc);
GString* g_string_insert_len (GString *string, ssize_t pos, const char *val, ssize_t len);

GString* g_string_overwrite (GString *string, ssize_t pos, const char *val);
GString* g_string_overwrite_len (GString *string, ssize_t pos, const char *val, ssize_t len);

GString* g_string_erase (GString *string, ssize_t pos, ssize_t len);

GString* g_string_ascii_down (GString *string);
GString* g_string_ascii_up (GString *string);

void g_string_vprintf (GString *string, const char *format, va_list args);
void g_string_printf (GString *string, const char *format, ...);
void g_string_append_vprintf (GString *string, const char *format, va_list args);
void g_string_append_printf (GString *string, const char *format, ...);

// #####################################################################

word g_utf8_get_char_validated ( const char *p, ssize_t max_len);
static inline word g_utf8_get_char_extended (const char *p, ssize_t max_len);

char g_ascii_tolower (char c);
char g_ascii_toupper (char c);

int g_vasprintf (char **string, const char *format, va_list args);
ssize_t g_printf_string_upper_bound (const char *format, va_list args);

// #####################################################################

#endif /* __G_STRING_H__ */
