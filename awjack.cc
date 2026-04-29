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


#include <stdio.h>
#include <string.h>
#include <jack/jack.h>
#include "aweight.h"


class AWtest
{
public:

    AWtest (void);
    int process (jack_nframes_t nframes);

    jack_port_t *_iport;
    jack_port_t *_oport;

    Aweight      _awfilt;

private:

};


AWtest::AWtest (void)
{
}


int AWtest::process (jack_nframes_t nframes)
{
    jack_default_audio_sample_t *ip = (jack_default_audio_sample_t *) jack_port_get_buffer (_iport, nframes);
    jack_default_audio_sample_t *op = (jack_default_audio_sample_t *) jack_port_get_buffer (_oport, nframes);

    _awfilt.process (nframes, ip, op);

    return 0;  
}


// --------------------------------------------------------------------------------------------------------------


static int process (jack_nframes_t nframes, void *arg)
{
    return ((AWtest *) arg)->process (nframes); 
}


extern "C" int jack_initialize (jack_client_t *client, const char *data)
{
    AWtest *A = new AWtest;

    jack_set_process_callback (client, process, A);

    A->_iport = jack_port_register (client, "in", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    A->_oport = jack_port_register (client, "out", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

    jack_activate (client);
    A->_awfilt.init (jack_get_sample_rate (client));

    return 0;
}


extern "C" void jack_finish (void *arg)
{
   delete (AWtest *) arg;    
}


// --------------------------------------------------------------------------------------------------------------


