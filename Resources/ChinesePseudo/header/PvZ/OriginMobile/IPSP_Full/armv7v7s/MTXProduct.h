/*****************************\
 * Copyright © 2008 - 2011   *
 * Electronic Arts           *
 * Version 12.3.1.0          *
\*****************************/

#ifndef _IPSP_MTXPRODUCT_H_
	#define _IPSP_MTXPRODUCT_H_

#import <Foundation/Foundation.h>


@interface MTXProduct : NSObject <NSCoding, NSCopying> {
	NSString*	m_Title;
	int			m_iSellId;
	NSString*	m_Desc;
	NSString*	m_Version;
	NSString*	m_ProdIdentifier;
	bool		m_bFreeItem;
	double		m_dItemPrice;
	NSDate*		m_ReleaseDate;
	NSString*	m_Category;
	int			m_iPackSize;
	NSData*		m_BinPack; //Thumbnail, screen short (game understandable format)
	NSString*	m_BinPackURL; //URL for downloading binary pack
	bool		m_bGranted;
	bool		m_bDownlodable;	
	bool		m_bItemNew;
	NSString*	m_LocalCurrency;
	NSString*	m_CurrencySymbol;
	bool		m_bConsumable;
	NSString*	m_Dummy;
}

@property (nonatomic) int	 m_iSellId;
@property (nonatomic) double m_dItemPrice;
@property (nonatomic) int	 m_iPackSize;
@property (nonatomic) bool	 m_bGranted;
@property (nonatomic) bool	 m_bFreeItem;
@property (nonatomic) bool	 m_bDownlodable;
@property (nonatomic) bool	 m_bItemNew;
@property (nonatomic) bool	 m_bConsumable;

@property (nonatomic, retain) NSString*	m_Title;
@property (nonatomic, retain) NSString*	m_Desc;
@property (nonatomic, retain) NSString*	m_Version;
@property (nonatomic, retain) NSString*	m_ProdIdentifier;
@property (nonatomic, retain) NSDate*	m_ReleaseDate;
@property (nonatomic, retain) NSString*	m_Category;
@property (nonatomic, retain) NSData*	m_BinPack;
@property (nonatomic, retain) NSString*	m_BinPackURL;
@property (nonatomic, retain) NSString*	m_LocalCurrency;
@property (nonatomic, retain) NSString*	m_CurrencySymbol;
@property (nonatomic, retain) NSString*	m_Dummy;

@end

#endif //_IPSP_MTXPRODUCT_H_