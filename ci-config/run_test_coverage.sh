#!/bin/bash

# Run tests to generate coverage information. Upload test coverage data.
# Must run codecov script in top-level source directory.

SRC_DIR=`pwd`
BUILD_DIR=${SRC_DIR}/../../build/pylith

cd ${BUILD_DIR}

# ------------------------------------------------------------------------------
# libtests
# ------------------------------------------------------------------------------
make clean-coverage && make -j$(nproc) check -C tests/libtests VERBOSE=1
if [ $? != 0 ]; then exit 1; fi

make coverage-libtests.info
if [ $? != 0 ]; then exit 1; fi

if [ -r coverage-libtests.info ]; then
  pushd ${SRC_DIR} && \
      bash <(curl -s https://codecov.io/bash) -X gcov -f ${BUILD_DIR}/coverage-libtests.info -F libtests -y ci-config/codecov.yml \
	  || echo "Codecov did not collect coverage reports." && \
      popd
fi


# ------------------------------------------------------------------------------
# mmstests
# ------------------------------------------------------------------------------
make clean-coverage && make -j$(nproc) check -C tests/mmstests VERBOSE=1
if [ $? != 0 ]; then exit 1; fi

make coverage-mmstests.info
if [ $? != 0 ]; then exit 1; fi

if [ -r coverage-mmstests.info ]; then
  pushd ${SRC_DIR} && \
      bash <(curl -s https://codecov.io/bash) -X gcov -f ${BUILD_DIR}/coverage-mmstests.info -F mmstests -y ci-config/codecov.yml \
	  || echo "Codecov did not collect coverage reports." && \
      popd
fi


# ------------------------------------------------------------------------------
# pytests
# ------------------------------------------------------------------------------
make -j$(nproc) check -C tests/pytests VERBOSE=1
if [ $? != 0 ]; then exit 1; fi

make coverage-pytests.xml
if [ $? != 0 ]; then exit 1; fi

if [ -r coverage-pytests.xml ]; then
  pushd ${SRC_DIR} && \
      bash <(curl -s https://codecov.io/bash) -X gcov -f ${BUILD_DIR}/coverage-pytests.xml -F pytests -y ci-config/codecov.yml \
	  || echo "Codecov did not collect coverage reports." && \
      popd
fi


# ------------------------------------------------------------------------------
# fullscale
# ------------------------------------------------------------------------------
make clean-coverage && make -j$(nproc) check -C tests/fullscale VERBOSE=1
if [ $? != 0 ]; then exit 1; fi

make coverage-fullscale.info
if [ $? != 0 ]; then exit 1; fi

if [ -r coverage-fullscale.info ]; then
  pushd ${SRC_DIR} && \
      bash <(curl -s https://codecov.io/bash) -X gcov -f ${BUILD_DIR}/coverage-fullscale.info -F fullscale -y ci-config/codecov.yml \
	  || echo "Codecov did not collect coverage reports." && \
      popd
fi


exit 0
