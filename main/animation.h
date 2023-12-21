#include <U8g2lib.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C auxScreen(U8G2_R0);

const int sizeBytes = 376;
const int frames = 4;

static unsigned char icon_animation [frames][sizeBytes] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0,
   0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0x03, 0xe4, 0x03, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00,
   0xe2, 0x03, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0xd9, 0x07, 0x00, 0x00,
   0x00, 0x00, 0x0c, 0x80, 0xf9, 0x0e, 0x00, 0x00, 0x00, 0x60, 0x06, 0x80,
   0x78, 0x18, 0x00, 0x00, 0x00, 0x60, 0x03, 0x40, 0x3a, 0x18, 0x00, 0x00,
   0x00, 0xa0, 0x03, 0x40, 0x3c, 0x20, 0x00, 0x00, 0x00, 0x20, 0x01, 0x40,
   0x1a, 0x60, 0x00, 0x00, 0x00, 0x60, 0x02, 0x60, 0x1e, 0xc0, 0x00, 0x00,
   0x00, 0x60, 0x08, 0x60, 0x0f, 0xc0, 0x00, 0x00, 0x18, 0xd0, 0x12, 0xf0,
   0x1f, 0x80, 0x01, 0x00, 0x78, 0xa0, 0x01, 0x10, 0x20, 0x80, 0x01, 0x00,
   0xf8, 0x20, 0x26, 0x08, 0x20, 0x00, 0x01, 0x00, 0xf8, 0xf3, 0x00, 0x48,
   0x31, 0x00, 0x03, 0x00, 0x70, 0x7e, 0x57, 0xf8, 0x37, 0x62, 0x03, 0x00,
   0xb0, 0x7c, 0x00, 0xe9, 0x75, 0x66, 0x03, 0x00, 0xc0, 0x9b, 0x4a, 0xd8,
   0x2b, 0x04, 0x02, 0x00, 0x00, 0x1e, 0x0a, 0xf8, 0x35, 0xc0, 0xff, 0x0f,
   0x80, 0x1b, 0x00, 0xd8, 0x7b, 0x78, 0x00, 0x3d, 0xf0, 0x3c, 0x00, 0xf8,
   0x37, 0x06, 0x00, 0x18, 0x78, 0x16, 0x00, 0xf8, 0x3f, 0x04, 0x00, 0x08,
   0xf8, 0x33, 0x00, 0xe0, 0x1f, 0x0c, 0x00, 0x0c, 0xe0, 0x20, 0x00, 0x00,
   0x04, 0x08, 0x07, 0x06, 0x00, 0x60, 0x00, 0x00, 0x00, 0x90, 0x3f, 0x03,
   0x00, 0xc0, 0x00, 0x00, 0x00, 0xf0, 0xe0, 0x01, 0x00, 0xc0, 0x01, 0x00,
   0x00, 0xe0, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0x78, 0x00, 0x00,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x01,
   0x40, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x55, 0xd5, 0x03, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe,
   0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0e, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x0c, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
   0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xce, 0x0f, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xfe, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0xfb, 0x01, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x80, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0xff, 0x03, 0x00, 0x00,
   
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x80, 0x07, 0xee, 0x01, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00,
   0xe2, 0x03, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0xf3, 0x03, 0x00, 0x00,
   0x00, 0x00, 0x18, 0x00, 0xe9, 0x07, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x80,
   0x78, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x02, 0xc0, 0x3a, 0x18, 0x00, 0x00,
   0x00, 0x00, 0x03, 0x40, 0x3c, 0x30, 0x00, 0x00, 0x00, 0x80, 0x01, 0x40,
   0x1c, 0x60, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x60, 0x1e, 0x40, 0x00, 0x00,
   0x00, 0x40, 0x00, 0x60, 0x0f, 0xc0, 0x00, 0x00, 0x18, 0x60, 0x00, 0xe0,
   0x1f, 0x80, 0x00, 0x00, 0x38, 0x38, 0x00, 0x18, 0x30, 0x80, 0x01, 0x00,
   0xf8, 0xf8, 0x00, 0x08, 0x20, 0x00, 0x01, 0x00, 0xf8, 0x3b, 0x0d, 0x88,
   0x20, 0x00, 0x03, 0x00, 0x78, 0xbf, 0x50, 0xf8, 0x7f, 0x62, 0x03, 0x00,
   0x70, 0xfc, 0x05, 0xf8, 0x33, 0x66, 0x03, 0x00, 0xe0, 0x3b, 0x55, 0xd9,
   0x6b, 0x06, 0x02, 0x00, 0x00, 0x5f, 0x05, 0xf8, 0x35, 0x80, 0xff, 0x03,
   0x00, 0x1f, 0x00, 0xd8, 0x3b, 0xf8, 0xd5, 0x3f, 0xe0, 0x19, 0x00, 0xf8,
   0x3b, 0x0e, 0x00, 0x18, 0x78, 0x36, 0x00, 0xf8, 0x3f, 0x04, 0x00, 0x18,
   0xf8, 0x33, 0x00, 0xf0, 0x3f, 0x0c, 0x00, 0x0c, 0xe0, 0x30, 0x00, 0x40,
   0x05, 0x08, 0x03, 0x06, 0x00, 0x60, 0x00, 0x00, 0x00, 0x90, 0x1f, 0x02,
   0x00, 0xe0, 0x00, 0x00, 0x00, 0xb0, 0xf1, 0x03, 0x00, 0xc0, 0x02, 0x00,
   0x00, 0xe0, 0x00, 0x01, 0x00, 0x80, 0x13, 0x00, 0x00, 0x74, 0x00, 0x00,
   0x00, 0x00, 0x07, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x44,
   0xa4, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x78, 0x89, 0xc0, 0x07, 0x00, 0x00,
   0x00, 0x00, 0xe0, 0xbf, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
   0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xee, 0x31, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xfe, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c,
   0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x3e, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9f,
   0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30,
   0x00, 0x00, 0x00, 0x00,
   
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x7f, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x80, 0x0f, 0xee, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x01,
   0xe6, 0x03, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0xd2, 0x03, 0x00, 0x00,
   0x00, 0x00, 0x18, 0x80, 0xf1, 0x07, 0x00, 0x00, 0x00, 0x20, 0x0c, 0x80,
   0x78, 0x0c, 0x00, 0x00, 0x00, 0x60, 0x06, 0x80, 0x38, 0x18, 0x00, 0x00,
   0x00, 0xe0, 0x03, 0x40, 0x3e, 0x30, 0x00, 0x00, 0x00, 0xa0, 0x01, 0x40,
   0x1a, 0x60, 0x00, 0x00, 0x00, 0x20, 0x01, 0x40, 0x1e, 0x40, 0x00, 0x00,
   0x00, 0x60, 0x04, 0x20, 0x1d, 0xc0, 0x00, 0x00, 0x08, 0xf0, 0x08, 0xe0,
   0x1f, 0x80, 0x00, 0x00, 0x38, 0x90, 0x01, 0x38, 0x11, 0x80, 0x01, 0x00,
   0x78, 0x20, 0x2b, 0x08, 0x20, 0x00, 0x01, 0x00, 0xf8, 0x71, 0x00, 0x08,
   0x20, 0x00, 0x01, 0x00, 0x78, 0xf7, 0x4b, 0xf8, 0x3f, 0x20, 0x03, 0x00,
   0x30, 0x7c, 0x14, 0xe8, 0x31, 0x66, 0x03, 0x00, 0xe0, 0x59, 0x41, 0xf9,
   0x77, 0x46, 0x02, 0x00, 0x80, 0x9f, 0x09, 0xe8, 0x35, 0x00, 0xff, 0x00,
   0x00, 0x1e, 0x04, 0xf8, 0x6b, 0xf0, 0xff, 0x3f, 0xc0, 0x19, 0x00, 0xf8,
   0x3b, 0x1e, 0x00, 0x38, 0x78, 0x3e, 0x00, 0xf8, 0x3e, 0x04, 0x00, 0x18,
   0xf8, 0x12, 0x00, 0xf0, 0x3f, 0x04, 0x00, 0x0c, 0xf0, 0x31, 0x00, 0xa0,
   0x0d, 0x08, 0x01, 0x04, 0x00, 0x20, 0x00, 0x00, 0x00, 0x10, 0x0f, 0x06,
   0x00, 0x60, 0x00, 0x00, 0x00, 0xb0, 0xf9, 0x03, 0x00, 0xc0, 0x00, 0x00,
   0x00, 0xe0, 0x80, 0x01, 0x00, 0x80, 0x03, 0x00, 0x00, 0x68, 0x00, 0x00,
   0x00, 0x00, 0x07, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00,
   0x80, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x49, 0x92, 0x07, 0x00, 0x00,
   0x00, 0x00, 0xe0, 0x97, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff,
   0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x01, 0xf8, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xe0, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00,
   0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0xe0, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x70, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00,
   0xf0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xb8, 0x0f, 0xf8, 0x1f, 0x00, 0x00,
   0x00, 0x00, 0xf8, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x1f,
   0x00, 0x00, 0x00, 0x00,
   
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x80, 0x07, 0xee, 0x01, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00,
   0xe2, 0x03, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0xf3, 0x03, 0x00, 0x00,
   0x00, 0x00, 0x18, 0x00, 0xe9, 0x07, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x80,
   0x78, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x02, 0xc0, 0x3a, 0x18, 0x00, 0x00,
   0x00, 0x00, 0x03, 0x40, 0x3c, 0x30, 0x00, 0x00, 0x00, 0x80, 0x01, 0x40,
   0x1c, 0x60, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x60, 0x1e, 0x40, 0x00, 0x00,
   0x00, 0x40, 0x00, 0x60, 0x0f, 0xc0, 0x00, 0x00, 0x18, 0x60, 0x00, 0xe0,
   0x1f, 0x80, 0x00, 0x00, 0x38, 0x38, 0x00, 0x18, 0x30, 0x80, 0x01, 0x00,
   0xf8, 0xf8, 0x00, 0x08, 0x20, 0x00, 0x01, 0x00, 0xf8, 0x3b, 0x0d, 0x88,
   0x20, 0x00, 0x03, 0x00, 0x78, 0xbf, 0x50, 0xf8, 0x7f, 0x62, 0x03, 0x00,
   0x70, 0xfc, 0x05, 0xf8, 0x33, 0x66, 0x03, 0x00, 0xe0, 0x3b, 0x55, 0xd9,
   0x6b, 0x06, 0x02, 0x00, 0x00, 0x5f, 0x05, 0xf8, 0x35, 0x80, 0xff, 0x03,
   0x00, 0x1f, 0x00, 0xd8, 0x3b, 0xf8, 0xd5, 0x3f, 0xe0, 0x19, 0x00, 0xf8,
   0x3b, 0x0e, 0x00, 0x18, 0x78, 0x36, 0x00, 0xf8, 0x3f, 0x04, 0x00, 0x18,
   0xf8, 0x33, 0x00, 0xf0, 0x3f, 0x0c, 0x00, 0x0c, 0xe0, 0x30, 0x00, 0x40,
   0x05, 0x08, 0x03, 0x06, 0x00, 0x60, 0x00, 0x00, 0x00, 0x90, 0x1f, 0x02,
   0x00, 0xe0, 0x00, 0x00, 0x00, 0xb0, 0xf1, 0x03, 0x00, 0xc0, 0x02, 0x00,
   0x00, 0xe0, 0x00, 0x01, 0x00, 0x80, 0x13, 0x00, 0x00, 0x74, 0x00, 0x00,
   0x00, 0x00, 0x07, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x44,
   0xa4, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x78, 0x89, 0xc0, 0x07, 0x00, 0x00,
   0x00, 0x00, 0xe0, 0xbf, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
   0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x03, 0x0c, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x3e, 0x03, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x03,
   0x18, 0x70, 0x00, 0x00, 0x00, 0x80, 0xe7, 0x03, 0x18, 0xfc, 0x00, 0x00,
   0x00, 0xc0, 0x03, 0x00, 0x30, 0x7e, 0x00, 0x00, 0x00, 0xe0, 0x03, 0x00,
   0x30, 0x1f, 0x00, 0x00, 0x00, 0xf0, 0x01, 0x00, 0xe0, 0x07, 0x00, 0x00,
   0x00, 0xe0, 0x00, 0x00, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x40, 0x00, 0x00, 0x00 };

//BLOCKING FUNCTION
                //  WIDTH         HEIGHT      FRAME DELAY   X INC            Y INC         START X POS     END X POS    START Y POS   END Y POS   NO FRAMES    SIZE OF EACH FRAME            ICON
void playAnimation(int _width, int _height, int fDelay, int xIncrement, int yIncrement, int startXpos, int endXpos, int startYpos, int endYpos, int _frames, int _sizeBytes, unsigned char _icon[frames][sizeBytes])
{
    int xPos = startXpos;
    int yPos = startYpos;

    boolean toLoop = true;
    boolean lefttoRight = true;
    boolean upToDown = true;

    boolean XtoLoop = true;
    boolean YtoLoop = true;

    while (toLoop)
    {
        //draw animation on screen
        //unsigned char tmp_Icon[_sizeBytes]; //NO NEED FOR THIS CHARACTER ARRAY
        
        for(int i = 0; i < _frames; i++)
        {
            if((startXpos - endXpos) < 0)
            {
                //moving left to right
                lefttoRight = true;
                if(xPos<endXpos)
                {
                    XtoLoop = true;
                }
                else
                {
                    XtoLoop = false;
                }
            }
            else
            {
                //right to left
                lefttoRight = false;
                if(xPos > endXpos)
                {
                    XtoLoop = true;
                }
                else
                {
                    XtoLoop = false;
                }
            }
            
            if((startYpos - endYpos) < 0)
            {
                //moving Up to down
                upToDown = true;
                if(yPos<endYpos)
                {
                    YtoLoop = true;
                }
                else
                {
                    YtoLoop = false;
                }
            }
            else
            {
                //Moving from bottom to top
                upToDown = false;
                if(yPos > endYpos)
                {
                    YtoLoop = true;
                }
                else
                {
                    YtoLoop = false;
                }
            }


            /* THIS CODE HAS BEEN REPLACED WITH WHAT YOU CAN SEE ON LINE 239, NO NEED TO COPY THE ARRAY
            for(int ii = 0; ii < _sizeBytes; ii++)
            {
                tmp_Icon[ii] = _icon[i][ii];
            }
            */
            
            delay(fDelay);

            if(XtoLoop == true)
            {
                if(lefttoRight == true){xPos = xPos + xIncrement;}
                else {xPos = xPos - xIncrement;}
            }

            if(YtoLoop == true)
            {
                if(upToDown == true){yPos = yPos + yIncrement;}
                else {yPos = yPos - yIncrement;}
            }
            
            //auxScreen.drawXBM(xPos, yPos, _width, _height, tmp_Icon); //REPLACED WITH THE BELOW LINE OF CODE
            auxScreen.drawXBM(xPos, yPos, _width, _height, _icon[i]);
            auxScreen.sendBuffer();
            auxScreen.clearBuffer();

            if(XtoLoop == false && YtoLoop == false)
            {
                toLoop = false;
            }
        }
    }
}