// -*- C++ -*-
//
// ======================================================================
//
// Brad T. Aagaard, U.S. Geological Survey
// Charles A. Williams, GNS Science
// Matthew G. Knepley, University of Chicago
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2017 University of California, Davis
//
// See COPYING for license information.
//
// ======================================================================
//

// DO NOT EDIT THIS FILE
// This file was generated from python application maxwellisotropic3dtimedep.

#include "MaxwellIsotropic3DTimeDepData.hh"

const int pylith::materials::MaxwellIsotropic3DTimeDepData::_dimension = 3;

const int pylith::materials::MaxwellIsotropic3DTimeDepData::_numLocs = 2;

const int pylith::materials::MaxwellIsotropic3DTimeDepData::_numProperties = 4;

const int pylith::materials::MaxwellIsotropic3DTimeDepData::_numStateVars = 2;

const int pylith::materials::MaxwellIsotropic3DTimeDepData::_numDBProperties = 4;

const int pylith::materials::MaxwellIsotropic3DTimeDepData::_numDBStateVars = 12;

const int pylith::materials::MaxwellIsotropic3DTimeDepData::_numPropsQuadPt = 4;

const int pylith::materials::MaxwellIsotropic3DTimeDepData::_numVarsQuadPt = 12;

const PylithScalar pylith::materials::MaxwellIsotropic3DTimeDepData::_lengthScale =   1.00000000e+03;

const PylithScalar pylith::materials::MaxwellIsotropic3DTimeDepData::_timeScale =   1.00000000e+00;

const PylithScalar pylith::materials::MaxwellIsotropic3DTimeDepData::_pressureScale =   2.25000000e+10;

const PylithScalar pylith::materials::MaxwellIsotropic3DTimeDepData::_densityScale =   2.25000000e+04;

const PylithScalar pylith::materials::MaxwellIsotropic3DTimeDepData::_dtStableImplicit =   8.88888889e+06;

const PylithScalar pylith::materials::MaxwellIsotropic3DTimeDepData::_dtStableExplicit =   1.92450090e-01;

const int pylith::materials::MaxwellIsotropic3DTimeDepData::_numPropertyValues[] = {
1,
1,
1,
1,
};

const int pylith::materials::MaxwellIsotropic3DTimeDepData::_numStateVarValues[] = {
6,
6,
};

const char* pylith::materials::MaxwellIsotropic3DTimeDepData::_dbPropertyValues[] = {
"density",
"vs",
"vp",
"viscosity",
};

const char* pylith::materials::MaxwellIsotropic3DTimeDepData::_dbStateVarValues[] = {
"total-strain-xx",
"total-strain-yy",
"total-strain-zz",
"total-strain-xy",
"total-strain-yz",
"total-strain-xz",
"viscous-strain-xx",
"viscous-strain-yy",
"viscous-strain-zz",
"viscous-strain-xy",
"viscous-strain-yz",
"viscous-strain-xz",
};

const PylithScalar pylith::materials::MaxwellIsotropic3DTimeDepData::_dbProperties[] = {
  2.50000000e+03,
  3.00000000e+03,
  5.19615242e+03,
  1.00000000e+18,
  2.00000000e+03,
  1.20000000e+03,
  2.07846097e+03,
  1.00000000e+19,
};

const PylithScalar pylith::materials::MaxwellIsotropic3DTimeDepData::_dbStateVars[] = {
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
};

const PylithScalar pylith::materials::MaxwellIsotropic3DTimeDepData::_properties[] = {
  2.50000000e+03,
  2.25000000e+10,
  2.25000000e+10,
  4.44444444e+07,
  2.00000000e+03,
  2.88000000e+09,
  2.88000000e+09,
  3.47222222e+09,
};

const PylithScalar pylith::materials::MaxwellIsotropic3DTimeDepData::_stateVars[] = {
  1.10000000e-04,
  1.20000000e-04,
  1.30000000e-04,
  1.40000000e-04,
  1.50000000e-04,
  1.60000000e-04,
 -1.00000000e-05,
  1.35525272e-20,
  1.00000000e-05,
  1.40000000e-04,
  1.50000000e-04,
  1.60000000e-04,
  4.10000000e-04,
  4.20000000e-04,
  4.30000000e-04,
  4.40000000e-04,
  4.50000000e-04,
  4.60000000e-04,
 -1.00000000e-05,
  0.00000000e+00,
  1.00000000e-05,
  4.40000000e-04,
  4.50000000e-04,
  4.60000000e-04,
};

const PylithScalar pylith::materials::MaxwellIsotropic3DTimeDepData::_propertiesNondim[] = {
  1.11111111e-01,
  1.00000000e+00,
  1.00000000e+00,
  4.44444444e+07,
  8.88888889e-02,
  1.28000000e-01,
  1.28000000e-01,
  3.47222222e+09,
};

const PylithScalar pylith::materials::MaxwellIsotropic3DTimeDepData::_stateVarsNondim[] = {
  1.10000000e-04,
  1.20000000e-04,
  1.30000000e-04,
  1.40000000e-04,
  1.50000000e-04,
  1.60000000e-04,
 -1.00000000e-05,
  1.35525272e-20,
  1.00000000e-05,
  1.40000000e-04,
  1.50000000e-04,
  1.60000000e-04,
  4.10000000e-04,
  4.20000000e-04,
  4.30000000e-04,
  4.40000000e-04,
  4.50000000e-04,
  4.60000000e-04,
 -1.00000000e-05,
  0.00000000e+00,
  1.00000000e-05,
  4.40000000e-04,
  4.50000000e-04,
  4.60000000e-04,
};

const PylithScalar pylith::materials::MaxwellIsotropic3DTimeDepData::_density[] = {
  2.50000000e+03,
  2.00000000e+03,
};

const PylithScalar pylith::materials::MaxwellIsotropic3DTimeDepData::_strain[] = {
  1.20000000e-04,
  1.30000000e-04,
  1.40000000e-04,
  1.50000000e-04,
  1.60000000e-04,
  1.70000000e-04,
  4.20000000e-04,
  4.30000000e-04,
  4.40000000e-04,
  4.50000000e-04,
  4.60000000e-04,
  4.70000000e-04,
};

const PylithScalar pylith::materials::MaxwellIsotropic3DTimeDepData::_stress[] = {
  1.02165205e+07,
  1.07095000e+07,
  1.12024795e+07,
  5.23570271e+06,
  5.72868226e+06,
  6.22166181e+06,
  5.29936332e+06,
  5.35120000e+06,
  5.40303668e+06,
  2.21169236e+06,
  2.27504905e+06,
  2.33840573e+06,
};

const PylithScalar pylith::materials::MaxwellIsotropic3DTimeDepData::_elasticConsts[] = {
  6.74326019e+10,
  2.25336999e+10,
  2.25336999e+10,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  2.25336999e+10,
  6.74326010e+10,
  2.25336999e+10,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  2.25336999e+10,
  2.25336999e+10,
  6.74326010e+10,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  4.48989011e+10,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  4.48989016e+10,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  4.48989016e+10,
  8.63988977e+09,
  2.88005546e+09,
  2.88005546e+09,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  2.88005546e+09,
  8.63988977e+09,
  2.88005546e+09,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  2.88005499e+09,
  2.88005499e+09,
  8.63988930e+09,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  5.75983408e+09,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  5.75983408e+09,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  0.00000000e+00,
  5.75983408e+09,
};

const PylithScalar pylith::materials::MaxwellIsotropic3DTimeDepData::_initialStress[] = {
  2.10000000e+04,
  2.20000000e+04,
  2.30000000e+04,
  2.40000000e+04,
  2.50000000e+04,
  2.60000000e+04,
  5.10000000e+04,
  5.20000000e+04,
  5.30000000e+04,
  5.40000000e+04,
  5.50000000e+04,
  5.60000000e+04,
};

const PylithScalar pylith::materials::MaxwellIsotropic3DTimeDepData::_initialStrain[] = {
  3.60000000e-05,
  3.50000000e-05,
  3.40000000e-05,
  3.30000000e-05,
  3.20000000e-05,
  3.10000000e-05,
  6.10000000e-05,
  6.20000000e-05,
  6.30000000e-05,
  6.60000000e-05,
  6.50000000e-05,
  6.40000000e-05,
};

const PylithScalar pylith::materials::MaxwellIsotropic3DTimeDepData::_stateVarsUpdated[] = {
  1.20000000e-04,
  1.30000000e-04,
  1.40000000e-04,
  1.50000000e-04,
  1.60000000e-04,
  1.70000000e-04,
 -9.95510110e-06,
  2.70137575e-20,
  9.95510110e-06,
  1.49348949e-04,
  1.59304050e-04,
  1.69259151e-04,
  4.20000000e-04,
  4.30000000e-04,
  4.40000000e-04,
  4.50000000e-04,
  4.60000000e-04,
  4.70000000e-04,
 -9.99942402e-06,
  0.00000000e+00,
  9.99942402e-06,
  4.49974369e-04,
  4.59973793e-04,
  4.69973217e-04,
};

pylith::materials::MaxwellIsotropic3DTimeDepData::MaxwellIsotropic3DTimeDepData(void)
{ // constructor
  dimension = _dimension;
  numLocs = _numLocs;
  numProperties = _numProperties;
  numStateVars = _numStateVars;
  numDBProperties = _numDBProperties;
  numDBStateVars = _numDBStateVars;
  numPropsQuadPt = _numPropsQuadPt;
  numVarsQuadPt = _numVarsQuadPt;
  lengthScale = _lengthScale;
  timeScale = _timeScale;
  pressureScale = _pressureScale;
  densityScale = _densityScale;
  dtStableImplicit = _dtStableImplicit;
  dtStableExplicit = _dtStableExplicit;
  numPropertyValues = const_cast<int*>(_numPropertyValues);
  numStateVarValues = const_cast<int*>(_numStateVarValues);
  dbPropertyValues = const_cast<char**>(_dbPropertyValues);
  dbStateVarValues = const_cast<char**>(_dbStateVarValues);
  dbProperties = const_cast<PylithScalar*>(_dbProperties);
  dbStateVars = const_cast<PylithScalar*>(_dbStateVars);
  properties = const_cast<PylithScalar*>(_properties);
  stateVars = const_cast<PylithScalar*>(_stateVars);
  propertiesNondim = const_cast<PylithScalar*>(_propertiesNondim);
  stateVarsNondim = const_cast<PylithScalar*>(_stateVarsNondim);
  density = const_cast<PylithScalar*>(_density);
  strain = const_cast<PylithScalar*>(_strain);
  stress = const_cast<PylithScalar*>(_stress);
  elasticConsts = const_cast<PylithScalar*>(_elasticConsts);
  initialStress = const_cast<PylithScalar*>(_initialStress);
  initialStrain = const_cast<PylithScalar*>(_initialStrain);
  stateVarsUpdated = const_cast<PylithScalar*>(_stateVarsUpdated);
} // constructor

pylith::materials::MaxwellIsotropic3DTimeDepData::~MaxwellIsotropic3DTimeDepData(void)
{}


// End of file