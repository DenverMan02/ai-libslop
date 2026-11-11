/*
 * CustomLevelTemplate.h
 *
 *  Created on: 2021-11-23
 *      Author: admin
 */

#ifndef CUSTOMLEVELTEMPLATE_H_
#define CUSTOMLEVELTEMPLATE_H_

#include "CustomLevelCreator.h"
#include "CustomLevelConfig.h"

class CustomLevelMgr;

class CustomLevelTemplate
{
public:
	CustomLevelTemplate(CustomLevelMgr* i_manager);
	virtual ~CustomLevelTemplate() {}

	virtual bool GenerateTemplate(CustomLevelCreator& i_creator, const CustomLevelWorldParams& i_params, const CustomLevelConfig* i_config) = 0;

protected:
	CustomLevelMgr* getManager();

private:
	CustomLevelMgr* m_manager;
};

// Basic
class CustomLevelBasicTemplate : public CustomLevelTemplate
{
public:
	CustomLevelBasicTemplate(CustomLevelMgr* i_manager);
	virtual ~CustomLevelBasicTemplate() {}

	virtual bool GenerateTemplate(CustomLevelCreator& i_creator, const CustomLevelWorldParams& i_params, const CustomLevelConfig* i_config);

private:
	bool needDefaultModule(const std::string& i_moduleId, const CustomLevelWorldParams& i_params);
	bool needSunDropper(const CustomLevelWorldParams& i_params);
	bool needStandardIntro(const CustomLevelWorldParams& i_params);
	bool needZombieDeadWinCon(const CustomLevelWorldParams& i_params);
	bool needDefaultZombieWinCon(const CustomLevelWorldParams& i_params);
	bool needMowers(const CustomLevelWorldParams& i_params);

	void generateStageSpecificModules(CustomLevelCreator& i_creator, const std::string& i_stage, const CustomLevelConfig* i_config);
};

// Waves
class CustomLevelWaveAction
{
public:
	CustomLevelWaveAction();
	virtual ~CustomLevelWaveAction();

	virtual bool GenerateWaveAction(CustomLevelCreator& i_creator, const CustomWaveEvent& i_waveEvent, const CustomLevelConfig* i_config, std::vector<RtWeakPtr<class WaveActionProperties>>& i_actions) { return true; }
};

class CustomLevelWaveActionSandStorm : public CustomLevelWaveAction
{
public:
	CustomLevelWaveActionSandStorm();
	virtual ~CustomLevelWaveActionSandStorm() {}

	bool GenerateWaveAction(CustomLevelCreator& i_creator, const CustomWaveEvent& i_waveEvent, const CustomLevelConfig* i_config, std::vector<RtWeakPtr<class WaveActionProperties>>& i_actions) override;
};

class CustomLevelWaveActionSpiderRain : public CustomLevelWaveAction
{
public:
	CustomLevelWaveActionSpiderRain();
	virtual ~CustomLevelWaveActionSpiderRain() {}

	bool GenerateWaveAction(CustomLevelCreator& i_creator, const CustomWaveEvent& i_waveEvent, const CustomLevelConfig* i_config, std::vector<RtWeakPtr<class WaveActionProperties>>& i_actions) override;
};

class CustomLevelWaveActionPortal : public CustomLevelWaveAction
{
public:
	CustomLevelWaveActionPortal();
	virtual ~CustomLevelWaveActionPortal() {}

	bool GenerateWaveAction(CustomLevelCreator& i_creator, const CustomWaveEvent& i_waveEvent, const CustomLevelConfig* i_config, std::vector<RtWeakPtr<class WaveActionProperties>>& i_actions) override;
};

class CustomLevelWaveActionDinoRun : public CustomLevelWaveAction
{
public:
	CustomLevelWaveActionDinoRun();
	virtual ~CustomLevelWaveActionDinoRun() {}

	bool GenerateWaveAction(CustomLevelCreator& i_creator, const CustomWaveEvent& i_waveEvent, const CustomLevelConfig* i_config, std::vector<RtWeakPtr<class WaveActionProperties>>& i_actions) override;
};

class CustomLevelWaveActionRaidingParty : public CustomLevelWaveAction
{
public:
	CustomLevelWaveActionRaidingParty();
	virtual ~CustomLevelWaveActionRaidingParty() {}

	bool GenerateWaveAction(CustomLevelCreator& i_creator, const CustomWaveEvent& i_waveEvent, const CustomLevelConfig* i_config, std::vector<RtWeakPtr<class WaveActionProperties>>& i_actions) override;
};

class CustomLevelWaveActionFrostWind : public CustomLevelWaveAction
{
public:
	CustomLevelWaveActionFrostWind();
	virtual ~CustomLevelWaveActionFrostWind() {}

	bool GenerateWaveAction(CustomLevelCreator& i_creator, const CustomWaveEvent& i_waveEvent, const CustomLevelConfig* i_config, std::vector<RtWeakPtr<class WaveActionProperties>>& i_actions) override;
};

class CustomLevelWaveActionParachuteRain : public CustomLevelWaveAction
{
public:
	CustomLevelWaveActionParachuteRain();
	virtual ~CustomLevelWaveActionParachuteRain() {}

	bool GenerateWaveAction(CustomLevelCreator& i_creator, const CustomWaveEvent& i_waveEvent, const CustomLevelConfig* i_config, std::vector<RtWeakPtr<class WaveActionProperties>>& i_actions) override;
};

class CustomLevelWaveActionBlackHole : public CustomLevelWaveAction
{
public:
	CustomLevelWaveActionBlackHole();
	virtual ~CustomLevelWaveActionBlackHole() {}

	bool GenerateWaveAction(CustomLevelCreator& i_creator, const CustomWaveEvent& i_waveEvent, const CustomLevelConfig* i_config, std::vector<RtWeakPtr<class WaveActionProperties>>& i_actions) override;
};

class CustomLevelWaveTemplate : public CustomLevelTemplate
{
public:
	CustomLevelWaveTemplate(CustomLevelMgr* i_manager);
	virtual ~CustomLevelWaveTemplate();

	virtual bool GenerateTemplate(CustomLevelCreator& i_creator, const CustomLevelWorldParams& i_params, const CustomLevelConfig* i_config) override;

private:
	void initActions();
	void generateWaves(CustomLevelCreator& i_creator, const CustomWaveData& i_waveData, const CustomLevelConfig* i_config);
	void generateWave(CustomLevelCreator& i_creator, const std::vector<CustomWaveZombie>& i_zombies, const CustomWaveEvent& i_waveEvent, int i_plantfood,
			const CustomLevelConfig* i_config);

private:
	class WaveManagerModuleProperties* m_waveManager;
	std::vector<CustomLevelWaveAction*> m_actions;
};


// SeedBank
class CustomLevelSeedBankTemplate : public CustomLevelTemplate
{
public:
	CustomLevelSeedBankTemplate(CustomLevelMgr* i_manager);
	virtual ~CustomLevelSeedBankTemplate() {}

	virtual bool GenerateTemplate(CustomLevelCreator& i_creator, const CustomLevelWorldParams& i_params, const CustomLevelConfig* i_config) override;

private:
	bool CheckPresetListEmptyValue(const std::vector<std::string>& i_infos);
	bool needCreateModule(const CustomLevelWorldParams& i_params);
};

// Challenges
class CustomLevelChallengeTemplate : public CustomLevelTemplate
{
public:
	CustomLevelChallengeTemplate(CustomLevelMgr* i_manager);
	virtual ~CustomLevelChallengeTemplate() {}

	virtual bool GenerateTemplate(CustomLevelCreator& i_creator, const CustomLevelWorldParams& i_params, const CustomLevelConfig* i_config) override;
	virtual bool GenerateDetails(CustomLevelCreator& i_creator, const CustomLevelWorldParams& i_params, const CustomLevelConfig* i_config,
			RtWeakPtr<const LevelModuleProperties> i_modules) { return true; }
private:
	const std::vector<std::string> GetDefaultDescriptions(const CustomLevelWorldParams& i_params);
};

class CustomLevelChallengeLastStandTemplate : public CustomLevelTemplate
{
public:
	CustomLevelChallengeLastStandTemplate(CustomLevelMgr* i_manager);
	virtual ~CustomLevelChallengeLastStandTemplate() {}

	bool GenerateTemplate(CustomLevelCreator& i_creator, const CustomLevelWorldParams& i_params, const CustomLevelConfig* i_config) override;
};

class CustomLevelChallengeMoldsTemplate : public CustomLevelTemplate
{
public:
	CustomLevelChallengeMoldsTemplate(CustomLevelMgr* i_manager);
	virtual ~CustomLevelChallengeMoldsTemplate() {}

	bool GenerateTemplate(CustomLevelCreator& i_creator, const CustomLevelWorldParams& i_params, const CustomLevelConfig* i_config) override;
};

class CustomLevelChallengeStatueMazeTemplate : public CustomLevelTemplate
{
public:
	CustomLevelChallengeStatueMazeTemplate(CustomLevelMgr* i_manager);
	virtual ~CustomLevelChallengeStatueMazeTemplate() {}

	bool GenerateTemplate(CustomLevelCreator& i_creator, const CustomLevelWorldParams& i_params, const CustomLevelConfig* i_config) override;
};

class CustomLevelChallengeEvilDaveTemplate : public CustomLevelTemplate
{
public:
	CustomLevelChallengeEvilDaveTemplate(CustomLevelMgr* i_manager);
	virtual ~CustomLevelChallengeEvilDaveTemplate() {}

	bool GenerateTemplate(CustomLevelCreator& i_creator, const CustomLevelWorldParams& i_params, const CustomLevelConfig* i_config) override;
};

class CustomLevelChallengeTowerDefendTemplate : public CustomLevelTemplate
{
public:
	CustomLevelChallengeTowerDefendTemplate(CustomLevelMgr* i_manager);
	virtual ~CustomLevelChallengeTowerDefendTemplate() {}

	bool GenerateTemplate(CustomLevelCreator& i_creator, const CustomLevelWorldParams& i_params, const CustomLevelConfig* i_config) override;
	void generateWave(CustomLevelCreator& i_creator, const std::vector<TowerDefendWaveZombie>& i_zombies, const CustomLevelConfig* i_config, class WaveGeneratorProperties* i_waveGenerator);
};

class CustomLevelChallengeSingleHandedTemplate : public CustomLevelTemplate
{
public:
	CustomLevelChallengeSingleHandedTemplate(CustomLevelMgr* i_manager);
	virtual ~CustomLevelChallengeSingleHandedTemplate() {}

	bool GenerateTemplate(CustomLevelCreator& i_creator, const CustomLevelWorldParams& i_params, const CustomLevelConfig* i_config) override;
	void generateWave(CustomLevelCreator& i_creator, const std::vector<SingleHandedWaveZombie>& i_zombies, bool i_plantfood, const CustomLevelConfig* i_config, class WaveGeneratorProperties* i_waveGenerator);
};

class CustomLevelChallengeVaseBreakerTemplate : public CustomLevelTemplate
{
public:
	CustomLevelChallengeVaseBreakerTemplate(CustomLevelMgr* i_manager);
	virtual ~CustomLevelChallengeVaseBreakerTemplate() {}

	bool GenerateTemplate(CustomLevelCreator& i_creator, const CustomLevelWorldParams& i_params, const CustomLevelConfig* i_config) override;
};

// Elements
class CustomLevelElementsTemplate : public CustomLevelTemplate
{
public:
	CustomLevelElementsTemplate(CustomLevelMgr* i_manager);
	virtual ~CustomLevelElementsTemplate() {}

	virtual bool GenerateTemplate(CustomLevelCreator& i_creator, const CustomLevelWorldParams& i_params, const CustomLevelConfig* i_config) override;

private:
	void UpdateRailInfos(const std::vector<RailInfo>& i_infos, std::vector<RailInfo>& i_resultInfos);
	void UpdateRailInfo(RailInfo& i_info, std::vector<RailInfo>& i_resultInfos);
};

#endif /* CUSTOMLEVELTEMPLATE_H_ */
