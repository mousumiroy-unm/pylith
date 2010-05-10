// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ----------------------------------------------------------------------
//

/**
 * @file unittests/libtests/faults/TestFaultCohesiveDynHex8.hh
 *
 * @brief C++ TestFaultCohesiveDynHex8 object.
 *
 * C++ unit testing for FaultCohesiveDyn for mesh with 3-D quadrilateral cells.
 */

#if !defined(pylith_faults_testfaultcohesivedynhex8_hh)
#define pylith_faults_testfaultcohesivedynhex8_hh

#define NO_FAULT_OPENING

#include "TestFaultCohesiveDyn.hh" // ISA TestFaultCohesiveDyn

/// Namespace for pylith package
namespace pylith {
  namespace faults {
    class TestFaultCohesiveDynHex8;
  } // bc
} // pylith

/// C++ unit testing for FaultCohesiveDyn for mesh with 3-D quadrilateral cells.
class pylith::faults::TestFaultCohesiveDynHex8 : public TestFaultCohesiveDyn
{ // class TestFaultCohesiveDynHex8

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestFaultCohesiveDynHex8 );

  CPPUNIT_TEST( testInitialize );
  CPPUNIT_TEST( testConstrainSolnSpaceStick );
  CPPUNIT_TEST( testConstrainSolnSpaceSlip );
#if !defined(NO_FAULT_OPENING)
  CPPUNIT_TEST( testConstrainSolnSpaceOpen );
#endif
  CPPUNIT_TEST( testUpdateStateVars );
  CPPUNIT_TEST( testCalcTractions );

  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Setup testing data.
  void setUp(void);

}; // class TestFaultCohesiveDynHex8

#endif // pylith_faults_testfaultcohesivedynhex8_hh


// End of file 
