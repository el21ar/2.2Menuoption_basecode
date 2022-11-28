#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

const float h = 6.626e-34;
const int c = 3e8;
const float e = 1.6e-19; // Initialise constants used in calculations

int main() {

  std::map<std::string, int> col_map;
  // add some value/key pairs in a map
  // Each number value correspods to the minimum wavelength of its respective
  // colour Max wavelength before Red is 740nm  if wl > 740 then    its infra
  // red

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
  double res_array[24] = {1.0, 1.1, 1.2, 1.3, 1.5, 1.6, 1.8, 2.0,
                          2.2, 2.4, 2.7, 3.0, 3.3, 3.6, 3.9, 4.3,
                          4.7, 5.1, 5.6, 6.2, 6.8, 7.5, 8.2, 9.1};

  float wavelength = 0;
  std::string LED_colour;
  float CBev, VBev, Energygap, wlinhundreds;
  // initialise variables needed for first part of function
  bool valid_input_bandgap = false;
  int wrongloop;

  while (valid_input_bandgap == false) {
    wrongloop++;
    if (wrongloop >= 5) {
      std::cout << "Due to a number of invalid inputs this program has to "
                   "revert back to the main menu";
      exit(0);
      // go_to_menu
    }
    std::cout << "\nPlease enter the energy level value of the Conduction band "
                 "in the semiconductor in eV:\n ";
    std::cin >> CBev;

    std::cout << "\nPlease enter the energy level value of the Valence band in "
                 "the semiconductor in eV:\n ";
    std::cin >> VBev;
    // collect values from the user for CBev and VBev, note these values need to
    // be converted in or before calculation

    if (CBev == 0) {
      std::cout << "\nPlease enter valid input values, where the conduction "
                   "band energy value must be a non 0 number\n ";
    }

    else if (CBev > VBev) {

      Energygap =
          CBev * e - VBev * e; // get the bandgap energy level whilst converting
                               // the product from electronvolts to joules.
      wavelength =
          h * c / Energygap; // get the wavelength of the photons emitted

      std::cout
          << wavelength
          << std::endl; // Line used to output value calculated to check output
      valid_input_bandgap = true;
    }

    else if (CBev < VBev) {
      std::cout << "\nPlease enter valid input values, where the conduction "
                   "band energy value must be a larger numerical value than "
                   "the valence band energy value\n ";
    }
  }

  wlinhundreds = wavelength * 1e9; //Convert wavelength calculated from nm to be compared to numbers in the map
  for (i = col_map.begin(); i != col_map.end(); i++) {  // Loop next processes for each value of col_map

    if (wlinhundreds >= i->second) {  //Compare wlinhundreds to col_map int, if calculated value is greater than the value stored in the value part of map then:
      LED_colour = i->first;  // set the str variable to the current Key of the map
      break;  //break the for loop so that no more comparing happens and colour isn't changed
    }
  }

  if (wlinhundreds < 380) {    // If the calculated valuue is below the range in the col_map 
    std::cout << "The wavelength produced is beyond the visible light spectrum "
                 "into the ultra violet spectrum.";  // Give statement saying what is wrong
    LED_colour = "   Ultra Violet";  // Set colour to the next part in EM spectrum
    //  go_back_to_main();
    //Launches subroutine of returning to the main menu, liable to change to do another LED or return to menu
  } 
  else if (wlinhundreds > 740) {  // Opposite to previous if statement where if the wavelength is greater than the range, note this will still be included in the Red section so colour must be changed to account for this as otherwise it could carry on with incorrect values
    std::cout << "The wavelength produced is beyond the visible light spectrum "
                 "into the infra red spectrum.";  // Statement about why proprerties provided are inappropriate for an LED
    LED_colour = "   Infra Red";  // Set colour to real aspect of the EM spectrum
    //  go_back_to_main();
    //Launches subroutine of returning to the main menu, liable to change to do another LED or return to menu

  }
   LED_colour.erase(0, 3);    //Remove the first 3 characters of the srting stored in colour, this removes the number, dot and space or threee spaces in other cases This is useful as the string can be outputted in a sentence or something similar
  std::cout << LED_colour << std::endl;  //output LED_colour to see what value it is

}

