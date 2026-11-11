/*
 * WorldMapWelfareChooseDialog.h
 *
 *  Created on: 2021-3-31
 *      Author: Administrator
 */

#ifndef WORLDMAPWELFARECHOOSEDIALOG_H_
#define WORLDMAPWELFARECHOOSEDIALOG_H_


class WorldMapWelfareChooseDialog : public Widget, Sexy::ButtonListener, public InterfaceChooseDialog
{
public:
	WorldMapWelfareChooseDialog(int activityIndex);
    ~WorldMapWelfareChooseDialog();

    virtual void    ButtonPress(int i_id);
    virtual void	ButtonDepress(int i_id);
    virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(ModalFlags* theFlags, Graphics* i_g);

public:
    virtual void InitView();
    virtual float GetItemLeftMargin();
    virtual float GetItemHInterval();
    virtual float GetItemRightMargin();
    virtual int GetBaseHeight();
    virtual int GetPanelHeight();
    virtual int GetItemCount();
    virtual UIWidget * GetAssociatedMainWidget();
    void    OnOK();
    
    bool GetHomeActivityPos(HomeActityType id, SexyVector2& pos) override;

protected:
    virtual void PrepareActivityConfig();
    virtual void FillState();
    virtual int LayoutItems();

private:
    void onCloseDialog();

private:
    //std::unordered_map<int, PVZ2UIButton *> m_btnMap;
    //std::unordered_map<int, std::string> m_resNameMap;
    std::unordered_map<int, uint8_t> m_openStateMap;
    std::unordered_map<int, uint8_t> m_attachStateMap;
    std::vector<int> m_activityOrderList;
    int             m_iBgWidth;
    int             m_iBgHeight;

private:
    int             m_anniversaryAttachState = 0;
};



#endif /* WORLDMAPWELFARECHOOSEDIALOG_H_ */
