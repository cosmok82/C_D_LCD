#include <SPI.h>
#include <C_D_LCD.h>

uint8 font_dim;
char text[] = "Ahi quanto a dir\nqual era e' cosa dura, esta selva selvaggia e aspra e forte, che nel pensier rinova la paura!";

void setup() {
  SPILCD.begin();
  font_dim = 1;
  SPILCD.x_start = SPILCD.y_start = 0;
}

void loop() {
    int i;
    
    SPILCD.fillScreen(BLACK);
    delay(2000);
    // circles demo
    for(i = 0; i < SPILCD.getHeight(); i += 2)
    {
        SPILCD.drawCircle(SPILCD.getWidth()/2, SPILCD.getHeight()/2, i, RED);
        delay(10);
    }
    delay(2000);
    SPILCD.fillScreen(RED);
    delay(2000);
    SPILCD.fillScreen(BLACK);
    delay(2000);
    
    // lines demo
    for(i = 0; i < SPILCD.getHeight(); i += 2)
    {   SPILCD.drawFastHLine(0, i, SPILCD.getWidth(), WHITE);
        delay(10);
    }
    delay(250);
    for(i = 0; i < SPILCD.getWidth(); i += 2)
    {
        SPILCD.drawFastVLine(i, 0, SPILCD.getHeight(), WHITE);
        delay(10);
    }
    delay(250);
    SPILCD.fillScreen(WHITE);
    delay(1000);
    SPILCD.fillScreen(BLACK);
    
    // rectangles demo
    for(i = 0; i < SPILCD.getWidth()/2; i += 2)
    {
        SPILCD.drawRect(i, i+(HEIGHT-WIDTH)/2, SPILCD.getWidth()-i*2, SPILCD.getWidth()-i*2, BLUE);
        delay(10);
    }
    delay(250);
    SPILCD.fillScreen(BLUE);
    delay(1000);
    SPILCD.fillScreen(BLACK);
    
    // round corners rectangles demo
    for(i = (SPILCD.getWidth()/2)-20; i > 0; i -= 2)
    {
        SPILCD.fillRoundRect(i, i+(HEIGHT-WIDTH)/2, SPILCD.getWidth()-i*2, SPILCD.getWidth()-i*2, 20, GREEN);
        delay(10);
    }
    delay(1000);
    SPILCD.fillScreen(BLACK);
    
    // RGB colors demos
    for(i = 42; i > 0; i--)
    {
        SPILCD.drawFastVLine(i+84, 0, SPILCD.getHeight(), ((i*0x3F) << (16+2)) );
        SPILCD.drawFastVLine(i+42, 0, SPILCD.getHeight(), ((i*0x3F) << (8+2))  );
        SPILCD.drawFastVLine(i,    0, SPILCD.getHeight(), ((i*0x3F) << 2)      );
    }
    delay(5000);
    
    for(i = 42; i > 0; i--)
    {            
        SPILCD.drawFastVLine(i+84, 0, SPILCD.getHeight(), ((i*0x3F) << (16+2)) | 0x00FCFC);
        SPILCD.drawFastVLine(i+42, 0, SPILCD.getHeight(), ((i*0x3F) << (8+2))  | 0xFC00FC);
        SPILCD.drawFastVLine(i,    0, SPILCD.getHeight(), ((i*0x3F) << 2)      | 0xFCFC00);
    }
    delay(5000);
    
    char textB[] = "www.creativityslashdesign.tk ";
    
    SPILCD.fillScreen(BLACK);
    SPILCD.print("First words.", WHITE, BLACK, font_dim);
    SPILCD.y_start += 8;
    SPILCD.print("Second words.", WHITE, BLACK, font_dim);
    delay(5000);
    
    SPILCD.fillScreen(RED);
    SPILCD.print(text, WHITE, BLACK, font_dim);
    SPILCD.x_start = 0;
    SPILCD.y_start = SPILCD.getHeight()/2;
    SPILCD.printN(textB, WHITE, BLACK, font_dim, 0);
    delay(5000);
    
    SPILCD.RotSetting(1);
    SPILCD.fillScreen(RED);
    SPILCD.print(text, WHITE, BLACK, font_dim);
    SPILCD.x_start = 0;
    SPILCD.y_start = SPILCD.getHeight()/2;
    SPILCD.printN(textB, WHITE, BLACK, font_dim, 1);
    delay(5000);
    
    SPILCD.RotSetting(2);
    SPILCD.fillScreen(RED);
    SPILCD.print(text, WHITE, BLACK, font_dim);
    SPILCD.x_start = 0;
    SPILCD.y_start = SPILCD.getHeight()/2;
    SPILCD.printN(textB, WHITE, BLACK, font_dim, 2);
    delay(5000);
    
    SPILCD.RotSetting(3);
    SPILCD.fillScreen(RED);
    SPILCD.print(text, WHITE, BLACK, font_dim);
    SPILCD.x_start = 0;
    SPILCD.y_start = SPILCD.getHeight()/2;
    SPILCD.printN(textB, WHITE, BLACK, font_dim, 3);
    delay(5000);
		
    SPILCD.RotSetting(0);     
}

