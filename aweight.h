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


#ifndef __AWEIGHT_H
#define __AWEIGHT_H


#include <stdlib.h>


class Aweight {
  public:

    Aweight (void) {}
    ~Aweight (void) {}

    int  init (int fsamp);
    void reset (void);
    void process (size_t n, const float *in, float *out);

  private:

    float _w1, _w2, _w3, _w4, _g;             // filter coefficients and gain
    float _z1a, _z1b, _z2, _z3, _z4a, _z4b;   // filter state
};


#endif


