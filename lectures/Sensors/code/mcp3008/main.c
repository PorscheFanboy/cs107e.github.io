/* Simple SPI + MCP3008 ADC test. */

#include "printf.h"
#include "mcp3008.h"

void main() {
    mcp3008_init();
    while (1) {
        int result = mcp3008_read(0);
        printf("%d\n", result);
    }
}
