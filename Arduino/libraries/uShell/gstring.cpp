/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997  Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * Ported to Arduino
 * by ValkaTR <valkur@gmail.com>
 * 24.01.2015
 */

/*
 * MT safe
 */

#include <Arduino.h>

#include "gstring.h"

// #####################################################################

/**
 * SECTION:strings
 * @title: Strings
 * @short_description: text buffers which grow automatically
 *     as text is added
 *
 * A #GString is an object that handles the memory management
 * of a C string for you. You can think of it as similar to a
 * Java StringBuffer. In addition to the string itself, GString
 * stores the length of the string, so can be used for binary
 * data with embedded nul bytes. To access the C string managed
 * by the GString @string, simply use @string->str.
 */

/**
 * GString:
 * @str: points to the character data. It may move as text is added.
 *   The @str field is null-terminated and so
 *   can be used as an ordinary C string.
 * @len: contains the length of the string, not including the
 *   terminating nul byte.
 * @allocated_len: the number of bytes that can be stored in the
 *   string before it needs to be reallocated. May be larger than @len.
 *
 * The GString struct contains the public fields of a GString.
 */


// For some unknown reason this doesn't work
// nearest_power would return -1
//#define MY_MAXSIZE      ((gssize)-1)

#define MY_MAXSIZE      (65535 - 1)

static inline gssize nearest_power( gssize base, gssize num )
{
	if( num > MY_MAXSIZE / 2 )
	{
		return MY_MAXSIZE;
	}
	else
	{
		gssize n = base;

		while( n < num )
			n <<= 1;

		return n;
	}
}

static void g_string_maybe_expand( GString *string, gssize len )
{
//Serial.println( String("g_string_maybe_expand: len = ") + len ); delay( 250 );
//Serial.println( String("g_string_maybe_expand: string->allocated_len = ") + string->allocated_len ); delay( 250 );
//Serial.println( String("g_string_maybe_expand: string->len = ") + string->len ); delay( 250 );
	if( string->len + len >= string->allocated_len )
	{
		string->allocated_len = nearest_power( 1, string->len + len + 1 );
//Serial.println( String("g_string_maybe_expand: new string->allocated_len = ") + string->allocated_len ); delay( 250 );
		string->str = ( gchar * ) realloc( string->str, string->allocated_len );

		//char *temp = (gchar *) malloc (string->allocated_len);
		//strncpy( temp, string->str, string->len );
		//free( string->str );
		//string->str = temp;
	}
}

/**
 * g_string_sized_new:
 * @dfl_size: the default size of the space allocated to
 *     hold the string
 *
 * Creates a new #GString, with enough space for @dfl_size
 * bytes. This is useful if you are going to add a lot of
 * text to the string and don't want it to be reallocated
 * too often.
 *
 * Returns: the new #GString
 */
GString *g_string_sized_new( gssize dfl_size )
{
	GString *string = ( GString * ) malloc( sizeof( GString ) );

	string->allocated_len = 0;
	string->len   = 0;
	string->str   = NULL;

	g_string_maybe_expand( string, MAX( dfl_size, 2 ) );
	string->str[0] = 0;

	return string;
}

/**
 * g_string_new:
 * @init: the initial text to copy into the string
 *
 * Creates a new #GString, initialized with the given string.
 *
 * Returns: the new #GString
 */
GString *g_string_new( const gchar *init )
{
	GString *string;

	if( init == NULL || *init == '\0' )
		string = g_string_sized_new( 2 );
	else
	{
		gint len;

		len = strlen( init );
		string = g_string_sized_new( len + 2 );

		g_string_append_len( string, init, len );
	}

	return string;
}

/**
 * g_string_new_len:
 * @init: initial contents of the string
 * @len: length of @init to use
 *
 * Creates a new #GString with @len bytes of the @init buffer.
 * Because a length is provided, @init need not be nul-terminated,
 * and can contain embedded nul bytes.
 *
 * Since this function does not stop at nul bytes, it is the caller's
 * responsibility to ensure that @init has at least @len addressable
 * bytes.
 *
 * Returns: a new #GString
 */
GString *g_string_new_len( const gchar *init, gssize len )
{
	GString *string;

	if( len < 0 )
		return g_string_new( init );
	else
	{
		string = g_string_sized_new( len );

		if( init )
			g_string_append_len( string, init, len );

		return string;
	}
}

/**
 * g_strinfree:
 * @string: a #GString
 * @free_segment: if %true, the actual character data is freed as well
 *
 * Frees the memory allocated for the #GString.
 * If @free_segment is %true it also frees the character data.  If
 * it's %false, the caller gains ownership of the buffer and must
 * free it after use with free().
 *
 * Returns: the character data of @string
 *          (i.e. %NULL if @free_segment is %true)
 */
char *g_string_free( GString  *string, bool  free_segment )
{
	gchar *segment;

	g_return_val_if_fail( string != NULL, NULL );

	if( free_segment )
	{
		free( string->str );
		segment = NULL;
	}
	else
		segment = string->str;

	free( string );

	return segment;
}

/**
 * g_string_equal:
 * @v: a #GString
 * @v2: another #GString
 *
 * Compares two strings for equality, returning %true if they are equal.
 * For use with #GHashTable.
 *
 * Returns: %true if they strings are the same length and contain the
 *     same bytes
 */
bool g_string_equal( const GString *v, const GString *v2 )
{
	gchar *p, *q;
	GString *string1 = ( GString * ) v;
	GString *string2 = ( GString * ) v2;
	gssize i = string1->len;

	if( i != string2->len )
		return false;

	p = string1->str;
	q = string2->str;
	while( i )
	{
		if( *p != *q )
			return false;
		p++;
		q++;
		i--;
	}
	return true;
}

/**
 * g_string_hash:
 * @str: a string to hash
 *
 * Creates a hash code for @str; for use with #GHashTable.
 *
 * Returns: hash code for @str
 */
guint g_string_hash( const GString *str )
{
	gchar *p = str->str;
	gssize n = str->len;
	guint h = 0;

	/* 31 bit hash function */
	while( n-- )
	{
		h = ( h << 5 ) - h + *p;
		p++;
	}

	return h;
}

/**
 * g_string_assign:
 * @string: the destination #GString. Its current contents
 *          are destroyed.
 * @rval: the string to copy into @string
 *
 * Copies the bytes from a string into a #GString,
 * destroying any previous contents. It is rather like
 * the standard strcpy() function, except that you do not
 * have to worry about having enough space to copy the string.
 *
 * Returns: @string
 */
GString *g_string_assign( GString *string, const gchar *rval )
{
	g_return_val_if_fail( string != NULL, NULL );
	g_return_val_if_fail( rval != NULL, string );

	/* Make sure assigning to itself doesn't corrupt the string. */
	if( string->str != rval )
	{
		/* Assigning from substring should be ok, since
		 * g_string_truncate() does not reallocate.
		 */
		g_string_truncate( string, 0 );
		g_string_append( string, rval );
	}

	return string;
}

/**
 * g_string_truncate:
 * @string: a #GString
 * @len: the new size of @string
 *
 * Cuts off the end of the GString, leaving the first @len bytes.
 *
 * Returns: @string
 */
GString *g_string_truncate( GString *string, gssize len )
{
	g_return_val_if_fail( string != NULL, NULL );

	string->len = MIN( len, string->len );
	string->str[string->len] = 0;

	return string;
}

/**
 * g_string_set_size:
 * @string: a #GString
 * @len: the new length
 *
 * Sets the length of a #GString. If the length is less than
 * the current length, the string will be truncated. If the
 * length is greater than the current length, the contents
 * of the newly added area are undefined. (However, as
 * always, string->str[string->len] will be a nul byte.)
 *
 * Return value: @string
 */
GString *g_string_set_size( GString *string, gssize len )
{
	g_return_val_if_fail( string != NULL, NULL );

	if( len >= string->allocated_len )
		g_string_maybe_expand( string, len - string->len );

	string->len = len;
	string->str[len] = 0;

	return string;
}

/**
 * g_string_insert_len:
 * @string: a #GString
 * @pos: position in @string where insertion should
 *       happen, or -1 for at the end
 * @val: bytes to insert
 * @len: number of bytes of @val to insert
 *
 * Inserts @len bytes of @val into @string at @pos.
 * Because @len is provided, @val may contain embedded
 * nuls and need not be nul-terminated. If @pos is -1,
 * bytes are inserted at the end of the string.
 *
 * Since this function does not stop at nul bytes, it is
 * the caller's responsibility to ensure that @val has at
 * least @len addressable bytes.
 *
 * Returns: @string
 */
GString *g_string_insert_len( GString *string, gssize pos, const gchar *val, gssize len )
{
	g_return_val_if_fail( string != NULL, NULL );
	g_return_val_if_fail( len == 0 || val != NULL, string );

	if( len == 0 )
		return string;

	if( len < 0 )
		len = strlen( val );
//Serial.println( String("len = ") + (int) len ); delay( 250 );
	if( pos < 0 )
		pos = string->len;
	else
		g_return_val_if_fail( pos <= string->len, string );
//Serial.println( String("pos = ") + (int) pos ); delay( 250 );
	/* Check whether val represents a substring of string.
	 * This test probably violates chapter and verse of the C standards,
	 * since ">=" and "<=" are only valid when val really is a substring.
	 * In practice, it will work on modern archs.
	 */
	if( val >= string->str && val <= string->str + string->len )
	{
//Serial.println( String("val represents a substring of string") ); delay( 250 );
		gssize offset = val - string->str;
		gssize precount = 0;
//Serial.println( String("offset = ") + (int) offset ); delay( 250 );
		g_string_maybe_expand( string, len );
		val = string->str + offset;
		/* At this point, val is valid again.  */
//Serial.println( String("new val = ") + val ); delay( 250 );
		/* Open up space where we are going to insert.  */
		if( pos < string->len )
			memmove( string->str + pos + len, string->str + pos, string->len - pos );

		/* Move the source part before the gap, if any.  */
		if( offset < pos )
		{
			precount = MIN( len, pos - offset );
//Serial.println( String("precount = ") + precount ); delay( 250 );
			memcpy( string->str + pos, val, precount );
		}

		/* Move the source part after the gap, if any.  */
		if( len > precount )
			memcpy( string->str + pos + precount,
			        val + /* Already moved: */ precount + /* Space opened up: */ len,
			        len - precount );
	}
	else
	{
//Serial.println( String("val does not represent a substring of string") ); delay( 250 );
		g_string_maybe_expand( string, len );

		/* If we aren't appending at the end, move a hunk
		 * of the old string to the end, opening up space
		 */
		if( pos < string->len )
			memmove( string->str + pos + len, string->str + pos, string->len - pos );

		/* insert the new string */
		if( len == 1 )
			string->str[pos] = *val;
		else
			memcpy( string->str + pos, val, len );
	}

	string->len += len;
//Serial.println( String("string->len = ") + string->len ); delay( 250 );

	string->str[string->len] = 0;

	return string;
}

#define SUB_DELIM_CHARS  "!$&'()*+,;="

static bool is_valid( gchar c, gchar *reserved_chars_allowed )
{
	if( g_ascii_isalnum( c ) ||
	        c == '-' ||
	        c == '.' ||
	        c == '_' ||
	        c == '~' )
		return true;

	if( reserved_chars_allowed &&
	        strchr( reserved_chars_allowed, c ) != NULL )
		return true;

	return false;
}

static bool word_ok( word c )
{
	return
	    ( c != ( word ) - 2 ) &&
	    ( c != ( word ) - 1 );
}

/**
 * g_string_append_uri_escaped:
 * @string: a #GString
 * @unescaped: a string
 * @reserved_chars_allowed: a string of reserved characters allowed
 *     to be used, or %NULL
 * @allow_utf8: set %true if the escaped string may include UTF8 characters
 *
 * Appends @unescaped to @string, escaped any characters that
 * are reserved in URIs using URI-style escape sequences.
 *
 * Returns: @string
 *
 * Since: 2.16
 */
GString *g_string_append_uri_escaped( GString *string, const gchar *unescaped, const gchar *reserved_chars_allowed, bool     allow_utf8 )
{
	guchar c;
	gchar *end;
	static gchar hex[32] = "0123456789ABCDEF";

	g_return_val_if_fail( string != NULL, NULL );
	g_return_val_if_fail( unescaped != NULL, NULL );

	end = ( gchar * ) unescaped + strlen( unescaped );

	while( ( c = *unescaped ) != 0 )
	{
		if( c >= 0x80 && allow_utf8 &&
		        word_ok( g_utf8_get_char_validated( unescaped, end - unescaped ) ) )
		{
			gint len = g_utf8_skip [c];
			g_string_append_len( string, unescaped, len );
			unescaped += len;
		}
		else if( is_valid( c, ( gchar * ) reserved_chars_allowed ) )
		{
			g_string_append_c( string, c );
			unescaped++;
		}
		else
		{
			g_string_append_c( string, '%' );
			g_string_append_c( string, hex[( ( unsigned char )c ) >> 4] );
			g_string_append_c( string, hex[( ( unsigned char )c ) & 0xf] );
			unescaped++;
		}
	}

	return string;
}

/**
 * g_string_append:
 * @string: a #GString
 * @val: the string to append onto the end of @string
 *
 * Adds a string onto the end of a #GString, expanding
 * it if necessary.
 *
 * Returns: @string
 */
GString *g_string_append( GString *string, const gchar *val )
{
	g_return_val_if_fail( string != NULL, NULL );
	g_return_val_if_fail( val != NULL, string );
//Serial.print( String("val = ") );
//Serial.println( val );
//Serial.print( String(";\r\n") );
	return g_string_insert_len( string, -1, val, -1 );
}

/**
 * g_string_append_len:
 * @string: a #GString
 * @val: bytes to append
 * @len: number of bytes of @val to use
 *
 * Appends @len bytes of @val to @string. Because @len is
 * provided, @val may contain embedded nuls and need not
 * be nul-terminated.
 *
 * Since this function does not stop at nul bytes, it is
 * the caller's responsibility to ensure that @val has at
 * least @len addressable bytes.
 *
 * Returns: @string
 */
GString *g_string_append_len( GString *string, const gchar *val, gssize len )
{
	g_return_val_if_fail( string != NULL, NULL );
	g_return_val_if_fail( len == 0 || val != NULL, string );

	return g_string_insert_len( string, -1, val, len );
}

/**
 * g_string_append_c:
 * @string: a #GString
 * @c: the byte to append onto the end of @string
 *
 * Adds a byte onto the end of a #GString, expanding
 * it if necessary.
 *
 * Returns: @string
 */
#undef g_string_append_c
GString *g_string_append_c( GString *string, gchar c )
{
	g_return_val_if_fail( string != NULL, NULL );

	return g_string_insert_c( string, -1, c );
}

/**
 * g_string_append_unichar:
 * @string: a #GString
 * @wc: a Unicode character
 *
 * Converts a Unicode character into UTF-8, and appends it
 * to the string.
 *
 * Return value: @string
 */
GString *g_string_append_unichar( GString *string, word wc )
{
	g_return_val_if_fail( string != NULL, NULL );

	return g_string_insert_unichar( string, -1, wc );
}

/**
 * g_string_prepend:
 * @string: a #GString
 * @val: the string to prepend on the start of @string
 *
 * Adds a string on to the start of a #GString,
 * expanding it if necessary.
 *
 * Returns: @string
 */
GString *g_string_prepend( GString *string, const gchar *val )
{
	g_return_val_if_fail( string != NULL, NULL );
	g_return_val_if_fail( val != NULL, string );

	return g_string_insert_len( string, 0, val, -1 );
}

/**
 * g_string_prepend_len:
 * @string: a #GString
 * @val: bytes to prepend
 * @len: number of bytes in @val to prepend
 *
 * Prepends @len bytes of @val to @string.
 * Because @len is provided, @val may contain
 * embedded nuls and need not be nul-terminated.
 *
 * Since this function does not stop at nul bytes,
 * it is the caller's responsibility to ensure that
 * @val has at least @len addressable bytes.
 *
 * Returns: @string
 */
GString *g_string_prepend_len( GString *string, const gchar *val, gssize len )
{
	g_return_val_if_fail( string != NULL, NULL );
	g_return_val_if_fail( val != NULL, string );

	return g_string_insert_len( string, 0, val, len );
}

/**
 * g_string_prepend_c:
 * @string: a #GString
 * @c: the byte to prepend on the start of the #GString
 *
 * Adds a byte onto the start of a #GString,
 * expanding it if necessary.
 *
 * Returns: @string
 */
GString *g_string_prepend_c( GString *string, gchar c )
{
	g_return_val_if_fail( string != NULL, NULL );

	return g_string_insert_c( string, 0, c );
}

/**
 * g_string_prepend_unichar:
 * @string: a #GString
 * @wc: a Unicode character
 *
 * Converts a Unicode character into UTF-8, and prepends it
 * to the string.
 *
 * Return value: @string
 */
GString *g_string_prepend_unichar( GString  *string, word  wc )
{
	g_return_val_if_fail( string != NULL, NULL );

	return g_string_insert_unichar( string, 0, wc );
}

/**
 * g_string_insert:
 * @string: a #GString
 * @pos: the position to insert the copy of the string
 * @val: the string to insert
 *
 * Inserts a copy of a string into a #GString,
 * expanding it if necessary.
 *
 * Returns: @string
 */
GString *g_string_insert( GString *string, gssize pos, const gchar *val )
{
	g_return_val_if_fail( string != NULL, NULL );
	g_return_val_if_fail( val != NULL, string );

	if( pos >= 0 )
		g_return_val_if_fail( pos <= string->len, string );

	return g_string_insert_len( string, pos, val, -1 );
}

/**
 * g_string_insert_c:
 * @string: a #GString
 * @pos: the position to insert the byte
 * @c: the byte to insert
 *
 * Inserts a byte into a #GString, expanding it if necessary.
 *
 * Returns: @string
 */
GString *g_string_insert_c( GString *string, gssize pos, gchar c )
{
	g_return_val_if_fail( string != NULL, NULL );

	g_string_maybe_expand( string, 1 );

	if( pos < 0 )
		pos = string->len;
	else
		g_return_val_if_fail( pos <= string->len, string );

	/* If not just an append, move the old stuff */
	if( pos < string->len )
		memmove( string->str + pos + 1, string->str + pos, string->len - pos );

	string->str[pos] = c;

	string->len += 1;

	string->str[string->len] = 0;

	return string;
}

/**
 * g_string_insert_unichar:
 * @string: a #GString
 * @pos: the position at which to insert character, or -1
 *     to append at the end of the string
 * @wc: a Unicode character
 *
 * Converts a Unicode character into UTF-8, and insert it
 * into the string at the given position.
 *
 * Return value: @string
 */
GString *g_string_insert_unichar( GString *string, gssize pos, word  wc )
{
	gint charlen, first, i;
	gchar *dest;

	g_return_val_if_fail( string != NULL, NULL );

	/* Code copied from g_unichar_to_utf() */
	if( wc < 0x80 )
	{
		first = 0;
		charlen = 1;
	}
	else if( wc < 0x800 )
	{
		first = 0xc0;
		charlen = 2;
	}
	else if( wc < 0x10000 )
	{
		first = 0xe0;
		charlen = 3;
	}
	else if( wc < 0x200000 )
	{
		first = 0xf0;
		charlen = 4;
	}
	else if( wc < 0x4000000 )
	{
		first = 0xf8;
		charlen = 5;
	}
	else
	{
		first = 0xfc;
		charlen = 6;
	}
	/* End of copied code */

	g_string_maybe_expand( string, charlen );

	if( pos < 0 )
		pos = string->len;
	else
		g_return_val_if_fail( pos <= string->len, string );

	/* If not just an append, move the old stuff */
	if( pos < string->len )
		memmove( string->str + pos + charlen, string->str + pos, string->len - pos );

	dest = string->str + pos;
	/* Code copied from g_unichar_to_utf() */
	for( i = charlen - 1; i > 0; --i )
	{
		dest[i] = ( wc & 0x3f ) | 0x80;
		wc >>= 6;
	}
	dest[0] = wc | first;
	/* End of copied code */

	string->len += charlen;

	string->str[string->len] = 0;

	return string;
}

/**
 * g_string_overwrite:
 * @string: a #GString
 * @pos: the position at which to start overwriting
 * @val: the string that will overwrite the @string starting at @pos
 *
 * Overwrites part of a string, lengthening it if necessary.
 *
 * Return value: @string
 *
 * Since: 2.14
 */
GString *g_string_overwrite( GString *string, gssize pos, gchar *val )
{
	g_return_val_if_fail( val != NULL, string );
	return g_string_overwrite_len( string, pos, val, strlen( val ) );
}

/**
 * g_string_overwrite_len:
 * @string: a #GString
 * @pos: the position at which to start overwriting
 * @val: the string that will overwrite the @string starting at @pos
 * @len: the number of bytes to write from @val
 *
 * Overwrites part of a string, lengthening it if necessary.
 * This function will work with embedded nuls.
 *
 * Return value: @string
 *
 * Since: 2.14
 */
GString *g_string_overwrite_len( GString *string, gssize pos, const gchar *val, gssize len )
{
	gssize end;

	g_return_val_if_fail( string != NULL, NULL );

	if( !len )
		return string;

	g_return_val_if_fail( val != NULL, string );
	g_return_val_if_fail( pos <= string->len, string );

	if( len < 0 )
		len = strlen( val );

	end = pos + len;

	if( end > string->len )
		g_string_maybe_expand( string, end - string->len );

	memcpy( string->str + pos, val, len );

	if( end > string->len )
	{
		string->str[end] = '\0';
		string->len = end;
	}

	return string;
}

/**
 * g_string_erase:
 * @string: a #GString
 * @pos: the position of the content to remove
 * @len: the number of bytes to remove, or -1 to remove all
 *       following bytes
 *
 * Removes @len bytes from a #GString, starting at position @pos.
 * The rest of the #GString is shifted down to fill the gap.
 *
 * Returns: @string
 */
GString *g_string_erase( GString *string, gssize pos, gssize len )
{
	g_return_val_if_fail( string != NULL, NULL );
	g_return_val_if_fail( pos >= 0, string );
	g_return_val_if_fail( pos <= string->len, string );

	if( len < 0 )
		len = string->len - pos;
	else
	{
		g_return_val_if_fail( pos + len <= string->len, string );

		if( pos + len < string->len )
			memmove( string->str + pos, string->str + pos + len, string->len - ( pos + len ) );
	}

	string->len -= len;

	string->str[string->len] = 0;

	return string;
}

/**
 * g_string_ascii_down:
 * @string: a GString
 *
 * Converts all uppercase ASCII letters to lowercase ASCII letters.
 *
 * Return value: passed-in @string pointer, with all the
 *     uppercase characters converted to lowercase in place,
 *     with semantics that exactly match g_ascii_tolower().
 */
GString *g_string_ascii_down( GString *string )
{
	gchar *s;
	gint n;

	g_return_val_if_fail( string != NULL, NULL );

	n = string->len;
	s = string->str;

	while( n )
	{
		*s = g_ascii_tolower( *s );
		s++;
		n--;
	}

	return string;
}

/**
 * g_string_ascii_up:
 * @string: a GString
 *
 * Converts all lowercase ASCII letters to uppercase ASCII letters.
 *
 * Return value: passed-in @string pointer, with all the
 *     lowercase characters converted to uppercase in place,
 *     with semantics that exactly match g_ascii_toupper().
 */
GString *g_string_ascii_up( GString *string )
{
	gchar *s;
	gint n;

	g_return_val_if_fail( string != NULL, NULL );

	n = string->len;
	s = string->str;

	while( n )
	{
		*s = g_ascii_toupper( *s );
		s++;
		n--;
	}

	return string;
}

/**
 * g_string_down:
 * @string: a #GString
 *
 * Converts a #GString to lowercase.
 *
 * Returns: the #GString
 *
 * Deprecated:2.2: This function uses the locale-specific
 *     tolower() function, which is almost never the right thing.
 *     Use g_string_ascii_down() or g_utf8_strdown() instead.
 */
GString *g_string_down( GString *string )
{
	guchar *s;
	gint n;

	g_return_val_if_fail( string != NULL, NULL );

	n = string->len;
	s = ( guchar * ) string->str;

	while( n )
	{
		if( isupper( *s ) )
			*s = tolower( *s );
		s++;
		n--;
	}

	return string;
}

/**
 * g_string_up:
 * @string: a #GString
 *
 * Converts a #GString to uppercase.
 *
 * Return value: @string
 *
 * Deprecated:2.2: This function uses the locale-specific
 *     toupper() function, which is almost never the right thing.
 *     Use g_string_ascii_up() or g_utf8_strup() instead.
 */
GString *g_string_up( GString *string )
{
	guchar *s;
	gint n;

	g_return_val_if_fail( string != NULL, NULL );

	n = string->len;
	s = ( guchar * ) string->str;

	while( n )
	{
		if( islower( *s ) )
			*s = toupper( *s );
		s++;
		n--;
	}

	return string;
}

/**
 * g_string_append_vprintf:
 * @string: a #GString
 * @format: the string format. See the printf() documentation
 * @args: the list of arguments to insert in the output
 *
 * Appends a formatted string onto the end of a #GString.
 * This function is similar to g_string_append_printf()
 * except that the arguments to the format string are passed
 * as a va_list.
 *
 * Since: 2.14
 */
void g_string_append_vprintf( GString *string, const gchar *format, va_list args )
{
	gchar *buf;
	gint len;

	g_return_if_fail( string != NULL );
	g_return_if_fail( format != NULL );

	len = g_vasprintf( &buf, format, args );

	if( len >= 0 )
	{
		g_string_maybe_expand( string, len );
		memcpy( string->str + string->len, buf, len + 1 );
		string->len += len;
		free( buf );
	}
}

/**
 * g_string_vprintf:
 * @string: a #GString
 * @format: the string format. See the printf() documentation
 * @args: the parameters to insert into the format string
 *
 * Writes a formatted string into a #GString.
 * This function is similar to g_string_printf() except that
 * the arguments to the format string are passed as a va_list.
 *
 * Since: 2.14
 */
void g_string_vprintf( GString *string, const gchar *format, va_list args )
{
	g_string_truncate( string, 0 );
	g_string_append_vprintf( string, format, args );
}

/**
 * g_string_sprintf:
 * @string: a #GString
 * @format: the string format. See the sprintf() documentation
 * @...: the parameters to insert into the format string
 *
 * Writes a formatted string into a #GString.
 * This is similar to the standard sprintf() function,
 * except that the #GString buffer automatically expands
 * to contain the results. The previous contents of the
 * #GString are destroyed.
 *
 * Deprecated: This function has been renamed to g_string_printf().
 */

/**
 * g_string_printf:
 * @string: a #GString
 * @format: the string format. See the printf() documentation
 * @...: the parameters to insert into the format string
 *
 * Writes a formatted string into a #GString.
 * This is similar to the standard sprintf() function,
 * except that the #GString buffer automatically expands
 * to contain the results. The previous contents of the
 * #GString are destroyed.
 */
void g_string_printf( GString *string, const gchar *format, ... )
{
	va_list args;

	g_string_truncate( string, 0 );

	va_start( args, format );
	g_string_append_vprintf( string, format, args );
	va_end( args );
}

/**
 * g_string_sprintfa:
 * @string: a #GString
 * @format: the string format. See the sprintf() documentation
 * @...: the parameters to insert into the format string
 *
 * Appends a formatted string onto the end of a #GString.
 * This function is similar to g_string_sprintf() except that
 * the text is appended to the #GString.
 *
 * Deprecated: This function has been renamed to g_string_append_printf()
 */

/**
 * g_string_append_printf:
 * @string: a #GString
 * @format: the string format. See the printf() documentation
 * @...: the parameters to insert into the format string
 *
 * Appends a formatted string onto the end of a #GString.
 * This function is similar to g_string_printf() except
 * that the text is appended to the #GString.
 */
void g_string_append_printf( GString *string, const gchar *format, ... )
{
	va_list args;

	va_start( args, format );
	g_string_append_vprintf( string, format, args );
	va_end( args );
}

// #####################################################################

/**
 * g_utf8_get_char_validated:
 * @p: a pointer to Unicode character encoded as UTF-8
 * @max_len: the maximum number of bytes to read, or -1, for no maximum or
 *           if @p is nul-terminated
 *
 * Convert a sequence of bytes encoded as UTF-8 to a Unicode character.
 * This function checks for incomplete characters, for invalid characters
 * such as characters that are out of the range of Unicode, and for
 * overlong encodings of valid characters.
 *
 * Return value: the resulting character. If @p points to a partial
 *    sequence at the end of a string that could begin a valid
 *    character (or if @max_len is zero), returns (word)-2;
 *    otherwise, if @p does not point to a valid UTF-8 encoded
 *    Unicode character, returns (word)-1.
 **/
word g_utf8_get_char_validated( const gchar *p, gssize max_len )
{
	word result;

	if( max_len == 0 )
		return ( word ) - 2;

	result = g_utf8_get_char_extended( p, max_len );

	if( result & 0x80000000 )
		return result;
	else if( !UNICODE_VALID( result ) )
		return ( word ) - 1;
	else
		return result;
}

/**
 * g_ascii_tolower:
 * @c: any character.
 *
 * Convert a character to ASCII lower case.
 *
 * Unlike the standard C library tolower() function, this only
 * recognizes standard ASCII letters and ignores the locale, returning
 * all non-ASCII characters unchanged, even if they are lower case
 * letters in a particular character set. Also unlike the standard
 * library function, this takes and returns a char, not an int, so
 * don't call it on <literal>EOF</literal> but no need to worry about casting to #guchar
 * before passing a possibly non-ASCII character in.
 *
 * Return value: the result of converting @c to lower case.
 *               If @c is not an ASCII upper case letter,
 *               @c is returned unchanged.
 **/
char g_ascii_tolower( gchar c )
{
	return g_ascii_isupper( c ) ? c - 'A' + 'a' : c;
}

/**
 * g_ascii_toupper:
 * @c: any character.
 *
 * Convert a character to ASCII upper case.
 *
 * Unlike the standard C library toupper() function, this only
 * recognizes standard ASCII letters and ignores the locale, returning
 * all non-ASCII characters unchanged, even if they are upper case
 * letters in a particular character set. Also unlike the standard
 * library function, this takes and returns a char, not an int, so
 * don't call it on <literal>EOF</literal> but no need to worry about casting to #guchar
 * before passing a possibly non-ASCII character in.
 *
 * Return value: the result of converting @c to upper case.
 *               If @c is not an ASCII lower case letter,
 *               @c is returned unchanged.
 **/
char g_ascii_toupper( gchar c )
{
	return g_ascii_islower( c ) ? c - 'a' + 'A' : c;
}

/**
 * g_vasprintf:
 * @string: the return location for the newly-allocated string.
 * @format: a standard printf() format string, but notice
 *          <link linkend="string-precision">string precision pitfalls</link>.
 * @args: the list of arguments to insert in the output.
 *
 * An implementation of the GNU vasprintf() function which supports
 * positional parameters, as specified in the Single Unix Specification.
 * This function is similar to g_vsprintf(), except that it allocates a
 * string to hold the output, instead of putting the output in a buffer
 * you allocate in advance.
 *
 * Returns: the number of bytes printed.
 *
 * Since: 2.4
 **/
gint g_vasprintf( gchar **string, const gchar *format, va_list args )
{
	gint len;
	g_return_val_if_fail( string != NULL, -1 );

	va_list args2;

	//G_VA_COPY (args2, args);
	args2 = args;

	*string = ( gchar * ) malloc( sizeof( gchar ) * g_printf_string_upper_bound( format, args ) );

	len = vsprintf( *string, format, args2 );
	va_end( args2 );

	return len;
}

/**
 * g_printf_string_upper_bound:
 * @format: the format string. See the printf() documentation
 * @args: the parameters to be inserted into the format string
 *
 * Calculates the maximum space needed to store the output
 * of the sprintf() function.
 *
 * Returns: the maximum space needed to store the formatted string
 */
gssize g_printf_string_upper_bound( const gchar *format, va_list args )
{
	gchar c;
	return vsnprintf( &c, 1, format, args ) + 1;
}
