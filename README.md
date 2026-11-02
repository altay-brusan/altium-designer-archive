# Altium Designer Archive

A collection of public Altium Designer resources (component libraries, scripts, example projects and reference designs) plus embedded-systems training material.

## Contents

### `Public Altium libraries/`
Schematic, PCB and integrated libraries for Altium Designer.

- **Components/**: about 76 downloaded component packages (symbols, footprints, 3D models).
- **3D models/**: STEP models for chip capacitors (`CAPC`), inductors (`INDC`) and resistors (`RESC`).
- **mouser/**: component libraries downloaded from Mouser.
- Project libraries: *Battery Holder*, *Water Tank Telemeter*, *iMX6 Rex Development Baseboard* (`.SchLib`, `.PcbLib`, `.IntLib`, `.LibPkg`).

### `Public Altium scripts/`
Altium's sample scripts, grouped by scripting language:

| Folder | Language |
|---|---|
| `Delphiscript Scripts/` | DelphiScript (`.pas`): DXP, FPGA, General, PCB, Processes, SCH, WSM |
| `EnableBasic Scripts/` | EnableBasic (`.bas`) |
| `JScript Scripts/` | JScript (`.js`) |
| `VB Scripts/` | VBScript (`.vbs`) |
| `Query Scripts/` | Query-language scripts |

To run a script in Altium Designer, open the `.PrjScr` project and go to **DXP » Run Script**.

### `Public Altium tools/`
- **Examples/**: Circuit simulation, CIS / database libraries, PCB auto-routing, scripts, signal integrity, snippets, soft designs, tutorials and VHDL simulation.
- **Reference-Designs/**: Altium reference boards, including NanoBoard NB1/NB2DSK/NB3000, daughter boards, Weather Station, SpiritLevel, Universal JTAG Interface, VideoMultiplexer and more.

### `Trainings/`
Embedded-systems training material:
- ARM / STM32 reference documents: ARM Compiler reference, Cortex-M4 programming manual, STM32F4 datasheets and reference manual, EMC design guide.
- **CortexMxProgramming-master/**: example code for the course *Embedded System Programming on ARM Cortex-Mx* (operation modes, bit-banding, stack, interrupts, faults, SVC, task scheduler).

## Notes
- The original `Examples.zip` and `Reference-Designs.zip` archives are left out of the repo. They duplicate the extracted folders, and `Reference-Designs.zip` is larger than GitHub's 100 MB file limit.
- All content belongs to its original authors (Altium, component vendors, ARM, STMicroelectronics, course authors). This archive is for reference and learning.
