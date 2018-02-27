# FlowMeter Library [![Version](https://img.shields.io/badge/FlowMeter-1.1.0-blue.svg 'still in beta')](https://github.com/sekdiy/FlowMeter) [![Build Status](https://travis-ci.org/sekdiy/FlowMeter.svg?branch=master)](https://travis-ci.org/sekdiy/FlowMeter) [![analytics](http://www.google-analytics.com/collect?v=1&t=pageview&dl=https%3A%2F%2Fgithub.com%2Fsekdiy%2FFlowMeter&cid=2238D739-76DE-4205-9768-2F3277FA2561&tid=UA-65656434-2&aip=1&dt=README)]()

**FlowMeter** is an Arduino library that provides calibrated flow and volume measurement with flow sensors.

You can use it to count flow and volume of liquids and gases (although the documentation focuses on applications using liquids) and can support multiple flow sensors at the same time.

It also works as a totalizer, accumulating total volume and average flow rate over the run time of your project.

A provision for calibration helps you to get the most out of your sensor. You can even estimate the recent and overall error margin.

The library is intended for use with flow sensors that provide a frequency output signal proportional to flow, although other types of sensors could be made to work.

## A Simple Example

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

In the above example, a flow sensor is assumed to be connected to the `INT0` pin. The corresponding object `Meter` is updated every `period` (in milliseconds, e.g. 1000ms).

So after every measurement `period`, the current *flow rate* and the total *volume* are printed out.

Please read on in the [examples](https://github.com/sekdiy/FlowMeter/wiki/Examples) section of the library's [documentation pages](https://github.com/sekdiy/FlowMeter/wiki).

## Installing the library

Just check out the [**FlowMeter**](https://github.com/sekdiy/FlowMeter) Repository on GitHub (or download the ZIP archive) and copy it to your `libraries/` folder (usually within your Arduino sketchbook).

See the [installation](https://github.com/sekdiy/FlowMeter/wiki/Installation) section in the [documentation pages](https://github.com/sekdiy/FlowMeter/wiki) for more.

## Unit of measure

The **FlowMeter** library expresses flow in the unit **l/min**.
Most units of measure can be derived by simple conversion (just try not to measure in [Sverdrups](https://en.wikipedia.org/wiki/Sverdrup)).

As an example, conversion between **l/min** and US **gal/min** can be done with a factor of *3.78541178*, conversion from **min**  to **s** with a factor of *60*.

```math
3.78541178 l/min ≈ 1 gal/min ≈ 0.0167 gal/s.
```

Please make sure you consult the [documentation](https://github.com/sekdiy/FlowMeter/wiki/Properties) in order to further understand how the library works.

## Should you calibrate your own sensor?

The **FlowMeter** library can be used with many different flow sensors right away. Some [sensor examples](https://github.com/sekdiy/FlowMeter/wiki/Sensors) are listed in the documentation.

For many projects you don't need to worry about calibration. But it still makes sense to be aware of the limitations that come with an uncalibrated sensor in a metering application.

It's easy to calibrate yourself. Preferrably you'd do this after installing the sensor into your project. The flow meter then benefits from increased precision within the viscosity and flow range of your application.

There's a [complete how-to](https://github.com/sekdiy/FlowMeter/wiki/Calibration) in the documentation.

![Calibration Example: Irrigation with FS400A](https://github.com/sekdiy/FlowMeter/wiki/images/FS400A-calibration.jpg)

## Documentation

For further details please take a look at the **FlowMeter** [documentation pages](https://github.com/sekdiy/FlowMeter/wiki).

Also, the library source code (in the folder [`src/`](src/)) and the examples (in the folder [`examples/`](examples/)) are fully documented.
