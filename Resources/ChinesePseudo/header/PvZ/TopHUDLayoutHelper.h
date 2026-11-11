//
//  TopHUDLayoutHelper.h
//  PvZ2
//
//  Created by Sola, Joseph on 10/17/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef TopHUDLayoutHelper_h
#define TopHUDLayoutHelper_h

#include <vector>
#include <string>

struct TopHUDLayoutHelperParams
{
    std::vector<std::string> TopLeftWidgets;
    std::vector<std::string> TopRightWidgets;
    bool ShowEASquaredButtons = false;
	bool ShowLODEventBar = false;
    std::string MetricsContext;
};

class TopHUDLayoutHelper
{
public:
    void ConfigureTopHUD(const TopHUDLayoutHelperParams& i_params);
    
private:
    void LayoutWidgetsFromTopLeft(const std::vector<std::string>& i_widgetNameList);
    void LayoutWidgetsFromTopRight(const std::vector<std::string>& i_widgetNameList);
    void ShowEASquaredButtons();
    void HideEASquaredButtons();
    void SetMetricsContext(const std::string& i_metricsContext);
	void ShowLODEventBar();
};

#endif /* TopHUDLayoutHelper_h */
