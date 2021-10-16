#include <iostream>
#include <string>
#include <fstream>


struct KVServerConfig {
    enum CacheReplacementType {
        LRU,
        LFU
    };

    int port;
    int thread_size;
    int cache_size;
    enum CacheReplacementType replacementType;

    /**
     * Reads content from the KVServer.conf and initialize the values.
     */
    KVServerConfig(std::string fileName) {

        std::fstream file;
        file.open(fileName, std::ios::in);
        std::string key;
        int32_t val;

        while ((not file.eof()) && file.is_open()) {
            file >> key >> val;
            if (key == "LISTENING_PORT") port = val;
            else if (key == "THREAD_POOL_SIZE") thread_size = val;
            else if (key == "CACHE_SIZE") cache_size = val;
        }
        replacementType = LRU;
        port = 8081;
        thread_size=10;
        cache_size=100;

        file.close();
    }
};