#include "SettingsMgr.h"
#include "IniReader.h"

bool eSettingsManager::m_bDisableDecalsDisappearing;
bool eSettingsManager::m_bRandomizeBloodDecals;
int  eSettingsManager::m_nDecalsAmount;
int  eSettingsManager::m_nDecalLifetime;

void eSettingsManager::Init()
{
	CIniReader ini("");

	m_bDisableDecalsDisappearing = ini.ReadBoolean("Settings", "bDisableDecalsDisappearing", false);
	m_bRandomizeBloodDecals = ini.ReadBoolean("Settings", "bRandomizeBloodDecals", false);
	m_nDecalsAmount = ini.ReadInteger("Settings", "iDecalsAmount", 130);
	m_nDecalLifetime = ini.ReadInteger("Settings", "iDecalLifetime", 40);
}
