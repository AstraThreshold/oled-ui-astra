/**
 * https://github.com/larryli/u8g2_wqy
 */
#ifndef _U8G2_WQY_H
#define _U8G2_WQY_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef U8G2_USE_LARGE_FONTS
#define U8G2_USE_LARGE_FONTS
#endif

#ifndef U8X8_FONT_SECTION

#ifdef __GNUC__
#  define U8X8_SECTION(name) __attribute__ ((section (name)))
#else
#  define U8X8_SECTION(name)
#endif

#if defined(__GNUC__) && defined(__AVR__)
#  define U8X8_FONT_SECTION(name) U8X8_SECTION(".progmem." name)
#endif

#if defined(ESP8266)
#  define U8X8_FONT_SECTION(name) __attribute__((section(".text." name)))
#endif

#ifndef U8X8_FONT_SECTION
#  define U8X8_FONT_SECTION(name) 
#endif

#endif

#ifndef U8G2_FONT_SECTION
#define U8G2_FONT_SECTION(name) U8X8_FONT_SECTION(name) 
#endif

extern const uint8_t u8g2_font_wqy12_t_chinese1[] U8G2_FONT_SECTION("u8g2_font_wqy12_t_chinese1");
extern const uint8_t u8g2_font_wqy12_t_chinese2[] U8G2_FONT_SECTION("u8g2_font_wqy12_t_chinese2");
extern const uint8_t u8g2_font_wqy12_t_chinese3[] U8G2_FONT_SECTION("u8g2_font_wqy12_t_chinese3");
extern const uint8_t u8g2_font_wqy12_t_gb2312[] U8G2_FONT_SECTION("u8g2_font_wqy12_t_gb2312");
extern const uint8_t u8g2_font_wqy12_t_gb2312a[] U8G2_FONT_SECTION("u8g2_font_wqy12_t_gb2312a");
extern const uint8_t u8g2_font_wqy12_t_gb2312b[] U8G2_FONT_SECTION("u8g2_font_wqy12_t_gb2312b");
extern const uint8_t u8g2_font_wqy13_t_chinese1[] U8G2_FONT_SECTION("u8g2_font_wqy13_t_chinese1");
extern const uint8_t u8g2_font_wqy13_t_chinese2[] U8G2_FONT_SECTION("u8g2_font_wqy13_t_chinese2");
extern const uint8_t u8g2_font_wqy13_t_chinese3[] U8G2_FONT_SECTION("u8g2_font_wqy13_t_chinese3");
extern const uint8_t u8g2_font_wqy13_t_gb2312[] U8G2_FONT_SECTION("u8g2_font_wqy13_t_gb2312");
extern const uint8_t u8g2_font_wqy13_t_gb2312a[] U8G2_FONT_SECTION("u8g2_font_wqy13_t_gb2312a");
extern const uint8_t u8g2_font_wqy13_t_gb2312b[] U8G2_FONT_SECTION("u8g2_font_wqy13_t_gb2312b");
extern const uint8_t u8g2_font_wqy14_t_chinese1[] U8G2_FONT_SECTION("u8g2_font_wqy14_t_chinese1");
extern const uint8_t u8g2_font_wqy14_t_chinese2[] U8G2_FONT_SECTION("u8g2_font_wqy14_t_chinese2");
extern const uint8_t u8g2_font_wqy14_t_chinese3[] U8G2_FONT_SECTION("u8g2_font_wqy14_t_chinese3");
extern const uint8_t u8g2_font_wqy14_t_gb2312[] U8G2_FONT_SECTION("u8g2_font_wqy14_t_gb2312");
extern const uint8_t u8g2_font_wqy14_t_gb2312a[] U8G2_FONT_SECTION("u8g2_font_wqy14_t_gb2312a");
extern const uint8_t u8g2_font_wqy14_t_gb2312b[] U8G2_FONT_SECTION("u8g2_font_wqy14_t_gb2312b");
extern const uint8_t u8g2_font_wqy15_t_chinese1[] U8G2_FONT_SECTION("u8g2_font_wqy15_t_chinese1");
extern const uint8_t u8g2_font_wqy15_t_chinese2[] U8G2_FONT_SECTION("u8g2_font_wqy15_t_chinese2");
extern const uint8_t u8g2_font_wqy15_t_chinese3[] U8G2_FONT_SECTION("u8g2_font_wqy15_t_chinese3");
extern const uint8_t u8g2_font_wqy15_t_gb2312[] U8G2_FONT_SECTION("u8g2_font_wqy15_t_gb2312");
extern const uint8_t u8g2_font_wqy15_t_gb2312a[] U8G2_FONT_SECTION("u8g2_font_wqy15_t_gb2312a");
extern const uint8_t u8g2_font_wqy15_t_gb2312b[] U8G2_FONT_SECTION("u8g2_font_wqy15_t_gb2312b");
extern const uint8_t u8g2_font_wqy16_t_chinese1[] U8G2_FONT_SECTION("u8g2_font_wqy16_t_chinese1");
extern const uint8_t u8g2_font_wqy16_t_chinese2[] U8G2_FONT_SECTION("u8g2_font_wqy16_t_chinese2");
extern const uint8_t u8g2_font_wqy16_t_chinese3[] U8G2_FONT_SECTION("u8g2_font_wqy16_t_chinese3");
extern const uint8_t u8g2_font_wqy16_t_gb2312[] U8G2_FONT_SECTION("u8g2_font_wqy16_t_gb2312");
extern const uint8_t u8g2_font_wqy16_t_gb2312a[] U8G2_FONT_SECTION("u8g2_font_wqy16_t_gb2312a");
extern const uint8_t u8g2_font_wqy16_t_gb2312b[] U8G2_FONT_SECTION("u8g2_font_wqy16_t_gb2312b");

#ifdef __cplusplus
}
#endif

#endif
