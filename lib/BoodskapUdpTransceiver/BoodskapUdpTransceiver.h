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
