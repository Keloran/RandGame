SET(_nordicos_HEADER_SEARCH_DIRS "./NordicOS/" "../NordicOS")
SET(_nordicos_ENV_ROOT_DIR "$ENV{NORDICOS_ROOT_DIR}")

IF(NOT NORDICOS_ROOT_DIR AND _nordicos_ENV_ROOT_DIR)
    SET(NORDICOS_ROOT_DIR "${_NORDICOS_ENV_ROOT_DIR}")
ENDIF(NOT NORDICOS_ROOT_DIR AND _nordicos_ENV_ROOT_DIR)

IF(NORDICOS_ROOT_DIR)
    SET(_nordicos_HEADER_SEARCH_DIRS "${NORDICOS_ROOT_DIR}" "${NORDICOS_ROOT_DIR}/NordicOS" ${_nordicos_HEADER_SEARCH_DIRS})
ENDIF(NORDICOS_ROOT_DIR)

FIND_PATH(NORDICOS_INCLUDE_DIR "os.hpp" PATHS ${_nordicos_HEADER_SEARCH_DIRS})

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(NORDICOS DEFAULT_MSG NORDICOS_INCLUDE_DIR)

IF (NORDICOS_FOUND)
    SET(NORDICOS_INCLUDE_DIRS "${NORDICOS_INCLUDE_DIR}")
    SET(NORDICOS_LIBRARY_DIRS "${NORDICOS_INCLUDE_DIR}")
    SET(NORDICOS_LIBRARY_DIR  "${NORDICOS_LIBRARY_DIRS}")

    MESSAGE(STATUS "NORDICOS_INCLUDE_DIR = ${NORDICOS_INCLUDE_DIR}")
ENDIF(NORDICOS_FOUND)
