/*****************************\
 * Copyright © 2008 - 2011   *
 * Electronic Arts           *
 * Version 12.3.1.0          *
\*****************************/

#ifndef _IPSP_MTXCATEGORY_H_
	#define _IPSP_MTXCATEGORY_H_

#import <Foundation/Foundation.h>

@interface MTXCategory : NSObject <NSCoding, NSCopying> {
	int			m_iCategoryId;
	NSString*	m_Title;
	NSData*		m_SelImgData;
	NSData*		m_RegImgData;
	int			m_BadgesCount;
}

@property (nonatomic) int	m_iCategoryId;
@property (nonatomic, retain) NSString*	m_Title;
@property (nonatomic, retain) NSData*	m_SelImgData;
@property (nonatomic, retain) NSData*	m_RegImgData;
@property (nonatomic) int	m_BadgesCount;

@end

#endif //_IPSP_MTXCATEGORY_H_