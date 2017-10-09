#include "..\CheatInclude.h"

PaintTraverseFn oPaintTraverse;
void __fastcall g_hkPaintTraverse( void* pPanels, int edx, unsigned int panel, bool forceRepaint, bool allowForce )
{
	static unsigned int scopePanel;
	if ( !scopePanel )
	{
		const char* panelname = g_pVPanel->GetName( panel );

		if ( !strcmp( panelname, "HudZoom" ) )
			scopePanel = panel;
	}

	if ( g_pInput->m_fCameraInThirdPerson && panel == scopePanel && Vars.Visuals.bSniperCrosshair )
		return;

	oPaintTraverse( pPanels, panel, forceRepaint, allowForce );

	static unsigned int drawPanel;
	if ( !drawPanel )
	{
		const char* panelname = g_pVPanel->GetName( panel );

		if ( !strcmp( panelname, "MatSystemTopPanel" ) )
			drawPanel = panel;
	}

	if ( panel != drawPanel )
		return;

	// dumb fix so we can have no visuals but still see the menu
	D::DrawPixel( 1, 1, Color( 0, 0, 0 ) );

	F::Visuals->Run();
}