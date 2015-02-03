/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997  Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/*
 * Modified by the GLib Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GLib Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GLib at ftp://ftp.gtk.org/pub/gtk/.
 */

#ifndef __G_TYPES_H__
#define __G_TYPES_H__

#include <Arduino.h>

/* Guard C code in headers, while including them from C++ */
#ifdef  __cplusplus
# define G_BEGIN_DECLS  extern "C" {
# define G_END_DECLS    }
#else
# define G_BEGIN_DECLS
# define G_END_DECLS
#endif

G_BEGIN_DECLS

#define g_malloc	malloc
#define g_free	free

// #####################################################################

#if    __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#define G_GNUC_WARN_UNUSED_RESULT       \
  __attribute__((warn_unused_result))
#else
#define G_GNUC_WARN_UNUSED_RESULT
#endif /* __GNUC__ */

// #####################################################################

#if defined(__GNUC__)  && __GNUC__ >= 4
#  define G_STRUCT_OFFSET(struct_type, member) \
      ((glong) offsetof (struct_type, member))
#else
#  define G_STRUCT_OFFSET(struct_type, member)  \
      ((glong) ((guint8*) &((struct_type*) 0)->member))
#endif

// #####################################################################

#undef  MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))

#undef  MIN
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))

#undef  ABS
#define ABS(a)     (((a) < 0) ? -(a) : (a))

#undef  CLAMP
#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

/* Functions like the ones in <ctype.h> that are not affected by locale. */
typedef enum {
	G_ASCII_ALNUM  = 1 << 0,
	G_ASCII_ALPHA  = 1 << 1,
	G_ASCII_CNTRL  = 1 << 2,
	G_ASCII_DIGIT  = 1 << 3,
	G_ASCII_GRAPH  = 1 << 4,
	G_ASCII_LOWER  = 1 << 5,
	G_ASCII_PRINT  = 1 << 6,
	G_ASCII_PUNCT  = 1 << 7,
	G_ASCII_SPACE  = 1 << 8,
	G_ASCII_UPPER  = 1 << 9,
	G_ASCII_XDIGIT = 1 << 10
} GAsciiType;

extern const unsigned int *g_ascii_table;

#define g_ascii_isalnum(c) ((g_ascii_table[(unsigned char) (c)] & G_ASCII_ALNUM) != 0)
#define g_ascii_islower(c) ((g_ascii_table[(unsigned char) (c)] & G_ASCII_LOWER) != 0)
#define g_ascii_isupper(c) ((g_ascii_table[(unsigned char) (c)] & G_ASCII_UPPER) != 0)
#define g_ascii_isxdigit(c) ((g_ascii_table[(unsigned char) (c)] & G_ASCII_XDIGIT) != 0)

#define g_return_val_if_fail(expr,val) { (void) 0; }
#define g_return_if_fail(expr) { (void) 0; }

/*
 * Check whether a Unicode (5.2) char is in a valid range.
 *
 * The first check comes from the Unicode guarantee to never encode
 * a point above 0x0010ffff, since UTF-16 couldn't represent it.
 *
 * The second check covers surrogate pairs (category Cs).
 *
 * The last two checks cover "Noncharacter": defined as:
 *   "A code point that is permanently reserved for
 *    internal use, and that should never be interchanged. In
 *    Unicode 3.1, these consist of the values U+nFFFE and U+nFFFF
 *    (where n is from 0 to 10_16) and the values U+FDD0..U+FDEF."
 *
 * @param Char the character
 */
#define UNICODE_VALID(Char)                   \
    ((Char) < 0x110000 &&                     \
     (((Char) & 0xFFFFF800) != 0xD800) &&     \
     ((Char) < 0xFDD0 || (Char) > 0xFDEF) &&  \
     ((Char) & 0xFFFE) != 0xFFFE)


// #####################################################################

/* Provide type definitions for commonly used types.
 *  These are useful because a "gint8" can be adjusted
 *  to be 1 byte (8 bits) on all platforms. Similarly and
 *  more importantly, "gint32" can be adjusted to be
 *  4 bytes (32 bits) on all platforms.
 */

typedef char   gchar;
typedef short  gshort;
typedef long   glong;
typedef int    gint;
typedef gint   gboolean;

typedef unsigned char   guchar;
typedef unsigned short  gushort;
typedef unsigned long   gulong;
typedef unsigned int    guint;

typedef float   gfloat;
typedef double  gdouble;

typedef void *gpointer;
typedef const void *gconstpointer;


typedef gint( *GCompareFunc )( gconstpointer  a,
                               gconstpointer  b );
typedef gint( *GCompareDataFunc )( gconstpointer  a,
                                   gconstpointer  b,
                                   gpointer       user_data );
typedef gboolean( *GEqualFunc )( gconstpointer  a,
                                 gconstpointer  b );
typedef void ( *GDestroyNotify )( gpointer       data );
typedef void ( *GFunc )( gpointer       data,
                         gpointer       user_data );
typedef guint( *GHashFunc )( gconstpointer  key );
typedef void ( *GHFunc )( gpointer       key,
                          gpointer       value,
                          gpointer       user_data );

/**
 * GFreeFunc:
 * @data: a data pointer
 *
 * Declares a type of function which takes an arbitrary
 * data pointer argument and has no return value. It is
 * not currently used in GLib or GTK+.
 */
typedef void ( *GFreeFunc )( gpointer       data );

/**
 * GTranslateFunc:
 * @str: the untranslated string
 * @data: user data specified when installing the function, e.g.
 *  in g_option_group_set_translate_func()
 *
 * The type of functions which are used to translate user-visible
 * strings, for <option>--help</option> output.
 *
 * Returns: a translation of the string for the current locale.
 *  The returned string is owned by GLib and must not be freed.
 */
typedef const gchar    *( *GTranslateFunc )( const gchar   *str,
        gpointer       data );


typedef signed char gint8;
typedef unsigned char guint8;
typedef signed short gint16;
typedef unsigned short guint16;
typedef signed int gint32;
typedef unsigned int guint32;
typedef signed int gint64;
typedef unsigned int guint64;

typedef signed int gssize;
typedef unsigned int gsize;

#define ALIGNOF_GUINT32 4
#define ALIGNOF_GUINT64 8
#define ALIGNOF_UNSIGNED_LONG 4

// #####################################################################

extern const char *g_utf8_skip;

// #####################################################################

gint g_atomic_int_get( volatile gint *atomic );
void g_atomic_int_set( volatile gint *atomic, gint value );

void g_atomic_int_inc( volatile gint *atomic );
gboolean g_atomic_int_dec_and_test( volatile gint *atomic );

static inline word g_utf8_get_char_extended( const char *p, ssize_t max_len );

// #####################################################################

void g_qsort_with_data( gconstpointer pbase, gint total_elems, gsize size, GCompareDataFunc compare_func, gpointer user_data );

// #####################################################################

G_END_DECLS

#endif /* __G_TYPES_H__ */
