# sem7labs

Semester 7 lab stuff. 
## PADP

This is a big Cmake Project. Cmake FTW.

## CG

The CG Folder is a big MSVC 2019 Solution. 
To create a new project under the solution:
1. Set the include paths, adding:
```
$(SolutionDir)etc/freeglut/include
$(SolutionDir)etc/glew-2.2.0/include
```
2. Set library files in the linker section
Add these library search paths
```
$(SolutionDir)etc/freeglut/lib/x64
$(SolutionDir)etc/freeglut/lib/Release/x64
```
Add these library names:
```
freeglut.lib
glew32.lib
glew32s.lib
```
3. Set environment
EITHER COPY THE DDLs TO `x64/Debug`, or edit environment and add this entry:
```
PATH=$(SolutionDir)dll;%PATH%
```

