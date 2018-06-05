#ifndef _VIDEO_H_
#define _VIDEO_H_

#include "constants.h"

u8* video_getBackBufferPtr();
void video_initBuffers();
void video_switchBuffers();
void video_resetScreenPtr();
bool video_isInsideViewport(u8 screen_x, u8 screen_y, u8 entity_x, u8 entity_y, u8 entity_width, u8 entity_height);
u16 pixel_to_tile(u8 x, u8 y);

#endif