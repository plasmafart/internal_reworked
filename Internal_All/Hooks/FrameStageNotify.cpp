#include "..\CheatInclude.h"

FrameStageNotifyFn oFrameStageNotify;

void __stdcall g_hkFrameStageNotify( ClientFrameStage_t stage )
{

	F::SkinChanger->Run( stage );

	F::Thirdperson->Run( stage );
	
	F::Misc->FixPositionInaccuracy( stage );

	oFrameStageNotify( stage );
}