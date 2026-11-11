#pragma once
#ifndef __REFPEFILES_H__
#define __REFPEFILES_H__
//****************************************************************************
//**
//**  File     :  REFPEFILES.H
//**  Summary  :  Header - Reflection - PE Executables
//**
//----------------------------------------------------------------------------
//**       $Id:$ 
//** $DateTime:$ 
//**   $Author:$ 
//**   $Change:$ 
//****************************************************************************
#ifdef SUPPORT_REF_PEFILES

//============================================================================
//    HEADERS
//============================================================================

namespace Reflection {
//============================================================================
//    DEFINITIONS / ENUMERATIONS / SIMPLE TYPEDEFS
//============================================================================
// PE magic numbers
enum
{
	PE_DOSHEADER_MAGIC		= (('M')+(('Z')<<8)), // "MZ"
	PE_DOSHEADER_SIGOFFSET	= 60, // offset in dos header of offset of start of PE header
	PE_HEADER_MAGIC			= (('P')+(('E')<<8)), // "PE"
	PE_HEADER_OPTMAGIC		= 0x010b // PE optional header signature
};

// PE header machine types
enum
{
	PEHMT_I386		= 0x14c, // 386 or better
	PEHMT_I486		= 0x14d, // 486 or better
	PEHMT_I586		= 0x14e, // Pentium or better
	PEHMT_R3000BE	= 0x160, // R3000 (MIPS), bigendian
	PEHMT_R3000		= 0x162, // R3000 (MIPS), littleendian
	PEHMT_R4000		= 0x166, // R4000 (MIPS), littleendian
	PEHMT_R10000	= 0x168, // R10000 (MIPS), littleendian
	PEHMT_ALPHA		= 0x184, // DEC Alpha AXP
	PEHMT_PPC		= 0x1f0, // PowerPC, littleendian
};

// PE header characteristics flags
enum
{
	PEHCF_RELOCS_STRIPPED		= 0x0001, // relocations within sections are stripped
	PEHCF_EXECUTABLE			= 0x0002, // image is executable
	PEHCF_LINENUMS_STRIPPED		= 0x0004, // line number info is stripped
	PEHCF_LOCALSYMS_STRIPPED	= 0x0008, // local symbol info is stripped
	PEHCF_AGGRESSIVE_WS_TRIM	= 0x0010, // aggressive working set trimming should be used (i.e. page out as much as possible)
	PEHCF_BYTES_REVERSED_LO		= 0x0080, // byte reversal, endianness should be swapped
	PEHCF_32BIT_MACHINE			= 0x0100, // 32-bit machine expected, should always be set
	PEHCF_DEBUG_STRIPPED		= 0x0200, // debugging info is stripped (conflicting info: other source says this is "nonrelocatable" bit)
	PEHCF_REMOVABLE_RUNFROMSWAP = 0x0400, // may not run from removable media (cdrom,floppy,etc), temp copy to swap file and exec
	PEHCF_NET_RUNFROMSWAP		= 0x0800, // may not run from network, temp copy to swap file and exec
	PEHCF_SYSTEMFILE			= 0x1000, // system file (i.e. a driver), not generally used
	PEHCF_DLL					= 0x2000, // file is a DLL
	PEHCF_UPSYSTEMONLY			= 0x4000, // will not run on multiprocessor systems, relies on there being only one processor
	PEHCF_BYTES_REVERSED_HI		= 0x8000  // byte reversal, endianness should be swapped
};

// PE header subsystem type
enum
{
	PEHSST_NATIVE		= 1, // no subsystem, used only for drivers
	PEHSST_WIN32_GUI	= 2, // win32 normal graphical binary
	PEHSST_WIN32_CON	= 3, // win32 console binary
	PEHSST_OS2_CON		= 5, // os/2 console binary, rarely used
	PEHSST_POSIX_CON	= 7  // posix console binary, rarely used
};

// PE header dll characteristics flags (may not be used)
enum
{
	PEHDCF_DLLLOAD			= 0x0001, // notify on DLL load (process attachment)
	PEHDCF_THREADDETACH		= 0x0002, // notify on thread detachments/terminations
	PEHDCF_THREADATTACH		= 0x0004, // notify on thread attachments/creations
	PEHDCF_DLLUNLOAD		= 0x0008  // notify on DLL unload (process detachment)
};

// PE header directory entries
enum
{
	PEHDE_EXPORTS		= 0, // export symbols
	PEHDE_IMPORTS		= 1, // import symbols
	PEHDE_RESOURCES		= 2, // resources
	PEHDE_EXCEPTION		= 3, // exception directory, organization unknown
	PEHDE_SECURITY		= 4, // security directory, organization unknown
	PEHDE_BASERELOC		= 5, // base relocation table
	PEHDE_DEBUG			= 6, // debug info, compiler-dependent organization (some compilers put debug info directly in code section)
	PEHDE_COPYRIGHT		= 7, // copyright string
	PEHDE_GLOBALPTR		= 8, // machine value (MIPS GP), organization unknown
	PEHDE_TLS			= 9, // thread local storage, organization unknown, affected by "__declspec(thread)" or whatnot
	PEHDE_LOADCONFIG	= 10, // load configuration, organization unknown
	PEHDE_BOUNDIMPORTS	= 11, // bound imports
	PEHDE_IAT			= 12  // import address table
};

// PE section characteristics flags
enum
{
	PESCF_CNT_CODE			= 0x00000020, // section contains executable code
	PESCF_CNT_INITDATA		= 0x00000040, // section contains initialized data
	PESCF_CNT_UNINITDATA	= 0x00000080, // section contains uninitialized data
	PESCF_LNK_INFO			= 0x00000200, // linker info/comments for object files
	PESCF_LNK_REMOVE		= 0x00000800, // for object files, section that is not needed after linking
	PESCF_LNK_COMDAT		= 0x00001000, // section contains "common block data", whatever that is
	PESCF_MEM_FARDATA		= 0x00008000, // is far data, meaning is obscure in 32-bit executables
	PESCF_MEM_PURGEABLE		= 0x00020000, // not the same as discardable, unsure meaning (conflict: may also indicate 16-bit contents)
	PESCF_MEM_LOCKED		= 0x00040000, // should not be moved? no relocation info? obscure meaning
	PESCF_MEM_PRELOAD		= 0x00080000, // section should be paged in before execution starts? obscure
	PESCF_ALIGN_BIT0		= 0x00100000, // alignment bit 0, unsure of meaning, defaults to 16-byte alignment i think
	PESCF_ALIGN_BIT1		= 0x00200000, // alignment bit 1, unsure of meaning
	PESCF_ALIGN_BIT2		= 0x00400000, // alignment bit 2, unsure of meaning
	PESCF_ALIGN_BIT3		= 0x00800000, // alignment bit 3, unsure of meaning
	PESCF_LNK_NRELOC_OVFL	= 0x01000000, // some extended relocation thing, unsure of meaning
	PESCF_MEM_DISCARDABLE	= 0x02000000, // section data not needed after execution begins (for relocations, etc.)
	PESCF_MEM_NOTCACHED		= 0x04000000, // section's data should not be cached
	PESCF_MEM_NOTPAGED		= 0x08000000, // section's data should not be paged out
	PESCF_MEM_SHARED		= 0x10000000, // section data is shared amongst all instances of the image
	PESCF_RIGHTS_EXECUTE	= 0x20000000, // process gets execute rights to section memory
	PESCF_RIGHTS_READ		= 0x40000000, // process gets read rights to section memory
	PESCF_RIGHTS_WRITE		= 0x80000000  // process gets write rights to section memory
};

// PE debug table type
enum
{
	PEDEBUGT_UNKNOWN		= 0, // unknown value
	PEDEBUGT_COFF			= 1, // COFF debug info
	PEDEBUGT_CODEVIEW		= 2, // CodeView debug info
	PEDEBUGT_FPO			= 3, // frame pointer omission (FPO) information
	PEDEBUGT_MISC			= 4, // miscellaneous
	PEDEBUGT_EXCEPTION		= 5, // exception information
	PEDEBUGT_FIXUP			= 6, // fixup information
	PEDEBUGT_OMAP_TO_SRC	= 7,
	PEDEBUGT_OMAP_FROM_SRC	= 8,
	PEDEBUGT_BORLAND		= 9, // Borland debugging information
	PEDEBUGT_RESERVED10		= 10,
	PEDEBUGT_CLSID			= 11,
};

//============================================================================
//    CLASSES / STRUCTURES
//============================================================================
#pragma pack(push, 1)

// PE header directory entry
struct SPeHeaderDirEntry
{
	unsigned long rva; // address of directory-pointed information, zero if unused
	unsigned long size; // size of directory-pointed information, zero if unused
};

// PE header
struct SPeHeader
{
	// normal PE header
	unsigned long magic; // must be PE_HEADER_MAGIC
	unsigned short machineType; // PEHMT_ machine type
	unsigned short numSections; // number of sections that follow headers
	unsigned long timeStamp; // timestamp at link time (appears to be a time_t)
	unsigned long ptrSymTable; // for debugging info, usually zero
	unsigned long numSymTableSyms; // for debugging info, usually zero
	unsigned short sizeOfOptHeader; // size of optional header, should always be 224
	unsigned short charFlags; // PEHCF_ characteristics flags
	
	// "optional" PE header, not really optional though
	unsigned short optMagic; // must be PE_HEADER_OPTMAGIC
	unsigned char majorLinkerVersion; // major version of linker, if used
	unsigned char minorLinkerVersion; // minor version of linker, if used
	unsigned long sizeOfCode; // size of executable code ("code"), unreliable, inspect sections instead
	unsigned long sizeOfInitData; // size of initialized data ("data"), unreliable, inspect sections instead
	unsigned long sizeOfUninitData; // size of uninitialized data ("bss"), unreliable, inspect sections instead
	unsigned long rvaEntryPoint; // entry point address, execution starts here
	unsigned long rvaBaseOfCode; // offset of code, unreliable, inspect sections instead
	unsigned long rvaBaseOfData; // offset of initialized data, unreliable, inspect sections instead
	unsigned long preferredLoadAddress; // preferred linear load address for image in memory, linker relocations assume this
	unsigned long sectionAlignMemory; // section alignment in memory
	unsigned long sectionAlignFile; // section alignment on disk
	unsigned short majorOSVersion; // major version of operating system, if used
	unsigned short minorOSVersion; // minor version of operating system, if used
	unsigned short majorImageVersion; // major version of image, if used by developer and/or linker
	unsigned short minorImageVersion; // minor version of image, if used by developer and/or linker
	unsigned short majorSubsystemVersion; // major subsystem version (win32/posix), IMPORTANT, should be 4
	unsigned short minorSubsystemVersion; // minor subsystem version (win32/posix), IMPORTANT, should be 0
	unsigned long versionWin32; // win32 version?  always seems to be zero
	unsigned long sizeOfImage; // amount of memory image will need (usually sum of header & section lengths at memory alignment)
	unsigned long sizeOfHeaders; // total length of headers, includes data directories & section headers, file offset of first section's raw data
	unsigned long checkSum; // checksum, only used for NT drivers
	unsigned short subsystemType; // PEHSST_ subsystem type
	unsigned short charDll; // PEHDCF_ DLL characteristics flags, apparently not used (zero) since DLL is still notified regardless
	unsigned long memReserveStack; // amount of memory to reserve for stack
	unsigned long memCommitStack; // amount of memory to commit for stack, also used for stack memory growth step
	unsigned long memReserveHeap; // amount of memory to reserve for heap
	unsigned long memCommitHeap; // amount of memory to commit for heap, also used for heap memory growth step
	unsigned long loaderFlags; // unknown, may affect debugging/breakpoints/etc, usually zero
	unsigned long numDirEntries; // number of SPeHeaderDirEntry entries that follow, should be 16
	SPeHeaderDirEntry dirEntries[1]; // PEHDE_ indexed directory entries, variable sized
};

// PE section header
struct SPeSectionHeader
{
	unsigned char name[8]; // ".code", ".text", ".data", ".bss", "CODE", "IAT", whatever.  Just a name, irrelevant to actual contents.
				    // NOTE: if all 8 bytes used, there is no null terminator!
	unsigned long objAddressBinSize; // for object files, address contents are relocated to, for binaries, size of the contents, unreliable
	unsigned long rvaData; // address of section's data in memory
	unsigned long sizeRawData; // size of section's data at file alignment
	unsigned long ptrRawData; // file pointer to raw data, offset of file start to section data (zero if not present i.e. arbitrary contents)
	unsigned long ptrRelocations; // object files only
	unsigned long ptrLineNumbers; // object files only
	unsigned short numRelocations; // object files only
	unsigned short numLineNumbers; // object files only
	unsigned long charSection; // PESCF_ characteristics flags
};

// PE export table
struct SPeExportTable
{
	unsigned long charExports; // characteristics, usually zero
	unsigned long timeStamp; // time stamp (appears to be a time_t)
	unsigned short majorVersion; // usually zero
	unsigned short minorVersion; // usually zero
	unsigned long rvaName; // address of binary name as a null-terminated string, if used
	unsigned long baseOrdinal; // first ordinal number, subtract ordinal by this to get item index
	unsigned long numExportItems; // number of exported items (functions/variables etc)
	unsigned long numExportNames; // number of exported names
	unsigned long rvaItems; // address of array of numExportItems items, each item is a dword RVA to the exported function/variable/etc
					  // NOTES: If an RVA in the item array is zero, it is unused.
	                  //        If the RVA points into the export table, the export is forwarded, the export data being a
	                  //        null-terminated string "otherdll.itemname" or "otherdll.#69" if by ordinal (no quotes).
	unsigned long rvaNames; // address of array of numExportNames names (if nonzero), each name is a dword RVA to a null-terminated string
	unsigned long rvaOrdinals; // address of array of numExportNames ordinals (if nonzero), each is a word 16-bit ordinal number
	                     // NOTE: these ordinal numbers may not be actual ordinal numbers, but raw indices (no base adjustment)
};

// PE import by name structure
struct SPeImportByName
{
	unsigned short hint; // optional "hint" index into exporting DLL name table, tried first before string search, potential speed help
	char name[1]; // variable sized, null terminated import name
};

// PE import thunk data
struct SPeImportThunkData
{
	unsigned long rvaImportByName; // only member of the structure for now, address of SPeImportByName, zero if thunk array terminator.
							 // That is if the dword has bit 31 clear.  If bit 31 is set, the low word is the ordinal number of
	                         //   the import (in which case there is no name information present)
};

// PE import descriptor
struct SPeImportDescriptor
{
	unsigned long rvaFirstThunkOriginal; // address to null-terminated array of rva's to SPeImportThunkData's
	unsigned long timeStamp; // time stamp (appears to be a time_t).  If nonzero and matches export binary's header timestamp, then the
	                   // bound imports which may be present within the rvaFirstThunk list (instead of names) are valid, assuming
	                   // that the export binary is loaded at its preferred load address.  If it needs to be relocated, or this
	                   // timestamp is zero or mismatched with the export binary's, then rvaFirstThunk must be repatched based on a
	                   // lookup from the firstThunkOriginal.  Addendum: If this timeStamp is -1, "new style" binding is in effect.
					   // In this case, the forwarder chain is not used and all firstThink bound imports will be patched whether
					   // they're forwarded or not.  If this is the case, PEDHE_BOUNDIMPORTS directory should be used for bound
					   // import information (see bound import structures below)
	unsigned long forwarderChain; // index of first forwarder in imported function list, -1 if no forwarders.  If used, this is the index
	                        // within the firstThunk list of the first forwarded export, i.e. an import that is not resolved by the
	                        // export binary but imported by the export binary from yet another binary.  The contents of the
	                        // firstThunk data at this index is the next forwarder, or -1 if there are no forwarders remaining.
	unsigned long rvaExporterName; // address of binary name as a null-terminated string
	unsigned long rvaFirstThunk; // on disk: address to null-terminated array of rva's to SPeImportThunkData's (same as original), or an
	                       //   array of bound imports ala as if it were in memory (see timeStamp member description above)
	                       // at run time: address to array of actual exported symbol linear addresses.  This modified rvaFirstThunk
	                       //   will fall into the IAT, even if the IAT doesn't have a directory entry of its own (it's still there)
};

// PE bound import forwarder ref
struct SPeBoundImportForwarderRef
{
	unsigned long timeStamp; // time stamp of forwarder binary
	unsigned short offsetBinaryName; // offset from beginning of bound import directory of null-terminated name of forwarder binary
	unsigned short reserved;
};

// PE bound import descriptor (for "new style" binding, see import descriptor timestamp member description above).
// Bound import directory at PEDHE_BOUNDIMPORTS is made up of a sequential list of these, terminated by a zero-memmed descriptor.
// Keep in mind that the forwarderRefs member is variable-size when calculating the next descriptor location
struct SPeBoundImportDescriptor
{
	unsigned long timeStamp; // time stamp of binary
	unsigned short offsetBinaryName; // offset from beginning of bound import directory of null-terminated name of binary
	unsigned short numForwarderRefs; // number of binaries that this binary uses for its forwarders
	SPeBoundImportForwarderRef forwarderRefs[1]; // variable sized
};

// PE debug table
struct SPeDebugTable
{
    unsigned long charDebug; // characteristics
    unsigned long timeStamp; // time stamp (appears to be a time_t)
    unsigned short majorVersion; // major version of debug info format
    unsigned short minorVersion; // minor version of debug info format
    unsigned long debugType; // PEDEBUGT_ debug type
    unsigned long sizeBytes; // size of debug information in bytes, not including directory entry itself
    unsigned long rvaRawData; // RVA of debug info
    unsigned long ptrRawData; // file pointer to debug info
};

//-------------------------------
// Runtime structures
//-------------------------------

struct SPeInfo
{
	void* fileImageData; // file image data
	SPeHeader* peHdr; // PE file header within image data
	SPeSectionHeader* peSectionHeaders; // section headers within image data
	bool isFromFile; // image data is from a file, rather than preloaded in memory
};

#pragma pack(pop)

//============================================================================
//    GLOBAL DATA
//============================================================================
//============================================================================
//    GLOBAL FUNCTIONS
//============================================================================
bool PE_GetInfo(void* inModuleBaseAddr, SPeInfo* outInfo, bool inIsFromFile);

unsigned long PE_UnDecorateSymbolName(const char* inDecoratedName, char* outUndecName, unsigned long inUndecNameLen, unsigned short inFlags);
void* PE_ResolveRVA(SPeInfo* inInfo, unsigned long inRVA);
void* PE_ResolveAVA(SPeInfo* inInfo, unsigned long inAVA);
void* PE_PatchImport(SPeInfo* inInfo, const char* inLibraryName, const char* inImportName, void* inFunction); // returns old function

const char* PE_GetPdbFileName(SPeInfo* inInfo);

void PE_DumpInfo(SPeInfo* inInfo);

//============================================================================
//    INLINE CLASS METHODS
//============================================================================
//============================================================================
//    TRAILING HEADERS
//============================================================================

} // namespace Reflection

#endif // #ifdef SUPPORT_REF_PEFILES
//****************************************************************************
//**
//**    END HEADER REFPEFILES.H
//**
//****************************************************************************
#endif // __REFPEFILES_H__
