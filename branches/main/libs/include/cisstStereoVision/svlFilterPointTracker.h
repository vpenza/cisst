/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */

/*
  $Id: svlPointTracker.h 75 2009-02-24 16:47:20Z adeguet1 $
  
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

#ifndef _svlFilterPointTracker_h
#define _svlFilterPointTracker_h

#include <cisstStereoVision/svlStreamManager.h>

// Always include last!
#include <cisstStereoVision/svlExport.h>


class svlPointTrackerAlgoBase;

class CISST_EXPORT svlFilterPointTracker : public svlFilterBase, public cmnGenericObject
{
    CMN_DECLARE_SERVICES(CMN_DYNAMIC_CREATION, CMN_LOG_LOD_RUN_ERROR);

public:
    typedef struct _TargetType {
        int x;
        int y;
    } TargetType;

    svlFilterPointTracker();
    virtual ~svlFilterPointTracker();

    void SetMovingAverageSmoothing(double weight);
    void SetFrameSkip(unsigned int skipcount) { FramesToSkip = static_cast<int>(skipcount); }
    int SetTrackerAlgo(svlPointTrackerAlgoBase* tracker, unsigned int targetcount, unsigned int videoch = SVL_LEFT);
    int SetWorkArea(unsigned int left, unsigned int top, unsigned int right, unsigned int bottom, unsigned int videoch = SVL_LEFT);
    int SetTarget(unsigned int targetid, int x, int y, unsigned int videoch = SVL_LEFT);
    void SetIterations(unsigned int count);
    void ResetTargets() { ResetFlag[0] = 1; ResetFlag[1] = 1; }

protected:
    virtual int Initialize(svlSample* inputdata);
    virtual int ProcessFrame(svlProcInfo* procInfo, svlSample* inputdata);
    virtual int Release();

private:
    void ResetToForcedPositions(unsigned int videoch);
    int StoreResults(unsigned int videoch = SVL_LEFT);
    int AllocateTargets(unsigned int targetcount, unsigned int videoch);
    void ReleaseTargets(unsigned int videoch);

    svlPointTrackerAlgoBase* Tracker[2];
    unsigned int WALeft[2];
    unsigned int WARight[2];
    unsigned int WATop[2];
    unsigned int WABottom[2];

    int ResetFlag[2];
    TargetType* Target[2];
    TargetType* ForcedTarget[2];

    int FrameCount[2];
    int FramesToSkip;
    double MovingAverageWeight;
    unsigned int Iterations;
};

class svlPointTrackerAlgoBase
{
friend class svlFilterPointTracker;

public:
	svlPointTrackerAlgoBase();
	virtual ~svlPointTrackerAlgoBase();

protected:
    bool Initialized;
    unsigned int Width;
    unsigned int Height;
    unsigned int Left;
    unsigned int Top;
    unsigned int Right;
    unsigned int Bottom;
    unsigned int TargetCount;
    svlFilterPointTracker::TargetType *TargetParams;

    unsigned int GetTargetCount() { return TargetCount; }
    void SetImageSize(unsigned int width, unsigned int height);
    void SetWorkArea(unsigned int left, unsigned int top, unsigned int right, unsigned int bottom);

    // overridables
    virtual int SetTargetCount(unsigned int targetcount);
    virtual int SetTarget(unsigned int targetid, svlFilterPointTracker::TargetType* target);
    virtual int Initialize();
    virtual void Release();
    virtual int PreProcessImage(unsigned char* image);
	virtual int Track(unsigned char* image);
    virtual int GetTarget(unsigned int targetid, svlFilterPointTracker::TargetType* target);

private:
    void ReallocateTargetParams(unsigned int targetcount);
};

CMN_DECLARE_SERVICES_INSTANTIATION_EXPORT(svlFilterPointTracker)

#endif // _svlFilterPointTracker_h

