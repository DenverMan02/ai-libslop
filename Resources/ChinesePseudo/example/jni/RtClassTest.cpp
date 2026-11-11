#include "RtClassTest.h"
#include "ReflectionBuilder.h"
#include "Board.h"

RT_CLASS_IMPLEMENT(TestIntroModule)
void TestIntroModule::StaticClassInit()
{
    REFLECTION_CLASSBUILDER_BEGIN(TestIntroModule);
    REFLECTION_CLASSBUILDER_RTCLASS_BIND;
    REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntro);

        REFLECTION_CLASSBUILDER_FIELD(PlantPtr, m_testPlant);

    REFLECTION_CLASSBUILDER_END(TestIntroModule);
}

void TestIntroModule::registerForEvents()
{
    StandardLevelIntro::registerForEvents();

    gMessageRouter->Subscribe(Message::ZombieDied, MakeDelegate(*this, &TestIntroModule::onZombieDied));
}

void TestIntroModule::onZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow)
{
    if (i_zombie == m_testZombie) {
        //gLawnApp->m_board->Quit();
        gLawnApp->m_board->AddZombie("chicken", 1, 0, 2)->SetFacing(ZombieFacing::ZFACING_Right);
    }
}

void TestIntroModule::startLevelIntro(PanType i_startingPanType, bool i_special)
{
    StandardLevelIntro::startLevelIntro(i_startingPanType, i_special);

    m_testPlant = gLawnApp->m_board->AddPlant(1, 2, gPlantTypeMgr->GetTypeFromTypeName("peashooter"), true, true, 3)->GetPtr();
    m_testZombie = gLawnApp->m_board->AddZombie("egypt_gargantuar", 10, 7, 2)->GetPtr();
}

void TestIntroModule::onStandardIntroComplete()
{
    if (m_testPlant.IsValid()) {
        m_testPlant->GetPlantFramework<PlantPeashooter>()->ApplyPlantfood();
        m_testZombie->SetFacing(ZombieFacing::ZFACING_Right);
    }
}

RT_CLASS_IMPLEMENT(TestIntroProperties)
void TestIntroProperties::StaticClassInit()
{
    REFLECTION_CLASSBUILDER_BEGIN(TestIntroProperties);
    REFLECTION_CLASSBUILDER_RTCLASS_BIND;
    REFLECTION_CLASSBUILDER_ANCESTOR(StandardLevelIntroProperties);

        REFLECTION_CLASSBUILDER_FIELD(bool, NewBoolField);
        REFLECTION_CLASSBUILDER_FIELD(std::string, NewStringField);

    REFLECTION_CLASSBUILDER_END(TestIntroProperties);
}
