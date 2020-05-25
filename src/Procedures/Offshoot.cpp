
#include <Procedures/Offshoot.hpp>
#include <Application/Application.hpp>

void OffshootBackWater::enter(KPStateMachine & sm) {
	println("Backing water");
	Application & app = *static_cast<Application *>(sm.controller);
	ValveBlock vBlock = app.currentValveNumberToBlock();

	app.shift.setAllRegistersLow();
	app.shift.setRegister(vBlock.regIndex, vBlock.pinIndex, HIGH);
	app.shift.writeLatchOut();
	app.pump.on(Direction::reverse);

	setTimeCondition(2, [&]() {
		sm.transitionTo(StateName::FLUSH);
	});
};

void OffshootFlush1::enter(KPStateMachine & sm) {

};