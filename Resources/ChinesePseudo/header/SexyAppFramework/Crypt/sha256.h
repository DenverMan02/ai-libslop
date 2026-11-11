
/* MD5DEEP - sha256.h
 *
 * By Jesse Kornblum
 *
 * This is a work of the US Government. In accordance with 17 USC 105,
 * copyright protection is not available for any work of the US Government.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/* $Id: sha256.h 501 2011-09-25 17:12:27Z xchatty $ */

#ifndef _SHA256_H
#define _SHA256_H

#include "Common.h"

namespace Sexy
{
	const uint32 SHA256_DIGEST_LENGTH = 32;
	struct SHA256Context
	{
	  uint32 total[2];
	  uint32 state[8];
	  uint8 buffer[64];
	};

	extern void SHA256Init( SHA256Context* ctx );
	extern void SHA256Update( SHA256Context* ctx, const uint8 *input, uint32 length );
	extern void SHA256Final( SHA256Context* ctx, uint8 digest[SHA256_DIGEST_LENGTH] );
}

#endif /* sha256.h */
