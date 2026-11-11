/* ------------------------------------------------------------------------------------------------------------
 
	Popcap Shanghai studio
 
	Created by weiqi.zhong @ 2012 -3- 13
 ------------------------------------------------------------------------------------------------------------*/

#ifndef NETWORKDEF_H
#define NETWORKDEF_H

#include "StructuredData.h"
#include"NetworkMsgProcess.h"

//-----------------------------function------------------------
//extern char *g_buff;

//char* g_buff = NULL;

typedef std::string AString;
typedef struct _NetWorkMsg
{
    AString  msg;
    int erro;
    _NetWorkMsg()
    {
        msg  = "";
        erro = 0;
    }
    void Clear()
    {
        msg  = "";
        erro = 0;
    }
}NetWorkMsg;
class PackMemberFunctionBase
{
public:
	virtual  void Process(const  NetWorkMsg&  obj ) = 0;

};

template<typename ClassType,typename PacketType>
class PacketMemberFuncHandle : public PackMemberFunctionBase
{
public :
	typedef void ( ClassType::* PacketFunctor )(const PacketType& rPkt );
	PacketMemberFuncHandle( ClassType* pObject, PacketFunctor pMemFunctor)
	{
		m_PacketFunc = pMemFunctor;
		m_pObject    = pObject;
	}
	virtual void Process( const NetWorkMsg& obj )
	{
	//	PacketType* rPacket = new(g_buff) PacketType();
      //  rPacket->Decode(objecValue);

		(m_pObject->*m_PacketFunc)(obj);
	}
	ClassType*     m_pObject;
	PacketFunctor  m_PacketFunc;
};



#define RegistFunHandle(MSG_ID,CLASS ,Pkg_Class,FUNC) \
	 G_msgFunMap[MSG_ID] = new PacketMemberFuncHandle<CLASS, Pkg_Class>(this, &CLASS::FUNC)


#define RegistFunHandleForNetWork(MSG_ID,FUNC) RegistFunHandle(MSG_ID,INetworkMsgProcess ,NetWorkMsg,FUNC)

#endif

