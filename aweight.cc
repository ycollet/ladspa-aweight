/*
    Copyright (C) 2005 Fons Adriaensen <fons.adriaensen@skynet.be>

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


#include <math.h>
#include "aweight.h"


#define AW_F1 20.5990
#define AW_F2 107.652
#define AW_F3 737.862
#define AW_F4 12194.2


int Aweight::init (int fsamp) {
    double f;

    reset ();
    _w1 = _w2 = _w3 = _w4 = _g = 0;

    switch (fsamp) {
    case 44100:
        _w4 = 0.846;
        break;
    case 48000:
        _w4 = 0.817;
        break;
    case 88200:
        _w4 = 0.587;
        break;
    case 96000:
        _w4 = 0.555;
        break;
    default:
        return 1;
    }

    _g = 1.2502f;

    f = AW_F1 / fsamp;
    _w1 = 2 * M_PI * f;
    _g *= 2 / (2 - _w1);
    _g *= 2 / (2 - _w1); // twice !!
    _w1 *= 1 - 3 * f;

    f = AW_F2 / fsamp;
    _w2 = 2 * M_PI * f;
    _g *= 2 / (2 - _w2);
    _w2 *= 1 - 3 * f;

    f = AW_F3 / fsamp;
    _w3 = 2 * M_PI * f;
    _g *= 2 / (2 - _w3);
    _w3 *= 1 - 3 * f;

    return 0;
}


void Aweight::reset (void) {
    // reset filter state
    _z1a = _z1b = _z2 = _z3 = _z4a = _z4b = 0;
}


void Aweight::process (size_t n, const float *in, float *out) {
    float x, e;

    e = ldexpf (1.0f, -40);

    while (n--) {
        x = *in++;

        // highpass sections
        _z1a += _w1 * (x - _z1a + e);
        x -= _z1a;
        _z1b += _w1 * (x - _z1b + e);
        x -= _z1b;
        _z2 += _w2 * (x - _z2 + e);
        x -= _z2;
        _z3 += _w3 * (x - _z3 + e);
        x -= _z3;

        // lowpass sections
        _z4a += _w4 * (x - _z4a);
        x  = 0.25 * _z4b;
        _z4b += _w4 * (_z4a - _z4b);
        x += 0.75 * _z4b;

        *out++ = _g * x;
    }
}
