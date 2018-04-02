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
// Copyright (c) 2010-2016 University of California, Davis
//
// See COPYING for license information.
//
// ======================================================================
//

/**
 * @file modulesrc/meshio/OutputManager.i
 *
 * @brief Python interface to C++ OutputManager object.
 */

namespace pylith {
    namespace meshio {

	class pylith::meshio::OutputManager : public pylith::utils::PyreComponent
	{ // OutputManager

	    // PUBLIC METHODS /////////////////////////////////////////////////
	public :

		// PUBLIC ENUMS ///////////////////////////////////////////////////
	public:

		enum TriggerEnum {
		    SKIP_TIMESTEPS=0, ///< Skip X time steps between writes.
	    	ELAPSED_TIME=1, ///< Skip x time between writes.
		}; // TriggerEnum


	    /// Constructor
	    OutputManager(void);

	    /// Destructor
	    virtual
	    ~OutputManager(void);

	    /// Deallocate PETSc and local data structures.
	    virtual
	    void deallocate(void);

	    /** Set trigger for how often to write output.
	     *
	     * @param[in] flag Flag indicating which method to use for determining how often to write output.
	     */
	    void trigger(TriggerEnum flag);

	    /** Get trigger for how often to write otuput.
	     *
	     * @returns Flag indicating which method to use for determining how often to write output.
	     */
	    TriggerEnum trigger(void) const;

	    /** Set number of time steps to skip between writes.
	     *
	     * @param[in] Number of time steps to skip between writes.
	     */
	    void numTimeStepsSkip(const int value);

	    /** Get number of time steps to skip between writes.
	     *
	     * @returns Number of time steps to skip between writes.
	     */
	    int numTimeStepsSkip(void) const;

	    /** Set elapsed time between writes.
	     *
	     * @param[in] Elapsed time between writes.
	     */
	    void timeSkip(const double value);

	    /** Get elapsed time between writes.
	     *
	     * @returns Elapsed time between writes.
	     */
	    double timeSkip(void) const;

	    /** Set writer to write data to file.
	     *
	     * @param datawriter Writer for data.
	     */
	    void writer(DataWriter* const datawriter);

	    /** Set filter for vertex data.
	     *
	     * @param filter Filter to apply to vertex data before writing.
	     */
	    void vertexFilter(VertexFilter* const filter);

	    /** Set filter for cell data.
	     *
	     * @param filter Filter to apply to cell data before writing.
	     */
	    void cellFilter(CellFilter* const filter);

	    /** Set names of vertex information fields to output.
	     *
	     * @param[in] names Array of field names.
	     * @param[in] numNames Length of array.
	     */
	    %apply(const char* const* string_list, const int list_len){
			(const char* names[], const int numNames)
	    };
	    void vertexInfoFields(const char* names[],
				  const int numNames);
	    %clear(const char* const* names, const int numNames);

	    /** Set names of vertex data fields to output.
	     *
	     * @param[in] names Array of field names.
	     * @param[in] numNames Length of array.
	     */
	    %apply(const char* const* string_list, const int list_len){
			(const char* names[], const int numNames)
	    };
	    void vertexDataFields(const char* names[],
				  const int numNames);
	    %clear(const char* const* names, const int numNames);

	    /** Set names of cell information fields to output.
	     *
	     * @param[in] names Array of field names.
	     * @param[in] numNames Length of array.
	     */
	    %apply(const char* const* string_list, const int list_len){
			(const char* names[], const int numNames)
	    };
	    void cellInfoFields(const char* names[],
				const int numNames);
	    %clear(const char* const* names, const int numNames);

	    /** Set names of cell data fields to output.
	     *
	     * @param[in] names Array of field names.
	     * @param[in] numNames Length of array.
	     */
	    %apply(const char* const* string_list, const int list_len){
			(const char* names[], const int numNames)
	    };
	    void cellDataFields(const char* names[],
				const int numNames);
	    %clear(const char* const* names, const int numNames);

	    /** Verify configuration.
	     *
	     * @param[in] solution Solution field.
	     * @param[in] auxField Auxiliary field.
	     */
	    virtual
	    void verifyConfiguration(const pylith::topology::Field& solution,
				     const pylith::topology::Field& auxField) const;
	    
	    /** Write information.
	     *
	     * @param[in] auxField Auxiliary field.
	     * @param label Name of label defining cells to include in output
	     *   (=NULL means use all cells in mesh).
	     * @param labelId Value of label defining which cells to include.
	     */
	    virtual
	    void writeInfo(const pylith::topology::Field& auxField,
			   const char* label,
		const int labelId);
	    
	    /** Write solution at time step.
	     *
	     * @param[in] t Current time.
	     * @param[in] tindex Current time step.
	     * @param[in] solution Solution at time t.
	     * @param[in] auxField Auxiliary field.
	     */
	    virtual
	    void writeTimeStep(const PylithReal t,
			       const PylithInt tindex,
			       const pylith::topology::Field& solution,
			       const pylith::topology::Field& auxField);
	    
	    /** Prepare for output.
	     *
	     * @param mesh Finite-element mesh object.
	     * @param isInfo True if writing only once.
	     * @param label Name of label defining cells to include in output
	     *   (=NULL means use all cells in mesh).
	     * @param labelId Value of label defining which cells to include.
	     */
	    virtual
	    void open(const pylith::topology::Mesh& mesh,
		      const bool isInfo,
		      const char* label =NULL,
		      const int labelId =0);

	    /// Close output files.
	    virtual
	    void close(void);

	    /** Setup file for writing fields at time step.
	     *
	     * @param t Time of time step.
	     * @param mesh Finite-element mesh object.
	     * @param label Name of label defining cells to include in output
	     *   (=0 means use all cells in mesh).
	     * @param labelId Value of label defining which cells to include.
	     */
	    virtual
	    void openTimeStep(const PylithScalar t,
			      const pylith::topology::Mesh& mesh,
			      const char* label =NULL,
			      const int labelId =0);

	    /// End writing fields at time step.
	    virtual
	    void closeTimeStep(void);

	    /** Append finite-element vertex field to file.
	     *
	     * @param t Time associated with field.
	     * @param field Vertex field.
	     * @param mesh Mesh for output.
	     */
	    virtual
	    void appendVertexField(const PylithScalar t,
				   pylith::topology::Field& field,
				   const pylith::topology::Mesh& mesh);

	    /** Append finite-element cell field to file.
	     *
	     * @param t Time associated with field.
	     * @param field Cell field.
	     * @param label Name of label defining cells to include in output
	     *   (=0 means use all cells in mesh).
	     * @param labelId Value of label defining which cells to include.
	     */
	    virtual
	    void appendCellField(const PylithScalar t,
				 pylith::topology::Field& field,
				 const char* label =NULL,
				 const int labelId =0);

            /** Check whether we want to write output at time t.
	     *
	     * @param[in] t Time of proposed write.
	     * @param[in] timeStep Inxex of current time step.
	     * @returns True if output should be written at time t, false otherwise.
	     */
	    bool shouldWrite(const PylithReal t,
			   const PylithInt timeStep);

            /** Get buffer for field.
	     *
	     * Find the most appropriate buffer that matches field, reusing and reallocating as necessary.
	     *
	     * @param[in] fieldIn Input field.
	     * @param[in] name Name of subfield (optional).
	     * @returns Field to use as buffer for outputting field.
	     */
	    pylith::topology::Field& getBuffer(const pylith::topology::Field& fieldIn,
					       const char* name =NULL);

	}; // OutputManager

    } // meshio
} // pylith


// End of file
