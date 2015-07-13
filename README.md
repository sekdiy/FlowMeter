# Simple Flow Meter

An Ardunino library that provides calibrated liquid flow and volume measurement with flow sensors.

## Calibration and Error

The **FlowMeter** library is primarily intended for use with impeller flow sensors, although other types of sensors could be made to work.

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

Consider the FS300A "Water Flow Sensor" (as sold by [Seeed Studio](http://www.seeedstudio.com/wiki/G3/4_Water_Flow_sensor), just to name one source).

{photo}

* range "1～60L/min", suggesting a turndown ratio of 60:1.

* Notice how no accuracy or reproducability figures are stated.

* Some websites show a figure of 'Accuracy: 2%'.

* Other sellers state '+/-10% accuracy' for identically looking sensors, which would be very poor performance.

* Pulse Frequency (Hz) = 5.5*Q +/- 2% where Q = water flow (L/min)
Q(water flow)= Frequency/5.5
