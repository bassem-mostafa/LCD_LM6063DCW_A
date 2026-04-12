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

#include <stddef.h>
#include <stdint.h>

#include "../../LCD_Internal.h"
#include "LCD_LM6063DCW_A.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

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
    LCD_LM6063DCW_A_Command_t Command[ 1 ];

    struct
    {
        uint8_t State : 1;
        uint8_t       : 7;
    };
} LCD_LM6063DCW_A_SetDisplay_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetLine
{
    LCD_LM6063DCW_A_Command_t Command[ 1 ];

    struct
    {
        uint8_t Line : 6;
        uint8_t      : 2;
    };
} LCD_LM6063DCW_A_SetLine_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetPage
{
    LCD_LM6063DCW_A_Command_t Command[ 1 ];

    struct
    {
        uint8_t Page : 4;
        uint8_t      : 4;
    };
} LCD_LM6063DCW_A_SetPage_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetColumn
{
    LCD_LM6063DCW_A_Command_t Command[ 2 ];

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
    LCD_LM6063DCW_A_Command_t Command[ 1 ];

    struct
    {
        uint8_t Direction : 1;
        uint8_t           : 7;
    };
} LCD_LM6063DCW_A_SetSEG_Direction_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetDisplayInverse
{
    LCD_LM6063DCW_A_Command_t Command[ 1 ];

    struct
    {
        uint8_t Inverse : 1;
        uint8_t         : 7;
    };
} LCD_LM6063DCW_A_SetDisplayInverse_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetAllPixel
{
    LCD_LM6063DCW_A_Command_t Command[ 1 ];

    struct
    {
        uint8_t On : 1;
        uint8_t    : 7;
    };
} LCD_LM6063DCW_A_SetAllPixel_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetBias
{
    LCD_LM6063DCW_A_Command_t Command[ 1 ];

    struct
    {
        uint8_t Bias : 1;
        uint8_t      : 7;
    };
} LCD_LM6063DCW_A_SetBias_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_Reset
{
    LCD_LM6063DCW_A_Command_t Command[ 1 ];
} LCD_LM6063DCW_A_Reset_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetCOM_Direction
{
    LCD_LM6063DCW_A_Command_t Command[ 1 ];

    struct
    {
        uint8_t         : 3;
        uint8_t Reverse : 1;
        uint8_t         : 4;
    };
} LCD_LM6063DCW_A_SetCOM_Direction_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetPowerControl
{
    LCD_LM6063DCW_A_Command_t Command[ 1 ];

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
    LCD_LM6063DCW_A_Command_t Command[ 1 ];

    struct
    {
        uint8_t Ratio : 3;
        uint8_t       : 5;
    };
} LCD_LM6063DCW_A_SetRegulation_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetElectronicVolume
{
    LCD_LM6063DCW_A_Command_t Command[ 2 ];

    struct
    {
        uint8_t       : 8;
        uint8_t Level : 6;
        uint8_t       : 2;
    };
} LCD_LM6063DCW_A_SetElectronicVolume_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_SetBooster
{
    LCD_LM6063DCW_A_Command_t Command[ 2 ];

    struct
    {
        uint8_t       : 8;
        uint8_t Level : 1;
        uint8_t       : 7;
    };
} LCD_LM6063DCW_A_SetBooster_t;

typedef union __attribute__( ( packed, aligned( 1 ) ) ) LCD_LM6063DCW_A_NOP
{
    LCD_LM6063DCW_A_Command_t Command[ 1 ];
} LCD_LM6063DCW_A_NOP_t;

/**
 * @brief LCD LM6063DCW_A Operation
 *
 * @enum LCD_LM6063DCW_A_OperationType_t
 */
typedef enum LCD_LM6063DCW_A_OperationType
{
    LCD_LM6063DCW_A_OperationType_None = 0,         ///< None
    LCD_LM6063DCW_A_OperationType_Pending,          ///< Pending
    LCD_LM6063DCW_A_OperationType_PowerOff,         ///< Power Off
    LCD_LM6063DCW_A_OperationType_PowerOn,          ///< Power On
    LCD_LM6063DCW_A_OperationType_DisplayOn,        ///< Display On
    LCD_LM6063DCW_A_OperationType_DisplayOff,       ///< Display Off
    LCD_LM6063DCW_A_OperationType_Line,             ///< Set Line
    LCD_LM6063DCW_A_OperationType_Page,             ///< Set Page
    LCD_LM6063DCW_A_OperationType_Column,           ///< Set Column
    LCD_LM6063DCW_A_OperationType_SEG_Direction,    ///< Set SEG Direction
    LCD_LM6063DCW_A_OperationType_DisplayDirection, ///< Set Display Direction
    LCD_LM6063DCW_A_OperationType_PixelsOn,         ///< Set Pixels On
    LCD_LM6063DCW_A_OperationType_PixelsOff,        ///< Set Pixels Off
    LCD_LM6063DCW_A_OperationType_Bias,             ///< Set Bias
    LCD_LM6063DCW_A_OperationType_Reset,            ///< Reset
    LCD_LM6063DCW_A_OperationType_COM_Direction,    ///< Set COM Direction
    LCD_LM6063DCW_A_OperationType_Power,            ///< Set Power
    LCD_LM6063DCW_A_OperationType_RegulationRatio,  ///< Set Regulation Ratio
    LCD_LM6063DCW_A_OperationType_ElectronicVolume, ///< Set Electronic Volume
    LCD_LM6063DCW_A_OperationType_BoosterLevel,     ///< Set Booster Level
    LCD_LM6063DCW_A_OperationType_PowerSaveEnter,   ///< PowerSaveEnter
    LCD_LM6063DCW_A_OperationType_PowerSaveExit,    ///< Power Save Exit
    LCD_LM6063DCW_A_OperationType_NOP,              ///< NOP
    LCD_LM6063DCW_A_OperationType_Write,            ///< Write
    LCD_LM6063DCW_A_OperationType_Flush,            ///< Flush

    LCD_LM6063DCW_A_OperationType_Pixel, ///< Set Pixel
} LCD_LM6063DCW_A_OperationType_t;

/**
 * @brief LCD LM6063DCW_A Operation Handler
 */
typedef LCD_LM6063DCW_A_Status_t ( *LCD_LM6063DCW_A_OperationHandler_t )( LCD_LM6063DCW_A_Instance_t * Instance );

/**
 * @brief LCD LM6063DCW_A Operation Context
 *
 * @struct LCD_LM6063DCW_A_OperationContext_t
 */
typedef struct LCD_LM6063DCW_A_OperationContext
{
    LCD_LM6063DCW_A_Page_t Page;
    uint8_t ScreenPage[ LCD_LM6063DCW_A_WIDTH ]; // FIXME Could it be replaced by using context screen directly ?

    union
    {
        LCD_LM6063DCW_A_SetDisplay_t SetDisplay;
        LCD_LM6063DCW_A_SetLine_t SetLine;
        LCD_LM6063DCW_A_SetSEG_Direction_t Set_SEG_Direction;
        LCD_LM6063DCW_A_SetDisplayInverse_t SetDisplayInverse;
        LCD_LM6063DCW_A_SetAllPixel_t SetAllPixel;
        LCD_LM6063DCW_A_SetBias_t SetBias;
        LCD_LM6063DCW_A_SetCOM_Direction_t Set_COM_Direction;
        LCD_LM6063DCW_A_SetPowerControl_t SetPowerControl;
        LCD_LM6063DCW_A_SetRegulation_t SetRegulation;
        LCD_LM6063DCW_A_SetBooster_t SetBooster;
        LCD_LM6063DCW_A_SetElectronicVolume_t SetElectronicVolume;
        LCD_LM6063DCW_A_SetPage_t SetPage;
        LCD_LM6063DCW_A_SetColumn_t SetColumn;
    };
} LCD_LM6063DCW_A_OperationContext_t;

typedef struct LCD_LM6063DCW_A_Operation
{
    LCD_LM6063DCW_A_OperationType_t Type;       ///< Type
    LCD_LM6063DCW_A_OperationHandler_t Handler; ///< Handler
    LCD_LM6063DCW_A_Status_t Status;            ///< Status
    TIM_Timestamp_t Timeout;                    ///< Timeout
    LCD_LM6063DCW_A_OperationContext_t Context; ///< Context
} LCD_LM6063DCW_A_Operation_t;

/**
 * @brief LCD LM6063DCW_A Process Type
 *
 * @enum LCD_LM6063DCW_A_ProcessType_t
 */
typedef enum ProcessType
{
    LCD_LM6063DCW_A_ProcessType_None = 0,   ///< None
    LCD_LM6063DCW_A_ProcessType_Initialize, ///< Initialize
    LCD_LM6063DCW_A_ProcessType_Flush,      ///< Flush
} LCD_LM6063DCW_A_ProcessType_t;

/**
 * @brief LCD LM6063DCW_A Process Handler
 */
typedef LCD_LM6063DCW_A_Status_t ( *LCD_LM6063DCW_A_Process_Handler_t )( LCD_LM6063DCW_A_Instance_t * Instance );

/**
 * @brief LCD LM6063DCW_A Process Context
 *
 * @struct LCD_LM6063DCW_A_ProcessContext_t
 */
typedef struct LCD_LM6063DCW_A_ProcessContext
{
    LCD_LM6063DCW_A_Operation_t Operation; ///< Operation
} LCD_LM6063DCW_A_ProcessContext_t;

/**
 * @brief LCD LM6063DCW_A Process
 *
 * @struct LCD_LM6063DCW_A_Process_t
 */
typedef struct LCD_LM6063DCW_A_Process
{
    LCD_LM6063DCW_A_ProcessType_t Type;        ///< Type
    LCD_LM6063DCW_A_Process_Handler_t Handler; ///< Handler
    LCD_LM6063DCW_A_ProcessContext_t Context;  ///< Context
} LCD_LM6063DCW_A_Process_t;

/**
 * @brief LCD LM6063DCW_A Event
 *
 * @enum LCD_LM6063DCW_A_Event_t
 */
typedef enum LCD_LM6063DCW_A_Event
{
    LCD_LM6063DCW_A_Event_None = 0,
    LCD_LM6063DCW_A_Event_Timeout = UTIL_BIT( 0 ),
    LCD_LM6063DCW_A_Event_SPI_Success = UTIL_BIT( 1 ),
    LCD_LM6063DCW_A_Event_SPI_Error = UTIL_BIT( 2 ),
} LCD_LM6063DCW_A_Event_t;

typedef struct LCD_LM6063DCW_A_InstanceContext
{
    LCD_LM6063DCW_A_Instance_t * Instance; // Owner Instance

    LCD_LM6063DCW_A_Event_t Event;

    LCD_LM6063DCW_A_Process_t Process;

    LCD_LM6063DCW_A_SEG_Direction_t SEG_Direction;
    LCD_LM6063DCW_A_Screen_t Screen;
} LCD_LM6063DCW_A_InstanceContext_t;

typedef struct LCD_LM6063DCW_A_Context
{
    TIM_Timestamp_t Timestamp;
    LCD_LM6063DCW_A_InstanceContext_t Context[ LCD_LM6063DCW_A_Count ];
} LCD_LM6063DCW_A_Context_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

static SPI_Status_t SPI_CallbackOnComplete( SPI_t SPIx, SPI_Status_t Status );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Context_Initialize( void );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Context_Cycle( void );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Context_DeInitialize( void );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Instance_Initialize( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Instance_Cycle( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Instance_DeInitialize( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetProcess( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_ProcessType_t ProcessType );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Execute( LCD_LM6063DCW_A_Instance_t * Instance, uint8_t * buffer, uint32_t length );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Transfer( LCD_LM6063DCW_A_Instance_t * Instance, uint8_t * buffer, uint32_t length );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_ProcessInitialize( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_ProcessFlush( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationPowerOffExecute( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationPowerOffResolve( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationPowerOnExecute( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationPowerOnResolve( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationDisplayOnExecute( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationDisplayOnResolve( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationLineExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Line_t Line );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationLineResolve( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Operation_SEG_DirectionExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_SEG_Direction_t SEG_Direction );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Operation_SEG_DirectionResolve( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationDisplayDirectionExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_DisplayDirection_t DisplayDirection );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationDisplayDirectionResolve( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationPixelsOffExecute( LCD_LM6063DCW_A_Instance_t * Instance );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationPixelsOffResolve( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationBiasExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Bias_t Bias );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationBiasResolve( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Operation_COM_DirectionExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_COM_Direction_t COM_Direction );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Operation_COM_DirectionResolve( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationPowerExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_PowerBooster_t PowerBooster, LCD_LM6063DCW_A_PowerRegulator_t PowerRegulator, LCD_LM6063DCW_A_PowerFollower_t PowerFollower );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationPowerResolve( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationRegulationRatioExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_RegulationRatio_t RegulationRatio );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationRegulationRatioResolve( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationBoosterLevelExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_BoosterLevel_t BoosterLevel );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationBoosterLevelResolve( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationElectronicVolumeExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_ElectronicVolume_t ElectronicVolume );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationElectronicVolumeResolve( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationPageExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Page_t Page );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationPageResolve( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationColumnExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Column_t Column );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationColumnResolve( LCD_LM6063DCW_A_Instance_t * Instance );

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationFlushExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Page_t Page );
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationFlushResolve( LCD_LM6063DCW_A_Instance_t * Instance );

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
        LCD_LM6063DCW_A_InstanceContext_t * Context = NULL;
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
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

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

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Context_Initialize( void )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( void )", __FUNCTION__ );

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_GetTimestamp( LCD_TIM, &LCD_LM6063DCW_A_Context.Timestamp ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Context_Cycle( void )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( void )", __FUNCTION__ );

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_GetTimestamp( LCD_TIM, &LCD_LM6063DCW_A_Context.Timestamp ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Context_DeInitialize( void )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( void )", __FUNCTION__ );
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

        GPIO_Status_t GPIO_Status = GPIO_Status_Success;
        if ( ( GPIO_Status = GPIO_Write( Instance->PowerEnable, GPIO_Value_High ) ) != GPIO_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        if ( ( GPIO_Status = GPIO_Write( Instance->BacklightEnable, GPIO_Value_Low ) ) != GPIO_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        SPI_Status_t SPI_Status = SPI_Status_Success;
        if ( ( SPI_Status = SPI_SetCallbackOnComplete( Instance->SPIx, SPI_CallbackOnComplete ) ) != SPI_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];

        Context->Event = LCD_LM6063DCW_A_Event_None;

        Context->SEG_Direction = LCD_LM6063DCW_A_SEG_Direction_Reverse;
        UTIL_MemorySetZero( Context->Screen, UTIL_SizeOf( Context->Screen ) );

        Context->Instance = Instance;

        Instance->Context = Context;

        Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Initialize );
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Instance_Cycle( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;
        LCD_LM6063DCW_A_Event_t Event = Context->Event; // CAUTION: Has to copy events occurred at the early start of the cycle, so as to be cleared at the end of the cycle,
                                                        //          which let events occurs after that for the next cycle call

        if ( Operation->Handler != NULL )
        {
            LCD_LM6063DCW_A_Status_t LM6063DCW_A_Status = LCD_LM6063DCW_A_Status_Error;
            if ( ( LM6063DCW_A_Status = Operation->Handler( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
            {
                Status = LM6063DCW_A_Status;
                // FIXME Operation reported non success status, is there any action ?
            }
        }

        if ( Process->Handler != NULL )
        {
            LCD_LM6063DCW_A_Status_t LM6063DCW_A_Status = LCD_LM6063DCW_A_Status_Error;
            if ( ( LM6063DCW_A_Status = Process->Handler( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
            {
                Status = LM6063DCW_A_Status;
                // FIXME Process reported non success status, is there any action ?
            }
        }

        if ( ( Event & LCD_LM6063DCW_A_Event_Timeout ) == LCD_LM6063DCW_A_Event_Timeout )
        {
            Context->Event &= ~LCD_LM6063DCW_A_Event_Timeout;
            LCD_Trace( "Timeout: Instance=%p, LM6063DCW_A=%d", Instance, Instance->LM6063DCW_A );
            // TODO Invoke Callback
        }

        if ( ( Event & LCD_LM6063DCW_A_Event_SPI_Success ) == LCD_LM6063DCW_A_Event_SPI_Success )
        {
            Context->Event &= ~LCD_LM6063DCW_A_Event_SPI_Success;
            LCD_Debug( "SPI Success: Instance=%p, LM6063DCW_A=%d", Instance, Instance->LM6063DCW_A );
            // TODO Invoke Callback
        }

        if ( ( Event & LCD_LM6063DCW_A_Event_SPI_Error ) == LCD_LM6063DCW_A_Event_SPI_Error )
        {
            Context->Event &= ~LCD_LM6063DCW_A_Event_SPI_Error;
            LCD_Debug( "SPI Error: Instance=%p, LM6063DCW_A=%d", Instance, Instance->LM6063DCW_A );
            // TODO Invoke Callback
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Instance_DeInitialize( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetProcess( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_ProcessType_t ProcessType )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        Process->Type = ProcessType;

        switch ( ProcessType )
        {
            case LCD_LM6063DCW_A_ProcessType_None:
                Process->Handler = NULL;
                break;

            case LCD_LM6063DCW_A_ProcessType_Initialize:
                Process->Handler = LCD_LM6063DCW_A_ProcessInitialize;
                break;

            case LCD_LM6063DCW_A_ProcessType_Flush:
                Process->Handler = LCD_LM6063DCW_A_ProcessFlush;
                break;

            default:
                LCD_Warning( "%s Not Handled Type %d", __FUNCTION__, ProcessType );
                Status = LCD_LM6063DCW_A_Status_NotSupported;
                break;
        }
        if ( Status != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Process->Type = ProcessType;

        Operation->Handler = NULL;
        Operation->Status = LCD_LM6063DCW_A_Status_Success;
        Operation->Timeout = LCD_LM6063DCW_A_Context.Timestamp;

        switch ( ProcessType )
        {
            case LCD_LM6063DCW_A_ProcessType_None:
                Operation->Type = LCD_LM6063DCW_A_OperationType_None;
                break;

            default:
                Operation->Type = LCD_LM6063DCW_A_OperationType_Pending;
                break;
        }
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

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_ProcessInitialize( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        if ( Process->Type != LCD_LM6063DCW_A_ProcessType_Initialize )
        {
            LCD_Error( "%s Got %d Expected %d", __FUNCTION__, Process->Type, LCD_LM6063DCW_A_ProcessType_Initialize );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        if ( Operation->Handler != NULL )
        {
            // Operation In-progress
            break;
        }

        if ( Operation->Status != LCD_LM6063DCW_A_Status_Success )
        {
            Operation->Type = LCD_LM6063DCW_A_OperationType_None;
        }

        switch ( Operation->Type )
        {
            case LCD_LM6063DCW_A_OperationType_Pending:
                Operation->Status = LCD_LM6063DCW_A_OperationPowerOffExecute( Instance );
                break;

            case LCD_LM6063DCW_A_OperationType_PowerOff:
                Operation->Status = LCD_LM6063DCW_A_OperationPowerOnExecute( Instance );
                break;

            case LCD_LM6063DCW_A_OperationType_PowerOn:
                Operation->Status = LCD_LM6063DCW_A_OperationDisplayOnExecute( Instance );
                break;

            case LCD_LM6063DCW_A_OperationType_DisplayOn:
                Operation->Status = LCD_LM6063DCW_A_OperationLineExecute( Instance, LCD_LM6063DCW_A_Line_0 );
                break;

            case LCD_LM6063DCW_A_OperationType_Line:
                Operation->Status = LCD_LM6063DCW_A_Operation_SEG_DirectionExecute( Instance, LCD_LM6063DCW_A_SEG_Direction_Reverse );
                break;

            case LCD_LM6063DCW_A_OperationType_SEG_Direction:
                Operation->Status = LCD_LM6063DCW_A_OperationDisplayDirectionExecute( Instance, LCD_LM6063DCW_A_DisplayDirection_Normal );
                break;

            case LCD_LM6063DCW_A_OperationType_DisplayDirection:
                Operation->Status = LCD_LM6063DCW_A_OperationPixelsOffExecute( Instance );
                break;

            case LCD_LM6063DCW_A_OperationType_PixelsOff:
                Operation->Status = LCD_LM6063DCW_A_OperationBiasExecute( Instance, LCD_LM6063DCW_A_Bias_1_9 );
                break;

            case LCD_LM6063DCW_A_OperationType_Bias:
                Operation->Status = LCD_LM6063DCW_A_Operation_COM_DirectionExecute( Instance, LCD_LM6063DCW_A_COM_Direction_Normal );
                break;

            case LCD_LM6063DCW_A_OperationType_COM_Direction:
                Operation->Status = LCD_LM6063DCW_A_OperationPowerExecute( Instance, LCD_LM6063DCW_A_PowerBooster_On, LCD_LM6063DCW_A_PowerRegulator_On, LCD_LM6063DCW_A_PowerFollower_On );
                break;

            case LCD_LM6063DCW_A_OperationType_Power:
                Operation->Status = LCD_LM6063DCW_A_OperationRegulationRatioExecute( Instance, LCD_LM6063DCW_A_RegulationRatio_5_5 );
                break;

            case LCD_LM6063DCW_A_OperationType_RegulationRatio:
                Operation->Status = LCD_LM6063DCW_A_OperationBoosterLevelExecute( Instance, LCD_LM6063DCW_A_BoosterLevel_X4 );
                break;

            case LCD_LM6063DCW_A_OperationType_BoosterLevel:
                Operation->Status = LCD_LM6063DCW_A_OperationElectronicVolumeExecute( Instance, LCD_LM6063DCW_A_ElectronicVolume_33 );
                break;

            case LCD_LM6063DCW_A_OperationType_ElectronicVolume:
            default:
                // TODO OnComplete Callback
                // if ( Instance->OnComplete != NULL )
                // {
                //     Instance->OnComplete( Instance, Operation->Status );
                // }

                // Successful initialization is followed by flush process
                if ( Operation->Status != LCD_LM6063DCW_A_Status_Success )
                {
                    Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_None );
                    break;
                }

                Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Flush );
                break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_ProcessFlush( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        if ( Process->Type != LCD_LM6063DCW_A_ProcessType_Flush )
        {
            LCD_Error( "%s Got %d Expected %d", __FUNCTION__, Process->Type, LCD_LM6063DCW_A_ProcessType_Flush );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        if ( Operation->Handler != NULL )
        {
            // Operation In-progress
            break;
        }

        if ( Operation->Status != LCD_LM6063DCW_A_Status_Success )
        {
            Operation->Type = LCD_LM6063DCW_A_OperationType_None;
        }

        switch ( Operation->Type )
        {
            case LCD_LM6063DCW_A_OperationType_Pending:
                Operation->Context.Page = LCD_LM6063DCW_A_Page_0;
                Operation->Status = LCD_LM6063DCW_A_OperationPageExecute( Instance, Operation->Context.Page );
                break;

            case LCD_LM6063DCW_A_OperationType_Page:
                // FIX align with the visual pixels
                switch ( Instance->Context->SEG_Direction )
                {
                    case LCD_LM6063DCW_A_SEG_Direction_Normal:
                        Operation->Status = LCD_LM6063DCW_A_OperationColumnExecute( Instance, LCD_LM6063DCW_A_Column_4 );
                        break;
                    case LCD_LM6063DCW_A_SEG_Direction_Reverse:
                    default:
                        Operation->Status = LCD_LM6063DCW_A_OperationColumnExecute( Instance, LCD_LM6063DCW_A_Column_0 );
                        break;
                }
                break;

            case LCD_LM6063DCW_A_OperationType_Column:
                Operation->Status = LCD_LM6063DCW_A_OperationFlushExecute( Instance, Operation->Context.Page );
                break;

            case LCD_LM6063DCW_A_OperationType_Flush:
                if ( Operation->Context.Page < LCD_LM6063DCW_A_Page_8 )
                {
                    // Start flush again for the next page
                    Operation->Context.Page++;
                    Operation->Status = LCD_LM6063DCW_A_OperationPageExecute( Instance, Operation->Context.Page );
                    break;
                }

                Operation->Context.Page = LCD_LM6063DCW_A_Page_0;
                // no break

            default:
                // TODO OnComplete Callback
                // if ( Instance->OnComplete != NULL )
                // {
                //     Instance->OnComplete( Instance, Operation->Status );
                // }
                LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_None );
                break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationPowerOffExecute( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        GPIO_Status_t GPIO_Status = GPIO_Status_Success;
        if ( ( GPIO_Status = GPIO_Write( Instance->Reset, GPIO_Value_Low ) ) != GPIO_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        Operation->Type = LCD_LM6063DCW_A_OperationType_PowerOff;
        Operation->Handler = LCD_LM6063DCW_A_OperationPowerOffResolve;
        Operation->Status = LCD_LM6063DCW_A_Status_Success;
        Operation->Timeout = LCD_LM6063DCW_A_Context.Timestamp;

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_Timestamp_AddMillisecond( &Operation->Timeout, 100 ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationPowerOffResolve( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        if ( Operation->Type != LCD_LM6063DCW_A_OperationType_PowerOff )
        {
            LCD_Error( "%s Got %d Expected %d", __FUNCTION__, Operation->Type, LCD_LM6063DCW_A_OperationType_PowerOff );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_IsExpiredTimestamp( LCD_TIM, &Operation->Timeout ) ) == TIM_Status_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Success;
            Operation->Handler = NULL;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationPowerOnExecute( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        GPIO_Status_t GPIO_Status = GPIO_Status_Success;
        if ( ( GPIO_Status = GPIO_Write( Instance->Reset, GPIO_Value_High ) ) != GPIO_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        Operation->Type = LCD_LM6063DCW_A_OperationType_PowerOn;
        Operation->Handler = LCD_LM6063DCW_A_OperationPowerOnResolve;
        Operation->Status = LCD_LM6063DCW_A_Status_Success;
        Operation->Timeout = LCD_LM6063DCW_A_Context.Timestamp;

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_Timestamp_AddMillisecond( &Operation->Timeout, 100 ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationPowerOnResolve( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        if ( Operation->Type != LCD_LM6063DCW_A_OperationType_PowerOn )
        {
            LCD_Error( "%s Got %d Expected %d", __FUNCTION__, Operation->Type, LCD_LM6063DCW_A_OperationType_PowerOn );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_IsExpiredTimestamp( LCD_TIM, &Operation->Timeout ) ) == TIM_Status_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Success;
            Operation->Handler = NULL;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationDisplayOnExecute( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        Operation->Context.SetDisplay = ( LCD_LM6063DCW_A_SetDisplay_t ) { { LCD_LM6063DCW_A_Command_SetDisplay } };
        Operation->Context.SetDisplay.State = 1;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &Operation->Context.SetDisplay, UTIL_SizeOf( Operation->Context.SetDisplay ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Operation->Type = LCD_LM6063DCW_A_OperationType_DisplayOn;
        Operation->Handler = LCD_LM6063DCW_A_OperationDisplayOnResolve;
        Operation->Status = LCD_LM6063DCW_A_Status_Success;
        Operation->Timeout = LCD_LM6063DCW_A_Context.Timestamp;

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_Timestamp_AddMillisecond( &Operation->Timeout, 100 ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationDisplayOnResolve( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        if ( Operation->Type != LCD_LM6063DCW_A_OperationType_DisplayOn )
        {
            LCD_Error( "%s Got %d Expected %d", __FUNCTION__, Operation->Type, LCD_LM6063DCW_A_OperationType_DisplayOn );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_IsExpiredTimestamp( LCD_TIM, &Operation->Timeout ) ) == TIM_Status_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Timeout;
            Operation->Handler = NULL;
            break;
        }

        if ( ( Context->Event & LCD_LM6063DCW_A_Event_SPI_Success ) == LCD_LM6063DCW_A_Event_SPI_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Success;
            Operation->Handler = NULL;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationLineExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Line_t Line )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        Operation->Context.SetLine = ( LCD_LM6063DCW_A_SetLine_t ) { { LCD_LM6063DCW_A_Command_SetLine } };
        Operation->Context.SetLine.Line = Line;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &Operation->Context.SetLine, UTIL_SizeOf( Operation->Context.SetLine ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Operation->Type = LCD_LM6063DCW_A_OperationType_Line;
        Operation->Handler = LCD_LM6063DCW_A_OperationLineResolve;
        Operation->Status = LCD_LM6063DCW_A_Status_Success;
        Operation->Timeout = LCD_LM6063DCW_A_Context.Timestamp;

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_Timestamp_AddMillisecond( &Operation->Timeout, 100 ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationLineResolve( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        if ( Operation->Type != LCD_LM6063DCW_A_OperationType_Line )
        {
            LCD_Error( "%s Got %d Expected %d", __FUNCTION__, Operation->Type, LCD_LM6063DCW_A_OperationType_Line );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_IsExpiredTimestamp( LCD_TIM, &Operation->Timeout ) ) == TIM_Status_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Timeout;
            Operation->Handler = NULL;
            break;
        }

        if ( ( Context->Event & LCD_LM6063DCW_A_Event_SPI_Success ) == LCD_LM6063DCW_A_Event_SPI_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Success;
            Operation->Handler = NULL;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Operation_SEG_DirectionExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_SEG_Direction_t SEG_Direction )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        Operation->Context.Set_SEG_Direction = ( LCD_LM6063DCW_A_SetSEG_Direction_t ) { { LCD_LM6063DCW_A_Command_SetSEG_Direction } };
        Operation->Context.Set_SEG_Direction.Direction = SEG_Direction;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &Operation->Context.Set_SEG_Direction, UTIL_SizeOf( Operation->Context.Set_SEG_Direction ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        // Update SEG_Direction
        Instance->Context->SEG_Direction = SEG_Direction;

        Operation->Type = LCD_LM6063DCW_A_OperationType_SEG_Direction;
        Operation->Handler = LCD_LM6063DCW_A_Operation_SEG_DirectionResolve;
        Operation->Status = LCD_LM6063DCW_A_Status_Success;
        Operation->Timeout = LCD_LM6063DCW_A_Context.Timestamp;

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_Timestamp_AddMillisecond( &Operation->Timeout, 100 ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Operation_SEG_DirectionResolve( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        if ( Operation->Type != LCD_LM6063DCW_A_OperationType_SEG_Direction )
        {
            LCD_Error( "%s Got %d Expected %d", __FUNCTION__, Operation->Type, LCD_LM6063DCW_A_OperationType_SEG_Direction );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_IsExpiredTimestamp( LCD_TIM, &Operation->Timeout ) ) == TIM_Status_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Timeout;
            Operation->Handler = NULL;
            break;
        }

        if ( ( Context->Event & LCD_LM6063DCW_A_Event_SPI_Success ) == LCD_LM6063DCW_A_Event_SPI_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Success;
            Operation->Handler = NULL;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationDisplayDirectionExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_DisplayDirection_t DisplayDirection )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        Operation->Context.SetDisplayInverse = ( LCD_LM6063DCW_A_SetDisplayInverse_t ) { { LCD_LM6063DCW_A_Command_SetDisplayInverse } };
        Operation->Context.SetDisplayInverse.Inverse = DisplayDirection;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &Operation->Context.SetDisplayInverse, UTIL_SizeOf( Operation->Context.SetDisplayInverse ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Operation->Type = LCD_LM6063DCW_A_OperationType_DisplayDirection;
        Operation->Handler = LCD_LM6063DCW_A_OperationDisplayDirectionResolve;
        Operation->Status = LCD_LM6063DCW_A_Status_Success;
        Operation->Timeout = LCD_LM6063DCW_A_Context.Timestamp;

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_Timestamp_AddMillisecond( &Operation->Timeout, 100 ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationDisplayDirectionResolve( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        if ( Operation->Type != LCD_LM6063DCW_A_OperationType_DisplayDirection )
        {
            LCD_Error( "%s Got %d Expected %d", __FUNCTION__, Operation->Type, LCD_LM6063DCW_A_OperationType_DisplayDirection );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_IsExpiredTimestamp( LCD_TIM, &Operation->Timeout ) ) == TIM_Status_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Timeout;
            Operation->Handler = NULL;
            break;
        }

        if ( ( Context->Event & LCD_LM6063DCW_A_Event_SPI_Success ) == LCD_LM6063DCW_A_Event_SPI_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Success;
            Operation->Handler = NULL;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationPixelsOffExecute( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        Operation->Context.SetAllPixel = ( LCD_LM6063DCW_A_SetAllPixel_t ) { { LCD_LM6063DCW_A_Command_SetAllPixel } };
        Operation->Context.SetAllPixel.On = 0;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &Operation->Context.SetAllPixel, UTIL_SizeOf( Operation->Context.SetAllPixel ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Operation->Type = LCD_LM6063DCW_A_OperationType_PixelsOff;
        Operation->Handler = LCD_LM6063DCW_A_OperationPixelsOffResolve;
        Operation->Status = LCD_LM6063DCW_A_Status_Success;
        Operation->Timeout = LCD_LM6063DCW_A_Context.Timestamp;

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_Timestamp_AddMillisecond( &Operation->Timeout, 100 ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationPixelsOffResolve( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        if ( Operation->Type != LCD_LM6063DCW_A_OperationType_PixelsOff )
        {
            LCD_Error( "%s Got %d Expected %d", __FUNCTION__, Operation->Type, LCD_LM6063DCW_A_OperationType_PixelsOff );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_IsExpiredTimestamp( LCD_TIM, &Operation->Timeout ) ) == TIM_Status_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Timeout;
            Operation->Handler = NULL;
            break;
        }

        if ( ( Context->Event & LCD_LM6063DCW_A_Event_SPI_Success ) == LCD_LM6063DCW_A_Event_SPI_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Success;
            Operation->Handler = NULL;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationBiasExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Bias_t Bias )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        Operation->Context.SetBias = ( LCD_LM6063DCW_A_SetBias_t ) { { LCD_LM6063DCW_A_Command_SetBias } };
        Operation->Context.SetBias.Bias = Bias;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &Operation->Context.SetBias, UTIL_SizeOf( Operation->Context.SetBias ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Operation->Type = LCD_LM6063DCW_A_OperationType_Bias;
        Operation->Handler = LCD_LM6063DCW_A_OperationBiasResolve;
        Operation->Status = LCD_LM6063DCW_A_Status_Success;
        Operation->Timeout = LCD_LM6063DCW_A_Context.Timestamp;

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_Timestamp_AddMillisecond( &Operation->Timeout, 100 ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationBiasResolve( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        if ( Operation->Type != LCD_LM6063DCW_A_OperationType_Bias )
        {
            LCD_Error( "%s Got %d Expected %d", __FUNCTION__, Operation->Type, LCD_LM6063DCW_A_OperationType_Bias );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_IsExpiredTimestamp( LCD_TIM, &Operation->Timeout ) ) == TIM_Status_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Timeout;
            Operation->Handler = NULL;
            break;
        }

        if ( ( Context->Event & LCD_LM6063DCW_A_Event_SPI_Success ) == LCD_LM6063DCW_A_Event_SPI_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Success;
            Operation->Handler = NULL;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Operation_COM_DirectionExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_COM_Direction_t COM_Direction )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        Operation->Context.Set_COM_Direction = ( LCD_LM6063DCW_A_SetCOM_Direction_t ) { { LCD_LM6063DCW_A_Command_SetCOM_Direction } };
        Operation->Context.Set_COM_Direction.Reverse = COM_Direction;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &Operation->Context.Set_COM_Direction, UTIL_SizeOf( Operation->Context.Set_COM_Direction ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Operation->Type = LCD_LM6063DCW_A_OperationType_COM_Direction;
        Operation->Handler = LCD_LM6063DCW_A_Operation_COM_DirectionResolve;
        Operation->Status = LCD_LM6063DCW_A_Status_Success;
        Operation->Timeout = LCD_LM6063DCW_A_Context.Timestamp;

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_Timestamp_AddMillisecond( &Operation->Timeout, 100 ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Operation_COM_DirectionResolve( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        if ( Operation->Type != LCD_LM6063DCW_A_OperationType_COM_Direction )
        {
            LCD_Error( "%s Got %d Expected %d", __FUNCTION__, Operation->Type, LCD_LM6063DCW_A_OperationType_COM_Direction );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_IsExpiredTimestamp( LCD_TIM, &Operation->Timeout ) ) == TIM_Status_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Timeout;
            Operation->Handler = NULL;
            break;
        }

        if ( ( Context->Event & LCD_LM6063DCW_A_Event_SPI_Success ) == LCD_LM6063DCW_A_Event_SPI_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Success;
            Operation->Handler = NULL;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationPowerExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_PowerBooster_t PowerBooster, LCD_LM6063DCW_A_PowerRegulator_t PowerRegulator, LCD_LM6063DCW_A_PowerFollower_t PowerFollower )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        Operation->Context.SetPowerControl = ( LCD_LM6063DCW_A_SetPowerControl_t ) { { LCD_LM6063DCW_A_Command_SetPowerControl } };
        Operation->Context.SetPowerControl.VB = PowerBooster;
        Operation->Context.SetPowerControl.VR = PowerRegulator;
        Operation->Context.SetPowerControl.VF = PowerFollower;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &Operation->Context.SetPowerControl, UTIL_SizeOf( Operation->Context.SetPowerControl ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Operation->Type = LCD_LM6063DCW_A_OperationType_Power;
        Operation->Handler = LCD_LM6063DCW_A_OperationPowerResolve;
        Operation->Status = LCD_LM6063DCW_A_Status_Success;
        Operation->Timeout = LCD_LM6063DCW_A_Context.Timestamp;

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_Timestamp_AddMillisecond( &Operation->Timeout, 100 ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationPowerResolve( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        if ( Operation->Type != LCD_LM6063DCW_A_OperationType_Power )
        {
            LCD_Error( "%s Got %d Expected %d", __FUNCTION__, Operation->Type, LCD_LM6063DCW_A_OperationType_Power );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_IsExpiredTimestamp( LCD_TIM, &Operation->Timeout ) ) == TIM_Status_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Timeout;
            Operation->Handler = NULL;
            break;
        }

        if ( ( Context->Event & LCD_LM6063DCW_A_Event_SPI_Success ) == LCD_LM6063DCW_A_Event_SPI_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Success;
            Operation->Handler = NULL;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationRegulationRatioExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_RegulationRatio_t RegulationRatio )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        Operation->Context.SetRegulation = ( LCD_LM6063DCW_A_SetRegulation_t ) { { LCD_LM6063DCW_A_Command_SetRegulation } };
        Operation->Context.SetRegulation.Ratio = RegulationRatio;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &Operation->Context.SetRegulation, UTIL_SizeOf( Operation->Context.SetRegulation ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Operation->Type = LCD_LM6063DCW_A_OperationType_RegulationRatio;
        Operation->Handler = LCD_LM6063DCW_A_OperationRegulationRatioResolve;
        Operation->Status = LCD_LM6063DCW_A_Status_Success;
        Operation->Timeout = LCD_LM6063DCW_A_Context.Timestamp;

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_Timestamp_AddMillisecond( &Operation->Timeout, 100 ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationRegulationRatioResolve( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        if ( Operation->Type != LCD_LM6063DCW_A_OperationType_RegulationRatio )
        {
            LCD_Error( "%s Got %d Expected %d", __FUNCTION__, Operation->Type, LCD_LM6063DCW_A_OperationType_RegulationRatio );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_IsExpiredTimestamp( LCD_TIM, &Operation->Timeout ) ) == TIM_Status_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Timeout;
            Operation->Handler = NULL;
            break;
        }

        if ( ( Context->Event & LCD_LM6063DCW_A_Event_SPI_Success ) == LCD_LM6063DCW_A_Event_SPI_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Success;
            Operation->Handler = NULL;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationBoosterLevelExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_BoosterLevel_t BoosterLevel )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        Operation->Context.SetBooster = ( LCD_LM6063DCW_A_SetBooster_t ) {
            { LCD_LM6063DCW_A_Command_SetBooster_1, LCD_LM6063DCW_A_Command_SetBooster_2 }
        };
        Operation->Context.SetBooster.Level = BoosterLevel;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &Operation->Context.SetBooster, UTIL_SizeOf( Operation->Context.SetBooster ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Operation->Type = LCD_LM6063DCW_A_OperationType_BoosterLevel;
        Operation->Handler = LCD_LM6063DCW_A_OperationBoosterLevelResolve;
        Operation->Status = LCD_LM6063DCW_A_Status_Success;
        Operation->Timeout = LCD_LM6063DCW_A_Context.Timestamp;

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_Timestamp_AddMillisecond( &Operation->Timeout, 100 ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationBoosterLevelResolve( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        if ( Operation->Type != LCD_LM6063DCW_A_OperationType_BoosterLevel )
        {
            LCD_Error( "%s Got %d Expected %d", __FUNCTION__, Operation->Type, LCD_LM6063DCW_A_OperationType_BoosterLevel );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_IsExpiredTimestamp( LCD_TIM, &Operation->Timeout ) ) == TIM_Status_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Timeout;
            Operation->Handler = NULL;
            break;
        }

        if ( ( Context->Event & LCD_LM6063DCW_A_Event_SPI_Success ) == LCD_LM6063DCW_A_Event_SPI_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Success;
            Operation->Handler = NULL;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationElectronicVolumeExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_ElectronicVolume_t ElectronicVolume )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        Operation->Context.SetElectronicVolume = ( LCD_LM6063DCW_A_SetElectronicVolume_t ) {
            { LCD_LM6063DCW_A_Command_SetElectronicVolume_1, LCD_LM6063DCW_A_Command_SetElectronicVolume_2 }
        };
        Operation->Context.SetElectronicVolume.Level = ElectronicVolume;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &Operation->Context.SetElectronicVolume, UTIL_SizeOf( Operation->Context.SetElectronicVolume ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Operation->Type = LCD_LM6063DCW_A_OperationType_ElectronicVolume;
        Operation->Handler = LCD_LM6063DCW_A_OperationElectronicVolumeResolve;
        Operation->Status = LCD_LM6063DCW_A_Status_Success;
        Operation->Timeout = LCD_LM6063DCW_A_Context.Timestamp;

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_Timestamp_AddMillisecond( &Operation->Timeout, 100 ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationElectronicVolumeResolve( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        if ( Operation->Type != LCD_LM6063DCW_A_OperationType_ElectronicVolume )
        {
            LCD_Error( "%s Got %d Expected %d", __FUNCTION__, Operation->Type, LCD_LM6063DCW_A_OperationType_ElectronicVolume );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_IsExpiredTimestamp( LCD_TIM, &Operation->Timeout ) ) == TIM_Status_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Timeout;
            Operation->Handler = NULL;
            break;
        }

        if ( ( Context->Event & LCD_LM6063DCW_A_Event_SPI_Success ) == LCD_LM6063DCW_A_Event_SPI_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Success;
            Operation->Handler = NULL;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationPageExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Page_t Page )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        Operation->Context.SetPage = ( LCD_LM6063DCW_A_SetPage_t ) { { LCD_LM6063DCW_A_Command_SetPage } };
        Operation->Context.SetPage.Page = Page;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &Operation->Context.SetPage, UTIL_SizeOf( Operation->Context.SetPage ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Operation->Type = LCD_LM6063DCW_A_OperationType_Page;
        Operation->Handler = LCD_LM6063DCW_A_OperationPageResolve;
        Operation->Status = LCD_LM6063DCW_A_Status_Success;
        Operation->Timeout = LCD_LM6063DCW_A_Context.Timestamp;

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_Timestamp_AddMillisecond( &Operation->Timeout, 100 ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationPageResolve( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        if ( Operation->Type != LCD_LM6063DCW_A_OperationType_Page )
        {
            LCD_Error( "%s Got %d Expected %d", __FUNCTION__, Operation->Type, LCD_LM6063DCW_A_OperationType_Page );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_IsExpiredTimestamp( LCD_TIM, &Operation->Timeout ) ) == TIM_Status_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Timeout;
            Operation->Handler = NULL;
            break;
        }

        if ( ( Context->Event & LCD_LM6063DCW_A_Event_SPI_Success ) == LCD_LM6063DCW_A_Event_SPI_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Success;
            Operation->Handler = NULL;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationColumnExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Column_t Column )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        Operation->Context.SetColumn = ( LCD_LM6063DCW_A_SetColumn_t ) {
            { LCD_LM6063DCW_A_Command_SetColumn_1, LCD_LM6063DCW_A_Command_SetColumn_2 }
        };
        Operation->Context.SetColumn.ColumnMSB = ( Column & 0xF0 ) >> 4;
        Operation->Context.SetColumn.ColumnLSB = ( Column & 0x0F ) >> 0;
        if ( ( Status = LCD_LM6063DCW_A_Execute( Instance, ( uint8_t * ) &Operation->Context.SetColumn, UTIL_SizeOf( Operation->Context.SetColumn ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Operation->Type = LCD_LM6063DCW_A_OperationType_Column;
        Operation->Handler = LCD_LM6063DCW_A_OperationColumnResolve;
        Operation->Status = LCD_LM6063DCW_A_Status_Success;
        Operation->Timeout = LCD_LM6063DCW_A_Context.Timestamp;

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_Timestamp_AddMillisecond( &Operation->Timeout, 100 ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationColumnResolve( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        if ( Operation->Type != LCD_LM6063DCW_A_OperationType_Column )
        {
            LCD_Error( "%s Got %d Expected %d", __FUNCTION__, Operation->Type, LCD_LM6063DCW_A_OperationType_Column );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_IsExpiredTimestamp( LCD_TIM, &Operation->Timeout ) ) == TIM_Status_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Timeout;
            Operation->Handler = NULL;
            break;
        }

        if ( ( Context->Event & LCD_LM6063DCW_A_Event_SPI_Success ) == LCD_LM6063DCW_A_Event_SPI_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Success;
            Operation->Handler = NULL;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationFlushExecute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Page_t Page )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        for ( uint32_t column = 0; column < LCD_LM6063DCW_A_WIDTH; ++column )
        {
            Operation->Context.ScreenPage[ column ] = 0x00;
            for ( uint32_t line = 0; line < 8; ++line )
            {
                Operation->Context.ScreenPage[ column ] |= Context->Screen[ Page * 8 + line ][ column ] << line;
            }
        }

        if ( ( Status = LCD_LM6063DCW_A_Transfer( Instance, ( uint8_t * ) Operation->Context.ScreenPage, UTIL_SizeOf( Operation->Context.ScreenPage ) ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Operation->Type = LCD_LM6063DCW_A_OperationType_Flush;
        Operation->Handler = LCD_LM6063DCW_A_OperationFlushResolve;
        Operation->Status = LCD_LM6063DCW_A_Status_Success;
        Operation->Timeout = LCD_LM6063DCW_A_Context.Timestamp;

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_Timestamp_AddMillisecond( &Operation->Timeout, 1000 ) ) != TIM_Status_Success )
        {
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
    }
    while ( 0 );

    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_OperationFlushResolve( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        if ( Operation->Type != LCD_LM6063DCW_A_OperationType_Flush )
        {
            LCD_Error( "%s Got %d Expected %d", __FUNCTION__, Operation->Type, LCD_LM6063DCW_A_OperationType_Flush );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }

        TIM_Status_t TIM_Status = TIM_Status_Error;
        if ( ( TIM_Status = TIM_IsExpiredTimestamp( LCD_TIM, &Operation->Timeout ) ) == TIM_Status_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Timeout;
            Operation->Handler = NULL;
            break;
        }

        if ( ( Context->Event & LCD_LM6063DCW_A_Event_SPI_Success ) == LCD_LM6063DCW_A_Event_SPI_Success )
        {
            Operation->Status = LCD_LM6063DCW_A_Status_Success;
            Operation->Handler = NULL;
            break;
        }
    }
    while ( 0 );

    return Status;
}

#if 0 // TODO Update and Support the following
static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Process_PowerSaveEnter_Handler( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Process.Type != LCD_LM6063DCW_A_ProcessType_PowerSaveEnter )
        {
            LCD_Error( "Invalid Process Handler, Expected %d Found %d", LCD_LM6063DCW_A_ProcessType_PowerSaveEnter, Instance->Context->Process.Type );
            LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_None );
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
                LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_None );
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
            LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_None );
            Status = LCD_LM6063DCW_A_Status_Error;
            break;
        }
        switch ( Instance->Context->Operation.Type )
        {
            case LCD_LM6063DCW_A_OperationType_Pending:
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_OperationPixelsOffExecute( Instance );
                break;
            case LCD_LM6063DCW_A_OperationType_SetPixelsOff:
                Instance->Context->Operation.Status = LCD_LM6063DCW_A_SetDisplayOn_Execute( Instance );
                break;
            case LCD_LM6063DCW_A_OperationType_SetDisplayOn:
            case LCD_LM6063DCW_A_OperationType_None:
            default:
                LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_None );
                break;
        }
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayOff_Resolve( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_SetDisplayOff )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_SetDisplayOff, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_None );
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
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_SetDisplayOff_Resolve;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 100 ); // FIXME Set Appropriate Delay Value
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPixelsOn_Resolve( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_SetPixelsOn )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_SetPixelsOn, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_None );
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
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_SetPixelsOn_Resolve;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 100 ); // FIXME Set Appropriate Delay Value
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Reset_Resolve( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_Reset )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_Reset, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_None );
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
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_Reset_Resolve;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 100 ); // FIXME Set Appropriate Delay Value
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
        Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_PowerSaveEnter );
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
        Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_PowerSaveExit );
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_NOP_Resolve( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );
        if ( Instance->Context->Operation.Type != LCD_LM6063DCW_A_OperationType_NOP )
        {
            LCD_Error( "Invalid Operation Handler, Expected %d Found %d", LCD_LM6063DCW_A_OperationType_NOP, Instance->Context->Operation.Type );
            LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_None );
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
        Instance->Context->Operation.Handler = LCD_LM6063DCW_A_NOP_Resolve;
        Instance->Context->Operation.Status = LCD_LM6063DCW_A_Status_Success;
        Instance->Context->Operation.Timestamp = LCD_LM6063DCW_A_Context.Timestamp;
        LCD_LM6063DCW_A_Delay( Instance, 100 ); // FIXME Set Appropriate Delay Value
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


static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_GetSize_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Size_t * Size )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p, Size=%p )", __FUNCTION__, Instance, Size );
        if ( Size == NULL )
        {
            Status = LCD_LM6063DCW_A_Status_ArgumentInvalid;
            break;
        }

        Size->Height = LCD_LM6063DCW_A_HEIGHT;
        Size->Width = LCD_LM6063DCW_A_WIDTH;
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}

static LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_GetScreen_Execute( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Screen_t ** Screen )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Error;
    do
    {
        LCD_Trace( "%s( Instance=%p, Screen=%p )", __FUNCTION__, Instance, Screen );
        if ( Screen == NULL )
        {
            Status = LCD_LM6063DCW_A_Status_ArgumentInvalid;
            break;
        }

        *Screen = &Instance->Context->Screen;
        Status = LCD_LM6063DCW_A_Status_Success;
    }
    while ( 0 );
    return Status;
}
#endif

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
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        if ( Process->Type != LCD_LM6063DCW_A_ProcessType_None
             || Operation->Type != LCD_LM6063DCW_A_OperationType_None )
        {
            Status = LCD_LM6063DCW_A_Status_Busy;
            break;
        }
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_GetSize( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Size_t * Size )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p, Size=%p )", __FUNCTION__, Instance, Size );

        if ( Instance == NULL || Size == NULL )
        {
            Status = LCD_LM6063DCW_A_Status_ArgumentInvalid;
            break;
        }

        Size->Width = LCD_LM6063DCW_A_WIDTH;
        Size->Height = LCD_LM6063DCW_A_HEIGHT;
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetCursor( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Coordinate_t Coordinate )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p, Coordinate={Row=%d, Column=%d} )", __FUNCTION__, Instance, Coordinate.Row, Coordinate.Column );

        // TODO Implement
        Status = LCD_LM6063DCW_A_Status_NotSupported;
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Write( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Character_t Character )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p, Character=%02X )", __FUNCTION__, Instance, Character );

        // TODO Implement
        Status = LCD_LM6063DCW_A_Status_NotSupported;
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPixel( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Coordinate_t Coordinate, LCD_LM6063DCW_A_Pixel_t Pixel )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p, Coordinate={Row=%d, Column=%d}, Pixel=%02X )", __FUNCTION__, Instance, Coordinate.Row, Coordinate.Column, Pixel );

        if ( Instance == NULL
             || Coordinate.Row < 0
             || Coordinate.Row >= LCD_LM6063DCW_A_HEIGHT
             || Coordinate.Column < 0
             || Coordinate.Column >= LCD_LM6063DCW_A_WIDTH )
        {
            Status = LCD_LM6063DCW_A_Status_ArgumentInvalid;
            break;
        }

        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        LCD_LM6063DCW_A_InstanceContext_t * Context = &LCD_LM6063DCW_A_Context.Context[ Instance->LM6063DCW_A ];
        LCD_LM6063DCW_A_Process_t * Process = &Context->Process;
        LCD_LM6063DCW_A_Operation_t * Operation = &Process->Context.Operation;

        Context->Screen[ Coordinate.Row ][ Coordinate.Column ] = Pixel;
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_GetScreen( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Screen_t ** Screen )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p, Screen=%p )", __FUNCTION__, Instance, Screen );

        if ( Instance == NULL || Screen == NULL )
        {
            Status = LCD_LM6063DCW_A_Status_ArgumentInvalid;
            break;
        }

        // FIXME Do we need to copy it here instead of reference it ?
        *Screen = &Instance->Context->Screen;
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Flush( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Flush );
    }
    while ( 0 );

    return Status;
}

#if 0 // TODO Update and Support the following
LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayOn( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

    #if 0
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        if ( ( Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Status = LCD_LM6063DCW_A_SetDisplayOn_Execute( Instance );
    #endif
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayOff( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

    #if 0
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        if ( ( Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Status = LCD_LM6063DCW_A_SetDisplayOff_Execute( Instance );
    #endif
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetLine( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Line_t Line )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

    #if 0
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        if ( ( Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Status = LCD_LM6063DCW_A_OperationLineExecute( Instance, Line );
    #endif
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPage( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Page_t Page )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

    #if 0
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        if ( ( Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Status = LCD_LM6063DCW_A_OperationPageExecute( Instance, Page );
    #endif
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetColumn( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Column_t Column )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

    #if 0
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        if ( ( Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Status = LCD_LM6063DCW_A_OperationColumnExecute( Instance, Column );
    #endif
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetSEG_Direction( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_SEG_Direction_t SEG_Direction )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

    #if 0
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        if ( ( Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Status = LCD_LM6063DCW_A_Operation_SEG_DirectionExecute( Instance, SEG_Direction );
    #endif
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetDisplayDirection( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_DisplayDirection_t DisplayDirection )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

    #if 0
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        if ( ( Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Status = LCD_LM6063DCW_A_OperationDisplayDirectionExecute( Instance, DisplayDirection );
    #endif
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPixelsOn( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

    #if 0
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        if ( ( Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Status = LCD_LM6063DCW_A_SetPixelsOn_Execute( Instance );
    #endif
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPixelsOff( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

    #if 0
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        if ( ( Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Status = LCD_LM6063DCW_A_OperationPixelsOffExecute( Instance );
    #endif
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetBias( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_Bias_t Bias )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

    #if 0
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        if ( ( Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Status = LCD_LM6063DCW_A_OperationBiasExecute( Instance, Bias );
    #endif
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_Reset( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

    #if 0
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        if ( ( Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Status = LCD_LM6063DCW_A_Reset_Execute( Instance );
    #endif
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetCOM_Direction( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_COM_Direction_t COM_Direction )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

    #if 0
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        if ( ( Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Status = LCD_LM6063DCW_A_Operation_COM_DirectionExecute( Instance, COM_Direction );
    #endif
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetPower( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_PowerBooster_t PowerBooster, LCD_LM6063DCW_A_PowerRegulator_t PowerRegulator, LCD_LM6063DCW_A_PowerFollower_t PowerFollower )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

    #if 0
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        if ( ( Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Status = LCD_LM6063DCW_A_OperationPowerExecute( Instance, PowerBooster, PowerRegulator, PowerFollower );
    #endif
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetRegulationRatio( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_RegulationRatio_t RegulationRatio )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

    #if 0
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        if ( ( Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Status = LCD_LM6063DCW_A_OperationRegulationRatioExecute( Instance, RegulationRatio );
    #endif
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetElectronicVolume( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_ElectronicVolume_t ElectronicVolume )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

    #if 0
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        if ( ( Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Status = LCD_LM6063DCW_A_OperationElectronicVolumeExecute( Instance, ElectronicVolume );
    #endif
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_SetBoosterLevel( LCD_LM6063DCW_A_Instance_t * Instance, LCD_LM6063DCW_A_BoosterLevel_t BoosterLevel )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

    #if 0
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        if ( ( Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Status = LCD_LM6063DCW_A_OperationBoosterLevelExecute( Instance, BoosterLevel );
    #endif
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_PowerSaveEnter( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

    #if 0
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        if ( ( Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Status = LCD_LM6063DCW_A_PowerSaveEnter_Execute( Instance );
    #endif
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_PowerSaveExit( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

    #if 0
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        if ( ( Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Status = LCD_LM6063DCW_A_PowerSaveExit_Execute( Instance );
    #endif
    }
    while ( 0 );

    return Status;
}

LCD_LM6063DCW_A_Status_t LCD_LM6063DCW_A_NOP( LCD_LM6063DCW_A_Instance_t * Instance )
{
    LCD_LM6063DCW_A_Status_t Status = LCD_LM6063DCW_A_Status_Success;

    do
    {
        LCD_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

    #if 0
        if ( ( Status = LCD_LM6063DCW_A_IsReady( Instance ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        if ( ( Status = LCD_LM6063DCW_A_SetProcess( Instance, LCD_LM6063DCW_A_ProcessType_Command ) ) != LCD_LM6063DCW_A_Status_Success )
        {
            break;
        }

        Status = LCD_LM6063DCW_A_NOP_Execute( Instance );
    #endif
    }
    while ( 0 );

    return Status;
}
#endif

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

const char LCD_LM6063DCW_A_VERSION[] = "0.0.0.v20260412-1852";

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
