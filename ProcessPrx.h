/***************************************************************
 * PRXTool : Utility for PSP executables.
 * (c) TyRaNiD 2k5
 *
 * ProcessPrx.h - Definition of a class to process PRX files.
 ***************************************************************/

#ifndef __PROCESSPRX_H__
#define __PROCESSPRX_H__

#include "ProcessElf.h"
#include "VirtualMem.h"
#include "prxtypes.h"
#include "NidMgr.h"
#include "disasm.h"

/* Define ProcessPrx derived from ProcessElf */
class CProcessPrx : public CProcessElf
{
	PspModule m_modInfo;
	CNidMgr   m_defNidMgr;
	CNidMgr*  m_pCurrNidMgr;
	CVirtualMem m_vMem;
	bool m_blPrxLoaded;
	/* Pointer to the allocated relocation entries, if available */
	ElfReloc  *m_pElfRelocs;
	/* Number of relocations */
	int m_iRelocCount;

	bool FillModule(ElfSection *pInfoSect);
	void FreeMemory();
	int  LoadSingleImport(PspModuleImport *pImport, u32 addr);
	bool LoadImports();
	int  LoadSingleExport(PspModuleExport *pExport, u32 addr);
	bool LoadExports();
	bool LoadRelocs();
	void BuildSymbols(SymbolMap &syms, u32 dwBase);
	void FreeSymbols(SymbolMap &syms);
	void FreeImms(ImmMap &imms);
	void FixupRelocs(u32 dwBase, ImmMap &imms);
	bool ReadString(u32 dwAddr, std::string &str, bool unicode);
	void DumpStrings(FILE *fp, u32 dwAddr, u32 iSize, unsigned char *pData);
	void DumpData(FILE *fp, u32 dwAddr, u32 iSize, unsigned char *pData);
	void Disasm(FILE *fp, u32 dwAddr, u32 iSize, unsigned char *pData, ImmMap &imms, u32 dwBase);
public:
	CProcessPrx();
	virtual ~CProcessPrx();
	virtual bool LoadFromFile(const char *szFilename);

	bool PrxToElf(FILE *fp);
	bool ElfToPrx(FILE *fp);

	PspModule* GetModuleInfo();
	ElfReloc* GetRelocs(int &iCount);
	ElfSymbol* GetSymbols(int &iCount);
	PspLibImport *GetImports();
	PspLibExport *GetExports();
	void SetNidMgr(CNidMgr* nidMgr);
	void Dump(bool blAll, FILE *fp, const char *disopts, u32 dwBase);
};

#endif
