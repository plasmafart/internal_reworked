#pragma once

class VMTHook
{
public:
	VMTHook();

	VMTHook( PDWORD* ppdwClassBase );

	~VMTHook();

	bool bInitialize( PDWORD* ppdwClassBase );
	bool bInitialize( PDWORD** pppdwClassBase );

	void UnHook();

	void ReHook();

	int iGetFuncCount();

	DWORD GetFuncAddress( int Index );

	PDWORD GetOldVT();

	DWORD HookFunction( DWORD dwNewFunc, unsigned int iIndex );

private:
	DWORD GetVTCount( PDWORD pdwVMT );

	PDWORD*	m_ClassBase;
	PDWORD	m_NewVT, m_OldVT;
	DWORD	m_VTSize;
};

