Example showing how two programs, main and tricky, are linked.

% make clean
% make tricky.o
% arm-none-eabi-nm -S tricky.o
00000004 00000004 C i
00000000 00000004 b j
00000000 00000004 D k
00000004 00000004 d l
00000000 00000004 R m
                  U p
00000000 00000048 T tricky

# Note that the global uninitialized variable i is in common.

# Note that the static const variable n has been removed by the compiler.

% make main.o
# print size of each symbol, sort numerically
% arm-none-eabi-nm -S -n main.o
                  U i
                  U k
                  U tricky
00000000 00000044 T main
00000000 00000004 D p

% make main.exe
% arm-none-eabi-nm -S -n main.exe 
00008000          T _start
0000800c          t hang
00008010 00000038 T _cstart
00008048 00000044 T tricky
0000808c 00000044 T main
000080d0 00000004 D k
000080d4 00000004 d l
000080d8 00000004 D p
000080dc 00000004 R m
000080e0          B __bss_start__
000080e0 00000004 b j
000080e4 00000004 B i
000080e8          B __bss_end__


# the size of the executable is equal to the size of the .o's

% arm-none-eabi-size main.exe
   text    data     bss     dec     hex filename
    212      12       8     232      e8 main.exe
% arm-none-eabi-size start.o cstart.o tricky.o main.o
   text    data     bss     dec     hex filename
     12       0       0      12       c start.o
     56       0       0      56      38 cstart.o
     76       8       4      88      58 tricky.o
     68       4       0      72      48 main.o

# 212 = 12+56+76+68




