#pragma once
#include <KPState.hpp>

class NewSample : public KPState {
public:
	void enter(KPStateMachine & machine) override;
};

class OffshootClean : public KPState {
public:
	int cleanTime = 2000;
	void enter(KPStateMachine & machine) override;
};

class OffshootPreload : public KPState {
public:
	int preloadTime = 2000;
	void enter(KPStateMachine & machine) override;
};

class NewFlush : public KPState {
public:
	const char * nextStateName = nullptr;
	NewFlush(const char * name)
		: nextStateName(name) {}
	void enter(KPStateMachine & machine) override;
};