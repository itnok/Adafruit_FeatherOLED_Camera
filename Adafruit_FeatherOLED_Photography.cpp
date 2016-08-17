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
    @brief  Get width of the bounding box of a text with the current typographic settings
*/
/******************************************************************************/

uint16_t Adafruit_FeatherOLED_Photography::getTextBoxWidth( String str )
{

    int16_t  i_txtBoxX  = 0;
    int16_t  i_txtBoxY  = 0;
    uint16_t ui_txtBoxW = 0;
    uint16_t ui_txtBoxH = 0;

    int      i_strLen   = str.length() + 1;

    char     charArray[ i_strLen ];



    //
    // Copy str over to charArray
    //

    str.toCharArray( charArray, i_strLen );



    //
    // Evaluate width differently according to
    // the text nature ( fixed width or font )
    //

    if ( ! gfxFont )
    {

        return ( i_strLen - 1 ) * 6 * textsize + 1;

    }
    else
    {

        getTextBounds( charArray, 0, 0, &i_txtBoxX, &i_txtBoxY, &ui_txtBoxW, &ui_txtBoxH );

        return ui_txtBoxW;

    }

}



/******************************************************************************/
/*!
    @brief  Get the percentage of juice in the battery
*/
/******************************************************************************/

float Adafruit_FeatherOLED_Photography::getBatteryPercentage( void )
{

    float    f_batteryPercentage = 0.0F;



    //
    // Calculate battery juice percentage
    //

    f_batteryPercentage = ( _battery - 3.39F ) * 100 / ( 4.26F - 3.39F );



    //
    // Make sure percentage is in the correct range
    //

    if ( f_batteryPercentage < 0.0F )
    {

        f_batteryPercentage = 0.0F;

    }
    else if ( f_batteryPercentage > 100.0F )
    {

        f_batteryPercentage = 100.0F;

    }



    return f_batteryPercentage;

}



/******************************************************************************/
/*!
    @brief  Get width of the bounding box of a text with the current typographic settings
*/
/******************************************************************************/

String Adafruit_FeatherOLED_Photography::getBatteryText( void )
{

    float    f_batteryPercentage = getBatteryPercentage();

    String   s_batteryText       = "";



    if ( _batteryText == FOLED_BATTERYTEXT_VOLT )
    {

        //
        // Create the string containing percentage of battery charge
        //

        s_batteryText += String( _battery, 2 );
        s_batteryText += "V";
        s_batteryText.trim();

    }
    else if ( _batteryText == FOLED_BATTERYTEXT_PERC )
    {

        //
        // Create the string containing percentage of battery charge
        //

        s_batteryText += String( f_batteryPercentage, 0 );
        s_batteryText += "%";
        s_batteryText.trim();

    }

    return s_batteryText;

}



/******************************************************************************/
/*!
    @brief  Renders the battery icon
*/
/******************************************************************************/
void Adafruit_FeatherOLED_Photography::renderBattery ( void )
{

    uint8_t  ui_icnBatteryStartX     = 0;
    uint8_t  ui_icnBatteryStartY     = 0;

    uint8_t  ui_icnBatteryHalfWidth  = (int)( ( _icnBatteryWidth  - 2 ) * 0.5 + 0.5 );  // it's like round( ( _icnBatteryWidth  - 2 ) / 2 );
    uint8_t  ui_icnBatteryHalfHeight = (int)( ( _icnBatteryHeight - 2 ) * 0.5 + 0.5 );  // it's like round( ( _icnBatteryHeight - 2 ) / 2 );

    uint8_t  ui_icnSize              = getIconsSize();
    uint8_t  ui_txtBatteryStartX     = 0;
    uint8_t  ui_txtBatteryStartY     = 0;

    uint8_t  ui_originalTxtSize      = getTextSize();

    String   s_batText               = "";



    if ( _batteryVisible )
    {

        //
        // Render the battery icon if requested
        //

        setTextSize( getIconsSize() );

        switch ( _batteryIcon )
        {
            case FOLED_BATTERYICON_BARS:

                ui_icnBatteryStartX = _width - ( _icnBatteryWidth * ui_icnSize );



                //
                // Draw the base ( empty ) battery icon
                //

                drawLine( ui_icnBatteryStartX + 1,
                          ui_icnBatteryStartY,
                          ui_icnBatteryStartX + ( _icnBatteryWidth  * ui_icnSize ) - 4,
                          ui_icnBatteryStartY,
                          WHITE );

                drawLine( ui_icnBatteryStartX,
                          ui_icnBatteryStartY + 1,
                          ui_icnBatteryStartX,
                          ui_icnBatteryStartY + ( _icnBatteryHeight * ui_icnSize ) - 2,
                          WHITE );

                drawLine( ui_icnBatteryStartX + 1,
                          ui_icnBatteryStartY + ( _icnBatteryHeight * ui_icnSize ) - 1,
                          ui_icnBatteryStartX + ( _icnBatteryWidth  * ui_icnSize ) - 4,
                          ui_icnBatteryStartY + ( _icnBatteryHeight * ui_icnSize ) - 1,
                          WHITE );

                drawLine( ui_icnBatteryStartX + ( _icnBatteryWidth  * ui_icnSize ) - 3,
                          ui_icnBatteryStartY + 1,
                          ui_icnBatteryStartX + ( _icnBatteryWidth  * ui_icnSize ) - 2,
                          ui_icnBatteryStartY + 1,
                          WHITE );

                drawLine( ui_icnBatteryStartX + ( _icnBatteryWidth  * ui_icnSize ) - 1,
                          ui_icnBatteryStartY + 2,
                          ui_icnBatteryStartX + ( _icnBatteryWidth  * ui_icnSize ) - 1,
                          ui_icnBatteryStartY + ( _icnBatteryHeight * ui_icnSize ) - 3,
                          WHITE );

                drawLine( ui_icnBatteryStartX + ( _icnBatteryWidth  * ui_icnSize ) - 3,
                          ui_icnBatteryStartY + ( _icnBatteryHeight * ui_icnSize ) - 2,
                          ui_icnBatteryStartX + ( _icnBatteryWidth  * ui_icnSize ) - 2,
                          ui_icnBatteryStartY + ( _icnBatteryHeight * ui_icnSize ) - 2,
                          WHITE );



                //
                // Draw the appropriate number of bars
                //

                if( ( _battery >= 3.4F ) )
                {

                    //
                    // One bar
                    //

                    fillRect( ui_icnBatteryStartX   + 2,
                              ui_icnBatteryStartY   + 2,
                              ( _icnBatteryBarWidth * ui_icnSize ) - 1,
                              ( _icnBatteryHeight   * ui_icnSize ) - 4,
                              WHITE );

                    if ( _battery >= 3.6F )
                    {

                        //
                        // 2nd bar
                        //

                        fillRect( ui_icnBatteryStartX   + ( _icnBatteryBarWidth * ui_icnSize ) + 2,
                                  ui_icnBatteryStartY   + 2,
                                  ( _icnBatteryBarWidth * ui_icnSize ) - 1,
                                  ( _icnBatteryHeight   * ui_icnSize ) - 4,
                                  WHITE );

                    }

                    if ( _battery >= 3.83F )
                    {

                        //
                        // 3rd bar
                        //

                        fillRect( ui_icnBatteryStartX   + ( _icnBatteryBarWidth * ui_icnSize * 2 ) + 2,
                                  ui_icnBatteryStartY   + 2,
                                  ( _icnBatteryBarWidth * ui_icnSize ) - 1,
                                  ( _icnBatteryHeight   * ui_icnSize ) - 4,
                                  WHITE );

                    }

                    if ( _battery >= 4.05F )
                    {

                        //
                        // 4th bar
                        //

                        fillRect( ui_icnBatteryStartX   + ( _icnBatteryBarWidth * ui_icnSize * 3 ) + 2,
                                  ui_icnBatteryStartY   + 2,
                                  ( _icnBatteryBarWidth * ui_icnSize ) - 1,
                                  ( _icnBatteryHeight   * ui_icnSize ) - 4,
                                  WHITE );

                    }

                    if ( _battery >= 4.26F )
                    {

                        //
                        // Fully Charged
                        //

                        fillRect( ui_icnBatteryStartX + 1,
                                  ui_icnBatteryStartY + 1,
                                  ( _icnBatteryWidth  * ui_icnSize ) - 2,
                                  ( _icnBatteryHeight * ui_icnSize ) - 2,
                                  WHITE );

                        //
                        // Bolt Symbol
                        //

                        fillTriangle( ui_icnBatteryStartX + ( ui_icnBatteryHalfWidth * ui_icnSize ) - 1,
                                      ui_icnBatteryStartY + ( _icnBatteryHeight      * ui_icnSize ) - ui_icnSize - 1,
                                      ui_icnBatteryStartX + ( ui_icnBatteryHalfWidth + ui_icnBatteryHalfHeight ) * ui_icnSize - 1,
                                      ui_icnBatteryStartY + ( _icnBatteryHeight      - ui_icnBatteryHalfHeight ) * ui_icnSize - ui_icnSize - 1,
                                      ui_icnBatteryStartX + ( ui_icnBatteryHalfWidth * ui_icnSize ) - 1,
                                      ui_icnBatteryStartY + ( _icnBatteryHeight      - ui_icnBatteryHalfHeight ) * ui_icnSize - 1,
                                      BLACK);

                        fillTriangle( ui_icnBatteryStartX + ( ui_icnBatteryHalfWidth - ui_icnBatteryHalfHeight ) * ui_icnSize,
                                      ui_icnBatteryStartY + ( _icnBatteryHeight      - ui_icnBatteryHalfHeight ) * ui_icnSize + ui_icnSize - 1,
                                      ui_icnBatteryStartX + ( ui_icnBatteryHalfWidth * ui_icnSize ),
                                      ui_icnBatteryStartY + ui_icnSize,
                                      ui_icnBatteryStartX + ( ui_icnBatteryHalfWidth * ui_icnSize ) - 1,
                                      ui_icnBatteryStartY + ( _icnBatteryHeight      - ui_icnBatteryHalfHeight ) * ui_icnSize - 1,
                                      BLACK);

                    }
                }

                break;

            case FOLED_BATTERYICON_MINI:

                ui_icnBatteryStartX = _width - ( _icnBatteryMiniWidth * ui_icnSize );



                //
                // Draw the mini ( vertical ) battery icon
                //

                drawLine( ui_icnBatteryStartX,
                          ui_icnBatteryStartY + ui_icnSize,
                          ui_icnBatteryStartX,
                          ui_icnBatteryStartY + ( _icnBatteryMiniHeight * ui_icnSize ) - 1,
                          WHITE );

                drawLine( ui_icnBatteryStartX,
                          ui_icnBatteryStartY + ( _icnBatteryMiniHeight * ui_icnSize ) - 1,
                          ui_icnBatteryStartX + ( _icnBatteryMiniWidth  * ui_icnSize ) - 1,
                          ui_icnBatteryStartY + ( _icnBatteryMiniHeight * ui_icnSize ) - 1,
                          WHITE );

                drawLine( ui_icnBatteryStartX + ( _icnBatteryMiniWidth  * ui_icnSize ) - 1,
                          ui_icnBatteryStartY + ( _icnBatteryMiniHeight * ui_icnSize ) - 1,
                          ui_icnBatteryStartX + ( _icnBatteryMiniWidth  * ui_icnSize ) - 1,
                          ui_icnBatteryStartY + ui_icnSize,
                          WHITE );

                fillRect( ui_icnBatteryStartX    + 1,
                          ui_icnBatteryStartY,
                          ( _icnBatteryMiniWidth * ui_icnSize ) - 2,
                          ui_icnSize             + 1,
                          WHITE );



                //
                // Draw the juice level in the mini vertical battery icon
                //

                if( ui_icnBatteryStartX + 2 < ui_icnBatteryStartX + ( _icnBatteryMiniWidth  * ui_icnSize ) - 3 )
                {

                    fillRect( ui_icnBatteryStartX + 2,
                              ui_icnBatteryStartY + ( _icnBatteryMiniHeight * ui_icnSize ) - 2 -
                              ( int )( ( _icnBatteryMiniHeight * ui_icnSize - 4 - ui_icnSize ) * getBatteryPercentage() * 0.01 + 0.5 ),
                              ( _icnBatteryMiniWidth * ui_icnSize ) - 4,
                              ( int )( ( _icnBatteryMiniHeight * ui_icnSize - 4 - ui_icnSize ) * getBatteryPercentage() * 0.01 + 0.5 ),
                              WHITE );

                }

                break;

            default:
                break;

        }



        s_batText = getBatteryText();


        //
        // Set correct text position
        //

        if ( _batteryIcon == FOLED_BATTERYICON_NONE )
        {

            ui_txtBatteryStartX = _width - getTextBoxWidth( s_batText ) - 1;

        }
        else if ( _batteryIcon == FOLED_BATTERYICON_BARS )
        {

            ui_txtBatteryStartX = ui_icnBatteryStartX - getTextBoxWidth( s_batText ) - 1;

        }
        else if ( _batteryIcon == FOLED_BATTERYICON_MINI )
        {

            ui_txtBatteryStartX = ui_icnBatteryStartX - getTextBoxWidth( s_batText ) - 1;

        }



        //
        // Print text on the OLED display
        //

        setCursor( ui_txtBatteryStartX, ui_txtBatteryStartY );

        println( s_batText );

        setTextSize( ui_originalTxtSize );

    }
}



/******************************************************************************
 *
 *                                                               PUBLIC methods
 *
 ******************************************************************************/



/******************************************************************************/
/*!
    @brief  Get display width
*/
/******************************************************************************/

uint16_t Adafruit_FeatherOLED_Photography::getDisplayWidth ( void )
{
    return _width;      // _width variable is declared in the Adafruit_GFX.h as a property of the Adafruit_GFX object
}



/******************************************************************************/
/*!
    @brief  Get display width
*/
/******************************************************************************/

uint16_t Adafruit_FeatherOLED_Photography::getDisplayHeight ( void )
{
    return _height;     // _height variable is declared in the Adafruit_GFX.h as a property of the Adafruit_GFX object
}



/******************************************************************************/
/*!
    @brief  Get text size
*/
/******************************************************************************/

uint8_t Adafruit_FeatherOLED_Photography::getTextSize ( void )
{
    return textsize;    // textsize variable is declared in the Adafruit_GFX.h as a property of the Adafruit_GFX object
}



/******************************************************************************/
/*!
    @brief  Get icons text size
*/
/******************************************************************************/

uint8_t Adafruit_FeatherOLED_Photography::getIconsSize ( void )
{
    return _iconsSize;
}



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

uint8_t Adafruit_FeatherOLED_Photography::getBatteryIconStyle ( void )
{
    return _batteryIcon;
}



/******************************************************************************/
/*!
    @brief  Get battery text visibility status
*/
/******************************************************************************/

uint8_t Adafruit_FeatherOLED_Photography::getBatteryTextStyle ( void )
{
    return _batteryText;
}



/******************************************************************************/
/*!
    @brief  Set battery icon and descriptive text visibility
*/
/******************************************************************************/

void Adafruit_FeatherOLED_Photography::setIconsSize( uint8_t size )
{
    _iconsSize = ( size > 0 ) ? size : 1;
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

            setBatteryIconStyle( FOLED_BATTERYICON_BARS );

        }

    }
    else
    {

        if( _batteryIcon == FOLED_BATTERYICON_BARS ||
            _batteryText == FOLED_BATTERYTEXT_VOLT ||
            _batteryText == FOLED_BATTERYTEXT_PERC )
        {

            setBatteryIconStyle( FOLED_BATTERYICON_NONE );
            setBatteryTextStyle( FOLED_BATTERYTEXT_NONE );

        }

    }

}



/******************************************************************************/
/*!
    @brief  Set battery icon visibility status and icon type
*/
/******************************************************************************/

void Adafruit_FeatherOLED_Photography::setBatteryIconStyle ( uint8_t enable = FOLED_BATTERYICON_BARS )
{
    _batteryIcon    = enable;
}



/******************************************************************************/
/*!
    @brief  Set battery text visibility status and text formatting
*/
/******************************************************************************/

void Adafruit_FeatherOLED_Photography::setBatteryTextStyle ( uint8_t textType = FOLED_BATTERYTEXT_PERC )
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

    uint8_t ui_icnSize         = getIconsSize();
    uint8_t ui_originalTxtSize = getTextSize();



    //
    // Set text size according to cions size
    //

    setTextSize( getIconsSize() );



    //
    // Erase the canvas
    //

    fillRect( _width - ( _icnBatteryWidth * ui_icnSize ) - max( getTextBoxWidth( getBatteryText() ) - 6 * ui_icnSize, 5 * 6 * ui_icnSize ),
              0,
              _width,
              ( _icnBatteryHeight * ui_icnSize ) + 1,
              BLACK );



    //
    // Render all the icons and controls
    //

    renderBattery();



    //
    // Restore text size
    //

    setTextSize( ui_originalTxtSize );


    //
    // Display on screen
    //

    display();

}



/******************************************************************************/
/*!
    @brief  Clears the message area (the area below the top icons strip) and
            sets the cursor to 0, 8 * getIconsSize()
*/
/******************************************************************************/

void Adafruit_FeatherOLED_Photography::clearMsgArea ( void )
{

  fillRect( 0, 8 * getIconsSize(), 128, _height - getIconsSize(), BLACK);

  setCursor( 0, 8 * getIconsSize() );

  display();

}


