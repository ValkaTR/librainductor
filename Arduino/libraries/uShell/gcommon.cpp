// #####################################################################

#include "gcommon.h"

// #####################################################################

static const char utf8_skip_data[256] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 1, 1
};

const char *g_utf8_skip = utf8_skip_data;

static unsigned int ascii_table_data[256] = {
	0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004,
	0x004, 0x104, 0x104, 0x004, 0x104, 0x104, 0x004, 0x004,
	0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004,
	0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004,
	0x140, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0,
	0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0,
	0x459, 0x459, 0x459, 0x459, 0x459, 0x459, 0x459, 0x459,
	0x459, 0x459, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0,
	0x0d0, 0x653, 0x653, 0x653, 0x653, 0x653, 0x653, 0x253,
	0x253, 0x253, 0x253, 0x253, 0x253, 0x253, 0x253, 0x253,
	0x253, 0x253, 0x253, 0x253, 0x253, 0x253, 0x253, 0x253,
	0x253, 0x253, 0x253, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x0d0,
	0x0d0, 0x473, 0x473, 0x473, 0x473, 0x473, 0x473, 0x073,
	0x073, 0x073, 0x073, 0x073, 0x073, 0x073, 0x073, 0x073,
	0x073, 0x073, 0x073, 0x073, 0x073, 0x073, 0x073, 0x073,
	0x073, 0x073, 0x073, 0x0d0, 0x0d0, 0x0d0, 0x0d0, 0x004
	/* the upper 128 are all zeroes */
};

const unsigned int *g_ascii_table = ascii_table_data;

// #####################################################################

//static pthread_mutex_t g_atomic_lock = PTHREAD_MUTEX_INITIALIZER;

gint g_atomic_int_get( volatile gint *atomic )
{
	gint value;

	//pthread_mutex_lock (&g_atomic_lock);
	value = *atomic;
	//pthread_mutex_unlock (&g_atomic_lock);

	return value;
}

void g_atomic_int_set( volatile gint *atomic, gint value )
{
	//pthread_mutex_lock (&g_atomic_lock);
	*atomic = value;
	//pthread_mutex_unlock (&g_atomic_lock);
}

void g_atomic_int_inc( volatile gint *atomic )
{
	//pthread_mutex_lock (&g_atomic_lock);
	( *atomic )++;
	//pthread_mutex_unlock (&g_atomic_lock);
}

gboolean g_atomic_int_dec_and_test( volatile gint *atomic )
{
	gboolean is_zero;

	//pthread_mutex_lock (&g_atomic_lock);
	is_zero = --( *atomic ) == 0;
	//pthread_mutex_unlock (&g_atomic_lock);

	return is_zero;
}

// #####################################################################

/* Like g_utf8_get_char, but take a maximum length
 * and return (word)-2 on incomplete trailing character;
 * also check for malformed or overlong sequences
 * and return (word)-1 in this case.
 */
static inline word g_utf8_get_char_extended( const char *p, ssize_t max_len )
{
	unsigned int i, len;
	word min_code;
	word wc = ( unsigned char ) * p;

	if( wc < 0x80 )
	{
		return wc;
	}
	else if( ( wc < 0xc0 ) )
	{
		return ( word ) - 1;
	}
	else if( wc < 0xe0 )
	{
		len = 2;
		wc &= 0x1f;
		min_code = 1 << 7;
	}
	else if( wc < 0xf0 )
	{
		len = 3;
		wc &= 0x0f;
		min_code = 1 << 11;
	}
	else if( wc < 0xf8 )
	{
		len = 4;
		wc &= 0x07;
		min_code = 1 << 16;
	}
	else if( wc < 0xfc )
	{
		len = 5;
		wc &= 0x03;
		min_code = 1 << 21;
	}
	else if( wc < 0xfe )
	{
		len = 6;
		wc &= 0x01;
		min_code = 1 << 26;
	}
	else
	{
		return ( word ) - 1;
	}

	if( ( max_len >= 0 && len > max_len ) )
	{
		for( i = 1; i < max_len; i++ )
		{
			if( ( ( ( unsigned char * )p )[i] & 0xc0 ) != 0x80 )
				return ( word ) - 1;
		}
		return ( word ) - 2;
	}

	for( i = 1; i < len; ++i )
	{
		word ch = ( ( unsigned char * )p )[i];

		if( ( ( ch & 0xc0 ) != 0x80 ) )
		{
			if( ch )
				return ( word ) - 1;
			else
				return ( word ) - 2;
		}

		wc <<= 6;
		wc |= ( ch & 0x3f );
	}

	if( ( wc < min_code ) )
		return ( word ) - 1;

	return wc;
}

// #####################################################################

struct msort_param
{
	size_t s;
	size_t var;
	GCompareDataFunc cmp;
	void *arg;
	char *t;
};

static void msort_with_tmp( const struct msort_param *p, void *b, size_t n );

static void msort_with_tmp( const struct msort_param *p, void *b, size_t n )
{
	char *b1, *b2;
	size_t n1, n2;
	char *tmp = p->t;
	const size_t s = p->s;
	GCompareDataFunc cmp = p->cmp;
	void *arg = p->arg;

	if( n <= 1 )
		return;

	n1 = n / 2;
	n2 = n - n1;
	b1 = b;
	b2 = ( char * ) b + ( n1 * p->s );

	msort_with_tmp( p, b1, n1 );
	msort_with_tmp( p, b2, n2 );

	switch( p->var )
	{
		case 0:
			while( n1 > 0 && n2 > 0 )
			{
				if( ( *cmp )( b1, b2, arg ) <= 0 )
				{
					*( guint32 * ) tmp = *( guint32 * ) b1;
					b1 += sizeof( guint32 );
					--n1;
				}
				else
				{
					*( guint32 * ) tmp = *( guint32 * ) b2;
					b2 += sizeof( guint32 );
					--n2;
				}
				tmp += sizeof( guint32 );
			}
			break;
		case 1:
			while( n1 > 0 && n2 > 0 )
			{
				if( ( *cmp )( b1, b2, arg ) <= 0 )
				{
					*( guint64 * ) tmp = *( guint64 * ) b1;
					b1 += sizeof( guint64 );
					--n1;
				}
				else
				{
					*( guint64 * ) tmp = *( guint64 * ) b2;
					b2 += sizeof( guint64 );
					--n2;
				}
				tmp += sizeof( guint64 );
			}
			break;
		case 2:
			while( n1 > 0 && n2 > 0 )
			{
				unsigned long *tmpl = ( unsigned long * ) tmp;
				unsigned long *bl;

				tmp += s;
				if( ( *cmp )( b1, b2, arg ) <= 0 )
				{
					bl = ( unsigned long * ) b1;
					b1 += s;
					--n1;
				}
				else
				{
					bl = ( unsigned long * ) b2;
					b2 += s;
					--n2;
				}
				while( tmpl < ( unsigned long * ) tmp )
					*tmpl++ = *bl++;
			}
			break;
		case 3:
			while( n1 > 0 && n2 > 0 )
			{
				if( ( *cmp )( *( const void ** ) b1, *( const void ** ) b2, arg ) <= 0 )
				{
					*( void ** ) tmp = *( void ** ) b1;
					b1 += sizeof( void * );
					--n1;
				}
				else
				{
					*( void ** ) tmp = *( void ** ) b2;
					b2 += sizeof( void * );
					--n2;
				}
				tmp += sizeof( void * );
			}
			break;
		default:
			while( n1 > 0 && n2 > 0 )
			{
				if( ( *cmp )( b1, b2, arg ) <= 0 )
				{
					memcpy( tmp, b1, s );
					tmp += s;
					b1 += s;
					--n1;
				}
				else
				{
					memcpy( tmp, b2, s );
					tmp += s;
					b2 += s;
					--n2;
				}
			}
			break;
	}

	if( n1 > 0 )
		memcpy( tmp, b1, n1 * s );
	memcpy( b, p->t, ( n - n2 ) * s );
}


static void msort_r( void *b, size_t n, size_t s, GCompareDataFunc cmp, void *arg )
{
	size_t size = n * s;
	char *tmp = NULL;
	struct msort_param p;

	/* For large object sizes use indirect sorting.  */
	if( s > 32 )
		size = 2 * n * sizeof( void * ) + s;

	if( size < 1024 )
		/* The temporary array is small, so put it on the stack.  */
		//p.t = g_alloca (size);
		p.t = malloc( size );
	else
	{
		/* It's large, so malloc it.  */
		tmp = malloc( size );
		p.t = tmp;
	}

	p.s = s;
	p.var = 4;
	p.cmp = cmp;
	p.arg = arg;

	if( s > 32 )
	{
		/* Indirect sorting.  */
		char *ip = ( char * ) b;
		void **tp = ( void ** )( p.t + n * sizeof( void * ) );
		void **t = tp;
		void *tmp_storage = ( void * )( tp + n );
		char *kp;
		size_t i;

		while( ( void * ) t < tmp_storage )
		{
			*t++ = ip;
			ip += s;
		}
		p.s = sizeof( void * );
		p.var = 3;
		msort_with_tmp( &p, p.t + n * sizeof( void * ), n );

		/* tp[0] .. tp[n - 1] is now sorted, copy around entries of
		the original array.  Knuth vol. 3 (2nd ed.) exercise 5.2-10.  */
		for( i = 0, ip = ( char * ) b; i < n; i++, ip += s )
			if( ( kp = tp[i] ) != ip )
			{
				size_t j = i;
				char *jp = ip;
				memcpy( tmp_storage, ip, s );

				do
				{
					size_t k = ( kp - ( char * ) b ) / s;
					tp[j] = jp;
					memcpy( jp, kp, s );
					j = k;
					jp = kp;
					kp = tp[k];
				}
				while( kp != ip );

				tp[j] = jp;
				memcpy( jp, tmp_storage, s );
			}
	}
	else
	{
		if( ( s & ( sizeof( guint32 ) - 1 ) ) == 0
		        && ( ( char * ) b - ( char * ) 0 ) % ALIGNOF_GUINT32 == 0 )
		{
			if( s == sizeof( guint32 ) )
				p.var = 0;
			else if( s == sizeof( guint64 )
			         && ( ( char * ) b - ( char * ) 0 ) % ALIGNOF_GUINT64 == 0 )
				p.var = 1;
			else if( ( s & ( sizeof( unsigned long ) - 1 ) ) == 0
			         && ( ( char * ) b - ( char * ) 0 )
			         % ALIGNOF_UNSIGNED_LONG == 0 )
				p.var = 2;
		}
		msort_with_tmp( &p, b, n );
	}
	g_free( tmp );
}

/**
 * g_qsort_with_data:
 * @pbase: start of array to sort
 * @total_elems: elements in the array
 * @size: size of each element
 * @compare_func: function to compare elements
 * @user_data: data to pass to @compare_func
 *
 * This is just like the standard C qsort() function, but
 * the comparison routine accepts a user data argument.
 *
 * This is guaranteed to be a stable sort since version 2.32.
 */
void g_qsort_with_data( gconstpointer pbase, gint total_elems, gsize size, GCompareDataFunc compare_func, gpointer user_data )
{
	msort_r( ( gpointer )pbase, total_elems, size, compare_func, user_data );
}

// #####################################################################
