/*
 * CardGameBoard.h
 *
 *  Created on: 2022-5-31
 *      Author: admin
 */

#ifndef CARDGAMEBOARD_H_
#define CARDGAMEBOARD_H_

#include "Singleton.h"
#include "DNode/DNodeWidget.h"
#include "DNode/DButton.h"
#include "DNode/DMenu.h"
#include "PVZTypes.h"
#include "CardType.h"
#include "CardGameNetworkMgr.h"

enum CardDestination
{
	CardDestination_Hand,
	CardDestination_Library
};

struct TutorialCardInfo
{
	TutorialCardInfo()
	: Id(-1)
	, GridX(-1)
	, GridY(-1)
	{

	}

	TutorialCardInfo(int i_id, int i_gridX, int i_gridY)
	: Id(i_id)
	, GridX(i_gridX)
	, GridY(i_gridY)
	{

	}

	int Id;
	int GridX;
	int GridY;
};

class CardBoardMgr : public LazySingleton <CardBoardMgr>
{
public:
	CardBoardMgr();
    ~CardBoardMgr();

    // Board Config
    const class CardGameBoardConfig* GetConfig() const;

    // Board
    void gatherBoardInfo(Sexy::Rect& i_rect);
    void gatherHandCardsInfo(Sexy::FRect& i_rect, Widget* i_parent);
    const float GetInitialHandCardsCoverRate() const;

    void SetPresetCards(const std::vector<int>& i_cards);
    const std::vector<int>& GetPresetCards();

    void SetTutorialCards(const std::vector<TutorialCardInfo>& i_cards);

    int GetInitialHandCardsCount();
    void SetInitialHandCardsCount(int i_count) { m_initialCardsCount = i_count; }
    void SetCurrentCardsCount(int i_count) { m_currentCardsCount = i_count; }
    int GetCurrentCardsCount() { return m_currentCardsCount; }
    bool ReachMaxHandCards();

    void SpendCost(int i_cost);
    void SetCurrentPlayerSun(int i_count);
    int GetCurrentPlayerSun() { return m_currentPlayerSun; }
    bool HasEmptySun();
    void FillPlayerSun();
    void SetInitialPlayerSun(int i_count);
    int GetInitialPlayerSun() { return m_initialPlayerSun; }
    void SetTurnLeftTime(float i_time);

    // Card
    void gatherCardInfo(CardUIInfo& i_info, int i_id);
    RtWeakPtr<class CardObject> CreateCardObject(int i_id);
    bool VerifyCardDestination(RtWeakPtr<CardObject> i_object, CardDestination i_destination);

    // Test
    void TestDrawCard(int i_handPosition = 0);
    void TestDiscardAllCards();
    
    void OnAppLostFocus();

    void DiscardCards(int i_count, int i_destination = 0);
    // temp, 0 to create hand card, 1 to create library card
    void CreateCard(int i_id, CardDestination i_destination = CardDestination_Hand, SexyVector2 i_start = SexyVector2(0,0));
    void TryHideCards(const Sexy::Touch& touch);

    void CreateBoard();
    void RemoveBoard();

    // Turns
    void TurnPlayerBegan(int i_round);
    void TurnPlayerPlayCards();
    void TurnPlayerEnd();

    // Utils
    void ConvertToBoardTouch(Sexy::Touch& i_touch);
    const Point ConvertTouchPositionIntoBoardGrid(const Sexy::Touch& touch);
    const FPoint ConvertTouchPositionIntoBoardPosition(const Sexy::Touch& touch);
    const Point ConvertBoardPositionIntoBoardGrid(float i_x, float i_y);
    void TryAddPlantAt(PlantTypePtr i_plantType, int i_gridX, int i_gridY, int i_level = 1);
    float CalcOffsetXByCenterPt(int i_handPosition, float i_cardWidth);
    float CalcInitialOffsetXByCenterPt(int i_handPosition, float i_cardWidth);
    float CalcRepositionDelta(const FPoint& i_centerPt, class Card* i_card, float i_cardWidth, float i_cardXOffset);
    DVec2 CalcSlideOffset(Card* i_card, bool i_out, float i_initialY);
    DVec2 GetSlideOffset(Card* i_card);
    float GetBoardScale();
    const std::string& GetCurrentScreenType() { return m_screenType; }

    const std::vector<TutorialCardInfo>& GetTutorialCardInfos() { return m_tutorialCardInfos; }

private:
    const class CardGameBoardConfig* getConfig() const;

    int m_currentCardsCount;
    int m_initialCardsCount;
    int m_currentPlayerSun;
    int m_initialPlayerSun;
    std::vector<int> m_presetCards;
    std::string m_screenType;
    std::vector<TutorialCardInfo> m_tutorialCardInfos;
};

class DFixedLayer:public DLayer
{
protected:
	DFixedLayer() = default;
public:
    virtual ~DFixedLayer() = default;

    virtual void draw(const DMatrix& mat,Graphics* i_g) override;

    DFixedLayer& setFixedRect(float i_x, float i_y, float i_width, float i_height);

    friend class DRefPtr<DFixedLayer>;

protected:
    FRect m_fixedRect;
};

class DBoard : public DMenu
{
public:

    virtual ~DBoard() = default;

    virtual bool handleTouchBegan(const Sexy::Touch& touch) override;
    virtual void handleTouchMoved(const Sexy::Touch& touch) override;
    virtual void handleTouchEnded(const Sexy::Touch& touch) override;
    virtual void handleTouchCancelled(const Sexy::Touch& touch)override;

protected:
    DBoard();

protected:
    friend class DRefPtr<DBoard>;
    bool m_isTouching;
};

class Card : public DButton
{
	typedef DButton Super;
public:
	Card();
	virtual ~Card();

	void longPress(const Sexy::Touch& touch) override;

	void InitPreview(int i_id);
	void Init(CardBoardMgr* i_manager, int i_id, int i_handPosition);
	CardBoardMgr* GetManager();
	void Generate();
	void GeneratePreview(RtWeakPtr<class CardType> i_type);
	DRefPtr<DSpriteNode> Generate(RtWeakPtr<class CardType> i_type);

    DRefPtr<DSpriteNode> clone() const { auto b = _copy(); DRefPtr<DSpriteNode> a(b); return a; }
	DRefPtr<DSpriteNode> CloneImgNode();
	void SetDisabledNode(bool i_greyEffect);

	void SetHandPosition(int i_position);
	int GetHandPosition() { return m_handPosition; }

	virtual bool TryUse(int i_gridX, int i_gridY);
	virtual bool TryUse(FPoint i_position);
	virtual bool Use(int i_gridX, int i_gridY);
	virtual bool Use(FPoint i_position);
	int GetCost();

	bool InsideTouch(const Sexy::Touch& touch);
	void DisplayCursor(const Sexy::Touch& touch);
	void SetCursorVisible(bool i_visible);

	RtWeakPtr<class CardObject> GetCardObject() { return m_cardObject; }
	void GetValidRange(Sexy::Rect& i_rect);
	bool IsConsumable();
	int GetId() { return m_id; }

	void SetTutorialGrid(const Point& i_grid) { m_tutorialGrid = i_grid; }

protected:
	virtual DSpriteNode* _copy() const { auto a = new DSpriteNode(); *a = *this->m_imageNode; return a;}
    
    FRect getRect() override;

	friend class DRefPtr<Card>;

private:
	void generate(const CardUIInfo& i_info);
	void gatherCardInfo(CardUIInfo& i_info);
	void setDisableEffect(DTransformNode* i_parent);

	RtWeakPtr<class CardObject> m_cardObject;

	CardUIInfo m_cardInfo;
	CardBoardMgr* m_manager;
	int m_handPosition;
	int m_id;
	Point m_tutorialGrid;

	DSpriteNode* m_imageNode = NULL;
};

enum HandCardState
{
	HandCardState_Normal,
	HandCardState_Offside
};

enum PlayerState
{
	PlayerState_None,
	PlayerState_PlayCards,
	PlayerState_End
};

enum TutorialStep
{
	TutorialStep_None = -1,
	TutorialStep_PreGame,
	TutorialStep_Dave,
	TutorialStep_1,
	TutorialStep_2,
	TutorialStep_3,
	TutorialStep_4,
	TutorialStep_5,
	TutorialStep_6,
	TutorialStep_7,
	TutorialStep_8,
	TutorialStep_Dave2,
	TutorialStep_9,
	TutorialStep_10,
	TutorialStep_11,
	TutorialStep_Count
};

class DTouchCloseLayer : public DMenu
{
public:

    virtual ~DTouchCloseLayer() = default;

    virtual bool handleTouchBegan(const Sexy::Touch& touch) override;
    virtual void handleTouchEnded(const Sexy::Touch& touch) override;

    void onTouchEndedCallback(std::function<void(const Sexy::Touch&)> i_func){ m_touchEndedCallback = i_func; }

protected:
    DTouchCloseLayer();

protected:
    friend class DRefPtr<DTouchCloseLayer>;

    std::function<void(const Sexy::Touch&)> m_touchEndedCallback;
};

class CardGameBoard : public DNodeWidget
{
public:
	enum CardArrowEffectType
	{
		LibraryToHands,
		HandsToGraveyard,
		HandsToLibrary,
		DisplayToGraveyard,
		GraveyardToHands,
		GraveyardToLibrary,
		HandsToRemove,
		EnemyToHands,
		EnemyToLibrary
	};

	enum TouchState
	{
		TouchState_TouchBegan,
		TouchState_TouchMove,
		TouchState_TouchEnd
	};

    static CardGameBoard* create();
    static CardGameBoard* get();

    CardGameBoard();
    virtual ~CardGameBoard();

    virtual void Initialize() override;

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void Update() override;

    void Remove();

    void CreateBoard();
    void CreateLibrary(DTransformNode* i_parent);
    void CreateGraveyard(DTransformNode* i_parent);
    void CreatePlayerSun(DTransformNode* i_parent);
    void CreateTurnDisplay(DTransformNode* i_parent);
    void CreateTestDraw(DTransformNode* i_parent);
    void SetImageNode(DSpriteNode* i_node, DTransformNode* i_parent, int i_zOrder);
    void ClearImageNode();
    void DisplayImageNode(class Card* i_usedCard, DTransformNode* i_parent);
    void AddToPlayedImageNodes(class Card* i_usedCard, DTransformNode* i_parent);
    void SunChanged();
    void SunMaxChanged();
    void TurnEndTimeChanged(float i_leftTime);

    // Turns
    void TurnPlayerBegan(int i_round);
    void TurnPlayerPlayCards();
    void TurnPlayerEnd();

    // Cards Func
    void HideCards(const Sexy::Touch& touch);
    void FillCards();
    void EnableHandCards(bool i_enable);
    void EnableHandCardsTouch(bool i_enable);
    void CheckCost();
    DRefPtr<Card> CreateRawCard(int i_id, bool i_scaled = false);
    DRefPtr<Card> CreateHandCard(Card* i_raw, int i_testPosition, DTransformNode* i_parent);
    void UseCard(class Card* i_card, const Sexy::Touch& touch);
    void DrawCard();
    void DrawCard(int i_handPosition);
    void ShuffleCards();
    void RepositionCards();
    void SlideCards(bool i_out, class Card* i_usedCard);
    void SlideRepositionCards(bool i_out);
    void InsertCard(Card* i_card, int i_handPosition, DTransformNode* i_parent);
    void CancelCard(Card* i_card);
    void DiscardCards();

    void TryFillCards();
    void TryDiscardCards(int i_count);
    void TryCreateCard(int i_id, CardDestination i_destination, SexyVector2 i_start);
    void TryCreateCard(const std::vector<int>& i_idList);

    //
    bool VerifyCardDestination(RtWeakPtr<CardObject> i_object, CardDestination i_destination);

    // Tests
    void CreateTestInit();
    void CreateTestCards();
	void LostFocus();
	
    // Tutorial
	void CheckTutorial();
	void EndTutorial();
    void TriggerTutorial(DVec2 i_start, DVec2 i_end, float i_duration, bool i_enableTouch, bool i_repeat);
    void SetTutorialStep(TutorialStep i_step);
    void setupTutorialAdvice();
    void ClearTutorialTouch();
    void CreateTutorialTouch();
    void ContinueTutorial();
    void OnNarrativeTutorialStartCompleted();
    void OnNarrativeTutorialEndCompleted();
    bool HasTutorial();
    void onSetTutorialStep(TutorialStep i_step);

private:
    static CardGameBoard* s_pWidgetHandler;

    const FPoint GetCardInitialPosition(Card* i_card);
    const FPoint GetCardInitialPosition(int i_handPosition);
    void OnUsedCard(Card* i_card);
    void OnDrawCard(Card* i_card);
    void createLibraryUI(DTransformNode* i_parent);
    void createLibraryCards();
    void onBoardPreCreated();
    void onBoardCreated();
    void changeSunDisplay(int i_value);
    void createBounceEffect(DTransformNode* i_node);
    void changeInitialSunDisplay(int i_value);
    void changeTurnDisplay(float i_value);
    void resetTurnDisplay();
    void refreshGraveyardDisplay();
    void changeGraveyardDisplay(int i_value);
    void refreshLibraryDisplay();
    void changeLibraryDisplay(int i_value);
    bool tryDrawCardFromLibrary(int i_cardsToDraw = 1);
    DRefPtr<Card> drawCardFromLibrary();
    void onCreateCardCallback(std::function<void(int)> i_func){ m_createCardCallback = i_func; }
    void onRefillCallback(std::function<void(int)> i_func){ m_refillCallback = i_func; }
    void continueFillCards();
    void continueDrawCards(int i_handPosition);
    void continueCreateCards(int i_id, CardDestination i_destination);
    void fillDiscardCards(int i_count);
    void tryRefillLibrary();
    void refillLibrary();
    void displayCursorArea(DTransformNode* i_parent, Sexy::Rect i_rect);
    void clearCursorArea();
    bool canHideCards();
    void setCardsVisible(bool i_visible);
    void setCardVisible(int i_position, bool i_visible);
    void createCursor(Card* i_card, const Sexy::Touch& touch);
    void setCursorVisible(Card* i_card, bool i_visible);
    void passTouchToBoard(TouchState i_state, const Sexy::Touch& touch);
    void getCardValidRange(Card* i_card, Sexy::Rect& i_rect);
    bool isConsumableCard(Card* i_card);

    DRefPtr<DAnimNode> createTempArrowEffect(DTransformNode* i_parent);
    void createArrowEffect(DTransformNode* i_parent);
    void createArrowEffects(DTransformNode* i_parent);
    void resetArrowEffects();
    void moveArrowEffect(CardArrowEffectType i_type, DVec2 i_start = DVec2(0,0));
    void onMoveDone(CardArrowEffectType i_type);
    void onStartMove(CardArrowEffectType i_type, int i_position);
    void onSingleMoveDone(CardArrowEffectType i_type, int i_position);

    void createTutorialEffect(DTransformNode* i_parent);
    void clearTutorialEffect();

    void drawTutorials(Sexy::Graphics* i_g);
    void updateTutorials();
    void enableAllBtns(bool i_enable);

    DArray<Card*> m_handCards;
    DArray<Card*> m_graveyardCards;
    DArray<Card*> m_libraryCards;
    DSpriteNode* m_imageNode;
    DFixedLayer* m_fixedLayer;
    class DBoard* m_touchBoard;
    DArray<DSpriteNode*> m_playedImageNodes;
    DAnimNode* m_arrowEffect;
    DArray<DAnimNode*> m_arrowEffects;

    DAnimNode* m_tutorialEffect;

    DButton* m_libraryBtn;
    DButton* m_graveyardBtn;
    DStringNode* m_sunDisplay;
    DStringNode* m_turnDisplay;
    DSpriteNode* m_sunNode;
    DButton* m_turnBtn;
    pvztime_t m_nextTurnDisplayTime;
    DVec2 m_previousPt;
    std::vector<SexyVector2> m_previousPts;

    FPoint m_centerPt;
    FRect m_cardFrame;

    std::vector<int> m_cardsToDiscard;
    int m_usingCardHandPosition;
    HandCardState m_cardState;
    PlayerState m_playerState;

    std::function<void(int)> m_createCardCallback;
    std::function<void(int)> m_refillCallback;

    TutorialStep m_tutorialStep;
    bool m_tutorialHasLongPress;
    bool m_tutorialNextFrame;
    //bool m_tutorialHasUsedCard;
    DTouchCloseLayer* m_tutorialTouch;
    pvztime_t m_tutorialStartTime;
    //DStringNode* m_tutorialHint;
};

class CardDisplay:public DNodeWidget
{
public:
    static CardDisplay* create(const DArray<Card*>& i_cards, bool i_library);
    static CardDisplay* get();

    virtual ~CardDisplay();

    virtual void Initialize() override;

    virtual void UserInit() override;

    void TryRemoveSelf(const Sexy::Touch& touch);

    FRect getRect();

public:
    static CardDisplay* s_pWidgetHandler;
    DArray<Card*> m_cards;
    static bool m_isLibrary;
};

class CardSelect:public DNodeWidget
{
public:
    static CardSelect* create(const std::vector<CardGameCardInfo>& i_cards);
    static CardSelect* get();

    CardSelect();

    virtual ~CardSelect();

    virtual void Initialize() override;

    virtual void UserInit() override;

    DArray<Card*> CreateCard(int i_id, int i_count);

    DRefPtr<DSpriteNode> CreateMark(DTransformNode* i_parent);

public:
    static CardSelect* s_pWidgetHandler;
    std::vector<CardGameCardInfo> m_cards;
    DArray<Card*> m_currentCards;
};

namespace Message
{
	void NotifyDrawCardsActionDone();
	void NotifyPlayCardsActionDone();
	void NotifyCardSelectDone();
	void NotifyCardTutorial(bool i_trigger);
}

#define gCardBoardMgr CardBoardMgr::GetInstancePtr()
#define gCardSystemMgr gLawnApp->m_board->GetGameSubSystem<CardSystemManager>()

#endif /* CARDGAMEBOARD_H_ */
