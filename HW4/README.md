Notes: https://hackmd.io/etVscIRjQ3aSW3JlQKYs9A?view##HW4

make read_text遇到的問題及解法(已換string.c)：
1. 路徑不對 -> 建資料夾、改路徑
2. code_ram不夠大，少了560 bytes(沒記錯的話) -> 把code_ram的length增加到5000

做完以上已經可以make成功，但是執行起來還是讀不到，會顯示"read_file: out of memory.\n"

後來再做了一些修改：
1. 參考作業三那個pi_ddr的ld檔，改了一些東西
2. read_text.c裡uint8_t *fbuf  = (uint8_t *) 0x82000000L改成0x81000000L

之後就能成功讀取test.txt

以上的問題，似乎只有我遇到？助教說也有可能是因為sdcard沒有先格式化，但我用的是自己的sdcard，裡面還有其他資料，所以不太方便。
