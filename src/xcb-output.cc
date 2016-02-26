#include "xcb-output.hh"

XcbOutput::XcbOutput(int width, int height)
{
    con_ = xcb_connect(nullptr, nullptr);
    xcb_create_window(con_, 24, 0, 0, 0, 0, width, height, 1, 0, 0, 0, nullptr);
}

XcbOutput::~XcbOutput()
{
    xcb_disconnect(con_);
}
