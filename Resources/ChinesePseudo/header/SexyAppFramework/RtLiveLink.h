#pragma once
#ifndef __RTLIVELINK_H__
#define __RTLIVELINK_H__
//****************************************************************************
//**
//**  File     :  RTLIVELINK.H
//**  Summary  :  Header - Rt - LiveLink-related support
//**
//----------------------------------------------------------------------------
//**       $Id:$ 
//** $DateTime:$ 
//**   $Author:$ 
//**   $Change:$ 
//****************************************************************************
//============================================================================
//    HEADERS
//============================================================================
#include "Common.h"

#include "Reflection.h"
#include "RtSerial.h"

#if SEXY_IS_LIVELINK_ENABLED
	#include "LiveLinkPacket.h"
#endif



namespace Sexy 
{
    
namespace RtLiveLink 
{

//============================================================================
//    DEFINITIONS / ENUMERATIONS / SIMPLE TYPEDEFS
//============================================================================
//============================================================================
//    CLASSES / STRUCTURES
//============================================================================
#if SEXY_IS_LIVELINK_ENABLED


class RtObjectSubPathValueSync
{
public:
	enum EResult
	{
		EResult_Invalid,
		EResult_NoError,
		EResult_ErrorNullRtId,
		EResult_ErrorInvalidRtId, // could not lookup RtObject from RtId.
		EResult_ErrorNavigatingPath, // bad/malformed path, subpath does not exist, non-lead property found along path.
		EResult_ErrorNoReflectionData, // the object or one of it's subobjects did not have reflection data
		EResult_ErrorReflectionDisabled, // reflection has been disabled in the game.
	};

	RtObjectSubPathValueSync(const RtId& inRtId, std::string inSubPath);
	bool IsValid()
	{
		return mNavResult == EResult_NoError;
	}

	bool SyncWithRton(RtSerialRtonSync& inRtonSync, const std::string& inRtonValueKey, 
					  const std::string& inRtonRtClassNameKey, const std::string& inRtonReflectionTypeKey);

	bool SyncWithRton(RtSerialRtonSync& inRtonSync, const std::string& inRtonValueKey)
	{
		return SyncWithRton(inRtonSync, inRtonValueKey, "", "");
	}
    
    bool SyncArrayElementWithRton(RtSerialRtonSync& inRtonSync, const std::string& inRtonValueKey, int32 inElementIndex);

    bool InsertArrayElementWithRton(RtSerialRtonSync& inRtonSync, const std::string& inRtonValueKey, int32 inInsertAtIndex, int32& outActualInsertAtIndex);
    bool DeleteArrayElement(int32 inDeleteIndex);
    
private:
    template<typename T>
    T* castBasedOnSubTypeCategory(typename T::SubTypeCategory inSubTypeCategory)
    {
        if (mInstanceDataType != NULL)
        {
            if (mInstanceDataType->GetTypeCategory() == T::StaticGetTypeCategory())
            {
                T* subType = (T*)mInstanceDataType;
                if (subType->GetSubTypeCategory() == inSubTypeCategory)
                {
                    return subType;
                }
            }
        }
        
        return NULL;   
    }

	RtObject*			mObj;
	RtClass*			mObjClass;
	void*				mInstanceData;
	Reflection::RType*	mInstanceDataType;

	RtId				mId; 
	std::string			mSubPath;
	std::string			mRemainingSubPath;

	EResult				mNavResult;
};


/*
	RequestInfo
*/
struct RequestInfo
{
	int32 mResponseToken;
	RtSerialRtonReader* mRtonRequestInfo;

	RequestInfo(int32 inResponseToken = -1, RtSerialRtonReader* inRtonRequestInfo = NULL)
	: mResponseToken(inResponseToken)
	, mRtonRequestInfo(inRtonRequestInfo)
	{
	}
	~RequestInfo()
	{
		delete mRtonRequestInfo;
	}
};

/*
	BaseRequestPacket
*/
class BaseRequestPacket
: public LiveLinkPacket
{
public:
	RT_CLASS_DEFINE_ABSTRACT(RtLiveLink::BaseRequestPacket, LiveLinkPacket, LiveLinkPacketMetaClass) {}

	BaseRequestPacket()
	{}

protected:
	virtual bool SyncPayload(RtSerialBuffer& inSerialBuffer) override
	{
		SEXY_ASSERT(inSerialBuffer.IsReading()); // Only support reading this packet at this time.

		int32 responseToken = inSerialBuffer.ReadInt32Fixed();
		int32 rtonByteCount = inSerialBuffer.ReadInt32Fixed();

		if (rtonByteCount == 0)
		{
			mRequestInfo = RequestInfo(responseToken, NULL);
		}
		else
		{
			mRequestInfo.mResponseToken = responseToken;
			mRequestInfo.mRtonRequestInfo = new RtSerialRtonReader(inSerialBuffer.GetDataPtr()+inSerialBuffer.Tell(), rtonByteCount);
		}
		
		return true;
	}

public:
	RequestInfo mRequestInfo;
};

/*
	BaseResponsePacket
*/
class BaseResponsePacket
: public LiveLinkPacket
{
public:
	RT_CLASS_DEFINE_ABSTRACT(RtLiveLink::BaseResponsePacket, LiveLinkPacket, LiveLinkPacketMetaClass)
	{}

	BaseResponsePacket(const RequestInfo* inRequestInfo)
	: mRequestInfo(inRequestInfo)
	{}

protected:
	virtual void WriteRtonPayload(RtSerialBuffer& inSerialBuffer) = 0;

	void WriteRtonError(RtSerialBuffer& inSerialBuffer, const std::string& inErrorStr, RtSerialRtonWriter* inExistingWriter = NULL)
	{
		if (inExistingWriter)
		{
			inExistingWriter->WriteString("$error", inErrorStr);
		}
		else
		{
			RtSerialRtonWriter rton(&inSerialBuffer);
			rton.BeginDocumentObject();
			rton.WriteString("$error", inErrorStr);
			rton.EndDocumentObject();
		}
	}

	virtual bool SyncPayload(RtSerialBuffer& inSerialBuffer) override
	{
		SEXY_ASSERT(inSerialBuffer.IsWriting()); // Only support sending this packet at this time.

		inSerialBuffer.WriteInt32Fixed(mRequestInfo ? mRequestInfo->mResponseToken : -1);

		// placeholder for rton byte size (filled in afterwards)
		uint32 rtonSizeOffset = inSerialBuffer.Tell();
		inSerialBuffer.WriteInt32Fixed(0);

		// write the rton payload
		uint32 startOffset = inSerialBuffer.Tell();
		WriteRtonPayload(inSerialBuffer);
		uint32 endOffset = inSerialBuffer.Tell();

		// patch up the rton size
		int32 rtonSize = endOffset - startOffset;
		inSerialBuffer.SeekStart(rtonSizeOffset);
		inSerialBuffer.WriteInt32Fixed(rtonSize);
		inSerialBuffer.SeekStart(endOffset);
		
		return true;
	}

public:
	const RequestInfo* mRequestInfo;
};

/*
	ReflectionSymbols
*/
namespace ReflectionSymbols
{
	class RequestPacket
	: public BaseRequestPacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::ReflectionSymbols::RequestPacket, BaseRequestPacket, LiveLinkPacketMetaClass);
	};

	class ResponsePacket
	: public BaseResponsePacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::ReflectionSymbols::ResponsePacket, BaseResponsePacket, LiveLinkPacketMetaClass);
		
		ResponsePacket(const RequestInfo* inRequestInfo = NULL)
		: BaseResponsePacket(inRequestInfo)
		{}

		static void ProcessRequest(const LiveLinkPacket& inPacket)
		{
			RequestPacket* packet = inPacket.Cast<RequestPacket>();
			if (!packet)
			{
				SEXY_WARN("RtLiveLink::ReflectionSymbols::RequestPacket::ProcessPacket: Unexpected request packet type");
				return;
			}

			ResponsePacket(&packet->mRequestInfo).Send();
		} 

	protected:
		virtual void WriteRtonPayload(RtSerialBuffer& inSerialBuffer) override
		{
			Reflection::CRefSymbolDb::GetManualReflection()->WriteRtonRepresentation(&inSerialBuffer);
		}
	};
}

/*
	TableSummary
*/
namespace TableSummary
{
	class RequestPacket
	: public BaseRequestPacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::TableSummary::RequestPacket, BaseRequestPacket, LiveLinkPacketMetaClass);
	};

	class ResponsePacket
	: public BaseResponsePacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::TableSummary::ResponsePacket, BaseResponsePacket, LiveLinkPacketMetaClass);
		
		ResponsePacket(const RequestInfo* inRequestInfo = NULL)
		: BaseResponsePacket(inRequestInfo)
		{}

		static void ProcessRequest(const LiveLinkPacket& inPacket)
		{
			RequestPacket* packet = inPacket.Cast<RequestPacket>();
			if (!packet)
			{
				SEXY_WARN("RtLiveLink::TableSummary::RequestPacket::ProcessPacket: Unexpected request packet type");
				return;
			}

			ResponsePacket(&packet->mRequestInfo).Send();
		} 

	protected:
		virtual void WriteRtonPayload(RtSerialBuffer& inSerialBuffer) override
		{
			RtDb::GetDb()->WriteRtonTableSummary(&inSerialBuffer);
		}
	};
}

/*
	TableRtIdList
*/
namespace TableRtIdList
{
	class RequestPacket
	: public BaseRequestPacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::TableRtIdList::RequestPacket, BaseRequestPacket, LiveLinkPacketMetaClass);
	};

	class ResponsePacket
	: public BaseResponsePacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::TableRtIdList::ResponsePacket, BaseResponsePacket, LiveLinkPacketMetaClass);
		
		ResponsePacket(const RequestInfo* inRequestInfo = NULL)
		: BaseResponsePacket(inRequestInfo)
		{}

		static void ProcessRequest(const LiveLinkPacket& inPacket)
		{
			RequestPacket* packet = inPacket.Cast<RequestPacket>();
			if (!packet)
			{
				SEXY_WARN("RtLiveLink::TableRtIdList::ResponsePacket::ProcessPacket: Unexpected request packet type");
				return;
			}
			if (!packet->mRequestInfo.mRtonRequestInfo)
			{
				SEXY_WARN("RtLiveLink::TableRtIdList::ResponsePacket::ProcessPacket: Missing RTON request info");
				return;
			}
			
			ResponsePacket(&packet->mRequestInfo).Send();
		} 

	protected:
		virtual void WriteRtonPayload(RtSerialBuffer& inSerialBuffer) override
		{
			DBG_ASSERTE((mRequestInfo != NULL) && "RtLiveLink::TableRtIdList::ResponsePacket::WriteRtonPayload: Null request info");

			int32 tableIndex = -1;
			RtSerialRtonReader* reader = mRequestInfo->mRtonRequestInfo;
			if (reader->BeginDocumentObject())
			{
				tableIndex = reader->ReadInt32("table_index");
				reader->EndDocumentObject();
			}

			if (tableIndex < 0)
			{
				SEXY_WARN("RtLiveLink::TableRtIdList::ResponsePacket::WriteRtonPayload: Missing table index");
				WriteRtonError(inSerialBuffer, "Expected positive table_index");
				return;
			}
			RtDbTable* table = RtDb::GetDb()->GetTable(tableIndex);
			if (!table)
			{
				SEXY_WARN("RtLiveLink::TableRtIdList::ResponsePacket::WriteRtonPayload: Invalid table index %d", (int)tableIndex);
				WriteRtonError(inSerialBuffer, StrFormat("Invalid table index %d", tableIndex));
				return;
			}

			table->WriteRtonRtIdList(&inSerialBuffer);
		}
	};
}

/*
	GetRtObjectState
*/
namespace GetRtObjectState
{
	class RequestPacket
	: public BaseRequestPacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::GetRtObjectState::RequestPacket, BaseRequestPacket, LiveLinkPacketMetaClass);
	};

	class ResponsePacket
	: public BaseResponsePacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::GetRtObjectState::ResponsePacket, BaseResponsePacket, LiveLinkPacketMetaClass);
		
		ResponsePacket(const RequestInfo* inRequestInfo = NULL)
		: BaseResponsePacket(inRequestInfo)
		{}

		static void ProcessRequest(const LiveLinkPacket& inPacket)
		{
			RequestPacket* packet = inPacket.Cast<RequestPacket>();
			if (!packet)
			{
				SEXY_WARN("RtLiveLink::GetRtObjectState::ResponsePacket::ProcessPacket: Unexpected request packet type");
				return;
			}
			if (!packet->mRequestInfo.mRtonRequestInfo)
			{
				SEXY_WARN("RtLiveLink::GetRtObjectState::ResponsePacket::ProcessPacket: Missing RTON request info");
				return;
			}
			
			ResponsePacket(&packet->mRequestInfo).Send();
		} 

	protected:

		virtual void WriteRtonPayload(RtSerialBuffer& inSerialBuffer) override
		{
			DBG_ASSERTE((mRequestInfo != NULL) && "RtLiveLink::GetRtObjectState::ResponsePacket::WriteRtonPayload: Null request info");

			RtId id;
			RtSerialRtonReader* reader = mRequestInfo->mRtonRequestInfo;
			std::string subPath;
			if (reader->BeginDocumentObject())
			{
				id = reader->ReadRtId("id");
                id = RtDb::GetDb()->ResolveNamedId(id);
                
				subPath = reader->ReadString("subpath");
				reader->EndDocumentObject();
			}

			RtObjectSubPathValueSync rtObjSubPathSync(id, subPath);
			if (!rtObjSubPathSync.IsValid())
			{
				// $$$$ (avy) should add a method to RtObjectSubpathValueSync for getting back specific error conditions (e.g. non existence of RtId, subpath does not exist, Non-leaf property found along subpath, etc...
				std::string idStr;
				id.ToString(idStr);
				SEXY_WARN("RtLiveLink::GetRtObjectState::ResponsePacket::WriteRtonPayload: Failed to get value/type of subpath %s on RtId %s", subPath.c_str(), idStr.c_str());
				WriteRtonError(inSerialBuffer, StrFormat("Failed to get value/type of subpath %s on RtId %s", subPath.c_str(), idStr.c_str()));
				return;
			}

			RtSerialRtonWriter writer(&inSerialBuffer);

			writer.BeginDocumentObject();
			{
				writer.WriteRtId("id", id);
				if (!subPath.empty())
					writer.WriteString("subpath", subPath);
				
				RtSerialRtonSync rtonSync(&writer);

				if (!rtObjSubPathSync.SyncWithRton(rtonSync, "objdata", "data_rtclass_name", "data_reflection_type"))
				{
					std::string idStr;
					id.ToString(idStr);
					SEXY_WARN("RtLiveLink::GetRtObjectState::ResponsePacket::WriteRtonPayload: Failed to serialize the value/type of subpath '%s' on RtId %s", subPath.c_str(), idStr.c_str());
					WriteRtonError(inSerialBuffer, 
						StrFormat("Failed to serialize the value/type of subpath '%s' on RtId %s", subPath.c_str(), idStr.c_str()),
						&writer);
				}

			}
			writer.EndDocumentObject();
		}
	};
}

/*
	GetBatchRtObjectState
*/
namespace GetBatchRtObjectState
{
	class RequestPacket
	: public BaseRequestPacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::GetBatchRtObjectState::RequestPacket, BaseRequestPacket, LiveLinkPacketMetaClass);
	};

	class ResponsePacket
	: public BaseResponsePacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::GetBatchRtObjectState::ResponsePacket, BaseResponsePacket, LiveLinkPacketMetaClass);
		
		ResponsePacket(const RequestInfo* inRequestInfo = NULL)
		: BaseResponsePacket(inRequestInfo)
		{}

		static void ProcessRequest(const LiveLinkPacket& inPacket)
		{
			RequestPacket* packet = inPacket.Cast<RequestPacket>();
			if (!packet)
			{
				SEXY_WARN("RtLiveLink::GetBatchRtObjectState::ResponsePacket::ProcessPacket: Unexpected request packet type");
				return;
			}
			if (!packet->mRequestInfo.mRtonRequestInfo)
			{
				SEXY_WARN("RtLiveLink::GetBatchRtObjectState::ResponsePacket::ProcessPacket: Missing RTON request info");
				return;
			}
			
			ResponsePacket(&packet->mRequestInfo).Send();
		} 

	protected:
		virtual void WriteRtonPayload(RtSerialBuffer& inSerialBuffer) override
		{
			DBG_ASSERTE((mRequestInfo != NULL) && "RtLiveLink::GetBatchRtObjectState::ResponsePacket::WriteRtonPayload: Null request info");

			int32 tableIndex = -1;
			std::vector<std::string> subPaths;

			RtSerialRtonReader* reader = mRequestInfo->mRtonRequestInfo;
			if (!reader->BeginDocumentObject())
			{
				SEXY_WARN("RtLiveLink::GetBatchRtObjectState::ResponsePacket::WriteRtonPayload: bad rton document");
				WriteRtonError(inSerialBuffer, "bad rton document");
				return;
			}

			tableIndex = reader->ReadInt32("table_index");
			uint32 subPathCount = 0;
			if (!reader->BeginArray("subpaths", subPathCount))
			{
				SEXY_WARN("RtLiveLink::GetBatchRtObjectState::ResponsePacket::WriteRtonPayload: missing subpaths key");
				WriteRtonError(inSerialBuffer, "Expected subpaths key");
				return;
			}

			for (uint32 iSubPath=0; iSubPath<subPathCount; ++iSubPath)
			{
				subPaths.push_back(reader->ReadString(NULL));
			}
			reader->EndArray();

			reader->EndDocumentObject();
		
			if (tableIndex < 0)
			{
				SEXY_WARN("RtLiveLink::GetBatchRtObjectState::ResponsePacket::WriteRtonPayload: Missing table index");
				WriteRtonError(inSerialBuffer, "Expected positive table_index");
				return;
			}

			RtDbTable* table = RtDb::GetDb()->GetTable(tableIndex);
			if (table == NULL)
			{
				SEXY_WARN("RtLiveLink::GetBatchRtObjectState::ResponsePacket::WriteRtonPayload: Invalid table index %d", (int)tableIndex);
				WriteRtonError(inSerialBuffer, StrFormat("Invalid table index %d", tableIndex));
				return;
			}


			RtSerialRtonWriter writer(&inSerialBuffer);
			writer.BeginDocumentObject();
			{
#ifdef SUPPORT_REFLECTION
				writer.WriteInt32("table_index", tableIndex);
				int objCount = table->GetRtIdCount();
				writer.BeginArray("objects", objCount, RtSerialRtonTag::RtId);
				{
					int i = 0;
					for (RtDbTable::Iterator idIter(table, table->GetSharedIteratorStorage()); idIter; ++idIter, ++i)
					{
						if (i >= objCount)
						{
							SEXY_ERROR("RtLiveLink::GetBatchRtObjectState::ResponsePacket::WriteRtonPayload: mUsedSlotCount did not match actual number of objects in the table");
							// $ Don't generate an error in the RTON, continue on.
							break;
						}

						RtId id = *idIter;
						RtObject* obj = RtDb::GetDb()->GetObjectForId(id);
						if (obj == NULL)
						{
                            // There's a null object at this rtid, so just write an empty object
                            writer.BeginObject(NULL);
                            writer.EndObject();
							continue;
						}
                        else 
                        {
                            serializeRtObjectSubPathValues(writer, id, *obj, subPaths);
                        }
					}

					if (i != objCount)
					{
						SEXY_ERROR("RtLiveLink::GetBatchRtObjectState::ResponsePacket::WriteRtonPayload: mUsedSlotCount did not match actual number of objects in the table");
						// $ Don't generate an error in the RTON, continue on.
					}
				}
				writer.EndArray();
#else
				SEXY_WARN("RtLiveLink::GetBatchRtObjectState::ResponsePacket::WriteRtonPayload: Subpath \"%s\" requires reflection, but reflection is not supported", subPath.c_str());
				WriteRtonError(inSerialBuffer, StrFormat("Serialization must be supported to use GetBatchObjectState packet.", &writer));
#endif // SUPPORT_REFLECTION
			}
			writer.EndDocumentObject();				
		}


#ifdef SUPPORT_REFLECTION
		void serializeRtObjectSubPathValues(RtSerialRtonWriter& inWriter, const RtId& inRtId, RtObject& inRtObj, std::vector<std::string> const& inSubPaths)
		{
			RtClass* rootObjClass = inRtObj.GetClass();
			Reflection::RType* rootInstanceDataType = rootObjClass->GetBoundReflectionClass(); // may be null

			inWriter.BeginObject(NULL);
			{
				inWriter.WriteRtId("id", inRtId);

				if (rootObjClass)
				{
					inWriter.WriteString("data_rtclass_name", rootObjClass->GetName());
				}

				if (rootInstanceDataType)
				{
					inWriter.WriteRtId("data_reflection_type", rootInstanceDataType->GetRtId());
				}

				inWriter.BeginObject("subpath_values");
				{
					if (rootInstanceDataType == NULL)
					{
						SEXY_WARN("RtLiveLink::GetBatchRtObjectState::ResponsePacket::WriteRtonPayload: requires reflection, but class %s does not have reflection data", rootObjClass->GetName());
					}
					else
					{
						for (std::vector<std::string>::const_iterator subPathIter = inSubPaths.begin(); subPathIter != inSubPaths.end(); ++subPathIter)
						{
							const std::string& subPath = *subPathIter;

							RtObjectSubPathValueSync rtObjSubPathSync(inRtId, subPath);
							if (!rtObjSubPathSync.IsValid())
							{
								// subPath is not navigable on object of class objClass, that's fine not all subpaths must exist for
								// all objects in this table.
								continue;
							}
			
							inWriter.BeginObject(subPath);
							{							
								RtSerialRtonSync rtonSync(&inWriter);

								if (!rtObjSubPathSync.SyncWithRton(rtonSync, "*", "data_rtclass_name", "data_reflection_type"))
								{									
									std::string idStr;
									inRtId.ToString(idStr);
									SEXY_WARN("RtLiveLink::GetBatchRtObjectState::ResponsePacket::WriteRtonPayload: serialization failed for subpath %s on RtObject with id %s and RClass %s", subPath.c_str(), idStr.c_str(), rootObjClass->GetName());
									WriteRtonError(*inWriter.GetBuffer(), StrFormat("Object id %s of class %s serialization failed for subpath %s", idStr.c_str(), rootObjClass->GetName(), subPath.c_str()), &inWriter);
								}
							}
							inWriter.EndObject();
						}
					}
				}
				inWriter.EndObject(); // end of "subpath_values" object
			}
			inWriter.EndObject();
		}
#endif // SUPPORT_REFLECTION

	};
}


/*
	SetRtObjectState
*/
namespace SetRtObjectState
{
	class RequestPacket
	: public BaseRequestPacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::SetRtObjectState::RequestPacket, BaseRequestPacket, LiveLinkPacketMetaClass);
	};

	class ResponsePacket
	: public BaseResponsePacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::SetRtObjectState::ResponsePacket, BaseResponsePacket, LiveLinkPacketMetaClass);
		
		ResponsePacket(const RequestInfo* inRequestInfo = NULL)
		: BaseResponsePacket(inRequestInfo)
		{}

		static void ProcessRequest(const LiveLinkPacket& inPacket)
		{
			RequestPacket* packet = inPacket.Cast<RequestPacket>();
			if (!packet)
			{
				SEXY_WARN("RtLiveLink::SetRtObjectState::ResponsePacket::ProcessPacket: Unexpected request packet type");
				return;
			}
			if (!packet->mRequestInfo.mRtonRequestInfo)
			{
				SEXY_WARN("RtLiveLink::SetRtObjectState::ResponsePacket::ProcessPacket: Missing RTON request info");
				return;
			}
			
			ResponsePacket(&packet->mRequestInfo).Send();
		} 

	protected:
		virtual void WriteRtonPayload(RtSerialBuffer& inSerialBuffer) override
		{
			DBG_ASSERTE((mRequestInfo != NULL) && "RtLiveLink::SetRtObjectState::ResponsePacket::WriteRtonPayload: Null request info");

			RtId id;
			RtSerialRtonReader* reader = mRequestInfo->mRtonRequestInfo;
			if (!reader->BeginDocumentObject())
			{
				SEXY_WARN("RtLiveLink::SetRtObjectState::ResponsePacket::WriteRtonPayload: Expected valid RTON document");
				WriteRtonError(inSerialBuffer, "Expected valid RTON document");
				return;
			}
			
			id = reader->ReadRtId("id");
            id = RtDb::GetDb()->ResolveNamedId(id);
            
			std::string subPath = reader->ReadString("subpath");

			RtObjectSubPathValueSync rtObjSubPathSync(id, subPath);
			if (!rtObjSubPathSync.IsValid())
			{
				reader->EndDocumentObject();
				std::string idStr;
				id.ToString(idStr);
				SEXY_WARN("RtLiveLink::SetRtObjectState::ResponsePacket::WriteRtonPayload: Failed to get value/type of subpath %s on RtId %s", subPath.c_str(), idStr.c_str());
				WriteRtonError(inSerialBuffer, StrFormat("Failed to get value/type of subpath %s on RtId %s", subPath.c_str(), idStr.c_str()));
				return;
			}
	
			RtSerialRtonSync rtonSync(reader);

			if (!rtObjSubPathSync.SyncWithRton(rtonSync, "objdata"))
			{
				std::string idStr;
				id.ToString(idStr);
				SEXY_WARN("RtLiveLink::SetRtObjectState::ResponsePacket::WriteRtonPayload: Failed to serialize the value/type of subpath '%s' on RtId %s", subPath.c_str(), idStr.c_str());
				WriteRtonError(inSerialBuffer, StrFormat("Failed to serialize the value/type of subpath '%s' on RtId %s", subPath.c_str(), idStr.c_str()));
				return;
			}

			reader->EndDocumentObject();
		
			RtSerialRtonWriter writer(&inSerialBuffer);
			writer.BeginDocumentObject();
			{
				writer.WriteRtId("id", id);
			}
			writer.EndDocumentObject();
		}
	};
}


/*
 InsertArrayElement
 */
namespace InsertArrayElement
{
    class RequestPacket
    : public BaseRequestPacket
    {
    public:
        RT_CLASS_DEFINE(RtLiveLink::InsertArrayElement::RequestPacket, BaseRequestPacket, LiveLinkPacketMetaClass);
    };
    
    class ResponsePacket
    : public BaseResponsePacket
    {
    public:
        RT_CLASS_DEFINE(RtLiveLink::InsertArrayElement::ResponsePacket, BaseResponsePacket, LiveLinkPacketMetaClass);
        
        ResponsePacket(const RequestInfo* inRequestInfo = NULL)
        : BaseResponsePacket(inRequestInfo)
        {}
        
        static void ProcessRequest(const LiveLinkPacket& inPacket)
        {
            RequestPacket* packet = inPacket.Cast<RequestPacket>();
            if (!packet)
            {
                SEXY_WARN("RtLiveLink::InsertArrayElement::ResponsePacket::ProcessPacket: Unexpected request packet type");
                return;
            }
            if (!packet->mRequestInfo.mRtonRequestInfo)
            {
                SEXY_WARN("RtLiveLink::InsertArrayElement::ResponsePacket::ProcessPacket: Missing RTON request info");
                return;
            }
            
            ResponsePacket(&packet->mRequestInfo).Send();
        } 
        
    protected:
        virtual void WriteRtonPayload(RtSerialBuffer& inSerialBuffer) override
        {
            DBG_ASSERTE((mRequestInfo != NULL) && "RtLiveLink::InsertArrayElement::ResponsePacket::WriteRtonPayload: Null request info");
            
            RtId id;
            RtSerialRtonReader* reader = mRequestInfo->mRtonRequestInfo;
            if (!reader->BeginDocumentObject())
            {
                SEXY_WARN("RtLiveLink::InsertArrayElement::ResponsePacket::WriteRtonPayload: Expected valid RTON document");
                WriteRtonError(inSerialBuffer, "Expected valid RTON document");
                return;
            }
            
            id = reader->ReadRtId("id");
            std::string arraySubPath = reader->ReadString("array_subpath");
            int32 insertAtIndex = reader->ReadInt32("insert_at_index");
            
            RtObjectSubPathValueSync rtObjSubPathSync(id, arraySubPath);
            if (!rtObjSubPathSync.IsValid())
            {
                reader->EndDocumentObject();
                std::string idStr;
                id.ToString(idStr);
                SEXY_WARN("RtLiveLink::InsertArrayElement::ResponsePacket::WriteRtonPayload: Failed to get value/type of subpath '%s' on RtId %s", arraySubPath.c_str(), idStr.c_str());
                WriteRtonError(inSerialBuffer, StrFormat("Failed to get value/type of subpath '%s' on RtId %s", arraySubPath.c_str(), idStr.c_str()));
                return;
            }
            
            int32 actualInsertAtIndex = -1; // will contain the index where the element was actually inserted (will not be < 0, once set)
            
            // $ scope
            { 
                RtSerialRtonSync rtonSyncReader(reader);
                
                if (!rtObjSubPathSync.InsertArrayElementWithRton(rtonSyncReader, "element_data", insertAtIndex, actualInsertAtIndex))
                {
                    std::string idStr;
                    id.ToString(idStr);
                    SEXY_WARN("RtLiveLink::InsertArrayElement::ResponsePacket::WriteRtonPayload: Failed to insert into array '%s' at index %d on RtId %s", arraySubPath.c_str(), (int)insertAtIndex, idStr.c_str());
                    WriteRtonError(inSerialBuffer, StrFormat("Failed to insert into array '%s' at index %d on RtId %s", arraySubPath.c_str(), insertAtIndex, idStr.c_str()));
                    return;
                }
            }
            
            reader->EndDocumentObject();
            
            
            RtSerialRtonWriter writer(&inSerialBuffer);
            
            writer.BeginDocumentObject();
            {
                RtSerialRtonSync rtonSyncWriter(&writer);
                
                writer.WriteInt32VarS("index", actualInsertAtIndex);
                
                if (rtObjSubPathSync.SyncArrayElementWithRton(rtonSyncWriter, "element_data", insertAtIndex))
                {
                    writer.WriteString("status", "success");
                }
                else
                {
                    SEXY_WARN("RtLiveLink::InsertArrayElement::ResponsePacket::WriteRtonPayload: Failed to serialize the value of the new array element");
                    WriteRtonError(inSerialBuffer, StrFormat("Failed to serialize the value of the new array element"), &writer);
                }
            }
            writer.EndDocumentObject();
        }
    };
}


/*
 DeleteArrayElement
 */
namespace DeleteArrayElement
{
    class RequestPacket
    : public BaseRequestPacket
    {
    public:
        RT_CLASS_DEFINE(RtLiveLink::DeleteArrayElement::RequestPacket, BaseRequestPacket, LiveLinkPacketMetaClass);
    };
    
    class ResponsePacket
    : public BaseResponsePacket
    {
    public:
        RT_CLASS_DEFINE(RtLiveLink::DeleteArrayElement::ResponsePacket, BaseResponsePacket, LiveLinkPacketMetaClass);
        
        ResponsePacket(const RequestInfo* inRequestInfo = NULL)
        : BaseResponsePacket(inRequestInfo)
        {}
        
        static void ProcessRequest(const LiveLinkPacket& inPacket)
        {
            RequestPacket* packet = inPacket.Cast<RequestPacket>();
            if (!packet)
            {
                SEXY_WARN("RtLiveLink::DeleteArrayElement::ResponsePacket::ProcessPacket: Unexpected request packet type");
                return;
            }
            if (!packet->mRequestInfo.mRtonRequestInfo)
            {
                SEXY_WARN("RtLiveLink::DeleteArrayElement::ResponsePacket::ProcessPacket: Missing RTON request info");
                return;
            }
            
            ResponsePacket(&packet->mRequestInfo).Send();
        } 
        
    protected:
        virtual void WriteRtonPayload(RtSerialBuffer& inSerialBuffer) override
        {
            DBG_ASSERTE((mRequestInfo != NULL) && "RtLiveLink::DeleteArrayElement::ResponsePacket::WriteRtonPayload: Null request info");
            
            RtId id;
            RtSerialRtonReader* reader = mRequestInfo->mRtonRequestInfo;
            if (!reader->BeginDocumentObject())
            {
                SEXY_WARN("RtLiveLink::DeleteArrayElement::ResponsePacket::WriteRtonPayload: Expected valid RTON document");
                WriteRtonError(inSerialBuffer, "Expected valid RTON document");
                return;
            }
            
            id = reader->ReadRtId("id");
            std::string arraySubPath = reader->ReadString("array_subpath");
            int32 deleteIndex = reader->ReadInt32("delete_index");
            
            RtObjectSubPathValueSync rtObjSubPathSync(id, arraySubPath);
            if (!rtObjSubPathSync.IsValid())
            {
                reader->EndDocumentObject();
                std::string idStr;
                id.ToString(idStr);
                SEXY_WARN("RtLiveLink::DeleteArrayElement::ResponsePacket::WriteRtonPayload: Failed to get value/type of subpath '%s' on RtId %s", arraySubPath.c_str(), idStr.c_str());
                WriteRtonError(inSerialBuffer, StrFormat("Failed to get value/type of subpath '%s' on RtId %s", arraySubPath.c_str(), idStr.c_str()));
                return;
            }
            
            if (!rtObjSubPathSync.DeleteArrayElement(deleteIndex))
            {
                std::string idStr;
                id.ToString(idStr);
                SEXY_WARN("RtLiveLink::DeleteArrayElement::ResponsePacket::WriteRtonPayload: Failed to delete element at index %d from array '%s' on RtId %s", (int)deleteIndex, arraySubPath.c_str(), idStr.c_str());
                WriteRtonError(inSerialBuffer, StrFormat("Failed to delete element at index %d from array '%s' on RtId %s", deleteIndex, arraySubPath.c_str(), idStr.c_str()));
                return;
            }
            
            reader->EndDocumentObject();
            
            RtSerialRtonWriter writer(&inSerialBuffer);
            writer.BeginDocumentObject();
            {
                writer.WriteString("status", "success");
            }
            writer.EndDocumentObject();
        }
    };
}
    

    
/*
	NewRtObject
*/
namespace NewRtObject
{
	class RequestPacket
	: public BaseRequestPacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::NewRtObject::RequestPacket, BaseRequestPacket, LiveLinkPacketMetaClass);
	};

	class ResponsePacket
	: public BaseResponsePacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::NewRtObject::ResponsePacket, BaseResponsePacket, LiveLinkPacketMetaClass);
		
		ResponsePacket(const RequestInfo* inRequestInfo = NULL)
		: BaseResponsePacket(inRequestInfo)
		{}

		static void ProcessRequest(const LiveLinkPacket& inPacket)
		{
			RequestPacket* packet = inPacket.Cast<RequestPacket>();
			if (!packet)
			{
				SEXY_WARN("RtLiveLink::NewRtObject::ResponsePacket::ProcessPacket: Unexpected request packet type");
				return;
			}
			if (!packet->mRequestInfo.mRtonRequestInfo)
			{
				SEXY_WARN("RtLiveLink::NewRtObject::ResponsePacket::ProcessPacket: Missing RTON request info");
				return;
			}
			
			ResponsePacket(&packet->mRequestInfo).Send();
		} 

	protected:
		virtual void WriteRtonPayload(RtSerialBuffer& inSerialBuffer) override
		{
			DBG_ASSERTE((mRequestInfo != NULL) && "RtLiveLink::NewRtObject::ResponsePacket::WriteRtonPayload: Null request info");

			RtSerialRtonReader* reader = mRequestInfo->mRtonRequestInfo;
			if (!reader->BeginDocumentObject())
			{
				SEXY_WARN("RtLiveLink::NewRtObject::ResponsePacket::WriteRtonPayload: Expected valid RTON document");
				WriteRtonError(inSerialBuffer, "Expected valid RTON document");
				return;
			}
			
			int32 tableIndex = reader->ReadInt32("table_index");
			RtDbTable* table = RtDb::GetDb()->GetTable(tableIndex);
			if (table == NULL)
			{
				reader->EndDocumentObject();
				SEXY_WARN("RtLiveLink::NewRtObject::ResponsePacket::WriteRtonPayload: Could not locate table by name");
				WriteRtonError(inSerialBuffer, StrFormat("Unknown table index: %d", tableIndex));
				return;
			}

			// see if an optional uid has been give to assign to the new rtobject
			std::string optionalUidStr = reader->ReadString("uid", "");
			RtId::Uid uidToCreateWith; // will be null uid if no uid was in the packet, which will cause a RtId to be generated.
			if (optionalUidStr != "")
			{
				uidToCreateWith = RtId::Uid::StaticParse(optionalUidStr);
				if (!uidToCreateWith)
				{
					SEXY_WARN("RtLiveLink::NewRtObject::ResponsePacket::WriteRtonPayload: got invalid uid string.");
					WriteRtonError(inSerialBuffer, "invalid uid string: '"+optionalUidStr+"'");
					return;
				}
			}

			std::string rtClassName = reader->ReadString("rtclass_name");
			RtClass* rtClass = RtClass::StaticGetClassNamed(rtClassName.c_str());
			if (rtClass == NULL)
			{
				reader->EndDocumentObject();
				SEXY_WARN("RtLiveLink::NewRtObject::ResponsePacket::WriteRtonPayload: Could not locate rtClass by name");
				std::string errorStr = std::string("Unknown rtClass name: ") + rtClassName;
				WriteRtonError(inSerialBuffer, errorStr);
				return;
			}

			if (rtClass->IsAbstract())
			{
				reader->EndDocumentObject();
				SEXY_WARN("RtLiveLink::NewRtObject::ResponsePacket::WriteRtonPayload: Cannot instantiate an abstract rtClass.");
				std::string errorStr = std::string("Cannot instantiate abstract rtClass: ") + rtClassName;
				WriteRtonError(inSerialBuffer, errorStr);
				return;
			}

			RtObject* newRtObject = rtClass->New();
			if (newRtObject == NULL)
			{
				reader->EndDocumentObject();
				SEXY_WARN("RtLiveLink::NewRtObject::ResponsePacket::WriteRtonPayload: Failed to instantiate rtClass.");
				std::string errorStr = "Failed to instantiate rtClass:" + rtClassName;
				WriteRtonError(inSerialBuffer, errorStr);
				return;
			}
            
            RtId id = table->AllocId(newRtObject, RtDbTable::ODM_Auto, true, 
									 uidToCreateWith ? &uidToCreateWith : NULL);
            
            RtObjectSubPathValueSync rtObjSubPathSync(id, ""); // $ use an empty subpath, we're serializing a whole object
            
            RtSerialRtonSync rtonSync(reader);
            
            if (!rtObjSubPathSync.SyncWithRton(rtonSync, "objdata"))
            {
                std::string idStr;
                id.ToString(idStr);
                SEXY_WARN("RtLiveLink::NewRtObject::ResponsePacket::WriteRtonPayload: Failed to serialize the value/type on RtId %s", idStr.c_str());
                WriteRtonError(inSerialBuffer, StrFormat("Failed to serialize the value/type on RtId %s", idStr.c_str()));
                return;
            }
            
			reader->EndDocumentObject();

			RtSerialRtonWriter writer(&inSerialBuffer);
			writer.BeginDocumentObject();
			{
				writer.WriteRtId("id", id);
			}
			writer.EndDocumentObject();
		}
	};
}


/*
	DeleteRtId
*/
namespace DeleteRtId
{
	class RequestPacket
	: public BaseRequestPacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::DeleteRtId::RequestPacket, BaseRequestPacket, LiveLinkPacketMetaClass);
	};

	class ResponsePacket
	: public BaseResponsePacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::DeleteRtId::ResponsePacket, BaseResponsePacket, LiveLinkPacketMetaClass);
		
		ResponsePacket(const RequestInfo* inRequestInfo = NULL)
		: BaseResponsePacket(inRequestInfo)
		{}

		static void ProcessRequest(const LiveLinkPacket& inPacket)
		{
			RequestPacket* packet = inPacket.Cast<RequestPacket>();
			if (!packet)
			{
				SEXY_WARN("RtLiveLink::DeleteRtId::ResponsePacket::ProcessPacket: Unexpected request packet type");
				return;
			}
			if (!packet->mRequestInfo.mRtonRequestInfo)
			{
				SEXY_WARN("RtLiveLink::DeleteRtId::ResponsePacket::ProcessPacket: Missing RTON request info");
				return;
			}
			
			ResponsePacket(&packet->mRequestInfo).Send();
		} 

	protected:
		virtual void WriteRtonPayload(RtSerialBuffer& inSerialBuffer) override
		{
			DBG_ASSERTE((mRequestInfo != NULL) && "RtLiveLink::DeleteRtId::ResponsePacket::WriteRtonPayload: Null request info");

			RtSerialRtonReader* reader = mRequestInfo->mRtonRequestInfo;
			if (!reader->BeginDocumentObject())
			{
				SEXY_WARN("RtLiveLink::DeleteRtId::ResponsePacket::WriteRtonPayload: Expected valid RTON document");
				WriteRtonError(inSerialBuffer, "Expected valid RTON document");
				return;
			}

			RtId rtIdToDelete = reader->ReadRtId("id");
            rtIdToDelete = RtDb::GetDb()->ResolveNamedId(rtIdToDelete);

			reader->EndDocumentObject();

			
			RtDbTable* table = RtDb::GetDb()->GetTable(rtIdToDelete.GetTableIndex());
			if (table == NULL)
			{
				WriteRtonError(inSerialBuffer, "Cannot delete. Could not resolve RtId to RtDbTable. Bad RtId.");
				return;
			}

			if (table->GetObjectDeletionMode(rtIdToDelete) == RtDbTable::ODM_Never)
			{
				WriteRtonError(inSerialBuffer, "Cannot delete. RtId ObjectDeletionMode is 'Never' (possible bad RtId).");
				return;
			}

			if (!table->GetObjectIsStandalone(rtIdToDelete))
			{
				WriteRtonError(inSerialBuffer, "Cannot delete. RtId is not Standalone.");
				return;
			}

			if (RtDb::GetDb()->GetRefCountForId(rtIdToDelete) > 1)
			{
				WriteRtonError(inSerialBuffer, "Cannot delete. RtId still referenced. Ref count is greater than 1.");
				return;
			}

			// $$$ (avy) would prefer to only write the response after the call the ReleaseId() but right now
			// released rtids cannot be serializated so we write the response before we actually delete the rtid.
			RtSerialRtonWriter writer(&inSerialBuffer);
			writer.BeginDocumentObject();
			{
				writer.WriteRtId("id", rtIdToDelete);
			}
			writer.EndDocumentObject();

			if (!RtDb::GetDb()->ReleaseId(rtIdToDelete))
			{
				// $ Shouldn't get here given all the above checks.
				WriteRtonError(inSerialBuffer, "Cannot delete. No such RtId.");
				return;
			}
		}
	};
}


/*
	AddAlias
*/
namespace AddAlias
{
	class RequestPacket
	: public BaseRequestPacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::AddAlias::RequestPacket, BaseRequestPacket, LiveLinkPacketMetaClass);
	};

	class ResponsePacket
	: public BaseResponsePacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::AddAlias::ResponsePacket, BaseResponsePacket, LiveLinkPacketMetaClass);
		
		ResponsePacket(const RequestInfo* inRequestInfo = NULL)
		: BaseResponsePacket(inRequestInfo)
		{}

		static void ProcessRequest(const LiveLinkPacket& inPacket)
		{
			RequestPacket* packet = inPacket.Cast<RequestPacket>();
			if (!packet)
			{
				SEXY_WARN("RtLiveLink::AddAlias::ResponsePacket::ProcessPacket: Unexpected request packet type");
				return;
			}
			if (!packet->mRequestInfo.mRtonRequestInfo)
			{
				SEXY_WARN("RtLiveLink::AddAlias::ResponsePacket::ProcessPacket: Missing RTON request info");
				return;
			}
			
			ResponsePacket(&packet->mRequestInfo).Send();
		} 

	protected:
		virtual void WriteRtonPayload(RtSerialBuffer& inSerialBuffer) override
		{
			DBG_ASSERTE((mRequestInfo != NULL) && "RtLiveLink::AddAlias::ResponsePacket::WriteRtonPayload: Null request info");

			RtSerialRtonReader* reader = mRequestInfo->mRtonRequestInfo;
			if (!reader->BeginDocumentObject())
			{
				SEXY_WARN("RtLiveLink::AddAlias::ResponsePacket::WriteRtonPayload: Expected valid RTON document");
				WriteRtonError(inSerialBuffer, "Expected valid RTON document");
				return;
			}

			std::wstring alias = StringToWString(reader->ReadString("alias"));
			RtId rtIdToAlias = reader->ReadRtId("id");
            rtIdToAlias = RtDb::GetDb()->ResolveNamedId(rtIdToAlias);
			std::string existingAliasPolicy = reader->ReadString("existing_alias_policy");

			reader->EndDocumentObject();

			if (!RtDb::GetDb()->IsIdValid(rtIdToAlias))
			{
				RtSerialRtonWriter writer(&inSerialBuffer);
				writer.BeginDocumentObject();
				{
					writer.WriteString("status", "error_no_such_object");
					WriteRtonError(inSerialBuffer, "No such object", &writer);
				}
				writer.EndDocumentObject();
				return;
			}
	
			RtDbTable* table = RtDb::GetDb()->GetTable(rtIdToAlias.GetTableIndex());
			if (existingAliasPolicy == "error_if_alias_exists")
			{
				RtId existingRtIdForAlias = table->GetIdForAlias(alias);
				if (existingRtIdForAlias)
				{
					RtSerialRtonWriter writer(&inSerialBuffer);
					writer.BeginDocumentObject();
					{
						writer.WriteString("status", "error_alias_exists");
						writer.WriteRtId("existing_aliased_id", existingRtIdForAlias);
						WriteRtonError(inSerialBuffer, "Alias already exists", &writer);
					}
					writer.EndDocumentObject();
					return;
				}
			}

			bool success = table->SetIdForAlias(alias, rtIdToAlias);
			if (!success)
			{
				WriteRtonError(inSerialBuffer, "Failed to add alias");
				return;
			}

			RtSerialRtonWriter writer(&inSerialBuffer);
			writer.BeginDocumentObject();
			{
				writer.WriteString("status", "success");
			}
			writer.EndDocumentObject();
		}
	};
}


/*
	RemoveAlias
*/
namespace RemoveAlias
{
	class RequestPacket
	: public BaseRequestPacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::RemoveAlias::RequestPacket, BaseRequestPacket, LiveLinkPacketMetaClass);
	};

	class ResponsePacket
	: public BaseResponsePacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::RemoveAlias::ResponsePacket, BaseResponsePacket, LiveLinkPacketMetaClass);
		
		ResponsePacket(const RequestInfo* inRequestInfo = NULL)
		: BaseResponsePacket(inRequestInfo)
		{}

		static void ProcessRequest(const LiveLinkPacket& inPacket)
		{
			RequestPacket* packet = inPacket.Cast<RequestPacket>();
			if (!packet)
			{
				SEXY_WARN("RtLiveLink::RemoveAlias::ResponsePacket::ProcessPacket: Unexpected request packet type");
				return;
			}
			if (!packet->mRequestInfo.mRtonRequestInfo)
			{
				SEXY_WARN("RtLiveLink::RemoveAlias::ResponsePacket::ProcessPacket: Missing RTON request info");
				return;
			}
			
			ResponsePacket(&packet->mRequestInfo).Send();
		} 

	protected:
		virtual void WriteRtonPayload(RtSerialBuffer& inSerialBuffer) override
		{
			DBG_ASSERTE((mRequestInfo != NULL) && "RtLiveLink::RemoveAlias::ResponsePacket::WriteRtonPayload: Null request info");

			RtSerialRtonReader* reader = mRequestInfo->mRtonRequestInfo;
			if (!reader->BeginDocumentObject())
			{
				SEXY_WARN("RtLiveLink::RemoveAlias::ResponsePacket::WriteRtonPayload: Expected valid RTON document");
				WriteRtonError(inSerialBuffer, "Expected valid RTON document");
				return;
			}

			std::wstring alias = StringToWString(reader->ReadString("alias"));
			int32 tableIndex = reader->ReadInt32("table_index");

			reader->EndDocumentObject();
            
			RtDbTable* table = RtDb::GetDb()->GetTable(tableIndex);
			if (table == NULL)
			{
				RtSerialRtonWriter writer(&inSerialBuffer);
				writer.BeginDocumentObject();
				{
					writer.WriteString("status", "error_no_such_table");
					WriteRtonError(inSerialBuffer, "error, no such table", &writer);
				}
				writer.EndDocumentObject();
				return;
			}
            
			RtId existingAliasedRtId = table->GetIdForAlias(alias);
			if (!existingAliasedRtId)
			{
				RtSerialRtonWriter writer(&inSerialBuffer);
				writer.BeginDocumentObject();
				{
					writer.WriteString("status", "error_no_such_alias");
					WriteRtonError(inSerialBuffer, "no such alias", &writer);
				}
				writer.EndDocumentObject();
				return;
			}
            
			bool success = table->SetIdForAlias(alias, RtId()); // clear the alias
			if (!success)
			{
				WriteRtonError(inSerialBuffer, "Failed to remove alias");
				return;
			}

			RtSerialRtonWriter writer(&inSerialBuffer);
			writer.BeginDocumentObject();
			{
				writer.WriteString("status", "success");
			}
			writer.EndDocumentObject();
		}
	};
}

/*
	GetTableAliases
*/
namespace GetTableAliases
{
	class RequestPacket
	: public BaseRequestPacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::GetTableAliases::RequestPacket, BaseRequestPacket, LiveLinkPacketMetaClass);
	};

	class ResponsePacket
	: public BaseResponsePacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::GetTableAliases::ResponsePacket, BaseResponsePacket, LiveLinkPacketMetaClass);
		
		ResponsePacket(const RequestInfo* inRequestInfo = NULL)
		: BaseResponsePacket(inRequestInfo)
		{}

		static void ProcessRequest(const LiveLinkPacket& inPacket)
		{
			RequestPacket* packet = inPacket.Cast<RequestPacket>();
			if (!packet)
			{
				SEXY_WARN("RtLiveLink::GetTableAliases::ResponsePacket::ProcessPacket: Unexpected request packet type");
				return;
			}
			if (!packet->mRequestInfo.mRtonRequestInfo)
			{
				SEXY_WARN("RtLiveLink::GetTableAliases::ResponsePacket::ProcessPacket: Missing RTON request info");
				return;
			}
			
			ResponsePacket(&packet->mRequestInfo).Send();
		} 

	protected:
		virtual void WriteRtonPayload(RtSerialBuffer& inSerialBuffer) override
		{
			DBG_ASSERTE((mRequestInfo != NULL) && "RtLiveLink::GetTableAliases::ResponsePacket::WriteRtonPayload: Null request info");

			RtSerialRtonReader* reader = mRequestInfo->mRtonRequestInfo;
			if (!reader->BeginDocumentObject())
			{
				SEXY_WARN("RtLiveLink::GetTableAliases::ResponsePacket::WriteRtonPayload: Expected valid RTON document");
				WriteRtonError(inSerialBuffer, "Expected valid RTON document");
				return;
			}

			int32 tableIndex = reader->ReadInt32("table_index");

			reader->EndDocumentObject();
	
			RtDbTable* table = RtDb::GetDb()->GetTable(tableIndex);
			if (table == NULL)
			{
				RtSerialRtonWriter writer(&inSerialBuffer);
				writer.BeginDocumentObject();
				{
					writer.WriteString("status", "error_no_such_table");
					WriteRtonError(inSerialBuffer, "no such table", &writer);
				}
				writer.EndDocumentObject();
				return;
			}

			RtSerialRtonWriter writer(&inSerialBuffer);
			writer.BeginDocumentObject();
			{
				table->SerializeAllAliasesToRton(writer, "aliases");
			}
			writer.EndDocumentObject();
		}
	};
}


/*
	GetRtObjectAliases
*/
namespace GetRtObjectAliases
{
	class RequestPacket
	: public BaseRequestPacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::GetRtObjectAliases::RequestPacket, BaseRequestPacket, LiveLinkPacketMetaClass);
	};

	class ResponsePacket
	: public BaseResponsePacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::GetRtObjectAliases::ResponsePacket, BaseResponsePacket, LiveLinkPacketMetaClass);
		
		ResponsePacket(const RequestInfo* inRequestInfo = NULL)
		: BaseResponsePacket(inRequestInfo)
		{}

		static void ProcessRequest(const LiveLinkPacket& inPacket)
		{
			RequestPacket* packet = inPacket.Cast<RequestPacket>();
			if (!packet)
			{
				SEXY_WARN("RtLiveLink::GetRtObjectAliases::ResponsePacket::ProcessPacket: Unexpected request packet type");
				return;
			}
			if (!packet->mRequestInfo.mRtonRequestInfo)
			{
				SEXY_WARN("RtLiveLink::GetRtObjectAliases::ResponsePacket::ProcessPacket: Missing RTON request info");
				return;
			}
			
			ResponsePacket(&packet->mRequestInfo).Send();
		} 

	protected:
		virtual void WriteRtonPayload(RtSerialBuffer& inSerialBuffer) override
		{
			DBG_ASSERTE((mRequestInfo != NULL) && "RtLiveLink::GetRtObjectAliases::ResponsePacket::WriteRtonPayload: Null request info");

			RtSerialRtonReader* reader = mRequestInfo->mRtonRequestInfo;
			if (!reader->BeginDocumentObject())
			{
				SEXY_WARN("RtLiveLink::GetRtObjectAliases::ResponsePacket::WriteRtonPayload: Expected valid RTON document");
				WriteRtonError(inSerialBuffer, "Expected valid RTON document");
				return;
			}

			RtId rtId = reader->ReadRtId("id");
            rtId = RtDb::GetDb()->ResolveNamedId(rtId);

			reader->EndDocumentObject();

			if (!RtDb::GetDb()->IsIdValid(rtId))
			{
				RtSerialRtonWriter writer(&inSerialBuffer);
				writer.BeginDocumentObject();
				{
					writer.WriteString("status", "error_no_such_object");
					WriteRtonError(inSerialBuffer, "No such object", &writer);
				}
				writer.EndDocumentObject();
				return;
			}
	
			RtDbTable* table = RtDb::GetDb()->GetTable(rtId.GetTableIndex());
			if (table == NULL) // shouldn't happen, since the IsIdValid check above should fail before this.
			{
				WriteRtonError(inSerialBuffer, "no such table");
				return;
			}

			RtSerialRtonWriter writer(&inSerialBuffer);
			writer.BeginDocumentObject();
			{
				if (!table->SerializeRtIdAliasesToRton(writer, rtId, "aliases"))
				{
					WriteRtonError(inSerialBuffer, "Unexepected error. Rtid was not in table. This should not be possible.", &writer);
				}
			}
			writer.EndDocumentObject();
		}
	};
}

/*
	ReflectionSerialCmdMethodInvoke
*/
namespace ReflectionSerialCmdMethodInvoke
{
	class RequestPacket
	: public BaseRequestPacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::ReflectionSerialCmdMethodInvoke::RequestPacket, BaseRequestPacket, LiveLinkPacketMetaClass);
	};

	class ResponsePacket
	: public BaseResponsePacket
	{
	public:
		RT_CLASS_DEFINE(RtLiveLink::ReflectionSerialCmdMethodInvoke::ResponsePacket, BaseResponsePacket, LiveLinkPacketMetaClass);
		
		ResponsePacket(const RequestInfo* inRequestInfo = NULL)
		: BaseResponsePacket(inRequestInfo)
		{}

		static void ProcessRequest(const LiveLinkPacket& inPacket)
		{
			RequestPacket* packet = inPacket.Cast<RequestPacket>();
			if (!packet)
			{
				SEXY_WARN("RtLiveLink::ReflectionSerialCmdMethodInvoke::ResponsePacket::ProcessPacket: Unexpected request packet type");
				return;
			}
			if (!packet->mRequestInfo.mRtonRequestInfo)
			{
				SEXY_WARN("RtLiveLink::ReflectionSerialCmdMethodInvoke::ResponsePacket::ProcessPacket: Missing RTON request info");
				return;
			}
			
			ResponsePacket(&packet->mRequestInfo).Send();
		} 

	protected:
		virtual void WriteRtonPayload(RtSerialBuffer& inSerialBuffer) override
		{
			DBG_ASSERTE((mRequestInfo != NULL) && "RtLiveLink::ReflectionSerialCmdMethodInvoke::ResponsePacket::WriteRtonPayload: Null request info");

			RtSerialRtonReader* reader = mRequestInfo->mRtonRequestInfo;
			RtSerialRtonWriter writer(&inSerialBuffer);

			if (!Reflection::RMethod::StaticInvokeSerialCommand(reader, &writer))
			{
				SEXY_WARN("RtLiveLink::ReflectionSerialCmdMethodInvoke::ResponsePacket::WriteRtonPayload: Method invoke failed");
				WriteRtonError(inSerialBuffer, "Method invoke failed");
				return;
			}
		}
	};
}

/*
 ReflectionInvoke
 */
namespace ReflectionInvoke
{
    class RequestPacket
    : public BaseRequestPacket
    {
    public:
        RT_CLASS_DEFINE(RtLiveLink::ReflectionInvoke::RequestPacket, BaseRequestPacket, LiveLinkPacketMetaClass);
    };
    
    class ResponsePacket
    : public BaseResponsePacket
    {
    public:
        RT_CLASS_DEFINE(RtLiveLink::ReflectionInvoke::ResponsePacket, BaseResponsePacket, LiveLinkPacketMetaClass);
        
        ResponsePacket(const RequestInfo* inRequestInfo = NULL)
        : BaseResponsePacket(inRequestInfo)
        {}
        
        static void ProcessRequest(const LiveLinkPacket& inPacket)
        {
            RequestPacket* packet = inPacket.Cast<RequestPacket>();
            if (!packet)
            {
                SEXY_WARN("RtLiveLink::ReflectionInvoke::ResponsePacket::ProcessPacket: Unexpected request packet type");
                return;
            }
            if (!packet->mRequestInfo.mRtonRequestInfo)
            {
                SEXY_WARN("RtLiveLink::ReflectionInvoke::ResponsePacket::ProcessPacket: Missing RTON request info");
                return;
            }
            
            ResponsePacket(&packet->mRequestInfo).Send();
        }
        
    protected:
        virtual void WriteRtonPayload(RtSerialBuffer& inSerialBuffer) override
        {
            DBG_ASSERTE((mRequestInfo != NULL) && "RtLiveLink::ReflectionInvoke::ResponsePacket::WriteRtonPayload: Null request info");
            
            RtSerialRtonReader* reader = mRequestInfo->mRtonRequestInfo;
            
            if (!reader->BeginDocumentObject())
			{
				SEXY_WARN("RtLiveLink::GetRtObjectAliases::ResponsePacket::WriteRtonPayload: Expected valid RTON document");
				WriteRtonError(inSerialBuffer, "Expected valid RTON document");
				return;
			}
            
            
            RtObject* thisObj = NULL;
            
            { // $ scope
                
                RtId thisId = reader->ReadRtId("this");
                if (thisId)
                {
                    // look up a pointer to "this"
                    
                    thisId = RtDb::GetDb()->ResolveNamedId(thisId);
                    thisObj = RtDb::GetDb()->GetObjectForId(thisId);
                }
            }
            
            std::string className = reader->ReadString("class_name");
            std::string methodName = reader->ReadString("method_name");

            Reflection::RClass* rClass = Reflection::CRefSymbolDb::GetManualReflection()->GetClasses()->GetNamed(className);
            Reflection::RMethod* rMethod = rClass->GetMethods(true)->GetNamed(methodName); 
            
            
            if (thisObj == NULL)
            {
                // No "this" was provider, so the method better be callable as a static method
                if (!rMethod->CanInvoke(false))
                {
                    // This method is not invocable as a static method (or some other reason?)
                    
                    SEXY_WARN("RtLiveLink::ReflectionInvoke::ResponsePacket::WriteRtonPayload: Method must be static but is not.");
                    WriteRtonError(inSerialBuffer, "Method invoke failed. Expected a static method, but found instance method instead.");
                    return;
                }
            }
            else
            {
                // verify that this instance method can be called (with will work even if the method is static)
                if (!rMethod->CanInvoke(true))
                {
                    SEXY_WARN("RtLiveLink::ReflectionInvoke::ResponsePacket::WriteRtonPayload: RMethod::CanInvoke() returned false.");
                    WriteRtonError(inSerialBuffer, "Method invoke failed. The method cannot be invoked.");
                    return;
                }
            }
            
            Reflection::RType* methodType = rMethod->GetType();
            if (methodType->GetTypeCategory() != Reflection::RType::TC_Function)
            {
                SEXY_ERROR("Expected RType returned from RMethod::GetType to be of category TC_Function. It was not.");
                WriteRtonError(inSerialBuffer, "Method invoke failed. Internal Error. Expected method RType to be an instance of RFunctionType, it was not.");
                return;
            }
            
            Reflection::RFunctionType *funcType = methodType->CastChecked<Reflection::RFunctionType>();
            
            // A vector of strings, when this method's scope exits, the vector will clean up
            // the strings for us
            std::vector<std::string> stringArgs;
            std::vector<std::wstring> wstringArgs;
            
            std::vector<RtInvokeVariant> argsVector;
            uint32 argCount;
            if (!reader->BeginArray("args", argCount))
            {
                SEXY_WARN("RtLiveLink::ReflectionInvoke::ResponsePacket::WriteRtonPayload: missing args key.");
				WriteRtonError(inSerialBuffer, "Method invoke failed. Missing args key.");
                return;
            }
            
            if (argCount != funcType->GetArgTypeCount())
            {
                SEXY_WARN("RtLiveLink::ReflectionInvoke::ResponsePacket::WriteRtonPayload: incoming arg count does not match the number of args required by the method signature.");
				WriteRtonError(inSerialBuffer, "Method invoke failed. Wrong number of arguments.");
                return;
            }
            
            for (uint32 i = 0; i < argCount; ++i)
            {
                Reflection::RType* requiredArgType = funcType->GetArgTypeIndexed(i);
                Reflection::RSimpleType* simpleType = requiredArgType->Cast<Reflection::RSimpleType>();
                
                if (simpleType != NULL)
                {
                    switch (simpleType->GetSimpleTypeCategory())
                    {
                        case Reflection::RSimpleType::STC_Bool:  // bool
                            argsVector.push_back(RtInvokeVariant(reader->ReadBool(NULL)));
                            break;
                        case Reflection::RSimpleType::STC_AChar: // char (8-bit ansi character)
                            argsVector.push_back(RtInvokeVariant((char)reader->ReadInt32(NULL)));
                            break;
                        case Reflection::RSimpleType::STC_WChar: // wchar_t (16-bit wide character)
                            argsVector.push_back(RtInvokeVariant((wchar_t)reader->ReadInt32(NULL)));
                            break;
                        case Reflection::RSimpleType::STC_SInt:  // signed byte/word/dword/qword (check size)
                            argsVector.push_back(RtInvokeVariant(reader->ReadInt32(NULL)));
                            break;
                        case Reflection::RSimpleType::STC_UInt:  // unsigned byte/word/dword/qword (check size)
                            argsVector.push_back(RtInvokeVariant(reader->ReadUInt32(NULL)));
                            break;
                        case Reflection::RSimpleType::STC_Float: // float/double (check size)
                            argsVector.push_back(RtInvokeVariant(reader->ReadFloat(NULL)));
                            break;
                            
                        case Reflection::RSimpleType::STC_Void:      // FALL-THROUGH
                        case Reflection::RSimpleType::STC_Ellipsis:  // FALL-THROUGH
                        case Reflection::RSimpleType::STC_HResult:   // FALL-THROUGH
                        case Reflection::RSimpleType::STC_None:      // FALL-THROUGH
                        default:
                            SEXY_WARN("RtLiveLink::ReflectionInvoke::ResponsePacket::WriteRtonPayload: required argument was an unsupported RSimpleType: Void, Ellipsis, HResult or None.");
                            WriteRtonError(inSerialBuffer, "Method invoke failed. required argument was an unsupported RSimpleType: Void, Ellipsis, HResult or None.");
                        return;
                    }
                }
                else
                {
                    Reflection::RReferenceType* refType = requiredArgType->Cast<Reflection::RReferenceType>();
                    if (refType == NULL || refType->GetReferenceTypeCategory() != Reflection::RReferenceType::RTC_Ampersand)
                    {
                        SEXY_WARN("RtLiveLink::ReflectionInvoke::ResponsePacket::WriteRtonPayload: argument required was not RSimpleType or a string& type (RReferenceType ->   RCustomType).");
                        WriteRtonError(inSerialBuffer, "Method invoke failed. Required argument was not a simple type or a string&.");
                        return;
                    }
                    
                    Reflection::RType* innerRefedType = refType->GetInnerType();
                    
                    // Check to see if this is a custom type and, if so, see if its a string type
                    
                    Reflection::RCustomType* customType = innerRefedType->Cast<Reflection::RCustomType>();
                    if (customType == NULL)
                    {
                        SEXY_WARN("RtLiveLink::ReflectionInvoke::ResponsePacket::WriteRtonPayload: argument required was not RSimpleType or a string type (RCustomType).");
                        WriteRtonError(inSerialBuffer, "Method invoke failed. Required argument was not a simple type or a string&.");
                        return;
                    }
                                        
                    Reflection::RCustomType::ECustomTypeCategory customTypeCat = customType->GetCustomTypeCategory();
                    if (customTypeCat == Reflection::RCustomType::CTC_StdString)
                    {
                        stringArgs.push_back(reader->ReadString(NULL));
                        argsVector.push_back(RtInvokeVariant(&stringArgs.back()));
                    }
                    else if (customTypeCat == Reflection::RCustomType::CTC_StdWString)
                    {
                        wstringArgs.push_back(reader->ReadWString(NULL));
                        argsVector.push_back(RtInvokeVariant(&wstringArgs.back()));
                    }
                }
            }
            
            reader->EndArray();
            reader->EndDocumentObject();
            
            const char* returnValueKey = "return_value";
            Reflection::RType* retType = funcType->GetReturnType();
            
            // is the return type a simple type or a string?
            if (retType == NULL || retType->GetTypeCategory() == Reflection::RType::TC_Simple)
            {
            
                RtInvokeVariant returnVariant;
                if (!rMethod->Invoke(&returnVariant, thisObj, argsVector))
                {
                    SEXY_WARN("RtLiveLink::ReflectionInvoke::ResponsePacket::WriteRtonPayload: RMethod::Invoke() failed.");
                    WriteRtonError(inSerialBuffer, "Method invoke failed. RMethod::Invoke() failed.");
                    return;
                }
                
                RtSerialRtonWriter writer(&inSerialBuffer);
                writer.BeginDocumentObject();
                {
                    // Only support simple return types right now
                    // $$$ Should also look for and handle custom types that are strings
                    
                    if (retType != NULL && retType->GetTypeCategory() == Reflection::RType::TC_Simple)
                    {
                        Reflection::RSimpleType *returnType = retType->CastChecked<Reflection::RSimpleType>();
                        if (returnType->GetSimpleTypeCategory() != Reflection::RSimpleType::STC_Void)
                        {
                            // Ok, there is a return value that this method returns, so write it into
                            // the rton.
                            switch (returnVariant.mType)
                            {
                                case RtInvokeVariant::VT_UInt32:
                                {
                                    // RtInvokeVariant treats bool values as uint32, so check to see if
                                    // the method return type is a bool and serialize it as such.
                                    if (returnType->GetSimpleTypeCategory() == Reflection::RSimpleType::STC_Bool)
                                    {
                                        writer.WriteBool(returnValueKey, returnVariant.mUInt32 != 0);
                                    }
                                    else
                                    {
                                        writer.WriteUInt32(returnValueKey, returnVariant.mUInt32);
                                    }
                                    break;
                                }
                                case RtInvokeVariant::VT_SInt32:
                                    writer.WriteInt32(returnValueKey, returnVariant.mSInt32); break;
                                case RtInvokeVariant::VT_Float:
                                    writer.WriteFloat(returnValueKey, returnVariant.mFloat); break;
                                case RtInvokeVariant::VT_UInt64:
                                    writer.WriteUInt64(returnValueKey, returnVariant.mUInt64); break;
                                case RtInvokeVariant::VT_SInt64:
                                    writer.WriteInt64(returnValueKey, returnVariant.mSInt64); break;
                                case RtInvokeVariant::VT_Double:
                                    writer.WriteDouble(returnValueKey, returnVariant.mDouble); break;
                                case RtInvokeVariant::VT_Ptr:
                                    break; // $$$ Generate a warning? We don't know how to serialize out general pointers.
                            }
                        }
                    }

                }
                writer.EndDocumentObject();
            }
            else if (retType->GetTypeCategory() == Reflection::RType::TC_Custom)
            {
                Reflection::RCustomType* custRetType = retType->CastChecked<Reflection::RCustomType>();
                if (custRetType->GetCustomTypeCategory() == Reflection::RCustomType::CTC_StdString)
                {
                    std::string strReturnValue;
                    if (!rMethod->InvokeWithTypedReturn(&strReturnValue, thisObj, argsVector))
                    {
                        SEXY_WARN("RtLiveLink::ReflectionInvoke::ResponsePacket::WriteRtonPayload: RMethod::InvokeWithTypedReturn() failed.");
                        WriteRtonError(inSerialBuffer, "Method invoke failed. RMethod::InvokeWithTypedReturn() failed.");
                        return;
                    }
                    
                    RtSerialRtonWriter writer(&inSerialBuffer);
                    writer.BeginDocumentObject();
                    writer.WriteString(returnValueKey, strReturnValue);
                    writer.EndDocumentObject();
                }
                else
                {
                    SEXY_WARN("RtLiveLink::ReflectionInvoke::ResponsePacket::WriteRtonPayload: Unsupported return type. Return type must be a simple type of a string or wstring.");
                    WriteRtonError(inSerialBuffer, "Method invoke failed. Unsupported return type. Return type must be a simple type of a string.");
                    return;
                }
            }
            
            
        }
    };
}


//----------------------------------------------------------------------------
// Event Packets
//
class BaseRtonEventPacket
: public LiveLinkPacket
{
public:
	RT_CLASS_DEFINE_ABSTRACT(RtLiveLink::BaseRtonEventPacket, LiveLinkPacket, LiveLinkPacketMetaClass)
	{}

protected:
	
	virtual void WriteRtonPayload(RtSerialBuffer& inBuffer)
	{
		RtSerialRtonWriter rton(&inBuffer);

		rton.BeginDocumentObject();
		{
			rton.BeginObject("event_data");
			WriteRtonEventData(rton);
			rton.EndObject();
		}
		rton.EndDocumentObject();
	}

	virtual void WriteRtonEventData(RtSerialRtonWriter& inRtonWriter) = 0;

	virtual bool SyncPayload(RtSerialBuffer& inSerialBuffer) override
	{
		SEXY_ASSERT(inSerialBuffer.IsWriting()); // Only support sending this packet at this time.

		// placeholder for rton byte size (filled in afterwards)
		uint32 rtonSizeOffset = inSerialBuffer.Tell();
		inSerialBuffer.WriteInt32Fixed(0);

		// write the rton payload
		uint32 startOffset = inSerialBuffer.Tell();
		WriteRtonPayload(inSerialBuffer);
		uint32 endOffset = inSerialBuffer.Tell();

		// patch up the rton size
		int32 rtonSize = endOffset - startOffset;
		inSerialBuffer.SeekStart(rtonSizeOffset);
		inSerialBuffer.WriteInt32Fixed(rtonSize);
		inSerialBuffer.SeekStart(endOffset);
		
		return true;
	}

};

/*
	OnRtTableCreatedEvent
*/

class OnRtTableCreatedEvent
	: public BaseRtonEventPacket
{
public:
	RT_CLASS_DEFINE(RtLiveLink::OnRtTableCreatedEvent, BaseRtonEventPacket, LiveLinkPacketMetaClass);

	OnRtTableCreatedEvent() {}

	OnRtTableCreatedEvent(int inTableId)
	{
		mTableId = inTableId;
	}
protected:
	virtual void WriteRtonEventData(RtSerialRtonWriter& inRtonWriter) override
	{
		RtDbTable* table = RtDb::GetDb()->GetTable(mTableId);
		
		if (table != NULL)
		{
			inRtonWriter.BeginArray("tables", 1);
			inRtonWriter.BeginObject(NULL);
				table->WriteTableRtonKeys(inRtonWriter);
			inRtonWriter.EndObject();
			inRtonWriter.EndArray();
		}
		else
		{
			// $ Really an ERROR but using SEXY_WARN since we're in a packet and SEXY_ERROR would 
			// send a reporting packet.
			SEXY_WARN("RtLiveLink::OnRtTableCreatedEvent::WriteRtonPayload: Invalid table index %d", mTableId);
			inRtonWriter.BeginArray("tables", 0);
			inRtonWriter.EndArray();
		}
	}
private:
	int mTableId;
};


/*
	OnTableLoadedEvent
*/

class OnTableLoadEvent
	: public BaseRtonEventPacket
{
public:
	RT_CLASS_DEFINE(RtLiveLink::OnTableLoadEvent, BaseRtonEventPacket, LiveLinkPacketMetaClass);

    enum LoadStatus
    {
        SEXY_ENUM_BEGIN(LoadStatus_),
        LoadStatus_Unloading = 0,
        LoadStatus_Unloaded,
        LoadStatus_Loading,
        LoadStatus_Loaded,
        SEXY_ENUM_END(LoadStatus_)
    };
    
	OnTableLoadEvent() {}

	OnTableLoadEvent(LoadStatus inLoadStatus, int inTableId, std::wstring inPackageName)
	{
        mLoadStatus     = inLoadStatus;
		mTableId        = inTableId;
		mPackageName    = inPackageName;
	}
    
    //
    // Static methods for firing different forms of this event.
    // The signatures of these methods matches the various
    // OnTableLoad/Unload* Rt Events, which makes these methods easy
    // to add to those events as delegates.
    //
    static void FireOnTableUnloadingEvent(const RtDbTable& inTable)
    {
        OnTableLoadEvent(LoadStatus_Unloading, inTable.GetTableIndex(),
                         L"").Send();
    }
    
    static void FireOnTableUnloadedEvent(const RtDbTable& inTable)
    {
        OnTableLoadEvent(LoadStatus_Unloaded, inTable.GetTableIndex(),
                         L"").Send();
    }
    
    static void FireOnTableLoadingEvent(const RtDbTable& inTable)
    {
        OnTableLoadEvent(LoadStatus_Loading, inTable.GetTableIndex(),
                         inTable.GetCurrentPackageName().GetString()).Send();
    }
    
    static void FireOnTableLoadedEvent(const RtDbTable& inTable)
    {
        OnTableLoadEvent(LoadStatus_Loaded, inTable.GetTableIndex(),
                         inTable.GetCurrentPackageName().GetString()).Send();
    }
    
protected:
	virtual void WriteRtonEventData(RtSerialRtonWriter& inRtonWriter) override
	{
        inRtonWriter.WriteInt32(       "load_status",   mLoadStatus);
		inRtonWriter.WriteInt32(       "table_index",   mTableId);
		inRtonWriter.WriteUTF8String(  "package_name",  mPackageName);
	}
private:
    LoadStatus      mLoadStatus;
	int             mTableId;
	std::wstring    mPackageName;
};


/*
	OnRtIdCreatedEvent
*/

class OnRtIdCreatedEvent
	: public BaseRtonEventPacket
{
public:
	RT_CLASS_DEFINE(RtLiveLink::OnRtIdCreatedEvent, BaseRtonEventPacket, LiveLinkPacketMetaClass);

	OnRtIdCreatedEvent() {}

	OnRtIdCreatedEvent(const RtId& inRtIdCreated)
	{
		mRtIdCreated = inRtIdCreated;
	}
protected:
	virtual void WriteRtonEventData(RtSerialRtonWriter& inRtonWriter) override
	{
		inRtonWriter.BeginArray("rtids", 1);
		inRtonWriter.WriteRtId(NULL, mRtIdCreated);
		inRtonWriter.EndArray();
	}
private:
	RtId mRtIdCreated;
};



/*
	OnRtIdDeletedEvent
*/

class OnRtIdDestroyedEvent
	: public BaseRtonEventPacket
{
public:
	RT_CLASS_DEFINE(RtLiveLink::OnRtIdDestroyedEvent, BaseRtonEventPacket, LiveLinkPacketMetaClass);

	OnRtIdDestroyedEvent() {}

	OnRtIdDestroyedEvent(const RtId& inRtIdDeleted)
	{
		mRtIdDestroyed = inRtIdDeleted;
	}
protected:
	virtual void WriteRtonEventData(RtSerialRtonWriter& inRtonWriter) override
	{
		inRtonWriter.BeginArray("rtids", 1);
		inRtonWriter.WriteRtId(NULL, mRtIdDestroyed);
		inRtonWriter.EndArray();
	}
private:
	RtId mRtIdDestroyed;
};

/*
	OnAliasAddedEvent
*/

class OnAliasAddedEvent
	: public BaseRtonEventPacket
{
public:
	RT_CLASS_DEFINE(RtLiveLink::OnAliasAddedEvent, BaseRtonEventPacket, LiveLinkPacketMetaClass);

	OnAliasAddedEvent() {}

	OnAliasAddedEvent(const std::string& inAlias, const RtId& inRtId)
	{
		mAlias = inAlias;
		mRtId = inRtId;
	}
protected:
	virtual void WriteRtonEventData(RtSerialRtonWriter& inRtonWriter) override
	{
		inRtonWriter.BeginArray("aliases", 1);
		{
			inRtonWriter.BeginObject(NULL);
			{
				inRtonWriter.WriteString("alias", mAlias, true);
				inRtonWriter.WriteRtId("id", mRtId);
			}
			inRtonWriter.EndObject();
		}
		inRtonWriter.EndArray();
	}
private:
	std::string mAlias;
	RtId mRtId;
};



/*
	OnAliasRemovedEvent
*/

class OnAliasRemovedEvent
	: public BaseRtonEventPacket
{
public:
	RT_CLASS_DEFINE(RtLiveLink::OnAliasRemovedEvent, BaseRtonEventPacket, LiveLinkPacketMetaClass);

	OnAliasRemovedEvent() {}

	OnAliasRemovedEvent(const std::string& inAlias, const RtId& inRtId)
	{
		mAlias = inAlias;
		mRtId = inRtId;
	}
protected:
	virtual void WriteRtonEventData(RtSerialRtonWriter& inRtonWriter) override
	{
		inRtonWriter.BeginArray("aliases", 1);
		{
			inRtonWriter.BeginObject(NULL);
			{
				inRtonWriter.WriteString("alias", mAlias, true);
				inRtonWriter.WriteRtId("id", mRtId);
			}
			inRtonWriter.EndObject();
		}
		inRtonWriter.EndArray();
	}
private:
	std::string mAlias;
	RtId mRtId;
};
    

class OnRtObjectsSelectedEvent
: public BaseRtonEventPacket
{
public:
    RT_CLASS_DEFINE(RtLiveLink::OnRtObjectsSelectedEvent, BaseRtonEventPacket, LiveLinkPacketMetaClass);
    
    enum SelectFrom
    {
        SelectFrom_Package,
        SelectFrom_Table
    };

    OnRtObjectsSelectedEvent()
    {
        mSelectFrom = SelectFrom_Package;
    }
    
    // inContext indicates whether AirMarshal UI should open the given RtIds from a package or from a table.
    OnRtObjectsSelectedEvent(SelectFrom inSelectFrom)
    {
        mSelectFrom = inSelectFrom;
    }

    // inContext indicates whether AirMarshal UI should open the given RtIds from a package or from a table.
    OnRtObjectsSelectedEvent(SelectFrom inSelectFrom, const RtId& inSelectedRtId)
    {
        mSelectFrom = inSelectFrom;
        AddSelectedRtObject(inSelectedRtId);
    }
    
    void AddSelectedRtObject(const RtId& inSelectedRtId)
    {
        mSelectedRtIds.push_back(inSelectedRtId);
    }
    
protected:
    virtual void WriteRtonEventData(RtSerialRtonWriter& inRtonWriter) override
    {
        inRtonWriter.WriteString("select_from", mSelectFrom == SelectFrom_Package ? "package" : "table");
        inRtonWriter.BeginArray("rtids", static_cast<uint32_t>(mSelectedRtIds.size()));
        {
            for (std::vector<RtId>::iterator i = mSelectedRtIds.begin(); i != mSelectedRtIds.end(); ++i)
            {
                inRtonWriter.WriteRtId(NULL, *i);
            }
        }
        inRtonWriter.EndArray();
    }
    
private:
    SelectFrom mSelectFrom;
    std::vector<RtId> mSelectedRtIds;
};
    
    
//
// SaveDataPacket
//
// $$ (avy) this really isn't related the to Rt system and should be moved to another
// header file specific to the SaveData AirMarshal plugin.
//

class SaveDataPacket
: public BaseRtonEventPacket
{
public:
    RT_CLASS_DEFINE(RtLiveLink::SaveDataPacket, BaseRtonEventPacket, LiveLinkPacketMetaClass);
    
    enum Transformation
    {
        Transformation_None,
        Transformation_RtonToJson
    };
    
    SaveDataPacket() {}
    
    // inTransformationDesc can be "" which indicates no transformation should be formed on the data before saving.
    // or inTransformationDesc can be "RtonToJson" if the data is rton which should be converted to json before saving
    // to a file.
    SaveDataPacket(const std::string& inSaveToRelativeFilePath, uint8* inData, uint32 inDataByteCount, Transformation inTransformation = Transformation_None)
    {
        mSaveToRelativeFilePath = inSaveToRelativeFilePath;
        mTransformation = inTransformation;
        mData = inData;
        mDataByteCount = inDataByteCount;
    }
protected:
    virtual void WriteRtonEventData(RtSerialRtonWriter& inRtonWriter) override
    {
        inRtonWriter.WriteString("save_to_file_path", mSaveToRelativeFilePath);
        
        std::string transformationStr;
        switch (mTransformation)
        {
            case Transformation_None:
                transformationStr = "None";
                break;
            case Transformation_RtonToJson:
                transformationStr = "RtonToJson";
                break;
            default:
                SEXY_ERROR("SaveDataPacket::WriteRtonEventData() Unexpected value for mTransformation");
                transformationStr = "None";
                break;
        }
        
        inRtonWriter.WriteString("transformation", transformationStr);
        inRtonWriter.WriteBinaryBlob("file_contents", "application/octet-stream", mData, mDataByteCount);
    }
private:
    std::string mSaveToRelativeFilePath;
    Transformation mTransformation;
    uint8* mData;
    uint32 mDataByteCount;
};

    
#endif // SEXY_IS_LIVELINK_ENABLED

//============================================================================
//    GLOBAL DATA
//============================================================================
//============================================================================
//    GLOBAL FUNCTIONS
//============================================================================
//============================================================================
//    INLINE CLASS METHODS
//============================================================================
//============================================================================
//    TRAILING HEADERS
//============================================================================

} // namespace RtLiveLink
} // namespace Sexy
//****************************************************************************
//**
//**    END HEADER RTLIVELINK.H
//**
//****************************************************************************


#endif // __RTLIVELINK_H__
