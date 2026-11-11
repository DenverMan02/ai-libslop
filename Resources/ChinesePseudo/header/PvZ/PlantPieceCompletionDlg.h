//
//  PlantPieceCompletionDlg.hpp
//  PlantsVersusZombies2
//
//  Created by shizf on 16/5/11.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef PlantPieceCompletionDlg_h
#define PlantPieceCompletionDlg_h

#include "UISingletonDialog.h"
#include "PVZTypes.h"
#include "MagentoService.h"

class PlantPieceCompletionDlg : public UISingletonDialog<PlantPieceCompletionDlg>
{
public:
    PlantPieceCompletionDlg();
    virtual ~PlantPieceCompletionDlg();
    
    virtual bool            OnCreate() override;
    virtual void            OnClose() override;
    virtual std::string     GetLayoutName() override { return "PlantPieceCompletion"; }
    virtual void            Draw(Sexy::Graphics* i_g) override;
    virtual void            DrawAll(Sexy::ModalFlags *i_flags, Sexy::Graphics *i_g) override;
    
    // ButtonListener
    virtual void            ButtonDepress(int i_id) override;
    
    
    void                    setPlantPiece(PlantTypePtr i_plant,int i_num);
    
private:
    void                    onItemPurchasedFromStore(MagentoProductProps* i_props);
    void                    buySuccess();
    void                    onDialogClose();
    
private:
    PlantTypePtr m_plant;
    MagentoProductPropsPtr m_product;
};

namespace Message
{
    void PlantPieceCompletionClosed();
}

#endif /* PlantPieceCompletionDlg_h */
