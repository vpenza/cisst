/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */

/*
Author(s):	Rajesh Kumar, Anton Deguet
Created on:   2008-04-10

(C) Copyright 2008 Johns Hopkins University (JHU), All Rights
Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---
*/

#include <cisstParameterTypes/prmPositionJointGet.h>


CMN_IMPLEMENT_SERVICES(prmPositionJointGet);

prmPositionJointGet::~prmPositionJointGet()
{
}

void prmPositionJointGet::SetSize(size_type size)
{
    PositionMember.SetSize(size);
}


void prmPositionJointGet::ToStream(std::ostream & outputStream) const
{
    BaseType::ToStream(outputStream);
    outputStream << "\nPosition: " << this->PositionMember;
}

void prmPositionJointGet::ToStreamRaw(std::ostream & outputStream, const char delimiter,
                                      bool headerOnly, const std::string & headerPrefix) const {
    BaseType::ToStreamRaw(outputStream, delimiter, headerOnly, headerPrefix);
    outputStream << delimiter;
    this->PositionMember.ToStreamRaw(outputStream, delimiter, headerOnly, headerPrefix);
}

void prmPositionJointGet::SerializeRaw(std::ostream & outputStream) const 
{
    BaseType::SerializeRaw(outputStream);
    this->PositionMember.SerializeRaw(outputStream);
}

void prmPositionJointGet::DeSerializeRaw(std::istream & inputStream) 
{
    BaseType::DeSerializeRaw(inputStream);
    this->PositionMember.DeSerializeRaw(inputStream);
}

unsigned int prmPositionJointGet::GetNumberOfScalar(const bool CMN_UNUSED(visualizable)) const 
{
    return PositionMember.size();
}

double prmPositionJointGet::GetScalarAsDouble(const size_t index) const 
{
    if (index >= GetNumberOfScalar()) {
        return 0.0;
    }

    return static_cast<double>(this->PositionMember.at(index));
}

std::string prmPositionJointGet::GetScalarName(const size_t index) const 
{
    if (index >= GetNumberOfScalar()) {
        return "N/A";
    }

    std::stringstream ss;
    ss << "JointPosition";
    ss << index;
    
    return ss.str();
}
