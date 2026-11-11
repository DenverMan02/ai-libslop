#ifndef PS3_ERRORS_H_INCLUDED
#define PS3_ERRORS_H_INCLUDED

#define MODAL_RETRY_DIALOG_ID 0xFFFFF00D

enum PS3ErrorCode
{
	ERROR_PROFILE_READ,
	ERROR_SAVEGAME_NOT_OWNER,
	ERROR_SAVEGAME_SAVING,
	ERROR_SAVEGAME_LOADING,
	ERROR_SAVEGAME_DELETING,
	ERROR_SAVEGAME_CORRUPT,
	ERROR_ONLINE_DISABLED_PARENTAL_CONTROL
};

#define ERROR_TITLE(code) gSexyAppBase->GetString("PS3_"#code"_TITLE",StrFormat(L"%S","PS3_"#code"_TITLE"))
#define ERROR_TEXT(code) gSexyAppBase->GetString("PS3_"#code,StrFormat(L"%S","PS3_"#code))
#define ERROR_FOOTER(code) gSexyAppBase->GetString("PS3_"#code"_FOOTER",StrFormat(L"%S","PS3_"#code"_FOOTER"))

#endif
