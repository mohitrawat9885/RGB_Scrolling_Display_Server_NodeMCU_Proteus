#include <SPI.h>
#include <SocketIoClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>

const char* ssid = "Network Name!";
const char* pass = "Network Password!";

SocketIoClient webSocket;

// port register maniuplation macros
// #define sbi(port, bit) (port) |= (1 << (bit))
// #define cbi(port, bit) (port) &= ~(1 << (bit))

// int latchPin = 8;   // Pin connected to ST_CP of 74HC595
// int clockPin = 13;  // Pin connected to SH_CP of 74HC595
// int dataPin = 11;   // Pin connected to DS of 74HC595

int latchPin = 15; // pin D8 on NodeMCU boards
int clockPin = 14; // pin D5 on NodeMCU boards
int dataPin = 13; // pin D7 on NodeMCU



byte dict[200][8] = {
  {
    B00000000,	//Space (Char 0x20)
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
  },//cambias el tamaño del espacio entre letras
 {
    B01000000,	//!
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B00000000,
    B01000000,
 },
 {
    B10100000,	//"
    B10100000,
    B10100000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
 },
 {
    B01010000,	//#
    B01010000,
    B11111000,
    B01010000,
    B11111000,
    B01010000,
    B01010000,
 },
 {
    B00100000,	//$
    B01111000,
    B10100000,
    B01110000,
    B00101000,
    B11110000,
    B00100000,
 },
 {
    B11000000,	//%
    B11001000,
    B00010000,
    B00100000,
    B01000000,
    B10011000,
    B00011000,
 },
 {
    B01100000,	//&
    B10010000,
    B10100000,
    B01000000,
    B10101000,
    B10010000,
    B01101000,
 },
 {
    B11000000,	//'
    B01000000,
    B10000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
 },
 {
    B00100000,	//(
    B01000000,
    B10000000,
    B10000000,
    B10000000,
    B01000000,
    B00100000,
 },
 {
    B10000000,	//)
    B01000000,
    B00100000,
    B00100000,
    B00100000,
    B01000000,
    B10000000,
 },
 {
    B00000000,	//*
    B00100000,
    B10101000,
    B01110000,
    B10101000,
    B00100000,
    B00000000,
 },
 {
    B00000000,	//+
    B00100000,
    B00100000,
    B11111000,
    B00100000,
    B00100000,
    B00000000,
 },
 {
    B00000000,	//,
    B00000000,
    B00000000,
    B00000000,
    B11000000,
    B01000000,
    B10000000,
 },
 {
    B00000000,	//-
    B00000000,
    B11111000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
 },
 {
    B00000000,	//.
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11000000,
    B11000000,
 },
    {
    B00000000,	///
    B00001000,
    B00010000,
    B00100000,
    B01000000,
    B10000000,
    B00000000,
},
 {
    B01110000,	//0
    B10001000,
    B10011000,
    B10101000,
    B11001000,
    B10001000,
    B01110000,
    },{
 
    B01000000,	//1
    B11000000,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B11100000,
    },{
 
    B01110000,	//2
    B10001000,
    B00001000,
    B00010000,
    B00100000,
    B01000000,
    B11111000,
},
  {
    B11111000,	//3
    B00010000,
    B00100000,
    B00010000,
    B00001000,
    B10001000,
    B01110000,
    },{
 
    B00010000,	//4
    B00110000,
    B01010000,
    B10010000,
    B11111000,
    B00010000,
    B00010000,
    },{
 
    B11111000,	//5
    B10000000,
    B11110000,
    B00001000,
    B00001000,
    B10001000,
    B01110000,
    },{
 
    B00110000,	//6
    B01000000,
    B10000000,
    B11110000,
    B10001000,
    B10001000,
    B01110000,
    },{
 
    B11111000,	//7
    B10001000,
    B00001000,
    B00010000,
    B00100000,
    B00100000,
    B00100000,
    },{
 
    B01110000,	//8
    B10001000,
    B10001000,
    B01110000,
    B10001000,
    B10001000,
    B01110000,
    },{
 
    B01110000,	//9
    B10001000,
    B10001000,
    B01111000,
    B00001000,
    B00010000,
    B01100000,
    },{
 
    B00000000,	//:
    B11000000,
    B11000000,
    B00000000,
    B11000000,
    B11000000,
    B00000000,
    },
 {
    B00000000,	//;
    B11000000,
    B11000000,
    B00000000,
    B11000000,
    B01000000,
    B10000000,
    },
  {
    B00010000,	//<
    B00100000,
    B01000000,
    B10000000,
    B01000000,
    B00100000,
    B00010000,
    },{
 
    B00000000,	//=
    B00000000,
    B11111000,
    B00000000,
    B11111000,
    B00000000,
    B00000000,
    },{
 
    B10000000,	//>
    B01000000,
    B00100000,
    B00010000,
    B00100000,
    B01000000,
    B10000000,
    },{
 
    B01110000,	//?
    B10001000,
    B00001000,
    B00010000,
    B00100000,
    B00000000,
    B00100000,
    },{
 
    B01110000,	//@
    B10001000,
    B00001000,
    B01101000,
    B10101000,
    B10101000,
    B01110000,
    },{
 
    B01110000,	//A
    B10001000,
    B10001000,
    B10001000,
    B11111000,
    B10001000,
    B10001000,
    },{
 
    B11110000,	//B
    B10001000,
    B10001000,
    B11110000,
    B10001000,
    B10001000,
    B11110000,
    },{
 
    B01110000,	//C
    B10001000,
    B10000000,
    B10000000,
    B10000000,
    B10001000,
    B01110000,
    },{
 
    B11100000,	//D
    B10010000,
    B10001000,
    B10001000,
    B10001000,
    B10010000,
    B11100000,
    },{
 
    B11111000,	//E
    B10000000,
    B10000000,
    B11110000,
    B10000000,
    B10000000,
    B11111000,
    },{
 
    B11111000,	//F
    B10000000,
    B10000000,
    B11110000,
    B10000000,
    B10000000,
    B10000000,
    },{
 
    B01110000,	//G
    B10001000,
    B10000000,
    B10111000,
    B10001000,
    B10001000,
    B01111000,
    },{
 
    B10001000,	//H
    B10001000,
    B10001000,
    B11111000,
    B10001000,
    B10001000,
    B10001000,
    },{
 
    B11100000,	//I
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B11100000,
    },{
 
    B00111000,	//J
    B00010000,
    B00010000,
    B00010000,
    B00010000,
    B10010000,
    B01100000,
    },{
 
    B10001000,	//K
    B10010000,
    B10100000,
    B11000000,
    B10100000,
    B10010000,
    B10001000,
    },{
 
    B10000000,	//L
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B11111000,
    },{
 
    B10001000,	//M
    B11011000,
    B10101000,
    B10101000,
    B10001000,
    B10001000,
    B10001000,
    },{
 
    B10001000,	//N
    B10001000,
    B11001000,
    B10101000,
    B10011000,
    B10001000,
    B10001000,
    },{
 
    B01110000,	//O
    B10001000,
    B10001000,
    B10001000,
    B10001000,
    B10001000,
    B01110000,
    },{
 
    B11110000,	//P
    B10001000,
    B10001000,
    B11110000,
    B10000000,
    B10000000,
    B10000000,
    },{
 
    B01110000,	//Q
    B10001000,
    B10001000,
    B10001000,
    B10101000,
    B10010000,
    B01101000,
    },{
 
    B11110000,	//R
    B10001000,
    B10001000,
    B11110000,
    B10100000,
    B10010000,
    B10001000,
    },{
 
    B01111000,	//S
    B10000000,
    B10000000,
    B01110000,
    B00001000,
    B00001000,
    B11110000,
    },{
 
    B11111000,	//T
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    },{
 
    B10001000,	//U
    B10001000,
    B10001000,
    B10001000,
    B10001000,
    B10001000,

    B01110000,
    },{
 
    B10001000,	//V
    B10001000,
    B10001000,
    B10001000,
    B10001000,
    B01010000,
    B00100000,
    },{
 
    B10001000,	//W
    B10001000,
    B10001000,
    B10101000,
    B10101000,
    B10101000,
    B01010000,
    },{
 
    B10001000,	//X
    B10001000,
    B01010000,
    B00100000,
    B01010000,
    B10001000,
    B10001000,
    },{
 
    B10001000,	//Y
    B10001000,
    B10001000,
    B01010000,
    B00100000,
    B00100000,
    B00100000,
    },{
 
    B11111000,	//Z
    B00001000,
    B00010000,
    B00100000,
    B01000000,
    B10000000,
    B11111000,
    },{
 
    B11100000,	//[
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B11100000,
    },{
 
    B00000000,	//(Backward Slash)
    B10000000,
    B01000000,
    B00100000,
    B00010000,
    B00001000,
    B00000000,
    },{
 
    B11100000,	//]
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    B11100000,
    },{
 
    B00100000,	//^
    B01010000,
    B10001000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    },{
 
    B00000000,	//_
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11111000,
    },{
 
    B10000000,	//`
    B01000000,
    B00100000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    },{
 
    B00000000,	//a
    B00000000,
    B01110000,
    B00001000,
    B01111000,
    B10001000,
    B01111000,
    },{
 
    B10000000,	//b
    B10000000,
    B10110000,
    B11001000,
    B10001000,
    B10001000,
    B11110000,
    },{
 
    B00000000,	//c
    B00000000,
    B01110000,
    B10001000,
    B10000000,
    B10001000,
    B01110000,
    },{
 
    B00001000,	//d
    B00001000,
    B01101000,
    B10011000,
    B10001000,
    B10001000,
    B01111000,
    },{
 
    B00000000,	//e
    B00000000,
    B01110000,
    B10001000,
    B11111000,
    B10000000,
    B01110000,
    },{
 
    B00110000,	//f
    B01001000,
    B01000000,
    B11100000,
    B01000000,
    B01000000,
    B01000000,
    },{
 
    B00000000,	//g
    B01111000,
    B10001000,
    B10001000,
    B01111000,
    B00001000,
    B01110000,
    },{
 
    B10000000,	//h
    B10000000,
    B10110000,
    B11001000,
    B10001000,
    B10001000,
    B10001000,
    },{
 
    B01000000,	//i
    B00000000,
    B11000000,
    B01000000,
    B01000000,
    B01000000,
    B11100000,
    },{
 
    B00010000,	//j
    B00000000,
    B00110000,
    B00010000,
    B00010000,
    B10010000,
    B01100000,
    },{
 
    B10000000,	//k
    B10000000,
    B10010000,
    B10100000,
    B11000000,
    B10100000,
    B10010000,
    },{
 
    B11000000,	//l
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B11100000,
    },{
 
    B00000000,	//m
    B00000000,
    B11010000,
    B10101000,
    B10101000,
    B10001000,
    B10001000,
    },{
 
    B00000000,	//n
    B00000000,
    B10110000,
    B11001000,
    B10001000,
    B10001000,
    B10001000,
    },{
 
    B00000000,	//o
    B00000000,
    B01110000,
    B10001000,
    B10001000,
    B10001000,
    B01110000,
    },{
 
    B00000000,	//p
    B00000000,
    B11110000,
    B10001000,
    B11110000,
    B10000000,
    B10000000,
    },{
 
    B00000000,	//q
    B00000000,
    B01101000,
    B10011000,
    B01111000,
    B00001000,
    B00001000,
    },{
 
    B00000000,	//r
    B00000000,
    B10110000,
    B11001000,
    B10000000,
    B10000000,
    B10000000,
    },{
 
    B00000000,	//s
    B00000000,
    B01110000,
    B10000000,
    B01110000,
    B00001000,
    B11110000,
    },{
 
    B01000000,	//t
    B01000000,
    B11100000,
    B01000000,
    B01000000,
    B01001000,
    B00110000,
    },{
 
    B00000000,	//u
    B00000000,
    B10001000,
    B10001000,
    B10001000,
    B10011000,
    B01101000,
    },{
 
    B00000000,	//v
    B00000000,
    B10001000,
    B10001000,
    B10001000,
    B01010000,
    B00100000,
    },{
 
    B00000000,	//w
    B00000000,
    B10001000,
    B10101000,
    B10101000,
    B10101000,
    B01010000,
    },{
 
    B00000000,	//x
    B00000000,
    B10001000,
    B01010000,
    B00100000,
    B01010000,
    B10001000,
    },{
 
    B00000000,	//y
    B00000000,
    B10001000,
    B10001000,
    B01111000,
    B00001000,
    B01110000,
    },{
 
    B00000000,	//z
    B00000000,
    B11111000,
    B00010000,
    B00100000,
    B01000000,
    B11111000,
    },{
 
    B00100000,	//{
    B01000000,
    B01000000,
    B10000000,
    B01000000,
    B01000000,
    B00100000,
    },{
 
    B10000000,	//|
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    B10000000,
    },{
 
    B10000000,	//}
    B01000000,
    B01000000,
    B00100000,
    B01000000,
    B01000000,
    B10000000,
    },{
 
    B00000000,	//~
    B00000000,
    B00000000,
    B01101000,
    B10010000,
    B00000000,
    B00000000,
    },
    {B00011100,
      B00101010,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000000
},
{
  B00101010,
B00011100,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000
},
{
  B00001000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
  },
{B00000000,
B00000000,
B00000000,
B00000000,
B00000001,
B00000000,
B00000001,
B00000000},

{
  B00110000, //ऄ	
B00001100,
B11111111,
B00110100,
B00001100,
B10111100,
B01001100,
B00110100},

{B00000000, //अ
B00000000,
B11111111,
B00110100,
B00001100,
B10111100,
B01001100,
B00110100},

{B00000000,  // आ	
B00000000,
B11111111,
B00110101,
B00001101,
B10111101,
B01001101,
B00110101},

{B00000000, // इ	
B00000000,
B11111111,
B00111000,
B00100000,
B00111100,
B00000100,
B00111100},

{B00010000, //ई
B00001000,
B11111111,
B00111000,
B00100000,
B00111100,
B00000100,
B00111100},

{B00000000, // उ
B00000000,
B11111111,
B00010000,
B00001000,
B01011000,
B01000100,
B00111000},


{B00000000, // ऊ	
B00000000,
B11111111,
B00010000,
B00001011,
B01011101,
B01000100,
B00111000},

{B00000000, // ऋ	
B00000000,
B11111111,
B01101000,
B00011110,
B00011001,
B00101010,
B01001000},

{B00000000, // ऌ
B00000000,
B11111111,
B00101000,
B01011110,
B01000010,
B00100100,
B00010010},

{B00100010, // ऍ	
B00011100,
B11111111,
B00100100,
B00100100,
B00100100,
B00011000,
B00000100},

{B00110000, // ऎ	
B00001100,
B11111111,
B00100100,
B00100100,
B00100100,
B00011000,
B00000100},

{B00000000, // ए	
B00000000,
B11111111,
B00100100,
B00100100,
B00100100,
B00011000,
B00000100},

{B00111000, // ऐ
B00000100,
B11111111,
B00100100,
B00100100,
B00100100,
B00011000,
B00000100},

{B00010001, // ऑ
B00001110,
B11111111,
B00110101,
B01010101,
B10011101,
B01001101,
B00110101},

{B00010000, // ऒ	
B00001110,
B11111111,
B00110101,
B01010101,
B10011101,
B01001101,
B00110101},

{B00011100, // ओ
B00000010,
B11111111,
B00110101,
B01010101,
B10011101,
B01001101,
B00110101},

{B00011100, // औ	
B00011110,
B11111111,
B00110101,
B01010101,
B10011101,
B01001101,
B00110101},

{B00000000, // क
B00000000,
B11111111,
B01111000,
B01001110,
B01011010,
B00101010,
B00001000},

{B00000000, // ख
B00000000,
B11111111,
B00100100,
B00111100,
B01011100,
B00100100,
B00011100},

{B00000000, // ग	
B00000000,
B11111111,
B00010100,
B00110100,
B01110100,
B00110100,
B00000100},

{B00000000, // घ	
B00000000,
B11111111,
B01000100,
B01110100,
B00100100,
B00100100,
B00011100},

{B00000000, // ङ
B00000000,
B11111111,
B00001010,
B00111000,
B00111110,
B01000010,
B00111110},


{B00000000, // च	
B00000000,
B11111111,
B00000100,
B01110100,
B00100100,
B00101100,
B00010100},

{B00000000, // छ
B00000000,
B11111111,
B00101100,
B01001010,
B01110110,
B00100010,
B00111100},

{B00000000, // ज	
B00000000,
B11111111,
B00000100,
B00011100,
B01010100,
B01001100,
B00110100},

{B00000000, // झ	
B00000000,
B11111111,
B00110100,
B01000100,
B01111100,
B00010100,
B01110100},

{B00000000, // ञ
B00000000,
B11111111,
B00000100,
B01110100,
B00001100,
B01110100,
B00000100},

{B00000000, // ट	
B00000000,
B11111111,
B00001000,
B00111000,
B01000000,
B01000000,
B00111000},

{B00000000, // ठ
B00000000,
B11111111,
B00001000,
B00111100,
B01000010,
B01000010,
B00111100},

{B00000000, // ड
B00000000,
B11111111,
B00001000,
B00111000,
B00111100,
B01000100,
B00111100},

{B00000000, // ढ
B00000000,
B11111111,
B00001000,
B00111000,
B01000000,
B01011100,
B00111000},

{B00000000, // ण
B00000000,
B11111111,
B01010100,
B01010100,
B01010100,
B01110100,
B00100100},

{B00000000, // त
B00000000,
B11111111,
B00000100,
B00111100,
B01000100,
B00100100,
B00010100},

{B00000000, // थ
B00000000,
B11111111,
B01100100,
B01110100,
B00010100,
B00100100,
B00011100},

{B00000000, // द	
B00000000,
B11111111,
B00001000,
B00111000,
B01000000,
B01001100,
B00111010},

{B00000000, // ध	
B00000000,
B11111111,
B01100100,
B01000100,
B00110100,
B01001100,
B00110100},

{B00000000, // न 
B00000000,
B11111111,
B00000100,
B01111100,
B01100100,
B00000100,
B00000100},
 
{B00000000, // ऩ
B00000000,
B11111111,
B00000100,
B01111100,
B01100100,
B00000100,
B00010100},

{B00000000, // प	 
B00000000,
B11111111,
B00100100,
B00100100,
B00100100,
B00011100,
B00000100},

{B00000000, // फ
B00000000,
B11111111,
B01001000,
B01001110,
B00111010,
B00001010,
B00001000},

{B00000000,  // ब	
B00000000,
B11111111,
B00111000,
B01101000,
B01011000,
B00111000,
B00001000},

{B00000000, // भ	
B00000000,
B01110111,
B01110100,
B00010100,
B00111100,
B00010100,
B00000100},

{B00000000, // म
B00000000,
B11111111,
B00100100,
B00100100,
B01111100,
B01100100,
B00000100},

{B00000000, // य	
B00000000,
B11111111,
B00100100,
B00010100,
B01010100,
B01111100,
B00110100},

{B00000000, // र	
B00000000,
B11111111,
B00110000,
B00001000,
B00111000,
B00010000,
B00001000},

{B00000000, // ऱ
B00000000,
B11111111,
B00110000,
B00001000,
B00111000,
B00010000,
B01001000},


{B00000000, // ल	
B00000000,
B11111111,
B00100100,
B01011100,
B01010100,
B01000100,
B00100100},

{B00000000, //  ळ	
B00000000,
B11111111,
B00000100,
B01110110,
B01001010,
B00110110,
B00000000},

{B00000000, // ऴ
B00000000,
B11111111,
B00000100,
B01110110,
B01001010,
B00110110,
B00001000},

{B00000000, // व	
B00000000,
B11111111,
B00011100,
B00100100,
B00100100,
B00111100,
B00000100},

{B00000000, // श	
B00000000,
B11111111,
B01100100,
B01110100,
B00010100,
B00100100,
B00010100},

{B00000000, // ष
B00000000,
B11111111,
B01100100,
B01010100,
B01001100,
B00111100,
B00000100},

{B00000000, // स	
B00000000,
B11111111,
B01000100,
B00100100,
B01111100,
B01000100,
B00110100},

{B00000000,  // ह
B00000000,
B11111111,
B00001000,
B00111000,
B00111100,
B00100010,
B00011000},

{B00001000, // ऺ	
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000},

{B00000001, // ऻ	
B00000000,
B00000001,
B00000001,
B00000001,
B00000001,
B00000001,
B00000001},

{B00000000, // ़	
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00001000},

{B00000000, // ऽ	
B01111100,
B01000000,
B00111000,
B00000100,
B00000010,
B00100010,
B00011100},

{B00000000, // ा	
B00000000,
B00000001,
B00000001,
B00000001,
B00000001,
B00000001,
B00000001},

{B01110000, // ि	
B10001000,
B10000000,
B10000000,
B10000000,
B10000000,
B10000000,
B10000000},

{B00000010, // ी	
B00000101,
B00001001,
B00000001,
B00000001,
B00000001,
B00000001,
B00000001},

{B00000000, // ु
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00001100,
B00111100},

{B00000000, // ू
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00110000,
B00101110},

{B00000000, // ृ
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00110000,
B00100000},

{B00000000, // ॄ	
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00110000,
B00110000},

{B00100010, // ॅ
B00011100,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000},

{B01000000, // ॆ
B00111000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000},

{B01110000, // े
B00001000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000},

{B01110000, // ै
B01111000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000},


{B00001001, // ॉ	
B00000110,
B00000001,
B00000001,
B00000001,
B00000001,
B00000001,
B00000001},

{B00010000, // ॊ	
B00001110,
B00000001,
B00000001,
B00000001,
B00000001,
B00000001,
B00000001},

{B00011100, // ो
B00000010,
B00000001,
B00000001,
B00000001,
B00000001,
B00000001,
B00000001},

{B00011100, // ौ	
B00011110,
B00000001,
B00000001,
B00000001,
B00000001,
B00000001,
B00000001},

{B00000000, // ्	
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00010000,
B00001000},

{B00000000, // ॎ
B00000000,
B10000000,
B10000000,
B10000000,
B10000000,
B10000000,
B10000000},

{B00010110, // ॏ	
B00001110,
B00000001,
B00000001,
B00000001,
B00000001,
B00000001,
B00000001},

{B00010101, // ॐ	
B00001110,
B00011100,
B00000101,
B01001111,
B01000111,
B00100100,
B00011000}
};

int maxColm = 0;
int num_of_Panels = 4;  // Number of rgb matrix 8x8

byte text[8][600] = {{}};

int colmColor[75][3] = {{100, 100, 100}};

// counter to hold the 'frame number' used to drive PWM
int pwmc = 1;

// counter for column moves
long colm = 1;
int scrollSpeed = 100;

// mapping from columns to array entries
int col1 = -(num_of_Panels * 8) + 0, 
    col2 = -(num_of_Panels * 8) + 1,
    col3 = -(num_of_Panels * 8) + 2,
    col4 = -(num_of_Panels * 8) + 3,
    col5 = -(num_of_Panels * 8) + 4,
    col6 = -(num_of_Panels * 8) + 5,
    col7 = -(num_of_Panels * 8) + 6,
    col8 = -(num_of_Panels * 8) + 7;

void setup() {
  // setup the pins
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  connectWiFi();
  webSocket.on("message", controlled);
  webSocket.emit("client", "\"Hello from RGB Display.\"");
  webSocket.begin("192.168.43.14", 5000);

  // setup SPI
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  // SPI.setBitOrder(LSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.begin();
  Serial.begin(74880);  
  // set pwmc
  pwmc = 1;
}

void connectWiFi(){
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  Serial.print("");
  Serial.println("WiFi connected");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());
}

int buildColorText(int colmNum, int color, int numberToDisplay){

    int t =      ((col1 + colmNum <= maxColm && text[numberToDisplay][col1 + colmNum] == 1 && colmColor[(col1 + colmNum)/8][color] >= pwmc) ? B10000000 : B00000000) |
                 ((col1 + colmNum <= maxColm && text[numberToDisplay][col2 + colmNum] == 1 && colmColor[(col2 + colmNum)/8][color] >= pwmc) ? B01000000 : B00000000) |
                 ((col1 + colmNum <= maxColm && text[numberToDisplay][col3 + colmNum] == 1 && colmColor[(col3 + colmNum)/8][color] >= pwmc) ? B00100000 : B00000000) |
                 ((col1 + colmNum <= maxColm && text[numberToDisplay][col4 + colmNum] == 1 && colmColor[(col4 + colmNum)/8][color] >= pwmc) ? B00010000 : B00000000) |
                 ((col1 + colmNum <= maxColm && text[numberToDisplay][col5 + colmNum] == 1 && colmColor[(col5 + colmNum)/8][color] >= pwmc) ? B00001000 : B00000000) |
                 ((col1 + colmNum <= maxColm && text[numberToDisplay][col6 + colmNum] == 1 && colmColor[(col6 + colmNum)/8][color] >= pwmc) ? B00000100 : B00000000) |
                 ((col1 + colmNum <= maxColm && text[numberToDisplay][col7 + colmNum] == 1 && colmColor[(col7 + colmNum)/8][color] >= pwmc) ? B00000010 : B00000000) |
                 ((col1 + colmNum <= maxColm && text[numberToDisplay][col8 + colmNum] == 1 && colmColor[(col8 + colmNum)/8][color] >= pwmc) ? B00000001 : B00000000);
    return t;
}

void print(){
  // reset pwm counter if too high
  if (pwmc > 100) {
    pwmc = 1;
  }
    if (colm == scrollSpeed) {
    col1 = col1 == maxColm ?  -(num_of_Panels * 8) : col1 + 1;
    col2 = col2 == maxColm ?  -(num_of_Panels * 8) : col2 + 1;
    col3 = col3 == maxColm ?  -(num_of_Panels * 8) : col3 + 1;
    col4 = col4 == maxColm ?  -(num_of_Panels * 8) : col4 + 1;
    col5 = col5 == maxColm ?  -(num_of_Panels * 8) : col5 + 1;
    col6 = col6 == maxColm ?  -(num_of_Panels * 8) : col6 + 1;
    col7 = col7 == maxColm ?  -(num_of_Panels * 8) : col7 + 1;
    col8 = col8 == maxColm ?  -(num_of_Panels * 8) : col8 + 1;
    colm = 1;
  }

  int row = 1;
  for (int numberToDisplay = 0; numberToDisplay < 8; numberToDisplay++) {
    // cbi(PORTB, 0);
    digitalWrite(latchPin, LOW);

    for(int i=0;i<=2;i++){
        // 0 is Red, 1 is Green, 2 is Blue
        for(int j=0;j<num_of_Panels;j++){
            int colorMatrix  = buildColorText(8*j, i, numberToDisplay);
            SPI.transfer(~colorMatrix);
    }
    }
    SPI.transfer(row);
    row = row << 1 ;
    digitalWrite(latchPin, HIGH);
    // sbi(PORTB, 0);
  }
  pwmc++;
  if(scrollSpeed != 0) colm++;
}

void resetColoms(){
    col1 = -(num_of_Panels * 8) + 0, 
    col2 = -(num_of_Panels * 8) + 1,
    col3 = -(num_of_Panels * 8) + 2,
    col4 = -(num_of_Panels * 8) + 3,
    col5 = -(num_of_Panels * 8) + 4,
    col6 = -(num_of_Panels * 8) + 5,
    col7 = -(num_of_Panels * 8) + 6,
    col8 = -(num_of_Panels * 8) + 7;
}

void loadText(int *textIndexes, int l){
  // int l = msg.length();
  memset(text, 0, sizeof(text));
  int final_l = l;
  colm = 1;
  resetColoms();
  maxColm = l * 8;
  int count = 0;
  for(int i=0;i<8;i++){
    int c = 0;
    for(int j=0;j<l;j++){
      if(textIndexes[j] >= 153 && textIndexes[j] <= 174){
        count++;
        continue;
      }
      for(int k=0;k<8;k++){
        byte d;
        if( j < (l-1) && textIndexes[j+1] >= 153 && textIndexes[j+1] <= 174){ 
            d = dict[textIndexes[j]][i] | dict[textIndexes[j+1]][i];
        }
        else {
          d = dict[textIndexes[j]][i];
        }
            byte mask = 1;
            d = d >> (7-k);
            mask = mask & d;
            text[i][c++] = mask;
      }
      // text[i][c++] = 0;
    }
  }
    final_l -= (count / 8);
    maxColm = final_l * 8;
    maxColm -= 1;
    Serial.println(maxColm);
}

void loadTextColor(int pos, int r, int g, int b){
    colmColor[pos][0] = r;
    colmColor[pos][1] = g;
    colmColor[pos][2] = b;
}

void controlled(const char* message, size_t length){
  DynamicJsonDocument doc(6144);
  deserializeJson(doc, message);
  int sp = doc["speed"];
  scrollSpeed = sp;
  Serial.print("Speed:- ");
  Serial.println(scrollSpeed);

  String newText = doc["text"];
  int s = newText.length();
  Serial.print("Length:- ");
  Serial.println(s);

  byte utf8Bytes[newText.length()+1];
  newText.getBytes(utf8Bytes, newText.length()+1);

  int newTextIndexes[s];
  int textIndex = 0;
 for (int i = 0; i < newText.length(); i++) {
    if(utf8Bytes[i] != 224){
        newTextIndexes[textIndex++] = utf8Bytes[i] - 32;
    }
    else{
      if(utf8Bytes[i+1] == 165){
          newTextIndexes[textIndex++] = utf8Bytes[i+2] + 31;        
      }
      else{
        newTextIndexes[textIndex++] = utf8Bytes[i+2] - 33;
      }
      i+= 2;
      s -= 2;
    }
  }

int colorIndex = 0;
  for(int i=0;i<s;i++){
       if(!(newTextIndexes[i] >= 153 && newTextIndexes[i] <= 174)){
          int r = doc["colors"][i][0];
          int g = doc["colors"][i][1];
          int b = doc["colors"][i][2];
          loadTextColor(colorIndex++, r, g, b);
    }
  }
  loadText(newTextIndexes, s);
  webSocket.emit("client", "\"Data received.\"");
}

void initialize(){
  loadTextColor(0, 100, 0, 0);
  loadTextColor(1, 0, 100, 0);
  loadTextColor(2, 0, 0, 100);
  loadTextColor(3, 100, 100, 0);
  loadTextColor(4, 0, 100, 0);
  loadTextColor(5, 0, 0, 100);
  loadTextColor(6, 100, 100, 0);
  loadTextColor(7, 0, 100, 0);
  loadTextColor(8, 0, 0, 100);
  loadTextColor(9, 100, 0, 100);
  loadTextColor(10, 0, 100, 100);

  String t = "RGBDisplay";
  int tIndex[t.length()];
  Serial.print("Text Indexes:- ");
  for(int i=0; i<t.length();i++){
    tIndex[i] = t[i] - 32;
  }
  loadText(tIndex, t.length());
}
void loop() {
    initialize();
    while(true){
      yield();
      print();
      // if(col8 < maxColm) continue;
      webSocket.loop();
  }
}

