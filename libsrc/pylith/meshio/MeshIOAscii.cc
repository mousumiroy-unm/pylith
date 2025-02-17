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

#include <portinfo>

#include "MeshIOAscii.hh" // implementation of class methods

#include "MeshBuilder.hh" // USES MeshBuilder
#include "pylith/topology/Mesh.hh" // USES Mesh

#include "pylith/utils/array.hh" // USES scalar_array, int_array, string_vector
#include "spatialdata/utils/LineParser.hh" // USES LineParser

#include "pylith/utils/journals.hh" // USES PYLITH_COMPONENT_*

#include <iomanip> // USES setw(), setiosflags(), resetiosflags()
#include <strings.h> // USES strcasecmp()
#include <cassert> // USES assert()
#include <fstream> // USES std::ifstream, std::ofstream
#include <stdexcept> // USES std::runtime_error
#include <sstream> // USES std::ostringstream
#include <typeinfo> // USES std::typeid

// ---------------------------------------------------------------------------------------------------------------------
namespace pylith {
    namespace meshio {
        class _MeshIOAscii {
public:

            static const char* groupTypeNames[];
        }; // _MeshIOAscii
        const char* _MeshIOAscii::_MeshIOAscii::groupTypeNames[2] = {
            "vertices",
            "cells",
        };
    } // meshio
} // pylith

// ---------------------------------------------------------------------------------------------------------------------
// Constructor
pylith::meshio::MeshIOAscii::MeshIOAscii(void) :
    _filename(""),
    _useIndexZero(true) { // constructor
    PyreComponent::setName("meshioascii");
} // constructor


// ---------------------------------------------------------------------------------------------------------------------
// Destructor
pylith::meshio::MeshIOAscii::~MeshIOAscii(void) { // destructor
    deallocate();
} // destructor


// ---------------------------------------------------------------------------------------------------------------------
// Deallocate PETSc and local data structures.
void
pylith::meshio::MeshIOAscii::deallocate(void) { // deallocate
    PYLITH_METHOD_BEGIN;

    MeshIO::deallocate();

    PYLITH_METHOD_END;
} // deallocate


// ---------------------------------------------------------------------------------------------------------------------
// Read mesh.
void
pylith::meshio::MeshIOAscii::_read(void) { // _read
    PYLITH_METHOD_BEGIN;
    PYLITH_COMPONENT_DEBUG("_read()");

    const int commRank = _mesh->commRank();
    int meshDim = 0;
    int spaceDim = 0;
    int numVertices = 0;
    int numCells = 0;
    int numCorners = 0;
    scalar_array coordinates;
    int_array cells;
    int_array materialIds;

    if (0 == commRank) {
        std::ifstream filein(_filename.c_str());
        if (!filein.is_open() || !filein.good()) {
            std::ostringstream msg;
            msg << "Could not open mesh file '" << _filename
                << "' for reading.\n";
            throw std::runtime_error(msg.str());
        } // if

        spatialdata::utils::LineParser parser(filein, "//");
        parser.eatwhitespace(true);

        std::string token;
        std::istringstream buffer;
        const int maxIgnore = 1024;

        buffer.str(parser.next());
        buffer >> token;
        if (strcasecmp(token.c_str(), "mesh")) {
            std::ostringstream msg;
            msg << "Expected 'mesh' token but encountered '" << token << "'\n";
            throw std::runtime_error(msg.str());
        } // if

        bool readDim = false;
        bool readCells = false;
        bool readVertices = false;
        bool builtMesh = false;

        try {
            buffer.str(parser.next());
            buffer.clear();
            buffer >> token;
            while (buffer.good() && token != "}") {
                if (0 == strcasecmp(token.c_str(), "dimension")) {
                    buffer.ignore(maxIgnore, '=');
                    buffer >> meshDim;
                    readDim = true;
                } else if (0 == strcasecmp(token.c_str(), "use-index-zero")) {
                    buffer.ignore(maxIgnore, '=');
                    std::string flag = "";
                    buffer >> flag;
                    if (0 == strcasecmp(flag.c_str(), "true")) {
                        _useIndexZero = true;
                    } else {
                        _useIndexZero = false;
                    }
                } else if (0 == strcasecmp(token.c_str(), "vertices")) {
                    _readVertices(parser, &coordinates, &numVertices, &spaceDim);
                    readVertices = true;
                } else if (0 == strcasecmp(token.c_str(), "cells")) {
                    _readCells(parser, &cells, &materialIds, &numCells, &numCorners);
                    readCells = true;
                } else if (0 == strcasecmp(token.c_str(), "group")) {
                    std::string name;
                    GroupPtType type;
                    int_array points;

                    if (!builtMesh) {
                        throw std::runtime_error("Both 'vertices' and 'cells' must "
                                                 "precede any groups in mesh file.");
                    }
                    _readGroup(parser, &points, &type, &name);
                    _setGroup(name, type, points);
                } else {
                    std::ostringstream msg;
                    msg << "Could not parse '" << token << "' into a mesh setting.";
                    throw std::runtime_error(msg.str());
                } // else

                if (readDim && readCells && readVertices && !builtMesh) {
                    // Can now build mesh
                    MeshBuilder::buildMesh(_mesh, &coordinates, numVertices, spaceDim, cells, numCells, numCorners, meshDim);
                    _setMaterials(materialIds);
                    builtMesh = true;
                } // if

                buffer.str(parser.next());
                buffer.clear();
                buffer >> token;
            } // while
            if (token != "}") {
                throw std::runtime_error("I/O error occurred while parsing mesh tokens.");
            }
        } catch (const std::exception& err) {
            std::ostringstream msg;
            msg << "Error occurred while reading PyLith mesh ASCII file '"
                << _filename << "'.\n"
                << err.what();
            throw std::runtime_error(msg.str());
        } catch (...) {
            std::ostringstream msg;
            msg << "Unknown I/O error while reading PyLith mesh ASCII file '"
                << _filename << "'.\n";
            throw std::runtime_error(msg.str());
        } // catch
        filein.close();
    } else {
        MeshBuilder::buildMesh(_mesh, &coordinates, numVertices, spaceDim, cells, numCells, numCorners, meshDim);
        _setMaterials(materialIds);
    } // if/else
    _distributeGroups();

    PYLITH_METHOD_END;
} // read


// ---------------------------------------------------------------------------------------------------------------------
// Write mesh to file.
void
pylith::meshio::MeshIOAscii::_write(void) const { // write
    PYLITH_METHOD_BEGIN;
    PYLITH_COMPONENT_DEBUG("_write()");

    std::ofstream fileout(_filename.c_str());
    if (!fileout.is_open() || !fileout.good()) {
        std::ostringstream msg;
        msg << "Could not open mesh file '" << _filename
            << "' for writing.\n";
        throw std::runtime_error(msg.str());
    } // if

    fileout
        << "mesh = {\n"
        << "  dimension = " << getMeshDim() << "\n"
        << "  use-index-zero = " << (_useIndexZero ? "true" : "false") << "\n";

    _writeVertices(fileout);
    _writeCells(fileout);

    string_vector groups;
    _getGroupNames(&groups);
    const int numGroups = groups.size();
    for (int i = 0; i < numGroups; ++i) {
        _writeGroup(fileout, groups[i].c_str());
    }

    fileout << "}\n";
    fileout.close();

    PYLITH_METHOD_END;
} // write


// ----------------------------------------------------------------------
// Read mesh vertices.
void
pylith::meshio::MeshIOAscii::_readVertices(spatialdata::utils::LineParser& parser,
                                           scalar_array* coordinates,
                                           int* numVertices,
                                           int* numDims) const { // _readVertices
    PYLITH_METHOD_BEGIN;
    PYLITH_COMPONENT_DEBUG("_readVertices(parser="<<typeid(parser).name()<<", cordinates="<<coordinates<<", numVertices="<<numVertices<<", numDims="<<numDims<<")");

    assert(coordinates);
    assert(numVertices);
    assert(numDims);

    std::string token;
    std::istringstream buffer;
    const int maxIgnore = 1024;
    buffer.str(parser.next());
    buffer.clear();
    buffer >> token;
    while (buffer.good() && token != "}") {
        if (0 == strcasecmp(token.c_str(), "dimension")) {
            buffer.ignore(maxIgnore, '=');
            buffer >> *numDims;
        } else if (0 == strcasecmp(token.c_str(), "count")) {
            buffer.ignore(maxIgnore, '=');
            buffer >> *numVertices;
        } else if (0 == strcasecmp(token.c_str(), "coordinates")) {
            const int size = (*numVertices) * (*numDims);
            if (0 == size) {
                const char* msg =
                    "Tokens 'dimension' and 'count' must precede 'coordinates'.";
                throw std::runtime_error(msg);
            } // if
            coordinates->resize(size);
            int label;
            for (int iVertex = 0, i = 0; iVertex < *numVertices; ++iVertex) {
                buffer.str(parser.next());
                buffer.clear();
                buffer >> label;
                for (int iDim = 0; iDim < *numDims; ++iDim) {
                    buffer >> (*coordinates)[i++];
                }
            } // for
            parser.ignore('}');
        } else {
            std::ostringstream msg;
            msg << "Could not parse '" << token << "' into a vertices setting.";
            throw std::runtime_error(msg.str());
        } // else
        buffer.str(parser.next());
        buffer.clear();
        buffer >> token;
    } // while
    if (token != "}") {
        throw std::runtime_error("I/O error while parsing vertices.");
    }

    PYLITH_METHOD_END;
} // _readVertices


// ----------------------------------------------------------------------
// Write mesh vertices.
void
pylith::meshio::MeshIOAscii::_writeVertices(std::ostream& fileout) const { // _writeVertices
    PYLITH_METHOD_BEGIN;
    PYLITH_COMPONENT_DEBUG("_writeVertices(fileout="<<typeid(fileout).name()<<")");

    int spaceDim = 0;
    int numVertices = 0;
    scalar_array coordinates;
    _getVertices(&coordinates, &numVertices, &spaceDim);

    fileout
        << "  vertices = {\n"
        << "    dimension = " << spaceDim << "\n"
        << "    count = " << numVertices << "\n"
        << "    coordinates = {\n"
        << std::resetiosflags(std::ios::fixed)
        << std::setiosflags(std::ios::scientific)
        << std::setprecision(6);
    for (int iVertex = 0, i = 0; iVertex < numVertices; ++iVertex) {
        fileout << "      ";
        fileout << std::setw(8) << iVertex;
        for (int iDim = 0; iDim < spaceDim; ++iDim) {
            fileout << std::setw(18) << coordinates[i++];
        }
        fileout << "\n";
    } // for
    fileout
        << "    }\n"
        << "  }\n";

    PYLITH_METHOD_END;
} // _writeVertices


// ----------------------------------------------------------------------
// Read mesh cells.
void
pylith::meshio::MeshIOAscii::_readCells(spatialdata::utils::LineParser& parser,
                                        int_array* cells,
                                        int_array* materialIds,
                                        int* numCells,
                                        int* numCorners) const { // _readCells
    PYLITH_METHOD_BEGIN;
    PYLITH_COMPONENT_DEBUG("_readCells(parser="<<typeid(parser).name()<<", cells="<<cells<<", materialIds="<<materialIds<<", numCells="<<numCells<<",numCorners="<<numCorners<<")");

    assert(cells);
    assert(materialIds);
    assert(numCells);
    assert(numCorners);

    std::string token;
    std::istringstream buffer;
    const int maxIgnore = 1024;
    buffer.str(parser.next());
    buffer.clear();
    buffer >> token;
    while (buffer.good() && token != "}") {
        if (0 == strcasecmp(token.c_str(), "num-corners")) {
            buffer.ignore(maxIgnore, '=');
            buffer >> *numCorners;
        } else if (0 == strcasecmp(token.c_str(), "count")) {
            buffer.ignore(maxIgnore, '=');
            buffer >> *numCells;
        } else if (0 == strcasecmp(token.c_str(), "simplices")) {
            const int size = (*numCells) * (*numCorners);
            if (0 == size) {
                const char* msg =
                    "Tokens 'num-corners' and 'count' must precede 'cells'.";
                throw std::runtime_error(msg);
            } // if
            cells->resize(size);
            int label;
            for (int iCell = 0, i = 0; iCell < *numCells; ++iCell) {
                buffer.str(parser.next());
                buffer.clear();
                buffer >> label;
                for (int iCorner = 0; iCorner < *numCorners; ++iCorner) {
                    buffer >> (*cells)[i++];
                }
            } // for
            if (!_useIndexZero) {
                // if files begins with index 1, then decrement to index 0
                // for compatibility with PETSc
                for (int i = 0; i < size; ++i) {
                    --(*cells)[i];
                }
            } // if
            parser.ignore('}');
        } else if (0 == strcasecmp(token.c_str(), "material-ids")) {
            if (0 == *numCells) {
                const char* msg =
                    "Token 'count' must precede 'material-ids'.";
                throw std::runtime_error(msg);
            } // if
            const int size = *numCells;
            materialIds->resize(size);
            int label = 0;
            for (int iCell = 0; iCell < *numCells; ++iCell) {
                buffer.str(parser.next());
                buffer.clear();
                buffer >> label;
                buffer >> (*materialIds)[iCell];
            } // for

            // Zero index does NOT apply to materialIds.

            parser.ignore('}');
        } else {
            std::ostringstream msg;
            msg << "Could not parse '" << token << "' into an cells setting.";
            throw std::runtime_error(msg.str());
        } // else
        buffer.str(parser.next());
        buffer.clear();
        buffer >> token;
    } // while
    if (token != "}") {
        throw std::runtime_error("I/O error while parsing cells.");
    }

    // If no materials given, assign each cell material identifier of 0
    if ((0 == materialIds->size()) && (*numCells > 0)) {
        const int size = *numCells;
        materialIds->resize(size);
        (*materialIds) = 0;
    } // if

    PYLITH_METHOD_END;
} // _readCells


// ----------------------------------------------------------------------
// Write mesh cells.
void
pylith::meshio::MeshIOAscii::_writeCells(std::ostream& fileout) const { // _writeCells
    PYLITH_METHOD_BEGIN;
    PYLITH_COMPONENT_DEBUG("_writeCells(fileout="<<typeid(fileout).name()<<")");

    int meshDim = 0;
    int numCells = 0;
    int numCorners = 0;
    int_array cells;
    _getCells(&cells, &numCells, &numCorners, &meshDim);

    fileout
        << "  cells = {\n"
        << "    count = " << numCells << "\n"
        << "    num-corners = " << numCorners << "\n"
        << "    simplices = {\n";

    for (int iCell = 0, i = 0; iCell < numCells; ++iCell) {
        fileout << "      " << std::setw(8) << iCell;
        for (int iCorner = 0; iCorner < numCorners; ++iCorner) {
            fileout << std::setw(8) << cells[i++];
        }
        fileout << "\n";
    } // for
    fileout << "    }\n";

    // Write material identifiers
    int_array materialIds;
    _getMaterials(&materialIds);
    assert(size_t(numCells) == materialIds.size());
    fileout << "    material-ids = {\n";
    for (int iCell = 0; iCell < numCells; ++iCell) {
        fileout << "      " << std::setw(8) << iCell;
        fileout << std::setw(4) << materialIds[iCell] << "\n";
    } // for
    fileout << "    }\n";

    fileout << "  }\n";

    PYLITH_METHOD_END;
} // _writeCells


// ----------------------------------------------------------------------
// Read mesh group.
void
pylith::meshio::MeshIOAscii::_readGroup(spatialdata::utils::LineParser& parser,
                                        int_array* points,
                                        GroupPtType* type,
                                        std::string* name) const { // _readGroup
    PYLITH_METHOD_BEGIN;
    PYLITH_COMPONENT_DEBUG("_readGroup(parser="<<typeid(parser).name()<<", points="<<points<<", type="<<type<<", name="<<name<<")");

    assert(points);
    assert(type);
    assert(name);

    std::string token;
    std::istringstream buffer;
    const int maxIgnore = 1024;
    int numPoints = -1;
    buffer.str(parser.next());
    buffer.clear();
    buffer >> token;
    while (buffer.good() && token != "}") {
        if (0 == strcasecmp(token.c_str(), "name")) {
            buffer.ignore(maxIgnore, '=');
            buffer >> std::ws;
            char cbuffer[maxIgnore];
            buffer.get(cbuffer, maxIgnore, '\n');
            *name = cbuffer;
        } else if (0 == strcasecmp(token.c_str(), "type")) {
            std::string typeName;
            buffer.ignore(maxIgnore, '=');
            buffer >> typeName;
            if (typeName == _MeshIOAscii::groupTypeNames[VERTEX]) {
                *type = VERTEX;
            } else if (typeName == _MeshIOAscii::groupTypeNames[CELL]) {
                *type = CELL;
            } else {
                std::ostringstream msg;
                msg << "Invalid point type " << typeName << ".";
                throw std::runtime_error(msg.str());
            } // else
        } else if (0 == strcasecmp(token.c_str(), "count")) {
            buffer.ignore(maxIgnore, '=');
            buffer >> numPoints;
        } else if (0 == strcasecmp(token.c_str(), "indices")) {
            if (-1 == numPoints) {
                std::ostringstream msg;
                msg << "Tokens 'count' must precede 'indices'.";
                throw std::runtime_error(msg.str());
            } // if
            points->resize(numPoints);
            buffer.str(parser.next());
            buffer.clear();
            int i = 0;
            while (buffer.good() && i < numPoints) {
                buffer >> (*points)[i++];
                buffer >> std::ws;
                if (!buffer.good() && (i < numPoints)) {
                    buffer.str(parser.next());
                    buffer.clear();
                } // if
            } // while
            parser.ignore('}');
        } else {
            std::ostringstream msg;
            msg << "Could not parse '" << token << "' into a group setting.";
            throw std::runtime_error(msg.str());
        } // else
        buffer.str(parser.next());
        buffer.clear();
        buffer >> token;
    } // while
    if (token != "}") {
        std::ostringstream msg;
        msg << "I/O error while parsing group '" << *name << "'.";
        throw std::runtime_error(msg.str());
    } // if

    if (!_useIndexZero) {
        *points -= 1;
    }

    PYLITH_METHOD_END;
} // _readGroup


// ----------------------------------------------------------------------
// Write mesh group.
void
pylith::meshio::MeshIOAscii::_writeGroup(std::ostream& fileout,
                                         const char* name) const { // _writeGroup
    PYLITH_METHOD_BEGIN;
    PYLITH_COMPONENT_DEBUG("_writeGroup(fileout="<<typeid(fileout).name()<<", name="<<name<<")");

    int_array points;
    GroupPtType type;
    _getGroup(&points, &type, name);

    const int offset = _useIndexZero ? 0 : 1;

    const int numPoints = points.size();
    fileout
        << "  group = {\n"
        << "    name = " << name << "\n"
        << "    type = " << _MeshIOAscii::groupTypeNames[type] << "\n"
        << "    count = " << numPoints << "\n"
        << "    indices = {\n";
    for (int i = 0; i < numPoints; ++i) {
        fileout << "      " << points[i]+offset << "\n";
    }

    fileout
        << "    }\n"
        << "  }\n";

    PYLITH_METHOD_END;
} // _writeGroup


// End of file
