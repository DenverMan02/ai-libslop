#ifndef __SEXYAPPFRAMEWORK_POPLOC_H__
#define __SEXYAPPFRAMEWORK_POPLOC_H__

#include "Common.h"

#define _(str)			gSexyAppBase->GetString(str, _S(str))			// backwards-compatible
#define _ID(str, id)	gSexyAppBase->mPopLoc.GetString(id, _S(str))	// new approach.

namespace Sexy
{
	class PopLoc
	{
		typedef std::map<int, SexyString>		IdToStringMap;
		typedef std::map<SexyString, SexyString> NameToStringMap;

		IdToStringMap			mIdStrings;
		NameToStringMap			mNameStrings;

	public:
		PopLoc(void);
		~PopLoc(void);

		//----------------------------------------------------------------
		// GetString will search the localization map by id or name and return
		// a string if found. If the map contains no such id or name, theDefaultString
		// will be returned instead.
		//
		// Name is case insensitive.
		//----------------------------------------------------------------
		SexyString				GetString(const int theId, const SexyString& theDefaultString) const;
		SexyString				GetString(const SexyString& theName, const SexyString& theDefaultString) const;

		//----------------------------------------------------------------
		// SetString will insert a string into the map based searchable by
		// id or name. If a string already exists with that id or name, 
		// SetString will return false.
		// If reset is set to true, previous values will be removed, and the
		// new one inserted in its place.
		//
		// Name is case insensitive.
		//----------------------------------------------------------------
		bool					SetString(const int theId, const SexyString& theString, bool reset=false);
		bool					SetString(const SexyString& theName, const SexyString& theString, bool reset=false);

		//----------------------------------------------------------------
		// RemoveString will remove a string by id or name from the map. true is
		// returned if and only if the string is removed.
		//
		// Name is case insensitive.
		//----------------------------------------------------------------
		bool					RemoveString(const int theId);
		bool					RemoveString(const SexyString& theName);

		//----------------------------------------------------------------
		// Evaluate will replace instances of "%StringName%" with the value
		// found in the map.  If StringName is not found, the empty string
		// is used instead. If StringName evaluates to an integer, the 
		// id-based map will be checked first.
		// 
		// %% is used to mean %. %%%% means %%. And so on.
		// Take care to not do dumb things like Foo = Bar %Foo%
		// You will create an infinite loop in Evaluate as it keeps expanding
		// the string to Bar Bar Bar Bar ... %Foo% and evaluating the last %Foo%
		//----------------------------------------------------------------
		SexyString				Evaluate(const SexyString& theInput) const;
	};
}

#endif // #ifndef __SEXYAPPFRAMEWORK_POPLOC_H__
