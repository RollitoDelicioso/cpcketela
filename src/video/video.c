// Required Include files
#include <cpctelera.h>
#include "constants.h"

// Global variable pointing to the present memory used as back buffer
// (Changes on every call to switchBuffers).
u8* video_buffer;

////////////////////////////////////////////////////////////////////////////////////
// GET BACK BUFFER POINTER
// Returns a pointer to the start of the current memory used as hardware 
// back buffer. There it is safe to draw anything, as it will not be displayed 
// until a call to switchBuffers is performed.
//
u8* video_getBackBufferPtr(){

    return video_buffer;
}

////////////////////////////////////////////////////////////////////////////////////
// SWITCH VIDEO BUFFERS
// Sets the contents of current hardware backbuffer to be displayed as main 
// screen immediately (after next VSYNC), also shadowing current displayed screen,
// that will be considered next hardware backbuffer.
//
void video_switchBuffers(){

    // Check were the current backbuffer is pointing and switch buffers
    // accordingly (if video_buffer points to our default HW_BACKBUFFER,
    // make it point to default VMEM_START, else make it point to HW_BACKBUFFER)
    // and also change CRTC Register R13 (current video memory page) accordingly
    if (video_buffer == HW_BACKBUFFER) {
        // Current Backbuffer is at 0x8000. Make that part of memory
        // displayed changing CRTC Register 13, then point to VMEM_START.
        cpct_setVideoMemoryPage(cpct_page80);
        video_buffer = CPCT_VMEM_START;
    }
    else {
        // Current Backbuffer is at 0xC000. Make that part of memory
        // displayed changing CRTC Register 13, then point to HW_BACKBUFFER.
        cpct_setVideoMemoryPage(cpct_pageC0);
        video_buffer = HW_BACKBUFFER;
    }
}

////////////////////////////////////////////////////////////////////////////////////
// INITIALIZE VIDEO BUFFERS
// Ensures initial conditions for both video buffers to be used.
//
void video_initBuffers(){

    // Hardware backbuffer has to be cleared as it usually has code in it that
    // would be displayed as coloured pixels if not set to 0.
    cpct_memset(HW_BACKBUFFER, 0, 0x4000);  // 16K HW_BACKBUFFER set to 0
    // First call to video Switch Buffers will initialize video_buffer global
    // variable containing a pointer to the current hardware backbuffer.
    // This call will also set CRTC registers that will left video_buffer 
    // undisplayed and the other buffer displayed.
    video_switchBuffers();
}