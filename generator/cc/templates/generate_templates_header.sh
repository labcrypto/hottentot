#!/bin/bash

echo "" > $1/templates.cc

for f in `find . -name "*.template"`; do
  xxd -i $f >> $1/templates.cc
done

echo "" > $1/templates.h

echo "#ifndef _NAEEM_HOTTENTOT_GENERATOR__TEMPLATES_H_" >> $1/templates.h
echo "#define _NAEEM_HOTTENTOT_GENERATOR__TEMPLATES_H_" >> $1/templates.h
echo "" >> $1/templates.h

SAVEIFS=$IFS
IFS=$(echo -en "\n\b")
for f in `cat $1/templates.cc | grep unsigned | cut -d'=' -f1`; do
  echo "extern $f;" >> $1/templates.h
done
IFS=$SAVEIFS

echo "" >> $1/templates.h
echo "#endif" >> $1/templates.h
