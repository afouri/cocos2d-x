#ifndef __CCDEVICE_H__
#define __CCDEVICE_H__

#include "CCPlatformMacros.h"

NS_CC_BEGIN

class CC_DLL CCDevice
{
private:
    CCDevice();
public:
    /**
     *  Gets the DPI of device
     *  @return The DPI of device.
     */
    // 获取dpi:Dot Per Inch 分辨率
    static int getDPI();
};


NS_CC_END

#endif /* __CCDEVICE_H__ */
