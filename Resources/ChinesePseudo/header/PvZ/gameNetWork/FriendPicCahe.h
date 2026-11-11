
/* ------------------------------------------------------------------------------------------------------------
 
	Popcap Shanghai studio
 
	Created by weiqi.zhong @ 2012 -3- 13
 ------------------------------------------------------------------------------------------------------------*/

#ifndef FRIEND_PIC_CACHE_H_
#define FRIEND_PIC_CACHE_H_
#include "Image.h"
#include "AtlasedImageStore.h"
#include <map>

typedef std::map<int32,Sexy::Image*> UserPicMap;
typedef UserPicMap::iterator  UserPicIter;
class FriendPicCache
{
public:
    FriendPicCache();
    ~FriendPicCache();
    Sexy::Image* GetImage(int32 userId);
    static FriendPicCache* Instance();
    void Clear();
    static FriendPicCache* s_pFriendPicCache;
    bool   IsExist(int32 userId);
    void   SavePic(ImageLib::Image* image,std::string& uuid);
    
private:
   
    std::string m_ext;
    UserPicMap  m_PicMap;
    //Sexy::AtlasedImageStore mImageStore;
};

#endif
