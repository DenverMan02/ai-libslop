#pragma once

template <typename T>
class ObjectTypeDirectory
{
public:
	void** vftable;
	std::map<SexyString, Sexy::RtWeakPtr<T>*> m_typeMap;

	inline Sexy::RtWeakPtr<T> GetTypeByName(const SexyString& typeName)
	{
		Sexy::RtWeakPtr<T> weakPtr;
		auto type = m_typeMap.find(typeName);
		if (type != m_typeMap.end()) weakPtr = type->second;
		return weakPtr;
	}
};