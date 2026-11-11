//
//  UISingletonDialog.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/6/9.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _UISingletonDialog_h_
#define _UISingletonDialog_h_

#include "UIDialog.h"

template <class T>
class UISingletonDialog : public UI::Dialog, public NonCopyable
{
public:
	typedef UISingletonDialog<T> base_type;
public:
	UISingletonDialog() {}
	virtual ~UISingletonDialog() { if (m_pInstance == this) m_pInstance = NULL; }

public:
	static T*			ShowDialog();
	static void		CloseDialog();
	static T*			GetSingletonPtr() { return m_pInstance; }

private:
	static T*			m_pInstance;
};


template <class T>
T* UISingletonDialog<T>::m_pInstance = NULL;

template <class T>
T* UISingletonDialog<T>::ShowDialog()
{
	if (!m_pInstance)
	{
		m_pInstance = new T();
		if (!m_pInstance->OnCreate())
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}
	return m_pInstance;
}

template <class T>
void UISingletonDialog<T>::CloseDialog()
{
	if (m_pInstance)
	{
		m_pInstance->OnClose();
		m_pInstance = NULL;
	}
}

#endif
