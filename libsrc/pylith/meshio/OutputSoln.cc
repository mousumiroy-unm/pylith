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

#include <portinfo>

#include "OutputSoln.hh" // Implementation of class methods

#include "pylith/meshio/DataWriter.hh" // USES DataWriter
#include "pylith/meshio/FieldFilter.hh" // USES FieldFilter
#include "pylith/meshio/OutputTrigger.hh" // USES OutputTrigger

#include "pylith/topology/Mesh.hh" // USES Mesh
#include "pylith/topology/Field.hh" // USES Field
#include "pylith/topology/Fields.hh" // USES Fields

#include "pylith/utils/journals.hh" // USES PYLITH_COMPONENT_*

#include <iostream> // USES std::cout
#include <typeinfo> // USES typeid()

// ---------------------------------------------------------------------------------------------------------------------
// Constructor
pylith::meshio::OutputSoln::OutputSoln(void) {}


// ---------------------------------------------------------------------------------------------------------------------
// Destructor
pylith::meshio::OutputSoln::~OutputSoln(void) {
    deallocate();
} // destructor


// ---------------------------------------------------------------------------------------------------------------------
// Deallocate PETSc and local data structures.
void
pylith::meshio::OutputSoln::deallocate(void) {
    PYLITH_METHOD_BEGIN;

    ObserverSoln::deallocate();
    OutputObserver::deallocate();

    PYLITH_METHOD_END;
} // deallocate


// ---------------------------------------------------------------------------------------------------------------------
// Set names of solution subfields requested for output.
void
pylith::meshio::OutputSoln::setOutputSubfields(const char* names[],
                                               const int numNames) {
    PYLITH_METHOD_BEGIN;
    PYLITH_COMPONENT_DEBUG("OutputSoln::dataFields(names="<<names<<", numNames="<<numNames<<")");

    assert((names && numNames) || (!names && !numNames));

    _subfieldNames.resize(numNames);
    for (int i = 0; i < numNames; ++i) {
        assert(names[i]);
        _subfieldNames[i] = names[i];
    } // for

    PYLITH_METHOD_END;
} // setOutputSubfields


// ---------------------------------------------------------------------------------------------------------------------
// Get names of solution subfields requested for output.
const pylith::string_vector&
pylith::meshio::OutputSoln::getOutputSubfields(void) const {
    PYLITH_METHOD_BEGIN;
    PYLITH_COMPONENT_DEBUG("OutputSoln::dataFields()");

    PYLITH_METHOD_RETURN(_subfieldNames);
} // getOutputSubfields


// ---------------------------------------------------------------------------------------------------------------------
// Set time scale.
void
pylith::meshio::OutputSoln::setTimeScale(const PylithReal value) {
    OutputObserver::setTimeScale(value);
} // setTimeScale


// ---------------------------------------------------------------------------------------------------------------------
// Verify configuration is acceptable.
void
pylith::meshio::OutputSoln::verifyConfiguration(const pylith::topology::Field& solution) const {
    PYLITH_METHOD_BEGIN;
    PYLITH_COMPONENT_DEBUG("verifyConfiguration(solution="<<solution.label()<<")");

    const size_t numSubfieldNames = _subfieldNames.size();
    if ((numSubfieldNames > 0) && (std::string("all") != _subfieldNames[0])) {
        for (size_t iField = 0; iField < numSubfieldNames; iField++) {
            if (!solution.hasSubfield(_subfieldNames[iField].c_str())) {
                std::ostringstream msg;
                msg << "Could not find subfield '" << _subfieldNames[iField] << "' in solution '" << solution.label()
                    << "' for output using solution observer ''" << PyreComponent::getIdentifier() <<"''.";
                throw std::runtime_error(msg.str());
            } // if
        } // for
    } // if

    PYLITH_METHOD_END;
} // verifyConfiguration


// ---------------------------------------------------------------------------------------------------------------------
// Get update from integrator (subject of observer).
void
pylith::meshio::OutputSoln::update(const PylithReal t,
                                   const PylithInt tindex,
                                   const pylith::topology::Field& solution) {
    assert(_trigger);
    if (_trigger->shouldWrite(t, tindex)) {
        _writeSolnStep(t, tindex, solution);
    } // if
} // update


// ---------------------------------------------------------------------------------------------------------------------
// Prepare for output.
void
pylith::meshio::OutputSoln::_open(const pylith::topology::Mesh& mesh) {
    PYLITH_METHOD_BEGIN;
    PYLITH_COMPONENT_DEBUG("OutputSoln::open(mesh="<<typeid(mesh).name()<<")");

    if (!_writer) {
        PYLITH_COMPONENT_ERROR("Writer for solution output observer '"<<getIdentifier()<<"'.");
    } // if

    assert(_trigger);
    _trigger->setTimeScale(_timeScale);

    assert(_writer);
    const bool isInfo = false;
    _writer->timeScale(_timeScale);
    _writer->open(mesh, isInfo);

    PYLITH_METHOD_END;
} // _open


// ---------------------------------------------------------------------------------------------------------------------
/// Close output files.
void
pylith::meshio::OutputSoln::_close(void) {
    PYLITH_METHOD_BEGIN;
    PYLITH_COMPONENT_DEBUG("OutputSoln::_close()");

    assert(_writer);
    _writer->close();

    PYLITH_METHOD_END;
} // _close


// ---------------------------------------------------------------------------------------------------------------------
// Prepare for output at this solution step.
void
pylith::meshio::OutputSoln::_openSolnStep(const PylithReal t,
                                          const pylith::topology::Mesh& mesh) {
    PYLITH_METHOD_BEGIN;
    PYLITH_COMPONENT_DEBUG("OutputSoln::_openSolnStep(t="<<t<<", mesh="<<typeid(mesh).name()<<")");

    assert(_writer);
    if (!_writer->isOpen()) {
        _open(mesh);
    } // if
    _writer->openTimeStep(t, mesh);

    PYLITH_METHOD_END;
} // _openSolnStep


// ---------------------------------------------------------------------------------------------------------------------
// Finalize output at this solution step.
void
pylith::meshio::OutputSoln::_closeSolnStep(void) {
    assert(_writer);
    _writer->closeTimeStep();

} // _closeSolnStep


// ---------------------------------------------------------------------------------------------------------------------
// Write data for step in solution.
void
pylith::meshio::OutputSoln::_writeSolnStep(const PylithReal t,
                                           const PylithInt tindex,
                                           const pylith::topology::Field& solution) {
    PYLITH_METHOD_BEGIN;
    PYLITH_COMPONENT_DEBUG("OutputSoln::_writeSolnStep(t="<<t<<", tindex="<<tindex<<", solution="<<solution.label()<<") empty method");

    // Empty method.

    PYLITH_METHOD_END;
} // _writeSolnStep


// ---------------------------------------------------------------------------------------------------------------------
// Append finite-element vertex field to file.
void
pylith::meshio::OutputSoln::_appendField(const PylithReal t,
                                         pylith::topology::Field* field,
                                         const pylith::topology::Mesh& mesh) {
    PYLITH_METHOD_BEGIN;
    PYLITH_COMPONENT_DEBUG("OutputSoln::appendField(t="<<t<<", field="<<typeid(field).name()<<", mesh="<<typeid(mesh).name()<<")");

    assert(field);

    pylith::topology::Field* fieldFiltered = _fieldFilter->filter(field);
    pylith::topology::Field* fieldDimensioned = _dimensionField(fieldFiltered);assert(fieldDimensioned);

    const int basisOrder = _getBasisOrder(*fieldDimensioned);
    switch (basisOrder) {
    case 0:
        _writer->writeCellField(t, *fieldDimensioned);
        break;

    case 1:
        _writer->writeVertexField(t, *fieldDimensioned, mesh);
        break;

    default:
        PYLITH_COMPONENT_ERROR(
            "Unsupported basis order ("
                << basisOrder <<") for output. Use FieldFilterProject with basis order of 0 or 1. Skipping output of '"
                << field->label() << "' field."
            );
    } // switch

    PYLITH_METHOD_END;
} // _appendField


// ---------------------------------------------------------------------------------------------------------------------
// Get names of subfields for output.
pylith::string_vector
pylith::meshio::OutputSoln::_expandSubfieldNames(const pylith::topology::Field& solution) const {
    PYLITH_METHOD_BEGIN;

    if ((1 == _subfieldNames.size()) && (std::string("all") == _subfieldNames[0])) {
        PYLITH_METHOD_RETURN(solution.subfieldNames());
    } // if

    PYLITH_METHOD_RETURN(_subfieldNames);
} // _expandSubfieldNames


// End of file