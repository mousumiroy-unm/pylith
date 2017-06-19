#!/usr/bin/env python

## @file make_synth_data.py

## @brief Python application to create synthetic data from PyLith points output.

import math
import numpy
import h5py
# import pdb

from pyre.applications.Script import Script as Application

class MakeSyntheticGpsdisp(Application):
  """
  Python application to create synthetic data from PyLith points output.
  """
  
  import pyre.inventory
  ## Python object for managing MakeSyntheticGpsdisp facilities and properties.
  ##
  ## \b Properties
  ## @li \b point_input_file HDF5 input file generated by PyLith.
  ## @li \b time_step Time step to use for data generation.
  ## @li \b sigma_east Sigma value for east displacements.
  ## @li \b sigma_north Sigma value for north displacements.
  ## @li \b sigma_up Sigma value for up displacements.
  ## @li \b output_file Name of ASCII output file.
  ##

  pointInputFile = pyre.inventory.str("point_input_file", default="cascadia-cgps_points.h5")
  pointInputFile.meta['tip'] = "HDF5 point output file from PyLith."

  timeStep = pyre.inventory.int("time_step", default=0)
  timeStep.meta['tip'] = "Time step to use for data generation."

  sigmaEast = pyre.inventory.float("sigma_east", default=0.0005)
  sigmaEast.meta['tip'] = "Sigma value for East displacements."

  sigmaNorth = pyre.inventory.float("sigma_north", default=0.0005)
  sigmaNorth.meta['tip'] = "Sigma value for North displacements."

  sigmaUp = pyre.inventory.float("sigma_up", default=0.001)
  sigmaUp.meta['tip'] = "Sigma value for Up displacements."

  outputFile = pyre.inventory.str("output_file", default="cascadia-cgps_disp.txt")
  outputFile.meta['tip'] = "Name of ASCII output file."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="make_synthetic_gpsdisp"):
    Application.__init__(self, name)

    self.coords = None
    self.stations = None
    self.dispRaw = None
    self.dispNoise = None

    self.numStations = 0

    return


  def main(self):
    # pdb.set_trace()
    self._readHDF5()
    self._addNoise()
    self._writeOutput()

    return
  

  # PRIVATE METHODS /////////////////////////////////////////////////////


  def _configure(self):
    """
    Setup members using inventory.
    """
    Application._configure(self)

    return


  def _readHDF5(self):
    """
    Function to read HDF5 file from PyLith.
    """

    h5 = h5py.File(self.pointInputFile, 'r')
    self.coords = h5['geometry/vertices'][:]
    self.stations = h5['stations'][:]
    self.dispRaw = h5['vertex_fields/displacement'][self.timeStep,:,:]
    h5.close()

    self.numStations = self.coords.shape[0]

    return


  def _addNoise(self):
    """
    Function to add noise to computed displacements.
    """
    self.dispNoise = self.dispRaw.copy()
    self.dispNoise[:,0] += self.sigmaEast * numpy.random.randn(self.numStations)
    self.dispNoise[:,1] += self.sigmaNorth * numpy.random.randn(self.numStations)
    self.dispNoise[:,2] += self.sigmaUp * numpy.random.randn(self.numStations)
    return
    

  def _writeOutput(self):
    """
    Function to write output file with noisy data and uncertainties.
    """
    head = "Station\tX\tY\tZ\tUEast\tUNorth\tUUp\tSigEast\tSigNorth\tSigUp\n"
    outFmt = "%s" + 9 * "\t%g" + "\n"

    f = open(self.outputFile, 'w')
    f.write(head)

    for stationNum in range(self.numStations):
      outLine = outFmt % (self.stations[stationNum],
                          self.coords[stationNum,0], self.coords[stationNum,1],
                          self.coords[stationNum,2],
                          self.dispNoise[stationNum,0],
                          self.dispNoise[stationNum,1],
                          self.dispNoise[stationNum,2],
                          self.sigmaEast, self.sigmaNorth, self.sigmaUp)
      f.write(outLine)

    f.close()

    return


# ----------------------------------------------------------------------
if __name__ == '__main__':
  app = MakeSyntheticGpsdisp()
  app.run()

# End of file
