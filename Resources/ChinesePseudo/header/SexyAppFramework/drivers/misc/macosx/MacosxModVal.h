#ifndef MACOSXMODVAL_H_INCLUDED
#define MACOSXMODVAL_H_INCLUDED



namespace Sexy 
{
#if (SEXY_IS_MODVALS_ENABLED && SEXY_IS_MODVALS_LEGACY_ENABLED)
    class MacosxAppDriver;
	
	bool InitializeMacosxModValSystem(MacosxAppDriver*);
	bool DestroyMacosxModValSystem();
    bool ReparsesModValues();   //Bokun Zhao changed function name, original bool ReparseModValues(), to avoid redefinition in namespace Sexy
	
#endif // (SEXY_IS_MODVALS_ENABLED && SEXY_IS_MODVALS_LEGACY_ENABLED)
}

#endif