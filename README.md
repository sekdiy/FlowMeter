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

See the complete source code of the [**Simple**](examples/Simple/Simple.ino) example (included with this library) for more.

## Simulation Example <a id="simulation-example"></a>

```c++
// let's provide our own sensor properties, including calibration points for error correction
FlowSensorProperties MySensor = {50.0f, 4.8f, {1.2, 1.1, 1.05, 1, 1, 1, 1, 0.95, 0.9, 0.8}};

// let's pretend there's a flow sensor connected to pin 3
FlowMeter Meter = FlowMeter(3, MySensor);
```

In this example, the `FlowMeter` object `Meter` is initialized to pin 3 using a custom `FlowSensorProperties` structure `MySensor`.

This structure holds the following values (written in a compact inline notation):

```c++
MySensor.capacity = 50.0f;
MySensor.kFactor = 4.8f;
MySensor.mFactor = {1.2, 1.1, 1.05, 1, 1, 1, 1, 0.95, 0.9, 0.8};
```

The `mFactor` array provides a non-linear, flow dependent correction to the otherwise flow independent `kFactor`.
The ten data points in the array correspond to flow rates within the [centiles](https://en.wikipedia.org/wiki/Percentile) (0%, 10%, 20%, 30%, 40%, 50%, 60%, 70%, 80% and 90%) of the `capacity` value, respectively.

The example then randomly simulates a sensor frequency and measurement period.
The flow rate varies between 0 and `capacity` with updates after up to five seconds.

After running the simulation for a while, the average flow rate settles around `capacity/2` and the average error converges towards 0 (since the `mFactor` array has a mean value of 1).
You can of course play with the values in `MySensor` to see how this changes the behaviour.

<!---
So what this example demonstrates is how the error correction works and that the results are independent of how long or short your measurement periods are (within limits, of course).
-->

See [below](#calibration-and-error) for the math and motivation behind sensor calibration. The complete source code of the [**Simulation**](examples/Simulator/Simulator.ino) example is included with this library.

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

[...](wiki/Properties.md)

## Example Flow Sensors <a id="example-flow-sensors"></a>

[...](wiki/Sensors.md)

## How to calibrate your own sensor

It's easy to calibrate yourself. Preferrably you'd do this after installing the sensor into your project. The flow meter then benefits from increased precision within the flow range of your application.

[...](wiki/Calibration.md)

## Documentation

For further documentation please take a look at the **FlowMeter** [wiki pages](wiki/).

You can find additional datasheets, diagrams and pictures in the folder `doc/`.

Also, the library source code (in the folder [`src/`](src/)) and the examples (in the folder [`examples/`](examples/)) are fully documented.
