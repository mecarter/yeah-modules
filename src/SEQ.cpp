#include "plugin.hpp"
#include <cmath>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <string>
using namespace std;

struct SEQ : Module
{
  enum ParamId
  {
    SEQ_1_OCT,
    SEQ_1_LEN,
    SEQ_1_01,
    SEQ_1_02,
    SEQ_1_03,
    SEQ_1_04,
    SEQ_1_05,
    SEQ_1_06,
    SEQ_1_07,
    SEQ_1_08,
    SEQ_1_09,
    SEQ_1_10,
    SEQ_2_OCT,
    SEQ_2_LEN,
    SEQ_2_01,
    SEQ_2_02,
    SEQ_2_03,
    SEQ_2_04,
    SEQ_2_05,
    SEQ_2_06,
    SEQ_2_07,
    SEQ_2_08,
    SEQ_2_09,
    SEQ_2_10,
    SEQ_3_OCT,
    SEQ_3_LEN,
    SEQ_3_01,
    SEQ_3_02,
    SEQ_3_03,
    SEQ_3_04,
    SEQ_3_05,
    SEQ_3_06,
    SEQ_3_07,
    SEQ_3_08,
    SEQ_3_09,
    SEQ_3_10,
    SEQ_4_OCT,
    SEQ_4_LEN,
    SEQ_4_01,
    SEQ_4_02,
    SEQ_4_03,
    SEQ_4_04,
    SEQ_4_05,
    SEQ_4_06,
    SEQ_4_07,
    SEQ_4_08,
    SEQ_4_09,
    SEQ_4_10,
    PARAMS_LEN
  };

  enum InputId
  {
    SEQ_1_TRIG,
    SEQ_2_TRIG,
    SEQ_3_TRIG,
    SEQ_4_TRIG,
    INPUTS_LEN
  };

  enum OutputId
  {
    SEQ_1_OUTPUT,
    SEQ_2_OUTPUT,
    SEQ_3_OUTPUT,
    SEQ_4_OUTPUT,
    OUTPUTS_LEN
  };

  enum LightId
  {
    SEQ_1_TRIG_LIGHT,
    SEQ_1_01_LIGHT,
    SEQ_1_02_LIGHT,
    SEQ_1_03_LIGHT,
    SEQ_1_04_LIGHT,
    SEQ_1_05_LIGHT,
    SEQ_1_06_LIGHT,
    SEQ_1_07_LIGHT,
    SEQ_1_08_LIGHT,
    SEQ_1_09_LIGHT,
    SEQ_1_10_LIGHT,
    SEQ_1_OUTPUT_LIGHT,
    SEQ_2_TRIG_LIGHT,
    SEQ_2_01_LIGHT,
    SEQ_2_02_LIGHT,
    SEQ_2_03_LIGHT,
    SEQ_2_04_LIGHT,
    SEQ_2_05_LIGHT,
    SEQ_2_06_LIGHT,
    SEQ_2_07_LIGHT,
    SEQ_2_08_LIGHT,
    SEQ_2_09_LIGHT,
    SEQ_2_10_LIGHT,
    SEQ_2_OUTPUT_LIGHT,
    SEQ_3_TRIG_LIGHT,
    SEQ_3_01_LIGHT,
    SEQ_3_02_LIGHT,
    SEQ_3_03_LIGHT,
    SEQ_3_04_LIGHT,
    SEQ_3_05_LIGHT,
    SEQ_3_06_LIGHT,
    SEQ_3_07_LIGHT,
    SEQ_3_08_LIGHT,
    SEQ_3_09_LIGHT,
    SEQ_3_10_LIGHT,
    SEQ_3_OUTPUT_LIGHT,
    SEQ_4_TRIG_LIGHT,
    SEQ_4_01_LIGHT,
    SEQ_4_02_LIGHT,
    SEQ_4_03_LIGHT,
    SEQ_4_04_LIGHT,
    SEQ_4_05_LIGHT,
    SEQ_4_06_LIGHT,
    SEQ_4_07_LIGHT,
    SEQ_4_08_LIGHT,
    SEQ_4_09_LIGHT,
    SEQ_4_10_LIGHT,
    SEQ_4_OUTPUT_LIGHT,
    LIGHTS_LEN
  };

  class Sequencer
  {
  public:
    int id;
    bool isTriggered = false;
    float triggerOffTimer = 0.f;
    int step = 1;
    float value = 0.0f;
    float trigger;
    int patternLength;
    int octave;
    float octaveDivider;
  };

  Sequencer seq[4];

  SEQ()
  {
    for (int i = 0; i < 2; i++)
    {
      seq[i].id = i;
    }

    config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);

    //
    // SEQUENCER 1
    //
    configInput(SEQ_1_TRIG, "Sequencer 1 trigger");

    configSwitch(SEQ_1_OCT, 0, 2, 2, "1/2/5v", {"1v", "2v", "5v"});

    configParam(SEQ_1_LEN, 0.f, 10.f, 10.f, "Sequencer 1 sequence length");

    configParam(SEQ_1_01, 0.f, 10.f, 0.f, "Sequencer 1 step 1");
    configParam(SEQ_1_02, 0.f, 10.f, 0.f, "Sequencer 1 step 2");
    configParam(SEQ_1_03, 0.f, 10.f, 0.f, "Sequencer 1 step 3");
    configParam(SEQ_1_04, 0.f, 10.f, 0.f, "Sequencer 1 step 4");
    configParam(SEQ_1_05, 0.f, 10.f, 0.f, "Sequencer 1 step 5");
    configParam(SEQ_1_06, 0.f, 10.f, 0.f, "Sequencer 1 step 6");
    configParam(SEQ_1_07, 0.f, 10.f, 0.f, "Sequencer 1 step 7");
    configParam(SEQ_1_08, 0.f, 10.f, 0.f, "Sequencer 1 step 8");
    configParam(SEQ_1_09, 0.f, 10.f, 0.f, "Sequencer 1 step 9");
    configParam(SEQ_1_10, 0.f, 10.f, 0.f, "Sequencer 1 step 10");

    configOutput(SEQ_1_OUTPUT, "Sequencer 1");

    //
    // SEQUENCER 2
    //
    configInput(SEQ_2_TRIG, "Sequencer 2 trigger");

    configSwitch(SEQ_2_OCT, 0, 2, 2, "1/2/5v", {"1v", "2v", "5v"});

    configParam(SEQ_2_LEN, 0.f, 10.f, 10.f, "Sequencer 2 sequence length");

    configParam(SEQ_2_01, 0.f, 10.f, 0.f, "Sequencer 2 step 1");
    configParam(SEQ_2_02, 0.f, 10.f, 0.f, "Sequencer 2 step 2");
    configParam(SEQ_2_03, 0.f, 10.f, 0.f, "Sequencer 2 step 3");
    configParam(SEQ_2_04, 0.f, 10.f, 0.f, "Sequencer 2 step 4");
    configParam(SEQ_2_05, 0.f, 10.f, 0.f, "Sequencer 2 step 5");
    configParam(SEQ_2_06, 0.f, 10.f, 0.f, "Sequencer 2 step 6");
    configParam(SEQ_2_07, 0.f, 10.f, 0.f, "Sequencer 2 step 7");
    configParam(SEQ_2_08, 0.f, 10.f, 0.f, "Sequencer 2 step 8");
    configParam(SEQ_2_09, 0.f, 10.f, 0.f, "Sequencer 2 step 9");
    configParam(SEQ_2_10, 0.f, 10.f, 0.f, "Sequencer 2 step 10");

    configOutput(SEQ_2_OUTPUT, "Sequencer 2");

    //
    // SEQUENCER 3
    //
    configInput(SEQ_3_TRIG, "Sequencer 3 trigger");

    configSwitch(SEQ_3_OCT, 0, 2, 2, "1/2/5v", {"1v", "2v", "5v"});

    configParam(SEQ_3_LEN, 0.f, 10.f, 10.f, "Sequencer 3 sequence length");

    configParam(SEQ_3_01, 0.f, 10.f, 0.f, "Sequencer 3 step 1");
    configParam(SEQ_3_02, 0.f, 10.f, 0.f, "Sequencer 3 step 2");
    configParam(SEQ_3_03, 0.f, 10.f, 0.f, "Sequencer 3 step 3");
    configParam(SEQ_3_04, 0.f, 10.f, 0.f, "Sequencer 3 step 4");
    configParam(SEQ_3_05, 0.f, 10.f, 0.f, "Sequencer 3 step 5");
    configParam(SEQ_3_06, 0.f, 10.f, 0.f, "Sequencer 3 step 6");
    configParam(SEQ_3_07, 0.f, 10.f, 0.f, "Sequencer 3 step 7");
    configParam(SEQ_3_08, 0.f, 10.f, 0.f, "Sequencer 3 step 8");
    configParam(SEQ_3_09, 0.f, 10.f, 0.f, "Sequencer 3 step 9");
    configParam(SEQ_3_10, 0.f, 10.f, 0.f, "Sequencer 3 step 10");

    configOutput(SEQ_3_OUTPUT, "Sequencer 3");

    //
    // SEQUENCER 4
    //
    configInput(SEQ_4_TRIG, "Sequencer 4 trigger");

    configSwitch(SEQ_4_OCT, 0, 2, 2, "1/2/5v", {"1v", "2v", "5v"});

    configParam(SEQ_4_LEN, 0.f, 10.f, 10.f, "Sequencer 4 sequence length");

    configParam(SEQ_4_01, 0.f, 10.f, 0.f, "Sequencer 4 step 1");
    configParam(SEQ_4_02, 0.f, 10.f, 0.f, "Sequencer 4 step 2");
    configParam(SEQ_4_03, 0.f, 10.f, 0.f, "Sequencer 4 step 3");
    configParam(SEQ_4_04, 0.f, 10.f, 0.f, "Sequencer 4 step 4");
    configParam(SEQ_4_05, 0.f, 10.f, 0.f, "Sequencer 4 step 5");
    configParam(SEQ_4_06, 0.f, 10.f, 0.f, "Sequencer 4 step 6");
    configParam(SEQ_4_07, 0.f, 10.f, 0.f, "Sequencer 4 step 7");
    configParam(SEQ_4_08, 0.f, 10.f, 0.f, "Sequencer 4 step 8");
    configParam(SEQ_4_09, 0.f, 10.f, 0.f, "Sequencer 4 step 9");
    configParam(SEQ_4_10, 0.f, 10.f, 0.f, "Sequencer 4 step 10");

    configOutput(SEQ_4_OUTPUT, "Sequencer 4");
  }

  void process(const ProcessArgs &args) override
  {
    for (int i = 0; i < 4; i++)
    {
      // Triggers
      // Seq 1
      if (i == 0)
      {
        seq[i].trigger = inputs[SEQ_1_TRIG].getVoltage();
      }
      // Seq 2
      if (i == 1)
      {
        if (!inputs[SEQ_2_TRIG].isConnected())
        {
          seq[i].trigger = inputs[SEQ_1_TRIG].getVoltage();
        }
        else
        {
          seq[i].trigger = inputs[SEQ_2_TRIG].getVoltage();
        }
      }
      // Seq 3
      if (i == 2)
      {
        if (!inputs[SEQ_3_TRIG].isConnected() && !inputs[SEQ_2_TRIG].isConnected())
        {
          seq[i].trigger = inputs[SEQ_1_TRIG].getVoltage();
        }
        else if (!inputs[SEQ_3_TRIG].isConnected())
        {
          seq[i].trigger = inputs[SEQ_2_TRIG].getVoltage();
        }
        else
        {
          seq[i].trigger = inputs[SEQ_3_TRIG].getVoltage();
        }
      }
      // Seq 4
      if (i == 3)
      {
        if (!inputs[SEQ_4_TRIG].isConnected() && !inputs[SEQ_3_TRIG].isConnected() && !inputs[SEQ_2_TRIG].isConnected())
        {
          seq[i].trigger = inputs[SEQ_1_TRIG].getVoltage();
        }
        else if (!inputs[SEQ_4_TRIG].isConnected() && !inputs[SEQ_3_TRIG].isConnected())
        {
          seq[i].trigger = inputs[SEQ_2_TRIG].getVoltage();
        }
        else if (!inputs[SEQ_4_TRIG].isConnected())
        {
          seq[i].trigger = inputs[SEQ_3_TRIG].getVoltage();
        }
        else
        {
          seq[i].trigger = inputs[SEQ_4_TRIG].getVoltage();
        }
      }

      //
      // Pattern length
      //
      // Seq 1
      if (i == 0)
      {
        seq[i].patternLength = floor(params[SEQ_1_LEN].getValue());
      }
      // Seq 2
      if (i == 1)
      {
        seq[i].patternLength = floor(params[SEQ_2_LEN].getValue());
      }
      // Seq 3
      if (i == 2)
      {
        seq[i].patternLength = floor(params[SEQ_3_LEN].getValue());
      }
      // Seq 4
      if (i == 3)
      {
        seq[i].patternLength = floor(params[SEQ_4_LEN].getValue());
      }

      //
      // Octave
      //
      // Seq 1
      if (i == 0)
      {
        seq[i].octave = params[SEQ_1_OCT].getValue();
      }
      // Seq 2
      if (i == 1)
      {
        seq[i].octave = params[SEQ_2_OCT].getValue();
      }
      // Seq 3
      if (i == 2)
      {
        seq[i].octave = params[SEQ_3_OCT].getValue();
      }
      // Seq 4
      if (i == 3)
      {
        seq[i].octave = params[SEQ_4_OCT].getValue();
      }

      //
      // Octave Divider
      //
      // Default
      seq[i].octaveDivider = 1.f;

      //
      // Trigger event
      //
      if (!seq[i].isTriggered && seq[i].trigger >= 5.f)
      {
        seq[i].isTriggered = true;
        seq[i].step++;

        if (seq[i].step > seq[i].patternLength)
        {
          seq[i].step = 1;
        }

        // Trigger light on
        if (i == 0)
        {
          lights[SEQ_1_TRIG_LIGHT].setBrightness(10.f);
        }
        if (i == 1)
        {
          lights[SEQ_2_TRIG_LIGHT].setBrightness(10.f);
        }
        if (i == 2)
        {
          lights[SEQ_3_TRIG_LIGHT].setBrightness(10.f);
        }
        if (i == 3)
        {
          lights[SEQ_4_TRIG_LIGHT].setBrightness(10.f);
        }
      }

      //
      // Trigger off event
      //
      if (seq[i].isTriggered && seq[i].trigger < 5.f)
      {
        seq[i].isTriggered = false;
        seq[i].triggerOffTimer = args.frame;
      }

      //
      // Trigger light off
      //
      if (seq[i].triggerOffTimer > 0.f && (args.frame - seq[i].triggerOffTimer >= 3000.f))
      {
        if (i == 0)
        {
          lights[SEQ_1_TRIG_LIGHT].setBrightness(0.f);
        }
        if (i == 1)
        {
          lights[SEQ_2_TRIG_LIGHT].setBrightness(0.f);
        }
        if (i == 2)
        {
          lights[SEQ_3_TRIG_LIGHT].setBrightness(0.f);
        }
        if (i == 3)
        {
          lights[SEQ_4_TRIG_LIGHT].setBrightness(0.f);
        }

        seq[i].triggerOffTimer = 0.f;
      }

      //
      // Set the voltage range from Octave Divider
      //
      switch (seq[i].octave)
      {
      // 1v
      case 0:
        seq[i].octaveDivider = 10.f;
        break;

      // 2v
      case 1:
        seq[i].octaveDivider = 5.f;
        break;

      // 5v / default
      default:
        seq[i].octaveDivider = 2.f;
      }

      //
      // Get the voltage at the current step
      //
      switch (seq[i].step)
      {
      case 1:
        // Seq 1
        if (i == 0)
        {
          seq[i].value = params[SEQ_1_01].getValue();
        }
        // Seq 2
        if (i == 1)
        {
          seq[i].value = params[SEQ_2_01].getValue();
        }
        // Seq 3
        if (i == 2)
        {
          seq[i].value = params[SEQ_3_01].getValue();
        }
        // Seq 4
        if (i == 3)
        {
          seq[i].value = params[SEQ_4_01].getValue();
        }
        break;

      case 2:
        // Seq 1
        if (i == 0)
        {
          seq[i].value = params[SEQ_1_02].getValue();
        }
        // Seq 2
        if (i == 1)
        {
          seq[i].value = params[SEQ_2_02].getValue();
        }
        // Seq 3
        if (i == 2)
        {
          seq[i].value = params[SEQ_3_02].getValue();
        }
        // Seq 4
        if (i == 3)
        {
          seq[i].value = params[SEQ_4_02].getValue();
        }
        break;

      case 3:
        // Seq 1
        if (i == 0)
        {
          seq[i].value = params[SEQ_1_03].getValue();
        }
        // Seq 2
        if (i == 1)
        {
          seq[i].value = params[SEQ_2_03].getValue();
        }
        // Seq 3
        if (i == 2)
        {
          seq[i].value = params[SEQ_3_03].getValue();
        }
        // Seq 4
        if (i == 3)
        {
          seq[i].value = params[SEQ_4_03].getValue();
        }
        break;

      case 4:
        // Seq 1
        if (i == 0)
        {
          seq[i].value = params[SEQ_1_04].getValue();
        }
        // Seq 2
        if (i == 1)
        {
          seq[i].value = params[SEQ_2_04].getValue();
        }
        // Seq 3
        if (i == 2)
        {
          seq[i].value = params[SEQ_3_04].getValue();
        }
        // Seq 4
        if (i == 3)
        {
          seq[i].value = params[SEQ_4_04].getValue();
        }
        break;

      case 5:
        // Seq 1
        if (i == 0)
        {
          seq[i].value = params[SEQ_1_05].getValue();
        }
        // Seq 2
        if (i == 1)
        {
          seq[i].value = params[SEQ_2_05].getValue();
        }
        // Seq 3
        if (i == 2)
        {
          seq[i].value = params[SEQ_3_05].getValue();
        }
        // Seq 4
        if (i == 3)
        {
          seq[i].value = params[SEQ_4_05].getValue();
        }
        break;

      case 6:
        // Seq 1
        if (i == 0)
        {
          seq[i].value = params[SEQ_1_06].getValue();
        }
        // Seq 2
        if (i == 1)
        {
          seq[i].value = params[SEQ_2_06].getValue();
        }
        // Seq 3
        if (i == 2)
        {
          seq[i].value = params[SEQ_3_06].getValue();
        }
        // Seq 4
        if (i == 3)
        {
          seq[i].value = params[SEQ_4_06].getValue();
        }
        break;

      case 7:
        // Seq 1
        if (i == 0)
        {
          seq[i].value = params[SEQ_1_07].getValue();
        }
        // Seq 2
        if (i == 1)
        {
          seq[i].value = params[SEQ_2_07].getValue();
        }
        // Seq 3
        if (i == 2)
        {
          seq[i].value = params[SEQ_3_07].getValue();
        }
        // Seq 4
        if (i == 3)
        {
          seq[i].value = params[SEQ_4_07].getValue();
        }
        break;

      case 8:
        // Seq 1
        if (i == 0)
        {
          seq[i].value = params[SEQ_1_08].getValue();
        }
        // Seq 2
        if (i == 1)
        {
          seq[i].value = params[SEQ_2_08].getValue();
        }
        // Seq 3
        if (i == 2)
        {
          seq[i].value = params[SEQ_3_08].getValue();
        }
        // Seq 4
        if (i == 3)
        {
          seq[i].value = params[SEQ_4_08].getValue();
        }
        break;

      case 9:
        // Seq 1
        if (i == 0)
        {
          seq[i].value = params[SEQ_1_09].getValue();
        }
        // Seq 2
        if (i == 1)
        {
          seq[i].value = params[SEQ_2_09].getValue();
        }
        // Seq 3
        if (i == 2)
        {
          seq[i].value = params[SEQ_3_09].getValue();
        }
        // Seq 4
        if (i == 3)
        {
          seq[i].value = params[SEQ_4_09].getValue();
        }
        break;

      case 10:
        // Seq 1
        if (i == 0)
        {
          seq[i].value = params[SEQ_1_10].getValue();
        }
        // Seq 2
        if (i == 1)
        {
          seq[i].value = params[SEQ_2_10].getValue();
        }
        // Seq 3
        if (i == 2)
        {
          seq[i].value = params[SEQ_3_10].getValue();
        }
        // Seq 4
        if (i == 3)
        {
          seq[i].value = params[SEQ_4_10].getValue();
        }
        break;
      }

      //
      // Step lights
      //
      // Seq 1
      if (i == 0)
      {
        lights[SEQ_1_01_LIGHT].setBrightness(seq[i].step == 1 ? 10.f : 0.f);
        lights[SEQ_1_02_LIGHT].setBrightness(seq[i].step == 2 ? 10.f : 0.f);
        lights[SEQ_1_03_LIGHT].setBrightness(seq[i].step == 3 ? 10.f : 0.f);
        lights[SEQ_1_04_LIGHT].setBrightness(seq[i].step == 4 ? 10.f : 0.f);
        lights[SEQ_1_05_LIGHT].setBrightness(seq[i].step == 5 ? 10.f : 0.f);
        lights[SEQ_1_06_LIGHT].setBrightness(seq[i].step == 6 ? 10.f : 0.f);
        lights[SEQ_1_07_LIGHT].setBrightness(seq[i].step == 7 ? 10.f : 0.f);
        lights[SEQ_1_08_LIGHT].setBrightness(seq[i].step == 8 ? 10.f : 0.f);
        lights[SEQ_1_09_LIGHT].setBrightness(seq[i].step == 9 ? 10.f : 0.f);
        lights[SEQ_1_10_LIGHT].setBrightness(seq[i].step == 10 ? 10.f : 0.f);
      }
      // Seq 2
      if (i == 1)
      {
        lights[SEQ_2_01_LIGHT].setBrightness(seq[i].step == 1 ? 10.f : 0.f);
        lights[SEQ_2_02_LIGHT].setBrightness(seq[i].step == 2 ? 10.f : 0.f);
        lights[SEQ_2_03_LIGHT].setBrightness(seq[i].step == 3 ? 10.f : 0.f);
        lights[SEQ_2_04_LIGHT].setBrightness(seq[i].step == 4 ? 10.f : 0.f);
        lights[SEQ_2_05_LIGHT].setBrightness(seq[i].step == 5 ? 10.f : 0.f);
        lights[SEQ_2_06_LIGHT].setBrightness(seq[i].step == 6 ? 10.f : 0.f);
        lights[SEQ_2_07_LIGHT].setBrightness(seq[i].step == 7 ? 10.f : 0.f);
        lights[SEQ_2_08_LIGHT].setBrightness(seq[i].step == 8 ? 10.f : 0.f);
        lights[SEQ_2_09_LIGHT].setBrightness(seq[i].step == 9 ? 10.f : 0.f);
        lights[SEQ_2_10_LIGHT].setBrightness(seq[i].step == 10 ? 10.f : 0.f);
      }
      // Seq 3
      if (i == 2)
      {
        lights[SEQ_3_01_LIGHT].setBrightness(seq[i].step == 1 ? 10.f : 0.f);
        lights[SEQ_3_02_LIGHT].setBrightness(seq[i].step == 2 ? 10.f : 0.f);
        lights[SEQ_3_03_LIGHT].setBrightness(seq[i].step == 3 ? 10.f : 0.f);
        lights[SEQ_3_04_LIGHT].setBrightness(seq[i].step == 4 ? 10.f : 0.f);
        lights[SEQ_3_05_LIGHT].setBrightness(seq[i].step == 5 ? 10.f : 0.f);
        lights[SEQ_3_06_LIGHT].setBrightness(seq[i].step == 6 ? 10.f : 0.f);
        lights[SEQ_3_07_LIGHT].setBrightness(seq[i].step == 7 ? 10.f : 0.f);
        lights[SEQ_3_08_LIGHT].setBrightness(seq[i].step == 8 ? 10.f : 0.f);
        lights[SEQ_3_09_LIGHT].setBrightness(seq[i].step == 9 ? 10.f : 0.f);
        lights[SEQ_3_10_LIGHT].setBrightness(seq[i].step == 10 ? 10.f : 0.f);
      }
      // Seq 4
      if (i == 3)
      {
        lights[SEQ_4_01_LIGHT].setBrightness(seq[i].step == 1 ? 10.f : 0.f);
        lights[SEQ_4_02_LIGHT].setBrightness(seq[i].step == 2 ? 10.f : 0.f);
        lights[SEQ_4_03_LIGHT].setBrightness(seq[i].step == 3 ? 10.f : 0.f);
        lights[SEQ_4_04_LIGHT].setBrightness(seq[i].step == 4 ? 10.f : 0.f);
        lights[SEQ_4_05_LIGHT].setBrightness(seq[i].step == 5 ? 10.f : 0.f);
        lights[SEQ_4_06_LIGHT].setBrightness(seq[i].step == 6 ? 10.f : 0.f);
        lights[SEQ_4_07_LIGHT].setBrightness(seq[i].step == 7 ? 10.f : 0.f);
        lights[SEQ_4_08_LIGHT].setBrightness(seq[i].step == 8 ? 10.f : 0.f);
        lights[SEQ_4_09_LIGHT].setBrightness(seq[i].step == 9 ? 10.f : 0.f);
        lights[SEQ_4_10_LIGHT].setBrightness(seq[i].step == 10 ? 10.f : 0.f);
      }

      //
      // Output!
      //
      // Seq 1
      if (i == 0)
      {
        outputs[SEQ_1_OUTPUT].setVoltage(seq[i].value / seq[i].octaveDivider);
        lights[SEQ_1_OUTPUT_LIGHT].setBrightness(seq[i].value / 10.f);
      }
      // Seq 2
      if (i == 1)
      {
        outputs[SEQ_2_OUTPUT].setVoltage(seq[i].value / seq[i].octaveDivider);
        lights[SEQ_2_OUTPUT_LIGHT].setBrightness(seq[i].value / 10.f);
      }
      // Seq 3
      if (i == 2)
      {
        outputs[SEQ_3_OUTPUT].setVoltage(seq[i].value / seq[i].octaveDivider);
        lights[SEQ_3_OUTPUT_LIGHT].setBrightness(seq[i].value / 10.f);
      }
      // Seq 4
      if (i == 3)
      {
        outputs[SEQ_4_OUTPUT].setVoltage(seq[i].value / seq[i].octaveDivider);
        lights[SEQ_4_OUTPUT_LIGHT].setBrightness(seq[i].value / 10.f);
      }
    }
  }
};

struct SEQWidget : ModuleWidget
{
  SEQWidget(SEQ *module)
  {
    setModule(module);
    setPanel(createPanel(asset::plugin(pluginInstance, "res/SEQ.svg")));

    addChild(createWidget<ScrewBlack>(Vec(RACK_GRID_WIDTH, 0)));
    addChild(createWidget<ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
    addChild(createWidget<ScrewBlack>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
    addChild(createWidget<ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

    float seqTrigX = 31.0f;
    float seqSwitchX = 68.0f;
    float seqStartX = 106.75f;
    float seqSpacing = 45.0f;
    float seqLightOffsetY = 24.2f;

    //
    // SEQUENCER 1
    //
    float seq1Y = 66.5f;

    addInput(createInputCentered<CL1362Port>(Vec(seqTrigX, seq1Y), module, SEQ::SEQ_1_TRIG));

    addParam(createParamCentered<BefacoSwitch>(Vec(seqSwitchX, seq1Y), module, SEQ::SEQ_1_OCT));

    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX, seq1Y), module, SEQ::SEQ_1_LEN));

    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + seqSpacing, seq1Y), module, SEQ::SEQ_1_01));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 2), seq1Y), module, SEQ::SEQ_1_02));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 3), seq1Y), module, SEQ::SEQ_1_03));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 4), seq1Y), module, SEQ::SEQ_1_04));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 5), seq1Y), module, SEQ::SEQ_1_05));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 6), seq1Y), module, SEQ::SEQ_1_06));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 7), seq1Y), module, SEQ::SEQ_1_07));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 8), seq1Y), module, SEQ::SEQ_1_08));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 9), seq1Y), module, SEQ::SEQ_1_09));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 10), seq1Y), module, SEQ::SEQ_1_10));

    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqTrigX, seq1Y + seqLightOffsetY), module, SEQ::SEQ_1_TRIG_LIGHT));

    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + seqSpacing, seq1Y + seqLightOffsetY), module, SEQ::SEQ_1_01_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 2), seq1Y + seqLightOffsetY), module, SEQ::SEQ_1_02_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 3), seq1Y + seqLightOffsetY), module, SEQ::SEQ_1_03_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 4), seq1Y + seqLightOffsetY), module, SEQ::SEQ_1_04_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 5), seq1Y + seqLightOffsetY), module, SEQ::SEQ_1_05_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 6), seq1Y + seqLightOffsetY), module, SEQ::SEQ_1_06_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 7), seq1Y + seqLightOffsetY), module, SEQ::SEQ_1_07_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 8), seq1Y + seqLightOffsetY), module, SEQ::SEQ_1_08_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 9), seq1Y + seqLightOffsetY), module, SEQ::SEQ_1_09_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 10), seq1Y + seqLightOffsetY), module, SEQ::SEQ_1_10_LIGHT));
    
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 11) - 2.5, seq1Y + seqLightOffsetY), module, SEQ::SEQ_1_OUTPUT_LIGHT));

    addOutput(createOutputCentered<CL1362Port>(Vec(seqStartX + (seqSpacing * 11) - 2.5, seq1Y), module, SEQ::SEQ_1_OUTPUT));

    //
    // SEQUENCER 2
    //
    float seq2Y = 150.f;

    addInput(createInputCentered<CL1362Port>(Vec(seqTrigX, seq2Y), module, SEQ::SEQ_2_TRIG));

    addParam(createParamCentered<BefacoSwitch>(Vec(seqSwitchX, seq2Y), module, SEQ::SEQ_2_OCT));

    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX, seq2Y), module, SEQ::SEQ_2_LEN));

    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + seqSpacing, seq2Y), module, SEQ::SEQ_2_01));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 2), seq2Y), module, SEQ::SEQ_2_02));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 3), seq2Y), module, SEQ::SEQ_2_03));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 4), seq2Y), module, SEQ::SEQ_2_04));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 5), seq2Y), module, SEQ::SEQ_2_05));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 6), seq2Y), module, SEQ::SEQ_2_06));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 7), seq2Y), module, SEQ::SEQ_2_07));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 8), seq2Y), module, SEQ::SEQ_2_08));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 9), seq2Y), module, SEQ::SEQ_2_09));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 10), seq2Y), module, SEQ::SEQ_2_10));

        addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqTrigX, seq2Y + seqLightOffsetY), module, SEQ::SEQ_2_TRIG_LIGHT));

    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + seqSpacing, seq2Y + seqLightOffsetY), module, SEQ::SEQ_2_01_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 2), seq2Y + seqLightOffsetY), module, SEQ::SEQ_2_02_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 3), seq2Y + seqLightOffsetY), module, SEQ::SEQ_2_03_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 4), seq2Y + seqLightOffsetY), module, SEQ::SEQ_2_04_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 5), seq2Y + seqLightOffsetY), module, SEQ::SEQ_2_05_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 6), seq2Y + seqLightOffsetY), module, SEQ::SEQ_2_06_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 7), seq2Y + seqLightOffsetY), module, SEQ::SEQ_2_07_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 8), seq2Y + seqLightOffsetY), module, SEQ::SEQ_2_08_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 9), seq2Y + seqLightOffsetY), module, SEQ::SEQ_2_09_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 10), seq2Y + seqLightOffsetY), module, SEQ::SEQ_2_10_LIGHT));
    
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 11) - 2.5, seq2Y + seqLightOffsetY), module, SEQ::SEQ_2_OUTPUT_LIGHT));

    addOutput(createOutputCentered<CL1362Port>(Vec(seqStartX + (seqSpacing * 11) - 2.5, seq2Y), module, SEQ::SEQ_2_OUTPUT));

    //
    // SEQUENCER 3
    //
    float seq3Y = 234.f;

    addInput(createInputCentered<CL1362Port>(Vec(seqTrigX, seq3Y), module, SEQ::SEQ_3_TRIG));

    addParam(createParamCentered<BefacoSwitch>(Vec(seqSwitchX, seq3Y), module, SEQ::SEQ_3_OCT));

    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX, seq3Y), module, SEQ::SEQ_3_LEN));

    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + seqSpacing, seq3Y), module, SEQ::SEQ_3_01));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 2), seq3Y), module, SEQ::SEQ_3_02));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 3), seq3Y), module, SEQ::SEQ_3_03));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 4), seq3Y), module, SEQ::SEQ_3_04));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 5), seq3Y), module, SEQ::SEQ_3_05));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 6), seq3Y), module, SEQ::SEQ_3_06));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 7), seq3Y), module, SEQ::SEQ_3_07));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 8), seq3Y), module, SEQ::SEQ_3_08));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 9), seq3Y), module, SEQ::SEQ_3_09));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 10), seq3Y), module, SEQ::SEQ_3_10));

        addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqTrigX, seq3Y + seqLightOffsetY), module, SEQ::SEQ_3_TRIG_LIGHT));

    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + seqSpacing, seq3Y + seqLightOffsetY), module, SEQ::SEQ_3_01_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 2), seq3Y + seqLightOffsetY), module, SEQ::SEQ_3_02_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 3), seq3Y + seqLightOffsetY), module, SEQ::SEQ_3_03_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 4), seq3Y + seqLightOffsetY), module, SEQ::SEQ_3_04_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 5), seq3Y + seqLightOffsetY), module, SEQ::SEQ_3_05_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 6), seq3Y + seqLightOffsetY), module, SEQ::SEQ_3_06_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 7), seq3Y + seqLightOffsetY), module, SEQ::SEQ_3_07_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 8), seq3Y + seqLightOffsetY), module, SEQ::SEQ_3_08_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 9), seq3Y + seqLightOffsetY), module, SEQ::SEQ_3_09_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 10), seq3Y + seqLightOffsetY), module, SEQ::SEQ_3_10_LIGHT));
    
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 11) - 2.5, seq3Y + seqLightOffsetY), module, SEQ::SEQ_3_OUTPUT_LIGHT));

    addOutput(createOutputCentered<CL1362Port>(Vec(seqStartX + (seqSpacing * 11) - 2.5, seq3Y), module, SEQ::SEQ_3_OUTPUT));

    //
    // SEQUENCER 4
    //
    float seq4Y = 318.f;

    addInput(createInputCentered<CL1362Port>(Vec(seqTrigX, seq4Y), module, SEQ::SEQ_4_TRIG));

    addParam(createParamCentered<BefacoSwitch>(Vec(seqSwitchX, seq4Y), module, SEQ::SEQ_4_OCT));

    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX, seq4Y), module, SEQ::SEQ_4_LEN));

    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + seqSpacing, seq4Y), module, SEQ::SEQ_4_01));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 2), seq4Y), module, SEQ::SEQ_4_02));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 3), seq4Y), module, SEQ::SEQ_4_03));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 4), seq4Y), module, SEQ::SEQ_4_04));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 5), seq4Y), module, SEQ::SEQ_4_05));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 6), seq4Y), module, SEQ::SEQ_4_06));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 7), seq4Y), module, SEQ::SEQ_4_07));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 8), seq4Y), module, SEQ::SEQ_4_08));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 9), seq4Y), module, SEQ::SEQ_4_09));
    addParam(createParamCentered<Davies1900hBlackKnob>(Vec(seqStartX + (seqSpacing * 10), seq4Y), module, SEQ::SEQ_4_10));

        addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqTrigX, seq4Y + seqLightOffsetY), module, SEQ::SEQ_4_TRIG_LIGHT));

    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + seqSpacing, seq4Y + seqLightOffsetY), module, SEQ::SEQ_4_01_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 2), seq4Y + seqLightOffsetY), module, SEQ::SEQ_4_02_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 3), seq4Y + seqLightOffsetY), module, SEQ::SEQ_4_03_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 4), seq4Y + seqLightOffsetY), module, SEQ::SEQ_4_04_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 5), seq4Y + seqLightOffsetY), module, SEQ::SEQ_4_05_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 6), seq4Y + seqLightOffsetY), module, SEQ::SEQ_4_06_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 7), seq4Y + seqLightOffsetY), module, SEQ::SEQ_4_07_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 8), seq4Y + seqLightOffsetY), module, SEQ::SEQ_4_08_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 9), seq4Y + seqLightOffsetY), module, SEQ::SEQ_4_09_LIGHT));
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 10), seq4Y + seqLightOffsetY), module, SEQ::SEQ_4_10_LIGHT));
    
    addChild(createLightCentered<MediumLight<GreenLight>>(Vec(seqStartX + (seqSpacing * 11) - 2.5, seq4Y + seqLightOffsetY), module, SEQ::SEQ_4_OUTPUT_LIGHT));

    addOutput(createOutputCentered<CL1362Port>(Vec(seqStartX + (seqSpacing * 11) - 2.5, seq4Y), module, SEQ::SEQ_4_OUTPUT));
  }
};

Model *modelSEQ = createModel<SEQ, SEQWidget>("SEQ");
