#include "plugin.hpp"
#include "../rust/target/cxxbridge/synth/src/lib.rs.h"

struct RustModule : Module {
	enum ParamId {
		PITCH_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		PITCH_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		SINE_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		BLINK_LIGHT,
		LIGHTS_LEN
	};

    ::rust::Box<Synth> rustSynth;


    RustModule() : rustSynth(new_synth()) {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(PITCH_PARAM, 0.f, 1.f, 0.f, "");
		configInput(PITCH_INPUT, "");
		configOutput(SINE_OUTPUT, "");

	}

	void process(const ProcessArgs& args) override {
        // auto rustSynth = new_synth();

        float pitchInput = params[PITCH_PARAM].getValue();
        rustSynth->set_frequency(pitchInput*1000.0);

        float nextSample = rustSynth->next_sample();
        outputs[SINE_OUTPUT].setVoltage(nextSample/5000.0);
	}
};


struct RustModuleWidget : ModuleWidget {
	RustModuleWidget(RustModule* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/RustModule.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.24, 46.063)), module, RustModule::PITCH_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(15.24, 77.478)), module, RustModule::PITCH_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.24, 108.713)), module, RustModule::SINE_OUTPUT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 25.81)), module, RustModule::BLINK_LIGHT));
	}
};


Model* modelRustModule = createModel<RustModule, RustModuleWidget>("RustModule");