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

#include "Platform.h"

// #############################################################################
// #### Control Macro(s) #######################################################
// #############################################################################

#ifndef DEBUG
    #define DEBUG
#endif

#ifdef DEBUG
    #undef DEBUG
#endif

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

#include "../../LCD_Internal.h"
#include "LCD_LM6063DCW_A.h"

#include <stddef.h>
#include <stdint.h>

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

#define LCD_LM6063DCW_A_BUFFER_SIZE_TRANSMIT ( 8 )

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef enum LCD_LM6063DCW_A_Command
{
    LCD_LM6063DCW_A_Command_SetDisplay = 0b10101110,            // AE
    LCD_LM6063DCW_A_Command_SetLine = 0b01000000,               // 40
    LCD_LM6063DCW_A_Command_SetPage = 0b10110000,               // B0
    LCD_LM6063DCW_A_Command_SetColumn_1 = 0b00010000,           // 10
    LCD_LM6063DCW_A_Command_SetColumn_2 = 0b00000000,           // 00
    LCD_LM6063DCW_A_Command_SetSEG_Direction = 0b10100000,      // A0
    LCD_LM6063DCW_A_Command_SetDisplayInverse = 0b10100110,     // A6
    LCD_LM6063DCW_A_Command_SetAllPixel = 0b10100100,           // A4
    LCD_LM6063DCW_A_Command_SetBias = 0b10100010,               // A2
    LCD_LM6063DCW_A_Command_Reset = 0b11100010,                 // E2
    LCD_LM6063DCW_A_Command_SetCOM_Direction = 0b11000000,      // C0
    LCD_LM6063DCW_A_Command_SetPowerControl = 0b00101000,       // 28
    LCD_LM6063DCW_A_Command_SetRegulation = 0b00100000,         // 20
    LCD_LM6063DCW_A_Command_SetElectronicVolume_1 = 0b10000001, // 81
    LCD_LM6063DCW_A_Command_SetElectronicVolume_2 = 0b00000000, // 00
    LCD_LM6063DCW_A_Command_SetBooster_1 = 0b11111000,          // F8
    LCD_LM6063DCW_A_Command_SetBooster_2 = 0b00000000,          // 00
    LCD_LM6063DCW_A_Command_NOP = 0b11100011,                   // E3
} LCD_LM6063DCW_A_Command_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetDisplay
{
    const LCD_LM6063DCW_A_Command_t Command[ 1 ];

    struct
    {
        uint8_t State : 1;
        uint8_t       : 7;
    };
} LCD_LM6063DCW_A_SetDisplay_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetLine
{
    const LCD_LM6063DCW_A_Command_t Command[ 1 ];

    struct
    {
        uint8_t Line : 6;
        uint8_t      : 2;
    };
} LCD_LM6063DCW_A_SetLine_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetPage
{
    const LCD_LM6063DCW_A_Command_t Command[ 1 ];

    struct
    {
        uint8_t Page : 4;
        uint8_t      : 4;
    };
} LCD_LM6063DCW_A_SetPage_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetColumn
{
    const LCD_LM6063DCW_A_Command_t Command[ 2 ];

    struct
    {
        uint8_t ColumnMSB : 4;
        uint8_t           : 4;
        uint8_t ColumnLSB : 4;
        uint8_t           : 4;
    };
} LCD_LM6063DCW_A_SetColumn_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetSEG_Direction
{
    const LCD_LM6063DCW_A_Command_t Command[ 1 ];

    struct
    {
        uint8_t Direction : 1;
        uint8_t           : 7;
    };
} LCD_LM6063DCW_A_SetSEG_Direction_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetDisplayInverse
{
    const LCD_LM6063DCW_A_Command_t Command[ 1 ];

    struct
    {
        uint8_t Inverse : 1;
        uint8_t         : 7;
    };
} LCD_LM6063DCW_A_SetDisplayInverse_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetAllPixel
{
    const LCD_LM6063DCW_A_Command_t Command[ 1 ];

    struct
    {
        uint8_t On : 1;
        uint8_t    : 7;
    };
} LCD_LM6063DCW_A_SetAllPixel_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetBias
{
    const LCD_LM6063DCW_A_Command_t Command[ 1 ];

    struct
    {
        uint8_t Bias : 1;
        uint8_t      : 7;
    };
} LCD_LM6063DCW_A_SetBias_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_Reset
{
    const LCD_LM6063DCW_A_Command_t Command[ 1 ];
} LCD_LM6063DCW_A_Reset_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetCOM_Direction
{
    const LCD_LM6063DCW_A_Command_t Command[ 1 ];

    struct
    {
        uint8_t         : 3;
        uint8_t Reverse : 1;
        uint8_t         : 4;
    };
} LCD_LM6063DCW_A_SetCOM_Direction_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetPowerControl
{
    const LCD_LM6063DCW_A_Command_t Command[ 1 ];

    struct
    {
        uint8_t VF : 1;
        uint8_t VR : 1;
        uint8_t VB : 1;
        uint8_t    : 5;
    };
} LCD_LM6063DCW_A_SetPowerControl_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetRegulation
{
    const LCD_LM6063DCW_A_Command_t Command[ 1 ];

    struct
    {
        uint8_t Ratio : 3;
        uint8_t       : 5;
    };
} LCD_LM6063DCW_A_SetRegulation_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetElectronicVolume
{
    const LCD_LM6063DCW_A_Command_t Command[ 2 ];

    struct
    {
        uint8_t       : 8;
        uint8_t Level : 6;
        uint8_t       : 2;
    };
} LCD_LM6063DCW_A_SetElectronicVolume_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetBooster
{
    const LCD_LM6063DCW_A_Command_t Command[ 2 ];

    struct
    {
        uint8_t       : 8;
        uint8_t Level : 1;
        uint8_t       : 7;
    };
} LCD_LM6063DCW_A_SetBooster_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_NOP
{
    const LCD_LM6063DCW_A_Command_t Command[ 1 ];
} LCD_LM6063DCW_A_NOP_t;

typedef enum LCD_LM6063DCW_A_OperationType
{
    LCD_LM6063DCW_A_OperationType_None = 0,

    // Process Pre-Operation
    LCD_LM6063DCW_A_OperationType_Pending,

    // Basic Operation(s)
    LCD_LM6063DCW_A_OperationType_Power_On,
    LCD_LM6063DCW_A_OperationType_Power_Off,

    // General Operation(s)
    LCD_LM6063DCW_A_OperationType_SetDisplayOn,
    LCD_LM6063DCW_A_OperationType_SetDisplayOff,
    LCD_LM6063DCW_A_OperationType_SetLine,
    LCD_LM6063DCW_A_OperationType_SetPage,
    LCD_LM6063DCW_A_OperationType_SetColumn,
    LCD_LM6063DCW_A_OperationType_SetSEG_Direction,
    LCD_LM6063DCW_A_OperationType_SetDisplayDirection,
    LCD_LM6063DCW_A_OperationType_SetPixelsOn,
    LCD_LM6063DCW_A_OperationType_SetPixelsOff,
    LCD_LM6063DCW_A_OperationType_SetBias,
    LCD_LM6063DCW_A_OperationType_Reset,
    LCD_LM6063DCW_A_OperationType_SetCOM_Direction,
    LCD_LM6063DCW_A_OperationType_SetPower,
    LCD_LM6063DCW_A_OperationType_SetRegulationRatio,
    LCD_LM6063DCW_A_OperationType_SetElectronicVolume,
    LCD_LM6063DCW_A_OperationType_SetBoosterLevel,
    LCD_LM6063DCW_A_OperationType_PowerSaveEnter,
    LCD_LM6063DCW_A_OperationType_PowerSaveExit,
    LCD_LM6063DCW_A_OperationType_NOP,

    LCD_LM6063DCW_A_OperationType_Write,
    LCD_LM6063DCW_A_OperationType_Flush,
} LCD_LM6063DCW_A_OperationType_t;

typedef LCD_LM6063DCW_A_Status_t ( *LCD_LM6063DCW_A_OperationHandler_t )( LCD_LM6063DCW_A_Instance_t * Instance );

/**
 * @brief LCD LM6063DCW_A Operation Context
 *
 * @struct LCD_LM6063DCW_A_OperationContext_t
 */
typedef struct LCD_LM6063DCW_A_OperationContext
{
} LCD_LM6063DCW_A_OperationContext_t;

typedef struct LCD_LM6063DCW_A_Operation
{
    LCD_LM6063DCW_A_OperationType_t Type;       ///< Type
    LCD_LM6063DCW_A_OperationHandler_t Handler; ///< Handler
    LCD_LM6063DCW_A_Status_t Status;            ///< Status
    TIM_Timestamp_t Timeout;                    ///< Timeout
    LCD_LM6063DCW_A_OperationContext_t Context; ///< Context

    TIM_Timestamp_t Timestamp;
} LCD_LM6063DCW_A_Operation_t;

typedef enum LCD_LM6063DCW_A_ProcessType
{
    LCD_LM6063DCW_A_ProcessType_None = 0,
    LCD_LM6063DCW_A_ProcessType_Command,
    LCD_LM6063DCW_A_ProcessType_Initialize,
    LCD_LM6063DCW_A_ProcessType_DeInitialize,
    LCD_LM6063DCW_A_ProcessType_TurnOn,
    LCD_LM6063DCW_A_ProcessType_TurnOff,
    LCD_LM6063DCW_A_ProcessType_Flush,
    LCD_LM6063DCW_A_ProcessType_PowerSaveEnter,
    LCD_LM6063DCW_A_ProcessType_PowerSaveExit,
} LCD_LM6063DCW_A_ProcessType_t;

typedef LCD_LM6063DCW_A_Status_t ( *LCD_LM6063DCW_A_Process_Handler_t )( LCD_LM6063DCW_A_Instance_t * Instance );

/**
 * @brief LCD LM6063DCW_A Process Context
 *
 * @struct LCD_LM6063DCW_A_ProcessContext_t
 */
typedef struct LCD_LM6063DCW_A_ProcessContext
{
} LCD_LM6063DCW_A_ProcessContext_t;

typedef struct LCD_LM6063DCW_A_Process
{
    LCD_LM6063DCW_A_ProcessType_t Type;
    LCD_LM6063DCW_A_Process_Handler_t Handler;
    LCD_LM6063DCW_A_ProcessContext_t Context; ///< Context
    LCD_LM6063DCW_A_Status_t Status;
} LCD_LM6063DCW_A_Process_t;

typedef struct LCD_LM6063DCW_A_Buffer_Transmit
{
    uint32_t Length;
    uint8_t Content[ LCD_LM6063DCW_A_BUFFER_SIZE_TRANSMIT ];
} LCD_LM6063DCW_A_Buffer_Transmit_t;

typedef enum LCD_LM6063DCW_A_Event
{
    LCD_LM6063DCW_A_Event_None = 0,
    LCD_LM6063DCW_A_Event_Timeout = UTIL_BIT( 0 ),
    LCD_LM6063DCW_A_Event_SPI_Success = UTIL_BIT( 1 ),
    LCD_LM6063DCW_A_Event_SPI_Error = UTIL_BIT( 2 ),
} LCD_LM6063DCW_A_Event_t;

typedef struct LCD_LM6063DCW_A_Instance_Context
{
    LCD_LM6063DCW_A_Instance_t * Instance; // Owner Instance

    LCD_LM6063DCW_A_Event_t Event;

    LCD_LM6063DCW_A_Process_t Process;
    LCD_LM6063DCW_A_Operation_t Operation; // TODO Move into Process->Context
    LCD_LM6063DCW_A_Screen_t Screen;
    LCD_LM6063DCW_A_Buffer_Transmit_t Transmit;
    LCD_LM6063DCW_A_SEG_Direction_t SEG_Direction;
} LCD_LM6063DCW_A_Instance_Context_t;

typedef struct LCD_LM6063DCW_A_Context
{
    TIM_Timestamp_t Timestamp;
    LCD_LM6063DCW_A_Instance_Context_t Context[ LCD_LM6063DCW_A_Count ];
} LCD_LM6063DCW_A_Context_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

static SPI_Status_t SPI_CallbackOnComplete( SPI_t SPIx, SPI_Status_t Status );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Process_Command_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Process_Initialize_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Process_Flush_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Process_PowerSaveEnter_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Process_PowerSaveExit_Handler( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Process_Set( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_ProcessType_t LCD_LM6063DCW_A_ProcessType );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_GetSize_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Size_t * LCD_LM6063DCW_A_Size );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetCursor_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Coordinate_t LCD_LM6063DCW_A_Coordinate );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Write_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Character_t LCD_LM6063DCW_A_Character );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPixel_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Coordinate_t LCD_LM6063DCW_A_Coordinate, LCD_LM6063DCW_A_Pixel_t LCD_LM6063DCW_A_Pixel );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_GetScreen_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Screen_t ** LCD_LM6063DCW_A_Screen );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Flush_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Flush_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Page_t LCD_LM6063DCW_A_Page );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayOn_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayOn_Execute( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayOff_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayOff_Execute( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetLine_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetLine_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Line_t LCD_LM6063DCW_A_Line );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPage_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPage_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Page_t LCD_LM6063DCW_A_Page );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetColumn_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetColumn_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Column_t LCD_LM6063DCW_A_Column );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetSEG_Direction_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetSEG_Direction_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_SEG_Direction_t LCD_LM6063DCW_A_SEG_Direction );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayDirection_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayDirection_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_DisplayDirection_t LCD_LM6063DCW_A_DisplayDirection );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPixelsOn_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPixelsOn_Execute( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPixelsOff_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPixelsOff_Execute( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetBias_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetBias_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Bias_t LCD_LM6063DCW_A_Bias );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Reset_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Reset_Execute( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetCOM_Direction_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetCOM_Direction_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_COM_Direction_t LCD_LM6063DCW_A_COM_Direction );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPower_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPower_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_PowerBooster_t LCD_LM6063DCW_A_PowerBooster, LCD_LM6063DCW_A_PowerRegulator_t LCD_LM6063DCW_A_PowerRegulator, LCD_LM6063DCW_A_PowerFollower_t LCD_LM6063DCW_A_PowerFollower );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetRegulationRatio_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetRegulationRatio_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_RegulationRatio_t LCD_LM6063DCW_A_RegulationRatio );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetElectronicVolume_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetElectronicVolume_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_ElectronicVolume_t LCD_LM6063DCW_A_ElectronicVolume );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetBoosterLevel_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetBoosterLevel_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_BoosterLevel_t LCD_LM6063DCW_A_BoosterLevel );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_PowerSaveEnter_Execute( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_PowerSaveExit_Execute( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_NOP_Handler( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_NOP_Execute( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_IsIdle( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_IsTimeout( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Delay( LCD_LM6063DCW_A_Instance_t * Instance, uint32_t time_us );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Execute( LCD_LM6063DCW_A_Instance_t * Instance, uint8_t * buffer, uint32_t length );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Transfer( LCD_LM6063DCW_A_Instance_t * Instance, uint8_t * buffer, uint32_t length );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Instance_Initialize( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Instance_Cycle( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Instance_DeInitialize( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Context_Initialize( void );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Context_Cycle( void );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Context_DeInitialize( void );

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

static LCD_LM6063DCW_A_Context_t LCD_LM6063DCW_A_Context;

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

static SPI_Status_t SPI_CallbackOnComplete( SPI_t SPIx, SPI_Status_t Status )
{
    SPI_Status_t SPI_Status = SPI_Status_Success;

    do
    {
        LCD_Debug( "%s( SPIx=%d, Status=%p )", __FUNCTION__, SPIx, Status );

        // FIXME Enhance the following
        LCD_LM6063DCW_A_Instance_Context_t * Context = NULL;
        for ( LCD_LM6063DCW_A_t LCD_LM6063DCW_A_x = LCD_LM6063DCW_A_1; LCD_LM6063DCW_A_x < LCD_LM6063DCW_A_Count; ++LCD_LM6063DCW_A_x )
        {
            Context = &LCD_LM6063DCW_A_Context.Context[ LCD_LM6063DCW_A_x ];
            if ( Context->Instance->SPIx == SPIx )
            {
                break;
            }

            Context = NULL;
        }
        if ( Context == NULL )
        {
            break;
        }

        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Context->Operation;

        switch ( Status )
        {
            case SPI_Status_Success:
                Context->Event |= LCD_LM6063DCW_A_Event_SPI_Success;
                break;

            default:
                Context->Event |= LCD_LM6063DCW_A_Event_SPI_Error;
                break;
        }

        GPIO_Status_t GPIO_Status = GPIO_Status_Success;
        if ( ( GPIO_Status = GPIO_Write( Context->Instance->ChipSelect, GPIO_Value_High ) ) != GPIO_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
    }
    while ( 0 );

    return SPI_Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Process_Command_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Process.Type != LCD_LM6063DCW_A_ProcessType_Command )
        {
            LCD_Error( "Invalid Process Handler, Expected %d Found %d", LCD_LM6063DCW_A_ProcessType_Command, Instance->Context->Process.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
        Status = LCD_LM6063DCW_A_Status_Success;

        if ( LCD_LM6063DCW_A_IsIdle( Instance ) != LCD_LM6063DCW_A_Status_Success )
        {
            // Operation In-progress
            break;
        }
        if ( Instance->Context->Operation.Status != LCD_LM6063DCW_A_Status_Success )
        {
            Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_None;
        }
        switch ( Instance->Context->Operation.Type )
        {
            default:
                Instance->Context->Process.Status = Instance->Context->Operation.Status;
                // TODO OnComplete Callback
                LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
                break;
        }
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Process_Initialize_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Process.Type != LCD_LM6063DCW_A_ProcessType_Initialize )
        {
            LCD_Error( "Invalid Process Handler, Expected %d Found %d", LCD_LM6063DCW_A_ProcessType_Initialize, Instance->Context->Process.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
        Status = LCD_LM6063DCW_A_Status_Success;

        if ( LCD_LM6063DCW_A_IsIdle( Instance ) != LCD_LM6063DCW_A_Status_Success )
        {
            // Operation In-progress
            break;
        }
        if ( Instance->Context->Operation.Status != LCD_LM6063DCW_A_Status_Success )
        {
            Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_None;
        }
        switch ( Instance->Context->Operation.Type )
        {
            case LCD_LM6063DCW_A_OperationType_Pending:
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_Reset_Execute( Instance );
                break;
            case LCD_LM6063DCW_A_OperationType_Reset:
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_SetDisplayOn_Execute( Instance );
                break;
            case LCD_LM6063DCW_A_OperationType_SetDisplayOn:
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_SetLine_Execute( Instance, LCD_LM6063DCW_A_Line_0 );
                break;
            case LCD_LM6063DCW_A_OperationType_SetLine:
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_SetSEG_Direction_Execute( Instance, LCD_LM6063DCW_A_SEG_Direction_Reverse );
                break;
            case LCD_LM6063DCW_A_OperationType_SetSEG_Direction:
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_SetDisplayDirection_Execute( Instance, LCD_LM6063DCW_A_DisplayDirection_Normal );
                break;
            case LCD_LM6063DCW_A_OperationType_SetDisplayDirection:
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_SetPixelsOff_Execute( Instance );
                break;
            case LCD_LM6063DCW_A_OperationType_SetPixelsOff:
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_SetBias_Execute( Instance, LCD_LM6063DCW_A_Bias_1_9 );
                break;
            case LCD_LM6063DCW_A_OperationType_SetBias:
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_SetCOM_Direction_Execute( Instance, LCD_LM6063DCW_A_COM_Direction_Normal );
                break;
            case LCD_LM6063DCW_A_OperationType_SetCOM_Direction:
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_SetPower_Execute( Instance, LCD_LM6063DCW_A_PowerBooster_On, LCD_LM6063DCW_A_PowerRegulator_On, LCD_LM6063DCW_A_PowerFollower_On );
                break;
            case LCD_LM6063DCW_A_OperationType_SetPower:
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_SetRegulationRatio_Execute( Instance, LCD_LM6063DCW_A_RegulationRatio_5_5 );
                break;
            case LCD_LM6063DCW_A_OperationType_SetRegulationRatio:
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_SetBoosterLevel_Execute( Instance, LCD_LM6063DCW_A_BoosterLevel_X4 );
                break;
            case LCD_LM6063DCW_A_OperationType_SetBoosterLevel:
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_SetElectronicVolume_Execute( Instance, LCD_LM6063DCW_A_ElectronicVolume_33 );
                break;
            case LCD_LM6063DCW_A_OperationType_SetElectronicVolume:
            case LCD_LM6063DCW_A_OperationType_None:
            default:
                Instance->Context->Process.Status = Instance->Context->Operation.Status;
                // TODO OnComplete Callback
                // Initialization followed by flush process
                LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Flush );
                break;
        }
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Process_Flush_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Process.Type != LCD_LM6063DCW_A_ProcessType_Flush )
        {
            LCD_Error( "Invalid Process Handler, Expected %d Found %d", LCD_LM6063DCW_A_ProcessType_Flush, Instance->Context->Process.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
        Status = LCD_LM6063DCW_A_Status_Success;

        if ( LCD_LM6063DCW_A_IsIdle( Instance ) != LCD_LM6063DCW_A_Status_Success )
        {
            // Operation In-progress
            break;
        }
        if ( Instance->Context->Operation.Status != LCD_LM6063DCW_A_Status_Success )
        {
            Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_None;
        }
        // FIXME let this workaround be more efficient
        static LCD_LM6063DCW_A_Page_t LCD_LM6063DCW_A_Page = LCD_LM6063DCW_A_Page_0;
        switch ( Instance->Context->Operation.Type )
        {
            case LCD_LM6063DCW_A_OperationType_Pending:
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_SetPage_Execute( Instance, LCD_LM6063DCW_A_Page );
                break;
            case LCD_LM6063DCW_A_OperationType_SetPage:
                // FIX align with the visual pixels
                switch ( Instance->Context->SEG_Direction )
                {
                    case LCD_LM6063DCW_A_SEG_Direction_Normal:
                        Instance->Context->Operation.Status = LCD_LM6063DCW_A_SetColumn_Execute( Instance, LCD_LM6063DCW_A_Column_4 );
                        break;
                    case LCD_LM6063DCW_A_SEG_Direction_Reverse:
                    default:
                        Instance->Context->Operation.Status = LCD_LM6063DCW_A_SetColumn_Execute( Instance, LCD_LM6063DCW_A_Column_0 );
                        break;
                }
                break;
            case LCD_LM6063DCW_A_OperationType_SetColumn:
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_Flush_Execute( Instance, LCD_LM6063DCW_A_Page );
                break;
            case LCD_LM6063DCW_A_OperationType_Flush:
                if ( LCD_LM6063DCW_A_Page >= LCD_LM6063DCW_A_Page_8 )
                {
                    LCD_LM6063DCW_A_Page = LCD_LM6063DCW_A_Page_0;
                    // no break
                }
                else
                {
                    // Start flush again for the next page
                    LCD_LM6063DCW_A_Page++;
                    Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_Pending;
                    break;
                }
            case LCD_LM6063DCW_A_OperationType_None:
            default:
                Instance->Context->Process.Status = Instance->Context->Operation.Status;
                // TODO OnComplete Callback
                LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
                break;
        }
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Process_PowerSaveEnter_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Process.Type != LCD_LM6063DCW_A_ProcessType_PowerSaveEnter )
        {
            LCD_Error( "Invalid Process Handler, Expected %d Found %d", LCD_LM6063DCW_A_ProcessType_PowerSaveEnter, Instance->Context->Process.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
        switch ( Instance->Context->Operation.Type )
        {
            case LCD_LM6063DCW_A_OperationType_Pending:
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_SetDisplayOff_Execute( Instance );
                break;
            case LCD_LM6063DCW_A_OperationType_SetDisplayOff:
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_SetPixelsOn_Execute( Instance );
                break;
            case LCD_LM6063DCW_A_OperationType_SetPixelsOn:
            case LCD_LM6063DCW_A_OperationType_None:
            default:
                LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
                break;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Process_PowerSaveExit_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Process.Type != LCD_LM6063DCW_A_ProcessType_PowerSaveExit )
        {
            LCD_Error( "Invalid Process Handler, Expected %d Found %d", LCD_LM6063DCW_A_ProcessType_PowerSaveExit, Instance->Context->Process.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
        switch ( Instance->Context->Operation.Type )
        {
            case LCD_LM6063DCW_A_OperationType_Pending:
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_SetPixelsOff_Execute( Instance );
                break;
            case LCD_LM6063DCW_A_OperationType_SetPixelsOff:
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_SetDisplayOn_Execute( Instance );
                break;
            case LCD_LM6063DCW_A_OperationType_SetDisplayOn:
            case LCD_LM6063DCW_A_OperationType_None:
            default:
                LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
                break;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Process_Set( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_ProcessType_t LCD_LM6063DCW_A_ProcessType )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        Instance->Context->Process.Type = LCD_LM6063DCW_A_ProcessType;
        Instance->Context->Process.Status = LCD_LM6063DCW_A_Status_Success;
        switch ( Instance->Context->Process.Type )
        {
            case LCD_LM6063DCW_A_ProcessType_Command:
                Instance->Context->Process.Handler = LCD_LM6063DCW_A_Process_Command_Handler;
                break;
            case LCD_LM6063DCW_A_ProcessType_Initialize:
                Instance->Context->Process.Handler = LCD_LM6063DCW_A_Process_Initialize_Handler;
                break;
            case LCD_LM6063DCW_A_ProcessType_Flush:
                Instance->Context->Process.Handler = LCD_LM6063DCW_A_Process_Flush_Handler;
                break;
            case LCD_LM6063DCW_A_ProcessType_PowerSaveEnter:
                Instance->Context->Process.Handler = LCD_LM6063DCW_A_Process_PowerSaveEnter_Handler;
                break;
            case LCD_LM6063DCW_A_ProcessType_PowerSaveExit:
                Instance->Context->Process.Handler = LCD_LM6063DCW_A_Process_PowerSaveExit_Handler;
                break;
            case LCD_LM6063DCW_A_ProcessType_None:
            default:
                Instance->Context->Process.Handler = NULL;
                if ( Instance->Context->Process.Type != LCD_LM6063DCW_A_ProcessType_None )
                {
                    Instance->Context->Process.Type = LCD_LM6063DCW_A_ProcessType_None;
                    LCD_Warning( "Un-Handled Process Setting" );
                }
                break;
        }
        switch ( Instance->Context->Process.Type )
        {
            case LCD_LM6063DCW_A_ProcessType_Command:
                // Externally Handled Operation
                break;
            case LCD_LM6063DCW_A_ProcessType_None:
                Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_None;
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
                break;
            default:
                Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_Pending;
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
                break;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_GetSize_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Size_t * LCD_LM6063DCW_A_Size )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p, Size=%p )", __FUNCTION__, Instance, LCD_LM6063DCW_A_Size );
        if ( LCD_LM6063DCW_A_Size == NULL )
        {
            Status = LCD_LM6063DCW_A_Status_ArgumentInvalid;
            break;
        }

        LCD_LM6063DCW_A_Size->Height = LCD_LM6063DCW_A_HEIGHT;
        LCD_LM6063DCW_A_Size->Width = LCD_LM6063DCW_A_WIDTH;
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetCursor_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Coordinate_t LCD_LM6063DCW_A_Coordinate )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p, Coordinate={Row=%d, Column=%d} )", __FUNCTION__, Instance, LCD_LM6063DCW_A_Coordinate.Row, LCD_LM6063DCW_A_Coordinate.Column );
        //    if ( LCD_LM6063DCW_A_Coordinate.Row < 0
        //      || LCD_LM6063DCW_A_Coordinate.Row > LCD_LM6063DCW_A_HEIGHT
        //      || LCD_LM6063DCW_A_Coordinate.Column < 0
        //      || LCD_LM6063DCW_A_Coordinate.Column > LCD_LM6063DCW_A_WIDTH )
        //    {
        //      Status = LCD_LM6063DCW_A_Status_ArgumentInvalid;
        //      break;
        //    }

        // TODO
        Status = LCD_LM6063DCW_A_Status_NotSupported;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Write_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Character_t LCD_LM6063DCW_A_Character )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p, Character=%02X )", __FUNCTION__, Instance, LCD_LM6063DCW_A_Character );

        // TODO
        Status = LCD_LM6063DCW_A_Status_NotSupported;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPixel_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Coordinate_t LCD_LM6063DCW_A_Coordinate, LCD_LM6063DCW_A_Pixel_t LCD_LM6063DCW_A_Pixel )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p, Coordinate={Row=%d, Column=%d}, Pixel=%02X )", __FUNCTION__, Instance, LCD_LM6063DCW_A_Coordinate.Row, LCD_LM6063DCW_A_Coordinate.Column, LCD_LM6063DCW_A_Pixel );
        if ( LCD_LM6063DCW_A_Coordinate.Row < 0
             || LCD_LM6063DCW_A_Coordinate.Row >= LCD_LM6063DCW_A_HEIGHT
             || LCD_LM6063DCW_A_Coordinate.Column < 0
             || LCD_LM6063DCW_A_Coordinate.Column >= LCD_LM6063DCW_A_WIDTH )
        {
            Status = LCD_LM6063DCW_A_Status_ArgumentInvalid;
            break;
        }

        Instance->Context->Screen[ LCD_LM6063DCW_A_Coordinate.Row ][ LCD_LM6063DCW_A_Coordinate.Column ] = LCD_LM6063DCW_A_Pixel;
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_GetScreen_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Screen_t ** LCD_LM6063DCW_A_Screen )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p, Screen=%p )", __FUNCTION__, Instance, LCD_LM6063DCW_A_Screen );
        if ( LCD_LM6063DCW_A_Screen == NULL )
        {
            Status = LCD_LM6063DCW_A_Status_ArgumentInvalid;
            break;
        }

        *LCD_LM6063DCW_A_Screen = &Instance->Context->Screen;
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Flush_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_Flush )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_Flush, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            Instance->Context->Operation.Status = Status;
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_IsTimeout( Instance ) ) == LCD_LM6063DCW_A_Status_Success )
        {
            Instance->Context->Operation.Handler = NULL;
            Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success; // FIXME
        }
        // TODO Verify SPI Status
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Flush_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Page_t LCD_LM6063DCW_A_Page )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        // FIXME let this workaround be more efficient
        static uint8_t ScreenPage[ LCD_LM6063DCW_A_WIDTH ];
        for ( uint32_t column = 0; column < LCD_LM6063DCW_A_WIDTH; ++column )
        {
            ScreenPage[ column ] = 0x00;
            for ( uint32_t line = 0; line < 8; ++line )
            {
                ScreenPage[ column ] |= Instance->Context->Screen[ LCD_LM6063DCW_A_Page * 8 + line ][ column ] << line;
            }
        }
        if ( ( Status = LCD_LM6063DCW_A_Transfer( Instance, ScreenPage, LCD_LM6063DCW_A_WIDTH ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_Flush;
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_Flush_Handler;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 1 ); // FIXME Set Appropriate Delay Value
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayOn_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_SetDisplayOn )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_SetDisplayOn, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            Instance->Context->Operation.Status = Status;
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_IsTimeout( Instance ) ) == LCD_LM6063DCW_A_Status_Success )
        {
            Instance->Context->Operation.Handler = NULL;
            Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayOn_Execute( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_SetDisplay_t LCD_LM6063DCW_A_SetDisplay = { { LCD_LM6063DCW_A_Command_SetDisplay } };
        LCD_LM6063DCW_A_SetDisplay.State = 1;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &LCD_LM6063DCW_A_SetDisplay, UTIL_SizeOf( LCD_LM6063DCW_A_SetDisplay ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_SetDisplayOn;
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_SetDisplayOn_Handler;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 1 ); // FIXME Set Appropriate Delay Value
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayOff_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_SetDisplayOff )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_SetDisplayOff, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            Instance->Context->Operation.Status = Status;
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_IsTimeout( Instance ) ) == LCD_LM6063DCW_A_Status_Success )
        {
            Instance->Context->Operation.Handler = NULL;
            Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayOff_Execute( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_SetDisplay_t LCD_LM6063DCW_A_SetDisplay = { { LCD_LM6063DCW_A_Command_SetDisplay } };
        LCD_LM6063DCW_A_SetDisplay.State = 0;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &LCD_LM6063DCW_A_SetDisplay, UTIL_SizeOf( LCD_LM6063DCW_A_SetDisplay ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_SetDisplayOff;
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_SetDisplayOff_Handler;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 1 ); // FIXME Set Appropriate Delay Value
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetLine_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_SetLine )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_SetLine, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            Instance->Context->Operation.Status = Status;
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_IsTimeout( Instance ) ) == LCD_LM6063DCW_A_Status_Success )
        {
            Instance->Context->Operation.Handler = NULL;
            Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetLine_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Line_t LCD_LM6063DCW_A_Line )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_SetLine_t LCD_LM6063DCW_A_SetLine = { { LCD_LM6063DCW_A_Command_SetLine } };
        LCD_LM6063DCW_A_SetLine.Line = LCD_LM6063DCW_A_Line;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &LCD_LM6063DCW_A_SetLine, UTIL_SizeOf( LCD_LM6063DCW_A_SetLine ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_SetLine;
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_SetLine_Handler;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 1 ); // FIXME Set Appropriate Delay Value
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPage_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_SetPage )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_SetPage, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            Instance->Context->Operation.Status = Status;
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_IsTimeout( Instance ) ) == LCD_LM6063DCW_A_Status_Success )
        {
            Instance->Context->Operation.Handler = NULL;
            Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPage_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Page_t LCD_LM6063DCW_A_Page )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_SetPage_t LCD_LM6063DCW_A_SetPage = { { LCD_LM6063DCW_A_Command_SetPage } };
        LCD_LM6063DCW_A_SetPage.Page = LCD_LM6063DCW_A_Page;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &LCD_LM6063DCW_A_SetPage, UTIL_SizeOf( LCD_LM6063DCW_A_SetPage ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_SetPage;
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_SetPage_Handler;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 1 ); // FIXME Set Appropriate Delay Value
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetColumn_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_SetColumn )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_SetColumn, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            Instance->Context->Operation.Status = Status;
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_IsTimeout( Instance ) ) == LCD_LM6063DCW_A_Status_Success )
        {
            Instance->Context->Operation.Handler = NULL;
            Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetColumn_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Column_t LCD_LM6063DCW_A_Column )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_SetColumn_t LCD_LM6063DCW_A_SetColumn = {
            { LCD_LM6063DCW_A_Command_SetColumn_1, LCD_LM6063DCW_A_Command_SetColumn_2 }
        };
        LCD_LM6063DCW_A_SetColumn.ColumnMSB = ( LCD_LM6063DCW_A_Column & 0xF0 ) >> 4;
        LCD_LM6063DCW_A_SetColumn.ColumnLSB = ( LCD_LM6063DCW_A_Column & 0x0F ) >> 0;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &LCD_LM6063DCW_A_SetColumn, UTIL_SizeOf( LCD_LM6063DCW_A_SetColumn ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_SetColumn;
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_SetColumn_Handler;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 1 ); // FIXME Set Appropriate Delay Value
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetSEG_Direction_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_SetSEG_Direction )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_SetSEG_Direction, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            Instance->Context->Operation.Status = Status;
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_IsTimeout( Instance ) ) == LCD_LM6063DCW_A_Status_Success )
        {
            Instance->Context->Operation.Handler = NULL;
            Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetSEG_Direction_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_SEG_Direction_t LCD_LM6063DCW_A_SEG_Direction )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_SetSEG_Direction_t LCD_LM6063DCW_A_SetSEG_Direction = { { LCD_LM6063DCW_A_Command_SetSEG_Direction } };
        LCD_LM6063DCW_A_SetSEG_Direction.Direction = LCD_LM6063DCW_A_SEG_Direction;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &LCD_LM6063DCW_A_SetSEG_Direction, UTIL_SizeOf( LCD_LM6063DCW_A_SetSEG_Direction ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        // Update SEG_Direction
        Instance->Context->SEG_Direction = LCD_LM6063DCW_A_SEG_Direction;

        Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_SetSEG_Direction;
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_SetSEG_Direction_Handler;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 1 ); // FIXME Set Appropriate Delay Value
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayDirection_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_SetDisplayDirection )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_SetDisplayDirection, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            Instance->Context->Operation.Status = Status;
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_IsTimeout( Instance ) ) == LCD_LM6063DCW_A_Status_Success )
        {
            Instance->Context->Operation.Handler = NULL;
            Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayDirection_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_DisplayDirection_t LCD_LM6063DCW_A_DisplayDirection )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        LCD_LM6063DCW_A_SetDisplayInverse_t LCD_LM6063DCW_A_SetDisplayInverse = { { LCD_LM6063DCW_A_Command_SetDisplayInverse } };
        LCD_LM6063DCW_A_SetDisplayInverse.Inverse = LCD_LM6063DCW_A_DisplayDirection;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &LCD_LM6063DCW_A_SetDisplayInverse, UTIL_SizeOf( LCD_LM6063DCW_A_SetDisplayInverse ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_SetDisplayDirection;
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_SetDisplayDirection_Handler;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 1 ); // FIXME Set Appropriate Delay Value
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPixelsOn_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_SetPixelsOn )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_SetPixelsOn, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            Instance->Context->Operation.Status = Status;
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_IsTimeout( Instance ) ) == LCD_LM6063DCW_A_Status_Success )
        {
            Instance->Context->Operation.Handler = NULL;
            Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPixelsOn_Execute( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        LCD_LM6063DCW_A_SetAllPixel_t LCD_LM6063DCW_A_SetAllPixel = { { LCD_LM6063DCW_A_Command_SetAllPixel } };
        LCD_LM6063DCW_A_SetAllPixel.On = 1;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &LCD_LM6063DCW_A_SetAllPixel, UTIL_SizeOf( LCD_LM6063DCW_A_SetAllPixel ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_SetPixelsOn;
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_SetPixelsOn_Handler;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 1 ); // FIXME Set Appropriate Delay Value
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPixelsOff_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_SetPixelsOff )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_SetPixelsOff, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            Instance->Context->Operation.Status = Status;
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_IsTimeout( Instance ) ) == LCD_LM6063DCW_A_Status_Success )
        {
            Instance->Context->Operation.Handler = NULL;
            Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPixelsOff_Execute( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_SetAllPixel_t LCD_LM6063DCW_A_SetAllPixel = { { LCD_LM6063DCW_A_Command_SetAllPixel } };
        LCD_LM6063DCW_A_SetAllPixel.On = 0;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &LCD_LM6063DCW_A_SetAllPixel, UTIL_SizeOf( LCD_LM6063DCW_A_SetAllPixel ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_SetPixelsOff;
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_SetPixelsOff_Handler;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 1 ); // FIXME Set Appropriate Delay Value
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetBias_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_SetBias )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_SetBias, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            Instance->Context->Operation.Status = Status;
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_IsTimeout( Instance ) ) == LCD_LM6063DCW_A_Status_Success )
        {
            Instance->Context->Operation.Handler = NULL;
            Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetBias_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Bias_t LCD_LM6063DCW_A_Bias )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_SetBias_t LCD_LM6063DCW_A_SetBias = { { LCD_LM6063DCW_A_Command_SetBias } };
        LCD_LM6063DCW_A_SetBias.Bias = LCD_LM6063DCW_A_Bias;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &LCD_LM6063DCW_A_SetBias, UTIL_SizeOf( LCD_LM6063DCW_A_SetBias ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_SetBias;
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_SetBias_Handler;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 1 ); // FIXME Set Appropriate Delay Value
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Reset_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_Reset )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_Reset, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            Instance->Context->Operation.Status = Status;
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_IsTimeout( Instance ) ) == LCD_LM6063DCW_A_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Success;
            GPIO_Status_t GPIO_Status = GPIO_Status_Error;
            if ( ( GPIO_Status = GPIO_Write( Instance->Reset, GPIO_Value_High ) ) != GPIO_Status_Success )
            {
                Status = LCD_LM6063DCW_A_Status_Error;
            }
            Instance->Context->Operation.Handler = NULL;
            Instance->Context->Operation.Status = Status;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Reset_Execute( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

#if 0
    LCD_LM6063DCW_A_Reset_t LCD_LM6063DCW_A_Reset = { { LCD_LM6063DCW_A_Command_Reset } };
    if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t* )&LCD_LM6063DCW_A_Reset, UTIL_SizeOf( LCD_LM6063DCW_A_Reset ) ) ) != LCD_LM6063DCW_A_Status_Success )
    {
      break;
    }
#else
        GPIO_Status_t GPIO_Status = GPIO_Status_Error;
        if ( ( GPIO_Status = GPIO_Write( Instance->Reset, GPIO_Value_Low ) ) != GPIO_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
#endif
        Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_Reset;
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_Reset_Handler;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 1 ); // FIXME Set Appropriate Delay Value
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetCOM_Direction_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_SetCOM_Direction )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_SetCOM_Direction, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            Instance->Context->Operation.Status = Status;
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_IsTimeout( Instance ) ) == LCD_LM6063DCW_A_Status_Success )
        {
            Instance->Context->Operation.Handler = NULL;
            Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetCOM_Direction_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_COM_Direction_t LCD_LM6063DCW_A_COM_Direction )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_SetCOM_Direction_t LCD_LM6063DCW_A_SetCOM_Direction = { { LCD_LM6063DCW_A_Command_SetCOM_Direction } };
        LCD_LM6063DCW_A_SetCOM_Direction.Reverse = LCD_LM6063DCW_A_COM_Direction;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &LCD_LM6063DCW_A_SetCOM_Direction, UTIL_SizeOf( LCD_LM6063DCW_A_SetCOM_Direction ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_SetCOM_Direction;
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_SetCOM_Direction_Handler;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 1 ); // FIXME Set Appropriate Delay Value
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPower_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_SetPower )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_SetPower, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            Instance->Context->Operation.Status = Status;
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_IsTimeout( Instance ) ) == LCD_LM6063DCW_A_Status_Success )
        {
            Instance->Context->Operation.Handler = NULL;
            Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPower_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_PowerBooster_t LCD_LM6063DCW_A_PowerBooster, LCD_LM6063DCW_A_PowerRegulator_t LCD_LM6063DCW_A_PowerRegulator, LCD_LM6063DCW_A_PowerFollower_t LCD_LM6063DCW_A_PowerFollower )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_SetPowerControl_t LCD_LM6063DCW_A_SetPowerControl = { { LCD_LM6063DCW_A_Command_SetPowerControl } };
        LCD_LM6063DCW_A_SetPowerControl.VB = LCD_LM6063DCW_A_PowerBooster;
        LCD_LM6063DCW_A_SetPowerControl.VR = LCD_LM6063DCW_A_PowerRegulator;
        LCD_LM6063DCW_A_SetPowerControl.VF = LCD_LM6063DCW_A_PowerFollower;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &LCD_LM6063DCW_A_SetPowerControl, UTIL_SizeOf( LCD_LM6063DCW_A_SetPowerControl ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_SetPower;
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_SetPower_Handler;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 1 ); // FIXME Set Appropriate Delay Value
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetRegulationRatio_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_SetRegulationRatio )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_SetRegulationRatio, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            Instance->Context->Operation.Status = Status;
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_IsTimeout( Instance ) ) == LCD_LM6063DCW_A_Status_Success )
        {
            Instance->Context->Operation.Handler = NULL;
            Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetRegulationRatio_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_RegulationRatio_t LCD_LM6063DCW_A_RegulationRatio )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_SetRegulation_t LCD_LM6063DCW_A_SetRegulation = { { LCD_LM6063DCW_A_Command_SetRegulation } };
        LCD_LM6063DCW_A_SetRegulation.Ratio = LCD_LM6063DCW_A_RegulationRatio;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &LCD_LM6063DCW_A_SetRegulation, UTIL_SizeOf( LCD_LM6063DCW_A_SetRegulation ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_SetRegulationRatio;
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_SetRegulationRatio_Handler;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 1 ); // FIXME Set Appropriate Delay Value
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetElectronicVolume_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_SetElectronicVolume )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_SetElectronicVolume, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            Instance->Context->Operation.Status = Status;
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_IsTimeout( Instance ) ) == LCD_LM6063DCW_A_Status_Success )
        {
            Instance->Context->Operation.Handler = NULL;
            Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetElectronicVolume_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_ElectronicVolume_t LCD_LM6063DCW_A_ElectronicVolume )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_SetElectronicVolume_t LCD_LM6063DCW_A_SetElectronicVolume = {
            { LCD_LM6063DCW_A_Command_SetElectronicVolume_1, LCD_LM6063DCW_A_Command_SetElectronicVolume_2 }
        };
        LCD_LM6063DCW_A_SetElectronicVolume.Level = LCD_LM6063DCW_A_ElectronicVolume;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &LCD_LM6063DCW_A_SetElectronicVolume, UTIL_SizeOf( LCD_LM6063DCW_A_SetElectronicVolume ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_SetElectronicVolume;
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_SetElectronicVolume_Handler;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 1 ); // FIXME Set Appropriate Delay Value
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetBoosterLevel_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_SetBoosterLevel )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_SetBoosterLevel, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            Instance->Context->Operation.Status = Status;
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_IsTimeout( Instance ) ) == LCD_LM6063DCW_A_Status_Success )
        {
            Instance->Context->Operation.Handler = NULL;
            Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetBoosterLevel_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_BoosterLevel_t LCD_LM6063DCW_A_BoosterLevel )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        LCD_LM6063DCW_A_SetBooster_t LCD_LM6063DCW_A_SetBooster = {
            { LCD_LM6063DCW_A_Command_SetBooster_1, LCD_LM6063DCW_A_Command_SetBooster_2 }
        };
        LCD_LM6063DCW_A_SetBooster.Level = LCD_LM6063DCW_A_BoosterLevel;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &LCD_LM6063DCW_A_SetBooster, UTIL_SizeOf( LCD_LM6063DCW_A_SetBooster ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_SetBoosterLevel;
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_SetBoosterLevel_Handler;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 1 ); // FIXME Set Appropriate Delay Value
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_PowerSaveEnter_Execute( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_PowerSaveEnter );
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_PowerSaveExit_Execute( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_PowerSaveExit );
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_NOP_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_NOP )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_NOP, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            Instance->Context->Operation.Status = Status;
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_IsTimeout( Instance ) ) == LCD_LM6063DCW_A_Status_Success )
        {
            Instance->Context->Operation.Handler = NULL;
            Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_NOP_Execute( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        LCD_LM6063DCW_A_NOP_t LCD_LM6063DCW_A_NOP = { { LCD_LM6063DCW_A_Command_NOP } };
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &LCD_LM6063DCW_A_NOP, UTIL_SizeOf( LCD_LM6063DCW_A_NOP ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Instance->Context->Operation.Type = LCD_LM6063DCW_A_OperationType_NOP;
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_NOP_Handler;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 1 ); // FIXME Set Appropriate Delay Value
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_IsIdle( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( Instance->Context->Operation.Handler != NULL )
        {
            Status = LCD_LM6063DCW_A_Status_Busy;
            break;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_IsTimeout( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_IsExpiredTimestamp( LCD_TIM, &Instance->Context->Operation.Timestamp ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Busy;
            break;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Delay( LCD_LM6063DCW_A_Instance_t * Instance, uint32_t time_ms )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_Timestamp_AddMillisecond( &Instance->Context->Operation.Timestamp, time_ms ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Execute( LCD_LM6063DCW_A_Instance_t * Instance, uint8_t * buffer, uint32_t length )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        GPIO_Status_t GPIO_Status = GPIO_Status_Error;
        if ( ( GPIO_Status = GPIO_Write( Instance->RegisterSelect, GPIO_Value_Low ) ) != GPIO_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
        SPI_Status_t SPI_Status = SPI_Status_Error;
        if ( ( GPIO_Status = GPIO_Write( Instance->ChipSelect, GPIO_Value_Low ) ) != GPIO_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
        if ( ( SPI_Status = SPI_Write( Instance->SPIx, buffer, length ) ) != SPI_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Transfer( LCD_LM6063DCW_A_Instance_t * Instance, uint8_t * buffer, uint32_t length )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        GPIO_Status_t GPIO_Status = GPIO_Status_Error;
        if ( ( GPIO_Status = GPIO_Write( Instance->RegisterSelect, GPIO_Value_High ) ) != GPIO_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
        if ( ( GPIO_Status = GPIO_Write( Instance->ChipSelect, GPIO_Value_Low ) ) != GPIO_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
        SPI_Status_t SPI_Status = SPI_Status_Error;
        if ( ( SPI_Status = SPI_Write( Instance->SPIx, buffer, length ) ) != SPI_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Instance_Initialize( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        // TODO GPIOs Configuration

        SPI_Status_t SPI_Status = SPI_Status_Success;
        if ( ( SPI_Status = SPI_SetCallbackOnComplete( Instance->SPIx, SPI_CallbackOnComplete ) ) != SPI_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        LCD_LM6063DCW_A_Instance_Context_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];

        UTIL_MemorySetZero( Context->Screen, UTIL_SizeOf( Context->Screen ) );

        Context->Transmit.Length = 0;
        Context->Transmit.Content[ Context->Transmit.Length ] = 0;

        Context->Operation.Type = LCD_LM6063DCW_A_OperationType_None;
        Context->Operation.Handler = NULL;
        Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;

        Context->Process.Type = LCD_LM6063DCW_A_ProcessType_None;
        Context->Process.Handler = NULL;
        Context->Process.Status = LCD_LM6063DCW_A_Status_Success;

        Context->SEG_Direction = LCD_LM6063DCW_A_SEG_Direction_Reverse;

        Instance->Context = Context;

        Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Initialize );
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Instance_Cycle( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Operation.Handler != NULL )
        {
            if ( ( Status = Instance->Context->Operation.Handler( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
            {
                // FIXME
            }
        }
        if ( Instance->Context->Process.Handler != NULL )
        {
            if ( ( Status = Instance->Context->Process.Handler( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
            {
                // FIXME
            }
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Instance_DeInitialize( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_DeInitialize ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Context_Initialize( void )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( void )", __FUNCTION__ );
        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_GetTimestamp( LCD_TIM, &LCD_LM6063DCW_A_Context.Timestamp ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Context_Cycle( void )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( void )", __FUNCTION__ );
        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_GetTimestamp( LCD_TIM, &LCD_LM6063DCW_A_Context.Timestamp ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Context_DeInitialize( void )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( void )", __FUNCTION__ );
        // Nothing to be done
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Initialize( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_Context_Initialize( ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_Instance_Initialize( Instance );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Cycle( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_Context_Cycle( ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_Instance_Cycle( Instance );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_DeInitialize( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_Instance_DeInitialize( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_Context_DeInitialize( );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_IsReady( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Process.Type != LCD_LM6063DCW_A_ProcessType_None
             || Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_None )
        {
            Status = LCD_LM6063DCW_A_Status_Busy;
            break;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_GetSize( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Size_t * LCD_LM6063DCW_A_Size )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p, Size=%p )", __FUNCTION__, Instance, LCD_LM6063DCW_A_Size );
        // FIXME
        //    if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        //    {
        //      break;
        //    }
        //    if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        //    {
        //      break;
        //    }
        Status = LCD_LM6063DCW_A_GetSize_Execute( Instance, LCD_LM6063DCW_A_Size );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetCursor( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Coordinate_t LCD_LM6063DCW_A_Coordinate )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p, Coordinate={Row=%d, Column=%d} )", __FUNCTION__, Instance, LCD_LM6063DCW_A_Coordinate.Row, LCD_LM6063DCW_A_Coordinate.Column );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_SetCursor_Execute( Instance, LCD_LM6063DCW_A_Coordinate );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Write( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Character_t LCD_LM6063DCW_A_Character )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p, Character=%02X )", __FUNCTION__, Instance, LCD_LM6063DCW_A_Character );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_Write_Execute( Instance, LCD_LM6063DCW_A_Character );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPixel( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Coordinate_t LCD_LM6063DCW_A_Coordinate, LCD_LM6063DCW_A_Pixel_t LCD_LM6063DCW_A_Pixel )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p, Coordinate={Row=%d, Column=%d}, Pixel=%02X )", __FUNCTION__, Instance, LCD_LM6063DCW_A_Coordinate.Row, LCD_LM6063DCW_A_Coordinate.Column, LCD_LM6063DCW_A_Pixel );
        // FIXME
        //    if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        //    {
        //      break;
        //    }
        //    if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        //    {
        //      break;
        //    }
        Status = LCD_LM6063DCW_A_SetPixel_Execute( Instance, LCD_LM6063DCW_A_Coordinate, LCD_LM6063DCW_A_Pixel );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_GetScreen( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Screen_t ** LCD_LM6063DCW_A_Screen )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p, Screen=%p )", __FUNCTION__, Instance, LCD_LM6063DCW_A_Screen );
        // FIXME
        //    if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        //    {
        //      break;
        //    }
        //    if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        //    {
        //      break;
        //    }
        Status = LCD_LM6063DCW_A_GetScreen_Execute( Instance, LCD_LM6063DCW_A_Screen );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Flush( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Flush );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayOn( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_SetDisplayOn_Execute( Instance );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayOff( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_SetDisplayOff_Execute( Instance );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetLine( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Line_t LCD_LM6063DCW_A_Line )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_SetLine_Execute( Instance, LCD_LM6063DCW_A_Line );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPage( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Page_t LCD_LM6063DCW_A_Page )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_SetPage_Execute( Instance, LCD_LM6063DCW_A_Page );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetColumn( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Column_t LCD_LM6063DCW_A_Column )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_SetColumn_Execute( Instance, LCD_LM6063DCW_A_Column );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetSEG_Direction( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_SEG_Direction_t LCD_LM6063DCW_A_SEG_Direction )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_SetSEG_Direction_Execute( Instance, LCD_LM6063DCW_A_SEG_Direction );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayDirection( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_DisplayDirection_t LCD_LM6063DCW_A_DisplayDirection )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_SetDisplayDirection_Execute( Instance, LCD_LM6063DCW_A_DisplayDirection );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPixelsOn( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_SetPixelsOn_Execute( Instance );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPixelsOff( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_SetPixelsOff_Execute( Instance );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetBias( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Bias_t LCD_LM6063DCW_A_Bias )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_SetBias_Execute( Instance, LCD_LM6063DCW_A_Bias );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Reset( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_Reset_Execute( Instance );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetCOM_Direction( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_COM_Direction_t LCD_LM6063DCW_A_COM_Direction )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_SetCOM_Direction_Execute( Instance, LCD_LM6063DCW_A_COM_Direction );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPower( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_PowerBooster_t LCD_LM6063DCW_A_PowerBooster, LCD_LM6063DCW_A_PowerRegulator_t LCD_LM6063DCW_A_PowerRegulator, LCD_LM6063DCW_A_PowerFollower_t LCD_LM6063DCW_A_PowerFollower )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_SetPower_Execute( Instance, LCD_LM6063DCW_A_PowerBooster, LCD_LM6063DCW_A_PowerRegulator, LCD_LM6063DCW_A_PowerFollower );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetRegulationRatio( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_RegulationRatio_t LCD_LM6063DCW_A_RegulationRatio )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_SetRegulationRatio_Execute( Instance, LCD_LM6063DCW_A_RegulationRatio );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetElectronicVolume( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_ElectronicVolume_t LCD_LM6063DCW_A_ElectronicVolume )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_SetElectronicVolume_Execute( Instance, LCD_LM6063DCW_A_ElectronicVolume );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetBoosterLevel( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_BoosterLevel_t LCD_LM6063DCW_A_BoosterLevel )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_SetBoosterLevel_Execute( Instance, LCD_LM6063DCW_A_BoosterLevel );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_PowerSaveEnter( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_PowerSaveEnter_Execute( Instance );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_PowerSaveExit( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_PowerSaveExit_Execute( Instance );
    }
    while ( 0 );
    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_NOP( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        if ( ( Status = LCD_LM6063DCW_A_Process_Set( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }
        Status = LCD_LM6063DCW_A_NOP_Execute( Instance );
    }
    while ( 0 );
    return Status;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

const char LCD_LM6063DCW_A_VERSION[] = "0.0.0.v20260120-0211";

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
