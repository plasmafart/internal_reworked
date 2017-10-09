#pragma once

class COffsets
{
public:
	void GrabOffsets();
	//sigs
	DWORD d3d9Device;
	DWORD dwCAM_Think;
	DWORD LoadFromBufferEx;
	DWORD InitKeyValuesEx;
};

extern COffsets* Offsets;