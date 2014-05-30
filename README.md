Microprocessor-2014-Spring-Q3
=====================================
Test on TEX5288  8051 Chip

=====================================

Needed the REG320.h from here instead of teacher's example code.

It been added some NEW in it.

    EX: /*LCM*/
        sbit RS_LCM	= P3^5;
        sbit RW_LCM	= P3^6;
        sbit EN_LCM	= P3^7;

====================================

To compile successful the Q3.c in keil C,
You will need a license to upgrade from original free limited edition.

(because of code size in free edition is limited in 2K)

You can get PSN key here:
    http://pages.silabs.com/lp-keil-pk51.html

And get the license fellow the step here:
    http://top.ampbb.net/2013/08/usb-silicon-labs-c8051.html

===================================

My hardware environment settings

    P0 for LCM dateline
    P1 for 4x4 keypad
    p3 for LCM cmdline
    //LCM 16 char per row, 2
    
My software environment settings

    BL51 Local:
        Code Range : 0X0000-0X3FFF
        Xdata Range : 0XFF00-0XFFFF
        Pdata : 0XFF00
