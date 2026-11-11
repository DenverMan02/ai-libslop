#ifndef _ANDROIDMUSICSTREAM_H_
#define _ANDROIDMUSICSTREAM_H_

#include <string>

namespace Sexy
{

class AndroidMusicStream
{
public:
	int mMusicId;
	std::string mFilename;
	int mOffset;
	int mLength;

	double mVolume;
	double mMaxVolume;

public:
	AndroidMusicStream( int InMusicId, std::string const& InFilename, int32 InOffset, int32 InLength );
	~AndroidMusicStream();

//	bool SetDataPointer( byte * pInData, uint32 InDataSize, bool bInCopyData );

	void SetVolume( double InNewVolume );
	void SetMaxVolume( double InNewMaxVolume );


	bool IsValid() const
	{
		return mMusicId != -1;
	}
};

}

#endif // _ANDROIDMUSICSTREAM_H_

