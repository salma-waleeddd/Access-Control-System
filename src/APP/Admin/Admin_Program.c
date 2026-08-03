#include <string.h>
#include <stdlib.h>
#include <util/delay.h>
#include "Admin_Interface.h"
#include "Admin_Private.h"
#include "../../MCAL/EEPROM/EEPROM_Interface.h"
#include "../../HAL/KEYPAD/KYP_Interface.h"
#include "../../HAL/LCD/LCD_Interface.h"

static char Admin_Pins[Admin_MaxUsers][Admin_PinSlotLen];
static uint8_t Admin_UserCount = 0;

static void Admin_ClearAndHome()
{
    LCD_Instruction(LCD_ClearScreen, LCD_8bitMode);
    LCD_Go_To_XY(0, 0);
}

static void Admin_ScanPassword(uint8_t x, uint8_t y, char *buffer, uint8_t maxLen)
{
    uint8_t index = 0;
    uint8_t key;

    LCD_Go_To_XY(x, y);
    while(1)
    {
        key = KPD_GetButtonValue();
        if(key == 0xFF)
        {
            continue;
        }
        if(key == '#')
        {
            break;
        }
        if(index < (uint8_t)(maxLen - 1))
        {
            buffer[index] = (char)key;
            index++;
            LCD_WriteData('*', LCD_8bitMode);
            _delay_ms(100);
        }
    }
    buffer[index] = '\0';
}

static void Admin_ScanInput(uint8_t x, uint8_t y, char *buffer, uint8_t maxLen)
{
    uint8_t index = 0;
    uint8_t key;

    LCD_Go_To_XY(x, y);
    while(1)
    {
        key = KPD_GetButtonValue();
        if(key == 0xFF)
        {
            continue;
        }
        if(key == '#')
        {
            break;
        }
        if(index < (uint8_t)(maxLen - 1))
        {
            buffer[index] = (char)key;
            index++;
            LCD_WriteData(key, LCD_8bitMode);
            _delay_ms(100);
        }
    }
    buffer[index] = '\0';
}

static void Admin_Save()
{
    uint8_t i, j;
    uint8_t Byte;

    Byte = Admin_UserCount;
    EEPROM_WriteData(Admin_EepromCountAddr, &Byte);
    for(i = 0; i < Admin_UserCount; i++)    // represents the number of users
    {
        for(j = 0; j < Admin_PinSlotLen; j++)  // reprsents the values of each slot of the user pin (we have 5 slots for each user, 4 for the pin and 1 for the null terminator)
        {
            Byte = (uint8_t)Admin_Pins[i][j]; // copy the value of the pin slot to the byte variable
            EEPROM_WriteData(Admin_EepromPinsAddr + (i * Admin_PinSlotLen) + j, &Byte); // wrute the value of the pin slot to the EEPROM at the correct address
        }
    }
    Byte = Admin_EepromMarkerValue;
    EEPROM_WriteData(Admin_EepromMarkerAddr, &Byte);
}

void Admin_Init()
{
    uint8_t i, j;
    uint8_t Marker;
    uint8_t Byte;

    EEPROM_ReadData(Admin_EepromMarkerAddr, &Marker);
    if(Marker == Admin_EepromMarkerValue)
    {
        EEPROM_ReadData(Admin_EepromCountAddr, &Byte);
        Admin_UserCount = Byte;
        if(Admin_UserCount > Admin_MaxUsers)
        {
            Admin_UserCount = Admin_MaxUsers;
        }

        for(i = 0; i < Admin_UserCount; i++)
        {
            for(j = 0; j < Admin_PinSlotLen; j++)
            {
                EEPROM_ReadData(Admin_EepromPinsAddr + (i * Admin_PinSlotLen) + j, &Byte);
                Admin_Pins[i][j] = (char)Byte;
            }
        }
    }
    else {
        // only first boot
        Admin_UserCount = 1;
        memcpy(Admin_Pins[0], "1234", Admin_PinLen);
        Admin_Pins[0][Admin_PinLen] = '\0';
        Admin_Save();
    }
}

uint8_t Admin_Count() {
    return Admin_UserCount;
}

uint8_t Admin_Authenticate(const char *Pin) {  
    uint8_t i;

    for(i = 0; i < Admin_UserCount; i++)
    {
        if(strcmp(Admin_Pins[i], Pin) == 0)
        {
            return i;
        }
    }
    return Admin_InvalidId;
}

static uint8_t Admin_AddUser(const char *Pin) {
    if(Admin_UserCount >= Admin_MaxUsers)
    {
        return 0;
    }

    memcpy(Admin_Pins[Admin_UserCount], Pin, Admin_PinLen);
    Admin_Pins[Admin_UserCount][Admin_PinLen] = '\0';
    Admin_UserCount++;                                     //////////
    Admin_Save();
    return 1;
}

static uint8_t Admin_RemoveUser(uint8_t Index) {
    uint8_t i;

    if(Index >= Admin_UserCount)
    {
        return 0;
    }

    for(i = Index; i < (uint8_t)(Admin_UserCount - 1); i++)
    {
        strcpy(Admin_Pins[i], Admin_Pins[i + 1]);
    }
    Admin_UserCount--;
    Admin_Save();
    return 1;
}

static uint8_t Admin_ChangePin(uint8_t Index, const char *NewPin) {
    if(Index >= Admin_UserCount)
    {
        return 0;
    }

    memcpy(Admin_Pins[Index], NewPin, Admin_PinLen);
    Admin_Pins[Index][Admin_PinLen] = '\0';
    Admin_Save();
    return 1;
}

static void Admin_HandleAdd() /////////
{
    char Pin[Admin_PinLen + 1];
    char PinConfirm[Admin_PinLen + 1];

    if(Admin_UserCount >= Admin_MaxUsers)
    {
        Admin_ClearAndHome();
        LCD_WriteString((uint8_t *)"Full database", LCD_8bitMode);
        _delay_ms(2500);
        return;
    }

    Admin_ClearAndHome();
    LCD_WriteString((uint8_t *)"New PIN:", LCD_8bitMode);
    Admin_ScanPassword(1, 0, Pin, Admin_PinLen + 1);

    Admin_ClearAndHome();
    LCD_WriteString((uint8_t *)"Confirm PIN:", LCD_8bitMode);
    Admin_ScanPassword(1, 0, PinConfirm, Admin_PinLen + 1);

    Admin_ClearAndHome();
    if(strcmp(Pin, PinConfirm) == 0)
    {
        Admin_AddUser(Pin);
        LCD_WriteString((uint8_t *)"User Added!", LCD_8bitMode);
    }
    else
    {
        LCD_WriteString((uint8_t *)"PINs don't match", LCD_8bitMode);
    }
    _delay_ms(2500);
}

static void Admin_HandleRemove()
{
    char IndexBuffer[3];

    if(Admin_UserCount == 0)
    {
        Admin_ClearAndHome();
        LCD_WriteString((uint8_t *)"No users", LCD_8bitMode);
        _delay_ms(2000);
        return;
    }

    Admin_ClearAndHome();
    LCD_WriteString((uint8_t *)"User # (0-idx):", LCD_8bitMode);
    Admin_ScanInput(1, 0, IndexBuffer, sizeof(IndexBuffer));

    Admin_ClearAndHome();
    int UserInput = IndexBuffer[0] - '0'; // better atoi to be used
    if(Admin_RemoveUser((uint8_t)UserInput))
    {
        LCD_WriteString((uint8_t *)"User deleted!", LCD_8bitMode);
    }
    else
    {
        LCD_WriteString((uint8_t *)"No such user.", LCD_8bitMode);
    }
    _delay_ms(2000);
}

static void Admin_HandleChange()
{
    char IndexBuffer[3];
    char NewPin[Admin_PinLen + 1];
    char ConfirmPin[Admin_PinLen + 1];
    uint8_t Index;

    if(Admin_UserCount == 0)
    {
        Admin_ClearAndHome();
        LCD_WriteString((uint8_t *)"No users", LCD_8bitMode);
        _delay_ms(2000);
        return;
    }

    Admin_ClearAndHome();
    LCD_WriteString((uint8_t *)"User # (0-idx):", LCD_8bitMode);
    Admin_ScanInput(1, 0, IndexBuffer, sizeof(IndexBuffer));
    int UserInput = IndexBuffer[0] - '0'; // better atoi to be used
    Index = (uint8_t)UserInput;

    if(Index >= Admin_UserCount){
        Admin_ClearAndHome();
        LCD_WriteString((uint8_t *)"No such user.", LCD_8bitMode);
        _delay_ms(2000);
        return;
    }

    Admin_ClearAndHome();
    LCD_WriteString((uint8_t *)"New PIN:", LCD_8bitMode);
    Admin_ScanPassword(1, 0, NewPin, Admin_PinLen + 1);

    Admin_ClearAndHome();
    LCD_WriteString((uint8_t *)"Confirm PIN:", LCD_8bitMode);
    Admin_ScanPassword(1, 0, ConfirmPin, Admin_PinLen + 1);

    Admin_ClearAndHome();
    if(strcmp(NewPin, ConfirmPin) == 0){
        Admin_ChangePin(Index, NewPin);
        LCD_WriteString((uint8_t *)"PIN changed!", LCD_8bitMode);
    }
    else {
        LCD_WriteString((uint8_t *)"PINs don't match", LCD_8bitMode);
    }
    _delay_ms(2000);
}

void Admin_RunMenu() { ////////////// ADMIN MENU
    uint8_t Running = 1;
    uint8_t MenuKey;

    while(Running)
    {
        Admin_ClearAndHome();
        LCD_WriteString((uint8_t *)"1)Add  2)Remove", LCD_8bitMode);
        LCD_Go_To_XY(1, 0);
        LCD_WriteString((uint8_t *)"3)Chg  4)Exit", LCD_8bitMode);

        do
        {
            MenuKey = KPD_GetButtonValue();
        } while(MenuKey == 0xFF);

        switch(MenuKey)
        {
            case '1':
                Admin_HandleAdd();
                break;
            case '2':
                Admin_HandleRemove();
                break;
            case '3':
                Admin_HandleChange();
                break;
            case '4':
                Running = 0;
                break;
            default:
                Admin_ClearAndHome();
                LCD_WriteString((uint8_t *)"Wrong Choice", LCD_8bitMode);
                _delay_ms(2500);
                break;
        }
    }
}
