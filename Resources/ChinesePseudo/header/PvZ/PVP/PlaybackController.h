//
//  PlaybackController.h
//  PlantsVersusZombies2
//
//  Created by Emma on 2016.5.4
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlaybackController_h
#define PlantsVersusZombies2_PlaybackController_h

enum PlaybackAddParamsType
{
	PlaybackAddParams_Invalid = 0,
	PlaybackAddParams_Food = 1,
	PlaybackAddParams_Rage = 2,
    PlaybackAddParams_ThrowBone = 3,
    PlaybackAddParams_FireImp = 4,
};
class PlaybackController
{
public:
	PlaybackController();
	~PlaybackController();

	int		GetEntityID() const { return m_EntityID; }
	void		SetEntityID(int iVal) { m_EntityID = iVal; }

	bool		IsPlaying() const { return m_bPlaying; }
	void		SetPlaying(bool setting) { m_bPlaying = setting; }
    bool    IsAccessory() const { return m_bAccessory; }
    void    SetAccessory(bool setting) { m_bAccessory = setting; }

	void		SetParam(uint8 iKey, const std::string& strValue);
	void		SetParam(uint8 iKey, int iValue);
	void		SetParam(uint8 iKey, float fValue);
	void		SetParam(uint8 iKey, const SexyVector3& pos);
    void		SetParam(uint8 iKey, const Sexy::Point& pt);
	const std::string&		GetParam(uint8 iKey);
	int			GetParamInt(uint8 iKey);
	float		GetParamFloat(uint8 iKey);
    SexyVector3 GetParamVector3(uint8 iKey);
    Sexy::Point GetParamPoint(uint8 iKey);
    void    RemoveParam(uint8 iKey);
	const std::map<uint8, std::string>& GetParams() const { return m_params; }
	void		ClearParams();
    
    void    RegisterFireGird(Delegate1<const Sexy::Point&> i_event);
    void    RegisterFirePosition(Delegate1<const SexyVector3&> i_event);

protected:
	std::map<uint8, std::string>	m_params;
	int			m_EntityID = 0;
	bool		m_bPlaying = false;
    bool    m_bAccessory = false;       // check if is spawned by another zombie.
};



#endif
