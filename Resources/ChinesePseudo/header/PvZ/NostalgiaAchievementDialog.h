#ifndef NostalgiaAchievementDialog_H
#define NostalgiaAchievementDialog_H

#include "Singleton.h"
#include "SlidingWidget.h"
#include "SexyAppFramework/Image.h"

class NostalgiaAchievementDialog : public SlidingWidget
{
public:
	RT_CLASS_DEFINE(NostalgiaAchievementDialog, UIWidget, RtClass);

    NostalgiaAchievementDialog();
    ~NostalgiaAchievementDialog();

    virtual void Draw(Sexy::Graphics* i_g) override;
    void InitView(const std::string& i_image, const std::string& i_name);
    void SetDescription(const SexyString& i_description);

protected:
	virtual void onUpdate() override;
    virtual void onSlideInFinished() override;
	virtual void onSlideOutFinished() override;
    virtual void onDestroy() override;

private:
    int m_type;
    bool m_normalDestroy;
    Sexy::Image* m_icon;
    SexyString m_name;
    pvztime_t m_timer;
};


class NostalgiaAchievementDialogManager : public LazySingleton<NostalgiaAchievementDialogManager>
{
public:
    NostalgiaAchievementDialogManager();

    void PlantKillZombie(const std::string& i_plantName, const std::string& i_zombieName);
    void NostalgiaAchievementFinish(const class PvZ1Achievement* i_achievement);
    void StartNext(NostalgiaAchievementDialog* i_current);

private:
    void StartSliding();
    bool m_canStart;
    std::vector<NostalgiaAchievementDialog*> m_queue;
};

#endif