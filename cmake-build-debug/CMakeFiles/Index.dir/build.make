# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.1.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.1.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\lukax\source\ide\clion\Index

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\lukax\source\ide\clion\Index\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\Index.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\Index.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\Index.dir\flags.make

CMakeFiles\Index.dir\main.cc.obj: CMakeFiles\Index.dir\flags.make
CMakeFiles\Index.dir\main.cc.obj: ..\main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\lukax\source\ide\clion\Index\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Index.dir/main.cc.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Index.dir\main.cc.obj /FdCMakeFiles\Index.dir\ /FS -c C:\Users\lukax\source\ide\clion\Index\main.cc
<<

CMakeFiles\Index.dir\main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Index.dir/main.cc.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe > CMakeFiles\Index.dir\main.cc.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\lukax\source\ide\clion\Index\main.cc
<<

CMakeFiles\Index.dir\main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Index.dir/main.cc.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Index.dir\main.cc.s /c C:\Users\lukax\source\ide\clion\Index\main.cc
<<

CMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\macros\index_macros.cc.obj: CMakeFiles\Index.dir\flags.make
CMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\macros\index_macros.cc.obj: ..\Index\Include\Include_Index\index_impl\macros\index_macros.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\lukax\source\ide\clion\Index\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Index.dir/Index/Include/Include_Index/index_impl/macros/index_macros.cc.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\macros\index_macros.cc.obj /FdCMakeFiles\Index.dir\ /FS -c C:\Users\lukax\source\ide\clion\Index\Index\Include\Include_Index\index_impl\macros\index_macros.cc
<<

CMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\macros\index_macros.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Index.dir/Index/Include/Include_Index/index_impl/macros/index_macros.cc.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe > CMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\macros\index_macros.cc.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\lukax\source\ide\clion\Index\Index\Include\Include_Index\index_impl\macros\index_macros.cc
<<

CMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\macros\index_macros.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Index.dir/Index/Include/Include_Index/index_impl/macros/index_macros.cc.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\macros\index_macros.cc.s /c C:\Users\lukax\source\ide\clion\Index\Index\Include\Include_Index\index_impl\macros\index_macros.cc
<<

CMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\macros\index_macros_end.cc.obj: CMakeFiles\Index.dir\flags.make
CMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\macros\index_macros_end.cc.obj: ..\Index\Include\Include_Index\index_impl\macros\index_macros_end.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\lukax\source\ide\clion\Index\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Index.dir/Index/Include/Include_Index/index_impl/macros/index_macros_end.cc.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\macros\index_macros_end.cc.obj /FdCMakeFiles\Index.dir\ /FS -c C:\Users\lukax\source\ide\clion\Index\Index\Include\Include_Index\index_impl\macros\index_macros_end.cc
<<

CMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\macros\index_macros_end.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Index.dir/Index/Include/Include_Index/index_impl/macros/index_macros_end.cc.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe > CMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\macros\index_macros_end.cc.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\lukax\source\ide\clion\Index\Index\Include\Include_Index\index_impl\macros\index_macros_end.cc
<<

CMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\macros\index_macros_end.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Index.dir/Index/Include/Include_Index/index_impl/macros/index_macros_end.cc.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\macros\index_macros_end.cc.s /c C:\Users\lukax\source\ide\clion\Index\Index\Include\Include_Index\index_impl\macros\index_macros_end.cc
<<

CMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\ui\include.cc.obj: CMakeFiles\Index.dir\flags.make
CMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\ui\include.cc.obj: ..\Index\Include\Include_Index\index_impl\ui\include.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\lukax\source\ide\clion\Index\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Index.dir/Index/Include/Include_Index/index_impl/ui/include.cc.obj"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\ui\include.cc.obj /FdCMakeFiles\Index.dir\ /FS -c C:\Users\lukax\source\ide\clion\Index\Index\Include\Include_Index\index_impl\ui\include.cc
<<

CMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\ui\include.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Index.dir/Index/Include/Include_Index/index_impl/ui/include.cc.i"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe > CMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\ui\include.cc.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\lukax\source\ide\clion\Index\Index\Include\Include_Index\index_impl\ui\include.cc
<<

CMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\ui\include.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Index.dir/Index/Include/Include_Index/index_impl/ui/include.cc.s"
	C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\ui\include.cc.s /c C:\Users\lukax\source\ide\clion\Index\Index\Include\Include_Index\index_impl\ui\include.cc
<<

# Object files for target Index
Index_OBJECTS = \
"CMakeFiles\Index.dir\main.cc.obj" \
"CMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\macros\index_macros.cc.obj" \
"CMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\macros\index_macros_end.cc.obj" \
"CMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\ui\include.cc.obj"

# External object files for target Index
Index_EXTERNAL_OBJECTS =

Index.exe: CMakeFiles\Index.dir\main.cc.obj
Index.exe: CMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\macros\index_macros.cc.obj
Index.exe: CMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\macros\index_macros_end.cc.obj
Index.exe: CMakeFiles\Index.dir\Index\Include\Include_Index\index_impl\ui\include.cc.obj
Index.exe: CMakeFiles\Index.dir\build.make
Index.exe: Index\Include\Include_Index\IndexInclude.lib
Index.exe: CMakeFiles\Index.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\lukax\source\ide\clion\Index\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable Index.exe"
	"C:\Program Files\JetBrains\CLion 2021.1.1\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\Index.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\mt.exe --manifests -- C:\PROGRA~2\MICROS~2\2019\COMMUN~1\VC\Tools\MSVC\1429~1.300\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\Index.dir\objects1.rsp @<<
 /out:Index.exe /implib:Index.lib /pdb:C:\Users\lukax\source\ide\clion\Index\cmake-build-debug\Index.pdb /version:0.0 /machine:X86 /debug /INCREMENTAL /subsystem:console  Index\Include\Include_Index\IndexInclude.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\Index.dir\build: Index.exe

.PHONY : CMakeFiles\Index.dir\build

CMakeFiles\Index.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Index.dir\cmake_clean.cmake
.PHONY : CMakeFiles\Index.dir\clean

CMakeFiles\Index.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\lukax\source\ide\clion\Index C:\Users\lukax\source\ide\clion\Index C:\Users\lukax\source\ide\clion\Index\cmake-build-debug C:\Users\lukax\source\ide\clion\Index\cmake-build-debug C:\Users\lukax\source\ide\clion\Index\cmake-build-debug\CMakeFiles\Index.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\Index.dir\depend

