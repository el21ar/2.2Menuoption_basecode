#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

const float h = 6.626e-34;
const int c = 3e8;
const float e = 1.6e-19; // Initialise constants used in calculations

void LED_bandgap_textfile();
void LED_res_textfile();

int main() {
  LED_bandgap_textfile();
  LED_res_textfile();
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
  double res_array[25] = {1.0, 1.1, 1.2, 1.3, 1.5, 1.6, 1.8, 2.0, 2.2,
                          2.4, 2.7, 3.0, 3.3, 3.6, 3.9, 4.3, 4.7, 5.1,
                          5.6, 6.2, 6.8, 7.5, 8.2, 9.1, 10};

  float wavelength = 0;
  std::string LED_colour;
  // initialise variables needed for first part of function
  bool valid_input_bandgap = false;
  int wrongloop;
  float CBev, VBev, Energygap, wlinhundreds;
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

  wlinhundreds = wavelength * 1e9; // Convert wavelength calculated from nm to
                                   // be compared to numbers in the map
  for (i = col_map.begin(); i != col_map.end();
       i++) { // Loop next processes for each value of col_map

    if (wlinhundreds >=
        i->second) { // Compare wlinhundreds to col_map int, if calculated value
                     // is greater than the value stored in the value part of
                     // map then:
      LED_colour =
          i->first; // set the str variable to the current Key of the map
      break; // break the for loop so that no more comparing happens and colour
             // isn't changed
    }
  }

  if (wlinhundreds <
      380) { // If the calculated valuue is below the range in the col_map
    std::cout
        << "The wavelength produced is beyond the visible light spectrum into "
           "the ultra violet spectrum."; // Give statement saying what is wrong
    LED_colour = "  Ultra Violet"; // Set colour to the next part in EM spectrum
    //  go_back_to_main();
    // Launches subroutine of returning to the main menu, liable to change to do
    // another LED or return to menu
  } else if (wlinhundreds >
             740) { // Opposite to previous if statement where if the wavelength
                    // is greater than the range, note this will still be
                    // included in the Red section so colour must be changed to
                    // account for this as otherwise it could carry on
                    // withincorrect values
    std::cout
        << "The wavelength produced is beyond the visible light spectrum into "
           "the infra red spectrum."; // Statement about why proprerties
                                      // provided are inappropriate for an LED
    LED_colour = "   Infra Red"; // Set colour to real aspect of the EM spectrum
    //  go_back_to_main();
    // Launches subroutine of returning to the main menu, liable to change to do
    // another LED or return to menu
  }
  LED_colour.erase(
      0, 3); // Remove the first 3 characters of the srting stored in
             // colour,this removes the number, dot and space or threee spaces
             // in other cases This is useful as the string can be outputted in
             // a sentence or something similar
  std::cout << LED_colour
            << std::endl; // output LED_colour to see what value it is

  float ForV; // initialise forward voltage for each colour, statements needed
              // to be changed when the erase command was added
  if (LED_colour == "Red") {
    ForV = 1.8;
  } else if (LED_colour == "Orange") {
    ForV = 2;
  } else if (LED_colour == "Yellow") {
    ForV = 2.3;
  } else if (LED_colour == "Green") {
    ForV = 3.5;
  } else if (LED_colour == "Cyan") {
    ForV = 3.6;
  } else if (LED_colour == "Blue") {
    ForV = 3.8;
  } else if (LED_colour == "Violet") {
    ForV = 4;
  } else {
    ForV = 0; // set ForV to 0 for UV or IR values inputted just in case they
              // got passed the return commands
  }
  std::cout << "Forward voltage: " << ForV << "\n";

  float Vsupply, IdealRes, resmult, e24base,
      e24final; // Initialise decimals used in calculations
  int t = 0;
  std::string choice;

  if (ForV == 0) { // if the UV or IR values got this far return to menu
    // go_back_to_main();
  } else {
    bool valid_input_res = false;

    while (valid_input_res ==
           false) { // Loop indefinitely until a correct input is added
      std::cout
          << "Do you want to calculate the protective resistor for the diode? "
             "Enter 'y' for yes or 'n' for no.\n "; // ask question on each
                                                    // loop, states correct
                                                    // inputs in '' marks

      std::cin >> choice; // set input to choice
      t = 0; // reset t to 0 as otherwise it would build up over the loops
      if (choice == "y") { // if want to carry on
        valid_input_res = true;
        bool valid_input_V = false;

        while (valid_input_V == false) {

          std::cout << "Please enter the supply voltage, a valid voltage must "
                       "be over "
                    << ForV << "V \n";
          std::cin >> Vsupply; // Get input value for supply Voltage

          if (Vsupply <= ForV) { // If voltage supply is less than forward V
            std::cout
                << "The voltage supplied is not sufficient enough to power "
                   "the LED.\n";
            // As boolean statement hasn't changed it loops back around
          } else {
            valid_input_V = true;
            IdealRes = (Vsupply - ForV) / LED_forCurrent;
            std::cout << "The ideal resistance is: " << IdealRes << "Ω \n";
            // Calc and output the ideal resistance
            resmult = IdealRes;
            // store output in another variable to be manipulated

            while (resmult > 10) {
              resmult = resmult / 10;
              t++;
              // Get the resistance into a form of x.x and increment a variable
              // for each time it divides by 10
            }

            for (int j = 1; j < 25;
                 j++) { // Go through each value of the e24 array
              if (resmult <=
                  res_array[j]) { // if the value pof resmult in form x.x is
                                  // less than the current value of the array
                e24base = res_array[j]; // set the base of the final res value
                                        // to the first appropriate value of the
                                        // e24 series and break the while loop
                break;
              }
            }

            e24final = e24base * pow(10,
                                     t); // use base and incremented variable to
                                         // get final e24 value
            std::cout << "The E24 resistance is: " << e24final << "Ω \n";

            std::cout << "Do you want to do another calculation for a diode or "
                         "return to the menu? Enter 'c' for calculation or "
                         "anything else for menu.\n "; // Give option to go
                                                       // again or back to menu
            std::string choice2;
            std::cin >> choice2;

            if (choice2 == "c") {
              // menu_item_()
            } else {
              //  go_back_to_main();
            } // as option is one key or other don't need to worry about wrong
              // input
          }
        }
      }

      else if (choice == "n") {
        valid_input_res = true;
        // go_back_to_main()
      }

      else {
        std::cout << "Please enter a valid input.";
        valid_input_res = false;
      }
    }
  }
}

// do question if want to calc again or not
// do text file editing
// implement in a basic menu template
// get your arse in gear

void LED_bandgap_textfile() {

  float BG, Wl, WlinHun;
  std::string LED_col;

  std::map<std::string, int> bg_map;
  bg_map["1. Red"] = 625;    // 625 - 740 nm
  bg_map["2. Orange"] = 590; // 590 - 625 nm
  bg_map["3. Yellow"] = 565; // 565 - 590 nm
  bg_map["4. Green"] = 520;  // 520 - 565 nm
  bg_map["5. Cyan"] = 500;   // 500 - 520 nm
  bg_map["6. Blue"] = 435;   // 435 - 500 nm
  bg_map["7. Violet"] = 380; // 380 - 435 nm
  std::map<std::string, int>::iterator i;

  std::ofstream LED_bandgap_example;
  LED_bandgap_example.open("LED_bandgap_examples.txt");

  for (float BG = 1.5; BG <= 3.5; BG = BG + 0.1) {
    Wl = h * c / (BG * e);
    WlinHun = Wl * 1e9;

    for (i = bg_map.begin(); i != bg_map.end();
         i++) { // Loop next processes for each value of col_map

      if (WlinHun >= i->second) { // Compare wlinhundreds to col_map int, if
                                  // calculated value
        // is greater than the value stored in the value part of
        // map then:
        LED_col =
            i->first; // set the str variable to the current Key of the map
        LED_col.erase(0, 3);
        break; // break the for loop so that no more comparing happens and
               // colour isn't changed
      }
    }
    if (WlinHun >= 740) {
      LED_col = "Infra Red";
    } else if (WlinHun <= 380) {
      LED_col = "Ultra Violet";
    }
    LED_bandgap_example << "Bandgap: " << BG << "ev\t Wavelength: " << WlinHun
                        << "nm\t LED colour: " << LED_col << "\n"
                        << std::endl;
  }
  LED_bandgap_example.close();
}

void LED_res_textfile() {
  float Vsup, IdealR, Rmult, E24base, E24fin, Vfor;
  int m = 0;
  std::string col;

  std::map<std::string, float> forv_map;
  forv_map["1. Red"] = 1.8;    // 625 - 740 nm
  forv_map["2. Orange"] = 2;   // 590 - 625 nm
  forv_map["3. Yellow"] = 2.3; // 565 - 590 nm
  forv_map["4. Green"] = 3.5;  // 520 - 565 nm
  forv_map["5. Cyan"] = 3.6;   // 500 - 520 nm
  forv_map["6. Blue"] = 3.8;   // 435 - 500 nm
  forv_map["7. Violet"] = 4;   // 380 - 435 nm
  std::map<std::string, float>::iterator w;

  float LED_forCurrent = 0.025;

  // Set array for each value of E24 resistor series
  double res_array[25] = {1.0, 1.1, 1.2, 1.3, 1.5, 1.6, 1.8, 2.0, 2.2,
                          2.4, 2.7, 3.0, 3.3, 3.6, 3.9, 4.3, 4.7, 5.1,
                          5.6, 6.2, 6.8, 7.5, 8.2, 9.1, 10};

  std::ofstream LED_proc_resistor_example;
  LED_proc_resistor_example.open("LED_proc_resistor_examples.txt");

  for (w = forv_map.begin(); w != forv_map.end();
       w++) { // Loop next processes for each value of col_map
    col = w->first;
    Vfor = w->second;
    m = 0;

    for (Vsup = 5; Vsup <= 25; Vsup = Vsup + 2.5) {
      m = 0;
      IdealR = (Vsup - Vfor) / LED_forCurrent;
      Rmult = IdealR;
      while (Rmult > 10) {
        Rmult = Rmult / 10;
        m++;
      }
      for (int j = 1; j < 25; j++) {
        if (Rmult <= res_array[j]) {
          E24base = res_array[j];
          break;
        }
      }
      E24fin = E24base * pow(10, m);
      LED_proc_resistor_example << "LED Colour: " << col
                                << ",\tSupply voltage: " << Vsup
                                << "V,\t Forward op voltage: " << Vfor
                                << "V,\t Ideal resistance:" << IdealR
                                << "Ω,\t E24 resistance:" << E24fin << "Ω\n"
                                << std::endl;
    }
    LED_proc_resistor_example << "\n\n" << std::endl;
  }
  LED_proc_resistor_example.close();
}
