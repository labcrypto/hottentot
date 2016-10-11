echo. 2> %1\templates.cc

for %%f in (".\*.template") do (
  %1\tools\xxd -i %%f >> %1\templates.cc
)

echo. 2> %1\templates.h

echo #ifndef _NAEEM_HOTTENTOT_GENERATOR__TEMPLATES_H_ >> %1/templates.h
echo #define _NAEEM_HOTTENTOT_GENERATOR__TEMPLATES_H_ >> %1/templates.h
echo. >> %1/templates.h

for /F "delims==" %%f in ('type templates.cc ^| find "unsigned"') do (
  echo extern %%f; >> %1/templates.h
)

echo. >> %1/templates.h
echo #endif >> %1/templates.h