/*****************************\
 * Copyright © 2008 - 2010   *
 * Electronic Arts           *
 * Version 1.0.0             *
\*****************************/
#ifndef _ZIPUTIL_H_
#define _ZIPUTIL_H_

#import <Foundation/Foundation.h>
#import "ZipArchive.h"

#define	TEMP_FILE_NAME	@"tempfile.txt.gz"
#define	UNZIPPED_DIR	@"unzipped"

@interface ZipUtil : NSObject {
	ZipArchive	*zipArchive;
}

@property (nonatomic, retain) ZipArchive *zipArchive;
		  
-(BOOL)CreateAndOpenFile:(NSData*)data;
-(NSData*)GetFileData:(NSData*)srcData, int fileIndex;
-(NSData*)GetFileData:(NSData*)srcData :(NSString*)fileName;
-(BOOL)CloseAndDeleteFile;
@end

#endif // _ZIPUTIL_H_
