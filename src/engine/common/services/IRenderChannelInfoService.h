#ifndef IRENDERCHANNELINFO_SERVICE_H
#define IRENDERCHANNELINFO_SERVICE_H

#include <string>

class IRenderChannelInfoService {

public:

	virtual ~IRenderChannelInfoService() { };

public:

	virtual std::string getActiveRenderChannel() const = 0;

};

#endif
