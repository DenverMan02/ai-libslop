#ifndef PolygonCheckWidget_H
#define PolygonCheckWidget_H

#include "Widget.h"

class PolygonCheck
{
public:
    void registerPolygonCheck(int i_id, const std::vector<Sexy::Point>& i_pointList);
    int doCheck(const Sexy::Point& i_point, int i_defalutResult = -1);

public:
    static bool IsPointInPolygon(Point i_point, const std::vector<Point>& i_list);

protected:
    std::map<int, std::vector<Sexy::Point>> m_polygonCheckMap;
};

class PolygonCheckWidget : public Widget, public PolygonCheck
{
public:
    PolygonCheckWidget();

	virtual void DrawAll(ModalFlags* i_theFlags, Graphics* i_g) override;

    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchMoved(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
	virtual void TouchesCanceled() override;

    virtual void onTouchBegan(int i_id);
    virtual void onTouchMoved(int i_id);
    virtual void onTouchEnded(int i_id);
    virtual void onTouchesCanceled();

protected:
    int m_beganTouchID;
    bool m_touchOverFlag;

    std::vector<Sexy::Point> m_debugPolygon;
};

#endif