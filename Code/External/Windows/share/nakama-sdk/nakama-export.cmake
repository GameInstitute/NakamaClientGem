# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.8)
   message(FATAL_ERROR "CMake >= 2.8.0 required")
endif()
if(CMAKE_VERSION VERSION_LESS "3.0.0")
   message(FATAL_ERROR "CMake >= 3.0.0 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 3.0.0...3.27)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_cmake_targets_defined "")
set(_cmake_targets_not_defined "")
set(_cmake_expected_targets "")
foreach(_cmake_expected_target IN ITEMS nakama-sdk nakama-sdk-interface nakama-api-proto nakama-impl-http-libcurl nakama-impl-ws-wslay nakama-sdk-core-misc nakama-sdk-core-rest nakama-sdk-core-rt nakama-sdk-core-common nakama-sdk-client-factory nakama-sdk-rtclient-factory)
  list(APPEND _cmake_expected_targets "${_cmake_expected_target}")
  if(TARGET "${_cmake_expected_target}")
    list(APPEND _cmake_targets_defined "${_cmake_expected_target}")
  else()
    list(APPEND _cmake_targets_not_defined "${_cmake_expected_target}")
  endif()
endforeach()
unset(_cmake_expected_target)
if(_cmake_targets_defined STREQUAL _cmake_expected_targets)
  unset(_cmake_targets_defined)
  unset(_cmake_targets_not_defined)
  unset(_cmake_expected_targets)
  unset(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT _cmake_targets_defined STREQUAL "")
  string(REPLACE ";" ", " _cmake_targets_defined_text "${_cmake_targets_defined}")
  string(REPLACE ";" ", " _cmake_targets_not_defined_text "${_cmake_targets_not_defined}")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_cmake_targets_defined_text}\nTargets not yet defined: ${_cmake_targets_not_defined_text}\n")
endif()
unset(_cmake_targets_defined)
unset(_cmake_targets_not_defined)
unset(_cmake_expected_targets)


# Compute the installation prefix relative to this file.
get_filename_component(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
if(_IMPORT_PREFIX STREQUAL "/")
  set(_IMPORT_PREFIX "")
endif()

# Create imported target nakama-sdk
add_library(nakama-sdk SHARED IMPORTED)

set_target_properties(nakama-sdk PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
  INTERFACE_LINK_LIBRARIES "nakama-sdk-interface"
)

# Create imported target nakama-sdk-interface
add_library(nakama-sdk-interface INTERFACE IMPORTED)

set_target_properties(nakama-sdk-interface PROPERTIES
  INTERFACE_COMPILE_DEFINITIONS "optional_CONFIG_SELECT_OPTIONAL=optional_OPTIONAL_NONSTD"
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include;${_IMPORT_PREFIX}/include"
  INTERFACE_LINK_LIBRARIES "nonstd::optional-lite"
)

if(NOT CMAKE_VERSION VERSION_LESS "3.23.0")
  target_sources(nakama-sdk-interface
    INTERFACE
      FILE_SET "HEADERS"
      TYPE "HEADERS"
      BASE_DIRS "${_IMPORT_PREFIX}/include"
      FILES "${_IMPORT_PREFIX}/include/nakama-cpp/config.h" "${_IMPORT_PREFIX}/include/nakama-cpp/ClientFactory.h" "${_IMPORT_PREFIX}/include/nakama-cpp/NClientInterface.h" "${_IMPORT_PREFIX}/include/nakama-cpp/NError.h" "${_IMPORT_PREFIX}/include/nakama-cpp/NException.h" "${_IMPORT_PREFIX}/include/nakama-cpp/NExport.h" "${_IMPORT_PREFIX}/include/nakama-cpp/NHttpTransportInterface.h" "${_IMPORT_PREFIX}/include/nakama-cpp/NPlatformParams.h" "${_IMPORT_PREFIX}/include/nakama-cpp/NSessionInterface.h" "${_IMPORT_PREFIX}/include/nakama-cpp/NTypes.h" "${_IMPORT_PREFIX}/include/nakama-cpp/NUtils.h" "${_IMPORT_PREFIX}/include/nakama-cpp/Nakama.h" "${_IMPORT_PREFIX}/include/nakama-cpp/NakamaVersion.h" "${_IMPORT_PREFIX}/include/nakama-cpp/URLParts.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data" "${_IMPORT_PREFIX}/include/nakama-cpp/log" "${_IMPORT_PREFIX}/include/nakama-cpp/realtime" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NAccount.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NAccountDevice.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NChannelMessage.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NChannelMessageList.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NFriend.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NFriendList.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NGroup.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NGroupList.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NGroupUser.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NGroupUserList.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NLeaderboardRecord.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NLeaderboardRecordList.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NMatch.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NMatchList.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NNotification.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NNotificationList.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NRpc.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NStorageObject.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NStorageObjectAck.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NStorageObjectId.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NStorageObjectList.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NStorageObjectWrite.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NStoragePermissions.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NTournament.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NTournamentList.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NTournamentRecordList.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NUser.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NUserGroup.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NUserGroupList.h" "${_IMPORT_PREFIX}/include/nakama-cpp/data/NUsers.h"
  )
else()
  set_property(TARGET nakama-sdk-interface
    APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
      "${_IMPORT_PREFIX}/include"
  )
endif()

# Create imported target nakama-api-proto
add_library(nakama-api-proto INTERFACE IMPORTED)

set_target_properties(nakama-api-proto PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include;${_IMPORT_PREFIX}/include"
  INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:protobuf::libprotobuf>"
)

# Create imported target nakama-impl-http-libcurl
add_library(nakama-impl-http-libcurl INTERFACE IMPORTED)

set_target_properties(nakama-impl-http-libcurl PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
  INTERFACE_LINK_LIBRARIES "nakama-api-proto;nakama-sdk-interface"
)

# Create imported target nakama-impl-ws-wslay
add_library(nakama-impl-ws-wslay INTERFACE IMPORTED)

set_target_properties(nakama-impl-ws-wslay PROPERTIES
  INTERFACE_COMPILE_DEFINITIONS "WSLAY_NETIO_"
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include;${_IMPORT_PREFIX}/include"
  INTERFACE_LINK_LIBRARIES "nakama-api-proto;nakama-sdk-interface;nakama-sdk-core-common;nakama-sdk-core-misc;wslay"
)

# Create imported target nakama-sdk-core-misc
add_library(nakama-sdk-core-misc INTERFACE IMPORTED)

set_target_properties(nakama-sdk-core-misc PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
  INTERFACE_LINK_LIBRARIES "nakama-sdk-interface"
)

# Create imported target nakama-sdk-core-rest
add_library(nakama-sdk-core-rest INTERFACE IMPORTED)

set_target_properties(nakama-sdk-core-rest PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
  INTERFACE_LINK_LIBRARIES "nakama-sdk-interface;\$<LINK_ONLY:rapidjson>;\$<LINK_ONLY:nakama-sdk-core-common>;\$<LINK_ONLY:nakama-sdk-core-rt>;nakama-sdk-core-rt;factory"
)

# Create imported target nakama-sdk-core-rt
add_library(nakama-sdk-core-rt INTERFACE IMPORTED)

set_target_properties(nakama-sdk-core-rt PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
  INTERFACE_LINK_LIBRARIES "nakama-sdk-interface;nakama-api-proto;nakama-sdk-core-common;\$<LINK_ONLY:nakama-sdk-rtclient-factory>"
)

# Create imported target nakama-sdk-core-common
add_library(nakama-sdk-core-common INTERFACE IMPORTED)

set_target_properties(nakama-sdk-core-common PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include;${_IMPORT_PREFIX}/include"
  INTERFACE_LINK_LIBRARIES "nakama-sdk-interface;nakama-api-proto;\$<\$<TARGET_EXISTS:nakama::grpc-proto>:nakama::grpc-proto>;\$<LINK_ONLY:protobuf::libprotobuf>"
)

# Create imported target nakama-sdk-client-factory
add_library(nakama-sdk-client-factory INTERFACE IMPORTED)

set_target_properties(nakama-sdk-client-factory PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
  INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:nakama-sdk-core-rest>;\$<LINK_ONLY:nakama-sdk-core-grpc>;\$<LINK_ONLY:nakama-impl-http-libcurl>"
)

# Create imported target nakama-sdk-rtclient-factory
add_library(nakama-sdk-rtclient-factory INTERFACE IMPORTED)

set_target_properties(nakama-sdk-rtclient-factory PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
  INTERFACE_LINK_LIBRARIES "nakama-sdk-interface;\$<LINK_ONLY:nakama-impl-ws-wslay>"
)

# Load information for each installed configuration.
file(GLOB _cmake_config_files "${CMAKE_CURRENT_LIST_DIR}/nakama-export-*.cmake")
foreach(_cmake_config_file IN LISTS _cmake_config_files)
  include("${_cmake_config_file}")
endforeach()
unset(_cmake_config_file)
unset(_cmake_config_files)

# Cleanup temporary variables.
set(_IMPORT_PREFIX)

# Loop over all imported files and verify that they actually exist
foreach(_cmake_target IN LISTS _cmake_import_check_targets)
  if(CMAKE_VERSION VERSION_LESS "3.28"
      OR NOT DEFINED _cmake_import_check_xcframework_for_${_cmake_target}
      OR NOT IS_DIRECTORY "${_cmake_import_check_xcframework_for_${_cmake_target}}")
    foreach(_cmake_file IN LISTS "_cmake_import_check_files_for_${_cmake_target}")
      if(NOT EXISTS "${_cmake_file}")
        message(FATAL_ERROR "The imported target \"${_cmake_target}\" references the file
   \"${_cmake_file}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
      endif()
    endforeach()
  endif()
  unset(_cmake_file)
  unset("_cmake_import_check_files_for_${_cmake_target}")
endforeach()
unset(_cmake_target)
unset(_cmake_import_check_targets)

# This file does not depend on other imported targets which have
# been exported from the same project but in a separate export set.

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
