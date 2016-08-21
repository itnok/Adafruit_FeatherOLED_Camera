/**************************************************************************/
/*!
    @file     Adafruit_FeatherOLED_Photography.h
    @author   Simone Conti

    @section LICENSE

    Copyright (c) 2016, Simone Conti (simoneconti.me)
    All rights reserved.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/

#ifndef _Adafruit_FeatherOLED_Photography_H_
#define _Adafruit_FeatherOLED_Photography_H_

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_FeatherOLED.h>

class Adafruit_FeatherOLED_Photography : public Adafruit_FeatherOLED
{
    protected:

        //
        // Text size for all the text related to icons and defining the icons size as well
        //

        uint8_t  _iconsSize;



        //
        // Icon styles
        //

        uint8_t  _batteryIcon;
        uint8_t  _batteryText;



        //
        // Battery icon dimensions ( Regular Size )
        //

        uint8_t  _icnBatteryWidth;
        uint8_t  _icnBatteryHeight;
        uint8_t  _icnBatteryBarWidth;



        //
        // Battery icon dimensions (Mini Size )
        //

        uint8_t  _icnBatteryMiniWidth;
        uint8_t  _icnBatteryMiniHeight;



        uint16_t getTextBoxWidth     ( String str );

        float    getBatteryPercentage( void );

        String   getBatteryText      ( void );

        void     renderBattery       ( void );



    public:

        enum
        {

            //
            // Battery icon status codes
            //

            FOLED_BATTERYICON_NONE  = 0,    // NO battery icon
            FOLED_BATTERYICON_BARS  = 1,    // Battery icon with bars
            FOLED_BATTERYICON_MINI  = 2,    // Mini battery icon



            //
            // Battery text status codes
            //

            FOLED_BATTERYTEXT_NONE  = 0,    // NO battery text
            FOLED_BATTERYTEXT_VOLT  = 1,    // Battery text showing voltage
            FOLED_BATTERYTEXT_PERC  = 2     // Battery text showing charge percentage

        };



        //
        // Constructor
        //

        Adafruit_FeatherOLED_Photography ( int reset = -1 ) : Adafruit_FeatherOLED( reset )
        {

            //
            // Show small icons by default
            //

            _iconsSize            = 1;



            //
            // Show battery bars by default
            //

            _batteryIcon          = FOLED_BATTERYICON_BARS;



            //
            // Show battery charge percentage by default
            //

            _batteryText          = FOLED_BATTERYTEXT_PERC;



            //
            // Change the following values if your display is different
            // or to draw bigger/smaller icons
            //

            _icnBatteryWidth      =  19;
            _icnBatteryHeight     =   7;
            _icnBatteryBarWidth   = ( ( _icnBatteryWidth - 3 ) / 4 );

            _icnBatteryMiniWidth  =   4;
            _icnBatteryMiniHeight =   7;

        }



        //
        // Getter methods
        //

        uint16_t getDisplayWidth    ( void );
        uint16_t getDisplayHeight   ( void );

        uint8_t  getTextSize        ( void );
        uint8_t  getIconsSize       ( void );

        bool     getBatteryVisible  ( void );
        bool     isBatteryVisible   ( void );
        uint8_t  getBatteryIconStyle( void );
        uint8_t  getBatteryTextStyle( void );



        //
        // Setter methods
        //

        void     setIconsSize       ( uint8_t );

        void     setBatteryVisible  ( bool    enable );
        void     setBatteryIconStyle( uint8_t enable );
        void     setBatteryTextStyle( uint8_t textType );



        //
        // Graphic related methods
        //

        void     refreshIcons       ( void );
        void     wipeMsgArea        ( void );
        void     clearMsgArea       ( void );

        void     printMsgArea       ( String str, uint8_t align );
        void     printShutterSpeed  ( String str );

};

#endif /* _Adafruit_FeatherOLED_Photography_H_ */
