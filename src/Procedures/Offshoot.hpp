#pragma once
#include <KPState.hpp>

#define JSON_GET(x, data) x = data[#x]

namespace StateName {
	constexpr const char * OFFSHOOT_IDLE		= "offshoot-idle-state";
	constexpr const char * OFFSHOOT_STOP		= "offshoot-stop-state";
	constexpr const char * OFFSHOOT_DECON	= "offshoot-decon-state";
	constexpr const char * OFFSHOOT_PRESERVE = "offshoot-preserve-state";
	constexpr const char * OFFSHOOT_DRY		= "offshoot-dry-state";
	constexpr const char * OFFSHOOT_SAMPLE	= "offshoot-sample-state";
	constexpr const char * OFFSHOOT_FLUSH	= "offshoot-flush-state";
	constexpr const char * OFFSHOOT_CLEAN    = "offshoot-clean-state";
};	// namespace StateName


// class OffshootAlcohol : public KPState {
// public:
// 	void enter(KPStateMachine & sm) override;
// };

// class OffshootAir : public KPState {
// public:
// 	unsigned long time = 0;
// 	void enter(KPStateMachine & sm) override;
// };

// class OffshootSample : public KPState {
// public:
// 	unsigned long time = 0;
// 	float pressure	   = 8;
// 	float volume	   = 100;
// 	void enter(KPStateMachine & sm) override;
// };

// class OffshootFlush2 : public KPState {
// public:
// 	unsigned long time = 150;
// 	float pressure	   = 8;
// 	float volume	   = 1000;
// 	void enter(KPStateMachine & sm) override;
// };

class OffshootBackWater : public KPState {
public:
	unsigned long time = 2;
	void enter(KPStateMachine & sm) override;
};

class OffshootFlush1 : public KPState {
public:
	unsigned long time = 150;
	float pressure	   = 8;
	float volume	   = 1000;
	void enter(KPStateMachine & sm) override;
};
