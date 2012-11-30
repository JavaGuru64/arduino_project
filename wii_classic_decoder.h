//
//  wii_classic_decoder.h
//  
//
//  Created by Joshua Long on 11/25/12.
//
//

#include <math.h>
#include <Arduino.h>
static uint8_t data_pack[6];

static void load_packet(uint8_t packet[])
{
    for(int i=0; i<6; i++)
    {
        data_pack[i] = packet[i];
    }
}

static void print_data()
{
    
    int l_joy_x = 0; // Left Joystick x value.
    int l_joy_y = 0; // Left Joystick y value.
    int r_joy_x = 0; // Right Joystick x value.
    int r_joy_y = 0; // Right Joystick y value.
    int pad_up = 0; // Plus pad up.
    int pad_dn = 0; // Plus pad down.
    int pad_lt = 0; // Plus pad left.
    int pad_rt = 0; // Plus pad right.
    int la_tgr = 0; // Left trigger < L Button > analog.
    int ra_tgr = 0; // Right trigger < R Button > analog.
    int ld_tgr = 0; // Left trigger < L Button > digital.
    int rd_tgr = 0; // Right trigger < R Button > digital.
    int zl_tgr = 0; // Left z trigger < ZL Button >.
    int zr_tgr = 0; // Right z trigger < ZR Button >.
    int ab = 0; // A Button.
    int bb = 0; // B Button.
    int xb = 0; // X Button.
    int yb = 0; // Y Button.
    int plus = 0; // (+) Start Button.
    int minus = 0; // (-) Select Button.
    int bhome = 0; // Home Button.
    
    Serial.print("joy_L: ");
    
    for(int i = 0; i < 6; i++)
    {
        l_joy_x += ((data_pack[0] >> i) & 1) * pow(2, i);
    }
    
    Serial.print(l_joy_x, DEC);
    Serial.print(", ");
    
    for(int i = 0; i < 6; i++)
    {
        l_joy_y += ((data_pack[1] >> i) & 1) * pow(2, i);
    }
    
    Serial.println(l_joy_y, DEC);
    Serial.print("joy_R: ");
    
    r_joy_x += ((data_pack[2] >> 7) & 1) * pow(2, 0);
    r_joy_x += ((data_pack[1] >> 6) & 1) * pow(2, 1);
    r_joy_x += ((data_pack[1] >> 7) & 1) * pow(2, 2);
    r_joy_x += ((data_pack[0] >> 6) & 1) * pow(2, 3);
    r_joy_x += ((data_pack[0] >> 7) & 1) * pow(2, 4);
    
    Serial.print(r_joy_x, DEC);
    Serial.print(", ");
    
    for(int i = 0; i < 5; i++)
    {
        r_joy_y += ((data_pack[2] >> i) & 1) * pow(2, i);
    }
    
    Serial.println(r_joy_y, DEC);
    Serial.print("Plus_Pad: ");
    
    pad_up =(data_pack[5] >> 0) & 1;
    
    Serial.print(pad_up, DEC);
    Serial.print(", ");
    
    pad_dn =(data_pack[4] >> 6) & 1;
    
    Serial.print(pad_dn, DEC);
    Serial.print(", ");
    
    pad_lt = (data_pack[5] >> 1) & 1;
    
    Serial.print(pad_lt, DEC);
    Serial.print(", ");
    
    pad_rt = (data_pack[4] >> 7) & 1;
    
    Serial.println(pad_rt, DEC);
    
    Serial.print("Triggers_Analog: L = ");
    
    la_tgr += ((data_pack[3] >> 5) & 1) * pow(2, 0);
    la_tgr += ((data_pack[3] >> 6) & 1) * pow(2, 1);
    la_tgr += ((data_pack[3] >> 7) & 1) * pow(2, 2);
    la_tgr += ((data_pack[2] >> 5) & 1) * pow(2, 3);
    la_tgr += ((data_pack[2] >> 6) & 1) * pow(2, 4);
    
    Serial.print(la_tgr, DEC);
    Serial.print("  R = ");
    
    for(int i = 0; i < 5; i++)
    {
        ra_tgr += ((data_pack[3] >> i) & 1) * pow(2, i);
    }
    
    Serial.println(ra_tgr, DEC);
    Serial.print("Triggers_Digital: L = ");
    
    ld_tgr = (data_pack[4] >> 5)  & 1;
    
    Serial.print(ld_tgr, DEC);
    Serial.print(" R = ");
    
    rd_tgr = (data_pack[4] >> 1) & 1;
    
    Serial.print(rd_tgr, DEC);
    Serial.print(" ZL = ");
    
    zl_tgr = (data_pack[5] >> 7) & 1;
    
    Serial.print(zl_tgr, DEC);
    Serial.print(" ZR = ");
    
    zr_tgr = (data_pack[5] >> 2) & 1;
    
    Serial.println(zr_tgr, DEC);
    Serial.print("ABXY_Buttons: A = ");
    
    ab = (data_pack[5] >> 4) & 1;
    
    Serial.print(ab, DEC);
    Serial.print(",  B = ");
    
    bb = (data_pack[5] >> 6) & 1;
    
    Serial.print(bb, DEC);
    Serial.print(",  X = ");
    
    xb = (data_pack[5] >> 3) & 1;
    
    Serial.print(xb, DEC);
    Serial.print(",  Y = ");
    
    yb = (data_pack[5] >> 5) & 1;
    
    Serial.println(yb, DEC);
    Serial.print("Special_Buttons: (+) start = ");
    
    plus = (data_pack[4] >> 2) & 1;
    
    Serial.print(plus, DEC);
    Serial.print(",  (-) select = ");
    
    minus = (data_pack[4] >> 4) & 1;
    
    Serial.print(minus, DEC);
    Serial.print(",  Home = ");
    
    bhome = (data_pack[4] >> 3) & 1;
    
    Serial.println(bhome, DEC);
    
    Serial.println("");
}

// Joysticks
static int get_l_joy_x()
{
    int val = 0;
    for(int i = 0; i < 6; i++)
    {
        val += ((data_pack[0] >> i) & 1) * pow(2, i);
    }
    return val;
}

static int get_l_joy_y()
{
    int val = 0;
    for(int i = 0; i < 6; i++)
    {
        val += ((data_pack[1] >> i) & 1) * pow(2, i);
    }
    return val;
}

static int get_r_joy_x()
{
    // This value is wierd and spread out between 3 bytes of data
    // so it is easier to hardcode this.
    int val = 0;
    val += ((data_pack[2] >> 70) & 1) * pow(2, 0);
    val += ((data_pack[1] >> 6) & 1) * pow(2, 1);
    val += ((data_pack[1] >> 7) & 1) * pow(2, 2);
    val += ((data_pack[0] >> 6) & 1) * pow(2, 3);
    val += ((data_pack[0] >> 7) & 1) * pow(2, 4);
    return val;
}

static int get_r_joy_y()
{
    int val = 0;
    for(int i = 0; i < 5; i++)
    {
        val += ((data_pack[2] >> i) & 1) * pow(2, i);
    }
    return val;
}

// PlusPad buttons
static int get_pad_up()
{
    // If a button is pressed it comes back as a 0.
    // We need to reverse this for boolean value's sake where 1 = true
    return ((data_pack[5] >> 0) & 1) ? 0 : 1;
}

static int get_pad_dn()
{
    return ((data_pack[4] >> 6) & 1) ? 0 : 1;
}

static int get_pad_lt()
{
    return ((data_pack[5] >> 2) & 1) ? 0 : 1;
}

static int get_pad_rt()
{
    return ((data_pack[4] >> 7) & 1) ? 0 : 1;
}

// Triggers Analog
static int get_la_tgr()
{
    // Another strange value.
    int val = 0;
    val += ((data_pack[3] >> 5) & 1) * pow(2, 0);
    val += ((data_pack[3] >> 6) & 1) * pow(2, 1);
    val += ((data_pack[3] >> 7) & 1) * pow(2, 2);
    val += ((data_pack[2] >> 5) & 1) * pow(2, 3);
    val += ((data_pack[2] >> 6) & 1) * pow(2, 4);
    return val;
}

static int get_ra_tgr()
{
    int val = 0;
    for(int i = 0; i < 5; i++)
    {
        val += ((data_pack[3] >> i) & 1) * pow(2, i);
    }
    return val;
}

// Triggers Digital
static int get_ld_tgr()
{
    return ((data_pack[4] >> 5) & 1) ? 0 : 1;
}

static int get_rd_tgr()
{
    return ((data_pack[4] >> 1) & 1) ? 0 : 1;
}

static int get_zl_tgr()
{
    return ((data_pack[5] >> 7) & 1) ? 0 : 1;
}

static int get_zr_tgr()
{
    return ((data_pack[5] >> 2) & 1) ? 0 : 1;
}

// ABXY Buttons
static int get_ab()
{
    return ((data_pack[5] >> 4) & 1) ? 0 : 1;
}

static int get_bb()
{
    return ((data_pack[5] >> 6) & 1) ? 0 : 1;
}

static int get_xb()
{
    return ((data_pack[5] >> 3) & 1) ? 0 : 1;
}

static int get_yb()
{
    return ((data_pack[5] >> 5) & 1) ? 0 : 1;
}

// Special Buttons
static int get_plus()
{
    return ((data_pack[4] >> 2) & 1) ? 0 : 1;
}

static int get_minus()
{
    return ((data_pack[4] >> 4) & 1) ? 0 : 1;
}

static int get_home()
{
    return ((data_pack[4] >> 3) & 1) ? 0 : 1;
}
