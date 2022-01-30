# FrozenAt V0.5

(This tool is for AmigaOS4.1)

A small command line tool to find out where a program is hanging.

Unlike a normal crash, a program that stuck in a infinity loop can be hard to debug, I expect the OS developers has a tool like this, but as far as I know it’s not publicly available.
This took should be used in combination with IRA disassemble tool.

The tool should give you an offset in the exe file, and IRA should provide offset address to match in the disassembled code.
In 2022, we are looking whys to fix problems in software related to old busy loops, waiting for changes in hardware register. Finding this problematic place in programs / assembly code, so we make software patches.

Before using disable JIT compiler in compatibility prefs.
AmigaOS4.1 uses a check sum and the size of program to detect if the program, executed by JIT compiler or interpreter.

Using:

FrozenAt ProgramName

Will show as starck trace with information about a running program.
