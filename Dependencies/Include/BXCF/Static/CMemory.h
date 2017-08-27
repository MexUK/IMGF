#pragma once

#include "nsbxcf.h"
#include "Type/Types.h"
#include <cstdarg>
#include <vector>

class CMemoryRange;

class bxcf::CMemory
{
public:
	void					callCdeclFunction(unsigned long uiFunctionAddress, unsigned short usArgumentCount, ...);
	void					callFunction(unsigned long uiFunctionAddress, unsigned short usArgumentCount, ...);

	void					setMemoryNopped(unsigned long uiAddress, unsigned short usByteCount = 1);
	void					restoreNoppedMemory(unsigned long uiAddress);
	CMemoryRange*			getNoppedMemoryRangeByAddress(unsigned long uiAddress);

	void					removeFunctionCall(unsigned long uiCallAddress, unsigned short usArgumentCount = 0, bool bCallerCleanStack = false);
	
	static void				copyAndDeleteUint8Array(void* pDestination, uint8* pSource, uint64 uiByteCountToCopy);

	static void				setPageFullAccess(unsigned long lpAddress, unsigned long dwSize);
	
	// generate array of addresses
	static std::vector<unsigned long>		getAddressReferences(unsigned long uiAddress);
	static void								getAddressReferencesForRange(
												unsigned long uiAddressStart,
												unsigned long uiAddressEnd,
												std::vector<unsigned long>& vecAddresses,
												std::vector<std::vector<unsigned long>>& vecAddressReferences);
	static std::string						generateAddressOverrideCode(unsigned long uiAddressStart, unsigned long uiAddressEnd);
	
private:
	__forceinline void		pushVL(unsigned short usStackEntryCount, va_list vlArguments);
	__forceinline void		push(unsigned long uiArgument);
	//__forceinline void		call(unsigned long uiFunctionAddress);
	__forceinline void		removeStackArguments(unsigned short usStackEntryCount);

	std::vector<CMemoryRange*>		m_vecNoppedMemory;
};

__forceinline void		call(unsigned long uiFunctionAddress);

// assembly instruction wrappers
void			bxcf::CMemory::push(unsigned long uiArgument)
{
	__asm
	{
		push	uiArgument
	}
}
void			bxcf::CMemory::pushVL(unsigned short usStackEntryCount, va_list vlArguments)
{
	for (int i = 0; i < usStackEntryCount; i++)
	{
		push(va_arg(vlArguments, unsigned long));
	}
}
void			bxcf::CMemory::removeStackArguments(unsigned short usStackEntryCount)
{
	unsigned long uiStackByteCount = usStackEntryCount * 4;
	__asm
	{
		add		esp, uiStackByteCount
	}
}
__declspec(naked) void			call(unsigned long uiFunctionAddress) // todo - namespace - and put in class?
{
	__asm
	{
		call	uiFunctionAddress
	}
}