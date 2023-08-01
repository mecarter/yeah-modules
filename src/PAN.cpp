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

    configInput(L1_INPUT, "Left 1 Input");
    configInput(L2_INPUT, "Left 2 Input");
    configInput(L3_INPUT, "Left 3 Input");
    configInput(R1_INPUT, "Right 1 Input");
    configInput(R2_INPUT, "Right 2 Input");
    configInput(R3_INPUT, "Right 3 Input");

    configOutput(L_OUTPUT, "Left Output");
    configOutput(R_OUTPUT, "Right Output");
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
    // 45.5
    addInput(createInputCentered<CL1362Port>(Vec(21.875, 70.25), module, PAN::L3_INPUT));
    addInput(createInputCentered<CL1362Port>(Vec(21.875, 115.75), module, PAN::L2_INPUT));
    addInput(createInputCentered<CL1362Port>(Vec(21.875, 161.25), module, PAN::L1_INPUT));

    addInput(createInputCentered<CL1362Port>(Vec(21.875, 206.75), module, PAN::R1_INPUT));
    addInput(createInputCentered<CL1362Port>(Vec(21.875, 252.25), module, PAN::R2_INPUT));
    addInput(createInputCentered<CL1362Port>(Vec(21.875, 297.75), module, PAN::R3_INPUT));

    addOutput(createOutputCentered<CL1362Port>(Vec(21.875, 24.75), module, PAN::L_OUTPUT));
    addOutput(createOutputCentered<CL1362Port>(Vec(21.875, 343.25), module, PAN::R_OUTPUT));
  }
};

Model *modelPAN = createModel<PAN, PANWidget>("PAN");
