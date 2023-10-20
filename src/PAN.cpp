#include "plugin.hpp"
#include <cmath>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>
using namespace std;

struct PAN : Module
{
  enum InputId
  {
    L1_INPUT,
    L2_INPUT,
    L3_INPUT,
    R1_INPUT,
    R2_INPUT,
    R3_INPUT,
    INPUTS_LEN
  };

  enum OutputId
  {
    L_OUTPUT,
    R_OUTPUT,
    OUTPUTS_LEN
  };

  PAN()
  {
    config(0, INPUTS_LEN, OUTPUTS_LEN);

    configInput(L1_INPUT, "Left 1");
    configInput(L2_INPUT, "Left 2");
    configInput(L3_INPUT, "Left 3");
    configInput(R1_INPUT, "Right 1");
    configInput(R2_INPUT, "Right 2");
    configInput(R3_INPUT, "Right 3");

    configOutput(L_OUTPUT, "Left");
    configOutput(R_OUTPUT, "Right");
  }

  void process(const ProcessArgs &args) override
  {
    float L3Input = inputs[L3_INPUT].getVoltage();
    float L2Input = inputs[L2_INPUT].getVoltage();
    float L1Input = inputs[L1_INPUT].getVoltage();
    float R1Input = inputs[R1_INPUT].getVoltage();
    float R2Input = inputs[R2_INPUT].getVoltage();
    float R3Input = inputs[R3_INPUT].getVoltage();

    float sumL =
        L3Input * 0.9 +
        L2Input * 0.75 +
        L1Input * 0.6 +
        R1Input * 0.45 +
        R2Input * 0.3 +
        R3Input * 0.15;

    float sumR =
        L3Input * 0.15 +
        L2Input * 0.3 +
        L1Input * 0.45 +
        R1Input * 0.6 +
        R2Input * 0.75 +
        R3Input * 0.9;

    outputs[L_OUTPUT].setVoltage(sumL);
    outputs[R_OUTPUT].setVoltage(sumR);
  }
};

struct PANWidget : ModuleWidget
{
  PANWidget(PAN *module)
  {
    setModule(module);
    setPanel(createPanel(asset::plugin(pluginInstance, "res/PAN.svg")));
    
    addChild(createWidget<ScrewBlack>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewBlack>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    float startingPoint = 37.75f;
    float endingPoint = 343.25f;
    float increment = (endingPoint - startingPoint) / 7;

    addInput(createInputCentered<CL1362Port>(Vec(21.875, startingPoint + increment), module, PAN::L3_INPUT));
    addInput(createInputCentered<CL1362Port>(Vec(21.875, startingPoint + (increment * 2)), module, PAN::L2_INPUT));
    addInput(createInputCentered<CL1362Port>(Vec(21.875, startingPoint + (increment * 3)), module, PAN::L1_INPUT));

    addInput(createInputCentered<CL1362Port>(Vec(21.875, startingPoint + (increment * 4)), module, PAN::R1_INPUT));
    addInput(createInputCentered<CL1362Port>(Vec(21.875, startingPoint + (increment * 5)), module, PAN::R2_INPUT));
    addInput(createInputCentered<CL1362Port>(Vec(21.875, startingPoint + (increment * 6)), module, PAN::R3_INPUT));

    addOutput(createOutputCentered<CL1362Port>(Vec(21.875, startingPoint), module, PAN::L_OUTPUT));
    addOutput(createOutputCentered<CL1362Port>(Vec(21.875, endingPoint), module, PAN::R_OUTPUT));
  }
};

Model *modelPAN = createModel<PAN, PANWidget>("PAN");
