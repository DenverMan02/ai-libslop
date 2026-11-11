//
//  Hmac-sha256.h
//  Solitaire_iosHD
//
//  Created by Scott Rankin on 8/23/12.
//  Copyright (c) 2012 PopCap Games, Inc. All rights reserved.
//

#pragma once
#include <string>

#include "Crypt/sha256.h"

namespace Sexy {
class HMAC_SHA256
{
public:
    HMAC_SHA256(const uchar*, uint32, const uchar*, uint32);
    ~HMAC_SHA256();
    
    std::string Base64URLEncodedHash();
    std::string HexEncodedHash();
    
private:
    static const int kDigestSize = ( 256 / 8);
    static const int kBlockSize = ( 512 / 8);
    
    typedef struct 
    {
        Sexy::SHA256Context ctx_inside;
        Sexy::SHA256Context ctx_outside;
        
        uchar block_ipad[kBlockSize];
        uchar block_opad[kBlockSize];
    } HMAC_SHA256_CTX;

    void Hash();
    void init();
    void update();
    void final();
    void Base64UrlEncodeHash();
    void HexEncodeHash();
    
    std::string to_hex(uchar);
    
    HMAC_SHA256_CTX context_;
    const uchar* message_;
    uint message_length_;
    const uchar* key_;
    uint key_length_;
    uchar mac_[kDigestSize];
    std::string hmac_sha256_;
};
}
