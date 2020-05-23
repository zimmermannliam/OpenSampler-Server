#pragma once

//
// ────────────────────────────────────────────────────────────────────────── I ──────────
//   :::::: V A L V E   S T A T U S   E N U M : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────────────
//
// This pattern provides the same scoping functionality as class enum but is a class and
// therefore much more powerful
//
class ValveStatus {
public:
	enum Code {
		unavailable = -1,
		sampled,	// 0
		free,		// 1
		operating,	// 2
		next,
		missed
	} _code;

	ValveStatus(Code code)
		: _code(code) {
	}

	Code code() const {
		return _code;
	}

	// Implicit conversion to int
	operator int() const {
		return _code;
	}
};