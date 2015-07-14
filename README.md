# FlowMeter

## Purpose

**FlowMeter** is an Ardunino library that provides calibrated liquid flow and volume measurement with liquid flow sensors.

The library is primarily intended for use with impeller flow sensors and water, although other types of sensors and media could be made to work.

## Simple Example ##

Getting started with **FlowMeter** is easy. Take a look at the [simple](/examples/Simple/Simple.ino) example:

```c++
void setup() {
  // prepare serial communication
  Serial.begin(9600);

  // enable a call to a helper function on every rising edge
  attachInterrupt(INT0, MeterISR, RISING);
}

void loop() {
  // wait between output updates
  delay(period);

  // process the (possibly) counted ticks
  Meter.tick(period);

  // output some measurement result
  Serial.print("Currently ");
  Serial.print(Meter.getCurrentFlowrate());
  Serial.print(" l/min, ");
  Serial.print(Meter.getTotalVolume());
  Serial.println(" l total.");

  //
  // any other code can go here
  //
}
```

In the above example, a flow sensor is assumed to be connected to the `INT0` pin. The corresponding object `Meter` is updated every `period` (in milliseconds, e.g. 1000ms).

See the source code of the [**Simple**](examples/Simple/Simple.ino) example (included with this library) for more.

## Installation ##

Just check out the [**FlowMeter**](https://github.com/sekdiy/FlowMeter) Repository on GitHub (or download the ZIP archive) and copy it to your `libraries/` folder (usually within your Arduino sketchbook).

In order to better follow the [examples](/examples) please also get and install the [**Streaming**](http://arduiniana.org/libraries/streaming/) library by Mikal Hart, which is a good idea anyway.

After (re)launching the Arduino IDE, **FlowMeter** will appear in your Sketchbook/Examples menu.

Alternatively, you can use Arduino's `Add .ZIP Library...` menu option.

## Error and Calibration

#### K-Factor

#### Meter Factor

Q_corrected = KF / MF

#### [turndown ratio](https://en.wikipedia.org/wiki/Turndown_ratio#Flow_meters)

"rangeability"

turndown ratio = maximum flow / minimum flow

The turndown ratio of a typical flow meter is [stated](https://en.wikipedia.org/wiki/Turndown_ratio#Typical_turndown_ratio_of_various_meter_types) as approximately 10:1.

#### Accuracy (% RD vs. % FS)

A *%*RD* accuracy rating indicates an error referred to the meter's *capacity*

Example: 50 l/min with an accuracy of +/-1% RD means an error of +/-0.5 l/min.

{table}

"The accuracy (really inaccuracy) of mass flow instruments is specified in one of two ways, either accuracy as a percentage of full scale (% FS), or accuracy as a percentage of reading (% RD).
If an instrument has accuracy specified as % FS then the error will have a fixed value no matter where the flow is in the flow range. Take, for example, an instrument calibrated for a flow of 100 ln/min with stated accuracy 1.0% of FS. At a flow of 100 ln/min (full scale) the error will be 1% of full scale, or +/- 1 ln/min. As the flow moves way from full scale the error will still be 1% FS (+/- 1 ln/min), so at a flow of 50 ln/min that error of +/- 1 ln/min becomes a larger percentage (+/- 2%) of flow. Going further away from full scale flow further increases the error as a percentage of flow; at a flow of 10 ln/min the +/- 1 ln/min error is +/- 10% of the flow.

Accuracy
If, however, an instrument has accuracy specified as % RD then the error will always be the same percentage of the actual flow. Using the 100 ln/min instrument again as the example, but this time with a stated accuracy of 1% RD, at 10 ln/min of flow the error is only +/- 1% of the flow, better by 10 times."

## Example Flow Meter

Consider the FS300A "Water Flow Sensor":

* Flow rate range: 1～60L/min
* Precision: 3% (flow rate from 1L/min to 10L/min)
* K-Factor: 5.5

Source: [Seed Studio](http://www.seeedstudio.com/wiki/G3/4_Water_Flow_sensor).

![FS300A](/doc/P21408651.jpg "Source: [Seed Studio](http://www.seeedstudio.com/wiki/G3/4_Water_Flow_sensor)")

Note that while the range figure suggests a turndown ratio of 60:1, the limits to the precision figure indicate an actual turndown ratio of 10:1.

Other sellers state '+/-10% accuracy' for identically looking sensors, which would be a very poor performance.

## Documentation

...
