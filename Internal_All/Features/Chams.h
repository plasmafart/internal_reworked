#pragma once

class CChams
{
public:
	void Run( void* context, void* state, const ModelRenderInfo_t& info, matrix3x4_t* pCustomBoneToWorld );
private:
	void ForceMaterial( IMaterial* material, Color color );
};