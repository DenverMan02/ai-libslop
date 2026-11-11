//
//  PackageContentsProvider.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 2/12/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PackageContentsProvider__
#define __PlantsVersusZombies2__PackageContentsProvider__

#include <string>

namespace Message
{
	void PackageContentsChanged(const std::string& i_packagePath);
};

class PackageContentsProvider
{
public:
	PackageContentsProvider(const std::string& i_defaultPackagePath, const std::string& i_overridePackagePath)
		: m_defaultPackagePath(i_defaultPackagePath), m_overridePackagePath(i_overridePackagePath)
	{}
	
	// Returns a path to the most up to date RTON source for the given relative package path.
	// Note that this is not guaranteed to return a valid absolute filename path that can be found on disk!
	// You should use SexyAppBase::ReadBufferFromFile to read it, as this will properly resolve
	// data that lives in the resident RSB memory. 
	bool GetPackageContentsPath(const std::string& i_packagePath, std::string& o_absolutePath) const;

	// Converts the given JSON to RTON and saves it as the current source for the given relative package path
	bool OverridePackageContentsWithJSON(const std::string& i_packagePath, const std::string& i_newJSON) const;
	
	// Removes any override RTON for the given relative package path
	bool ClearOverridePackageFor(const std::string& i_packagePath) const;
	// Removes all override RTON for all packages in our override package folder
	void ClearOverridePackageFolder() const;
	
private:
	std::string getDefaultPackagePath(const std::string& i_packagePath) const;
	std::string getOverridePackagePath(const std::string& i_packagePath) const;
	std::string getPackagePathFromAbsoluteDefaultPath(const std::string& i_absolutePath) const;
	std::string getPackagePathFromAbsoluteOverridePath(const std::string& i_absolutePath) const;
	
	std::string cleanPackagePath(const std::string& i_packagePath) const;
	std::string cleanAbsolutePath(const std::string& i_path) const;
		
	bool findDefaultPackageFor(const std::string& i_packagePath, std::string& o_defaultPath) const;
	bool findOverridePackageFor(const std::string& i_packagePath, std::string& o_overridePath) const;
	
	std::string m_defaultPackagePath;
	std::string m_overridePackagePath;
};

#endif /* defined(__PlantsVersusZombies2__PackageContentsProvider__) */
