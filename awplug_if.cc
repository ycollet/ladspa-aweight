/*
    Copyright (C) 2005 Fons Adriaensen

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

//-----------------------------------------------------------------------------------
// Common definitions


#include "awplug.h"

#define NMODS 1
#define VERSION "0.0.1"


static const char* maker = "Fons Adriaensen <fons.adriaensen@skynet.be>";
static const char* copyr = "(C) 2005 Fons Adriaensen, GNU General Public License Version 2 applies";


static void pconnect (LADSPA_Handle H, unsigned long port, LADSPA_Data *data) {
    ((LadspaPlugin *)H)->setport (port, data);
}

static void activate (LADSPA_Handle H) {
    ((LadspaPlugin *)H)->active (true);
}

static void runplugin (LADSPA_Handle H, unsigned long k) {
    ((LadspaPlugin *)H)->runproc (k, false);
}

//static void runadding (LADSPA_Handle H, unsigned long k)
//{
//  ((LadspaPlugin *)H)->runproc (k, true);
//}

//static void setadding (LADSPA_Handle H, LADSPA_Data gain)
//{
//  ((LadspaPlugin *)H)->setgain (gain);
//}

static void deactivate (LADSPA_Handle H) {
    ((LadspaPlugin *)H)->active (false);
}

static void cleanup (LADSPA_Handle H) {
    delete (LadspaPlugin *) H;
}


//-----------------------------------------------------------------------------------
// Plugin definitions


static const char* name1 = "A-weighting filter";
static const char* label1  = "AWfilt";

static LADSPA_Handle instant1 (const struct _LADSPA_Descriptor *desc, unsigned long rate) {
    return new AWplug (rate);
}

static const char * const pname1  [AWplug::NPORT] = {
    "Input",
    "Output"
};

static const LADSPA_PortDescriptor pdesc1 [AWplug::NPORT] = {
    LADSPA_PORT_INPUT  | LADSPA_PORT_AUDIO,
    LADSPA_PORT_OUTPUT | LADSPA_PORT_AUDIO
};

static const LADSPA_PortRangeHint phint1 [AWplug::NPORT] = {
    { 0, 0, 0 },
    { 0, 0, 0 }
};

static const LADSPA_Descriptor moddescr [NMODS] = {
    {
        1971,
        label1,
        LADSPA_PROPERTY_REALTIME | LADSPA_PROPERTY_HARD_RT_CAPABLE,
        name1,
        maker,
        copyr,
        AWplug::NPORT,
        pdesc1,
        pname1,
        phint1,
        0,
        instant1,
        pconnect,
        activate,
        runplugin,
        0,
        0,
        deactivate,
        cleanup
    }
};

extern "C" const LADSPA_Descriptor *ladspa_descriptor (unsigned long i) {
    if (i >= NMODS) return 0;
    return moddescr + i;
}

//-----------------------------------------------------------------------------------
