//
//  JoustStage.h
//  PvZ2
//
//  Created by Sola, Joseph on 10/4/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef JoustStage_h
#define JoustStage_h

#include "RtObject.h"
#include "StageModule.h"

namespace Sexy {
    class Graphics;
}  // namespace Sexy

class JoustStage : public StageModule
{
public:
    RT_CLASS_DEFINE(JoustStage, StageModule, RtClass);

protected:
    void registerForEvents() override;

private:
    void findMultiplierValues();
    void addFlagOverlayToRenderQueue(class RenderQueue* i_queue);
    void renderFlagOverlay(Graphics* i_g);
    void drawMultiplierLabel(Graphics* i_g, PrimeTypeface* i_font, int i_x, int i_y, const Color& i_color, float i_multiplier);
    
    std::vector<float> m_scoreMultipliers;
};

class JoustStageProperties : public StageModuleProperties
{
public:
    RT_CLASS_DEFINE(JoustStageProperties, StageModuleProperties, RtClass);
    
    JoustStageProperties()
    : DrawMultiplierOverlay(false)
    , DrawMultiplierLabels(false)
    {}
    
    RtClass* GetModuleClass() const override
    {
        return JoustStage::StaticGetClass();
    }
    
    bool DrawMultiplierOverlay;
    bool DrawMultiplierLabels;
};

#endif /* JoustStage_h */
