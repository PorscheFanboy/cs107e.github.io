This project contains a sample project set up with prototype build files

- makefile that links project against libpi
    - LIBPI_STUDENT_MODULES can be used to substitute student version
    - otherwise will pull from reference libpi

- canonical link map
- cstart.c

    - zeros bss
    - turns on LED 47 after main() completes
- start.s 

    - init sp = 0x800000