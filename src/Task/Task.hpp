#pragma once
#include <KPArray.hpp>
#include <KPFoundation.hpp>
#include <array>

#include <ArduinoJson.h>

#include <Application/Constants.hpp>
#include <Utilities/JsonEncodableDecodable.hpp>
#include <Utilities/JsonFileLoader.hpp>

struct Taskref;
struct Task : public JsonEncodable, public JsonDecodable, public Printable {
	char name[TaskSettings::NAME_LENGTH]{0};
	char notes[TaskSettings::NOTES_LENGTH]{0};

	int8_t valves[24]{0};
	int8_t valveCount		 = 0;
	int8_t currentValveIndex = -1;

	int status		 = 0;
	long creation	 = 0;
	long schedule	 = 0;
	long timeBetween = 0;

	unsigned long flushTime		 = 0;
	unsigned long flushVolume	 = 0;
	unsigned long sampleTime	 = 0;
	unsigned long samplePressure = 0;
	unsigned long sampleVolume	 = 0;
	unsigned long dryTime		 = 0;
	unsigned long preserveTime	 = 0;

	Task()					 = default;
	Task(const Task & other) = default;
	Task & operator=(const Task &) = default;

	explicit Task(const JsonObject & data) {
		decodeJSON(data);
	}

	//
	// ─── SECTION JSONDECODABLE COMPLIANCE ───────────────────────────────────────────
	//

	static const char * decoderName() {
		return "Task";
	}

	static constexpr size_t decoderSize() {
		return ProgramSettings::TASK_JSON_BUFFER_SIZE;
	}

	void load(const char * filepath) override {
		JsonFileLoader loader;
		loader.load(filepath, *this);
	}

	void decodeJSON(const JsonVariant & source) override {
		using namespace TaskSettings;

		if (source.containsKey("name")) {
			snprintf(name, NAME_LENGTH, "%s", source["name"].as<char *>());
		}

		if (source.containsKey("notes")) {
			snprintf(notes, NOTES_LENGTH, "%s", source["notes"].as<char *>());
		}

		if (source.containsKey("valves")) {
			copyArray(source["valves"], valves);
			valveCount		  = source["valves"].as<JsonArray>().size();
			currentValveIndex = source["currentValveIndex"];
		}

		creation	   = source["creation"];
		schedule	   = source["schedule"];
		status		   = source["status"];
		flushTime	   = source["flushTime"];
		flushVolume	   = source["flushVolume"];
		sampleTime	   = source["sampleTime"];
		samplePressure = source["samplePressure"];
		sampleVolume   = source["sampleVolume"];
		dryTime		   = source["dryTime"];
		preserveTime   = source["preserveTime"];
		timeBetween	   = source["timeBetween"];
	}

	//
	// ─── SECTION JSONENCODABLE COMPLIANCE ───────────────────────────────────────────
	//

	static const char * encoderName() {
		return "Task";
	}

	static constexpr size_t encoderSize() {
		return ProgramSettings::TASK_JSON_BUFFER_SIZE;
	}

	void save(const char * filepath) const override {
		JsonFileLoader loader;
		loader.save(filepath, *this);
	}

	bool encodeJSON(const JsonVariant & dest) const override {
		return dest["name"].set((char *) name)
			   && dest["notes"].set((char *) notes)
			   && dest["status"].set(status)
			   && dest["creation"].set(creation)
			   && dest["schedule"].set(schedule)
			   && dest["flushTime"].set(flushTime)
			   && dest["flushVolume"].set(flushVolume)
			   && dest["sampleTime"].set(sampleTime)
			   && dest["samplePressure"].set(samplePressure)
			   && dest["sampleVolume"].set(sampleVolume)
			   && dest["dryTime"].set(dryTime)
			   && dest["preserveTime"].set(preserveTime)
			   && dest["timeBetween"].set(timeBetween)
			   && copyArray(valves, valveCount, dest.createNestedArray("valves"))
			   && dest["currentValveIndex"].set(currentValveIndex);
	}

	size_t printTo(Print & printer) const override {
		StaticJsonDocument<encoderSize()> doc;
		JsonVariant object = doc.to<JsonVariant>();
		encodeJSON(object);
		return serializeJsonPretty(doc, Serial);
	}
};

// struct Taskref : public JsonEncodable, public JsonDecodable, public Printable {
// 	char name[TaskSettings::NAME_LENGTH]{0};

// 	Taskref()					   = default;
// 	Taskref(const Taskref & other) = default;
// 	Taskref & operator=(const Taskref &) = default;

// 	Taskref(const Task & task) {
// 		strcpy(name, task.name);
// 	}

// 	Taskref(const JsonObjectConst & data) {
// 		decodeJSON(data);
// 	}

// 	const char * decoderName() const {
// 		return "Taskref";
// 	}

// 	const char * encoderName() const {
// 		return "Taskref";
// 	}

// 	void load(const char * filepath) override {
// 		JsonFileLoader loader;
// 		loader.load<ProgramSettings::TASKREF_JSON_BUFFER_SIZE>(filepath, *this);
// 	}

// 	void save(const char * filepath) const override {
// 		JsonFileLoader loader;
// 		loader.save<ProgramSettings::TASKREF_JSON_BUFFER_SIZE>(filepath, *this);
// 	}

// 	void decodeJSON(const JsonObjectConst & source) override {
// 		using namespace TaskSettings;
// 		strncpy(name, source["name"], NAME_LENGTH);
// 		if (name[NAME_LENGTH - 1] != 0) {
// 			println("Warning (Task): Name exceeds its buffer size and will be truncated");
// 		}
// 	}

// 	bool encodeJSON(JsonVariant & dest) const override {
// 		return dest["name"].set((char *) name);
// 	}

// 	size_t printTo(Print & printer) const override {
// 		StaticJsonDocument<ProgramSettings::TASKREF_JSON_BUFFER_SIZE> doc;
// 		JsonVariant object = doc.to<JsonVariant>();
// 		encodeJSON(object);
// 		return serializeJsonPretty(object, Serial);
// 	}
// };
