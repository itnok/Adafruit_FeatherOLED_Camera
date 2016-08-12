/**************************************************************************/
/*!
    @file     Adafruit_FeatherOLED_Photography.cpp
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
#include "Adafruit_FeatherOLED_Photography.h"



/******************************************************************************
 *
 *                                                            PROTECTED methods
 *
 ******************************************************************************/



/******************************************************************************/
/*!
    @brief  Renders the battery icon
*/
/******************************************************************************/
void Adafruit_FeatherOLED_Photography::renderBattery ( void )
{

    uint8_t  i                    = 0;

    uint8_t  icnBatteryStartX     = 0;
    uint8_t  icnBatteryStartY     = 0;

    uint8_t  icnBatteryHalfWidth  = (int)( ( _icnBatteryWidth  - 2 ) * 0.5 + 0.5 );  // it's like round( ( _icnBatteryWidth  - 2 ) / 2 );
    uint8_t  icnBatteryHalfHeight = (int)( ( _icnBatteryHeight - 2 ) * 0.5 + 0.5 );  // it's like round( ( _icnBatteryHeight - 2 ) / 2 );

    uint8_t  txtBatteryStartX     = 0;
    uint8_t  txtBatteryStartY     = 0;

    float    batteryPercentage    = 0.0F;

    String   batText              = "";



    if ( _batteryVisible )
    {

        //
        // Render the battery icon if requested
        //

        switch ( _batteryIcon )
        {
            case FOLED_BATTERYICON_BARS:

                icnBatteryStartX = _displayWidth - _icnBatteryWidth;



                //
                // Draw the base ( empty ) battery icon
                //

                drawLine( icnBatteryStartX + 1,
                          icnBatteryStartY,
                          icnBatteryStartX + _icnBatteryWidth  - 4,
                          icnBatteryStartY,
                          WHITE );

                drawLine( icnBatteryStartX,
                          icnBatteryStartY + 1,
                          icnBatteryStartX,
                          icnBatteryStartY + _icnBatteryHeight - 2,
                          WHITE );

                drawLine( icnBatteryStartX + 1,
                          icnBatteryStartY + _icnBatteryHeight - 1,
                          icnBatteryStartX + _icnBatteryWidth  - 4,
                          icnBatteryStartY + _icnBatteryHeight - 1,
                          WHITE );

                drawLine( icnBatteryStartX + _icnBatteryWidth  - 3,
                          icnBatteryStartY + 1,
                          icnBatteryStartX + _icnBatteryWidth  - 2,
                          icnBatteryStartY + 1,
                          WHITE );

                drawLine( icnBatteryStartX + _icnBatteryWidth  - 1,
                          icnBatteryStartY + 2,
                          icnBatteryStartX + _icnBatteryWidth  - 1,
                          icnBatteryStartY + _icnBatteryHeight - 3,
                          WHITE );

                drawLine( icnBatteryStartX + _icnBatteryWidth  - 3,
                          icnBatteryStartY + _icnBatteryHeight - 2,
                          icnBatteryStartX + _icnBatteryWidth  - 2,
                          icnBatteryStartY + _icnBatteryHeight - 2,
                          WHITE );



                //
                // Draw the appropriate number of bars
                //

                if( ( _battery >= 3.4F ) )
                {

                    //
                    // One bar
                    //

                    fillRect( icnBatteryStartX    + 2,
                              icnBatteryStartY    + 2,
                              _icnBatteryBarWidth - 1,
                              _icnBatteryHeight   - 4,
                              WHITE );

                    if ( _battery >= 3.6F )
                    {

                        //
                        // 2nd bar
                        //

                        fillRect( icnBatteryStartX    + _icnBatteryBarWidth + 2,
                                  icnBatteryStartY    + 2,
                                  _icnBatteryBarWidth - 1,
                                  _icnBatteryHeight   - 4,
                                  WHITE );

                    }

                    if ( _battery >= 3.83F )
                    {

                        //
                        // 3rd bar
                        //

                        fillRect( icnBatteryStartX    + _icnBatteryBarWidth * 2 + 2,
                                  icnBatteryStartY    + 2,
                                  _icnBatteryBarWidth - 1,
                                  _icnBatteryHeight   - 4,
                                  WHITE );

                    }

                    if ( _battery >= 4.05F )
                    {

                        //
                        // 4th bar
                        //

                        fillRect( icnBatteryStartX    + _icnBatteryBarWidth * 3 + 2,
                                  icnBatteryStartY    + 2,
                                  _icnBatteryBarWidth - 1,
                                  _icnBatteryHeight   - 4,
                                  WHITE );

                    }

                    if ( _battery >= 4.26F )
                    {

                        //
                        // Fully Charged
                        //

                        fillRect( icnBatteryStartX  + 1,
                                  icnBatteryStartY  + 1,
                                  _icnBatteryWidth  - 2,
                                  _icnBatteryHeight - 2,
                                  WHITE );

                        //
                        // Bolt Symbol
                        //

                        drawLine( icnBatteryStartX + icnBatteryHalfWidth - 1,
                                  icnBatteryStartY + _icnBatteryHeight   - 2,
                                  icnBatteryStartX + icnBatteryHalfWidth + icnBatteryHalfHeight - 1,
                                  icnBatteryStartY + _icnBatteryHeight   - icnBatteryHalfHeight - 1,
                                  BLACK );

                        drawLine( icnBatteryStartX + icnBatteryHalfWidth + icnBatteryHalfHeight - 1,
                                  icnBatteryStartY + _icnBatteryHeight   - icnBatteryHalfHeight - 1,
                                  icnBatteryStartX + icnBatteryHalfWidth - icnBatteryHalfHeight,
                                  icnBatteryStartY + _icnBatteryHeight   - icnBatteryHalfHeight - 1,
                                  BLACK );

                        drawLine( icnBatteryStartX + icnBatteryHalfWidth - icnBatteryHalfHeight,
                                  icnBatteryStartY + _icnBatteryHeight   - icnBatteryHalfHeight - 1,
                                  icnBatteryStartX + icnBatteryHalfWidth,
                                  icnBatteryStartY + 1,
                                  BLACK );

                    }
                }

                break;

            case FOLED_BATTERYICON_MINI:

                icnBatteryStartX = _displayWidth - _icnBatteryMiniWidth;



                //
                // Draw the mini ( vertical ) battery icon
                //

                drawLine( icnBatteryStartX,
                          icnBatteryStartY + 1,
                          icnBatteryStartX,
                          icnBatteryStartY + _icnBatteryMiniHeight - 1,
                          WHITE );

                drawLine( icnBatteryStartX,
                          icnBatteryStartY + _icnBatteryMiniHeight - 1,
                          icnBatteryStartX + _icnBatteryMiniWidth  - 1,
                          icnBatteryStartY + _icnBatteryMiniHeight - 1,
                          WHITE );

                drawLine( icnBatteryStartX + _icnBatteryMiniWidth  - 1,
                          icnBatteryStartY + _icnBatteryMiniHeight - 1,
                          icnBatteryStartX + _icnBatteryMiniWidth  - 1,
                          icnBatteryStartY + 1,
                          WHITE );

                fillRect( icnBatteryStartX + 1,
                          icnBatteryStartY,
                          _icnBatteryMiniWidth - 2,
                          2,
                          WHITE );

                break;

            default:
                break;

        }



        //
        // Calculate battery juice percentage
        //

        batteryPercentage = ( _battery - 3.39F ) * 100 / ( 4.26F - 3.39F );



        //
        // Make sure percentage is in the correct range
        //

        if ( batteryPercentage < 0.0F )
        {

            batteryPercentage = 0.0F;

        }
        else if ( batteryPercentage > 100.0F )
        {

            batteryPercentage = 100.0F;

        }



        if ( _batteryText == FOLED_BATTERYTEXT_VOLT )
        {

            //
            // Create the string containing percentage of battery charge
            //

            batText += String( _battery, 2 );
            batText += "V";

            batText.trim();

        }
        else if ( _batteryText == FOLED_BATTERYTEXT_PERC )
        {

            //
            // Create the string containing percentage of battery charge
            //

            batText += String( batteryPercentage, 0 );
            batText += "%";

            batText.trim();

        }



        //
        // Set correct text position
        //

        if ( _batteryIcon == FOLED_BATTERYICON_NONE )
        {

            txtBatteryStartX = _displayWidth - getTextBoxWidth( batText ) - 1;

        }
        else if ( _batteryIcon == FOLED_BATTERYICON_BARS )
        {

            txtBatteryStartX = _displayWidth - _icnBatteryWidth - getTextBoxWidth( batText ) - 1;

        }
        else if ( _batteryIcon == FOLED_BATTERYICON_MINI )
        {

            txtBatteryStartX = _displayWidth - _icnBatteryMiniWidth - getTextBoxWidth( batText ) - 1;

        }



        //
        // Print text on the OLED display
        //

        setCursor( txtBatteryStartX, txtBatteryStartY );

        println( batText );

    }
}



/******************************************************************************/
/*!
    @brief  Get width of the bounding box of a text with the current typographic settings
*/
/******************************************************************************/

uint16_t Adafruit_FeatherOLED_Photography::getTextBoxWidth( String str )
{

    int16_t  txtBoxX  = 0;
    int16_t  txtBoxY  = 0;
    uint16_t txtBoxW  = 0;
    uint16_t txtBoxH  = 0;

    int strLen        = str.length() + 1;

    char charArray[ strLen ];



    //
    // Copy str over to charArray
    //

    str.toCharArray( charArray, strLen );



    //
    // Evaluate width differently according to
    // the text nature ( fixed width or font )
    //

    if ( ! gfxFont )
    {

        return ( strLen - 1 ) * textsize * 6;

    }
    else
    {

        getTextBounds( charArray, 0, 0, &txtBoxX, &txtBoxY, &txtBoxW, &txtBoxH );

        return txtBoxW;

    }

}



/******************************************************************************
 *
 *                                                               PUBLIC methods
 *
 ******************************************************************************/



/******************************************************************************/
/*!
    @brief  Get battery visibility status
*/
/******************************************************************************/

bool Adafruit_FeatherOLED_Photography::getBatteryVisible ( void )
{
    return _batteryVisible;
}



/******************************************************************************/
/*!
    @brief  getBatteryVisible alias
*/
/******************************************************************************/

bool Adafruit_FeatherOLED_Photography::isBatteryVisible ( void )
{

    return getBatteryVisible();

}



/******************************************************************************/
/*!
    @brief  Get battery icon visibility status
*/
/******************************************************************************/

uint8_t Adafruit_FeatherOLED_Photography::getBatteryIcon ( void )
{

    return _batteryIcon;

}



/******************************************************************************/
/*!
    @brief  Get battery text visibility status
*/
/******************************************************************************/

uint8_t Adafruit_FeatherOLED_Photography::getBatteryText ( void )
{

    return _batteryText;

}



/******************************************************************************/
/*!
    @brief  Set battery icon and descriptive text visibility
*/
/******************************************************************************/

void Adafruit_FeatherOLED_Photography::setBatteryVisible ( bool enable = true )
{

    _batteryVisible = enable;

    if( _batteryVisible )
    {

        if ( _batteryIcon == FOLED_BATTERYICON_NONE &&
             _batteryText == FOLED_BATTERYTEXT_NONE )
        {

            setBatteryIcon( FOLED_BATTERYICON_BARS );

        }

    }
    else
    {

        if( _batteryIcon == FOLED_BATTERYICON_BARS ||
            _batteryText == FOLED_BATTERYTEXT_VOLT ||
            _batteryText == FOLED_BATTERYTEXT_PERC )
        {

            setBatteryIcon( FOLED_BATTERYICON_NONE );
            setBatteryText( FOLED_BATTERYTEXT_NONE );

        }

    }

}



/******************************************************************************/
/*!
    @brief  Set battery icon visibility status and icon type
*/
/******************************************************************************/

void Adafruit_FeatherOLED_Photography::setBatteryIcon ( uint8_t enable = FOLED_BATTERYICON_BARS )
{

    _batteryIcon    = enable;

}



/******************************************************************************/
/*!
    @brief  Set battery text visibility status and text formatting
*/
/******************************************************************************/

void Adafruit_FeatherOLED_Photography::setBatteryText ( uint8_t textType = FOLED_BATTERYTEXT_PERC )
{

    _batteryText    = textType;

}



/******************************************************************************/
/*!
    @brief  Updates the OLED display
*/
/******************************************************************************/

void Adafruit_FeatherOLED_Photography::refreshIcons ( void )
{

    //
    // Erase the canvas
    //

    fillRect( _displayWidth - _icnBatteryWidth - 31,  0, _displayWidth, _icnBatteryHeight + 1, BLACK );



    //
    // Render all the icons and controls
    //

    renderBattery();



    //
    // Display on screen
    //

    display();

}


