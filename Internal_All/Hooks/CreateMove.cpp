#include "..\CheatInclude.h"

CreateMoveFn oCreateMove;

bool __stdcall g_hkCreateMove( float flInputSampleTime, CUserCmd* cmd )
{
	if ( F::Misc->FinishHalftimeFix( cmd ) )
		return true;

	if ( !cmd->command_number )
		return true;

	F::Misc->SetupHalftimeFix( cmd );

	F::Misc->Radar();

	return true;
}