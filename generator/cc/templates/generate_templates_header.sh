#!/bin/sh

echo "" > $1/templates.h
echo "#ifndef _NAEEM_HOTTENTOT_GENERATOR__TEMPLATES_H_" >> $1/templates.h
echo "#define _NAEEM_HOTTENTOT_GENERATOR__TEMPLATES_H_" >> $1/templates.h
echo "" >> $1/templates.h

for f in `find . -name "*.template"`; do
  xxd -i $f >> $1/templates.h
done

echo "#endif" >> $1/templates.h
