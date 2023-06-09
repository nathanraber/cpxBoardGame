//libraries:
#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>
#include <Talkie.h>

//variables:
int lrandlight; 
int rrandlight; 
volatile int userr = 0; 
volatile int userl = 9; 
int colorr; 
int colorg; 
int colorb; 
int score; 
volatile int gametime=5000; 
volatile bool lactuation =0; 
volatile bool ractuation =0; 
AsyncDelay tImer;
Talkie voice;

//spoken word data (from talkie library):
const uint8_t spLEVEL[] PROGMEM = {0x69,0xAB,0xC4,0xB3,0xD8,0x92,0x86,0x2D,0x83,0xEE,0x60,0xCD,0x12,0xD6,0x0C,0x66,0x45,0x2C,0x73,0x58,0x0B,0xA8,0x53,0xD6,0xAC,0x6D,0xE9,0xC0,0x57,0xC5,0xB2,0xAE,0xA1,0xB0,0x49,0x0D,0x7B,0xBD,0x86,0xA2,0x47,0x35,0xE3,0xF5,0xEA,0xB2,0x4B,0x4B,0xCB,0xC7,0xA3,0xCD,0xDE,0x23,0x59,0x1A,0x9A,0x31,0x8B,0xB0,0x54,0x76,0xE3,0xC6,0x26,0x5C,0x2C,0xCC,0x76,0x6B,0x92,0xBC,0x34,0x95,0xC6,0xA3,0xCE,0x74,0xDB,0x85,0x3B,0x8F,0xBA,0x90,0x9C,0x51,0xCC,0xD6,0xEA,0x4C,0x63,0x56,0x30,0x6D,0xA9,0x23,0xCF,0x59,0xD0,0x34,0xB5,0xF9,0x7F};
const uint8_t spZERO[] PROGMEM = {0x69,0xFB,0x59,0xDD,0x51,0xD5,0xD7,0xB5,0x6F,0x0A,0x78,0xC0,0x52,0x01,0x0F,0x50,0xAC,0xF6,0xA8,0x16,0x15,0xF2,0x7B,0xEA,0x19,0x47,0xD0,0x64,0xEB,0xAD,0x76,0xB5,0xEB,0xD1,0x96,0x24,0x6E,0x62,0x6D,0x5B,0x1F,0x0A,0xA7,0xB9,0xC5,0xAB,0xFD,0x1A,0x62,0xF0,0xF0,0xE2,0x6C,0x73,0x1C,0x73,0x52,0x1D,0x19,0x94,0x6F,0xCE,0x7D,0xED,0x6B,0xD9,0x82,0xDC,0x48,0xC7,0x2E,0x71,0x8B,0xBB,0xDF,0xFF,0x1F};
const uint8_t spONE[] PROGMEM = {0x66,0x4E,0xA8,0x7A,0x8D,0xED,0xC4,0xB5,0xCD,0x89,0xD4,0xBC,0xA2,0xDB,0xD1,0x27,0xBE,0x33,0x4C,0xD9,0x4F,0x9B,0x4D,0x57,0x8A,0x76,0xBE,0xF5,0xA9,0xAA,0x2E,0x4F,0xD5,0xCD,0xB7,0xD9,0x43,0x5B,0x87,0x13,0x4C,0x0D,0xA7,0x75,0xAB,0x7B,0x3E,0xE3,0x19,0x6F,0x7F,0xA7,0xA7,0xF9,0xD0,0x30,0x5B,0x1D,0x9E,0x9A,0x34,0x44,0xBC,0xB6,0x7D,0xFE,0x1F};
const uint8_t spTWO[]  PROGMEM = {0x06,0xB8,0x59,0x34,0x00,0x27,0xD6,0x38,0x60,0x58,0xD3,0x91,0x55,0x2D,0xAA,0x65,0x9D,0x4F,0xD1,0xB8,0x39,0x17,0x67,0xBF,0xC5,0xAE,0x5A,0x1D,0xB5,0x7A,0x06,0xF6,0xA9,0x7D,0x9D,0xD2,0x6C,0x55,0xA5,0x26,0x75,0xC9,0x9B,0xDF,0xFC,0x6E,0x0E,0x63,0x3A,0x34,0x70,0xAF,0x3E,0xFF,0x1F};
const uint8_t spTHREE[] PROGMEM = {0x0C,0xE8,0x2E,0x94,0x01,0x4D,0xBA,0x4A,0x40,0x03,0x16,0x68,0x69,0x36,0x1C,0xE9,0xBA,0xB8,0xE5,0x39,0x70,0x72,0x84,0xDB,0x51,0xA4,0xA8,0x4E,0xA3,0xC9,0x77,0xB1,0xCA,0xD6,0x52,0xA8,0x71,0xED,0x2A,0x7B,0x4B,0xA6,0xE0,0x37,0xB7,0x5A,0xDD,0x48,0x8E,0x94,0xF1,0x64,0xCE,0x6D,0x19,0x55,0x91,0xBC,0x6E,0xD7,0xAD,0x1E,0xF5,0xAA,0x77,0x7A,0xC6,0x70,0x22,0xCD,0xC7,0xF9,0x89,0xCF,0xFF,0x03};
const uint8_t spFOUR[] PROGMEM = {0x08,0x68,0x21,0x0D,0x03,0x1C,0x90,0xC0,0x88,0x92,0xB2,0x29,0x87,0x76,0x2B,0x2D,0x5C,0x7B,0x06,0xD9,0xED,0x74,0x64,0x51,0x54,0x4D,0xA2,0xBA,0x99,0xB7,0x3A,0xF8,0xEA,0x74,0xCA,0xD3,0x87,0xBE,0x94,0x3D,0xA4,0xD4,0x4E,0xC9,0x5F,0xF7,0x72,0xA7,0x9C,0x1C,0x63,0xDE,0xF2,0x9B,0xBE,0x34,0x84,0x27,0x2D,0x4B,0xF8,0x53,0x09,0x9C,0x0E,0xB7,0xEE,0xCB,0x5B,0x70,0xDD,0xB2,0xFC,0x3F};
const uint8_t spFIVE[] PROGMEM = {0x08,0x68,0x4E,0x9D,0x02,0x1C,0x60,0xC0,0x8C,0x69,0x12,0xB0,0xC0,0x28,0xAB,0x8C,0x9C,0xC0,0x2D,0xBB,0x38,0x79,0x31,0x15,0xA3,0xB6,0xE4,0x16,0xB7,0xDC,0xF5,0x6E,0x57,0xDF,0x54,0x5B,0x85,0xBE,0xD9,0xE3,0x5C,0xC6,0xD6,0x6D,0xB1,0xA5,0xBF,0x99,0x5B,0x3B,0x5A,0x30,0x09,0xAF,0x2F,0xED,0xEC,0x31,0xC4,0x5C,0xBE,0xD6,0x33,0xDD,0xAD,0x88,0x87,0xE2,0xD2,0xF2,0xF4,0xE0,0x16,0x2A,0xB2,0xE3,0x63,0x1F,0xF9,0xF0,0xE7,0xFF,0x01};
const uint8_t spSIX[] PROGMEM = {0x04,0xF8,0xB9,0x55,0x01,0xBF,0xA5,0x1B,0xE0,0x37,0x0F,0x03,0xFC,0x96,0x61,0x80,0xDF,0x3C,0x0C,0xF0,0x93,0xDA,0x4A,0x87,0x49,0x53,0x91,0x37,0x2B,0x6D,0xD2,0x55,0x23,0xDE,0xAC,0xAA,0xB9,0x16,0x09,0xFF,0xB2,0xFA,0x66,0x93,0x3C,0x63,0xF3,0x9C,0x10,0x38,0x45,0xA9,0x0A,0xD5,0x00,0x00,0x02,0x14,0x97,0xAA,0x80,0xAB,0x6B,0x0D,0xF0,0x63,0xA5,0x01,0x7E,0xCB,0x30,0xC0,0x6F,0xE9,0x0A,0xF8,0x25,0x93,0x01,0x3F,0x57,0xFC,0x3F};
const uint8_t spSEVEN[] PROGMEM = {0x0C,0x78,0xC6,0x95,0x01,0x3F,0xA5,0x28,0xE0,0xB7,0x52,0x0B,0x04,0xE0,0xB7,0x54,0x07,0xFC,0x52,0x66,0x80,0x9F,0xCB,0x56,0x59,0x6C,0x98,0x47,0x3E,0x59,0x4D,0x89,0x69,0x66,0xB9,0x7A,0x34,0x39,0x86,0x9B,0xD9,0xA6,0xD4,0xE7,0x10,0xAE,0xCA,0xAD,0x47,0x97,0x5D,0x9A,0xA9,0xAE,0x1A,0x75,0xB1,0xA5,0x66,0xF9,0xB2,0xD4,0x4D,0x63,0xB6,0x84,0x9A,0x52,0x76,0x45,0x11,0x1A,0xAA,0x4B,0x31,0x0C,0x79,0x4A,0xB0,0x49,0xC5,0x50,0xA2,0x41,0xA1,0xC9,0x65,0xD9,0xAB,0x89,0x56,0x84,0xFF,0x07};
const uint8_t spEIGHT[] PROGMEM = {0xAD,0x1B,0xDE,0x58,0x23,0x17,0xAF,0x6E,0xE8,0x20,0xEB,0x5C,0xBC,0xEA,0x61,0x03,0xAD,0x73,0xF6,0xAA,0x66,0x4A,0xD0,0xCC,0xD9,0xAB,0x1E,0x45,0xC1,0xA3,0x66,0xAF,0x61,0x36,0x03,0x8B,0x5A,0x9C,0xA6,0x51,0x04,0xA2,0x66,0x96,0xBB,0xBA,0x47,0xEC,0xED,0x8A,0x08,0x9C,0xA2,0x54,0x85,0x6A,0x00,0x80,0x02,0x86,0x74,0x63,0xC0,0xE6,0x6A,0xFF,0x0F};
const uint8_t spNINE[] PROGMEM = {0x62,0x75,0xDC,0x33,0xB5,0x62,0xB9,0x25,0x0B,0x8E,0x34,0x8F,0xD3,0xA6,0xAE,0x59,0xD2,0x34,0xE9,0x18,0x87,0x27,0xC9,0xD0,0x78,0xAB,0x6F,0xCE,0xC2,0x45,0x1B,0xAF,0xB6,0xF8,0x51,0x73,0x9D,0xB3,0x9A,0x12,0xC7,0x2C,0x6D,0xC9,0xAA,0x73,0x4B,0xF3,0x88,0x26,0xAB,0xCE,0x2D,0xCC,0x23,0xEA,0xAC,0x26,0xB7,0xD0,0x88,0x98,0xB3,0xBA,0x5C,0x43,0x32,0x7D,0xCE,0x1A,0x4A,0x0A,0xCD,0xF4,0x39,0x6B,0xAA,0x3E,0x24,0xCB,0x67,0xAF,0xB5,0xD9,0xE4,0x18,0x5F,0xB4,0xF6,0x6E,0x92,0x62,0x7D,0xD1,0x38,0xBA,0x09,0xF2,0x8D,0x59,0xED,0xE8,0x3A,0xD8,0x27,0x16,0xA6,0xBB,0x7B,0xF2,0x74,0x4F,0x92,0x9E,0x1E,0xC8,0x4A,0xC3,0x49,0x7A,0x9A,0x25,0x2B,0xF5,0x24,0xE9,0xEE,0xD1,0x24,0x25,0x27,0xBA,0xBB,0x25,0x51,0xD3,0xAA,0x24,0xAE,0x5E,0x54,0x55,0x3A,0xD4,0xFF,0x03};
const uint8_t spTEN[] PROGMEM = {0x0A,0xD8,0x5C,0x4D,0x03,0x2B,0xAB,0x5E,0xC4,0x33,0x2B,0xAF,0x62,0x84,0x12,0x0D,0x7B,0xB3,0xCA,0x66,0x43,0xA2,0xE3,0xF6,0xAA,0xAA,0x4E,0xC9,0x89,0xDB,0xAB,0x6E,0xBA,0xC5,0xDB,0x66,0xAF,0xB9,0xE8,0xE6,0x4C,0xBF,0x3D,0xE6,0x6A,0xC4,0x4B,0xCA,0x49,0xD9,0xBA,0x61,0x2B,0x09,0x25,0xED,0xE8,0x5A,0xB4,0xC4,0xED,0xA6,0x6B,0x18,0xE1,0x56,0xB7,0x9A,0xAE,0xA6,0x44,0x47,0xDC,0x6E,0xBE,0xC2,0xDD,0xA5,0xF0,0xB8,0xD9,0xFD,0x7F};
const uint8_t spELEVEN[] PROGMEM = {0x29,0x6F,0x52,0xA8,0xBB,0x6A,0x8F,0xBA,0x2B,0xC5,0xE8,0x9C,0xBD,0xAA,0x61,0x1D,0xB5,0xE3,0xF1,0xAA,0x9A,0x35,0xB6,0xB0,0xC5,0xAB,0x5E,0x44,0x53,0x4D,0xBA,0xAD,0x7A,0x42,0x1B,0xE1,0x5C,0xB3,0x9A,0x09,0x6D,0x94,0x62,0xE9,0x6A,0x8A,0x6A,0x37,0x8D,0xC7,0xAB,0x69,0xBC,0xDD,0xCC,0x5F,0xAF,0xB6,0xC9,0x76,0x37,0x7F,0xBD,0xDA,0x62,0xCA,0xDD,0x62,0xD1,0xEA,0xB2,0xCB,0x70,0xA3,0x45,0x69,0xCA,0x36,0xDD,0x14,0x1B,0xAE,0xBE,0x98,0x74,0x33,0x5E,0x39,0xFA,0x6C,0xC3,0x42,0xFC,0xF1,0xE8,0x8B,0x2E,0x71,0x8D,0xDB,0x63,0xA8,0x1A,0xAB,0x39,0x9C,0x8C,0xBE,0x69,0xCA,0xD2,0x50,0x32,0xFA,0xA6,0xD8,0x4B,0x52,0x71,0xEB,0xAA,0xE4,0x28,0x4E,0xD5,0xAD,0xCB,0xC2,0x3C,0x35,0x1D,0xB5,0x36,0xDB,0x14,0xAB,0x8C,0xF4,0xFF};
const uint8_t spTWELVE[] PROGMEM = {0x09,0x98,0xDA,0x22,0x01,0x37,0x78,0x1A,0x20,0x85,0xD1,0x50,0x3A,0x33,0x11,0x81,0x5D,0x5B,0x95,0xD4,0x44,0x04,0x76,0x9D,0xD5,0xA9,0x3A,0xAB,0xF0,0xA1,0x3E,0xB7,0xBA,0xD5,0xA9,0x2B,0xEB,0xCC,0xA0,0x3E,0xB7,0xBD,0xC3,0x5A,0x3B,0xC8,0x69,0x67,0xBD,0xFB,0xE8,0x67,0xBF,0xCA,0x9D,0xE9,0x74,0x08,0xE7,0xCE,0x77,0x78,0x06,0x89,0x32,0x57,0xD6,0xF1,0xF1,0x8F,0x7D,0xFE,0x1F};
const uint8_t spTHIRTEEN[] PROGMEM = {0x08,0x18,0xA2,0x12,0x03,0x18,0x40,0xC0,0x50,0x13,0x25,0x1D,0x3A,0x55,0x9D,0x5B,0xAF,0xAA,0xAB,0x74,0x4A,0xE9,0xB6,0xAA,0x6A,0xC7,0xA0,0xDD,0xDD,0xA8,0xAA,0x1F,0x82,0x75,0xED,0xA5,0x2A,0x8D,0x31,0xC6,0xB3,0x21,0x70,0x8A,0x52,0x15,0xAA,0x01,0x00,0x10,0x80,0xED,0x2C,0x12,0x70,0x53,0x55,0x00,0x66,0x2E,0x1D,0xD9,0x8C,0x46,0x14,0xB9,0x64,0xD5,0xD3,0x1B,0xD2,0xD4,0xAC,0xD1,0x2E,0x6B,0x44,0x9B,0xA5,0x46,0xBF,0xAC,0x91,0x6E,0x04,0x19,0xE3,0xD2,0x4A,0x76,0x6E,0xA4,0x2D,0xCB,0x2A,0xC9,0x65,0xE8,0xB6,0x0D,0x29,0x6C,0xEB,0xA1,0xC3,0xD1,0x1D,0x54,0xB9,0x28,0x75,0x67,0xB7,0x90,0xE5,0x6A,0x27,0xDC,0xDD,0xA1,0xB7,0xB9,0x92,0xF2,0x77,0x1B,0x1C,0x92,0x0D,0xDD,0xDF,0x92,0x9A,0x59,0x55,0xFC,0x7F};
const uint8_t spFOURTEEN[] PROGMEM = {0x08,0xE8,0x2A,0x94,0x00,0xC3,0x56,0x10,0x60,0xFA,0x0A,0x01,0x4C,0x97,0xAE,0x80,0x66,0xCB,0x4A,0x6F,0xF3,0x84,0xB1,0xB4,0x6E,0x9D,0x73,0x57,0x1A,0xD0,0x6E,0x74,0xC1,0x7D,0x71,0x61,0xD6,0x51,0x07,0xF7,0x26,0x25,0xDE,0x46,0x15,0xED,0x52,0x37,0xFB,0x29,0x65,0x1E,0x18,0x61,0xD6,0x1A,0x81,0x53,0x94,0xAA,0x50,0x0D,0x00,0x80,0x02,0x2C,0xE3,0x5E,0x80,0x13,0xBA,0x13,0x30,0x43,0xDB,0x2A,0x46,0x34,0xA2,0x8E,0xC5,0xAB,0x9A,0xDE,0x88,0x2E,0x4A,0xAD,0x7A,0x7A,0x25,0x7E,0x0F,0xB2,0xDA,0x69,0x84,0xED,0xC4,0xEC,0xEA,0xA6,0x15,0xF6,0x53,0xB1,0x6B,0x18,0x56,0x38,0x4F,0xCC,0x8D,0x71,0x5A,0x61,0x7F,0x35,0x3A,0xC6,0xA1,0x44,0xFC,0xCD,0x74,0x9B,0xBA,0xC1,0xCA,0x54,0xAB,0x6D,0x6C,0x06,0x3B,0x5D,0xED,0xB4,0xA1,0x29,0x6A,0x37,0x57,0xDD,0x86,0x2A,0xA9,0x52,0x43,0x51,0xEB,0xAA,0x0E,0x8E,0xA8,0x48,0xFF,0x0F};
const uint8_t spFIFTEEN[] PROGMEM = {0x02,0x68,0xD6,0xCC,0x00,0x43,0x9A,0x39,0x60,0x3A,0xF7,0x51,0x34,0x5B,0x6A,0x2C,0x6D,0x4E,0xD5,0x92,0x99,0x89,0x2C,0x39,0x55,0xF3,0xAE,0xA6,0x32,0x67,0x54,0xC5,0x99,0xB9,0xC8,0x1C,0x07,0x0C,0xA5,0x94,0x01,0x04,0x4E,0x51,0xAA,0x42,0x35,0x00,0x02,0xB0,0x84,0x4A,0x6B,0x4F,0x6C,0x23,0x15,0x2F,0x6D,0x18,0xC1,0x44,0xC2,0x17,0x8F,0x69,0xBA,0x54,0xA8,0x58,0x3D,0xE6,0x6D,0x53,0xA1,0x73,0xF5,0x5A,0xA6,0x31,0xA2,0x8D,0x89,0x63,0x9D,0xCE,0x88,0xD6,0x47,0xB6,0x75,0x5B,0x13,0x6C,0xAF,0x54,0x96,0x61,0x84,0x22,0x64,0x74,0x59,0x9A,0x61,0x4B,0x0D,0xA7,0x65,0x6A,0x86,0xD2,0x23,0x5C,0xA7,0xB1,0x08,0xCA,0xB0,0x70,0x9D,0x86,0xA2,0x38,0xC9,0xA2,0x55,0xE8,0x32,0x11,0x8F,0x94,0xD6,0xFF,0x0F};
const uint8_t spSIXTEEN[] PROGMEM = {0x0C,0x78,0xC6,0x95,0x01,0x3F,0xA5,0x28,0xE0,0xB7,0x52,0x0B,0x04,0xE0,0xB7,0x54,0x07,0xFC,0x52,0x66,0x80,0x9F,0xCB,0x96,0xB7,0xA5,0x1B,0x9B,0x66,0x5A,0x59,0xB3,0x26,0x1A,0xF6,0xA6,0x15,0xCD,0x2B,0x59,0xFA,0x6A,0x04,0x4E,0x51,0xAA,0x42,0x35,0x40,0x01,0x25,0xA7,0x24,0xE0,0x98,0x1E,0x07,0xFC,0x9D,0x2E,0x80,0x57,0x9D,0x18,0xB0,0x05,0x6A,0x02,0xAE,0x54,0x1D,0x6D,0x77,0xCA,0xEA,0xF9,0x78,0xF5,0xD3,0x1A,0x51,0xE7,0xE2,0x35,0x4F,0x6F,0xC4,0x53,0x93,0xC6,0x3A,0x9D,0x91,0x6C,0x86,0x6A,0xC7,0x34,0x2A,0x7A,0x66,0x36,0x9D,0xD3,0xA9,0xC8,0x99,0xD5,0x72,0x75,0xC7,0x92,0xA3,0x96,0xC3,0xD3,0x3D,0x46,0xA4,0x3A,0x09,0x4F,0x73,0x98,0xE1,0xEA,0x24,0x3C,0xDD,0x92,0x87,0xBB,0x93,0xF4,0x0D,0x63,0x94,0x2E,0x75,0xFF,0x1F};
const uint8_t spSEVENTEEN[] PROGMEM = {0x0C,0xF8,0x29,0x45,0x01,0xBF,0x95,0x5A,0x20,0x00,0xBF,0xA5,0x3A,0xE0,0x97,0x32,0x03,0xFC,0x5C,0xB6,0xAA,0x26,0x53,0xD5,0x7D,0xF5,0x6A,0x8A,0x4E,0xB5,0xCC,0x47,0xAB,0xAB,0xAA,0xD4,0xC2,0x36,0xA7,0x31,0xF9,0x30,0x33,0x49,0x9D,0x86,0x6C,0xD5,0x5D,0xA4,0xF5,0xE8,0xAB,0x32,0x37,0x97,0x95,0x69,0xA8,0x0A,0x7B,0x50,0xD5,0xA5,0xA1,0x69,0xA8,0x56,0x63,0x1B,0xC6,0xA6,0xB1,0x43,0xD4,0x35,0x24,0xE0,0x18,0xB3,0x96,0xAF,0xBC,0x99,0x86,0x9A,0x5A,0xD5,0x2C,0x71,0xD6,0xC4,0x5C,0xF5,0x2C,0x4E,0x94,0x31,0x6B,0x35,0x33,0x1A,0xF2,0x64,0xE9,0xD5,0x4F,0xAF,0xA8,0x1B,0x81,0xC7,0xBC,0xAC,0x91,0x9E,0x1B,0x29,0xDB,0x32,0x8A,0x7A,0x19,0xA8,0xEC,0x43,0x08,0xC5,0xB9,0xE9,0xF4,0x34,0x0D,0x35,0xAE,0x76,0xD3,0x5B,0x14,0x76,0xA9,0x3B,0x4A,0x7F,0x77,0x58,0xA1,0xE6,0x38,0xFD,0xDD,0x51,0x9A,0xBB,0xAB,0xF4,0x57,0x67,0x16,0xDA,0xB3,0xFE,0x1F};
const uint8_t spEIGHTEEN[] PROGMEM = {0x6B,0x18,0x36,0x88,0x3B,0x1B,0xEF,0x61,0x0D,0xD3,0x27,0x52,0xE5,0x9A,0x51,0x8F,0x1E,0xC8,0x96,0x4B,0x5A,0xD5,0x03,0x61,0xD5,0xCC,0x72,0x75,0x35,0x10,0xD3,0x13,0x11,0x81,0x53,0x94,0xAA,0x50,0x0D,0x80,0x02,0x2C,0x95,0x5A,0x80,0x17,0xC7,0x57,0x3E,0xBD,0x33,0x6B,0x36,0x59,0xD5,0xC8,0x4E,0xE4,0xB9,0x64,0xD5,0x33,0x24,0x61,0xE7,0xA4,0x35,0x2C,0xEF,0x28,0x9B,0xA5,0xC6,0x38,0x9D,0xA2,0x5F,0x84,0x6E,0xCB,0x74,0x8A,0x7E,0x6E,0xA6,0xEC,0xCD,0xB0,0x76,0x4B,0xD4,0x72,0x74,0x87,0x1E,0xA9,0x76,0xD2,0x3D,0x3C,0x59,0x84,0x26,0x4D,0x4F,0xD3,0x68,0x15,0xEE,0xE4,0xFF,0x01};
const uint8_t spNINETEEN[] PROGMEM = {0x6E,0x2F,0x44,0xB4,0x5B,0x93,0xA6,0xAD,0x32,0x96,0x2E,0x69,0xBA,0x96,0x26,0xD3,0xCC,0x65,0xF1,0x1A,0x9B,0x9C,0xE0,0xD4,0x2D,0x6B,0x68,0xA6,0xCD,0xCA,0x56,0xAF,0xAE,0xB9,0x64,0x6F,0x5F,0xB4,0xEA,0xE6,0x84,0xA7,0xA3,0x52,0xAB,0x5B,0x40,0xAB,0x28,0xD3,0xAE,0xCD,0x0A,0xC7,0x5D,0x35,0x23,0x70,0x8A,0x52,0x15,0xAA,0x01,0x50,0x80,0xAB,0x4C,0x0A,0xB0,0x7C,0x4B,0xCB,0x57,0xDE,0x4C,0x43,0x4D,0xAD,0x6A,0x96,0x38,0x6B,0x62,0xAE,0x7A,0x16,0x27,0xCA,0x98,0xB5,0x9A,0x19,0x0D,0x79,0xB2,0xF4,0xEA,0xA7,0x57,0xD4,0x8D,0xC0,0x63,0x5E,0xD6,0x48,0xCF,0x8D,0x94,0x6D,0x19,0x45,0xBD,0x0C,0x54,0xF6,0x21,0x84,0xE2,0xDC,0x74,0x79,0x9A,0x86,0x1A,0x57,0xBB,0xE5,0x2D,0x0A,0xBB,0xD4,0x1D,0x95,0xBF,0x3B,0xAC,0x50,0x73,0x5C,0xFE,0xEE,0x28,0xCD,0xDD,0x55,0xF8,0xAB,0x33,0x0B,0xED,0x59,0xFF,0x0F};
const uint8_t spTWENTY[] PROGMEM = {0x0A,0xE8,0x4A,0xCD,0x01,0xDB,0xB9,0x33,0xC0,0xA6,0x54,0x0C,0xA4,0x34,0xD9,0xF2,0x0A,0x6C,0xBB,0xB3,0x53,0x0E,0x5D,0xA6,0x25,0x9B,0x6F,0x75,0xCA,0x61,0x52,0xDC,0x74,0x49,0xA9,0x8A,0xC4,0x76,0x4D,0xD7,0xB1,0x76,0xC0,0x55,0xA6,0x65,0xD8,0x26,0x99,0x5C,0x56,0xAD,0xB9,0x25,0x23,0xD5,0x7C,0x32,0x96,0xE9,0x9B,0x20,0x7D,0xCB,0x3C,0xFA,0x55,0xAE,0x99,0x1A,0x30,0xFC,0x4B,0x3C,0xFF,0x1F};

//functions:
void randomcolors(){//random color light generating function
  colorr = random(255); //chose random red value
  colorg = random(255); //chose random green value
  colorb = random(255); //chose random blue value
  lrandlight = random(4)+5; //choose random position on left half of board
  rrandlight = random(4)+1; //choose random position on right half of board
  CircuitPlayground.setPixelColor(lrandlight, colorr, colorg, colorb); //display left random light
  CircuitPlayground.setPixelColor(rrandlight, colorr, colorg, colorb); //display right random light
}
void breathing(){//loosing color pattern
  for(int i=0; i<2; i++){
    for(int i=0;i<255;i++)
    {
    CircuitPlayground.setPixelColor(1, i, 0, 0);
    CircuitPlayground.setPixelColor(2, i, 0, 0);
    CircuitPlayground.setPixelColor(3, i, 0, 0);
    CircuitPlayground.setPixelColor(4, i, 0, 0);
    CircuitPlayground.setPixelColor(5, i, 0, 0);
    CircuitPlayground.setPixelColor(6, i, 0, 0);
    CircuitPlayground.setPixelColor(7, i, 0, 0);
    CircuitPlayground.setPixelColor(8, i, 0, 0);
    CircuitPlayground.setPixelColor(9, i, 0, 0);
    CircuitPlayground.setPixelColor(0, i, 0, 0);
    }
    tImer.repeat();
    for(int i=255;i>0;i--)
    {
    CircuitPlayground.setPixelColor(1, i, 0, 0);
    CircuitPlayground.setPixelColor(2, i, 0, 0);
    CircuitPlayground.setPixelColor(3, i, 0, 0);
    CircuitPlayground.setPixelColor(4, i, 0, 0);
    CircuitPlayground.setPixelColor(5, i, 0, 0);
    CircuitPlayground.setPixelColor(6, i, 0, 0);
    CircuitPlayground.setPixelColor(7, i, 0, 0);
    CircuitPlayground.setPixelColor(8, i, 0, 0);
    CircuitPlayground.setPixelColor(9, i, 0, 0);
    CircuitPlayground.setPixelColor(0, i, 0, 0);
    }
    tImer.repeat();
  }
}
void singlePressl() {//left button flag
  lactuation = 1;
}
void singlePressr() {//right button flag
  ractuation = 1;
}
void loose(){//losing function
  CircuitPlayground.clearPixels(); //turnoff all pixels
  score=(5000-gametime)/250; //evaluate score based on gametime
  CircuitPlayground.speaker.say(spLEVEL); // say "level"
  switch(score){// say "[score value]"
    case 0: CircuitPlayground.speaker.say(spZERO);
    break;
    case 1: CircuitPlayground.speaker.say(spONE);
    break;
    case 2: CircuitPlayground.speaker.say(spTWO);
    break;
    case 3: CircuitPlayground.speaker.say(spTHREE);
    break;
    case 4: CircuitPlayground.speaker.say(spFOUR);
    break;
    case 5: CircuitPlayground.speaker.say(spFIVE);
    break;
    case 6: CircuitPlayground.speaker.say(spSIX);
    break;
    case 7: CircuitPlayground.speaker.say(spSEVEN);
    break;
    case 8: CircuitPlayground.speaker.say(spEIGHT);
    break;
    case 9: CircuitPlayground.speaker.say(spNINE);
    break;
    case 10: CircuitPlayground.speaker.say(spTEN);
    break;
    case 11: CircuitPlayground.speaker.say(spELEVEN);
    break;
    case 12: CircuitPlayground.speaker.say(spTWELVE);
    break;
    case 13: CircuitPlayground.speaker.say(spTHIRTEEN);
    break;
    case 14: CircuitPlayground.speaker.say(spFOURTEEN);
    break;
    case 15: CircuitPlayground.speaker.say(spFIFTEEN);
    break;
    case 16: CircuitPlayground.speaker.say(spSIXTEEN);
    break;
    case 17: CircuitPlayground.speaker.say(spSEVENTEEN);
    break;
    case 18: CircuitPlayground.speaker.say(spEIGHTEEN);
    break;
    case 19: CircuitPlayground.speaker.say(spNINETEEN);
    break;
    case 20: CircuitPlayground.speaker.say(spTWENTY);
    break;
  }
  gametime=5000;//reset gametime
  score=0;//reset score
  breathing();// play losing animation
}
void win(){//winning function
  CircuitPlayground.clearPixels(); //turn off all lights
  gametime=gametime-250; //reduce the game time length by 250ms
}
void reset(){//reset function
    CircuitPlayground.clearPixels(); //turn off all pixels
    userr = 0; //set the right user selector led to the starting position
    userl = 9; //set the left user selector led to the starting position
}
//setup:
void setup(){
  CircuitPlayground.begin(); //initalize CPX board
  attachInterrupt(digitalPinToInterrupt(5), singlePressl, FALLING); //attach interupts to left pin
  attachInterrupt(digitalPinToInterrupt(4), singlePressr, FALLING); //attach interupts to right pin
}
//loop:
void loop() {
  randomSeed(random()); //randomize where you start in the random number sequence
  tImer.start(gametime, AsyncDelay::MILLIS); //start the global game timer
  randomcolors(); //display random colors on pins
  CircuitPlayground.setPixelColor(userl, 255, 255, 255); //set left selector led at beggining
  CircuitPlayground.setPixelColor(userr, 255, 255, 255); //set right selector led at beggining
  while(!tImer.isExpired()){ //while the timer is still going
    if(lactuation && (userl >= lrandlight)){ // if you push the left button and the left light is not on the pin of the random light yet
      userl--;//advance one position
      CircuitPlayground.setPixelColor(userl+1, 0, 0, 0); //turns selector led off
      CircuitPlayground.setPixelColor(userl, 255, 255, 255); //advances selector led to next position
      lactuation =0; //reset the left button flag
    }
    if(ractuation && (userr <= rrandlight)){ //if you push the right button and the right selector led is less than the random light
      userr++; //advance the selector led
      CircuitPlayground.setPixelColor(userr-1, 0, 0, 0); //set selector led to off
      CircuitPlayground.setPixelColor(userr, 255, 255, 255); //advance selector led position
      ractuation =0; //reset right button interupt
    }
    else if(!(userr <= rrandlight)){ //one way to loose; right selector led goes past random led
      loose(); //run through losing fuction
      break;// break out of while loop
      }
    else if(!(userl >= lrandlight)){ //another way to loose; left sector light is past left random light
      loose(); //run through losing fuction
      break; //break out of while loop
      }
    if(userr==rrandlight && userl==lrandlight){ //how you win; if both selector leds are equal to the random leds
      win(); //run through winning function
      break; //break out of while loop
    }
  }
  while(tImer.isExpired()){ //if the timer is up
    loose(); //you loose
    break; //break out of while loop
  }
  reset(); //the game resets
}
