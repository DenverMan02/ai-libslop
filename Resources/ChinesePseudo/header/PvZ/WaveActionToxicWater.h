#ifndef WaveActionToxicWater_h_
#define WaveActionToxicWater_h_

#include "Wave.h"
#include "Zombie.h"

//struct ToxicWaterData
//{
//	ToxicWaterData()
//	{
//		Column = 8;
//		Row = 4;
//		ThrowColumn =1;
//		ThrowRow = 1;
//		Damage = 333;
//    }
//
//	int 			Column;
//	int				Row;
//	int 			ThrowColumn;
//	int				ThrowRow;
//	float 			Damage;
//};


class WaveActionToxicWater : public WaveAction
{
public:
	RT_CLASS_DEFINE(WaveActionToxicWater, WaveAction, RtClass);

	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
    void WaveEnd(int i_waveNumber, Sexy::MTRand &i_random) override;

    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;


};

class WaveActionToxicWaterProps : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(WaveActionToxicWaterProps, WaveActionProperties, RtClass);

	WaveActionToxicWaterProps() {}
	RtClass* GetActionClass() const override { return WaveActionToxicWater::StaticGetClass(); }
	int 			Column = 9;
	int				Row = 1;
	int 			ThrowColumn =1;
	int				ThrowRow =1;
	float 			Damage =1;
	int 			WaveNum = 2 ;
//	ToxicWaterData ToxicWaters;
};

//Pool Terrain change
class WaveActionPoolTerrainChange : public WaveAction
{
public:
	RT_CLASS_DEFINE(WaveActionPoolTerrainChange, WaveAction, RtClass);

	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
    void WaveEnd(int i_waveNumber, Sexy::MTRand &i_random) override;

    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
//    void onStartEnd(Point i_Point);
//    void onLoopEnd(Point i_Point);

};

class WaveActionPoolTerrainChangeProps : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(WaveActionPoolTerrainChangeProps, WaveActionProperties, RtClass);

	WaveActionPoolTerrainChangeProps() {}
	RtClass* GetActionClass() const override {
		return WaveActionPoolTerrainChange::StaticGetClass(); }

	std::vector<Point> UpPoint;
	std::vector<Point> DownPoint;
//	ToxicWaterData ToxicWaters;
};

#endif /* WaveActionToxicWater_h_ */
