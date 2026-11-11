#ifndef __TYPINGCHECK_H__
#define __TYPINGCHECK_H__

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/KeyCodes.h"

class TypingCheck
{
protected:
	std::string m_phrase;
	std::string m_recentTyping;

public:
	TypingCheck();
	TypingCheck(const std::string &i_phrase);
	void SetPhrase(const std::string &i_phrase);
	void AddKeyCode(Sexy::KeyCode i_code);
	void AddChar(char i_char);

	bool Check(Sexy::KeyCode i_code);
	bool Check(char i_char);
};

#endif
