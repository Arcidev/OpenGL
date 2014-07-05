del Project.sdf

IF EXIST "Release" (
    rmdir "Release" /s /q
)

IF EXIST "Project\Release" (
    rmdir "Project\Release" /s /q
)
