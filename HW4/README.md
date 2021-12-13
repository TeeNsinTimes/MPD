# About HW4
**Notes:** https://hackmd.io/etVscIRjQ3aSW3JlQKYs9A?view##HW4
**github: ** 

## About read_text

**make read_text遇到的問題及解法**(已換string.c)
1. 路徑不對 -> 建資料夾、改路徑
2. code_ram不夠大，少了560 bytes(沒記錯的話) -> 把code_ram的length增加到5000

> 做完以上已經可以make成功，但是執行起來還是讀不到，會顯示"read_file: out of memory.\n"

**後來再做了一些修改**
1. 參考作業三那個pi_ddr的ld檔，改了一些東西
2. read_text.c裡uint8_t *fbuf  = (uint8_t *) 0x82000000L改成0x81000000L

> 之後就能成功讀取test.txt

以上問題，似乎只有我遇到？助教說也有可能是因為sdcard沒有先格式化，但我是用自己的sdcard，裡面還有其他資料，所以不太方便。

## About long file name
**原本的 fat32.c 對長檔名的處理方式**
1. 採用8_3格式
2. 長度超過8，一律變成[檔名前6字元][~1]
3. 如果現在有兩個前6字元相同的長檔名檔案，例如：

testlong1.txt:
```
This is for long file name testing 1.
```

testlong2.txt
```
This is for long file name testing 2.
```

  則原本的fat32.c會把這兩種長檔名的短檔名都視為TESTLO~1
  
  所以即使在read_text.c說要讀testlong2.txt，讀出來的內容仍然是"This is for long file name testing 1."

**所以首先要有方法取得正確的短檔名(on PC)**
1. python版本的很簡單，網路上很容易就找到可用的
2. c版本的就很難找，找到的大都不能用，get_8_3.c是我好不容易找到可用的，但也不是直接能用，還是有做一些修改
3. get_8_3.c可以取得正確的短檔(路徑)名，testlong1.txt 和 testlong2.txt 分別為 TESTLO~1.TXT 及 TESTLO~2.TXT
4. 根據短檔名，手動修改fat32.c裡的long2short()，之後生成的ebf file就可以在板子上讀出正確的內容

**然後我試圖把兩件事情合併**
```
//fat32.c - long2short()
    if (len > 8)
    {
        fname83[6] = '~';
        fname83[7] = '1';
        DWORD retval = 0;

        // the path and the file are valid...
        LPCWSTR szlongpath = L"E:\\testlong2.txt";
        LPWSTR szshortpath = (LPWSTR) malloc(sizeof(MAX_PATH));
        TCHAR* buffer = MAX_PATH;
        retval = GetShortPathNameW(szlongpath, szshortpath, buffer);
        if (retval == 0) {
            printf("GetshortPathName() failed! Error : %d\n", retval);
        }
        else {
            // displaying short and long path
            printf("The long path name = %S\n", szlongpath);
            printf("The short path name = %S\n", szshortpath);
            printf("The buffer length in TCHARs = %d\n", buffer);

            for (idx = 0; idx < sizeof(szshortpath)/sizeof(LPWSTR); ++idx) {
                if (szshortpath[idx] == '~') {
                    fname83[7] = szshortpath[idx + 1];
                    break;
                }
            }
        }
        
        if (szshortpath = NULL) printf("memory freed!\n");
        else free(szshortpath);
    }
```

但因為要多 include 一些 library，所以就變得很複雜

**以下是我嘗試過的方法，以及失敗的原因**
1. 像elibc裡的library一樣，把用到的檔案一個個複製進去 -> 檔案太多 include 不完
2. 修改 makefile 讓它可以像我在電腦上編譯 c file 一樣，去找到那些 library -> 好像不可行，不然就是我不會做
3. 先用 gcc 產生 .bin(參考https://stackoverflow.com/questions/1647359/is-there-a-way-to-get-gcc-to-output-raw-binary)，然後用 create_ebf.sh 把 .bin 變成 .ebf -> 出來的ebf很奇怪(比正常的短很多)

後來我問了助教，他說 include 外部的 library 就是會有這些問題，建議要自己寫，所以我決定放棄了：(

而且助教說有些外部的 library 會依賴作業系統，我這個方法好像確實只能在 Windows 上運行
