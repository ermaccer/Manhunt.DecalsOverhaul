#include "pch.h"
#include "CDecalEx.h"
#include "manhunt/Maths.h"
#include "manhunt/core.h"
#include "SettingsMgr.h"
int CDecalEx::pLastPed = 0;

bool CDecalEx::IsDecalBlood(eDecalTypes decal)
{
    return decal == DT_BLOOD || decal == DT_BLOOD2 || decal == DT_BLOOD3 || decal == DT_BLOOD_DEAD;
}

int CDecalEx::DecalSet(CVector* pos, CVector* a2, int a3, float size1, float size2, float a6, float a7, int r, int g, int b, int a, float a12, eDecalTypes decal)
{
    if (IsDecalBlood(decal) && eSettingsManager::m_bRandomizeBloodDecals)
    {
        decal = (eDecalTypes)CMaths::GetRandomInt(DT_BLOOD, DT_BLOOD_DEAD);
    }

    return CDecal::DecalSet(pos, a2, a3, size1, size2, a6, a7, r, g, b, a, a12, decal);
}

int CDecalEx::DecalSetPedBlood(CVector* pos, CVector* a2, int a3, float size1, float size2, float a6, float a7, int r, int g, int b, int a, float a12, eDecalTypes decal)
{
    // workaround for updating blood puddles

    if (pLastPed && eSettingsManager::m_bRandomizeBloodDecals)
        decal = (eDecalTypes)*(int*)(pLastPed + 4);

    return CDecal::DecalSet(pos, a2, a3, size1, size2, a6, a7, r, g, b, a, a12, decal);
}

void __declspec(naked) CDecalEx::Hook_GetPedBlood()
{
    static int jmp_continue = 0x4B3275;
    _asm {
        mov pLastPed, ebx
        mov esi, [ebx + 0x2E0]
        pushad
    }
    if (pLastPed)
    {
       if (*(int*)(pLastPed + 8) == 0)
       {
           // dt_blood looks ugly on peds
           *(int*)(pLastPed + 4) = CMaths::GetRandomInt(DT_BLOOD2, DT_BLOOD_DEAD);
           *(int*)(pLastPed + 8) = 1;
       }

    }
    _asm {
        popad
        jmp jmp_continue
    }
}
