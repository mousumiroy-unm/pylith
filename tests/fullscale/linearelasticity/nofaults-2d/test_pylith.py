#!/usr/bin/env nemesis
#
# ======================================================================
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
# ======================================================================

from pylith.testing.FullTestApp import TestDriver, TestCase

import unittest


class TestApp(TestDriver):
    """Driver application for full-scale tests.
    """

    def __init__(self):
        """Constructor.
        """
        TestDriver.__init__(self)
        return

    def _suite(self):
        """Create test suite.
        """
        suite = unittest.TestSuite()

        import TestAxialDisp
        for test in TestAxialDisp.test_cases():
            suite.addTest(unittest.makeSuite(test))

        import TestShearTraction
        for test in TestShearTraction.test_cases():
            suite.addTest(unittest.makeSuite(test))

        import TestShearTractionRate
        for test in TestShearTractionRate.test_cases():
            suite.addTest(unittest.makeSuite(test))

        import TestGravity
        for test in TestGravity.test_cases():
            suite.addTest(unittest.makeSuite(test))

        import TestGravityRefState
        for test in TestGravityRefState.test_cases():
            suite.addTest(unittest.makeSuite(test))

        import TestGravityIncompressible
        for test in TestGravityIncompressible.test_cases():
            suite.addTest(unittest.makeSuite(test))

        return suite


# ----------------------------------------------------------------------
if __name__ == '__main__':
    TestCase.parse_args()
    TestApp().main()


# End of file
