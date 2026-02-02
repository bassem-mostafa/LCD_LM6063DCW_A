// #############################################################################
// #### Copyright ##############################################################
// #############################################################################

/*
 * Copyright 2024 BaSSeM
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

// #############################################################################
// #### Description ############################################################
// #############################################################################

// #############################################################################
// #### Control Include(s) #####################################################
// #############################################################################

// #############################################################################
// #### Control Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#ifndef LCD_LM6063DCW_A_H_
    #define LCD_LM6063DCW_A_H_

    #ifdef __cplusplus
extern "C"
{
    #endif /* __cplusplus */

    // #############################################################################
    // #### Include(s) #############################################################
    // #############################################################################

    // #############################################################################
    // #### Public Macro(s) ########################################################
    // #############################################################################

    #define LCD_LM6063DCW_A_WIDTH  128 // in pixels
    #define LCD_LM6063DCW_A_HEIGHT 64  // in pixels

    // #############################################################################
    // #### Public Type(s) #########################################################
    // #############################################################################

    typedef enum LCD_LM6063DCW_A_Status
    {
        LCD_LM6063DCW_A_Status_Success = 0,
        LCD_LM6063DCW_A_Status_ArgumentInvalid,
        LCD_LM6063DCW_A_Status_NotSupported,
        LCD_LM6063DCW_A_Status_Error,
        LCD_LM6063DCW_A_Status_Busy,
        LCD_LM6063DCW_A_Status_Timeout,
    } LCD_LM6063DCW_A_Status_t;

    typedef enum LCD_LM6063DCW_A_Line
    {
        LCD_LM6063DCW_A_Line_0 = 0,
        LCD_LM6063DCW_A_Line_1,
        LCD_LM6063DCW_A_Line_2,
        LCD_LM6063DCW_A_Line_3,
        LCD_LM6063DCW_A_Line_4,
        LCD_LM6063DCW_A_Line_5,
        LCD_LM6063DCW_A_Line_6,
        LCD_LM6063DCW_A_Line_7,
        LCD_LM6063DCW_A_Line_8,
        LCD_LM6063DCW_A_Line_9,
        LCD_LM6063DCW_A_Line_10,
        LCD_LM6063DCW_A_Line_11,
        LCD_LM6063DCW_A_Line_12,
        LCD_LM6063DCW_A_Line_13,
        LCD_LM6063DCW_A_Line_14,
        LCD_LM6063DCW_A_Line_15,
        LCD_LM6063DCW_A_Line_16,
        LCD_LM6063DCW_A_Line_17,
        LCD_LM6063DCW_A_Line_18,
        LCD_LM6063DCW_A_Line_19,
        LCD_LM6063DCW_A_Line_20,
        LCD_LM6063DCW_A_Line_21,
        LCD_LM6063DCW_A_Line_22,
        LCD_LM6063DCW_A_Line_23,
        LCD_LM6063DCW_A_Line_24,
        LCD_LM6063DCW_A_Line_25,
        LCD_LM6063DCW_A_Line_26,
        LCD_LM6063DCW_A_Line_27,
        LCD_LM6063DCW_A_Line_28,
        LCD_LM6063DCW_A_Line_29,
        LCD_LM6063DCW_A_Line_30,
        LCD_LM6063DCW_A_Line_31,
        LCD_LM6063DCW_A_Line_32,
        LCD_LM6063DCW_A_Line_33,
        LCD_LM6063DCW_A_Line_34,
        LCD_LM6063DCW_A_Line_35,
        LCD_LM6063DCW_A_Line_36,
        LCD_LM6063DCW_A_Line_37,
        LCD_LM6063DCW_A_Line_38,
        LCD_LM6063DCW_A_Line_39,
        LCD_LM6063DCW_A_Line_40,
        LCD_LM6063DCW_A_Line_41,
        LCD_LM6063DCW_A_Line_42,
        LCD_LM6063DCW_A_Line_43,
        LCD_LM6063DCW_A_Line_44,
        LCD_LM6063DCW_A_Line_45,
        LCD_LM6063DCW_A_Line_46,
        LCD_LM6063DCW_A_Line_47,
        LCD_LM6063DCW_A_Line_48,
        LCD_LM6063DCW_A_Line_49,
        LCD_LM6063DCW_A_Line_50,
        LCD_LM6063DCW_A_Line_51,
        LCD_LM6063DCW_A_Line_52,
        LCD_LM6063DCW_A_Line_53,
        LCD_LM6063DCW_A_Line_54,
        LCD_LM6063DCW_A_Line_55,
        LCD_LM6063DCW_A_Line_56,
        LCD_LM6063DCW_A_Line_57,
        LCD_LM6063DCW_A_Line_58,
        LCD_LM6063DCW_A_Line_59,
        LCD_LM6063DCW_A_Line_60,
        LCD_LM6063DCW_A_Line_61,
        LCD_LM6063DCW_A_Line_62,
        LCD_LM6063DCW_A_Line_63,
    } LCD_LM6063DCW_A_Line_t;

    typedef enum LCD_LM6063DCW_A_Page
    {
        LCD_LM6063DCW_A_Page_0 = 0,
        LCD_LM6063DCW_A_Page_1,
        LCD_LM6063DCW_A_Page_2,
        LCD_LM6063DCW_A_Page_3,
        LCD_LM6063DCW_A_Page_4,
        LCD_LM6063DCW_A_Page_5,
        LCD_LM6063DCW_A_Page_6,
        LCD_LM6063DCW_A_Page_7,

        // TODO ...
        LCD_LM6063DCW_A_Page_8,
    } LCD_LM6063DCW_A_Page_t;

    typedef enum LCD_LM6063DCW_A_Column
    {
        LCD_LM6063DCW_A_Column_0 = 0,
        LCD_LM6063DCW_A_Column_1,
        LCD_LM6063DCW_A_Column_2,
        LCD_LM6063DCW_A_Column_3,
        LCD_LM6063DCW_A_Column_4,
        LCD_LM6063DCW_A_Column_5,
        LCD_LM6063DCW_A_Column_6,
        LCD_LM6063DCW_A_Column_7,
        LCD_LM6063DCW_A_Column_8,
        LCD_LM6063DCW_A_Column_9,
        LCD_LM6063DCW_A_Column_10,
        LCD_LM6063DCW_A_Column_11,
        LCD_LM6063DCW_A_Column_12,
        LCD_LM6063DCW_A_Column_13,
        LCD_LM6063DCW_A_Column_14,
        LCD_LM6063DCW_A_Column_15,
        LCD_LM6063DCW_A_Column_16,
        LCD_LM6063DCW_A_Column_17,
        LCD_LM6063DCW_A_Column_18,
        LCD_LM6063DCW_A_Column_19,
        LCD_LM6063DCW_A_Column_20,
        LCD_LM6063DCW_A_Column_21,
        LCD_LM6063DCW_A_Column_22,
        LCD_LM6063DCW_A_Column_23,
        LCD_LM6063DCW_A_Column_24,
        LCD_LM6063DCW_A_Column_25,
        LCD_LM6063DCW_A_Column_26,
        LCD_LM6063DCW_A_Column_27,
        LCD_LM6063DCW_A_Column_28,
        LCD_LM6063DCW_A_Column_29,
        LCD_LM6063DCW_A_Column_30,
        LCD_LM6063DCW_A_Column_31,
        LCD_LM6063DCW_A_Column_32,
        LCD_LM6063DCW_A_Column_33,
        LCD_LM6063DCW_A_Column_34,
        LCD_LM6063DCW_A_Column_35,
        LCD_LM6063DCW_A_Column_36,
        LCD_LM6063DCW_A_Column_37,
        LCD_LM6063DCW_A_Column_38,
        LCD_LM6063DCW_A_Column_39,
        LCD_LM6063DCW_A_Column_40,
        LCD_LM6063DCW_A_Column_41,
        LCD_LM6063DCW_A_Column_42,
        LCD_LM6063DCW_A_Column_43,
        LCD_LM6063DCW_A_Column_44,
        LCD_LM6063DCW_A_Column_45,
        LCD_LM6063DCW_A_Column_46,
        LCD_LM6063DCW_A_Column_47,
        LCD_LM6063DCW_A_Column_48,
        LCD_LM6063DCW_A_Column_49,
        LCD_LM6063DCW_A_Column_50,
        LCD_LM6063DCW_A_Column_51,
        LCD_LM6063DCW_A_Column_52,
        LCD_LM6063DCW_A_Column_53,
        LCD_LM6063DCW_A_Column_54,
        LCD_LM6063DCW_A_Column_55,
        LCD_LM6063DCW_A_Column_56,
        LCD_LM6063DCW_A_Column_57,
        LCD_LM6063DCW_A_Column_58,
        LCD_LM6063DCW_A_Column_59,
        LCD_LM6063DCW_A_Column_60,
        LCD_LM6063DCW_A_Column_61,
        LCD_LM6063DCW_A_Column_62,
        LCD_LM6063DCW_A_Column_63,
        LCD_LM6063DCW_A_Column_64,
        LCD_LM6063DCW_A_Column_65,
        LCD_LM6063DCW_A_Column_66,
        LCD_LM6063DCW_A_Column_67,
        LCD_LM6063DCW_A_Column_68,
        LCD_LM6063DCW_A_Column_69,
        LCD_LM6063DCW_A_Column_70,
        LCD_LM6063DCW_A_Column_71,
        LCD_LM6063DCW_A_Column_72,
        LCD_LM6063DCW_A_Column_73,
        LCD_LM6063DCW_A_Column_74,
        LCD_LM6063DCW_A_Column_75,
        LCD_LM6063DCW_A_Column_76,
        LCD_LM6063DCW_A_Column_77,
        LCD_LM6063DCW_A_Column_78,
        LCD_LM6063DCW_A_Column_79,
        LCD_LM6063DCW_A_Column_80,
        LCD_LM6063DCW_A_Column_81,
        LCD_LM6063DCW_A_Column_82,
        LCD_LM6063DCW_A_Column_83,
        LCD_LM6063DCW_A_Column_84,
        LCD_LM6063DCW_A_Column_85,
        LCD_LM6063DCW_A_Column_86,
        LCD_LM6063DCW_A_Column_87,
        LCD_LM6063DCW_A_Column_88,
        LCD_LM6063DCW_A_Column_89,
        LCD_LM6063DCW_A_Column_90,
        LCD_LM6063DCW_A_Column_91,
        LCD_LM6063DCW_A_Column_92,
        LCD_LM6063DCW_A_Column_93,
        LCD_LM6063DCW_A_Column_94,
        LCD_LM6063DCW_A_Column_95,
        LCD_LM6063DCW_A_Column_96,
        LCD_LM6063DCW_A_Column_97,
        LCD_LM6063DCW_A_Column_98,
        LCD_LM6063DCW_A_Column_99,
        LCD_LM6063DCW_A_Column_100,
        LCD_LM6063DCW_A_Column_101,
        LCD_LM6063DCW_A_Column_102,
        LCD_LM6063DCW_A_Column_103,
        LCD_LM6063DCW_A_Column_104,
        LCD_LM6063DCW_A_Column_105,
        LCD_LM6063DCW_A_Column_106,
        LCD_LM6063DCW_A_Column_107,
        LCD_LM6063DCW_A_Column_108,
        LCD_LM6063DCW_A_Column_109,
        LCD_LM6063DCW_A_Column_110,
        LCD_LM6063DCW_A_Column_111,
        LCD_LM6063DCW_A_Column_112,
        LCD_LM6063DCW_A_Column_113,
        LCD_LM6063DCW_A_Column_114,
        LCD_LM6063DCW_A_Column_115,
        LCD_LM6063DCW_A_Column_116,
        LCD_LM6063DCW_A_Column_117,
        LCD_LM6063DCW_A_Column_118,
        LCD_LM6063DCW_A_Column_119,
        LCD_LM6063DCW_A_Column_120,
        LCD_LM6063DCW_A_Column_121,
        LCD_LM6063DCW_A_Column_122,
        LCD_LM6063DCW_A_Column_123,
        LCD_LM6063DCW_A_Column_124,
        LCD_LM6063DCW_A_Column_125,
        LCD_LM6063DCW_A_Column_126,
        LCD_LM6063DCW_A_Column_127,

        // TODO ...
        LCD_LM6063DCW_A_Column_128,
        LCD_LM6063DCW_A_Column_129,
        LCD_LM6063DCW_A_Column_130,
        LCD_LM6063DCW_A_Column_131,
    } LCD_LM6063DCW_A_Column_t;

    typedef enum LCD_LM6063DCW_A_SEG_Direction
    {
        LCD_LM6063DCW_A_SEG_Direction_Normal = 0,
        LCD_LM6063DCW_A_SEG_Direction_Reverse,
    } LCD_LM6063DCW_A_SEG_Direction_t;

    typedef enum LCD_LM6063DCW_A_DisplayDirection
    {
        LCD_LM6063DCW_A_DisplayDirection_Normal = 0,
        LCD_LM6063DCW_A_DisplayDirection_Inverse,
    } LCD_LM6063DCW_A_DisplayDirection_t;

    typedef enum LCD_LM6063DCW_A_Bias
    {
        LCD_LM6063DCW_A_Bias_1_9 = 0,
        LCD_LM6063DCW_A_Bias_1_7,
    } LCD_LM6063DCW_A_Bias_t;

    typedef enum LCD_LM6063DCW_A_COM_Direction
    {
        LCD_LM6063DCW_A_COM_Direction_Normal = 0,
        LCD_LM6063DCW_A_COM_Direction_Reverse,
    } LCD_LM6063DCW_A_COM_Direction_t;

    typedef enum LCD_LM6063DCW_A_PowerBooster
    {
        LCD_LM6063DCW_A_PowerBooster_Off = 0,
        LCD_LM6063DCW_A_PowerBooster_On,
    } LCD_LM6063DCW_A_PowerBooster_t;

    typedef enum LCD_LM6063DCW_A_PowerRegulator
    {
        LCD_LM6063DCW_A_PowerRegulator_Off = 0,
        LCD_LM6063DCW_A_PowerRegulator_On,
    } LCD_LM6063DCW_A_PowerRegulator_t;

    typedef enum LCD_LM6063DCW_A_PowerFollower
    {
        LCD_LM6063DCW_A_PowerFollower_Off = 0,
        LCD_LM6063DCW_A_PowerFollower_On,
    } LCD_LM6063DCW_A_PowerFollower_t;

    typedef enum LCD_LM6063DCW_A_RegulationRatio
    {
        LCD_LM6063DCW_A_RegulationRatio_3_0 = 0,
        LCD_LM6063DCW_A_RegulationRatio_3_5,
        LCD_LM6063DCW_A_RegulationRatio_4_0,
        LCD_LM6063DCW_A_RegulationRatio_4_5,
        LCD_LM6063DCW_A_RegulationRatio_5_0,
        LCD_LM6063DCW_A_RegulationRatio_5_5,
        LCD_LM6063DCW_A_RegulationRatio_6_0,
        LCD_LM6063DCW_A_RegulationRatio_6_5,
    } LCD_LM6063DCW_A_RegulationRatio_t;

    typedef enum LCD_LM6063DCW_A_ElectronicVolume
    {
        LCD_LM6063DCW_A_ElectronicVolume_0 = 0,
        LCD_LM6063DCW_A_ElectronicVolume_1,
        LCD_LM6063DCW_A_ElectronicVolume_2,
        LCD_LM6063DCW_A_ElectronicVolume_3,
        LCD_LM6063DCW_A_ElectronicVolume_4,
        LCD_LM6063DCW_A_ElectronicVolume_5,
        LCD_LM6063DCW_A_ElectronicVolume_6,
        LCD_LM6063DCW_A_ElectronicVolume_7,
        LCD_LM6063DCW_A_ElectronicVolume_8,
        LCD_LM6063DCW_A_ElectronicVolume_9,
        LCD_LM6063DCW_A_ElectronicVolume_10,
        LCD_LM6063DCW_A_ElectronicVolume_11,
        LCD_LM6063DCW_A_ElectronicVolume_12,
        LCD_LM6063DCW_A_ElectronicVolume_13,
        LCD_LM6063DCW_A_ElectronicVolume_14,
        LCD_LM6063DCW_A_ElectronicVolume_15,
        LCD_LM6063DCW_A_ElectronicVolume_16,
        LCD_LM6063DCW_A_ElectronicVolume_17,
        LCD_LM6063DCW_A_ElectronicVolume_18,
        LCD_LM6063DCW_A_ElectronicVolume_19,
        LCD_LM6063DCW_A_ElectronicVolume_20,
        LCD_LM6063DCW_A_ElectronicVolume_21,
        LCD_LM6063DCW_A_ElectronicVolume_22,
        LCD_LM6063DCW_A_ElectronicVolume_23,
        LCD_LM6063DCW_A_ElectronicVolume_24,
        LCD_LM6063DCW_A_ElectronicVolume_25,
        LCD_LM6063DCW_A_ElectronicVolume_26,
        LCD_LM6063DCW_A_ElectronicVolume_27,
        LCD_LM6063DCW_A_ElectronicVolume_28,
        LCD_LM6063DCW_A_ElectronicVolume_29,
        LCD_LM6063DCW_A_ElectronicVolume_30,
        LCD_LM6063DCW_A_ElectronicVolume_31,
        LCD_LM6063DCW_A_ElectronicVolume_32,
        LCD_LM6063DCW_A_ElectronicVolume_33,
        LCD_LM6063DCW_A_ElectronicVolume_34,
        LCD_LM6063DCW_A_ElectronicVolume_35,
        LCD_LM6063DCW_A_ElectronicVolume_36,
        LCD_LM6063DCW_A_ElectronicVolume_37,
        LCD_LM6063DCW_A_ElectronicVolume_38,
        LCD_LM6063DCW_A_ElectronicVolume_39,
        LCD_LM6063DCW_A_ElectronicVolume_40,
        LCD_LM6063DCW_A_ElectronicVolume_41,
        LCD_LM6063DCW_A_ElectronicVolume_42,
        LCD_LM6063DCW_A_ElectronicVolume_43,
        LCD_LM6063DCW_A_ElectronicVolume_44,
        LCD_LM6063DCW_A_ElectronicVolume_45,
        LCD_LM6063DCW_A_ElectronicVolume_46,
        LCD_LM6063DCW_A_ElectronicVolume_47,
        LCD_LM6063DCW_A_ElectronicVolume_48,
        LCD_LM6063DCW_A_ElectronicVolume_49,
        LCD_LM6063DCW_A_ElectronicVolume_50,
        LCD_LM6063DCW_A_ElectronicVolume_51,
        LCD_LM6063DCW_A_ElectronicVolume_52,
        LCD_LM6063DCW_A_ElectronicVolume_53,
        LCD_LM6063DCW_A_ElectronicVolume_54,
        LCD_LM6063DCW_A_ElectronicVolume_55,
        LCD_LM6063DCW_A_ElectronicVolume_56,
        LCD_LM6063DCW_A_ElectronicVolume_57,
        LCD_LM6063DCW_A_ElectronicVolume_58,
        LCD_LM6063DCW_A_ElectronicVolume_59,
        LCD_LM6063DCW_A_ElectronicVolume_60,
        LCD_LM6063DCW_A_ElectronicVolume_61,
        LCD_LM6063DCW_A_ElectronicVolume_62,
        LCD_LM6063DCW_A_ElectronicVolume_63,
    } LCD_LM6063DCW_A_ElectronicVolume_t;

    typedef enum LCD_LM6063DCW_A_BoosterLevel
    {
        LCD_LM6063DCW_A_BoosterLevel_X4 = 0,
        LCD_LM6063DCW_A_BoosterLevel_X5,
    } LCD_LM6063DCW_A_BoosterLevel_t;

    typedef struct LCD_LM6063DCW_A_Coordinate
    {
        LCD_LM6063DCW_A_Line_t Row;
        LCD_LM6063DCW_A_Column_t Column;
    } LCD_LM6063DCW_A_Coordinate_t;

    typedef uint32_t LCD_LM6063DCW_A_Width_t;

    typedef uint32_t LCD_LM6063DCW_A_Height_t;

    typedef struct LCD_LM6063DCW_A_Size
    {
        LCD_LM6063DCW_A_Width_t Width;
        LCD_LM6063DCW_A_Height_t Height;
    } LCD_LM6063DCW_A_Size_t;

    typedef uint8_t LCD_LM6063DCW_A_Character_t;

    typedef uint8_t LCD_LM6063DCW_A_Pixel_t;

    typedef LCD_LM6063DCW_A_Pixel_t LCD_LM6063DCW_A_Screen_t[ LCD_LM6063DCW_A_HEIGHT ][ LCD_LM6063DCW_A_WIDTH ];

    typedef struct LCD_LM6063DCW_A_Instance_Context LCD_LM6063DCW_A_Instance_Context_t;

    typedef struct LCD_LM6063DCW_A_Instance
    {
        LCD_LM6063DCW_A_t LM6063DCW_A; // FIXME

        SPI_t SPIx;
        GPIO_t ChipSelect;
        GPIO_t RegisterSelect;
        GPIO_t Reset;
        GPIO_t PowerEnable;
        GPIO_t BacklightEnable;

        // Managed internally !
        LCD_LM6063DCW_A_Instance_Context_t * Context;
    } LCD_LM6063DCW_A_Instance_t;

    // #############################################################################
    // #### Public Method(s) #######################################################
    // #############################################################################

    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Initialize( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance );
    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Cycle( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance );
    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_DeInitialize( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance );

    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_IsReady( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance );

    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_GetSize( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance, LCD_LM6063DCW_A_Size_t * LCD_LM6063DCW_A_Size );

    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetCursor( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance, LCD_LM6063DCW_A_Coordinate_t LCD_LM6063DCW_A_Coordinate );

    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Write( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance, LCD_LM6063DCW_A_Character_t LCD_LM6063DCW_A_Character );

    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPixel( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance, LCD_LM6063DCW_A_Coordinate_t LCD_LM6063DCW_A_Coordinate, LCD_LM6063DCW_A_Pixel_t LCD_LM6063DCW_A_Pixel );

    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_GetScreen( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance, LCD_LM6063DCW_A_Screen_t ** LCD_LM6063DCW_A_Screen );

    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Flush( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance );

    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayOn( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance );
    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayOff( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance );
    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetLine( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance, LCD_LM6063DCW_A_Line_t LCD_LM6063DCW_A_Line );
    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPage( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance, LCD_LM6063DCW_A_Page_t LCD_LM6063DCW_A_Page );
    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetColumn( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance, LCD_LM6063DCW_A_Column_t LCD_LM6063DCW_A_Column );
    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetSEGDirection( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance, LCD_LM6063DCW_A_SEG_Direction_t LCD_LM6063DCW_A_SEG_Direction );
    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayDirection( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance, LCD_LM6063DCW_A_DisplayDirection_t LCD_LM6063DCW_A_DisplayDirection );
    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPixelsOn( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance );
    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPixelsOff( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance );
    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetBias( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance, LCD_LM6063DCW_A_Bias_t LCD_LM6063DCW_A_Bias );
    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Reset( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance );
    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetCOMDirection( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance, LCD_LM6063DCW_A_COM_Direction_t LCD_LM6063DCW_A_COM_Direction );
    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPower( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance, LCD_LM6063DCW_A_PowerBooster_t LCD_LM6063DCW_A_PowerBooster, LCD_LM6063DCW_A_PowerRegulator_t LCD_LM6063DCW_A_PowerRegulator, LCD_LM6063DCW_A_PowerFollower_t LCD_LM6063DCW_A_PowerFollower );
    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetRegulationRatio( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance, LCD_LM6063DCW_A_RegulationRatio_t LCD_LM6063DCW_A_RegulationRatio );
    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetElectronicVolume( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance, LCD_LM6063DCW_A_ElectronicVolume_t LCD_LM6063DCW_A_ElectronicVolume );
    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetBoosterLevel( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance, LCD_LM6063DCW_A_BoosterLevel_t LCD_LM6063DCW_A_BoosterLevel );
    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_PowerSaveEnter( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance );
    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_PowerSaveExit( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance );
    LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_NOP( LCD_LM6063DCW_A_Instance_t * LCD_LM6063DCW_A_Instance );

    // TODO Extended Commands

    // #############################################################################
    // #### Public Variable(s) #####################################################
    // #############################################################################

    extern const char LCD_LM6063DCW_A_VERSION[];

    // #############################################################################
    // #### File Guard #############################################################
    // #############################################################################

    #ifdef __cplusplus
} /* extern "C" */
    #endif /* __cplusplus */

#endif /* LCD_LM6063DCW_A_H_ */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
