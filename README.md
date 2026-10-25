# PocketSynth

PocketSynth is a small DIY electronic instrument built around a classic Arduino Nano. It uses eight push buttons to play notes and a ninth button to cycle between three octave settings. The firmware can mix up to four notes at once, creating simple polyphonic sound through a passive piezo buzzer.

## Features
- Eight note buttons for a C-major scale from C4 to C5.
- Four-note polyphony: up to four notes can sound simultaneously.
- Three octave settings: low, normal, and high, selected with the octave button.
- Button debouncing to help prevent accidental repeated state changes.
- Passive piezo output driven by timer-based waveform generation.


## Controls
Playing notes
Press any note button to play its assigned note. Up to four pressed note buttons are processed at once. If more than four note buttons are held, the firmware uses the first four pressed keys in the sketch's pin-array order (D2 through D9); additional held keys are ignored until one of those selected keys is released.

## Changing octaves
Press the button connected to D11 to cycle through the octave settings:
1. Normal — the frequencies listed in the pinout table
2. High — frequencies doubled
3. Low — frequencies halved
4. Then back to Normal
The initial setting after startup is Normal.

An enclosure was also build to house the PCB

<img width="1383" height="532" alt="image" src="https://github.com/user-attachments/assets/d48cb33b-2cc5-4c4e-bdcd-a993f509f98d" />


<img width="1682" height="728" alt="image" src="https://github.com/user-attachments/assets/1a9eac2e-c270-4c96-9476-76cf0d9eb251" />





##BOM

| Item             | Qty | Supplier     | Cost/item | Total Cost | link                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       |
|------------------|-----|--------------|-----------|------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| PCB              | 1   | JLCPCB       | $8.10     | $8.10      | https://cart.jlcpcb.com/quote?stencilLayer=2&stencilWidth=100&stencilLength=100&stencilCounts=5&plateType=1&spm=Jlcpcb.Homepage.1010                                                                                                                                                                                                                                                                                                                                                                       |
| Piezo Buzzer     | 1   | BastelGarage | $1.82     | $1.82      | https://www.bastelgarage.ch/piezo-buzzer-summer-aktiv?search=piezo                                                                                                                                                                                                                                                                                                                                                                                                                                         |
| Arduino Nano     | 1   | Amazon       | $11.99    | $11.99     | https://www.amazon.com/LUIRSAY-2Pcs-ATmega328P-Microcontroller-Compatible/dp/B0F1FQMNXM?crid=2W5GSQBC3HIJB&dib=eyJ2IjoiMSJ9.lGGUnkwyBAbnKti6S6SwYP2c6x-UGxlnKYzt2PNPgECSCdozHIAZ0OdamOZFqWbMvz8xpCRb1nKdGy6rfSHLUQPwaf3XGjoTjaAqPtBrrFQidVU9YVl90a602_HgnH4SrCyEkPTpDEKaLqP4j7S698Nc5fnB4vXDp_cE3KJylL8MgglIj20uxDazyTZKai4Y2EyphATkz1YSZvYsvpz0hkyqVcIGBWoc2mZFOu4FiWo.LpxEV_klTvgMHI9_awVb41E-o6UUeTSc5VZ7_uwAcRE&dib_tag=se&keywords=arduino+nano&qid=1792962564&sprefix=arduino+nan%2Caps%2C237&sr=8-3 |
| Switches         | 9   | BerryBase    | $1.12     | $10.08     | https://www.berrybase.ch/en/cherry-mx-blue-pushbutton-module-pcb-fixing-pin                                                                                                                                                                                                                                                                                                                                                                                                                                |
| Estimated total  |     |              |           | $31.99     |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            |
