# Teeny 4 CAN Tool

This directory has PCB schematics, BOMs, and Altium PCB project files.

All components are through hole, so it is easy to build with just a soldering iron.

PDFs of the schematics are available.

## Self-Assembly Instructions

### Materials

- Soldering iron
- Solder
- Teensy 4 CAN Tool PCB
- 30 AWG wire
- Wire cutters and strippers
- Good ventilation and lighting
- Bill of materials and all items listed
- PCB mount (recommended)
- Solder wick (recommended)

### Assembly

It is **highly** recommended assembling the board starting with the lowest profile components first (i.e. resistors and small capacitors) and the highest profile components near the end (i.e. headers, phoenix contacts, and jumpers). That way, it is much easier to align pins and solder the components properly or correct mistakes.

Solder items carefully, ensuring that pins are not bridged or lacking solder. Be wary of polarity for large capacitors and diodes. Properly dispose of component clippings.

The recommended order of population:

- Resistors (470 Ohm x4, 120 Ohm x3)
- Small Capacitors (0.1uF x3)
- IC (MCP2562 x3)
- LED's (GRN, YLW, RED, BLU)
- Headers (Female, 24 pin x2, 8 pin x2)
- Connectors (6 pin x1)
  - Cut into 3 sets of 2 pins ecah for the jumper connections
- Phoenix Contacts (x3)
- DSUB Connector
- Add terminating connections last (x3)

As for the Teensy 4.1 Board, solder (2x 24 pin Male Headers) then it can be directly placed onto the female headers on the CAN Tool PCB.

## Errata

The PCB board on revision 1 needs 30 AWG wire to be soldered from:

* CANH on Phoenix Connector to Pin 7 (CANH) on MCP2562 Designator U2
* Can RX/TX 3 to MCP2562 Designator U3
  * RX = Pin 30 On Teensy 4.1 -> Pin 4 (RX) on U3 MCP2562FD
  * TX = Pin 31 on Teensy 4.1 -> Pin 1 (TX) on U3 MCP2562FD

Pictures of the wiring are seen below:

![1671222418700](image/README/1671222418700.png)
