#include "text.hpp"
#include <fstream>
#include <stdio.h>
#include <tyra>

std::string ADVICE_CLICK_SEED_PACKET;
std::string NEW_PLANT;

enum FileEnconding{
  UTF8,
  UTF16BE,
  UTF16LE,
  ANSI
};

FileEnconding CheckFileEncoding(const char* text){
  if(text[0] == 0xFF && text[1] == 0xFE){
    return UTF16LE; // Little Endian
  } else if(text[0] == 0xFE && text[1] == 0xFF){
    return UTF16BE; // Big Endian
  } else if(text[0] == 0xEF && text[1] == 0xBB && text[2] == 0xBF){
    return UTF8;
  }
  return ANSI; 
}

void ReadTextFile(){
  const char* filename = "PROPERTIES/LawnStrings.txt";
  FILE* file = fopen(filename, "r");

  char text [512];
  
  TYRA_ASSERT(file != NULL, "The next file could not be found:", file);
  fgets (text , 512 , file);
  
  rewind(file);

  FileEnconding fEncoding = CheckFileEncoding(text);

  if(fEncoding == ANSI){
    while (fgets (text , 512 , file) != NULL)
    {
      if(text[0] == '['){
        if(strstr(text,"[ADVICE_CLICK_SEED_PACKET]")){
          fgets (text , 512 , file);
          int i=0;
          char utf8[2]; 
          while(text[i] !='\r'){
            if((unsigned char)text[i]>0x7F){
              // 0x3f = 0011-1111
              // byte[0] = 110x-xxyy
              // byte[1] = 10yy-zzzz
              utf8[0] = 0xC0 | (((unsigned char) text[i] >> 6)); 
              utf8[1] = 0x80 | ((unsigned char) text[i] & 0x3f);
              
              ADVICE_CLICK_SEED_PACKET += utf8[0];
              ADVICE_CLICK_SEED_PACKET += utf8[1];
            }else{
              ADVICE_CLICK_SEED_PACKET += text[i];
            }
            i++;
          }
        } else if(strstr(text,"[NEW_PLANT]")){
          fgets (text , 512 , file);
          int i=0;
          char utf8[2]; 
          while(text[i] !='\r'){
            if((unsigned char)text[i]>0x7F){
              // 0x3f = 0011-1111
              // byte[0] = 110x-xxyy
              // byte[1] = 10yy-zzzz
              utf8[0] = 0xC0 | (((unsigned char) text[i] >> 6)); 
              utf8[1] = 0x80 | ((unsigned char) text[i] & 0x3f);
              
              NEW_PLANT += utf8[0];
              NEW_PLANT += utf8[1];
            }else{
              NEW_PLANT += text[i];
            }
            i++;
          }
        }
      }
    }
  }else if(fEncoding == UTF8){
    while (fgets (text , 512 , file) != NULL)
    {
      if(text[0] == '['){
          if(strstr(text,"[ADVICE_CLICK_SEED_PACKET]")){
              fgets (text , 512 , file);
              ADVICE_CLICK_SEED_PACKET = text;
          }else if(strstr(text,"[NEW_PLANT]")){
              fgets (text , 512 , file);
              NEW_PLANT = text;
          }
      }
    }
  }else{
    TYRA_TRAP("FILE IS NOT SUPPORTED");
  }

  fclose (file);
}