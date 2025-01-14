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
# @file tests/fullscale/cornercases/2d/meshes.py
#
# @brief Mesh information for test cases.


class Tri(object):
    """Mesh information for tri mesh.
    """
    DOMAIN = {
        "ncells": 2,
        "ncorners": 3,
        "nvertices": 4,
    }
    MATERIALS = {
        "elastic": {
            "ncells": 2,
            "ncorners": 3,
            "nvertices": 4,
        },
    }
    BOUNDARIES = {
        "bc_xneg": {
            "ncells": 1,
            "ncorners": 2,
            "nvertices": 2,
        },
        "bc_xpos": {
            "ncells": 1,
            "ncorners": 2,
            "nvertices": 2,
        },
    }


class Quad(object):
    """Mesh information for quad mesh.
    """
    DOMAIN = {
        "ncells": 1,
        "ncorners": 4,
        "nvertices": 4,
    }
    MATERIALS = {
        "elastic": {
            "ncells": 1,
            "ncorners": 4,
            "nvertices": 4,
        },
    }
    BOUNDARIES = {
        "bc_xneg": {
            "ncells": 1,
            "ncorners": 2,
            "nvertices": 2,
        },
        "bc_xpos": {
            "ncells": 1,
            "ncorners": 2,
            "nvertices": 2,
        },
        "bc_yneg": {
            "ncells": 1,
            "ncorners": 2,
            "nvertices": 2,
        },
        "bc_ypos": {
            "ncells": 1,
            "ncorners": 2,
            "nvertices": 2,
        },
        "bc_domain": {
            "ncells": 4,
            "ncorners": 2,
            "nvertices": 4,
        },
    }


# End of file
