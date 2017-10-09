#include "..\CheatInclude.h"


HFont Font::ESP;

void D::SetupFonts()
{
	g_pSurface->SetFontGlyphSet( Font::ESP = g_pSurface->Create_Font(), charenc( "Ubuntu" ), 12, FW_DONTCARE, NULL, NULL, FONTFLAG_OUTLINE | FONTFLAG_ANTIALIAS );
}

void D::DrawString( HFont font, int x, int y, Color color, DWORD alignment, const char* msg, ... )
{
	va_list va_alist;
	char buf[ 1024 ];
	va_start( va_alist, msg );
	_vsnprintf( buf, sizeof( buf ), msg, va_alist );
	va_end( va_alist );
	wchar_t wbuf[ 1024 ];
	MultiByteToWideChar( CP_UTF8, 0, buf, 256, wbuf, 256 );

	int r = 255, g = 255, b = 255, a = 255;
	color.GetColor( r, g, b, a );

	int width, height;
	g_pSurface->GetTextSize( font, wbuf, width, height );

	if ( alignment & FONT_RIGHT )
		x -= width;
	if ( alignment & FONT_CENTER )
		x -= width / 2;

	g_pSurface->DrawSetTextFont( font );
	g_pSurface->DrawSetTextColor( r, g, b, a );
	g_pSurface->DrawSetTextPos( x, y - height / 2 );
	g_pSurface->DrawPrintText( wbuf, wcslen( wbuf ) );
}

void D::DrawStringUnicode( HFont font, int x, int y, Color color, bool bCenter, const wchar_t* msg, ... )
{
	int r = 255, g = 255, b = 255, a = 255;
	color.GetColor( r, g, b, a );

	int iWidth, iHeight;

	g_pSurface->GetTextSize( font, msg, iWidth, iHeight );
	g_pSurface->DrawSetTextFont( font );
	g_pSurface->DrawSetTextColor( r, g, b, a );
	g_pSurface->DrawSetTextPos( !bCenter ? x : x - iWidth / 2, y - iHeight / 2 );
	g_pSurface->DrawPrintText( msg, wcslen( msg ) );
}

void D::DrawRect( int x, int y, int w, int h, Color col )
{
	g_pSurface->DrawSetColor( col );
	g_pSurface->DrawFilledRect( x, y, x + w, y + h );
}

void D::DrawRectRainbow( int x, int y, int width, int height, float flSpeed, float &flRainbow )
{
	Color colColor( 0, 0, 0 );

	flRainbow += flSpeed;
	if ( flRainbow > 1.f ) flRainbow = 0.f;

	for ( int i = 0; i < width; i++ )
	{
		float hue = ( 1.f / ( float ) width ) * i;
		hue -= flRainbow;
		if ( hue < 0.f ) hue += 1.f;

		Color colRainbow = colColor.FromHSB( hue, 1.f, 1.f );
		D::DrawRect( x + i, y, 1, height, colRainbow );
	}
}

void D::DrawRectGradientHorizontal( int x, int y, int width, int height, Color color1, Color color2 )
{
	float flDifferenceR = ( float ) ( color2.r() - color1.r() ) / ( float ) width;
	float flDifferenceG = ( float ) ( color2.g() - color1.g() ) / ( float ) width;
	float flDifferenceB = ( float ) ( color2.b() - color1.b() ) / ( float ) width;

	for ( float i = 0.f; i < width; i++ )
	{
		Color colGradient = Color( color1.r() + ( flDifferenceR * i ), color1.g() + ( flDifferenceG * i ), color1.b() + ( flDifferenceB * i ), color1.a() );
		D::DrawRect( x + i, y, 1, height, colGradient );
	}
}

void D::DrawPixel( int x, int y, Color col )
{
	g_pSurface->DrawSetColor( col );
	g_pSurface->DrawFilledRect( x, y, x + 1, y + 1 );
}

void D::DrawOutlinedRect( int x, int y, int w, int h, Color col )
{
	g_pSurface->DrawSetColor( col );
	g_pSurface->DrawOutlinedRect( x, y, x + w, y + h );
}

void D::DrawOutlinedCircle( int x, int y, int r, Color col )
{
	g_pSurface->DrawSetColor( col );
	g_pSurface->DrawOutlinedCircle( x, y, r, 1 );
}

void D::DrawLine( int x0, int y0, int x1, int y1, Color col )
{
	g_pSurface->DrawSetColor( col );
	g_pSurface->DrawLine( x0, y0, x1, y1 );
}

void D::DrawCorner( int iX, int iY, int iWidth, int iHeight, bool bRight, bool bDown, Color colDraw )
{
	int iRealX = bRight ? iX - iWidth : iX;
	int iRealY = bDown ? iY - iHeight : iY;

	if ( bDown && bRight )
		iWidth = iWidth + 1;

	D::DrawRect( iRealX, iY, iWidth, 1, colDraw );
	D::DrawRect( iX, iRealY, 1, iHeight, colDraw );

	D::DrawRect( iRealX, bDown ? iY + 1 : iY - 1, !bDown && bRight ? iWidth + 1 : iWidth, 1, Color( 0, 0, 0, 255 ) );
	D::DrawRect( bRight ? iX + 1 : iX - 1, bDown ? iRealY : iRealY - 1, 1, bDown ? iHeight + 2 : iHeight + 1, Color( 0, 0, 0, 255 ) );
}

void D::DrawPolygon( int count, Vertex_t* Vertexs, Color color )
{
	static int Texture = g_pSurface->CreateNewTextureID( true );
	unsigned char buffer[ 4 ] = { 255, 255, 255, 255 };

	g_pSurface->DrawSetTextureRGBA( Texture, buffer, 1, 1 );
	g_pSurface->DrawSetColor( color );
	g_pSurface->DrawSetTexture( Texture );

	g_pSurface->DrawTexturedPolygon( count, Vertexs );
}

void D::DrawRoundedBox( int x, int y, int w, int h, int r, int v, Color col )
{
	std::vector<Vertex_t> p;
	for ( int _i = 0; _i < 3; _i++ )
	{
		int _x = x + ( _i < 2 && r || w - r );
		int _y = y + ( _i % 3 > 0 && r || h - r );
		for ( int i = 0; i < v; i++ )
		{
			int a = RAD2DEG( ( i / v ) * -90 - _i * 90 );
			p.push_back( Vertex_t( Vector2D( _x + sin( a ) * r, _y + cos( a ) * r ) ) );
		}
	}

	D::DrawPolygon( 4 * ( v + 1 ), &p[ 0 ], col );
}

bool D::ScreenTransform( const Vector &point, Vector &screen )
{
	float w;
	const VMatrix &worldToScreen = g_pEngine->WorldToScreenMatrix();

	screen.x = worldToScreen[ 0 ][ 0 ] * point[ 0 ] + worldToScreen[ 0 ][ 1 ] * point[ 1 ] + worldToScreen[ 0 ][ 2 ] * point[ 2 ] + worldToScreen[ 0 ][ 3 ];
	screen.y = worldToScreen[ 1 ][ 0 ] * point[ 0 ] + worldToScreen[ 1 ][ 1 ] * point[ 1 ] + worldToScreen[ 1 ][ 2 ] * point[ 2 ] + worldToScreen[ 1 ][ 3 ];
	w = worldToScreen[ 3 ][ 0 ] * point[ 0 ] + worldToScreen[ 3 ][ 1 ] * point[ 1 ] + worldToScreen[ 3 ][ 2 ] * point[ 2 ] + worldToScreen[ 3 ][ 3 ];
	screen.z = 0.0f;

	bool behind = false;

	if ( w < 0.001f )
	{
		behind = true;
		screen.x *= 100000;
		screen.y *= 100000;
	}
	else
	{
		behind = false;
		float invw = 1.0f / w;
		screen.x *= invw;
		screen.y *= invw;
	}

	return behind;
}

bool D::WorldToScreen( const Vector &origin, Vector &screen )
{
	if ( !ScreenTransform( origin, screen ) )
	{
		int ScreenWidth, ScreenHeight;
		g_pEngine->GetScreenSize( ScreenWidth, ScreenHeight );
		float x = ScreenWidth / 2;
		float y = ScreenHeight / 2;
		x += 0.5 * screen.x * ScreenWidth + 0.5;
		y -= 0.5 * screen.y * ScreenHeight + 0.5;
		screen.x = x;
		screen.y = y;
		return true;
	}

	return false;
}

int D::GetStringWidth( HFont font, const char* msg, ... )
{
	va_list va_alist;
	char buf[ 1024 ];
	va_start( va_alist, msg );
	_vsnprintf( buf, sizeof( buf ), msg, va_alist );
	va_end( va_alist );
	wchar_t wbuf[ 1024 ];
	MultiByteToWideChar( CP_UTF8, 0, buf, 256, wbuf, 256 );

	int iWidth, iHeight;

	g_pSurface->GetTextSize( font, wbuf, iWidth, iHeight );

	return iWidth;
}

void D::Draw3DBox( Vector* boxVectors, Color color )
{
	Vector boxVectors0, boxVectors1, boxVectors2, boxVectors3,
		boxVectors4, boxVectors5, boxVectors6, boxVectors7;


	if ( D::WorldToScreen( boxVectors[ 0 ], boxVectors0 ) &&
		 D::WorldToScreen( boxVectors[ 1 ], boxVectors1 ) &&
		 D::WorldToScreen( boxVectors[ 2 ], boxVectors2 ) &&
		 D::WorldToScreen( boxVectors[ 3 ], boxVectors3 ) &&
		 D::WorldToScreen( boxVectors[ 4 ], boxVectors4 ) &&
		 D::WorldToScreen( boxVectors[ 5 ], boxVectors5 ) &&
		 D::WorldToScreen( boxVectors[ 6 ], boxVectors6 ) &&
		 D::WorldToScreen( boxVectors[ 7 ], boxVectors7 ) )
	{

		/*
		.+--5---+
		.8 4    6'|
		+--7---+'  11
		9   |  10  |
		|  ,+--|3--+
		|.0    | 2'
		+--1---+'
		*/

		Vector2D lines[ 12 ][ 2 ];
		//bottom of box
		lines[ 0 ][ 0 ] = { boxVectors0.x, boxVectors0.y };
		lines[ 0 ][ 1 ] = { boxVectors1.x, boxVectors1.y };
		lines[ 1 ][ 0 ] = { boxVectors1.x, boxVectors1.y };
		lines[ 1 ][ 1 ] = { boxVectors2.x, boxVectors2.y };
		lines[ 2 ][ 0 ] = { boxVectors2.x, boxVectors2.y };
		lines[ 2 ][ 1 ] = { boxVectors3.x, boxVectors3.y };
		lines[ 3 ][ 0 ] = { boxVectors3.x, boxVectors3.y };
		lines[ 3 ][ 1 ] = { boxVectors0.x, boxVectors0.y };

		lines[ 4 ][ 0 ] = { boxVectors0.x, boxVectors0.y };
		lines[ 4 ][ 1 ] = { boxVectors6.x, boxVectors6.y };

		// top of box
		lines[ 5 ][ 0 ] = { boxVectors6.x, boxVectors6.y };
		lines[ 5 ][ 1 ] = { boxVectors5.x, boxVectors5.y };
		lines[ 6 ][ 0 ] = { boxVectors5.x, boxVectors5.y };
		lines[ 6 ][ 1 ] = { boxVectors4.x, boxVectors4.y };
		lines[ 7 ][ 0 ] = { boxVectors4.x, boxVectors4.y };
		lines[ 7 ][ 1 ] = { boxVectors7.x, boxVectors7.y };
		lines[ 8 ][ 0 ] = { boxVectors7.x, boxVectors7.y };
		lines[ 8 ][ 1 ] = { boxVectors6.x, boxVectors6.y };


		lines[ 9 ][ 0 ] = { boxVectors5.x, boxVectors5.y };
		lines[ 9 ][ 1 ] = { boxVectors1.x, boxVectors1.y };

		lines[ 10 ][ 0 ] = { boxVectors4.x, boxVectors4.y };
		lines[ 10 ][ 1 ] = { boxVectors2.x, boxVectors2.y };

		lines[ 11 ][ 0 ] = { boxVectors7.x, boxVectors7.y };
		lines[ 11 ][ 1 ] = { boxVectors3.x, boxVectors3.y };

		for ( int i = 0; i < 12; i++ )
		{
			D::DrawLine( lines[ i ][ 0 ].x, lines[ i ][ 0 ].y, lines[ i ][ 1 ].x, lines[ i ][ 1 ].y, color );
		}
	}
}

void D::DrawCircle( float x, float y, float r, float s, Color color )
{
	float Step = M_PI * 2.0 / s;
	for ( float a = 0; a < ( M_PI*2.0 ); a += Step )
	{
		float x1 = r * cos( a ) + x;
		float y1 = r * sin( a ) + y;
		float x2 = r * cos( a + Step ) + x;
		float y2 = r * sin( a + Step ) + y;

		DrawLine( x1, y1, x2, y2, color );
	}
}

void D::CornerBox( const int32_t x, const int32_t y, const int32_t w, const int32_t h, const bool outlined, const Color& color, const Color& outlined_color = 0xFF000000 )
{
	auto corner = [ & ] ( const int32_t _x, const int32_t _y, const int32_t width, const int32_t height, const bool right_side, const bool down, const Color& _color, const bool _outlined = false, const Color& _outlined_color = 0xFF000000 ) -> void
	{
		const auto corner_x = right_side ? _x - width : _x;
		const auto corner_y = down ? _y - height : _y;
		const auto corner_w = down && right_side ? width + 1 : width;

		D::DrawRect( corner_x, _y, corner_w, 1, _color );
		D::DrawRect( _x, corner_y, 1, height, _color );

		if ( _outlined ) {
			D::DrawRect( corner_x, down ? _y + 1 : _y - 1, !down && right_side ? corner_w + 1 : corner_w, 1, _outlined_color );
			D::DrawRect( right_side ? _x + 1 : _x - 1, down ? corner_y : corner_y - 1, 1, down ? height + 2 : height + 1, _outlined_color );
		}
	};

	corner( x - w, y, w / 2, w / 2, false, false, color, outlined, outlined_color );
	corner( x - w, y + h, w / 2, w / 2, false, true, color, outlined, outlined_color );
	corner( x + w, y, w / 2, w / 2, true, false, color, outlined, outlined_color );
	corner( x + w, y + h, w / 2, w / 2, true, true, color, outlined, outlined_color );
}