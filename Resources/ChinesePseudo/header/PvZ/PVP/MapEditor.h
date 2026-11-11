//
//  MapEditor.h
//  PlantsVersusZombies2
//
//  Created by csh on 15/10/13.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__MapEditor__
#define __PlantsVersusZombies2__MapEditor__

#include "RtDb.h"
#include "RtDelegate.h"
#include "TimeMgr.h"
#include "Widget.h"
#include "core.h"
#include "ButtonListener.h"
#include "PVZ2UIButton.h"
#include "Effect_PopAnim.h"
#include "WorldData.h"
#include "MapEventItem.h"

//#define UI_EDITOR_ENABLE

class Effect_PopAnim;

enum
{
    EDITE_MODE_INVALID = 0,
    EDITE_MODE_ADD,
    EDITE_MODE_COPY,
    EDITE_MODE_MOVE,
    EDITE_MODE_DELETE,
};

enum PVPMAP_EVENTTYPE //Cannot insert, only append
{
    PVPMAP_EVENTTYPE_NORMAL = 0,
    PVPMAP_EVENTTYPE_HOUSE = MAPEVENT_PVP_HOUSE,
    PVPMAP_EVENTTYPE_HOUSE_ACHIEVE = MAPEVENT_PVP_HOUSE_ACHIEVE,
    PVPMAP_EVENTTYPE_CLOUD = MAPEVENT_PVP_CLOUD,
    PVPMAP_EVENTTYPE_CLOUD_PRICE = MAPEVENT_PVP_CLOUD_PRICE,
    PVPMAP_EVENTTYPE_NUM = MAPEVENT_PVP_END,
};

typedef struct
{
    SexyString name;
    Rect rect;
} EditorButton;

class MapPiecesAnimRig
{
public:
    Rect GetAnimRect();
    void Clear();
public:
    int rigId = 0;
    int eventId = 0;
    Effect_PopAnim* rig = nullptr;
    Rect rect;
};

struct MapArtAnim
{
    PopAnim* anim;
    Rect rect;
    MapArtAnim()
    : anim(NULL)
    {
        
    }
};

static std::string eventTypeStr[PVPMAP_EVENTTYPE_NUM] =
{
    "NORMAL",
    "HOUSE",
    "HOUSE_ACHIEVE",
    "CLOUD",
    "CLOUD_PRICE",
};

class MapEditor : public Sexy::Widget //, public Sexy::ButtonListener //  Sexy::Widget
{
public:
    
    MapEditor();
    virtual ~MapEditor();
    
    virtual void    Update();
    virtual void	Draw(Sexy::Graphics* i_g);
    void            DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    void            DrawEditorButton(Graphics* i_g, const Rect& i_rect, const SexyString& i_label, const bool i_isDown);
    void            DrawEditorLabel(Graphics* i_g, const SexyString& i_labelText, Sexy::Point i_position);
    void            DrawEditorTextField(Graphics* i_g, const SexyString& i_labelText, Sexy::Point i_position);
    
    void            newMap(const std::string& i_worldName);
    void            loadMap(const std::string worldMapName, bool fromFile);
    void            rebuildResourceGrid();
    void            saveMap();
    void            saveMapManifest();
    int             getCurrentLayer() { return m_currentLayer;}
    void            insertLayer();
    void            addAnim(std::string name);
    void            switchAnim(int type, int index, int position);
    
    virtual void    EditorTouchMoved(const Sexy::Touch& touch, float scale);
    virtual void    EditorTouchBegan(const Sexy::Touch& touch, int inCameraX, int inCameraY);
    virtual void    EditorTouchEnded(const Sexy::Touch& touch);
    virtual void    HandleMapItem(Sexy::Touch *touch, int x, int y);
    
    WorldData*      m_editorWorldData;
    std::vector<MapPiecesAnimRig> m_mapPiecesPopAnimRig;
    int             m_editorMode;

    
    
protected:
    
    WorldMapCamera*                         m_camera;
    SexyVector2								m_cameraPosition;
    SexyVector2								m_cameraCenter;
    float									m_cameraZoomMin;
    float									m_cameraZoomMax;
    float									m_cameraZoom;
    
    int                                     m_currentHouseId;
    

private:
    
    void sortMapPiece();
    
    virtual void	ButtonPress(int i_id);
    virtual void	ButtonDepress(int i_id);
    
    void            setupScreen();
    void            SetEditorEnabled(bool enable) { m_editorEnable = enable;}
    void            initLoadedWorldResources();
    MapEventItem*   GetMapEventItemAtLocation(const int& i_mouseX, const int& i_mouseY);
    
private:
    
    std::map<int,MapArtAnim>                m_artPopAnim;
    WorldMapList*                           m_UIMapList;
    std::vector<std::string>				m_loadingResourcesList;
    MapEventItem							m_editorCurrentEditItem;
    bool                                    m_editorEnable;
    KeyCode                                 m_keyCode;
    MapEventItem*                           m_currentMapPiece;
    uint16                                  m_selectItemID;
    Sexy::Point                             m_startPosition;
    Sexy::Point                             m_touchPosition;
    bool                                    m_dragging;
    int                                     m_currentLayer;
    int                                     m_maxLayer;
    int                                     m_currentId;
    int                                     m_eventType;
    
    bool                                    m_hide;
    
    std::vector<EditorButton>               m_editorButton;
    std::vector<EditorButton>               m_itemTypeButton;
    std::vector<EditorButton>               m_layerButton;
    std::vector<EditorButton>               m_eventTypeButton;
    std::vector<EditorButton>               m_eventIdButton;
    EditorButton                            m_editorLabel;
};


#endif /* defined(__PlantsVersusZombies2__MapEditor__) */
