echo > %1\templates.cc

for %%i in (%1\*.template) do (
  echo %%i
)