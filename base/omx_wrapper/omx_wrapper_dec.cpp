/******************************************************************************
*
* Copyright (C) 2017 Allegro DVT2.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX OR ALLEGRO DVT2 BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of  Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
*
* Except as contained in this notice, the name of Allegro DVT2 shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Allegro DVT2.
*
******************************************************************************/

#include "base/omx_module/omx_module_dec.h"
#include "base/omx_codec/omx_codec_dec.h"
#include "base/omx_codec/omx_expertise_dec_hevc.h"
#include "base/omx_mediatype/omx_mediatype_dec_hevc.h"



#include "base/omx_module/omx_device_dec_hardware_mcu.h"

#include <string.h>
#include <memory>
#include <functional>
#include <stdexcept>

using namespace std;

extern "C" {
#include "lib_fpga/DmaAlloc.h"
}

static AL_TAllocator* createDmaAlloc(string deviceName)
{
  auto alloc = DmaAlloc_Create(deviceName.c_str());

  if(alloc == nullptr)
    throw runtime_error(string("Couldnt allocate dma allocator (tried using ") + deviceName + string(")"));
  return alloc;
}


#include "base/omx_codec/omx_expertise_dec_avc.h"
#include "base/omx_mediatype/omx_mediatype_dec_avc.h"


static DecCodec* GenerateAvcCodecHardware(OMX_HANDLETYPE hComponent, OMX_STRING cComponentName, OMX_STRING cRole)
{
  unique_ptr<DecMediatypeAVC> mediatype(new DecMediatypeAVC);
  unique_ptr<DecDeviceHardwareMcu> device(new DecDeviceHardwareMcu);
  deleted_unique_ptr<AL_TAllocator> allocator(createDmaAlloc("/dev/allegroDecodeIP"), [](AL_TAllocator* allocator) {
    AL_Allocator_Destroy(allocator);
  });
  unique_ptr<DecModule> module(new DecModule(move(mediatype), move(device), move(allocator)));
  unique_ptr<DecExpertiseAVC> expertise(new DecExpertiseAVC);
  return new DecCodec(hComponent, move(module), cComponentName, cRole, move(expertise));
}


static DecCodec* GenerateHevcCodecHardware(OMX_HANDLETYPE hComponent, OMX_STRING cComponentName, OMX_STRING cRole)
{
  unique_ptr<DecMediatypeHEVC> mediatype(new DecMediatypeHEVC);
  unique_ptr<DecDeviceHardwareMcu> device(new DecDeviceHardwareMcu);
  deleted_unique_ptr<AL_TAllocator> allocator(createDmaAlloc("/dev/allegroDecodeIP"), [](AL_TAllocator* allocator) {
    AL_Allocator_Destroy(allocator);
  });
  unique_ptr<DecModule> module(new DecModule(move(mediatype), move(device), move(allocator)));
  unique_ptr<DecExpertiseHEVC> expertise(new DecExpertiseHEVC);
  return new DecCodec(hComponent, move(module), cComponentName, cRole, move(expertise));
}


static OMX_PTR GenerateDefaultCodec(OMX_IN OMX_HANDLETYPE hComponent, OMX_IN OMX_STRING cComponentName, OMX_IN OMX_STRING cRole)
{
  OMX_PTR dec = nullptr;

  if(!strncmp(cComponentName, "OMX.allegro.h265.hardware.decoder", strlen(cComponentName)))
    dec = GenerateHevcCodecHardware(hComponent, cComponentName, cRole);

  if(!strncmp(cComponentName, "OMX.allegro.h265.decoder", strlen(cComponentName)))
    dec = GenerateHevcCodecHardware(hComponent, cComponentName, cRole);

  if(!strncmp(cComponentName, "OMX.allegro.h264.hardware.decoder", strlen(cComponentName)))
    dec = GenerateAvcCodecHardware(hComponent, cComponentName, cRole);

  if(!strncmp(cComponentName, "OMX.allegro.h264.decoder", strlen(cComponentName)))
    dec = GenerateAvcCodecHardware(hComponent, cComponentName, cRole);
  return dec;
}

extern "C"
{
OMX_PTR CreateComponentPrivate(OMX_IN OMX_HANDLETYPE hComponent, OMX_IN OMX_STRING cComponentName, OMX_IN OMX_STRING cRole)
{
  return GenerateDefaultCodec(hComponent, cComponentName, cRole);
}

void DestroyComponentPrivate(OMX_IN OMX_PTR pComponentPrivate)
{
  delete static_cast<DecCodec*>(pComponentPrivate);
}
}

