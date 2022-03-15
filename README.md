# Hind-Rectifiers-42kVA-Auxiliary-Power-Unit
42kVA DC-DC Converter followed by a 3 Phase Inverter for Mumbai Monorail

This systems is divided into two stages. The first stage consists of a novel DC-DC Converter. 
While in the second stage there are two outputs.
The first output is 24V and 450A DC output. The second output is a 415V and 30A 3-Phase AC output.
This novel DC-DC Converter has two Phase-Shifted Full Bridge Converters whose input sides are connected in parallel while the output of each of the PSFB is connected to its individual 1-phase high frequency transformer.
The output of these transformers are connected its own 1-phase diode bridge rectifier.
However there is one caveat, one of the leg of each these rectifier is shared with each other.
As a result of this, when the phase shift between the two converters is large, it is equivalent to the converters being connected in parallel on the output side.
Similarly, when the phase shift between the two converters is small, it is equivalent to the converters being connected in series on the output side.
This gives us very large operating range and makes the system very robust.
There are two DC links for the two outputs.
The first DC Link is the 24V and 450A DC output itself.
For the second output the second DC link voltage is 750V and it is connected to a 3-Phase inverter.
This 3-Phase inverter implements Space Vector Modulation as it has higher operating range and is more rpbust, however provisions have been made to implement Sinusoidal Pulsewidth Modulation as well.
