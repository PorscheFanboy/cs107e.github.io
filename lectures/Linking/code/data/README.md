Example to show how files and libraries are linked.

http://linux.die.net/man/1/ld

-M

--print-map Print a link map to the standard output. A link map
provides information about the link, including the following: •
Where object files are mapped into memory.  • How common symbols
are allocated.

• All archive members included in the link, with a mention of the
symbol which caused the archive member to be brought in.

• The values assigned to symbols.

Note - symbols whose values are computed by an expression which
involves a reference to a previous value of the same symbol may not
have correct result displayed in the link map. This is because the
linker discards intermediate results and only retains the final
value of an expression. Under such circumstances the linker will
display the final value enclosed by square brackets. Thus for example
a linker script containing: foo = 1 foo = foo * 4 foo = foo + 8
will produce the following output in the link map if the -M option
is used: 0x00000001                foo = 0x1 [0x0000000c]
foo = (foo * 0x4) [0x0000000c]                foo = (foo + 0x8) See
Expressions for more information about expressions in linker scripts.

--cref

Output a cross reference table. If a linker map file is being
generated, the cross reference table is printed to the map file.
Otherwise, it is printed on the standard output.

The format of the table is intentionally simple, so that it may be
easily processed by a script if necessary. The symbols are printed
out, sorted by name. For each symbol, a list of file names is given.
If the symbol is defined, the first file listed is the location of
the definition. The remaining files contain references to the symbol.

--gc-sections --no-gc-sections Enable garbage collection of unused
input sections. It is ignored on targets that do not support this
option. The default behaviour (of not performing this garbage
collection) can be restored by specifying --no-gc-sections on the
command line.  --gc-sections decides which input sections are used
by examining symbols and relocations. The section containing the
entry symbol and all sections containing symbols undefined on the
command-line will be kept, as will sections containing symbols
referenced by dynamic objects. Note that when building shared
libraries, the linker must assume that any visible symbol is
referenced. Once this initial set of sections has been determined,
the linker recursively marks as used any section referenced by their
relocations. See --entry and --undefined.

This option can be set when doing a partial link (enabled with
option -r). In this case the root of symbols kept must be explicitely
specified either by an --entry or --undefined option or by a "ENTRY"
command in the linker script.

--print-gc-sections --no-print-gc-sections

List all sections removed by garbage collection. The listing is
printed on stderr. This option is only effective if garbage collection
has been enabled via the --gc-sections) option. The default behaviour
(of not listing the sections that are removed) can be restored by
specifying --no-print-gc-sections on the command line.


