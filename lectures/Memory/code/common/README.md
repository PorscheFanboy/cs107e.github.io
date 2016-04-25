Example showing how two programs,
main and tricky, are linked.

% make tricky.o
% arm-none-eabi-nm tricky.o
% make main.o
% arm-none-eabi-nm main.o
% make main.exe
% arm-none-eabi-nm -S main.exe

% make sections

% make segments

