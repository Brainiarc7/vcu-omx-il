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

#pragma once

extern "C"
{
#include <lib_common_enc/EncChanParam.h>
#include <lib_common_enc/Settings.h>
}

#include "omx_module_enc_enums.h"

RateControlType ConvertToModuleRateControl(AL_ERateCtrlMode const& mode);
AspectRatioType ConvertToModuleAspectRatio(AL_EAspectRatio const& aspectRatio);
GopControlType ConvertToModuleGopControl(AL_EGopCtrlMode const& mode);
GdrType ConvertToModuleGdr(AL_EGdrMode const& gdr);
RateControlOptionType ConvertToModuleRateControlOption(AL_ERateCtrlOption const& option);
QPControlType ConvertToModuleQPControl(AL_EQpCtrlMode const& mode);
ScalingListType ConvertToModuleScalingList(AL_EScalingList const& scalingList);

AL_ERateCtrlMode ConvertToSoftRateControl(RateControlType const& mode);
AL_EAspectRatio ConvertToSoftAspectRatio(AspectRatioType const& aspectRatio);
AL_EGopCtrlMode ConvertToSoftGopControl(GopControlType const& mode);
AL_EScalingList ConvertToSoftScalingList(ScalingListType const& scalingList);
AL_EGdrMode ConvertToSoftGdr(GdrType const& gdr);
AL_ERateCtrlOption ConvertToSoftRateControlOption(RateControlOptionType const& option);
AL_EQpCtrlMode ConvertToSoftQPControl(QPControlType const& mode);

