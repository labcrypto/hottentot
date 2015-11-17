#include <iostream>

using namespace std;
#include "../ds/hot.h"
#include "java_generator.h"
#include "fake_hot_maker.h"


int main() {
    ::naeem::hottentot::generator::GenerationConfig generationConfig;
    //::naeem::hottentot::generator::GenerationConfig generationConfig;
    generationConfig.SetOutDir("home/developer/projects/hottentot-git/generator/java-generator/genarated");
    naeem::hottentot::generator::Generator *generator = new naeem::hottentot::generator::java::JavaGenerator();
    naeem::hottentot::generator::FakeHotMaker fakeHotMaker;
    fakeHotMaker.make();
    naeem::hottentot::generator::ds::Hot* hot = fakeHotMaker.getHot();
    generator->Generate(hot , generationConfig);
    return 0;
}