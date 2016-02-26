#pragma once

#include <xcb/xcb.h>

class XcbOutput
{
public:
    XcbOutput(int width, int height);
    ~XcbOutput();

private:
    xcb_connection_t *con_;
};
