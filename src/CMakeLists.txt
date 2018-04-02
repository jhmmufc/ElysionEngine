set(SRC
	include/ECSDefines.hpp
    include/Component.hpp
    include/Entity.hpp
    include/EntityManager.hpp
    include/Colour.hpp
    include/Maths/Maths.hpp
    include/Maths/Vector2.hpp
    include/Maths/Vector3.hpp
    include/Maths/Vector4.hpp
    Component.cpp
    Entity.cpp
    EntityManager.cpp)
    
add_library(elysion_engine ${SRC})

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(elysion_engine PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS elysion_engine EXPORT ElysionEngineConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT ElysionEngineConfig DESTINATION share/elysion_engine/cmake)

# This makes the project importable from the build directory
export(TARGETS elysion_engine FILE ElysionEngineConfig.cmake)