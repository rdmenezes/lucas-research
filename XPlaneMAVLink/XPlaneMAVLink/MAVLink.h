#ifndef MAVLink_h
#define MAVLink_h

#include "mavlink_types.h"
#include "common\common.h"
#include "DataLink.h"

class MAVLink {
public:
	MAVLink(DataLink *link);
private:
	DataLink *link;

}

#endif