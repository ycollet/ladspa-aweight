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


#ifndef __AWPLUG_H
#define __AWPLUG_H


#include "ladspaplugin.h"
#include "aweight.h"


class AWplug : public LadspaPlugin
{
public:

    enum { INP, OUT, NPORT };

    AWplug (unsigned long fsam) : LadspaPlugin (fsam) { _filt.init (fsam); }
    virtual void setport (unsigned long port, LADSPA_Data *data);  
    virtual void active  (bool act);  
    virtual void runproc (unsigned long len, bool add);
    virtual ~AWplug (void) {}  

private:

    float   *_port [NPORT];
    Aweight  _filt;    
};


#endif
