#pragma once

class CBaseClientState 
{
	public:
		void ForceFullUpdate() 
		{
			// m_nDeltaTick: 0x16C
			*reinterpret_cast<int*>(uintptr_t(this) + 0x174) = -1;
		};
};