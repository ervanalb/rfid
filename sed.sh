cp rfid.kicad_pcb rfid_old.kicad_pcb
sed -r '/fp_text/N;s/(\(fp_text.+\n.*\(size )[^)]+\) \(thickness [^)]+/\10.762 0.762) (thickness 0.130/' rfid_old.kicad_pcb > rfid.kicad_pcb
