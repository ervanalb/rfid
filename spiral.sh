#!/bin/bash

sed \$d rfid_orig.kicad_pcb > rfid.kicad_pcb
python spiraller.py >> rfid.kicad_pcb
echo ")" >> rfid.kicad_pcb
