#pragma once

namespace Font
{
	extern HFont ESP;
}

namespace D
{
	extern void SetupFonts();
	extern void DrawString( HFont font, int x, int y, Color color, DWORD alignment, const char* msg, ... );
	extern void DrawStringUnicode( HFont font, int x, int y, Color color, bool bCenter, const wchar_t* msg, ... );
	extern void DrawRect( int x, int y, int w, int h, Color col );
	extern void DrawRectRainbow( int x, int y, int w, int h, float flSpeed, float &flRainbow );
	extern void DrawRectGradientVertical( int x, int y, int w, int h, Color color1, Color color2 );
	extern void DrawRectGradientHorizontal( int x, int y, int w, int h, Color color1, Color color2 );
	extern void DrawPixel( int x, int y, Color col );
	extern void DrawOutlinedRect( int x, int y, int w, int h, Color col );
	extern void DrawOutlinedCircle( int x, int y, int r, Color col );
	extern void DrawLine( int x0, int y0, int x1, int y1, Color col );
	extern void DrawCorner( int iX, int iY, int iWidth, int iHeight, bool bRight, bool bDown, Color colDraw );
	extern void DrawRoundedBox( int x, int y, int w, int h, int r, int v, Color col );
	extern void DrawPolygon( int count, Vertex_t* Vertexs, Color color );
	extern bool ScreenTransform( const Vector &point, Vector &screen );
	extern bool WorldToScreen( const Vector &origin, Vector &screen );
	extern int GetStringWidth( HFont font, const char* msg, ... );
	extern void Draw3DBox( Vector* boxVectors, Color color );
	extern void DrawCircle( float x, float y, float r, float s, Color color );
	extern void CornerBox( const int32_t x, const int32_t y, const int32_t w, const int32_t h, const bool outlined, const Color & color, const Color & outlined_color );
}