rm -rf ./gen/hotgen
rm -rf ./prj/src/ir/ntnaeem/hottentot/examples/listtest/hotgen
hot --java --out ./gen services.hot
hot --java --out ./prj/src/ir/ntnaeem/hottentot/examples/listtest services.hot