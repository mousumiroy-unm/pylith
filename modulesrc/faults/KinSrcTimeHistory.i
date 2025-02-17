// -*- C++ -*-
//
// ----------------------------------------------------------------------
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
// ----------------------------------------------------------------------
//

/** @file modulesrc/faults/KinSrcTimeHistory.i
 *
 * @brief Python interface to C++ KinSrcTimeHistory object.
 */

namespace pylith {
    namespace faults {

	class KinSrcTimeHistory : public pylith::faults::KinSrc {

	    // PUBLIC METHODS /////////////////////////////////////////////////
	public :

	    /// Default constructor.
	    KinSrcTimeHistory(void);
      
	    /// Destructor.
	    ~KinSrcTimeHistory(void);
	  
	  /** Set time history database.
	   *
	   * @param[in] db Time history database.
	   */
	  void setTimeHistoryDB(spatialdata::spatialdb::TimeHistory* th);
	  
	  /** Get time history database.
	   *
	   * @preturns Time history database.
	   */
	  const spatialdata::spatialdb::TimeHistory* getTimeHistoryDB(void);
	  
	  /** Set slip values at time t.
	   *
	   * @param[inout] slipLocalVec Local PETSc vector for slip values.
	   * @param[in] faultAuxiliaryField Auxiliary field for fault.
	   * @param[in] t Time t.
	   * @param[in] timeScale Time scale for nondimensionalization.
	   */
	  void updateSlip(PetscVec slipLocalVec,
			  pylith::topology::Field* faultAuxiliaryField,
			  const PylithScalar t,
			  const PylithScalar timeScale);

	    // PROTECTED METHODS //////////////////////////////////////////////////
	protected:

	    /** Setup auxiliary subfields (discretization and query fns).
	     *
	     * @param[in] normalizer Normalizer for nondimensionalizing values.
	     * @param[in] cs Coordinate system for problem.
	     */
	    void _auxiliaryFieldSetup(const spatialdata::units::Nondimensional& normalizer,
				const spatialdata::geocoords::CoordSys* cs);
	    
	}; // class KinSrcTimeHistory

    } // faults
} // pylith


// End of file 
