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

/**
 * @file libsrc/topology/Mesh.hh
 *
 * @brief C++ PyLith finite-element mesh.
 */

#if !defined(pylith_topology_mesh_hh)
#define pylith_topology_mesh_hh

// Include directives ---------------------------------------------------
#include "topologyfwd.hh" // forward declarations
#include "spatialdata/geocoords/geocoordsfwd.hh" // forward declarations

#include "pylith/utils/petscfwd.h" // HASA PetscDM

// Mesh -----------------------------------------------------------------
/** @brief PyLith finite-element mesh.
 *
 * Extends PETSc mesh to include coordinate system associated with
 * domain.
 */
class pylith::topology::Mesh { // Mesh
    friend class TestMesh; // unit testing

    // PUBLIC METHODS ///////////////////////////////////////////////////////
public:

    /** Default constructor.
     *
     * @param isSubmesh True if mesh is a submesh of another mesh.
     */
    Mesh(const bool isSubmesh=false);

    /** Constructor with dimension and communicator.
     *
     * @param dim Dimension associated with mesh cells.
     * @param comm MPI communicator for mesh.
     */
    Mesh(const int dim,
         const MPI_Comm& comm=PETSC_COMM_WORLD);

    /// Default destructor
    ~Mesh(void);

    /// Deallocate PETSc and local data structures.
    void deallocate(void);

    /** Get DMPlex mesh.
     *
     * @returns DMPlex mesh.
     */
    PetscDM dmMesh(void) const;

    /** Set DMPlex mesh.
     *
     * @param DMPlex mesh.
     * @param label Label for mesh.
     */
    void dmMesh(PetscDM dm,
                const char* label="domain");

    /** Get name of label for all mesh cells, including hybrid cells.
     *
     * @returns Name of label.
     */
    static
    const char* const getCellsLabelName(void);

    /** Set coordinate system.
     *
     * @param cs Coordinate system.
     */
    void setCoordSys(const spatialdata::geocoords::CoordSys* cs);

    /** Get coordinate system.
     *
     * @returns Coordinate system.
     */
    const spatialdata::geocoords::CoordSys* getCoordSys(void) const;

    /** Set debug flag.
     *
     * @param value Turn on debugging if true.
     */
    void debug(const bool value);

    /** Get debug flag.
     *
     * @param Get debugging flag.
     */
    bool debug(void) const;

    /** Get dimension of mesh.
     *
     * @returns Dimension of mesh.
     */
    int dimension(void) const;

    /** Get the number of vertices per cell
     *
     * @returns Number of vertices per cell.
     */
    int numCorners(void) const;

    /** Get number of vertices in mesh.
     *
     * @returns Number of vertices in mesh.
     */
    int numVertices(void) const;

    /** Get number of cells in mesh.
     *
     * @returns Number of cells in mesh.
     */
    int numCells(void) const;

    /** Is mesh composed of simplex cells?
     *
     * @returns Number of cells in mesh.
     */
    bool isSimplex(void) const;

    /** Get MPI communicator associated with mesh.
     *
     * @returns MPI communicator.
     */
    MPI_Comm comm(void) const;

    /** Get MPI rank.
     *
     * @returns MPI rank.
     */
    int commRank(void) const;

    /** View mesh.
     *
     * @param viewOption PETSc DM view option.
     *
     * PETSc mesh view options include:
     *   short summary [empty]
     *   detail summary ::ascii_info_detail
     *   detail in a file :refined.mesh:ascii_info_detail
     *   latex in a file  :refined.tex:ascii_latex
     *   VTK vtk:refined.vtk:ascii_vtk
     */
    void view(const char* viewOption="") const;

    // PRIVATE MEMBERS //////////////////////////////////////////////////////
private:

    PetscDM _dmMesh;

    spatialdata::geocoords::CoordSys* _coordsys; ///< Coordinate system.
    bool _debug; ///< Debugging flag for mesh.
    const bool _isSubmesh; ///< True if mesh is a submesh of another mesh.
    bool _isSimplex; ///< True if mesh has simplex cells (line, tri, tet).

    // NOT IMPLEMENTED //////////////////////////////////////////////////////
private:

    Mesh(const Mesh&); ///< Not implemented
    const Mesh& operator=(const Mesh&); ///< Not implemented

}; // Mesh

#include "Mesh.icc"

#endif // pylith_topology_mesh_hh

// End of file
