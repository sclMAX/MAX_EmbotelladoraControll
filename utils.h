#ifndef UTILS_H
#define UTILS_H

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
/*********************************/
/** Number to string conversion **/
/*********************************/

#define DIGIT(n) ('0' + (n))
#define DIGIMOD(n) DIGIT((n) % 10)
char conv[8];
// Convert signed int to rj string with 123 or -12 format
char *itostr3(const int &x) {
  int xx = x;
  if (xx < 0) {
    conv[0] = '-';
    xx = -xx;
  } else
    conv[0] = xx >= 100 ? DIGIMOD(xx / 100) : ' ';

  conv[1] = xx >= 10 ? DIGIMOD(xx / 10) : ' ';
  conv[2] = DIGIMOD(xx);
  conv[3] = '\0';
  return conv;
}

char *charToChar(const char &c) {
  conv[0] = c;
  conv[1] = '\0';
  return conv;
}

// Convert signed int to rj string with _123, -123, _-12, or __-1 format
char *itostr4sign(const int &x) {
  int xx = abs(x);
  int sign = 0;
  if (xx >= 100) {
    conv[1] = DIGIMOD(xx / 100);
    conv[2] = DIGIMOD(xx / 10);
  } else if (xx >= 10) {
    conv[0] = ' ';
    sign = 1;
    conv[2] = DIGIMOD(xx / 10);
  } else {
    conv[0] = ' ';
    conv[1] = ' ';
    sign = 2;
  }
  conv[sign] = x < 0 ? '-' : ' ';
  conv[3] = DIGIMOD(xx);
  conv[4] = '\0';
  return conv;
}

// Convert float to rj string with 123 or -12 format
char *ftostr3(const float &x) { return itostr3((int)x); }
// Convert float to rj string with _123, -123, _-12, or __-1 format
char *ftostr4sign(const float &x) { return itostr4sign((int)x); }

// Convert unsigned int to string with 12 format
char *itostr2(const uint8_t &x) {
  int xx = x;
  conv[0] = DIGIMOD(xx / 10);
  conv[1] = DIGIMOD(xx);
  conv[2] = '\0';
  return conv;
}

// Convert float to string with +123.4 / -123.4 format
char *ftostr41sign(const float &x) {
  int xx = int(abs(x * 10)) % 10000;
  conv[0] = x >= 0 ? '+' : '-';
  conv[1] = DIGIMOD(xx / 1000);
  conv[2] = DIGIMOD(xx / 100);
  conv[3] = DIGIMOD(xx / 10);
  conv[4] = '.';
  conv[5] = DIGIMOD(xx);
  conv[6] = '\0';
  return conv;
}
// Convert float to string with +123.4 / -123.4 format
char *ftostr21(const float &x) {
  long xx = abs(x * 100);
  conv[0] = DIGIMOD(xx / 1000);
  conv[1] = DIGIMOD(xx / 100);
  conv[2] = '.';
  conv[3] = DIGIMOD(xx / 10);
  conv[4] = '\0';
  return conv;
}

// Convert signed float to string with 023.45 / -23.45 format
char *ftostr32(const float &x) {
  long xx = abs(x * 100);
  conv[0] = x >= 0 ? DIGIMOD(xx / 10000) : '-';
  conv[1] = DIGIMOD(xx / 1000);
  conv[2] = DIGIMOD(xx / 100);
  conv[3] = '.';
  conv[4] = DIGIMOD(xx / 10);
  conv[5] = DIGIMOD(xx);
  conv[6] = '\0';
  return conv;
}

// Convert signed float to string (6 digit) with -1.234 / _0.000 / +1.234 format
char *ftostr43sign(const float &x, char plus /*=' '*/) {
  long xx = x * 1000;
  if (xx == 0)
    conv[0] = ' ';
  else if (xx > 0)
    conv[0] = plus;
  else {
    xx = -xx;
    conv[0] = '-';
  }
  conv[1] = DIGIMOD(xx / 1000);
  conv[2] = '.';
  conv[3] = DIGIMOD(xx / 100);
  conv[4] = DIGIMOD(xx / 10);
  conv[5] = DIGIMOD(xx);
  conv[6] = '\0';
  return conv;
}

// Convert unsigned float to string with 1.23 format
char *ftostr12ns(const float &x) {
  long xx = x * 100;
  xx = abs(xx);
  conv[0] = DIGIMOD(xx / 100);
  conv[1] = '.';
  conv[2] = DIGIMOD(xx / 10);
  conv[3] = DIGIMOD(xx);
  conv[4] = '\0';
  return conv;
}

// Convert signed int to lj string with +012 / -012 format
char *itostr3sign(const int &x) {
  int xx;
  if (x >= 0) {
    conv[0] = '+';
    xx = x;
  } else {
    conv[0] = '-';
    xx = -x;
  }
  conv[1] = DIGIMOD(xx / 100);
  conv[2] = DIGIMOD(xx / 10);
  conv[3] = DIGIMOD(xx);
  conv[4] = '.';
  conv[5] = '0';
  conv[6] = '\0';
  return conv;
}

// Convert unsigned int to lj string with 123 format
char *itostr3left(const int &xx) {
  if (xx >= 100) {
    conv[0] = DIGIMOD(xx / 100);
    conv[1] = DIGIMOD(xx / 10);
    conv[2] = DIGIMOD(xx);
    conv[3] = '\0';
  } else if (xx >= 10) {
    conv[0] = DIGIMOD(xx / 10);
    conv[1] = DIGIMOD(xx);
    conv[2] = '\0';
  } else {
    conv[0] = DIGIMOD(xx);
    conv[1] = '\0';
  }
  return conv;
}

// Convert unsigned float to rj string with 12345 format
char *ftostr5rj(const float &x) {
  long xx = abs(x);
  conv[0] = xx >= 10000 ? DIGIMOD(xx / 10000) : ' ';
  conv[1] = xx >= 1000 ? DIGIMOD(xx / 1000) : ' ';
  conv[2] = xx >= 100 ? DIGIMOD(xx / 100) : ' ';
  conv[3] = xx >= 10 ? DIGIMOD(xx / 10) : ' ';
  conv[4] = DIGIMOD(xx);
  conv[5] = '\0';
  return conv;
}

// Convert signed float to string with +1234.5 format
char *ftostr51sign(const float &x) {
  long xx = abs(x * 10);
  conv[0] = (x >= 0) ? '+' : '-';
  conv[1] = DIGIMOD(xx / 10000);
  conv[2] = DIGIMOD(xx / 1000);
  conv[3] = DIGIMOD(xx / 100);
  conv[4] = DIGIMOD(xx / 10);
  conv[5] = '.';
  conv[6] = DIGIMOD(xx);
  conv[7] = '\0';
  return conv;
}

// Convert signed float to string with +123.45 format
char *ftostr52sign(const float &x) {
  long xx = abs(x * 100);
  conv[0] = (x >= 0) ? '+' : '-';
  conv[1] = DIGIMOD(xx / 10000);
  conv[2] = DIGIMOD(xx / 1000);
  conv[3] = DIGIMOD(xx / 100);
  conv[4] = '.';
  conv[5] = DIGIMOD(xx / 10);
  conv[6] = DIGIMOD(xx);
  conv[7] = '\0';
  return conv;
}

// Convert signed float to space-padded string with -_23.4_ format
char *ftostr52sp(const float &x) {
  long xx = x * 100;
  uint8_t dig;
  if (xx < 0) { // negative val = -_0
    xx = -xx;
    conv[0] = '-';
    dig = (xx / 1000) % 10;
    conv[1] = dig ? DIGIT(dig) : ' ';
  } else { // positive val = __0
    dig = (xx / 10000) % 10;
    if (dig) {
      conv[0] = DIGIT(dig);
      conv[1] = DIGIMOD(xx / 1000);
    } else {
      conv[0] = ' ';
      dig = (xx / 1000) % 10;
      conv[1] = dig ? DIGIT(dig) : ' ';
    }
  }

  conv[2] = DIGIMOD(xx / 100); // lsd always

  dig = xx % 10;
  if (dig) { // 2 decimal places
    conv[5] = DIGIT(dig);
    conv[4] = DIGIMOD(xx / 10);
    conv[3] = '.';
  } else { // 1 or 0 decimal place
    dig = (xx / 10) % 10;
    if (dig) {
      conv[4] = DIGIT(dig);
      conv[3] = '.';
    } else {
      conv[3] = conv[4] = ' ';
    }
    conv[5] = ' ';
  }
  conv[6] = '\0';
  return conv;
}
#endif // UTILS_H