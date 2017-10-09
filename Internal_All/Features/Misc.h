#pragma once

class CMisc
{
public:
	void FixPositionInaccuracy( ClientFrameStage_t stage );
	void Radar();
	bool FinishHalftimeFix( CUserCmd* cmd );
	void SetupHalftimeFix( CUserCmd* cmd );
private:
	bool m_bWasFrozen;
	QAngle m_oldangles;
};