/*
 * talking_game.h
 *
 *  Created on: 2013-9-22
 *      Author: chenyc
 */

#ifndef TALKING_GAME_H_
#define TALKING_GAME_H_
#include "core.h"


#ifdef HOST_ANDROID
#include <jni.h>
#endif


class talkingGame : public LazySingleton<talkingGame>
{
public:
	talkingGame();

	void setAccount();
	void setGameServer();
	void setLevel(int iLevel);
	void onPay(const char* itemid, int cash, int gem, const char* type );
	void onPayComplete( const char* payid );

	void onUseGem( const char* itemName, int amount, int price );
	void onUseItem( const char* itemName, int amount );

	void beginLevel( const char* levelname );
	void completeLevel( const char* levelname );
	void failLevel( const char* levelname , const char* reason );

	void onReward( int amount, const char* rewardid );
	void setisFirstTime( bool isNew ){ isNewUser_ = isNew;}


	void getGold( const char* reason, int amount );
	void useGold( const char* reason, int amount );

	void stayPlayer( const char* pointname );

    void setPause(bool isPause) {isPause_ = isPause;}
private:
	bool   		isNewUser_;
    bool        isPause_;
#ifdef HOST_ANDROID
	JNIEnv* 	env_;
	jclass 		clazz_;
#endif
};


#endif /* TALKING_GAME_H_ */
