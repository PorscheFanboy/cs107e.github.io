---
layout: page
title: Guide to Bare Metal Programming with GCC
---

*Written by Pat Hanrahan*

### Hosted versus non-hosted (standalone) environments
A typical program is compiled for a _hosted_ system where it has access to the standard libraries and facilities provided by the operating system layer. In hosted mode, the program runs at the pleasure of the host operating system.
In contrast, a bare metal program is non-hosted; it does not stand on top of an operating system or library; it runs entirely standalone. The program has the freedom to do whatever it wants, without any pesky interference from a overbearing OS, but cannot count on any facilities other than what it provides for itself.

The `gcc` default is to compile assuming a hosted environment, as this is the common case. To properly compile a bare metal program, we need to set the appropriate compiler and linker options to ensure the program is configured to run standalone.

### Compiler option -ffreestanding
This `gcc` option directs the compiler to limit this program to only those features available in the freestanding environment. 

	% arm-none-eabi-gcc -ffreestanding -c blink.c

In freestanding mode, the only available standard header files are: `<float.h>`, `<iso646.h>`, `<limits.h>`, `<stdarg.h>`, 
`<stdbool.h>`, `<stddef.h>`, and `<stdint.h>` (C99 standard 4.6).
These headers define the types appropriate for the machine being used, as well as useful constants such as the minimum and maximum values for different types. The other standard header files (`<stdio.h>`, `<string.h>` and so on) are not to be used.

In hosted mode, the `main` function must adhere to a rigid specification. Execution begins at the function named `main` and its signature must typically match:

    int main(int argv, char *argv[], char *env[])

The compiler will issue warnings if you define `main` differently for a hosted program.

Freestanding mode removes the special semantics for the `main` function. In the standalone world, `main` can have any type signature and it is configurable whether it is `main` or some other function that starts the program. A typical main signature for a freestanding program is simply:

    void main(void)

The `-ffreestanding` option also directs the compiler to not assume that standard functions have their usual definitions. This will prevent the compiler from making optimizations based on assumptions about the behaviors of the standard libraries. For example, in a hosted environment,`gcc` is assured that the available library meets the specification of the language standard. It can transform `printf("hi\n")` into `puts("hi")` because it *knows* from the definition of the standard IO library that these two functions are equivalent. In freestanding mode, you could define your own `puts` function and your version of `puts` could act completely differently than the standard `puts` function, making such a substitution invalid. Thus when `-ffreestanding` is used, `gcc` does not assume a standard library environment and will not make such optimizations. 


### Linker options for default libraries and start files
The linker option 

	-nostdlib

is used to link a program intended to run standalone. `-nostdlib` implies the individual options `-nodefaultlibs` and `-nostartfiles`. Below we discuss the two options separately, but the most typical use is just `nostdlib` for one-stop shopping.

When linking a hosted program, standard system libraries such as `libc` are linked by default, giving the program access to all standard functions (`printf`, `strlen` and friends).  The linker option

	-nodefaultlibs

prevents that automatic link, the only libraries linked are exactly those that you explicitly name to the linker using the `-l` flag.

`libgcc.a` is a standard library (linked by default, excluded by `-nodefaultlibs`) that provides internal subroutines to overcome shortcomings of particular machines.  For example, the ARM processor does not include a division instruction.  The ARM version of `libgcc.a` includes a division function and the compiler emits calls to that function where needed If you do not provide an implementation of these functions, a program with code that includes division by a variable will not link. You can explicitly link with `libgcc.a` (`-lgcc`)

A similar issue arises in certain contexts where the compiler generates calls to `memcmp`, `memset`, `memcpy` and `memmove` expecting them to be resolved by the function definitions in `libc`. These entry points should be supplied through some other mechanism when `-nodefaultlibs` is used.

Normally, when a program begins to run, the standard start function is called. This function sets up the machine to run the program.
The most common task performed by start is to initialize default values for any variables in your program and call the `main` function.

The option

    -nostartfiles

instructs the linker to not use the standard system startup functions nor link the code containing those functions.

If you don't link to a start function, program variables may not be properly initialized. You may need to provide your own start function when running in standalone mode.



