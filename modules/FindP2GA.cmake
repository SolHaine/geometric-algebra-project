# Find Libp2ga
#
#  P2GA_FOUND        - True if Libp2ga found.
#  P2GA_INCLUDE_DIRS - where to find Libp2ga include files
#  P2GA_LIBRARIES    - where to find Libp2ga binary libraries


# find include path
find_path (P2GA_INCLUDE_DIR 
		NAMES p2ga
		HINTS /usr/local/include)

# find library file
find_library (P2GA_LIBRARY 
		NAMES p2ga
		HINTS /usr/local/lib/ )


set(P2GA_LIBRARIES ${P2GA_LIBRARY})
set(P2GA_INCLUDE_DIRS ${P2GA_INCLUDE_DIR})

# handle the QUIETLY and REQUIRED arguments and set P2GA_FOUND to TRUE if
# all listed variables are TRUE
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (P2GA DEFAULT_MSG 
                                   P2GA_LIBRARIES P2GA_INCLUDE_DIRS)

mark_as_advanced(P2GA_INCLUDE_DIR P2GA_LIBRARIE)





