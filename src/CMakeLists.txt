cmake_minimum_required( VERSION 3.6 )

project( HDK_Project )

# CMAKE_PREFIX_PATH must contain the path to the toolkit/cmake subdirectory of
# the Houdini installation. See the "Compiling with CMake" section of the HDK
# documentation for more details, which describes several options for
# specifying this path.
list( APPEND CMAKE_PREFIX_PATH "$ENV{HFS}/toolkit/cmake" )

# Locate Houdini's libraries and header files.
# Registers an imported library target named 'Houdini'.
find_package( Houdini REQUIRED )
link_directories("$ENV{HFS}/custom/houdini/dsolib")

# Locate Boost libraries and header files.
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set( library_name SOP_Quarks )

# Add a library and its source files.
add_library( ${library_name} SHARED
    collisions/Collision.cpp
    forces/ForceFactory.cpp
    forces/NoiseForce.cpp
    forces/VDBForce.cpp
    houdini/AttribManager.cpp
    houdini/HQAdapter.cpp
    houdini/SOP_Quarks.C
    solver/ForceManager.cpp
    solver/OdeSolver.cpp
    solver/ParticleSystem.cpp
    solver/SoftBodyManager.cpp
    solver/SourceManager.cpp
    sources/SoftBodyData.cpp
    sources/SoftBodySource.cpp
    sources/SourceFactory.cpp
    sources/SphereSource.cpp
    sources/VDBSource.cpp
)

# Link against the Houdini libraries, and add required include directories and
# compile definitions.
target_link_libraries( ${library_name} Houdini openvdb_sesi ${Boost_LIBRARIES})

# Include ${CMAKE_CURRENT_BINARY_DIR} for the generated header.
target_include_directories( ${library_name} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Sets several common target properties, such as the library's output directory.
houdini_configure_target( ${library_name} )
