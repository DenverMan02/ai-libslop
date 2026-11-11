#ifndef CardTarget_H
#define CardTarget_H

#include "PropertySheetBase.h"
#include "BaseCursor.h"
#include "PVZTypes.h"
#include "RealObject.h"

class CardObject;
class Zombie;
typedef RtWeakPtr<class CardTargetProperty> CardTargetPropsPtr;


//Base Target Class

// enum CardTarget
// {
//     CardTarget_None;
//     CardTarget_Grid;
//     CardTarget_Zombie;
// };

class CardTargetProperty : public PropertySheetBase
{
public:
    RT_CLASS_DEFINE(CardTargetProperty, PropertySheetBase, RtClass);

    CardTargetProperty()
    :Targeted(true)
    {

    }

    virtual bool IsTargeted() const { return Targeted; };

    virtual RtClass* GetTargetAdaptorClass() const
    {
        DBG_HALT_MSG("CardTargetProperty of class %s does not implement GetCardTargetClass!", GetClass()->GetName());
        return nullptr;
    }

    bool Targeted;
};

class CardTargetAdaptor : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(CardTargetAdaptor, Sexy::RtObject, RtClass);

    virtual void initializaAdaptor(CardTargetPropsPtr i_targetProps);
    virtual void setTargetPosition(const Sexy::Point& i_position);
    virtual Sexy::Point getClosestValidTargetPosition(const Sexy::Point& i_position);
    virtual bool isValidTargetPosition(const Sexy::Point& i_position);

    template <typename T> const T* GetProps() const
	{
		DBG_ASSERT(mTargetProps.IsValid());
		return mTargetProps->Cast<const T>();
	}

    Sexy::Point mTargetPosition;
    CardTargetPropsPtr mTargetProps;
};




//Grid target

class GridTargetAdaptor : public CardTargetAdaptor
{
public:
    RT_CLASS_DEFINE(GridTargetAdaptor, CardTargetAdaptor, RtClass);

    virtual void initializaAdaptor(CardTargetPropsPtr i_targetProps) override;
    virtual void setTargetPosition(const Sexy::Point& i_position) override;
    virtual Sexy::Point getClosestValidTargetPosition(const Sexy::Point& i_position) override;
    virtual bool isValidTargetPosition(const Sexy::Point& i_position) override;

    Sexy::Point GetRegularGrid(int i_index);
    Sexy::Point GetRandomGrid();
    Sexy::Rect GetTargetRect();
protected:

    Sexy::Point mTargetGrid;
    Sexy::Rect mTargetArea;
};

class GridTargetProperty : public CardTargetProperty
{
public:
    RT_CLASS_DEFINE(GridTargetProperty, CardTargetProperty, RtClass);

    virtual RtClass* GetTargetAdaptorClass() const override
    {
        return GridTargetAdaptor::StaticGetClass();
    }

    GridTargetProperty()
    {
        Left = 0;
        Right = 0;
        Up = 0;
        Down = 0;
        TargetRange = Rect(0,0,6,7);
    }

    int Left;
    int Right;
    int Up;
    int Down;
    Sexy::Rect TargetRange;
};


//zombie target
class ZombieTargetAdaptor : public CardTargetAdaptor
{
public:
    RT_CLASS_DEFINE(ZombieTargetAdaptor, CardTargetAdaptor, RtClass);

    virtual void initializaAdaptor(CardTargetPropsPtr i_targetProps) override;
    virtual void setTargetPosition(const Sexy::Point& i_position) override;

    std::vector<RtWeakPtr<Zombie>> GetTargetList();
private:

    Sexy::Point mTargetGrid;
    Sexy::Rect mTargetArea;
};

class ZombieTargetProperty : public CardTargetProperty
{
public:
    RT_CLASS_DEFINE(ZombieTargetProperty, CardTargetProperty, RtClass);

    virtual RtClass* GetTargetAdaptorClass() const override
    {
        return ZombieTargetAdaptor::StaticGetClass();
    }

    virtual bool IsTargeted() const { return !AllZombie; };

    ZombieTargetProperty()
    {
        AllZombie = true;
        TeamFlag = TeamFlags::TEAM_PLANTS;
    }

    bool AllZombie;
    TeamFlags TeamFlag;
};


//griditem target
class GridItemTargetAdaptor : public GridTargetAdaptor
{
public:
    RT_CLASS_DEFINE(GridItemTargetAdaptor, GridTargetAdaptor, RtClass);

    virtual bool isValidTargetPosition(const Sexy::Point& i_position) override;
};

class GridItemTargetProperty : public GridTargetProperty
{
public:
    RT_CLASS_DEFINE(GridItemTargetProperty, GridTargetProperty, RtClass);

    GridItemTargetProperty()
    {
        GridItemCheck = true;
    }

    virtual RtClass* GetTargetAdaptorClass() const override
    {
        return GridItemTargetAdaptor::StaticGetClass();
    }

    bool GridItemCheck;
};


//grave stone Upgrade target
class GraveStoneUpgradeTargetAdaptor : public GridTargetAdaptor
{
public:
    RT_CLASS_DEFINE(GraveStoneUpgradeTargetAdaptor, GridTargetAdaptor, RtClass);

    virtual bool isValidTargetPosition(const Sexy::Point& i_position) override;

};

class GraveStoneUpgradeTargetProperty : public GridTargetProperty
{
public:
    RT_CLASS_DEFINE(GraveStoneUpgradeTargetProperty, GridTargetProperty, RtClass);

    virtual RtClass* GetTargetAdaptorClass() const override
    {
        return GraveStoneUpgradeTargetAdaptor::StaticGetClass();
    }
};




//Cursor
struct CursorAnimData
{
	CursorAnimData()
	: AnimRig(NULL)
	{

	}

	CursorAnimData(class PopAnimRig* i_rig, const SexyVector2& i_offset)
	: AnimRig(i_rig)
	, AnimOffset(i_offset)
	{

	}

	class PopAnimRig* AnimRig;
	SexyVector2 AnimOffset;
};

struct CursorAnimEffectData
{
	CursorAnimEffectData()
	: AnimRig(NULL)
	{

	}

	CursorAnimEffectData(class PopAnimRig* i_rig, const SexyVector2& i_offset, const SexyVector2& i_positionOffset)
	: AnimRig(i_rig)
	, AnimOffset(i_offset)
	, PositionOffset(i_positionOffset)
	{

	}

	class PopAnimRig* AnimRig;
	SexyVector2 AnimOffset;
	SexyVector2 PositionOffset;
};

class CardTargetCursorEffect : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(CardTargetCursorEffect, RtObject, RtClass) {};

	CardTargetCursorEffect();
    virtual ~CardTargetCursorEffect();

    void AddAnimRig(class PopAnimRig* i_animRig, SexyVector2 i_offset, SexyVector2 i_positionOffset);

    virtual void Update();
    virtual void Draw(Sexy::Graphics* i_g);

    void SetMirrorX(bool i_mirrorX) { m_mirrorX = i_mirrorX; }
    bool GetMirrorX() { return m_mirrorX; }

    void SetVisible(bool i_visible) { m_visible = i_visible; }
    bool IsVisible() { return m_visible; }

    Sexy::Point GetBoardPosition() const { return m_boardPosition; }
    void SetPositionFromBoardSpace(const Sexy::Point& i_boardSpacePos);

    RtWeakPtr<CardObject> m_cardObject;
    std::vector<CursorAnimEffectData> m_cursorAnimRigs;
    bool m_mirrorX;
    bool m_visible;
    Point m_boardPosition;
    Sexy::SexyVector2 m_cursorOffset;
};

class CardTargetCursorEffectMgr : public LazySingleton <CardTargetCursorEffectMgr>
{
public:
	CardTargetCursorEffectMgr();
    ~CardTargetCursorEffectMgr();

    void AddEffect(bool i_mirrorX);
    void AddAnim(class PopAnimRig* i_animRig, SexyVector2 i_offset, SexyVector2 i_positionEffect);
    void ClearEffect();

    void Draw(Sexy::Graphics* i_g);
    void Update();

    Sexy::Point GetBoardPosition();
    void SetPositionFromBoardSpace(const Sexy::Point& i_boardSpacePos);
    void SetVisible(bool i_visible);

    CardTargetCursorEffect* m_effect;
};

class CardTargetCursor : public BaseCursor
{
public:
	RT_CLASS_DEFINE(CardTargetCursor, BaseCursor, RtClass) {};

    //RtClass动态实例化不能带参数
	CardTargetCursor();
    virtual ~CardTargetCursor();
    //延迟初始化数据
    virtual void InitializaTargetCursor(const Sexy::Touch& i_boardSpaceTouch, RtWeakPtr<CardObject> i_cardObject);
    virtual void OnInitialized();
    virtual void GenerateAnim();

    bool onTouchEvent(const Sexy::Touch& i_boardSpaceTouch) override;

	virtual bool CanUseAtCurrentPosition();

	void GetValidRange(Sexy::Rect& i_rect);
    
	virtual void tryToUse();
    virtual void cancelToUse();

    void onDestroy() override;

    Sexy::SexyVector2 getCursorAnimOffset() const override;
    void AddAnimRig(class PopAnimRig* i_animRig, SexyVector2 i_offset);
    class PopAnimRig* CreateAnimRig(int i_type, const std::string& i_typeName);

    virtual void onUpdate();
    virtual void onDraw(Sexy::Graphics* i_g);

    RtWeakPtr<CardObject> m_cardObject;
    std::vector<CursorAnimData> m_cursorAnimRigs;
    Sexy::SexyVector2 m_cursorOffset;
};

class GridTargetCursor : public CardTargetCursor
{
public:
	RT_CLASS_DEFINE(GridTargetCursor, CardTargetCursor, RtClass) {};

	GridTargetCursor(){};
    virtual ~GridTargetCursor();
    virtual void InitializaTargetCursor(const Sexy::Touch& i_boardSpaceTouch, RtWeakPtr<CardObject> i_cardObject) override;

	virtual bool onTouchEvent(const Sexy::Touch& i_boardSpaceTouch) override;

	virtual bool CanUseAtCurrentPosition() override;
	virtual Point GetCurrentGridPosition();
    
	virtual void tryToUse() override;
    virtual void cancelToUse() override;

};


#endif
