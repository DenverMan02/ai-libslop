#ifndef __UILISTENER_H__
#define __UILISTENER_H__

class UIWidgetRadio;
namespace UI
{

    class RadioListener
    {
    public:
        virtual void RadioSelectionChanged(class UIWidgetRadio* pRadioBtn) = 0;
    };
    
    class TabControlListener
    {
    public:
        virtual void TabSelectionChanged(int tabID) {}
    };
    
    class PageListener
    {
    public:
        virtual void PageChanged() {}
    };

}

#endif //__UILISTENER_H__
