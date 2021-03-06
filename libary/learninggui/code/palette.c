/*   
 *  Copyright (C) 2011- 2018 Rao Youkun(960747373@qq.com)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 */

#include  <string.h>

#include  <lock.h>

#include  <screen.h>

#include  <palette.h>


    
#ifdef  _LG_COMMON_PALETTE_
static  GUI_DATA_CONST  GUI_COLOR  l1pal_color[] = 
{
    0x00000000,0x00FFFFFF
};

GUI_VAR_CONST  GUI_PALETTE  l1pal = 
{
    /* .num      = */ sizeof(l1pal_color)/sizeof(GUI_COLOR),
    /* .entries  = */ (GUI_COLOR *)l1pal_color
};

static  GUI_DATA_CONST  GUI_COLOR  l2pal_color[] = 
{
    0x000000FF,0x00FF00FF,0x0000FFFF,0x00FFFFFF
};

GUI_VAR_CONST  GUI_PALETTE  l2pal = 
{
    /* .num      = */ sizeof(l2pal_color)/sizeof(GUI_COLOR),
    /* .entries  = */ (GUI_COLOR *)l2pal_color
};

static  GUI_DATA_CONST  GUI_COLOR  l4pal_color[ ] = 
{
    0x00000000,0x00800000,0x00008000,0x00808000,
    0x00000080,0x00800080,0x00008080,0x00808080,
    0x00C0C0C0,0x00FF0000,0x0000FF00,0x00FFFF00,
    0x000000FF,0x00FF00FF,0x0000FFFF,0x00FFFFFF
};

GUI_VAR_CONST  GUI_PALETTE  l4pal = 
{
    /* .num      = */ sizeof(l4pal_color)/sizeof(GUI_COLOR),
    /* .entries  = */ (GUI_COLOR *)l4pal_color
};

static  GUI_DATA_CONST  GUI_COLOR  l8pal_color[ ] = 
{
    0x00000000,0x00800000,0x00008000,0x00808000,
    0x00000080,0x00800080,0x00008080,0x00C0C0C0,
    0x00C0DCC0,0x00A6CAF0,0x00402000,0x00602000,
    0x00802000,0x00A02000,0x00C02000,0x00E02000,
    0x00004000,0x00204000,0x00404000,0x00604000,
    0x00804000,0x00A04000,0x00C04000,0x00E04000,
    0x00006000,0x00206000,0x00406000,0x00606000,
    0x00806000,0x00A06000,0x00C06000,0x00E06000,
    0x00008000,0x00208000,0x00408000,0x00608000,
    0x00808000,0x00A08000,0x00C08000,0x00E08000,
    0x0000A000,0x0020A000,0x0040A000,0x0060A000,
    0x0080A000,0x00A0A000,0x00C0A000,0x00E0A000,
    0x0000C000,0x0020C000,0x0040C000,0x0060C000,
    0x0080C000,0x00A0C000,0x00C0C000,0x00E0C000,
    0x0000E000,0x0020E000,0x0040E000,0x0060E000,
    0x0080E000,0x00A0E000,0x00C0E000,0x00E0E000,
    0x00000040,0x00200040,0x00400040,0x00600040,
    0x00800040,0x00A00040,0x00C00040,0x00E00040,
    0x00002040,0x00202040,0x00402040,0x00602040,
    0x00802040,0x00A02040,0x00C02040,0x00E02040,
    0x00004040,0x00204040,0x00404040,0x00604040,
    0x00804040,0x00A04040,0x00C04040,0x00E04040,
    0x00006040,0x00206040,0x00406040,0x00606040,
    0x00806040,0x00A06040,0x00C06040,0x00E06040,
    0x00008040,0x00208040,0x00408040,0x00608040,
    0x00808040,0x00A08040,0x00C08040,0x00E08040,
    0x0000A040,0x0020A040,0x0040A040,0x0060A040,
    0x0080A040,0x00A0A040,0x00C0A040,0x00E0A040,
    0x0000C040,0x0020C040,0x0040C040,0x0060C040,
    0x0080C040,0x00A0C040,0x00C0C040,0x00E0C040,
    0x0000E040,0x0020E040,0x0040E040,0x0060E040,
    0x0080E040,0x00A0E040,0x00C0E040,0x00E0E040,
    0x00000080,0x00200080,0x00400080,0x00600080,
    0x00800080,0x00A00080,0x00C00080,0x00E00080,
    0x00002080,0x00202080,0x00402080,0x00602080,
    0x00802080,0x00A02080,0x00C02080,0x00E02080,
    0x00004080,0x00204080,0x00404080,0x00604080,
    0x00804080,0x00A04080,0x00C04080,0x00E04080,
    0x00006080,0x00206080,0x00406080,0x00606080,
    0x00806080,0x00A06080,0x00C06080,0x00E06080,
    0x00008080,0x00208080,0x00408080,0x00608080,
    0x00808080,0x00A08080,0x00C08080,0x00E08080,
    0x0000A080,0x0020A080,0x0040A080,0x0060A080,
    0x0080A080,0x00A0A080,0x00C0A080,0x00E0A080,
    0x0000C080,0x0020C080,0x0040C080,0x0060C080,
    0x0080C080,0x00A0C080,0x00C0C080,0x00E0C080,
    0x0000E080,0x0020E080,0x0040E080,0x0060E080,
    0x0080E080,0x00A0E080,0x00C0E080,0x00E0E080,
    0x000000C0,0x002000C0,0x004000C0,0x006000C0,
    0x008000C0,0x00A000C0,0x00C000C0,0x00E000C0,
    0x000020C0,0x002020C0,0x004020C0,0x006020C0,
    0x008020C0,0x00A020C0,0x00C020C0,0x00E020C0,
    0x000040C0,0x002040C0,0x004040C0,0x006040C0,
    0x008040C0,0x00A040C0,0x00C040C0,0x00E040C0,
    0x000060C0,0x002060C0,0x004060C0,0x006060C0,
    0x008060C0,0x00A060C0,0x00C060C0,0x00E060C0,
    0x000080C0,0x002080C0,0x004080C0,0x006080C0,
    0x008080C0,0x00A080C0,0x00C080C0,0x00E080C0,
    0x0000A0C0,0x0020A0C0,0x0040A0C0,0x0060A0C0,
    0x0080A0C0,0x00A0A0C0,0x00C0A0C0,0x00E0A0C0,
    0x0000C0C0,0x0020C0C0,0x0040C0C0,0x0060C0C0,
    0x0080C0C0,0x00A0C0C0,0x00FFFBF0,0x00A0A0A4,
    0x00808080,0x00FF0000,0x0000FF00,0x00FFFF00,
    0x000000FF,0x00FF00FF,0x0000FFFF,0x00FFFFFF
};

GUI_VAR_CONST  GUI_PALETTE  l8pal = 
{
    /* .num      = */ sizeof(l8pal_color)/sizeof(GUI_COLOR),
    /* .entries  = */ (GUI_COLOR *)l8pal_color
};
#endif  /* _LG_COMMON_PALETTE_ */


#ifdef  _LG_PALETTE_ROUTINE_

/* 
 * Do not delete this code. Because it can be read or writen. 
 */
  
#ifdef  _LG_8_BIT_SYSTEM_PALETTE_
static  GUI_COLOR  lpal_color[ ] = 
{
    0x00000000,0x00800000,0x00008000,0x00808000,
    0x00000080,0x00800080,0x00008080,0x00C0C0C0,
    0x00C0DCC0,0x00A6CAF0,0x00402000,0x00602000,
    0x00802000,0x00A02000,0x00C02000,0x00E02000,
    0x00004000,0x00204000,0x00404000,0x00604000,
    0x00804000,0x00A04000,0x00C04000,0x00E04000,
    0x00006000,0x00206000,0x00406000,0x00606000,
    0x00806000,0x00A06000,0x00C06000,0x00E06000,
    0x00008000,0x00208000,0x00408000,0x00608000,
    0x00808000,0x00A08000,0x00C08000,0x00E08000,
    0x0000A000,0x0020A000,0x0040A000,0x0060A000,
    0x0080A000,0x00A0A000,0x00C0A000,0x00E0A000,
    0x0000C000,0x0020C000,0x0040C000,0x0060C000,
    0x0080C000,0x00A0C000,0x00C0C000,0x00E0C000,
    0x0000E000,0x0020E000,0x0040E000,0x0060E000,
    0x0080E000,0x00A0E000,0x00C0E000,0x00E0E000,
    0x00000040,0x00200040,0x00400040,0x00600040,
    0x00800040,0x00A00040,0x00C00040,0x00E00040,
    0x00002040,0x00202040,0x00402040,0x00602040,
    0x00802040,0x00A02040,0x00C02040,0x00E02040,
    0x00004040,0x00204040,0x00404040,0x00604040,
    0x00804040,0x00A04040,0x00C04040,0x00E04040,
    0x00006040,0x00206040,0x00406040,0x00606040,
    0x00806040,0x00A06040,0x00C06040,0x00E06040,
    0x00008040,0x00208040,0x00408040,0x00608040,
    0x00808040,0x00A08040,0x00C08040,0x00E08040,
    0x0000A040,0x0020A040,0x0040A040,0x0060A040,
    0x0080A040,0x00A0A040,0x00C0A040,0x00E0A040,
    0x0000C040,0x0020C040,0x0040C040,0x0060C040,
    0x0080C040,0x00A0C040,0x00C0C040,0x00E0C040,
    0x0000E040,0x0020E040,0x0040E040,0x0060E040,
    0x0080E040,0x00A0E040,0x00C0E040,0x00E0E040,
    0x00000080,0x00200080,0x00400080,0x00600080,
    0x00800080,0x00A00080,0x00C00080,0x00E00080,
    0x00002080,0x00202080,0x00402080,0x00602080,
    0x00802080,0x00A02080,0x00C02080,0x00E02080,
    0x00004080,0x00204080,0x00404080,0x00604080,
    0x00804080,0x00A04080,0x00C04080,0x00E04080,
    0x00006080,0x00206080,0x00406080,0x00606080,
    0x00806080,0x00A06080,0x00C06080,0x00E06080,
    0x00008080,0x00208080,0x00408080,0x00608080,
    0x00808080,0x00A08080,0x00C08080,0x00E08080,
    0x0000A080,0x0020A080,0x0040A080,0x0060A080,
    0x0080A080,0x00A0A080,0x00C0A080,0x00E0A080,
    0x0000C080,0x0020C080,0x0040C080,0x0060C080,
    0x0080C080,0x00A0C080,0x00C0C080,0x00E0C080,
    0x0000E080,0x0020E080,0x0040E080,0x0060E080,
    0x0080E080,0x00A0E080,0x00C0E080,0x00E0E080,
    0x000000C0,0x002000C0,0x004000C0,0x006000C0,
    0x008000C0,0x00A000C0,0x00C000C0,0x00E000C0,
    0x000020C0,0x002020C0,0x004020C0,0x006020C0,
    0x008020C0,0x00A020C0,0x00C020C0,0x00E020C0,
    0x000040C0,0x002040C0,0x004040C0,0x006040C0,
    0x008040C0,0x00A040C0,0x00C040C0,0x00E040C0,
    0x000060C0,0x002060C0,0x004060C0,0x006060C0,
    0x008060C0,0x00A060C0,0x00C060C0,0x00E060C0,
    0x000080C0,0x002080C0,0x004080C0,0x006080C0,
    0x008080C0,0x00A080C0,0x00C080C0,0x00E080C0,
    0x0000A0C0,0x0020A0C0,0x0040A0C0,0x0060A0C0,
    0x0080A0C0,0x00A0A0C0,0x00C0A0C0,0x00E0A0C0,
    0x0000C0C0,0x0020C0C0,0x0040C0C0,0x0060C0C0,
    0x0080C0C0,0x00A0C0C0,0x00FFFBF0,0x00A0A0A4,
    0x00808080,0x00FF0000,0x0000FF00,0x00FFFF00,
    0x000000FF,0x00FF00FF,0x0000FFFF,0x00FFFFFF
};
#else  /* _LG_8_BIT_SYSTEM_PALETTE_ */
static  GUI_COLOR  lpal_color[] = 
{
    0x00000000,0x00800000,0x00008000,0x00808000,
    0x00000080,0x00800080,0x00008080,0x00808080,
    0x00C0C0C0,0x00FF0000,0x0000FF00,0x00FFFF00,
    0x000000FF,0x00FF00FF,0x0000FFFF,0x00FFFFFF
};
#endif  /* _LG_8_BIT_SYSTEM_PALETTE_ */

GUI_PALETTE  lpal = 
{
    /* .num      = */ sizeof(lpal_color)/sizeof(GUI_COLOR),
    /* .entries  = */ (GUI_COLOR *)lpal_color
};


int  in_palette_set(void *palette)
{
    GUI_PALETTE *pal = (GUI_PALETTE *)palette;


    if ( pal == NULL )
        return  -1;
    if ( (pal->num) == 0 )
        return  -1;
    if ( (pal->entries) == NULL )
        return  -1;

    memcpy((void *)(lpal.entries), (const void *)(pal->entries), (pal->num)*sizeof(GUI_COLOR));
    lpal.num = pal->num;

    if ( (lscrn.palette_set) != NULL )
        (lscrn.palette_set)(palette);

    return  1;
}

#ifndef  _LG_ALONE_VERSION_
int  palette_set(void *palette)
{
    int  ret = 0;

    gui_lock();
    ret = in_palette_set(palette);
    gui_unlock( );

    return  ret;
}
#endif  /* _LG_ALONE_VERSION_ */

int  in_palette_get(void *palette)
{
    GUI_PALETTE *pal = (void *)palette;


    if (pal == NULL)
        return  -1;
    if ((pal->num) == 0)
        return  -1;
    if ((pal->entries) == NULL)
        return  -1;

    if ( (lscrn.palette_get) != NULL)
        (lscrn.palette_get)(pal);

    /* Fix me */
    memcpy((void *)(pal->entries), (const void *)(lpal.entries), (lpal.num)*sizeof(GUI_COLOR));
    pal->num = lpal.num;

    return  1;
}

#ifndef  _LG_ALONE_VERSION_
int  palette_get(void *palette)
{
    int  ret = 0;

    gui_lock( );
    ret = in_palette_get(palette);
    gui_unlock( );

    return  ret;
}
#endif  /* _LG_ALONE_VERSION_ */

 
#ifdef  _LG_RESTORE_SYSTEM_PALETTE_
int  in_palette_restore_system(void)
{
#ifdef  _LG_8_BIT_SYSTEM_PALETTE_
    gpal.num     = 256;

    gpal.entries[0x00] = 0x00000000;
    gpal.entries[0x01] = 0x00800000;
    gpal.entries[0x02] = 0x00008000;
    gpal.entries[0x03] = 0x00808000;
    gpal.entries[0x04] = 0x00000080;
    gpal.entries[0x05] = 0x00800080;
    gpal.entries[0x06] = 0x00008080;
    gpal.entries[0x07] = 0x00C0C0C0;
    gpal.entries[0x08] = 0x00C0DCC0;
    gpal.entries[0x09] = 0x00A6CAF0;
    gpal.entries[0x0A] = 0x00402000;
    gpal.entries[0x0B] = 0x00602000;
    gpal.entries[0x0C] = 0x00802000;
    gpal.entries[0x0D] = 0x00A02000;
    gpal.entries[0x0E] = 0x00C02000;
    gpal.entries[0x0F] = 0x00E02000;
    gpal.entries[0x10] = 0x00004000;
    gpal.entries[0x11] = 0x00204000;
    gpal.entries[0x12] = 0x00404000;
    gpal.entries[0x13] = 0x00604000;
    gpal.entries[0x14] = 0x00804000;
    gpal.entries[0x15] = 0x00A04000;
    gpal.entries[0x16] = 0x00C04000;
    gpal.entries[0x17] = 0x00E04000;
    gpal.entries[0x18] = 0x00006000;
    gpal.entries[0x19] = 0x00206000;
    gpal.entries[0x1A] = 0x00406000;
    gpal.entries[0x1B] = 0x00606000;
    gpal.entries[0x1C] = 0x00806000;
    gpal.entries[0x1D] = 0x00A06000;
    gpal.entries[0x1E] = 0x00C06000;
    gpal.entries[0x1F] = 0x00E06000;
    gpal.entries[0x20] = 0x00008000;
    gpal.entries[0x21] = 0x00208000;
    gpal.entries[0x22] = 0x00408000;
    gpal.entries[0x23] = 0x00608000;
    gpal.entries[0x24] = 0x00808000;
    gpal.entries[0x25] = 0x00A08000;
    gpal.entries[0x26] = 0x00C08000;
    gpal.entries[0x27] = 0x00E08000;
    gpal.entries[0x28] = 0x0000A000;
    gpal.entries[0x29] = 0x0020A000;
    gpal.entries[0x2A] = 0x0040A000;
    gpal.entries[0x2B] = 0x0060A000;
    gpal.entries[0x2C] = 0x0080A000;
    gpal.entries[0x2D] = 0x00A0A000;
    gpal.entries[0x2E] = 0x00C0A000;
    gpal.entries[0x2F] = 0x00E0A000;
    gpal.entries[0x30] = 0x0000C000;
    gpal.entries[0x31] = 0x0020C000;
    gpal.entries[0x32] = 0x0040C000;
    gpal.entries[0x33] = 0x0060C000;
    gpal.entries[0x34] = 0x0080C000;
    gpal.entries[0x35] = 0x00A0C000;
    gpal.entries[0x36] = 0x00C0C000;
    gpal.entries[0x37] = 0x00E0C000;
    gpal.entries[0x38] = 0x0000E000;
    gpal.entries[0x39] = 0x0020E000;
    gpal.entries[0x3A] = 0x0040E000;
    gpal.entries[0x3B] = 0x0060E000;
    gpal.entries[0x3C] = 0x0080E000;
    gpal.entries[0x3D] = 0x00A0E000;
    gpal.entries[0x3E] = 0x00C0E000;
    gpal.entries[0x3F] = 0x00E0E000;
    gpal.entries[0x40] = 0x00000040;
    gpal.entries[0x41] = 0x00200040;
    gpal.entries[0x42] = 0x00400040;
    gpal.entries[0x43] = 0x00600040;
    gpal.entries[0x44] = 0x00800040;
    gpal.entries[0x45] = 0x00A00040;
    gpal.entries[0x46] = 0x00C00040;
    gpal.entries[0x47] = 0x00E00040;
    gpal.entries[0x48] = 0x00002040;
    gpal.entries[0x49] = 0x00202040;
    gpal.entries[0x4A] = 0x00402040;
    gpal.entries[0x4B] = 0x00602040;
    gpal.entries[0x4C] = 0x00802040;
    gpal.entries[0x4D] = 0x00A02040;
    gpal.entries[0x4E] = 0x00C02040;
    gpal.entries[0x4F] = 0x00E02040;
    gpal.entries[0x50] = 0x00004040;
    gpal.entries[0x51] = 0x00204040;
    gpal.entries[0x52] = 0x00404040;
    gpal.entries[0x53] = 0x00604040;
    gpal.entries[0x54] = 0x00804040;
    gpal.entries[0x55] = 0x00A04040;
    gpal.entries[0x56] = 0x00C04040;
    gpal.entries[0x57] = 0x00E04040;
    gpal.entries[0x58] = 0x00006040;
    gpal.entries[0x59] = 0x00206040;
    gpal.entries[0x5A] = 0x00406040;
    gpal.entries[0x5B] = 0x00606040;
    gpal.entries[0x5C] = 0x00806040;
    gpal.entries[0x5D] = 0x00A06040;
    gpal.entries[0x5E] = 0x00C06040;
    gpal.entries[0x5F] = 0x00E06040;
    gpal.entries[0x60] = 0x00008040;
    gpal.entries[0x61] = 0x00208040;
    gpal.entries[0x62] = 0x00408040;
    gpal.entries[0x63] = 0x00608040;
    gpal.entries[0x64] = 0x00808040;
    gpal.entries[0x65] = 0x00A08040;
    gpal.entries[0x66] = 0x00C08040;
    gpal.entries[0x67] = 0x00E08040;
    gpal.entries[0x68] = 0x0000A040;
    gpal.entries[0x69] = 0x0020A040;
    gpal.entries[0x6A] = 0x0040A040;
    gpal.entries[0x6B] = 0x0060A040;
    gpal.entries[0x6C] = 0x0080A040;
    gpal.entries[0x6D] = 0x00A0A040;
    gpal.entries[0x6E] = 0x00C0A040;
    gpal.entries[0x6F] = 0x00E0A040;
    gpal.entries[0x70] = 0x0000C040;
    gpal.entries[0x71] = 0x0020C040;
    gpal.entries[0x72] = 0x0040C040;
    gpal.entries[0x73] = 0x0060C040;
    gpal.entries[0x74] = 0x0080C040;
    gpal.entries[0x75] = 0x00A0C040;
    gpal.entries[0x76] = 0x00C0C040;
    gpal.entries[0x77] = 0x00E0C040;
    gpal.entries[0x78] = 0x0000E040;
    gpal.entries[0x79] = 0x0020E040;
    gpal.entries[0x7A] = 0x0040E040;
    gpal.entries[0x7B] = 0x0060E040;
    gpal.entries[0x7C] = 0x0080E040;
    gpal.entries[0x7D] = 0x00A0E040;
    gpal.entries[0x7E] = 0x00C0E040;
    gpal.entries[0x7F] = 0x00E0E040;
    gpal.entries[0x80] = 0x00000080;
    gpal.entries[0x81] = 0x00200080;
    gpal.entries[0x82] = 0x00400080;
    gpal.entries[0x83] = 0x00600080;
    gpal.entries[0x84] = 0x00800080;
    gpal.entries[0x85] = 0x00A00080;
    gpal.entries[0x86] = 0x00C00080;
    gpal.entries[0x87] = 0x00E00080;
    gpal.entries[0x88] = 0x00002080;
    gpal.entries[0x89] = 0x00202080;
    gpal.entries[0x8A] = 0x00402080;
    gpal.entries[0x8B] = 0x00602080;
    gpal.entries[0x8C] = 0x00802080;
    gpal.entries[0x8D] = 0x00A02080;
    gpal.entries[0x8E] = 0x00C02080;
    gpal.entries[0x8F] = 0x00E02080;
    gpal.entries[0x90] = 0x00004080;
    gpal.entries[0x91] = 0x00204080;
    gpal.entries[0x92] = 0x00404080;
    gpal.entries[0x93] = 0x00604080;
    gpal.entries[0x94] = 0x00804080;
    gpal.entries[0x95] = 0x00A04080;
    gpal.entries[0x96] = 0x00C04080;
    gpal.entries[0x97] = 0x00E04080;
    gpal.entries[0x98] = 0x00006080;
    gpal.entries[0x99] = 0x00206080;
    gpal.entries[0x9A] = 0x00406080;
    gpal.entries[0x9B] = 0x00606080;
    gpal.entries[0x9C] = 0x00806080;
    gpal.entries[0x9D] = 0x00A06080;
    gpal.entries[0x9E] = 0x00C06080;
    gpal.entries[0x9F] = 0x00E06080;
    gpal.entries[0xA0] = 0x00008080;
    gpal.entries[0xA1] = 0x00208080;
    gpal.entries[0xA2] = 0x00408080;
    gpal.entries[0xA3] = 0x00608080;
    gpal.entries[0xA4] = 0x00808080;
    gpal.entries[0xA5] = 0x00A08080;
    gpal.entries[0xA6] = 0x00C08080;
    gpal.entries[0xA7] = 0x00E08080;
    gpal.entries[0xA8] = 0x0000A080;
    gpal.entries[0xA9] = 0x0020A080;
    gpal.entries[0xAA] = 0x0040A080;
    gpal.entries[0xAB] = 0x0060A080;
    gpal.entries[0xAC] = 0x0080A080;
    gpal.entries[0xAD] = 0x00A0A080;
    gpal.entries[0xAE] = 0x00C0A080;
    gpal.entries[0xAF] = 0x00E0A080;
    gpal.entries[0xB0] = 0x0000C080;
    gpal.entries[0xB1] = 0x0020C080;
    gpal.entries[0xB2] = 0x0040C080;
    gpal.entries[0xB3] = 0x0060C080;
    gpal.entries[0xB4] = 0x0080C080;
    gpal.entries[0xB5] = 0x00A0C080;
    gpal.entries[0xB6] = 0x00C0C080;
    gpal.entries[0xB7] = 0x00E0C080;
    gpal.entries[0xB8] = 0x0000E080;
    gpal.entries[0xB9] = 0x0020E080;
    gpal.entries[0xBA] = 0x0040E080;
    gpal.entries[0xBB] = 0x0060E080;
    gpal.entries[0xBC] = 0x0080E080;
    gpal.entries[0xBD] = 0x00A0E080;
    gpal.entries[0xBE] = 0x00C0E080;
    gpal.entries[0xBF] = 0x00E0E080;
    gpal.entries[0xC0] = 0x000000C0;
    gpal.entries[0xC1] = 0x002000C0;
    gpal.entries[0xC2] = 0x004000C0;
    gpal.entries[0xC3] = 0x006000C0;
    gpal.entries[0xC4] = 0x008000C0;
    gpal.entries[0xC5] = 0x00A000C0;
    gpal.entries[0xC6] = 0x00C000C0;
    gpal.entries[0xC7] = 0x00E000C0;
    gpal.entries[0xC8] = 0x000020C0;
    gpal.entries[0xC9] = 0x002020C0;
    gpal.entries[0xCA] = 0x004020C0;
    gpal.entries[0xCB] = 0x006020C0;
    gpal.entries[0xCC] = 0x008020C0;
    gpal.entries[0xCD] = 0x00A020C0;
    gpal.entries[0xCE] = 0x00C020C0;
    gpal.entries[0xCF] = 0x00E020C0;
    gpal.entries[0xD0] = 0x000040C0;
    gpal.entries[0xD1] = 0x002040C0;
    gpal.entries[0xD2] = 0x004040C0;
    gpal.entries[0xD3] = 0x006040C0;
    gpal.entries[0xD4] = 0x008040C0;
    gpal.entries[0xD5] = 0x00A040C0;
    gpal.entries[0xD6] = 0x00C040C0;
    gpal.entries[0xD7] = 0x00E040C0;
    gpal.entries[0xD8] = 0x000060C0;
    gpal.entries[0xD9] = 0x002060C0;
    gpal.entries[0xDA] = 0x004060C0;
    gpal.entries[0xDB] = 0x006060C0;
    gpal.entries[0xDC] = 0x008060C0;
    gpal.entries[0xDD] = 0x00A060C0;
    gpal.entries[0xDE] = 0x00C060C0;
    gpal.entries[0xDF] = 0x00E060C0;
    gpal.entries[0xE0] = 0x000080C0;
    gpal.entries[0xE1] = 0x002080C0;
    gpal.entries[0xE2] = 0x004080C0;
    gpal.entries[0xE3] = 0x006080C0;
    gpal.entries[0xE4] = 0x008080C0;
    gpal.entries[0xE5] = 0x00A080C0;
    gpal.entries[0xE6] = 0x00C080C0;
    gpal.entries[0xE7] = 0x00E080C0;
    gpal.entries[0xE8] = 0x0000A0C0;
    gpal.entries[0xE9] = 0x0020A0C0;
    gpal.entries[0xEA] = 0x0040A0C0;
    gpal.entries[0xEB] = 0x0060A0C0;
    gpal.entries[0xEC] = 0x0080A0C0;
    gpal.entries[0xED] = 0x00A0A0C0;
    gpal.entries[0xEE] = 0x00C0A0C0;
    gpal.entries[0xEF] = 0x00E0A0C0;
    gpal.entries[0xF0] = 0x0000C0C0;
    gpal.entries[0xF1] = 0x0020C0C0;
    gpal.entries[0xF2] = 0x0040C0C0;
    gpal.entries[0xF3] = 0x0060C0C0;
    gpal.entries[0xF4] = 0x0080C0C0;
    gpal.entries[0xF5] = 0x00A0C0C0;
    gpal.entries[0xF6] = 0x00FFFBF0;
    gpal.entries[0xF7] = 0x00A0A0A4;
    gpal.entries[0xF8] = 0x00808080;
    gpal.entries[0xF9] = 0x00FF0000;
    gpal.entries[0xFA] = 0x0000FF00;
    gpal.entries[0xFB] = 0x00FFFF00;
    gpal.entries[0xFC] = 0x000000FF;
    gpal.entries[0xFD] = 0x00FF00FF;
    gpal.entries[0xFE] = 0x0000FFFF;
    gpal.entries[0xFF] = 0x00FFFFFF;

#else  /* _LG_8_BIT_SYSTEM_PALETTE_ */
    gpal.num          = 16;

    gpal.entries[0x00] = 0x00000000;
    gpal.entries[0x01] = 0x00800000;
    gpal.entries[0x02] = 0x00008000;
    gpal.entries[0x03] = 0x00808000;
    gpal.entries[0x04] = 0x00000080;
    gpal.entries[0x05] = 0x00800080;
    gpal.entries[0x06] = 0x00008080;
    gpal.entries[0x07] = 0x00808080;
    gpal.entries[0x08] = 0x00C0C0C0;
    gpal.entries[0x09] = 0x00FF0000;
    gpal.entries[0x0A] = 0x0000FF00;
    gpal.entries[0x0B] = 0x00FFFF00;
    gpal.entries[0x0C] = 0x000000FF;
    gpal.entries[0x0D] = 0x00FF00FF;
    gpal.entries[0x0E] = 0x0000FFFF;
    gpal.entries[0x0F] = 0x00FFFFFF;
#endif  /* _LG_8_BIT_SYSTEM_PALETTE_ */

    return  1;
}
#endif  /* _LG_RESTORE_SYSTEM_PALETTE_ */

#ifndef  _LG_ALONE_VERSION_
#ifdef  _LG_RESTORE_SYSTEM_PALETTE_
int  palette_restore_system(void)
{
    int  ret = 0;

    gui_lock( );
    ret = in_palette_restore_system( );
    gui_unlock( );

    return  ret;
}
#endif  /* _LG_RESTORE_SYSTEM_PALETTE_ */
#endif  /* _LG_ALONE_VERSION_ */

#endif  /* _LG_PALETTE_ROUTINE_ */
