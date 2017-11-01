/**
MIT License

Copyright (c) 2017 Boodskap Inc

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. 
 */ 
#ifdef USE_UDP

#include <WiFiUdp.h>
#include <BoodskapTransceiver.h>

#ifndef _BSKP_UDP_TRANSCEIVER_
#define _BSKP_UDP_TRANSCEIVER_

#define UDP_LOCAL_PORT 0 //Local UDP Port
#define UDP_HOST "udp.boodskap.io"
#define UDP_PORT 5555
#define UDP_HEARTBEAT_INTERVAL 15 //seconds

#endif //_BSKP_UDP_TRANSCEIVER_

#endif //USE_UDP
