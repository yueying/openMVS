if(MSVC)
	FILE(GLOB LIBRARY_FILES_C "*.cpp" "*.rc")
else()
	FILE(GLOB LIBRARY_FILES_C "*.cpp")
endif()
FILE(GLOB LIBRARY_FILES_H "*.h" "*.inl")

cxx_executable_with_flags_no_pch(InterfacePhotoScan "Apps" "${cxx_default}" "${LIBS_DEPEND}" ${LIBRARY_FILES_C} ${LIBRARY_FILES_H})

if(OpenMVS_USE_BREAKPAD AND BREAKPAD_FOUND)
	target_link_libraries(InterfacePhotoScan ${BREAKPAD_LIBS})
endif()
