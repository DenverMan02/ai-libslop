#ifndef __SEXYAPPFRAMEWORK_VISTAUPGRADEFILEMOVER_H__
#define __SEXYAPPFRAMEWORK_VISTAUPGRADEFILEMOVER_H__

namespace Sexy
{
	class VistaUpgradeFileMover
	{
		struct FileData
		{
			std::string		mSource;
			std::string		mDest;
		};
		typedef std::list<FileData> FileDataList;


		FileDataList		mFiles;
		
	public:
		VistaUpgradeFileMover(void);
		~VistaUpgradeFileMover(void);

		void				AddPath(const std::string& theSource);
		void				MoveFiles();
	};
}

#endif // #ifndef __SEXYAPPFRAMEWORK_VISTAUPGRADEFILEMOVER_H__
