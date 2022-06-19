#pragma once
#include "manhunt/Decal.h"

class CDecalEx : public CDecal {
public:

	static bool IsDecalBlood(eDecalTypes decal);

	static int pLastPed;

	static int DecalSet(CVector* pos, CVector* a2 /* rot?*/, int a3, float size1, float size2, float a6, float a7, int r, int g, int b, int a, float a12, eDecalTypes decal);
	static int DecalSetPedBlood(CVector* pos, CVector* a2 /* rot?*/, int a3, float size1, float size2, float a6, float a7, int r, int g, int b, int a, float a12, eDecalTypes decal);

	static void Hook_GetPedBlood();
};