/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */
/* $Id: C2ClientTask.h 781 2009-09-01 14:23:50Z adeguet1 $ */

#ifndef _C2ClientTask_h
#define _C2ClientTask_h

#include <cisstMultiTask.h>
#include "C2ClientUI.h"

class C2ClientTask: public mtsTaskPeriodic {
    // set log level to 5
    CMN_DECLARE_SERVICES(CMN_NO_DYNAMIC_CREATION, CMN_LOG_LOD_RUN_ERROR);

protected:
    mtsFunctionVoid VoidServer;
    mtsFunctionWrite WriteServer;
    mtsFunctionRead ReadServer;
    mtsFunctionQualifiedRead QualifiedReadServer;

    void EventWriteHandler(const mtsDouble & value);
    void EventVoidHandler(void);

    // user interface generated by FTLK/fluid
    C2ClientUI UI;

public:
    // see sineTask.h documentation
    C2ClientTask(const std::string & taskName, double period);
    ~C2ClientTask() {};
    void Configure(const std::string & CMN_UNUSED(filename) = "");
    void Startup(void);
    void Run(void);
    void Cleanup(void) {};
    bool UIOpened(void) const {
        return UI.Opened;
    }
};

CMN_DECLARE_SERVICES_INSTANTIATION(C2ClientTask);

#endif // _C2ClientTask_h

/*
  Author(s):  Anton Deguet, Min Yang Jung
  Created on: 2009-08-10

  (C) Copyright 2009-2010 Johns Hopkins University (JHU), All Rights
  Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---

*/
