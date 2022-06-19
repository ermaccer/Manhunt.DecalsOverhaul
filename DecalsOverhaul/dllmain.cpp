// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "MemoryMgr.h"
#include "CDecalEx.h"
#include "IniReader.h"
#include "SettingsMgr.h"

using namespace Memory::VP;

int decalsAmount = 0;

void  __declspec(naked) Hook_DecalsReset()
{
    static int jmp_reset_continue = 0x4827E9;
    decalsAmount = eSettingsManager::m_nDecalsAmount - 8;
    _asm {
        add edx, 320
        cmp eax, decalsAmount
        jmp jmp_reset_continue
    }
}

void  __declspec(naked) Hook_DecalsReset2()
{
    static int jmp_reset2_continue = 0x48305F;
    decalsAmount = eSettingsManager::m_nDecalsAmount - 8;
    _asm {
        add eax, 320
        cmp ecx, decalsAmount
        jmp jmp_reset2_continue
    }
}


void Init()
{
    eSettingsManager::Init();
    unsigned int newDecalSize = eSettingsManager::m_nDecalsAmount * sizeof(CDecalEntry);

    Patch(0x482641 + 1, newDecalSize);

    Patch(0x48259D + 2, eSettingsManager::m_nDecalsAmount);
    Patch(0x48260D + 2, eSettingsManager::m_nDecalsAmount);
    Patch(0x482998 + 3, eSettingsManager::m_nDecalsAmount);
    Patch(0x482EC6 + 6, eSettingsManager::m_nDecalsAmount);
    Patch(0x4831AF + 4, eSettingsManager::m_nDecalsAmount);


    Nop(0x4827E0, 6);
    InjectHook(0x4827E0, Hook_DecalsReset, PATCH_JUMP);
    
    Nop(0x483057, 6);
    InjectHook(0x483057, Hook_DecalsReset2, PATCH_JUMP);

    InjectHook(0x49DCD6, CDecalEx::DecalSet);
    InjectHook(0x4B32C8, CDecalEx::DecalSet);
    InjectHook(0x4CF49C, CDecalEx::DecalSet);
    InjectHook(0x4F2307, CDecalEx::DecalSet);
    InjectHook(0x4F41AC, CDecalEx::DecalSet);
    InjectHook(0x4F45DA, CDecalEx::DecalSet);
    InjectHook(0x4F482C, CDecalEx::DecalSet);
    InjectHook(0x4FAE65, CDecalEx::DecalSet);
    InjectHook(0x5CF9B8, CDecalEx::DecalSet);
    InjectHook(0x5D1C0B, CDecalEx::DecalSet);

    InjectHook(0x4B332E, CDecalEx::DecalSetPedBlood);

    Patch(0x482D8A + 4, eSettingsManager::m_nDecalLifetime);

    if (eSettingsManager::m_bDisableDecalsDisappearing)
        Nop(0x4828D4, 5);

    if (eSettingsManager::m_bRandomizeBloodDecals)
    {
        Nop(0x4B326F, 6);
        InjectHook(0x4B326F, CDecalEx::Hook_GetPedBlood, PATCH_JUMP);
    }


}


extern "C"
{
    __declspec(dllexport) void InitializeASI()
    {
        if (*(int*)0x63BC93 != 0x24448B66)
        {
            MessageBoxA(0, "Invalid executable!", "DecalsOverhaul", 0);
        }
        else Init();
    }
}
