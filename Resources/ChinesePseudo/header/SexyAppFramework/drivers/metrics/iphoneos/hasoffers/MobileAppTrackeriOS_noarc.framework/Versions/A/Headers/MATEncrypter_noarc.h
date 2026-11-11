#import <Foundation/Foundation.h>
#import <CommonCrypto/CommonDigest.h>
#import <CommonCrypto/CommonCryptor.h>

@interface MATEncrypter : NSObject
+(NSMutableString *)encryptString:(NSMutableString *)str key:(NSString *)key;
@end
