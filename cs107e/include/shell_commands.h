#ifndef COMMANDS_H
#define COMMANDS_H

typedef struct _command_struct {
    char *name;
    char *description;
    int (*fn)(int argc, const char *argv[]);
} command_t;

int cmd_echo(int argc, const char *argv[]);

/*
 * cmd_help
 * ========
 * Usage: help <[cmd]> print a list of commands or description of cmd
 *
 * When called without arguments: 
 * Prints a list of all available commands and their descriptions
 *
 * Example:
 *   Pi> help
 *   cmd1: description
 *   cmd2: description
 *
 * When called with one argument
 * Prints the description for that command, or an error message if tte
 * command does exist:
 *
 *   Pi> help reboot
 *   reboot:  reboot the Raspberry Pi back to the bootloader
 *   Pi> help please
 *   error: no such command `please`.
 *
 * Ignores any arguments after the first
 */
int cmd_help(int argc, const char *argv[]);

/*
 * cmd_help
 * ========
 *
 * reboot the Raspberry Pi back to the bootloader using `pi_reboot`
 *
 * Ignores all arguments
 */
int cmd_reboot(int argc, const char* argv[]);

/*
 * cmd_clear
 * ========
 *
 * Clears the screen.
 *
 * Ignores all arguments
 */
int cmd_clear(int argc, const char* argv[]);

/*
 * cmd_peek
 * ========
 *
 * Usage: peek [hex_addr]
 *
 * Prints the contents (4 bytes) of memory at hex_addr
 *
 * Ignores any arguments after the first
 *
 * Example:
 *
 *   Pi> peek FFFC
 *   0x0000fffc:  78 56 34 12
 *
 * If the address argument is missing or cannot be converted,
 * prints an error message:
 *
 *   Pi> peek
 *   error: peek expects 1 argument [address]
 *   Pi> peek not_hex
 *   error: peek cannot convert "not_hex"
 */
int cmd_peek(int argc, const char* argv[]);

/*
 * cmd_poke
 * ========
 *
 * Usage: poke [hex_addr] [hex_val]
 *
 * Stores `hex_val` into the memory at `hex_addr`.
 *
 * Ignores any arguments after the second
 *
 * Example:
 *
 *   Pi> peek FFFC
 *   0x0000fffc:  78 56 34 12
 *   Pi> poke FFFC 2244
 *   Pi> peek FFFC
 *   0x0000fffc:  44 22 00 00
 *   Pi> poke FFFC 0
 *   Pi> peek FFFC
 *   0x0000fffc:  00 00 00 00
 *
 * If the address argument is missing or cannot be converted,
 * prints an error message:
 *
 *   Pi> poke FFFC
 *   error: poke expects 2 arguments [hex_addr] [hex_val]
 *   Pi> poke invalid hex
 *   error: poke cannot convert "invalid"
 *   Pi> poke FFFC hex
 *   error: poke cannot convert "hex"
 */
int cmd_poke(int argc, const char* argv[]);

/*
 * cmd_poke
 * ========
 *
 * Usage: paint
 *
 * Enters mouse paint mode
 *
 * Ignores all arguments
 */
int cmd_paint(int argc, const char* argv[]);

#endif
