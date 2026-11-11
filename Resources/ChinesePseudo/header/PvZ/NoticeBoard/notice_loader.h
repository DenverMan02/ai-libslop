/*
 * notice_loader.h
 *
 *  Created on: 2013-9-11
 *      Author: chenyc
 */

#ifndef NOTICE_LOADER_H_
#define NOTICE_LOADER_H_

#include "NetworkServiceManager.h"

class noticeRequest : public Sexy::NetworkServiceListener
{
public:
	noticeRequest(){};
	virtual~noticeRequest(){};

	void sendNoticeRequest();

	virtual void ServiceRequestCompleted( const Sexy::StructuredData* response, const void* context );

	virtual void ServiceRequestCompleted( ImageLib::Image*& image, const void* context );

	virtual void ServiceRequestCompleted( const Buffer* buffer, const void* context );

	virtual void ServiceRequestFailed( const StructuredData* response, const void* context );
};



class noticeTranslate
{
public:
	noticeTranslate(){};
	~noticeTranslate(){};

	void enCodeNotice( const std::string& notice, std::string& title,  std::string& content, std::string& Url );



};


#endif /* NOTICE_LOADER_H_ */
