#ifndef MMU_H
#define MMU_H

#define MMU_PAGE_SECTION     0x00002 // 1MB sections
#define MMU_PAGE_CACHEABLE   0x00008 // cache enabled
#define MMU_PAGE_BUFFERABLE  0x00004 // write-buffer enabled

// 0 is also no access
#define MMU_PAGE_ACCESS_NONE 0x00400
#define MMU_PAGE_ACCESS_R    0x00800
#define MMU_PAGE_ACCESS_RW   0x00C00

extern void mmu_section ( unsigned base, unsigned vadd, unsigned padd, unsigned flags );
extern void mmu_init( unsigned base );

#endif
