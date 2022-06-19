#pragma once
class eSettingsManager {
public:
	static bool m_bDisableDecalsDisappearing;
	static bool m_bRandomizeBloodDecals;
	static int  m_nDecalsAmount;
	static int  m_nDecalLifetime;

	static void Init();
};