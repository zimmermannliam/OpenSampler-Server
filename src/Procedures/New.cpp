#include <Procedures/New.hpp>
#include <Application/Application.hpp>

void OffshootClean::enter(KPStateMachine & sm) {
	auto & app				= *static_cast<Application *>(sm.controller);
	const int valveId		= app.status.currentValve;
	const int registerIndex = app.shift.toRegisterIndex(valveId) + 1;
	const int pinIndex		= app.shift.toPinIndex(valveId);

	app.shift.setAllRegistersLow();	 // Reset shift registers
	app.shift.writeLatchOut();
	app.shift.setRegister(registerIndex, pinIndex, HIGH);
	app.shift.setPin(TPICDevices::FLUSH_VALVE, HIGH);
	app.shift.write();
	app.pump.on();

	setTimeCondition(cleanTime, [&]() {
		sm.transitionTo("flush3");
	});
};

void OffshootPreload::enter(KPStateMachine & sm) {
	// Intake valve is opened and the motor is runnning ...
	// Turnoff only the flush valve
	auto & app = *static_cast<Application *>(sm.controller);
	app.shift.setPin(TPICDevices::FLUSH_VALVE, LOW);

	// Reserving space for 25 state conditions for performance
	reserve(25);

	for (int i = 0; i < app.config.numberOfValves; i++) {
		setTimeCondition(i * preloadTime, [&app, i]() {
			if (i > 0) {  // Turn off the previous valve
				const auto prevRegPin = app.shift.toRegisterAndPinIndices(i - 1);
				app.shift.setRegister(prevRegPin.first + 1, prevRegPin.second, LOW);
			}

			const auto regPin = app.shift.toRegisterAndPinIndices(i);
			app.shift.setRegister(regPin.first + 1, regPin.second, HIGH);
			app.shift.write();
		});
	};

	// Transition to the next state after the last valve
	setTimeCondition(app.config.numberOfValves * preloadTime, [&]() {
		sm.transitionTo("flush2");
	});
};

void NewFlush::enter(KPStateMachine & sm) {
	auto & app = *static_cast<Application *>(sm.controller);
	app.shift.setAllRegistersLow();
	app.shift.writeLatchIn();
	app.shift.setPin(TPICDevices::FLUSH_VALVE, HIGH);
	app.shift.write();
	app.pump.on();

	// To next state after 10 secs
	setTimeCondition(10000, [&]() {
		sm.transitionTo(nextStateName);
	});
};