/* GLIB sliced memory - fast concurrent memory chunk allocator
 * Copyright (C) 2005 Tim Janik
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
/* MT safe */

#include <Arduino.h>

#include "gslice.h"

gpointer g_slice_alloc          	(gsize	       block_size)
{
	return malloc(block_size);
}

gpointer g_slice_alloc0         	(gsize         block_size)
{
	gpointer *data = malloc(block_size);
	memset(data, 0, block_size);
	return data;
}

gpointer g_slice_copy                   (gsize         block_size,
                                         gconstpointer mem_block)
{
	gpointer *data = malloc(block_size);
	memcpy(data, mem_block, block_size);
	return data;
}

void     g_slice_free1          	(gsize         block_size,
					 gpointer      mem_block)
{
	free(mem_block);
}

void     g_slice_free_chain_with_offset (gsize         block_size,
					 gpointer      mem_chain,
					 gsize         next_offset)
{
	gpointer slice = mem_chain;

	while (slice)
	{
		guint8 *current = slice;
		slice = *(gpointer*) (current + next_offset);
		free( current );
	}
}
