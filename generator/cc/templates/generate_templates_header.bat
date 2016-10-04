echo. 2> %1\templates.cc

for %%f in ("%1\*.template") do (
  d:\xxd -i %%f >> %1\templates.cc
)