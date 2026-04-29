#  Copyright (C) 2004 Fons Adriaensen <fons.adriaensen@skynet.be>
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.


# Compilation flags
#
DEBUG_FLAGS = -g
OPTIM_FLAGS = -O3
SHOBJ_FLAGS = -fpic -D_REENTRANT
CPPFLAGS = $(OPTIM_FLAGS) -Wall
LDFLAGS +=
LDLIBS +=


# Targets
#

AWJACK_0 = awjack.o aweight.o

awjack.so:	$(AWJACK_0)
	g++ -o $@ -shared $(AWJACK_0) -ljack -lm

awjack.o:	awjack.cc 
	g++ -c $(CPPFLAGS) $(SHOBJ_FLAGS) awjack.cc



AWPLUG_O = awplug.o awplug_if.o aweight.o

awplug.so:	$(AWPLUG_O)
	g++ -o $@ -shared $(AWPLUG_O) -lm 

awplug.o:	ladspaplugin.h awplug.h awplug.cc
	g++ -c $(CPPFLAGS) $(SHOBJ_FLAGS) awplug.cc

awplug_if.o:	ladspaplugin.h awplug.h awplug_if.cc
	g++ -c $(CPPFLAGS) $(SHOBJ_FLAGS) awplug_if.cc



install:	awjack.so awplug.so	
	/bin/cp  awjack.so /usr/lib/jack
	/bin/cp  awplug.so /usr/lib/ladspa

clean:
	/bin/rm -f *.o *.u *.so *~



DIR := $(shell basename `pwd`)

archive:	clean
	cd ..; /bin/rm -f $(DIR).tar.bz2; tar cvf $(DIR).tar $(DIR); bzip2 $(DIR).tar

