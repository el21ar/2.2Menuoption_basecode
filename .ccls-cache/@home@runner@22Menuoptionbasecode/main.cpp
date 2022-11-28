#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <fstream>

const float h = 6.626e-34;
const int c = 3e8;
const float e = 1.6e-19;


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
  
}