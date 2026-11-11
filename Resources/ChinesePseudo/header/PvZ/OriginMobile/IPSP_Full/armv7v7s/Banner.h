/*****************************\
 * Copyright © 2008 - 2011   *
 * Electronic Arts           *
 * Version 12.3.1.0          *
\*****************************/
#ifndef _IPSP_BANNER_H_
	#define _IPSP_BANNER_H_

#import <Foundation/Foundation.h>

@interface Banner : NSObject <NSCoding, NSCopying> {
	int			m_iBannerId;
	NSString*	m_Title;
	NSString*	m_URL;
	NSData*		m_ImgData;
	NSString*	m_Type;
}

@property (nonatomic) int	m_iBannerId;
@property (nonatomic, retain) NSString*	m_Title;
@property (nonatomic, retain) NSString*	m_URL;
@property (nonatomic, retain) NSData*	m_ImgData;
@property (nonatomic, retain) NSString*	m_Type;

@end

#endif //_IPSP_BANNER_H_
