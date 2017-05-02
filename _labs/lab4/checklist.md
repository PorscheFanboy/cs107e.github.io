---
layout: page
title: 'Lab 4: Linking and Loading Checklist'
permalink: /labs/lab4/checklist/
---

Before leaving the lab, check in with a TA and tell them you and your
partner's answers to these questions.

1. What does the `nm` tool print out, and what do the symbols `T`, `U`, etc. mean?

2. How is the instruction `bl _cstart` modified during the linking process?

3. As a group, write a description of how the bootloader works.

4. On a sheet of paper, with address 0x0 at the bottom of the page and 0x8000000 at the top,
   sketch a diagram of the memory layout created in `code/linking`. Add to your diagram
   the contents of the stack at the point where execution has just entered the 
   `main` function. (Use the `winky` diagram from [lab3](https://cs107e.github.io/labs/lab3)
   as a guide.)