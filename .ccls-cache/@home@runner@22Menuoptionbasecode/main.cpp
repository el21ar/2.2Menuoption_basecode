#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <fstream>

const float h = 6.626e-34;
const int c = 3e8;
const float e = 1.6e-19;  // Initialise constants used in calculations

int main() {
  
  std::map<std::string, int> col_map;
  // add some value/key pairs in a map
  // Each number value correspods to the minimum wavelength of its respective colour
  // Max wavelength before Red is 740nm  if wl > 740 then    its infra red

  col_map["1. Red"] = 625;    // 625 - 740 nm
  col_map["2. Orange"] = 590; // 590 - 625 nm
  col_map["3. Yellow"] = 565; // 565 - 590 nm
  col_map["4. Green"] = 520;  // 520 - 565 nm
  col_map["5. Cyan"] = 500;   // 500 - 520 nm
  col_map["6. Blue"] = 435;   // 435 - 500 nm
  col_map["7. Violet"] = 380; // 380 - 435 nm
  // wavelength after violet is UV at less than 380nm
  std::map<std::string, int>::iterator i;

  float LED_forCurrent = 0.025;

  // Set array for each value of E24 resistor series
  double res_array[24] = {1.0, 1.1, 1.2, 1.3, 1.5, 1.6, 1.8, 2.0, 2.2, 2.4, 2.7, 3.0, 3.3, 3.6, 3.9, 4.3, 4.7, 5.1, 5.6, 6.2, 6.8, 7.5, 8.2, 9.1};

  float wavelength = 0;
  std::string LED_colour;
  float CBev, VBev, Energygap, wlinhundreds;
  //initialise variables needed for first part of function
  
  
}