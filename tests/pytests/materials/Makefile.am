# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
# Charles A. Williams, GNS Science
# Matthew G. Knepley, University of Chicago
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2017 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

include $(top_srcdir)/check.am

SUBDIRS = data

TESTS = testmaterials.py
dist_check_SCRIPTS = testmaterials.py

noinst_PYTHON = \
	TestHomogeneous.py \
	TestIsotropicLinearElasticityPlaneStrain.py \
	TestIsotropicLinearMaxwellPlaneStrain.py \
	TestIsotropicLinearGenMaxwellPlaneStrain.py \
	TestIsotropicLinearElasticity3D.py \
	TestIsotropicLinearMaxwell3D.py \
	TestIsotropicLinearGenMaxwell3D.py


# End of file
