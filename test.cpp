#include <iostream>

#include "KVStorage.hpp"

int main(){
    FileService *fileService = new FileService();
    fileService->pushKeyFile("sagar", "test");
    fileService-> pushKeyFile("rama", "rest");
    fileService-> pushKeyFile("deva", "f");
    fileService->pushKeyFile("rumi", "du");
    fileService->pushKeyFile("dreek", "mynameisvhishalgandu");
    std::cout<<fileService->getValue("sagar")<<"\n";
    std::cout<<fileService->getValue("rama")<<"\n";
    std::cout<<fileService->getValue("deva")<<"\n";
    std::cout<<fileService->getValue("rumi")<<"\n";
    std::cout<<fileService->getValue("dreek" )<<"\n";
    fileService->popKeyFile("dreek");
    fileService->fileMetaDataMap.clear();
    fileService->getMetaData();
}