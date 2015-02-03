/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * Ported to Arduino
 * by ValkaTR <valkur@gmail.com>
 * 24.01.2015
 */

#ifndef __G_STRING_H__
#define __G_STRING_H__

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

extern const unsigned int * g_ascii_table;

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
