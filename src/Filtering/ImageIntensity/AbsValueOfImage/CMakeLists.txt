cmake_minimum_required(VERSION 3.10.2)

project(AbsValueOfImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


if(ENABLE_QUICKVIEW)
  find_package(VTK REQUIRED
    COMPONENTS
      vtkRenderingCore
      vtkRenderingGL2PSOpenGL2
    )

  if(VTK_VERSION VERSION_LESS "8.90.0")
    include(${VTK_USE_FILE})
  endif()

  add_executable(AbsValueOfImage Code.cxx)
  target_link_libraries(AbsValueOfImage ${ITK_LIBRARIES} ${VTK_LIBRARIES})

  if(NOT VTK_VERSION VERSION_LESS "8.90.0")
    vtk_module_autoinit(
      TARGETS AbsValueOfImage
      MODULES ${VTK_LIBRARIES}
      )
  endif()
else()
  add_executable(AbsValueOfImage Code.cxx)
  target_link_libraries(AbsValueOfImage ${ITK_LIBRARIES})
endif()

install(TARGETS AbsValueOfImage
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/AbsValueOfImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME AbsValueOfImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/AbsValueOfImage)

