# FlowMeter

## Purpose

**FlowMeter** is an Ardunino library that provides calibrated liquid flow and volume measurement with liquid flow sensors.

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

## Unit of measure

The **FlowMeter** library expresses flow in the unit **l/min**.
Most units of measure can be derived by simple conversion (just try not to measure in [Sverdrups](https://en.wikipedia.org/wiki/Sverdrup)).

As an example, conversion between **l/min** and US **gal/min** can be done with a factor of *3.78541178*, conversion from **min**  to **s** with a factor of *60*.

```math
3.78541178 l/min ≈ 1 gal/min ≈ 0.0167 gal/s.
```

## Installation

Just check out the [**FlowMeter**](https://github.com/sekdiy/FlowMeter) Repository on GitHub (or download the ZIP archive) and copy it to your `libraries/` folder (usually within your Arduino sketchbook).

In order to better follow the [examples](/examples) please also get and install the [**Streaming**](http://arduiniana.org/libraries/streaming/) library by Mikal Hart, which is a good idea anyway.

After (re)launching the Arduino IDE, **FlowMeter** will appear in your Sketchbook/Examples menu.

Alternatively, you can use Arduino's `Add .ZIP Library...` menu option.

## Calibration and Error

The **FlowMeter** library can be used with many different flow sensors (some examples are listed below).

There's a structure **FlowSensorProperties** in the library that you can use to customize the **FlowMeter** for your flow sensor:

```c++
typedef struct {
    double capacity;        // capacity
    double kFactor;         // k-factor
    double mFactor[10];     // m-factors
} FlowSensorProperties;
```

A default set of properties is supplied in order to get you started.

#### Capacity

One quality of a flow sensor is it's **capacity**, i.e. the maximum flow that it is able to handle without stalling or failing.

The **FlowMeter** stores the sensor capacity in the `capacity` field of a `FlowSensorProperties` structure.

#### K-Factor

This is the most important quantity of the flow sensor you use.

In theory a flow sensor (as considered in this library) converts a frequency into a flow rate.

The conversion factor between frequency *f* and flow rate *Q* is called the K-Factor *KF*:

```math
KF = f / Q
 Q = f / KF
```

The **FlowMeter** stores the K-Factor in the `kFactor` field of a `FlowSensorProperties` structure.

#### M-Factor

Practical flow sensors are non-ideal in that their output signal contains nonlinearities.

This error can be compensated by measuring volumes at different flow rates/frequencies/volumes and deriving a set of near-unity factors.

```math
MF = Q_actual / Q_nominal
   = f_actual / f_nominal
   = V_actual / V_nominal
```

The *meter factor* is applied during **FlowMeter's** internal calculations as follows (you don't need to do this yourself):

```math
Q_corrected = f / (KF / MF)
            = (f / KF) * MF
```

The **FlowMeter** stores the M-Factor in the `mFactor` field of a `FlowSensorProperties` structure. It can take ten data points, namely the deciles *0-10%* to *90-100%* of the sensor's `capacity` value.

If you don't provide individual `mFactor` values with your custom `FlowSensorProperties`, simply fill in the unity factor *1.0*.

#### Turndown ratio

The [turndown ratio](https://en.wikipedia.org/wiki/Turndown_ratio#Flow_meters) can be referred to as the "rangeability" of a sensor. It describes the ratio between maximum and minimum flow rates at which the sensor can still deliver a usable signal.

```math
turndown ratio = Q_max / Q_min
```

The turndown ratio of a typical flow meter can be  [assumed](https://en.wikipedia.org/wiki/Turndown_ratio#Typical_turndown_ratio_of_various_meter_types) as approximately 10:1.

You should consider this when choosing a flow sensor for your purpose. As a general rule, refrain from using a sensor at it's absolute maximum or minimum flow rate if you expect reliable results.

<!---
#### Accuracy (% RD vs. % FS)

A *%*RD* accuracy rating indicates an error referred to the meter's *capacity*

Example: 50 l/min with an accuracy of +/-1% RD means an error of +/-0.5 l/min.

{table}

"The accuracy (really inaccuracy) of mass flow instruments is specified in one of two ways, either accuracy as a percentage of full scale (% FS), or accuracy as a percentage of reading (% RD).
If an instrument has accuracy specified as % FS then the error will have a fixed value no matter where the flow is in the flow range. Take, for example, an instrument calibrated for a flow of 100 ln/min with stated accuracy 1.0% of FS. At a flow of 100 ln/min (full scale) the error will be 1% of full scale, or +/- 1 ln/min. As the flow moves way from full scale the error will still be 1% FS (+/- 1 ln/min), so at a flow of 50 ln/min that error of +/- 1 ln/min becomes a larger percentage (+/- 2%) of flow. Going further away from full scale flow further increases the error as a percentage of flow; at a flow of 10 ln/min the +/- 1 ln/min error is +/- 10% of the flow.

Accuracy
If, however, an instrument has accuracy specified as % RD then the error will always be the same percentage of the actual flow. Using the 100 ln/min instrument again as the example, but this time with a stated accuracy of 1% RD, at 10 ln/min of flow the error is only +/- 1% of the flow, better by 10 times."
-->

## Example Flow Sensors

#### FS300A

* Flow rate range: 1–60 l/min
* Precision: 3% (flow rate from 1L/min to 10L/min)
* K-Factor: 5.5

Source: [Seed Studio](http://www.seeedstudio.com/wiki/G3/4_Water_Flow_sensor).

![FS300A](/doc/P21408651.jpg)

Note that while the range figure suggests a turndown ratio of 60:1, the limits to the precision figure indicate an actual turndown ratio of 10:1.

![Flow Rate vs. Frequency](doc/G34_Flow_rate_to_frequency.jpg)

The flow rate vs. frequency diagram shows two slightly different specimen of the same sensor type. While the difference may seem small, your sensor may vary.

#### FS400A

* Flow rate range: 1–60 l/min
* Precision: none stated
* K-Factor: 4.8 (falsely stated as 56)

Source: [Ultisolar](http://ultisensor.com/post/G1-Hall-Effect-Flow-Sensor-USN-HS10TA-1-60Lmin.html)

![FS400A](/doc/USN-HS10TA.jpg)

This sensor is very similar to the FS300A.
Suitable for irrigation and wherever precision isn't crucial.

![Flow Rate vs. Frequency](doc/G1_pro3.jpg)

The values in this diagram show the difference between the different sensor models (i.e. different frequency per flow rate values).

It's never safe to assume linearity over the complete range.
Note how the diagram starts at *2 l/min* and ends at *10 l/min*, although the manufacturer states a range of *1–60 l/min*.

#### FHKSC

* Flow rate range: 0.05–1.2 l/min (depending on model)
* Precision: 2%
* Repeatability: 0.25%
* K-Factor: 20–40 (see [datasheet](/doc/932-950xBxxx_GB_20V.pdf))

Source: [Digimesa](http://www.digmesa.com/product-details/flow-sensor-fhksc/)

![FHKSC](doc/FHKSC.jpg)

A rather well documented flow sensor for the vending machine industry. Suitable in applications with lower pressures and flow rates. Higher precision than the above examples.

## Documentation

For further documentation please take a look at the examples in the `examples/` folder and the source code in the `src/` folder.

You can find datasheets, diagrams and pictures in the `doc/` folder.
