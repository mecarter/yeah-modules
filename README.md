# Yeah! VCV Rack 2 Modules

## About the project

This is repository is a work-in-progress. I'm slowly building a small library of useful plugins for
VCV Rack 2  with the intention of adding them to the [VCV Rack library](https://library.vcvrack.com/)
at some point in the future.

If you want to see what's inside, it's possible to clone this repository and buid the plugins locally.
For information about running this repository locally, refer to VCV Rack's documentation
[here](https://vcvrack.com/manual/PluginDevelopmentTutorial).

## What's inside (so far):

### EGG (Envelope GGenerator)

<img width="123" alt="EGG-screenshot" src="https://github.com/user-attachments/assets/886e167b-70bc-4a6b-9676-d89bd8ecdba0" />

EGG is a function/envelope generator with some handy features.

* **TRIG input:** trigger a new envelope with a pulse (gates will also work).
* **LOOP switch:** continuously trigger new envelopes as the previous envelope completes its cycle.
* **ATT knob:** set the attack time between 0-1000ms.
* **ATT input:** use CV to change the attack time (overrides knob setting).
* **ATT shape switch:** choose exponential, linear or logarithmic.
* **REL knob:** set the release time between 0-1000ms.
* **REL input:** use CV to change the release time (overrides knob setting).
* **REL shape switch:** choose exponential, linear or logarithmic.
* **EOA output**: sends a pulse when the attack phase is complete.
* **EOC output**: sends a pulse when the envelope cycle is complete.
* **ENV output**: sends the envelope output.

### The SEEQER (4 independent rhythm track 10 step sequencer)

<img width="935" alt="SEEQER-screenshot" src="https://github.com/user-attachments/assets/44a90a79-5477-4f91-8fdb-b813149756fa" />

The SEEQER is a 10 step sequencer with 4 tracks with independent trigger inputs for clocking at
different tempos or rhythmic divisions.

Each track has these features:

* **TRIG input**: a trigger input that accepts a pulse to advance to the next step in the sequence. Normalled to the input above (if present).
* **RANGE switch**: choose between 1v, 2v, or 5v range for the output signal.
* **LENGTH knob**: select the number of steps in the sequence, from 1-10.
* **SEQUENCE knobs**: each knob represents a step in the sequence. The output value will be scaled based on the RANGE value.
* **CV OUT output**: sequence value output.

### PAN (stereo field mixer)

<img width="108" alt="PAN-screenshot" src="https://github.com/user-attachments/assets/ecfab103-6afd-481d-ad24-7351ea81575b" />

Inspired by the [Takaab Nearness](https://modulargrid.net/e/takaab-nearness), this module is a minimalistic stereo
panning mixer. The L output is at the top, and the R output is at the bottom. Each input is panned closer to its
L/R output with the more central inputs panned closer to center. For example, Left Input 3 will be panned further
Left than Left Input 1.
