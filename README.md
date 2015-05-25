# C/D LCD
Fork of our previous TFTM1802 SPI Display Library for CY8CKIT-049-42xx, now ported on ESP8266 Arduino IDE.
</br>
</br>
Alpha version, never tested.
</br>
</br>
Topic on <a href="http://goo.gl/Y1xJHQ">esp8266.com</a> .
</br>
</br>

    0.0.1 (2015-04-22)
    ------------------
    New:
    -   Porting of the library from CY8CKIT-049-42xx to ESP8266
    Changes:
    -   Implemented as Class
    Fix:
    -   All problems of compilation solved as "external C"
    
    1.0.0 (2015-05-24)
    ------------------
    New:
    -   First working version of TFTM1802 SPI Display porting library to ESP8266
        (with 160Mhz overclock feature)
    -   Works pretty well at 40Mhz! (at 80Mhz or 160Mhz)
    Changes:
    -   Works with last SPI driver implemented into Arduino 1.6.4 IDE for ESP8266
    Fix:
    -   All problems solved
    -   Lots bug fix :)
    
    1.1.0 (2015-05-25)
    ------------------
    New:
    -   Added many methods to improve text writing
    -   Right now, the C_D_LCD Class is an extension of Print Class
    -   Improved the text writing
    Changes:
    -   C_D_LCD Class is an extension of Print Class, all data formats are now supported!
    Fix:
    -   Some bug fix
    

