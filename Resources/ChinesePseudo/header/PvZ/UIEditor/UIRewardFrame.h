//
//  UIWidgetImage.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/6/9.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _UIRewardFrame_h_
#define _UIRewardFrame_h_
#include "Widget.h"
#include "PVZTypes.h"
#include <string>

class UIRewardFrame : public Sexy::Widget
{
public:
    enum RewardType
    {
    	Reward_None = -1,
        Reward_Coin = 0,
		Reward_Gem = 1,
		Reward_Plant = 2,
		Reward_Plant_Piece = 3,
		Reward_Avatar_Piece = 4,
		Reward_Others = 5,
		// zhousen add
		Reward_Avatar = 6,
		Reward_Accessory = 7,
		Reward_Accessory_Piece = 8,
		Reward_Material = 9,
		Reward_New_Avatar = 10,
		Reward_New_Avatar_Piece = 11,
		Reward_Artifact = 12,
		Reward_Headshot = 13,
		Reward_Collection = 14,
		Reward_CardGame = 15,
		Reward_GeneSequence = 16,
		Reward_GeneEssence = 17,
		Reward_RankAvatar = 18,
		Reward_Exp = 19,
		Reward_TrailCard = 20,
    };

	// for decorator image draw position
	enum DecoratorType
	{
		Decorator_Invalid = -1,
		Decorator_LeftTop,
		Decorator_MiddleTop,
		Decorator_RightTop,
		Decorator_LeftMiddle,
		Decorator_RightMiddle,
		Decorator_LeftBottom,
		Decorator_MiddleBottom,
		Decorator_RightBottom,
		Decorator_Max,
	};
public:
    UIRewardFrame(RewardType type, const std::string& reward, int rewardQuantity, bool hasFrame = true);
	virtual ~UIRewardFrame();

	void SetRewardImage(Sexy::Image* rewardImage);
	virtual void					Draw(Sexy::Graphics* i_g) override;
	void SetQuantity(int quantity){ m_rewardQuantity = quantity; }
	void SetDecoratorString(const std::string str);
	void SetDecoratorType(DecoratorType type);
	void SetLockString(const std::string str);
	void SetFrameSet(int i_frameSet);
	void SetTextColor(Color color);// number color
	void SetLevel(int level);
	void SetObjectID(int objectID);
	void SetNeedDrawLevelImage(bool i_flag);

	static UIRewardFrame* CreateUIRewardFrame(int objectId, int num, bool hasFrame);
	
	virtual void DrawString_data(int quantity, Sexy::Graphics* i_g, int height, int width, Sexy::Color color);

	void EnableFrameRotation(bool enable);
	void SetFrameRotationScale(float scale);

protected:
    virtual void                        DrawCoin(Sexy::Graphics* i_g);
    virtual void                        DrawGem(Sexy::Graphics* i_g);
    virtual void 						DrawExp(Sexy::Graphics* i_g);
    virtual void                        DrawPlant(Sexy::Graphics* i_g);
    virtual void                        DrawPlantPiece(Sexy::Graphics* i_g);
    virtual void                        DrawAvatarPiece(Sexy::Graphics* i_g);
	virtual void 						DrawTrialCard(Sexy::Graphics* i_g);
    virtual void						DrawOthers(Sexy::Graphics* i_g);

	// zhousen add
    virtual void 						DrawAvatar(Sexy::Graphics* i_g);
    virtual void 						DrawAccessory(Sexy::Graphics* i_g);
    virtual void 						DrawAccessoryPiece(Sexy::Graphics* i_g);
	virtual void						DrawMaterial(Sexy::Graphics* i_g);
	virtual void 						DrawNewAvatar(Sexy::Graphics* i_g);
	virtual void 						DrawNewAvatarPiece(Sexy::Graphics* i_g);
	virtual void 						DrawArtifact(Sexy::Graphics* i_g);
	virtual void 						DrawHeadshot(Sexy::Graphics* i_g);
	virtual void						DrawCollection(Sexy::Graphics* i_g);
	virtual void 						DrawCardGame(Sexy::Graphics* i_g);
	virtual void 						DrawGeneSequence(Sexy::Graphics* i_g);
	virtual void 						DrawGeneEssence(Sexy::Graphics* i_g);
	virtual void						DrawRankAvatar(Sexy::Graphics* i_g);
	virtual void 						DrawDecorator(Sexy::Graphics* i_g);// for 8 directions decorator
	Sexy::Rect					GetDecoratorRect(DecoratorType type);// get decorator type

	virtual void						DrawLockImage(Sexy::Graphics* i_g);;// lock image
	virtual void 						DrawLevelImage(Sexy::Graphics* i_g);

	Sexy::Image*				GetLevelImage(int level);

protected:
	bool m_hasFrame;
	RewardType m_type;
	std::string m_reward;
	Sexy::Image* m_rewardImage;
	int m_rewardQuantity;
	Sexy::Image* m_decoratorImage;
	DecoratorType m_decoratorType;
	Sexy::Image* m_lockImage;
	Sexy::Image* m_levelImage;
	int m_frameSet;
	Color m_textColor;
	int m_level;
	bool m_needDrawLevelImage;
	int m_objectID;
	class Effect_PopAnim* m_frameRotationEffect;
	float m_frameRotationScale;
	bool m_showFrameRotationEffect;
	PlantTypePtr m_plantType;
};

#endif
