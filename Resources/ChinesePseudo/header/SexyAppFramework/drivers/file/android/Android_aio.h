#ifndef _ANDROID_AIO_H_
#define _ANDROID_AIO_H_

#include <sys/types.h>

namespace Sexy
{
	class AndroidAsyncIOFileDriver;
}

// Android doesn't support asynch IO, so we're going to make something similar to the posix standard
namespace AndroidAIO
{

	
enum
{
	  LIO_READ
	, LIO_WRITE
	, LIO_NOP
};

struct aiocb
{
	int aio_fildes; 	// File descriptor
	int aio_lio_opcode;
	/*volatile*/ void * aio_buf;
	size_t aio_nbytes;
	off_t aio_offset;

	// internal stuff
	int32 error_code;
	int32 return_code;

	class Sexy::AndroidAsyncIOFileDriver * pAsyncDriver;
};

int aio_read( struct aiocb * pContext  );
//int aio_write (struct aiocb *pContext);
//int aio_cancel (int fd, struct aiocb *pContext);

int aio_error( struct aiocb const * pContext  );
ssize_t aio_return (struct aiocb *pContext);


}

#endif // _ANDROID_AIO_H_

