#include "plugin.hpp"
#include <cmath>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>
using namespace std;
// TODOS

// 1. A newly triggered Env should start from the previous CV
// 2. Add looping!

struct EGG : Module
{
	enum ParamId
	{
		ATT_TIME_PARAM,
		REL_TIME_PARAM,
		ATT_SLOPE_PARAM,
		REL_SLOPE_PARAM,
		IS_LOOPING_PARAM,
		PARAMS_LEN
	};

	enum InputId
	{
		TRIG_INPUT,
		REL_CV_INPUT,
		ATT_CV_INPUT,
		INPUTS_LEN
	};

	enum OutputId
	{
		OUT_OUTPUT,
		EOA_OUTPUT,
		EOC_OUTPUT,
		OUTPUTS_LEN
	};

	enum LightId
	{
		STATUS_LIGHT,
		LIGHTS_LEN
	};

	enum SlopeAlgorithms
	{
		LOGARITHMIC,
		LINEAR,
		EXPONENTIAL
	};

	EGG()
	{
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);

		configParam(ATT_TIME_PARAM, 0.f, 1.f, 0.05f, "Attack Time", "ms", 0.f, 1000.f);
		configParam(REL_TIME_PARAM, 0.f, 1.f, 0.1f, "Release Time", "ms", 0.f, 1000.f);
		configParam(ATT_SLOPE_PARAM, 0.f, 2.f, 1.f, "Attack Slope");
		configParam(REL_SLOPE_PARAM, 0.f, 2.f, 1.f, "Release Slope");
		configParam(IS_LOOPING_PARAM, 0.f, 1.f, 0.f, "Is Looping");

		configInput(TRIG_INPUT, "Trigger Input");
		configInput(REL_CV_INPUT, "Release Time CV");
		configInput(ATT_CV_INPUT, "Attack Time CV");

		configOutput(OUT_OUTPUT, "Output");
		configOutput(EOA_OUTPUT, "End of Attack Trigger");
		configOutput(EOC_OUTPUT, "End of Cycle Trigger");
	}

	struct Env
	{
		float startTime;
		float attEndTime;
		float relEndTime;
		float attAlgorithm;
		float relAlgorithm;
		bool isAtEoa;
		bool isFinished;
	};

	vector<Env> envs;

	Env createEnv(
			float startTime,
			float attEndTime,
			float relEndTime,
			float attAlgorithm,
			float relAlgorithm)
	{
		Env newEnv;
		newEnv.startTime = startTime;
		newEnv.attEndTime = attEndTime;
		newEnv.relEndTime = relEndTime;
		newEnv.attAlgorithm = attAlgorithm;
		newEnv.relAlgorithm = relAlgorithm;
		newEnv.isAtEoa = false;
		newEnv.isFinished = false;
		return newEnv;
	}

	float currentVoltage = 0.f;
	float eoaTimer = 0.f;
	float eocTimer = 0.f;
	bool isLooping = false;
	bool mightBeGate = false;

	float calculateAttPosition(
			float currentTime,
			float startTime,
			float attEndTime,
			float algorithm)
	{
		float percentThroughAttCycle = (currentTime - startTime) / (attEndTime - startTime);

		// LOGARITHMIC
		if (algorithm == LOGARITHMIC)
		{
			return sin(percentThroughAttCycle * (M_PI / 2)) * 10.f;
		}

		// EXPONENTIAL
		if (algorithm == EXPONENTIAL)
		{
			return (sin((-1.f + percentThroughAttCycle) * (M_PI / 2)) + 1.f) * 10.f;
		}

		// LINEAR
		return percentThroughAttCycle * 10.f;
	}

	float calculateRelPosition(
			float currentTime,
			float attEndTime,
			float relEndTime,
			float algorithm)
	{
		float percentThroughRelCycle = ((currentTime - attEndTime) / (relEndTime - attEndTime));

		// LOGARITHMIC
		if (algorithm == LOGARITHMIC)
		{
			return cos(percentThroughRelCycle * (M_PI / 2)) * 10.f;
		}

		// EXPONENTIAL
		if (algorithm == EXPONENTIAL)
		{
			return 1.4f - 4.1703 * log((percentThroughRelCycle + 0.1f) * 1.270981615210141);
		}

		// LINEAR
		return 10.f - percentThroughRelCycle * 10.f;
	}

	void process(const ProcessArgs &args) override
	{
		float trigInput = inputs[TRIG_INPUT].getVoltage();
		float attTimeParam = params[ATT_TIME_PARAM].getValue();
		float attCvInput = inputs[ATT_CV_INPUT].getVoltage();
		float attAlgorithm = params[ATT_SLOPE_PARAM].getValue();
		float relTimeParam = params[REL_TIME_PARAM].getValue();
		float isLoopingParam = params[IS_LOOPING_PARAM].getValue();
		float relCvInput = inputs[REL_CV_INPUT].getVoltage();
		float relAlgorithm = params[REL_SLOPE_PARAM].getValue();
		float currentTime = args.frame * args.sampleTime;

		float attTime = clamp(attTimeParam + (attCvInput / 10.f), 0.f, 1.f);
		float relTime = clamp(relTimeParam + (relCvInput / 10.f), 0.f, 1.f);

		// Start looping?
		if (!isLooping && isLoopingParam == 1)
		{
			isLooping = true;

			if (envs.size() == 0)
			{
				// startTime, attEndTime, relEndTime, algorithm
				envs.push_back(
						createEnv(
								currentTime,
								currentTime + attTime,
								currentTime + attTime + relTime,
								attAlgorithm,
								relAlgorithm));
			}
		}

		// Quit looping?
		if (isLooping && isLoopingParam == 0)
		{
			isLooping = false;
		}

		// Triggered!
		if (!mightBeGate && trigInput >= 5.f)
		{
			mightBeGate = true;

			// startTime, attEndTime, relEndTime, algorithm
			envs.push_back(
					createEnv(
							currentTime,
							currentTime + attTime,
							currentTime + attTime + relTime,
							attAlgorithm,
							relAlgorithm));
		}

		// Interpret gates as triggers
		if (mightBeGate && trigInput == 0.f)
		{
			mightBeGate = false;
		}

		// Garbage collection: remove spent Envs
		envs.erase(std::remove_if(envs.begin(), envs.end(), [](const Env &env)
															{ return env.isFinished; }),
							 envs.end());

		// Loop over each env in the queue
		for (auto &env : envs)
		{
			// Attack Cycle
			if (currentTime < env.attEndTime)
			{
				float newCurrentVoltage = calculateAttPosition(
						currentTime,
						env.startTime,
						env.attEndTime,
						env.attAlgorithm);

				// Allow previous env to play out
				if (newCurrentVoltage < currentVoltage - newCurrentVoltage)
				{
					currentVoltage = currentVoltage - newCurrentVoltage;
				}
				else
				{
					currentVoltage = newCurrentVoltage;
				}
			}

			if (!env.isAtEoa && currentTime >= env.attEndTime)
			{
				env.isAtEoa = true;
				eoaTimer = 0.01f;
			}

			// Release Cycle
			if (currentTime > env.attEndTime && currentTime < env.relEndTime)
			{
				currentVoltage = calculateRelPosition(
						currentTime,
						env.attEndTime,
						env.relEndTime,
						env.relAlgorithm);
			}

			if (currentTime > env.relEndTime)
			{
				env.isFinished = true;
				eocTimer = 0.01f;

				if (isLooping && &env == &envs.back())
				{
					// startTime, attEndTime, relEndTime, algorithm
					envs.push_back(
							createEnv(
									currentTime,
									currentTime + attTime,
									currentTime + attTime + relTime,
									attAlgorithm,
									relAlgorithm));
				}
			}
		}

		outputs[OUT_OUTPUT]
				.setVoltage(currentVoltage);
		lights[STATUS_LIGHT].setBrightness(currentVoltage / 10.f);

		if (eoaTimer > 0.f)
		{
			eoaTimer -= args.sampleTime;
			outputs[EOA_OUTPUT].setVoltage(10.f);
		}
		else
		{
			outputs[EOA_OUTPUT].setVoltage(0.f);
		}

		// EOC
		if (eocTimer > 0.f)
		{
			eocTimer -= args.sampleTime;
			outputs[EOC_OUTPUT].setVoltage(10.f);
		}
		else
		{
			eocTimer = 0.f;
			outputs[EOC_OUTPUT].setVoltage(0.f);
		}
	}
};

struct EGGWidget : ModuleWidget
{
	EGGWidget(EGG *module)
	{
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/EGG.svg")));

		addChild(createWidget<ScrewBlack>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewBlack>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<Davies1900hBlackKnob>(Vec(24, 114), module, EGG::ATT_TIME_PARAM));
		addParam(createParamCentered<Davies1900hBlackKnob>(Vec(66, 114), module, EGG::REL_TIME_PARAM));
		addParam(createParamCentered<BefacoSwitch>(Vec(27.5, 196.5), module, EGG::ATT_SLOPE_PARAM));
		addParam(createParamCentered<BefacoSwitch>(Vec(72, 196.5), module, EGG::REL_SLOPE_PARAM));

		addParam(createParamCentered<BefacoSwitch>(Vec(67, 51.5), module, EGG::IS_LOOPING_PARAM));

		addInput(createInputCentered<CL1362Port>(Vec(23, 51), module, EGG::TRIG_INPUT));
		addInput(createInputCentered<CL1362Port>(Vec(23, 158), module, EGG::ATT_CV_INPUT));
		addInput(createInputCentered<CL1362Port>(Vec(67, 158), module, EGG::REL_CV_INPUT));

		addOutput(createOutputCentered<CL1362Port>(Vec(45, 318), module, EGG::OUT_OUTPUT));
		addOutput(createOutputCentered<CL1362Port>(Vec(23, 261.5), module, EGG::EOA_OUTPUT));
		addOutput(createOutputCentered<CL1362Port>(Vec(67, 261.5), module, EGG::EOC_OUTPUT));

		addChild(createLightCentered<MediumLight<GreenLight>>(Vec(17.5, 318.5), module, EGG::STATUS_LIGHT));
	}
};

Model *modelEGG = createModel<EGG, EGGWidget>("EGG");
