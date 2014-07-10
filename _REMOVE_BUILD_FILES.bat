del Project.sdf

IF EXIST "Release" (
    rmdir "Release" /s /q
)

IF EXIST "Project\Release" (
    rmdir "Project\Release" /s /q
)

IF EXIST "Debug" (
    rmdir "Debug" /s /q
)

IF EXIST "Project\Debug" (
    rmdir "Project\Debug" /s /q
)
