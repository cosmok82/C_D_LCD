#include <SPI.h>
#include <C_D_LCD.h>

C_D_LCD spilcd;

String text = "Ahi quanto a dir\nqual era e' cosa dura, esta selva selvaggia e aspra e forte, che nel pensier rinova la paura!";

void setup() {
  spilcd.begin();
  spilcd.setTextColor(WHITE, BLACK);
}

void loop() {
    int i;
    
    spilcd.fillScreen(BLACK);
    delay(2000);
    // circles demo
    for(i = 0; i < spilcd.getHeight(); i += 2)
    {
        spilcd.drawCircle(spilcd.getWidth()/2, spilcd.getHeight()/2, i, RED);
        delay(10);
    }
    delay(2000);
    spilcd.fillScreen(RED);
    delay(2000);
    spilcd.fillScreen(BLACK);
    delay(2000);
    
    // lines demo
    for(i = 0; i < spilcd.getHeight(); i += 2)
    {   spilcd.drawFastHLine(0, i, spilcd.getWidth(), WHITE);
        delay(10);
    }
    delay(250);
    for(i = 0; i < spilcd.getWidth(); i += 2)
    {
        spilcd.drawFastVLine(i, 0, spilcd.getHeight(), WHITE);
        delay(10);
    }
    delay(250);
    spilcd.fillScreen(WHITE);
    delay(1000);
    spilcd.fillScreen(BLACK);
    
    // rectangles demo
    for(i = 0; i < spilcd.getWidth()/2; i += 2)
    {
        spilcd.drawRect(i, i+(HEIGHT-WIDTH)/2, spilcd.getWidth()-i*2, spilcd.getWidth()-i*2, BLUE);
        delay(10);
    }
    delay(250);
    spilcd.fillScreen(BLUE);
    delay(1000);
    spilcd.fillScreen(BLACK);
    
    // round corners rectangles demo
    for(i = (spilcd.getWidth()/2)-20; i > 0; i -= 2)
    {
        spilcd.fillRoundRect(i, i+(HEIGHT-WIDTH)/2, spilcd.getWidth()-i*2, spilcd.getWidth()-i*2, 20, GREEN);
        delay(10);
    }
    delay(1000);
    spilcd.fillScreen(BLACK);
    
    // RGB colors demos
    for(i = 42; i > 0; i--)
    {
        spilcd.drawFastVLine(i+84, 0, spilcd.getHeight(), ((i*0x3F) << (16+2)) );
        spilcd.drawFastVLine(i+42, 0, spilcd.getHeight(), ((i*0x3F) << (8+2))  );
        spilcd.drawFastVLine(i,    0, spilcd.getHeight(), ((i*0x3F) << 2)      );
    }
    delay(5000);
    
    for(i = 42; i > 0; i--)
    {            
        spilcd.drawFastVLine(i+84, 0, spilcd.getHeight(), ((i*0x3F) << (16+2)) | 0x00FCFC);
        spilcd.drawFastVLine(i+42, 0, spilcd.getHeight(), ((i*0x3F) << (8+2))  | 0xFC00FC);
        spilcd.drawFastVLine(i,    0, spilcd.getHeight(), ((i*0x3F) << 2)      | 0xFCFC00);
    }
    delay(5000);
    
    String textB = "www.creativityslashdesign.tk ";
    
    spilcd.fillScreen(BLACK);
    spilcd.setCursor(0, 0);
    spilcd.print("First words.\nSecond words.");
    delay(5000);
    
    spilcd.fillScreen(RED);
    spilcd.setCursor(0, 0);
    spilcd.print(text);
    spilcd.setCursor(0, spilcd.getHeight()/2);
    spilcd.print(textB+" 0");
    delay(5000);
    
    spilcd.setRotation(1);
    spilcd.fillScreen(RED);
    spilcd.setCursor(0, 0);
    spilcd.print(text);
    spilcd.setCursor(0, spilcd.getHeight()/2);
    spilcd.print(textB+" 1");
    delay(5000);
    
    spilcd.setRotation(2);
    spilcd.fillScreen(RED);
    spilcd.setCursor(0, 0);
    spilcd.print(text);
    spilcd.setCursor(0, spilcd.getHeight()/2);
    spilcd.print(textB+" 2");
    delay(5000);
    
    spilcd.setRotation(3);
    spilcd.fillScreen(RED);
    spilcd.setCursor(0, 0);
    spilcd.print(text);
    spilcd.setCursor(0, spilcd.getHeight()/2);
    spilcd.print(textB+" 3");
    delay(5000);
		
    spilcd.setRotation(0);
}

