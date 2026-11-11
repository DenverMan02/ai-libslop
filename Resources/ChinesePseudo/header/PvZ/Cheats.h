#ifndef PVZ2_CHEATS_H
#define PVZ2_CHEATS_H

#include "Core.h"
#include "RtObject.h"
#include "RtDelegate.h"
#include "SexyAppFramework/drivers/crashtracking/CrashTracking.h"
#include "GameEventMgr.h"

namespace Message
{
    void CheatSystemInvalidated();
    void CheatActivated(const std::string& i_cheatName);
};

/// Base Cheat class

enum CheatContext
{
	PVZ_BEGIN_FLAG_ENUM(CHEATCONTEXT_),
	PVZ_FLAG(CHEATCONTEXT_Initial),
	PVZ_FLAG(CHEATCONTEXT_MainMenu),
	PVZ_FLAG(CHEATCONTEXT_Board),
	PVZ_FLAG(CHEATCONTEXT_WorldMap),
	PVZ_FLAG(CHEATCONTEXT_Almanac),
    PVZ_FLAG(CHEATCONTEXT_Store),
    PVZ_FLAG(CHEATCONTEXT_Adventure),
	PVZ_END_FLAG_ENUM(CHEATCONTEXT_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(CheatContext);

class Cheat : public RtObject
{
public:
	RT_CLASS_DEFINE(Cheat, RtObject, RtClass) {}

	/// Creation / Initialization
	Cheat()
		: m_validContexts(CHEATCONTEXT_Everything)
		, m_keyboardShortcut(0)
	{}
	Cheat(const std::string& i_name)
		: m_name(i_name)
		, m_validContexts(CHEATCONTEXT_Everything)
		, m_keyboardShortcut(0)
	{}
	
	/// Initialization Chain
	Cheat* SetValidContexts(CheatContext i_context);
	CheatContext GetValidContexts() const;
	
	Cheat* SetKeyboardShortcut(char i_key);
	char GetKeyboardShortcut() const;
	
	/// Accessors
	const std::string& GetName()  const {
		return m_name;
	}
	
private:
	std::string m_name;
	CheatContext m_validContexts;
	char m_keyboardShortcut;
};

/// Cheat Impls

class CheatToggle : public Cheat
{
public:
    RT_CLASS_DEFINE(CheatToggle, Cheat, RtClass) {}
    
    CheatToggle()
    : Cheat()
    , m_value(false)
    {}
    
    CheatToggle(const std::string& i_name, const bool i_value=false)
    : Cheat(i_name)
    , m_value(i_value)
    {}
    
    virtual bool GetValue() const {
        return m_value;
    }
    virtual void SetValue(bool i_newValue) {
        m_value = i_newValue;
        BroadcastMessage(Message::CheatActivated, GetName());
        CrashTracking::Log(StrFormat("PVZ_T: %f - [CHEAT] Cheat Toggled: %s with Value: %s", PVZ_T(), GetName().c_str(), m_value ? "true" : "false"));
    }
    virtual bool Toggle() {
        bool origValue = GetValue();
        SetValue(!origValue);
        
        return GetValue();
    }
    
protected:
    bool m_value;
};

class CheatToggleAction : public CheatToggle
{
public:
    RT_CLASS_DEFINE(CheatToggleAction, CheatToggle, RtClass) {}
    
    CheatToggleAction(): CheatToggleAction{std::string(), nullptr, false} {}
    CheatToggleAction(const std::string& i_name, std::function<void(bool)>&& i_action, const bool i_value = false)
    : CheatToggle{i_name, i_value}
    , m_action{std::move(i_action)}
    {
        
    }
    
    bool Toggle() override
    {
        auto origValue = m_value;
        auto newValue = SuperClass::Toggle();
        if (origValue != newValue)
        {
            m_action(newValue);
        }
        
        return m_value;
    }
    
private:
    std::function<void(bool)> m_action;
};

class CheatCommand : public Cheat
{
public:
    RT_CLASS_DEFINE(CheatCommand, Cheat, RtClass) {}
    
    CheatCommand()
    {}
    
    CheatCommand(const std::string& i_name, Delegate0 i_onActivate)
    : Cheat(i_name)
    , m_onActivate(i_onActivate)
    {}
    
    using CommandHandler = std::function<void()>;
    CheatCommand(const std::string& i_name, CommandHandler&& i_onActivate)
    : Cheat(i_name)
    , m_onActivate(std::move(i_onActivate))
    {}
    
    const CommandHandler& GetCommand() const {
        return m_onActivate;
    }
    
private:
    std::function<void()> m_onActivate;
};

/// Cheat Manager
class CheatManager : public LazySingleton<CheatManager>
{
public:
	CheatManager()
		: m_currentContext(CHEATCONTEXT_Initial)
	{}
	
	Cheat* AddCheat(Cheat* i_cheat);
	Cheat* GetCheat(const std::string& i_name) const;
	Cheat* GetCheatIgnoreContext(const std::string& i_name) const;
    
    void SetCheatCachedText(const std::string& i_name, const std::string& i_text);
    const std::string GetCheatCachedText(const std::string& i_name, const std::string& i_defaultText);
    void AddCheatCachedLog(const std::string& i_name, const std::string& i_text, int i_maxLines);
	
	void SetCurrentContext(CheatContext i_context);
	CheatContext GetCurrentContext() const;
	bool IsCheatValidForCurrentContext(Cheat* i_cheat) const;
	
	void CheckShortcuts();
	
	/// Shortcuts
	float GetVariableValue(const std::string& i_name) const;
	void SetVariableValue(const std::string& i_name, float i_newValue);
	bool GetToggleValue(const std::string& i_name) const;
	bool SetToggleValue(const std::string& i_name, bool i_newValue);
	bool ToggleCheat(const std::string& i_name);
	void DoCheatCommand(const std::string& i_name) const;
	
	bool ActivateCheatForKeyboardShortcut(char i_key);
	
private:
    std::string trimToMaxLines(const std::string& i_text, int i_maxLines);
    
    std::map<std::string, std::string> m_cheatCachedText;		// Text blocks we can cache from snapshots of other systems for easy retrieval
	std::map<std::string, Cheat*> m_cheats;
	CheatContext m_currentContext;
};

#define gCheats (CheatManager::GetInstancePtr())

#endif
