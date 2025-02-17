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

#include <portinfo>

#include "TestDataWriterHDF5ExtMaterial.hh" // Implementation of class methods

#include "pylith/topology/Mesh.hh" // USES Mesh
#include "pylith/topology/Field.hh" // USES Field
#include "pylith/meshio/DataWriterHDF5Ext.hh" // USES DataWriterHDF5Ext
#include "pylith/meshio/OutputSubfield.hh" // USES OutputSubfield

// ------------------------------------------------------------------------------------------------
// Setup testing data.
void
pylith::meshio::TestDataWriterHDF5ExtMaterial::setUp(void) {
    PYLITH_METHOD_BEGIN;

    TestDataWriterMaterial::setUp();
    _data = NULL;

    PYLITH_METHOD_END;
} // setUp


// ------------------------------------------------------------------------------------------------
// Tear down testing data.
void
pylith::meshio::TestDataWriterHDF5ExtMaterial::tearDown(void) {
    PYLITH_METHOD_BEGIN;

    TestDataWriterMaterial::tearDown();
    delete _data;_data = NULL;

    PYLITH_METHOD_END;
} // tearDown


// ------------------------------------------------------------------------------------------------
// Test open() and close()
void
pylith::meshio::TestDataWriterHDF5ExtMaterial::testOpenClose(void) {
    PYLITH_METHOD_BEGIN;

    CPPUNIT_ASSERT(_materialMesh);
    CPPUNIT_ASSERT(_data);

    DataWriterHDF5Ext writer;

    writer.filename(_data->opencloseFilename);

    const bool isInfo = false;
    writer.open(*_materialMesh, isInfo);
    writer.close();

    checkFile(_data->opencloseFilename);

    PYLITH_METHOD_END;
} // testOpenClose


// ------------------------------------------------------------------------------------------------
// Test writeVertexField.
void
pylith::meshio::TestDataWriterHDF5ExtMaterial::testWriteVertexField(void) {
    PYLITH_METHOD_BEGIN;

    CPPUNIT_ASSERT(_domainMesh);
    CPPUNIT_ASSERT(_materialMesh);
    CPPUNIT_ASSERT(_data);

    DataWriterHDF5Ext writer;

    pylith::topology::Field vertexField(*_domainMesh);
    _createVertexField(&vertexField);

    writer.filename(_data->vertexFilename);

    const PylithScalar timeScale = 4.0;
    writer.setTimeScale(timeScale);
    const PylithScalar t = _data->time / timeScale;

    const bool isInfo = false;
    writer.open(*_materialMesh, isInfo);
    writer.openTimeStep(t, *_materialMesh);

    const pylith::string_vector& subfieldNames = vertexField.subfieldNames();
    const size_t numFields = subfieldNames.size();
    for (size_t i = 0; i < numFields; ++i) {
        OutputSubfield* subfield = OutputSubfield::create(vertexField, *_materialMesh, subfieldNames[i].c_str(), 1);
        CPPUNIT_ASSERT(subfield);
        subfield->project(vertexField.outputVector());
        writer.writeVertexField(t, *subfield);
        delete subfield;subfield = NULL;
    } // for
    writer.closeTimeStep();
    writer.close();

    checkFile(_data->vertexFilename);

    PYLITH_METHOD_END;
} // testWriteVertexField


// ------------------------------------------------------------------------------------------------
// Test writeCellField.
void
pylith::meshio::TestDataWriterHDF5ExtMaterial::testWriteCellField(void) {
    PYLITH_METHOD_BEGIN;

    CPPUNIT_ASSERT(_materialMesh);
    CPPUNIT_ASSERT(_data);

    DataWriterHDF5Ext writer;

    pylith::topology::Field cellField(*_materialMesh);
    _createCellField(&cellField);

    writer.filename(_data->cellFilename);

    const PylithScalar timeScale = 4.0;
    writer.setTimeScale(timeScale);
    const PylithScalar t = _data->time / timeScale;

    const bool isInfo = false;
    writer.open(*_materialMesh, isInfo);
    writer.openTimeStep(t, *_materialMesh);

    const pylith::string_vector& subfieldNames = cellField.subfieldNames();
    const size_t numFields = subfieldNames.size();
    for (size_t i = 0; i < numFields; ++i) {
        OutputSubfield* subfield = OutputSubfield::create(cellField, *_materialMesh, subfieldNames[i].c_str(), 0);
        CPPUNIT_ASSERT(subfield);
        subfield->project(cellField.outputVector());
        writer.writeCellField(t, *subfield);
        delete subfield;subfield = NULL;
    } // for
    writer.closeTimeStep();
    writer.close();

    checkFile(_data->cellFilename);

    PYLITH_METHOD_END;
} // testWriteCellField


// ------------------------------------------------------------------------------------------------
// Get test data.
pylith::meshio::TestDataWriterMaterial_Data*
pylith::meshio::TestDataWriterHDF5ExtMaterial::_getData(void) {
    return _data;
} // _getData


// End of file
