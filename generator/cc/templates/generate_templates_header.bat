echo. 2> %1\templates.cc

for %%f in (".\*.template") do (
  %1\tools\xxd -i %%f >> %1\templates.cc
)