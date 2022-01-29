/*
 * tftlcd.c
 *
 *  Created on: 2020. 3. 19.
 *      Author: isjeon
 */

#include "tftlcd.h"
#include "main.h"

#define RST_GPIO_Port LED6_GPIO_Port
#define RST_Pin LED6_Pin
#define TFTLCD_NSS_GPIO_Port SPI2_NSS_GPIO_Port
#define TFTLCD_NSS_Pin SPI2_NSS_Pin

#define DC_GPIO_Port LED5_GPIO_Port
#define DC_Pin  LED5_Pin

#define LED_GPIO_Port LED4_GPIO_Port
#define LED_Pin  LED4_Pin
#define SPI_DC_LOW()  DC_GPIO_Port-> BSRR = DC_Pin << 16
#define SPI_DC_HIGH() DC_GPIO_Port-> BSRR = DC_Pin << 0

#define SPI_CS_LOW()  TFTLCD_NSS_GPIO_Port->BSRR = TFTLCD_NSS_Pin << 16
#define SPI_CS_HIGH() TFTLCD_NSS_GPIO_Port->BSRR = TFTLCD_NSS_Pin << 0
extern SPI_HandleTypeDef hspi2;

#define HSPI_TFTLCD &hspi2
#define TFT_SPI_TIMEOUT 100
void HSPI_WRITE(uint8_t data)
{
	while(!__HAL_SPI_GET_FLAG(HSPI_TFTLCD, SPI_FLAG_TXE));
	HAL_SPI_Transmit(HSPI_TFTLCD, &data, 1, TFT_SPI_TIMEOUT);
	while(!__HAL_SPI_GET_FLAG(HSPI_TFTLCD, SPI_FLAG_TXE));
//	printf("SPI2=%02x\n",data&0xff);
}
void _writeCommand16(uint16_t command) {
    SPI_DC_LOW();
    SPI_CS_LOW();

# ifdef HSPI_WRITE16
        HSPI_WRITE16(command);
#else
        HSPI_WRITE(command >> 8);
        HSPI_WRITE(0x00ff & command);
#endif

    SPI_CS_HIGH();
}

void _writeData16(uint16_t data) {
    SPI_DC_HIGH();
    SPI_CS_LOW();

# ifdef HSPI_WRITE16
        HSPI_WRITE16(data);
#else
        HSPI_WRITE(data >> 8);
        HSPI_WRITE(0x00ff & data);
#endif
    SPI_CS_HIGH();
}

static void _writeRegister(uint16_t reg, uint16_t data) {
    _writeCommand16(reg);
    _writeData16(data);
}

static void tft_init();

tft_fn(int ac, char *av[])
{
    printf("TFT LCD...\n");
	LED_GPIO_Port->BSRR = LED_Pin;
	tft_init();
}

void startWrite() {}
void endWrite() {}
#define delay  HAL_Delay

static int _blState, _orientation, _maxX, _maxY, _bgColor;

void setBacklight(int flag)
{
	_blState = flag;
}
void setOrientation(uint8_t orientation) {

    _orientation = orientation % 4;

    switch (_orientation) {
    case 0:
        _maxX = ILI9225_LCD_WIDTH;
        _maxY = ILI9225_LCD_HEIGHT;
        break;
    case 1:
        _maxX = ILI9225_LCD_HEIGHT;
        _maxY = ILI9225_LCD_WIDTH;
        break;
    case 2:
        _maxX = ILI9225_LCD_WIDTH;
        _maxY = ILI9225_LCD_HEIGHT;
        break;
    case 3:
        _maxX = ILI9225_LCD_HEIGHT;
        _maxY = ILI9225_LCD_WIDTH;
        break;
    }
}

void setBackgroundColor(uint16_t color) {
    _bgColor = color;
}

uint8_t getOrientation() {
    return _orientation;
}

#define min(a,b) a>b?b:a

void _setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    __setWindow( x0, y0, x1, y1, TopDown_L2R ); // default for drawing characters
}
// Corresponding modes if orientation changed:
const int modeTab [3][8] = {
//          { R2L_BottomUp, BottomUp_R2L, L2R_BottomUp, BottomUp_L2R, R2L_TopDown,  TopDown_R2L,  L2R_TopDown,  TopDown_L2R }//
/* 90�� */   { BottomUp_L2R, L2R_BottomUp, TopDown_L2R,  L2R_TopDown,  BottomUp_R2L, R2L_BottomUp, TopDown_R2L,  R2L_TopDown },
/*180�� */   { L2R_TopDown , TopDown_L2R,  R2L_TopDown,  TopDown_R2L,  L2R_BottomUp, BottomUp_L2R, R2L_BottomUp, BottomUp_R2L},
/*270�� */   { TopDown_R2L , R2L_TopDown,  BottomUp_R2L, R2L_BottomUp, TopDown_L2R,  L2R_TopDown,  BottomUp_L2R, L2R_BottomUp}
};

void _swap(uint16_t *a, uint16_t *b) {
    uint16_t w = *a;
    *a = *b;
    *b = w;
}

void _orientCoordinates(uint16_t x1, uint16_t y1) {

    switch (_orientation) {
        case 0:  // ok
            break;
        case 1: // ok
            y1 = _maxY - y1 - 1;
            _swap(&x1, &y1);
            break;
        case 2: // ok
            x1 = _maxX - x1 - 1;
            y1 = _maxY - y1 - 1;
            break;
        case 3: // ok
            x1 = _maxX - x1 - 1;
            _swap(&x1, &y1);
            break;
    }
}
#define DB_PRINT printf
void __setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,int  mode) {

//    DB_PRINT( "setWindows( x0=%d, y0=%d, x1=%d, y1=%d, mode=%d", x0,y0,x1,y1,mode );

    // clip to TFT-Dimensions
    x0 = min( x0, (uint16_t) (_maxX-1) );
    x1 = min( x1, (uint16_t) (_maxX-1) );
    y0 = min( y0, (uint16_t) (_maxY-1) );
    y1 = min( y1, (uint16_t) (_maxY-1) );
    _orientCoordinates(x0, y0);
    _orientCoordinates(x1, y1);

    if (x1<x0) _swap(&x0, &x1);
    if (y1<y0) _swap(&y0, &y1);

    startWrite();
    // autoincrement mode
    if ( _orientation > 0 ) mode = modeTab[_orientation-1][mode];
    _writeRegister(ILI9225_ENTRY_MODE, 0x1000 | ( mode<<3) );
    _writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR1,x1);
    _writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR2,x0);

    _writeRegister(ILI9225_VERTICAL_WINDOW_ADDR1,y1);
    _writeRegister(ILI9225_VERTICAL_WINDOW_ADDR2,y0);
//    DB_PRINT( "gedreht: x0=%d, y0=%d, x1=%d, y1=%d, mode=%d", x0,y0,x1,y1,mode );
    // starting position within window and increment/decrement direction
    switch ( mode>>1 ) {
        case 0:
            _writeRegister(ILI9225_RAM_ADDR_SET1,x1);
            _writeRegister(ILI9225_RAM_ADDR_SET2,y1);
            break;
        case 1:
            _writeRegister(ILI9225_RAM_ADDR_SET1,x0);
            _writeRegister(ILI9225_RAM_ADDR_SET2,y1);
            break;
        case 2:
            _writeRegister(ILI9225_RAM_ADDR_SET1,x1);
            _writeRegister(ILI9225_RAM_ADDR_SET2,y0);
            break;
        case 3:
            _writeRegister(ILI9225_RAM_ADDR_SET1,x0);
            _writeRegister(ILI9225_RAM_ADDR_SET2,y0);
            break;
    }
    _writeCommand16( ILI9225_GRAM_DATA_REG );

    //_writeRegister(ILI9225_RAM_ADDR_SET1,x0);
    //_writeRegister(ILI9225_RAM_ADDR_SET2,y0);

    //_writeCommand(0x00, 0x22);

    endWrite();
}


void _resetWindow() {
    _writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR1, 0x00AF);
    _writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR2, 0x0000);
    _writeRegister(ILI9225_VERTICAL_WINDOW_ADDR1, 0x00DB);
    _writeRegister(ILI9225_VERTICAL_WINDOW_ADDR2, 0x0000);

}
void fillRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {

    _setWindow(x1, y1, x2, y2);

    startWrite();
    for (uint16_t t=(y2 - y1 + 1) * (x2 - x1 + 1); t > 0; t--)
        _writeData16(color);
    endWrite();
    _resetWindow();
}

void clear() {
    uint8_t old = _orientation;
    setOrientation(0);
    fillRectangle(0, 0, _maxX - 1, _maxY - 1, COLOR_BLACK);
    setOrientation(old);
    delay(10);
}

void fill(uint16_t color)
{
    uint8_t old = _orientation;
    setOrientation(0);
    fillRectangle(0, 0, _maxX - 1, _maxY - 1, color);
    setOrientation(old);
    delay(10);
}
static void tft_init()
{
	static int init_flag = 0;
//	if(init_flag == 0)
	{
		init_flag = 1;
		RST_GPIO_Port->BSRR = RST_Pin; // HIGH
		HAL_Delay(1);
		RST_GPIO_Port->BSRR = RST_Pin << 16; // LOW
		HAL_Delay(10);
		RST_GPIO_Port->BSRR = RST_Pin; // HIGH
		HAL_Delay(50);
	}

/* Set SS bit and direction output from S528 to S1 */
    startWrite();
    _writeRegister(ILI9225_POWER_CTRL1, 0x0000); // Set SAP,DSTB,STB
    _writeRegister(ILI9225_POWER_CTRL2, 0x0000); // Set APON,PON,AON,VCI1EN,VC
    _writeRegister(ILI9225_POWER_CTRL3, 0x0000); // Set BT,DC1,DC2,DC3
    _writeRegister(ILI9225_POWER_CTRL4, 0x0000); // Set GVDD
    _writeRegister(ILI9225_POWER_CTRL5, 0x0000); // Set VCOMH/VCOML voltage
    endWrite();
    delay(40);

    // Power-on sequence
    startWrite();
    _writeRegister(ILI9225_POWER_CTRL2, 0x0018); // Set APON,PON,AON,VCI1EN,VC
    _writeRegister(ILI9225_POWER_CTRL3, 0x6121); // Set BT,DC1,DC2,DC3
    _writeRegister(ILI9225_POWER_CTRL4, 0x006F); // Set GVDD   /*007F 0088 */
    _writeRegister(ILI9225_POWER_CTRL5, 0x495F); // Set VCOMH/VCOML voltage
    _writeRegister(ILI9225_POWER_CTRL1, 0x0800); // Set SAP,DSTB,STB
    endWrite();
    delay(10);
    startWrite();
    _writeRegister(ILI9225_POWER_CTRL2, 0x103B); // Set APON,PON,AON,VCI1EN,VC
    endWrite();
    delay(50);

    startWrite();
    _writeRegister(ILI9225_DRIVER_OUTPUT_CTRL, 0x011C); // set the display line number and display direction
    _writeRegister(ILI9225_LCD_AC_DRIVING_CTRL, 0x0100); // set 1 line inversion
    _writeRegister(ILI9225_ENTRY_MODE, 0x1038); // set GRAM write direction and BGR=1.
    _writeRegister(ILI9225_DISP_CTRL1, 0x0000); // Display off
    _writeRegister(ILI9225_BLANK_PERIOD_CTRL1, 0x0808); // set the back porch and front porch
    _writeRegister(ILI9225_FRAME_CYCLE_CTRL, 0x1100); // set the clocks number per line
    _writeRegister(ILI9225_INTERFACE_CTRL, 0x0000); // CPU interface
    _writeRegister(ILI9225_OSC_CTRL, 0x0D01); // Set Osc  /*0e01*/
    _writeRegister(ILI9225_VCI_RECYCLING, 0x0020); // Set VCI recycling
    _writeRegister(ILI9225_RAM_ADDR_SET1, 0x0000); // RAM Address
    _writeRegister(ILI9225_RAM_ADDR_SET2, 0x0000); // RAM Address

    /* Set GRAM area */
     _writeRegister(ILI9225_GATE_SCAN_CTRL, 0x0000);
     _writeRegister(ILI9225_VERTICAL_SCROLL_CTRL1, 0x00DB);
     _writeRegister(ILI9225_VERTICAL_SCROLL_CTRL2, 0x0000);
     _writeRegister(ILI9225_VERTICAL_SCROLL_CTRL3, 0x0000);
     _writeRegister(ILI9225_PARTIAL_DRIVING_POS1, 0x00DB);
     _writeRegister(ILI9225_PARTIAL_DRIVING_POS2, 0x0000);
     _writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR1, 0x00AF);
     _writeRegister(ILI9225_HORIZONTAL_WINDOW_ADDR2, 0x0000);
     _writeRegister(ILI9225_VERTICAL_WINDOW_ADDR1, 0x00DB);
     _writeRegister(ILI9225_VERTICAL_WINDOW_ADDR2, 0x0000);

     /* Set GAMMA curve */
     _writeRegister(ILI9225_GAMMA_CTRL1, 0x0000);
     _writeRegister(ILI9225_GAMMA_CTRL2, 0x0808);
     _writeRegister(ILI9225_GAMMA_CTRL3, 0x080A);
     _writeRegister(ILI9225_GAMMA_CTRL4, 0x000A);
     _writeRegister(ILI9225_GAMMA_CTRL5, 0x0A08);
     _writeRegister(ILI9225_GAMMA_CTRL6, 0x0808);
     _writeRegister(ILI9225_GAMMA_CTRL7, 0x0000);
     _writeRegister(ILI9225_GAMMA_CTRL8, 0x0A00);
     _writeRegister(ILI9225_GAMMA_CTRL9, 0x0710);
     _writeRegister(ILI9225_GAMMA_CTRL10, 0x0710);

     _writeRegister(ILI9225_DISP_CTRL1, 0x0012);
     endWrite();
     delay(50);
     startWrite();
     _writeRegister(ILI9225_DISP_CTRL1, 0x1017);
     endWrite();

#define true 1 // by isjeon
     // Turn on backlight
      setBacklight(true);
      setOrientation(0);

      // Initialize variables
#define COLOR_BLUE           0x001F      /*   0,   0, 255 */
#define COLOR_GREEN          0x07E0      /*   0, 255,   0 */
#define COLOR_RED            0xF800      /* 255,   0,   0 */

      setBackgroundColor( COLOR_BLACK  );

      clear();


      fill(COLOR_RED);
      fill(COLOR_GREEN);
      fill(COLOR_BLUE);
}
