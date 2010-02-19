/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */

/*
  $Id: svlStereoImageJoiner.cpp 545 2009-07-14 08:38:33Z adeguet1 $
  
  Author(s):  Balazs Vagvolgyi
  Created on: 2007 

  (C) Copyright 2006-2007 Johns Hopkins University (JHU), All Rights
  Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---

*/

#include <cisstStereoVision/svlFilterStereoImageJoiner.h>
#include <string.h>

using namespace std;

/******************************************/
/*** svlFilterStereoImageJoiner class *****/
/******************************************/

CMN_IMPLEMENT_SERVICES(svlFilterStereoImageJoiner)

svlFilterStereoImageJoiner::svlFilterStereoImageJoiner() :
    svlFilterBase(),
    cmnGenericObject(),
    ImageLayout(SideBySide)
{
    AddSupportedType(svlTypeImageRGBStereo, svlTypeImageRGB);
    AddSupportedType(svlTypeImageMono8Stereo, svlTypeImageMono8);
    AddSupportedType(svlTypeImageMono16Stereo, svlTypeImageMono16);
}

svlFilterStereoImageJoiner::~svlFilterStereoImageJoiner()
{
    Release();
}

int svlFilterStereoImageJoiner::Initialize(svlSample* inputdata)
{
    svlSampleImageBase* input = dynamic_cast<svlSampleImageBase*>(inputdata);
    unsigned int width = input->GetWidth(SVL_LEFT);
    unsigned int height = input->GetHeight(SVL_LEFT);

    if (input->GetWidth(SVL_RIGHT)  != width ||
        input->GetHeight(SVL_RIGHT) != height) return SVL_FAIL;

    Release();

    switch (ImageLayout) {
        case VerticalInterlaced:
        case VerticalInterlacedRL:
            height += input->GetHeight(SVL_RIGHT);
        break;

        case SideBySide:
        case SideBySideRL:
            width += input->GetWidth(SVL_RIGHT);
        break;

        default:
            return SVL_FAIL;
    }

    svlSampleImageBase* output;
    if (GetInputType() == svlTypeImageRGBStereo) output = new svlSampleImageRGB;
    else if (GetInputType() == svlTypeImageMono8Stereo) output = new svlSampleImageMono8;
    else if (GetInputType() == svlTypeImageMono16Stereo) output = new svlSampleImageMono16;
    else return SVL_FAIL;
    output->SetSize(width, height);
    OutputData = output;

    return SVL_OK;
}

int svlFilterStereoImageJoiner::ProcessFrame(svlProcInfo* procInfo, svlSample* inputdata)
{
    ///////////////////////////////////////////
    // Check if the input sample has changed //
    if (!IsNewSample(inputdata))
        return SVL_ALREADY_PROCESSED;
    ///////////////////////////////////////////

    _OnSingleThread(procInfo)
    {
        svlSampleImageBase* id = dynamic_cast<svlSampleImageBase*>(inputdata);
        svlSampleImageBase* od = dynamic_cast<svlSampleImageBase*>(OutputData);
        unsigned int stride = id->GetWidth(SVL_LEFT) * id->GetBPP();
        unsigned int height = id->GetHeight();
        unsigned char *input1 = id->GetUCharPointer(SVL_LEFT);
        unsigned char *input2 = id->GetUCharPointer(SVL_RIGHT);
        unsigned char *output = od->GetUCharPointer();

        // copy data
        switch (ImageLayout) {
            case VerticalInterlaced:
            case SideBySide:
                for (unsigned int j = 0; j < height; j ++) {
                    memcpy(output, input1, stride);
                    input1 += stride;
                    output += stride;
                    memcpy(output, input2, stride);
                    input2 += stride;
                    output += stride;
                }
            break;

            case VerticalInterlacedRL:
            case SideBySideRL:
                for (unsigned int j = 0; j < height; j ++) {
                    memcpy(output, input2, stride);
                    input2 += stride;
                    output += stride;
                    memcpy(output, input1, stride);
                    input1 += stride;
                    output += stride;
                }
            break;

            default:
                return SVL_FAIL;
        }
    }

    return SVL_OK;
}

int svlFilterStereoImageJoiner::Release()
{
    if (OutputData) {
        delete OutputData;
        OutputData = 0;
    }
    return SVL_OK;
}

int svlFilterStereoImageJoiner::SetLayout(Layout layout)
{
    if (IsInitialized()) return SVL_FAIL;
    ImageLayout = layout;
    return SVL_OK;
}

