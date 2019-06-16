//
//  A palm shaped lamp showing the current time in COlour coded Roman Numerals.
//
//  Copyright (C) 2019 Nicola Cimmino
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "RomanDisplay.h"
#include "RTC.h"

RomanDisplay display;
RTC rtc;

void setup()
{
    display.clearDisplay();
    display.show();

    rtc.initialize();
    rtc.setTime(9, 51, 00);
}

void loop()
{
    display.clearDisplay();
    display.printNumber(rtc.getHours(), 0, 15);
    display.printNumber(rtc.getMinutes(), 15, 15);
    display.show();

    delay(1000);
}
