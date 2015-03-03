#!/usr/bin/env python
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
# Charles A. Williams, GNS Science
# Matthew G. Knepley, University of Chicago
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2015 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#
# PREREQUISITES: numpy

# ======================================================================
import numpy

# Define parameters.
splayFile = "splay_points.txt"
numProfiles = 5
pointsPerProfile = 4
journalFile = "splay_skinsurf.jou"
acisFile = "splay_surf.sat"


# Read coordinates and reshape them.
splayCoords = numpy.loadtxt(splayFile, dtype=numpy.float64).reshape(numProfiles, pointsPerProfile, 3)

j = open(journalFile, 'w')
j.write("# CUBIT journal file generated by splay_skinsurf.py.\n" + \
            "#\n" + \
            "# Create an ACIS NURBS surface from a set of profiles.\n" + \
            "#\n" \
            "# ----------------------------------------------------------\n" + \
            "reset\n")


# Loop over profiles.
for iProfile in range(numProfiles):
    points = splayCoords[iProfile,:,:]
    for iPoint in range(pointsPerProfile):
        point = points[iPoint,:]
        j.write("create vertex x %10.2e y %10.2e z %10.2e\n" % \
                    (point[0], point[1], point[2]))
        if 0 == iPoint:
            j.write("${idBeg=Id('vertex')}\n")
    j.write("${idEnd=Id('vertex')}\n")
    j.write("create curve spline vertex {idBeg} to {idEnd} delete\n")
    if 0 == iProfile:
        j.write("${idCBeg=Id('curve')}\n")
j.write("${idCEnd=Id('curve')}\n\n")

# Create skin surface.
j.write("create surface skin curve {idCBeg} to {idCEnd}\n")

# Delete spline curves and export Acis file.
j.write("delete curve all\n")
j.write("export Acis '%s' overwrite\n" % acisFile)
j.close()

# End of file
