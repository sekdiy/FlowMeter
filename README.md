# Sekdiy FlowMeter Library [![Build Status](https://travis-ci.org/sekdiy/FlowMeter.svg?branch=master)](https://travis-ci.org/sekdiy/FlowMeter)

## Purpose

**FlowMeter** is an Arduino library that provides calibrated liquid flow and volume measurement with liquid flow sensors.

The library is primarily intended for use with impeller flow sensors and water, although other types of sensors and media could be made to work.

## Simple Example

Getting started with **FlowMeter** is easy. Take a look at this simple example:

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

In the above example, a flow sensor is assumed to be connected to the `INT0` pin. The corresponding object `Meter` is updated every `period` (in milliseconds, e.g. 1000ms) within the helper function `MeterISR`.

Please read on in the [Examples](https://github.com/sekdiy/FlowMeter/wiki/Examples) section of the library's [wiki pages](https://github.com/sekdiy/FlowMeter/wiki).

## Unit of measure

The **FlowMeter** library expresses flow in the unit **l/min**.
Most units of measure can be derived by simple conversion (just try not to measure in [Sverdrups](https://en.wikipedia.org/wiki/Sverdrup)).

As an example, conversion between **l/min** and US **gal/min** can be done with a factor of *3.78541178*, conversion from **min**  to **s** with a factor of *60*.

```math
3.78541178 l/min ≈ 1 gal/min ≈ 0.0167 gal/s.
```

## Installation

Just check out the [**FlowMeter**](https://github.com/sekdiy/FlowMeter) Repository on GitHub (or download the ZIP archive) and copy it to your `libraries/` folder (usually within your Arduino sketchbook).

After (re)launching the Arduino IDE, **FlowMeter** will appear in your Sketchbook/Examples menu.

Alternatively, you can use Arduino's `Add .ZIP Library...` menu option.

## Calibration and Error <a id="calibration-and-error"></a>

The **FlowMeter** library can be used with many different flow sensors (some examples are listed [below](#example-flow-sensors)).

[...](https://github.com/sekdiy/FlowMeter/wiki/Properties.md)

## Example Flow Sensors <a id="example-flow-sensors"></a>

[...](https://github.com/sekdiy/FlowMeter/wiki/Sensors.md)

## How to calibrate your own sensor

It's easy to calibrate yourself. Preferrably you'd do this after installing the sensor into your project. The flow meter then benefits from increased precision within the flow range of your application.

[...](https://github.com/sekdiy/FlowMeter/wiki/Calibration.md)

## Documentation

For further documentation please take a look at the **FlowMeter** [wiki pages](https://github.com/sekdiy/FlowMeter/wiki).

Also, the library source code (in the folder [`src/`](src/)) and the examples (in the folder [`examples/`](examples/)) are fully documented.
