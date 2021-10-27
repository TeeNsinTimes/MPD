[strcpy_origin] - it is the original function of strcpy, DMIPS/Mhz = 0.72

[strcpy_1] - is similar to strcpy_origin, it copies 1 char in current position(address), and move tmp & src to the next position, DMIPS/Mhz = 0.71

[strcpy_2] - it uses 2 tmp addresses(tmp0 & tmp1) and 2 src addresses(src0 & src1), copies from src0 to tmp0, copies from src1 to tmp1, and add 2 to all 4 addresses, DMIPS/Mhz =  

[strcpy_3] - similar as above, but uses 3 tmps and 3 srcs, DMIPS/Mhz = 0.86

[strcpy_4] - similar as above, but uses 4 tmps and 4 srcs, DMIPS/Mhz = 

Notice:

Except for strcpy_4, all strcpys are doing the correct things; strcpy_4 failes to copy the last 2 chars, but I haven't found out the reason yet.

Each folder contains

1. string.c - the (modified) string.c file
2. *.objdump - used for tracing
3. *.ebf - the binary file send into Aquila
4. *.txt - the output of Dhrystone running on Tera Term
5. *.csv - the iladata saved after captured
6. *.png - contains iladata which I considered important
