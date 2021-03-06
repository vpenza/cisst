/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */

/*
  
  Author(s):  Anton Deguet
  Created on: 2005-11-16
  
  (C) Copyright 2005-2007 Johns Hopkins University (JHU), All Rights
  Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---
*/


#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include <cisstVector/vctRodriguezRotation3.h>
#include <cisstVector/vctQuaternionRotation3Base.h>

class vctRodriguezRotation3Test : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(vctRodriguezRotation3Test);

    CPPUNIT_TEST(TestDefaultConstructorDouble);
    CPPUNIT_TEST(TestDefaultConstructorFloat);

    CPPUNIT_TEST(TestNormalizeDouble);
    CPPUNIT_TEST(TestNormalizeFloat);

    CPPUNIT_TEST(TestConversionQuaternionDouble);
    CPPUNIT_TEST(TestConversionQuaternionFloat);

    CPPUNIT_TEST(TestConversionMatrixDouble);
    CPPUNIT_TEST(TestConversionMatrixFloat);

    CPPUNIT_TEST(TestConversionAxisAngleDouble);
    CPPUNIT_TEST(TestConversionAxisAngleFloat);

    CPPUNIT_TEST(TestFromSignaturesQuaternionDouble);
    CPPUNIT_TEST(TestFromSignaturesQuaternionFloat);

    CPPUNIT_TEST(TestFromSignaturesMatrixDouble);
    CPPUNIT_TEST(TestFromSignaturesMatrixFloat);

    CPPUNIT_TEST(TestFromSignaturesAxisAngleDouble);
    CPPUNIT_TEST(TestFromSignaturesAxisAngleFloat);

    CPPUNIT_TEST(TestRandomDouble);
    CPPUNIT_TEST(TestRandomFloat);

    CPPUNIT_TEST_SUITE_END();
    
 public:
    void setUp(void) {
    }
    
    void tearDown(void) {
    }

    /*! Test default constructor */
    template<class _elementType>
        void TestDefaultConstructor(void);
    void TestDefaultConstructorDouble(void);
    void TestDefaultConstructorFloat(void);
    
    /*! Test the normalize methods */
    template<class _elementType>
        void TestNormalize(void);
    void TestNormalizeDouble(void);
    void TestNormalizeFloat(void);

    /*! Test the conversion from and to quaternion rotation */
    template<class _elementType>
        void TestConversionQuaternion(void);
    void TestConversionQuaternionDouble(void);
    void TestConversionQuaternionFloat(void);

    /*! Test the conversion from and to matrix rotation */
    template<class _elementType>
        void TestConversionMatrix(void);
    void TestConversionMatrixDouble(void);
    void TestConversionMatrixFloat(void);

    /*! Test the conversion from and to AxisAngle rotation */
    template<class _elementType>
        void TestConversionAxisAngle(void);
    void TestConversionAxisAngleDouble(void);
    void TestConversionAxisAngleFloat(void);

    /*! Test the conversion from and to quaternion rotation */
    template<class _elementType>
        void TestFromSignaturesQuaternion(void);
    void TestFromSignaturesQuaternionDouble(void);
    void TestFromSignaturesQuaternionFloat(void);

    /*! Test the conversion from and to matrix rotation */
    template<class _elementType>
        void TestFromSignaturesMatrix(void);
    void TestFromSignaturesMatrixDouble(void);
    void TestFromSignaturesMatrixFloat(void);

    /*! Test the conversion from and to AxisAngle rotation */
    template<class _elementType>
        void TestFromSignaturesAxisAngle(void);
    void TestFromSignaturesAxisAngleDouble(void);
    void TestFromSignaturesAxisAngleFloat(void);

    /*! Test Random */
    template <class _elementType>
        void TestRandom(void);
    void TestRandomDouble(void);
    void TestRandomFloat(void);
};


