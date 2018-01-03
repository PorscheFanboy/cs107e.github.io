#include <stdio.h>

FILE *fp;

void sd_init() {
    fp = fopen("card.img", "r");
}

void sd_sector_read(void *buf, unsigned addr) {
    fseek(fp, 512*addr, SEEK_SET);
    fread(buf, 1, 512, fp);
}

void sd_sector_write(const void *buf, unsigned addr) {
  
}
