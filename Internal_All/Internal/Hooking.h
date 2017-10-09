#pragma once

class CHook
{
public:

	VMTHook* g_phkVPanel;
	VMTHook* g_phkClient;
	VMTHook* g_phkClientMode;
	VMTHook* g_phkD3D9;
	VMTHook* g_phkVModelRender;
	VMTHook* g_phkMaterialSystem;

	VMTHook* g_phkSvCheats;

	RecvPropHook* g_phkSequence;

	void HooksInit();
	void HooksUnhook();
};

extern CHook* Hook;