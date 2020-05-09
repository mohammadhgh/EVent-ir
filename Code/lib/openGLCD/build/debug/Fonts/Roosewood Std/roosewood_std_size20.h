

/*
 *
 * new Font
 *
 * created with GLCDFontCreator
 * original framework by F. Maximilian Thiele
 * Modified By Siddharth Kaul
 *
 *
 * File Name           : roosewood_std_size20.h
 * Date                : 10.11.2012
 * Font size in bytes  : 21024
 * Font width          : 10
 * Font height         : 22
 * Font first char     : 32
 * Font last char      : 128
 * Font used chars     : 96
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef NEW_FONT_H
#define NEW_FONT_H

#define NEW_FONT_WIDTH 10
#define NEW_FONT_HEIGHT 22

static uint8_t new_Font[] PROGMEM = {
    0x52, 0x20, // size
    0x0A, // width
    0x16, // height
    0x20, // first char
    0x60, // char count
    
    // char widths
    0x00, 0x06, 0x07, 0x09, 0x0A, 0x10, 0x0D, 0x04, 0x05, 0x07, 
    0x07, 0x09, 0x05, 0x04, 0x04, 0x08, 0x0A, 0x07, 0x0A, 0x0A, 
    0x0A, 0x0A, 0x0A, 0x0C, 0x0B, 0x0B, 0x04, 0x04, 0x09, 0x09, 
    0x09, 0x0A, 0x0E, 0x0C, 0x0C, 0x0B, 0x0C, 0x0B, 0x0A, 0x0B, 
    0x0C, 0x08, 0x0A, 0x0D, 0x0B, 0x0E, 0x0C, 0x0B, 0x0B, 0x0D, 
    0x0D, 0x0A, 0x0A, 0x0C, 0x0C, 0x0F, 0x0C, 0x0C, 0x0A, 0x06, 
    0x05, 0x07, 0x09, 0x0A, 0x05, 0x0C, 0x0C, 0x0B, 0x0C, 0x0B, 
    0x0A, 0x0B, 0x0C, 0x08, 0x0A, 0x0D, 0x0B, 0x0E, 0x0C, 0x0B, 
    0x0B, 0x0D, 0x0D, 0x0A, 0x0A, 0x0C, 0x0C, 0x0F, 0x0C, 0x0C, 
    0x0A, 0x08, 0x02, 0x06, 0x09, 0x0A, 
    
    // font data
    0xE0, 0xF0, 0xF0, 0x10, 0xE0, 0x80, 0xC1, 0x3F, 0x33, 0xFC, 0xFF, 0x07, 0x04, 0x08, 0x18, 0x1C, 0x1C, 0x00, // 33
    0x70, 0xF8, 0xF0, 0xF0, 0xF8, 0xF8, 0xF0, 0x00, 0x03, 0x07, 0x03, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 34
    0x00, 0x80, 0x80, 0xC0, 0xB0, 0x80, 0xC0, 0xB0, 0x80, 0x18, 0x99, 0x7D, 0x1B, 0xD9, 0x3D, 0x1B, 0x19, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 35
    0x80, 0xC0, 0xE0, 0xB8, 0xF8, 0xF0, 0x60, 0xC0, 0x80, 0x00, 0x73, 0x8F, 0x4F, 0x75, 0x87, 0x6B, 0x7B, 0x27, 0x8F, 0xFE, 0x00, 0x00, 0x04, 0x08, 0x30, 0x38, 0x38, 0x1C, 0x1C, 0x0C, // 36
    0xC0, 0xE0, 0xF0, 0xF0, 0xD0, 0xF0, 0x20, 0xC0, 0xC0, 0xB0, 0xD0, 0x70, 0x20, 0x00, 0x00, 0x00, 0x03, 0x05, 0x0B, 0x8F, 0x7F, 0x1B, 0xC4, 0xF7, 0x0B, 0x06, 0xFF, 0xF6, 0x06, 0x0C, 0xF8, 0xE0, 0x00, 0x00, 0x00, 0x1C, 0x18, 0x1C, 0x00, 0x00, 0x04, 0x08, 0x18, 0x18, 0x18, 0x1C, 0x0C, 0x04, // 37
    0x00, 0xC0, 0xE0, 0xF0, 0xF0, 0xF0, 0xE0, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x3E, 0x1F, 0x7D, 0x57, 0x76, 0x8F, 0x1B, 0x43, 0x72, 0x3A, 0xDC, 0x98, 0x00, 0x04, 0x08, 0x08, 0x18, 0x18, 0x1C, 0x18, 0x08, 0x18, 0x1C, 0x1C, 0x0C, // 38
    0x70, 0xE8, 0x08, 0xF0, 0x01, 0x02, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, // 39
    0x00, 0xF0, 0xE8, 0xF8, 0xF0, 0xFF, 0x95, 0x7F, 0xFF, 0x00, 0x00, 0x0C, 0x10, 0x3C, 0x3C, // 40
    0x08, 0xF8, 0x68, 0xF0, 0xE0, 0xC0, 0x00, 0x00, 0xC0, 0x3F, 0xAD, 0xD5, 0xFF, 0xFE, 0x08, 0x14, 0x30, 0x38, 0x3C, 0x0C, 0x00, // 41
    0xC0, 0xF0, 0xE8, 0xF8, 0xD8, 0x60, 0xE0, 0x00, 0x03, 0x05, 0x07, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 42
    0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0xFF, 0xFF, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x00, // 43
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x80, 0x00, 0x34, 0x68, 0x70, 0x7C, 0x38, // 44
    0x00, 0x00, 0x00, 0x00, 0x1C, 0x14, 0x14, 0x14, 0x00, 0x00, 0x00, 0x00, // 45
    0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x80, 0x00, 0x0C, 0x18, 0x1C, 0x1C, // 46
    0x00, 0x00, 0x00, 0x80, 0xE0, 0x70, 0xF0, 0x60, 0xC0, 0x30, 0x8E, 0xE7, 0x7D, 0x1F, 0x03, 0x00, 0x0C, 0x18, 0x1C, 0x0C, 0x00, 0x00, 0x00, 0x00, // 47
    0x00, 0xC0, 0xE0, 0xF0, 0xF0, 0xF0, 0xE0, 0xA0, 0xC0, 0x80, 0x3F, 0xFD, 0x07, 0x7F, 0xFF, 0x7F, 0x47, 0x3F, 0xC0, 0xFF, 0x00, 0x00, 0x04, 0x08, 0x18, 0x18, 0x1C, 0x1C, 0x0C, 0x04, // 48
    0xE0, 0xE0, 0xF0, 0xF0, 0xF0, 0xE0, 0x00, 0x80, 0x7F, 0x3E, 0x0A, 0xFF, 0xFF, 0x00, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x1C, // 49
    0xC0, 0xA0, 0xE0, 0xF0, 0xF0, 0xB0, 0xE0, 0xA0, 0xC0, 0x80, 0xC1, 0x33, 0x5D, 0x2F, 0x36, 0x7F, 0x7A, 0x1D, 0xFF, 0xC7, 0x0C, 0x18, 0x1C, 0x1C, 0x08, 0x08, 0x18, 0x1C, 0x1C, 0x0C, // 50
    0xC0, 0xA0, 0xD0, 0xF0, 0xF0, 0xF0, 0xE0, 0xA0, 0xC0, 0x00, 0xF1, 0x0B, 0x4E, 0xFF, 0x4E, 0x77, 0x39, 0x8F, 0xFF, 0xE7, 0x00, 0x04, 0x08, 0x08, 0x18, 0x18, 0x1C, 0x1C, 0x0C, 0x04, // 51
    0x00, 0x00, 0x00, 0x80, 0xE0, 0x50, 0xF0, 0xF0, 0xF0, 0xE0, 0x38, 0x64, 0x63, 0x72, 0xFD, 0x7F, 0x3D, 0x0D, 0x6F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x1C, // 52
    0x00, 0xE0, 0x30, 0xB0, 0xB0, 0xB0, 0xB0, 0x90, 0xF0, 0xC0, 0xF0, 0x0F, 0x0A, 0xFF, 0x4F, 0x7D, 0x7D, 0x93, 0xFD, 0xF1, 0x00, 0x04, 0x08, 0x08, 0x18, 0x18, 0x1C, 0x0C, 0x0C, 0x00, // 53
    0x00, 0xC0, 0xE0, 0x60, 0xB0, 0xF0, 0xD0, 0xE0, 0xC0, 0x80, 0x7F, 0x84, 0x3F, 0x77, 0xFB, 0x72, 0x4F, 0xBF, 0xFF, 0xE7, 0x00, 0x00, 0x04, 0x08, 0x18, 0x18, 0x18, 0x1C, 0x0C, 0x04, // 54
    0xF0, 0xF0, 0x70, 0xA0, 0xB0, 0xF0, 0x60, 0xE0, 0xD0, 0xF0, 0xF0, 0xE0, 0x07, 0x0F, 0x0F, 0xE7, 0x5E, 0x3B, 0xE5, 0xFE, 0x3F, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x18, 0x18, 0x1C, 0x1C, 0x00, 0x00, 0x00, 0x00, // 55
    0x80, 0xE0, 0xE0, 0xF0, 0x70, 0xF0, 0x30, 0xE0, 0xE0, 0xC0, 0x00, 0x73, 0x8F, 0x76, 0xF5, 0xB7, 0xAE, 0x7B, 0x7B, 0x85, 0xFF, 0xE7, 0x00, 0x04, 0x0C, 0x08, 0x18, 0x18, 0x18, 0x1C, 0x0C, 0x0C, 0x00, // 56
    0x80, 0xE0, 0xE0, 0xF0, 0xF0, 0xF0, 0xE0, 0xA0, 0xC0, 0x80, 0x00, 0xE7, 0x1B, 0x97, 0xFF, 0xBF, 0x7B, 0x47, 0x39, 0xC6, 0xFF, 0x7E, 0x00, 0x04, 0x0C, 0x08, 0x18, 0x18, 0x1C, 0x0C, 0x0C, 0x04, 0x00, // 57
    0x00, 0x00, 0x00, 0x00, 0x8E, 0x71, 0xBE, 0x1C, 0x0C, 0x18, 0x1C, 0x1C, // 58
    0x00, 0x00, 0x00, 0x00, 0x8E, 0x71, 0x7E, 0x98, 0x34, 0xF8, 0x70, 0x7C, // 59
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x18, 0x18, 0x3C, 0x24, 0x66, 0x42, 0xC3, 0x81, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, // 60
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 61
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x81, 0xC3, 0x42, 0x66, 0x24, 0x3C, 0x38, 0x18, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 62
    0xC0, 0xA0, 0xD0, 0xF0, 0xF0, 0xF0, 0xE0, 0xA0, 0xC0, 0x80, 0x03, 0x05, 0xDF, 0x36, 0x2F, 0xFB, 0x3C, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x04, 0x08, 0x18, 0x1C, 0x1C, 0x00, 0x00, 0x00, // 63
    0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x00, 0x00, 0x78, 0xFE, 0x07, 0xF1, 0xF8, 0x8C, 0x44, 0x22, 0xFE, 0xFE, 0x82, 0x40, 0x63, 0x1E, 0x00, 0x04, 0x0C, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x00, 0x00, // 64
    0x00, 0x00, 0x00, 0xC0, 0x40, 0xF0, 0xF0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x3C, 0x03, 0xE6, 0xE5, 0xEF, 0x77, 0x07, 0x3F, 0xF8, 0xC0, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, // 65
    0x30, 0x30, 0xF0, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0xD0, 0xA0, 0xC0, 0x00, 0x80, 0x80, 0x7F, 0x77, 0x0C, 0xFF, 0xFF, 0x77, 0x4F, 0xB5, 0xFF, 0xE7, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x0C, 0x04, // 66
    0x80, 0x40, 0xE0, 0xB0, 0xF0, 0xB0, 0x60, 0xF0, 0xF0, 0xF0, 0xC0, 0x7F, 0xBD, 0x03, 0x7F, 0xFF, 0x80, 0x77, 0x1F, 0x9F, 0xFF, 0xCF, 0x00, 0x04, 0x0C, 0x08, 0x18, 0x18, 0x18, 0x1C, 0x0C, 0x0C, 0x00, // 67
    0x30, 0x30, 0xF0, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0xD0, 0xA0, 0xC0, 0x80, 0x80, 0x82, 0x7F, 0x7F, 0x10, 0xFF, 0xFF, 0x60, 0x7F, 0x9F, 0xE0, 0xFF, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x0C, 0x0C, 0x04, // 68
    0x30, 0x30, 0xF0, 0xF0, 0x70, 0xF0, 0xF0, 0xB0, 0xF0, 0xF0, 0xC0, 0x80, 0x80, 0x7F, 0x7F, 0x14, 0xFF, 0xFF, 0x7F, 0x17, 0xF7, 0xC7, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x1C, // 69
    0x30, 0x30, 0xF0, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0x80, 0x80, 0x7F, 0x77, 0x0C, 0x7F, 0xFF, 0x1F, 0x1F, 0x07, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x00, 0x00, 0x00, // 70
    0x80, 0x40, 0xE0, 0xB0, 0xF0, 0xB0, 0xE0, 0xF0, 0xF0, 0xF0, 0xC0, 0x7F, 0xFD, 0x07, 0x7F, 0xFF, 0xB8, 0x6F, 0x0F, 0xEF, 0xEF, 0x7F, 0x00, 0x04, 0x0C, 0x08, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x1C, 0x00, // 71
    0x30, 0x30, 0xF0, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0x80, 0x80, 0x7F, 0x7F, 0x14, 0xFF, 0xFF, 0x7F, 0x6E, 0x16, 0xFF, 0xFF, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x18, 0x18, 0x18, 0x18, 0x1C, // 72
    0x70, 0x70, 0xF0, 0xF0, 0x30, 0xF0, 0xF0, 0xE0, 0x80, 0x80, 0x7F, 0x3F, 0x10, 0xFF, 0xFF, 0x00, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x18, // 73
    0x00, 0x00, 0x00, 0x00, 0x70, 0xB0, 0xF0, 0xF0, 0xF0, 0xF0, 0x70, 0x88, 0x08, 0x70, 0x60, 0x3F, 0x77, 0x9B, 0xFF, 0xFF, 0x00, 0x04, 0x0C, 0x08, 0x18, 0x18, 0x1C, 0x1C, 0x0C, 0x00, // 74
    0x30, 0x30, 0xF0, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0xF0, 0x70, 0xF0, 0xF0, 0xC0, 0x80, 0x80, 0x7F, 0x3F, 0x14, 0xFB, 0xED, 0xF3, 0x4E, 0x3F, 0x63, 0xC0, 0x00, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, // 75
    0x30, 0x30, 0xF0, 0xF0, 0x70, 0xF0, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x80, 0x82, 0x7F, 0x7F, 0x10, 0x7F, 0xFF, 0x80, 0x60, 0xE0, 0xC0, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x1C, // 76
    0x70, 0x50, 0xB0, 0xF0, 0x70, 0xF0, 0xE0, 0xA0, 0x70, 0xF0, 0xF0, 0xF0, 0xF0, 0xE0, 0x80, 0x80, 0x7F, 0x07, 0xFF, 0x8C, 0x77, 0x87, 0xFE, 0x7D, 0x1D, 0xFF, 0xFF, 0x00, 0x0C, 0x18, 0x18, 0x18, 0x1C, 0x1C, 0x18, 0x1C, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x1C, // 77
    0x70, 0x70, 0xF0, 0xF0, 0xF0, 0xF0, 0x70, 0xF0, 0xF0, 0xF0, 0xD0, 0xF0, 0x80, 0x80, 0x7F, 0x01, 0xFF, 0xF2, 0xBF, 0x0B, 0x07, 0xFF, 0xFF, 0x00, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x04, 0x18, 0x18, 0x1C, 0x1C, 0x00, // 78
    0x80, 0xC0, 0xE0, 0xF0, 0xF0, 0xF0, 0xD0, 0xA0, 0x40, 0xC0, 0x00, 0x7F, 0xFA, 0x07, 0x7F, 0xFF, 0x7F, 0x87, 0x7D, 0x86, 0xFF, 0xFF, 0x00, 0x04, 0x0C, 0x08, 0x18, 0x18, 0x18, 0x1C, 0x0C, 0x0C, 0x00, // 79
    0x70, 0x70, 0xF0, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0xE0, 0xA0, 0xC0, 0x80, 0x82, 0x7D, 0x7F, 0x04, 0xF7, 0xF7, 0x37, 0x35, 0x3B, 0x1F, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x18, 0x00, 0x00, 0x00, // 80
    0x00, 0xC0, 0xE0, 0xE0, 0xF0, 0xF0, 0xD0, 0xA0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x3F, 0xFE, 0x03, 0xEF, 0xEF, 0x5F, 0xC7, 0x3D, 0x06, 0xFF, 0x7E, 0xC0, 0x80, 0x00, 0x00, 0x0C, 0x0C, 0x18, 0x18, 0x18, 0x1C, 0x18, 0x18, 0x1C, 0x1C, 0x0C, // 81
    0x70, 0x70, 0xF0, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0x00, 0x00, 0x80, 0x80, 0x7F, 0x7F, 0x14, 0x7F, 0xFF, 0xFF, 0x1D, 0x73, 0x3F, 0x17, 0xE0, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x1C, 0x08, 0x08, 0x18, 0x18, 0x1C, // 82
    0xC0, 0xE0, 0x30, 0xF0, 0xF0, 0x70, 0xD0, 0xF0, 0xF0, 0xC0, 0xF3, 0x2E, 0x4D, 0x9A, 0xB7, 0x6E, 0x5A, 0x35, 0x87, 0xFB, 0x0C, 0x1C, 0x18, 0x08, 0x18, 0x18, 0x18, 0x1C, 0x0C, 0x0C, // 83
    0xF0, 0x70, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0x07, 0x0C, 0x8F, 0x7F, 0x3D, 0x15, 0xFF, 0xFF, 0x05, 0x0F, 0x00, 0x00, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x18, 0x00, // 84
    0x70, 0x70, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xD0, 0xF0, 0x00, 0x00, 0x7F, 0x8D, 0x7F, 0xFF, 0x80, 0x80, 0x7F, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x18, 0x18, 0x18, 0x1C, 0x0C, 0x04, 0x00, // 85
    0x30, 0x30, 0xF0, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0x00, 0x00, 0x3B, 0xCF, 0x74, 0x37, 0x0F, 0xE3, 0xFE, 0x7F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x04, 0x08, 0x18, 0x1C, 0x1C, 0x0C, 0x00, 0x00, 0x00, // 86
    0x30, 0xF0, 0x30, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0xF0, 0xE0, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0x00, 0x00, 0x07, 0x3B, 0xF4, 0x09, 0x87, 0xFF, 0xCC, 0x7F, 0x01, 0x07, 0xFC, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x18, 0x1C, 0x1C, 0x04, 0x08, 0x18, 0x18, 0x0C, 0x00, 0x00, // 87
    0x30, 0x30, 0x70, 0xF0, 0x70, 0xF0, 0xF0, 0x70, 0xF0, 0xB0, 0xD0, 0xF0, 0x00, 0x00, 0x80, 0x61, 0x1B, 0xED, 0xD7, 0x65, 0x1E, 0x67, 0xC1, 0x00, 0x00, 0x0C, 0x18, 0x18, 0x18, 0x1C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, // 88
    0x30, 0x30, 0xF0, 0xF0, 0xF0, 0x70, 0xF0, 0x70, 0xF0, 0xF0, 0xF0, 0xF0, 0x00, 0x00, 0x01, 0x82, 0x7F, 0x2F, 0x14, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x18, 0x10, 0x00, // 89
    0x00, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0x80, 0x61, 0x1B, 0x67, 0x1A, 0xE7, 0xFB, 0xBE, 0x77, 0xF1, 0x0C, 0x08, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, // 90
    0xF8, 0xF8, 0xF8, 0xF8, 0x68, 0x78, 0xFF, 0x7D, 0xFF, 0xFF, 0x00, 0x00, 0x1C, 0x30, 0x34, 0x34, 0x34, 0x38, // 91
    0x30, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x1E, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0C, // 92
    0x38, 0x78, 0x78, 0xF8, 0xF8, 0xF8, 0xF0, 0x00, 0x00, 0x00, 0xFF, 0x3D, 0xFF, 0xFF, 0x1C, 0x34, 0x34, 0x34, 0x30, 0x3C, 0x3C, // 93
    0x00, 0x00, 0x80, 0xE0, 0x60, 0xE0, 0x80, 0x00, 0x00, 0x08, 0x0E, 0x03, 0x00, 0x00, 0x01, 0x07, 0x0E, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 94
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, // 95
    0x06, 0x0B, 0x0E, 0x0E, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 96
    0x00, 0x00, 0x00, 0xC0, 0x40, 0xF0, 0xF0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x3C, 0x03, 0xE6, 0xE5, 0xEF, 0x77, 0x07, 0x3F, 0xF8, 0xC0, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, // 97
    0x30, 0x30, 0xF0, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0xD0, 0xA0, 0xC0, 0x00, 0x80, 0x80, 0x7F, 0x77, 0x0C, 0xFF, 0xFF, 0x77, 0x4F, 0xB5, 0xFF, 0xE7, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x0C, 0x04, // 98
    0x80, 0x40, 0xE0, 0xB0, 0xF0, 0xB0, 0x60, 0xF0, 0xF0, 0xF0, 0xC0, 0x7F, 0xBD, 0x03, 0x7F, 0xFF, 0x80, 0x77, 0x1F, 0x9F, 0xFF, 0xCF, 0x00, 0x04, 0x0C, 0x08, 0x18, 0x18, 0x18, 0x1C, 0x0C, 0x0C, 0x00, // 99
    0x30, 0x30, 0xF0, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0xD0, 0xA0, 0xC0, 0x80, 0x80, 0x82, 0x7F, 0x7F, 0x10, 0xFF, 0xFF, 0x60, 0x7F, 0x9F, 0xE0, 0xFF, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x0C, 0x0C, 0x04, // 100
    0x30, 0x30, 0xF0, 0xF0, 0x70, 0xF0, 0xF0, 0xB0, 0xF0, 0xF0, 0xC0, 0x80, 0x80, 0x7F, 0x7F, 0x14, 0xFF, 0xFF, 0x7F, 0x17, 0xF7, 0xC7, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x1C, // 101
    0x30, 0x30, 0xF0, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0x80, 0x80, 0x7F, 0x77, 0x0C, 0x7F, 0xFF, 0x1F, 0x1F, 0x07, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x00, 0x00, 0x00, // 102
    0x80, 0x40, 0xE0, 0xB0, 0xF0, 0xB0, 0xE0, 0xF0, 0xF0, 0xF0, 0xC0, 0x7F, 0xFD, 0x07, 0x7F, 0xFF, 0xB8, 0x6F, 0x0F, 0xEF, 0xEF, 0x7F, 0x00, 0x04, 0x0C, 0x08, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x1C, 0x00, // 103
    0x30, 0x30, 0xF0, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0x80, 0x80, 0x7F, 0x7F, 0x14, 0xFF, 0xFF, 0x7F, 0x6E, 0x16, 0xFF, 0xFF, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x18, 0x18, 0x18, 0x18, 0x1C, // 104
    0x70, 0x70, 0xF0, 0xF0, 0x30, 0xF0, 0xF0, 0xE0, 0x80, 0x80, 0x7F, 0x3F, 0x10, 0xFF, 0xFF, 0x00, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x18, // 105
    0x00, 0x00, 0x00, 0x00, 0x70, 0xB0, 0xF0, 0xF0, 0xF0, 0xF0, 0x70, 0x88, 0x08, 0x70, 0x60, 0x3F, 0x77, 0x9B, 0xFF, 0xFF, 0x00, 0x04, 0x0C, 0x08, 0x18, 0x18, 0x1C, 0x1C, 0x0C, 0x00, // 106
    0x30, 0x30, 0xF0, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0xF0, 0x70, 0xF0, 0xF0, 0xC0, 0x80, 0x80, 0x7F, 0x3F, 0x14, 0xFB, 0xED, 0xF3, 0x4E, 0x3F, 0x63, 0xC0, 0x00, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, // 107
    0x30, 0x30, 0xF0, 0xF0, 0x70, 0xF0, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x80, 0x82, 0x7F, 0x7F, 0x10, 0x7F, 0xFF, 0x80, 0x60, 0xE0, 0xC0, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x1C, // 108
    0x70, 0x50, 0xB0, 0xF0, 0x70, 0xF0, 0xE0, 0xA0, 0x70, 0xF0, 0xF0, 0xF0, 0xF0, 0xE0, 0x80, 0x80, 0x7F, 0x07, 0xFF, 0x8C, 0x77, 0x87, 0xFE, 0x7D, 0x1D, 0xFF, 0xFF, 0x00, 0x0C, 0x18, 0x18, 0x18, 0x1C, 0x1C, 0x18, 0x1C, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x1C, // 109
    0x70, 0x70, 0xF0, 0xF0, 0xF0, 0xF0, 0x70, 0xF0, 0xF0, 0xF0, 0xD0, 0xF0, 0x80, 0x80, 0x7F, 0x01, 0xFF, 0xF2, 0xBF, 0x0B, 0x07, 0xFF, 0xFF, 0x00, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x04, 0x18, 0x18, 0x1C, 0x1C, 0x00, // 110
    0x80, 0xC0, 0xE0, 0xF0, 0xF0, 0xF0, 0xD0, 0xA0, 0x40, 0xC0, 0x00, 0x7F, 0xFA, 0x07, 0x7F, 0xFF, 0x7F, 0x87, 0x7D, 0x86, 0xFF, 0xFF, 0x00, 0x04, 0x0C, 0x08, 0x18, 0x18, 0x18, 0x1C, 0x0C, 0x0C, 0x00, // 111
    0x70, 0x70, 0xF0, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0xE0, 0xA0, 0xC0, 0x80, 0x82, 0x7D, 0x7F, 0x04, 0xF7, 0xF7, 0x37, 0x35, 0x3B, 0x1F, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x18, 0x00, 0x00, 0x00, // 112
    0x00, 0xC0, 0xE0, 0xE0, 0xF0, 0xF0, 0xD0, 0xA0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x3F, 0xFE, 0x03, 0xEF, 0xEF, 0x5F, 0xC7, 0x3D, 0x06, 0xFF, 0x7E, 0xC0, 0x80, 0x00, 0x00, 0x0C, 0x0C, 0x18, 0x18, 0x18, 0x1C, 0x18, 0x18, 0x1C, 0x1C, 0x0C, // 113
    0x70, 0x70, 0xF0, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0x00, 0x00, 0x80, 0x80, 0x7F, 0x7F, 0x14, 0x7F, 0xFF, 0xFF, 0x1D, 0x73, 0x3F, 0x17, 0xE0, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x1C, 0x08, 0x08, 0x18, 0x18, 0x1C, // 114
    0xC0, 0xE0, 0x30, 0xF0, 0xF0, 0x70, 0xD0, 0xF0, 0xF0, 0xC0, 0xF3, 0x2E, 0x4D, 0x9A, 0xB7, 0x6E, 0x5A, 0x35, 0x87, 0xFB, 0x0C, 0x1C, 0x18, 0x08, 0x18, 0x18, 0x18, 0x1C, 0x0C, 0x0C, // 115
    0xF0, 0x70, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0x07, 0x0C, 0x8F, 0x7F, 0x3D, 0x15, 0xFF, 0xFF, 0x05, 0x0F, 0x00, 0x00, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x18, 0x00, // 116
    0x70, 0x70, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xD0, 0xF0, 0x00, 0x00, 0x7F, 0x8D, 0x7F, 0xFF, 0x80, 0x80, 0x7F, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x18, 0x18, 0x18, 0x1C, 0x0C, 0x04, 0x00, // 117
    0x30, 0x30, 0xF0, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0x00, 0x00, 0x3B, 0xCF, 0x74, 0x37, 0x0F, 0xE3, 0xFE, 0x7F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x04, 0x08, 0x18, 0x1C, 0x1C, 0x0C, 0x00, 0x00, 0x00, // 118
    0x30, 0xF0, 0x30, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0xF0, 0xE0, 0xF0, 0x30, 0xF0, 0xF0, 0xF0, 0x00, 0x00, 0x07, 0x3B, 0xF4, 0x09, 0x87, 0xFF, 0xCC, 0x7F, 0x01, 0x07, 0xFC, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x18, 0x1C, 0x1C, 0x04, 0x08, 0x18, 0x18, 0x0C, 0x00, 0x00, // 119
    0x30, 0x30, 0x70, 0xF0, 0x70, 0xF0, 0xF0, 0x70, 0xF0, 0xB0, 0xD0, 0xF0, 0x00, 0x00, 0x80, 0x61, 0x1B, 0xED, 0xD7, 0x65, 0x1E, 0x67, 0xC1, 0x00, 0x00, 0x0C, 0x18, 0x18, 0x18, 0x1C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, // 120
    0x30, 0x30, 0xF0, 0xF0, 0xF0, 0x70, 0xF0, 0x70, 0xF0, 0xF0, 0xF0, 0xF0, 0x00, 0x00, 0x01, 0x82, 0x7F, 0x2F, 0x14, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x18, 0x18, 0x18, 0x18, 0x1C, 0x18, 0x10, 0x00, // 121
    0x00, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0x80, 0x61, 0x1B, 0x67, 0x1A, 0xE7, 0xFB, 0xBE, 0x77, 0xF1, 0x0C, 0x08, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1C, // 122
    0x00, 0x00, 0xE0, 0xF0, 0x98, 0xF8, 0xF8, 0x60, 0x0C, 0x1C, 0xFF, 0x1B, 0x7F, 0xE7, 0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x10, 0x14, 0x38, 0x20, // 123
    0xFC, 0xFC, 0xFF, 0xFF, 0xFC, 0xFC, // 124
    0x38, 0xF8, 0xF0, 0xE0, 0xC0, 0x00, 0x00, 0xF3, 0x1F, 0xF4, 0xF7, 0x3C, 0x1C, 0x30, 0x30, 0x1C, 0x0C, 0x00, // 125
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x18, 0x08, 0x08, 0x18, 0x10, 0x10, 0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 126
    0xF8, 0x38, 0x68, 0x88, 0x08, 0x08, 0x88, 0x68, 0x38, 0xF8, 0xFF, 0xC0, 0x60, 0x19, 0x0F, 0x0F, 0x19, 0x60, 0xC0, 0xFF, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04 // 127
    
};

#endif