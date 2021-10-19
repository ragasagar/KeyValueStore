#include <iostream>
#include <utility>
#include <string.h>
#include <map>


#include "Node.hpp"
#include "../KVStorage.hpp"
#include "../logs/colorlog.hpp"

/**
 * LRU Cache with size, capacity and hashMap that holds the list of multiple key cache list.
 *
 *
 * @ref:
 * https://tech.ebayinc.com/engineering/high-throughput-thread-safe-lru-caching/
 */

using namespace std;

class Cache {
public:
    int size;
    int capacity;
    List *list;
    unordered_map<string, Node *> cacheHashMap;
    FileService *fileService;
    unique_lock<mutex> cache_mutex;

    virtual string get(string key) = 0;

    virtual string put(string key, string value) = 0;

    virtual string del(string key) = 0;
};

class LRUCache final : public Cache {
public:
    LRUCache(int cap) {
        size = 0;
        list = new List();
        cacheHashMap = unordered_map<string, Node *>();
        fileService = new FileService();
        capacity = cap;
    }

    /**
     * Get the value for the given key.
     * @param key
     * @return
     *
     * @ref:
     * *  https://www.geeksforgeeks.org/check-key-present-cpp-map-unordered_map/
     */
    string get(string key) override {
        INFO("LRUCache", "fetching value for key:" + key);
        cache_mutex.lock();
        if (cacheHashMap.find(key) == cacheHashMap.end()) {
            string value = fileService->getValue(key);
            if (value.empty()) {
                cache_mutex.unlock();
                ERROR("LRUCache", "key not found:" + key);
                return "key not found";
            } else {
                add(key, value);
                cache_mutex.unlock();
                return value;
            }
        } else {
            string val = cacheHashMap[key]->value;
            INFO("LRUCache", "Shifting node to front for key:" + key);
            list->pop_push_front(cacheHashMap[key]);
            cache_mutex.unlock();
            return val;

        }
    }


    /**
     * Insert new value to the cachemap.
     * @param key
     * @param value
     * @return
     */
    string put(string key, string value) override {
        cache_mutex.lock();
        if (cacheHashMap.find(key) != cacheHashMap.end()) {
            cacheHashMap[key]->dirty_type = 2;
            cacheHashMap[key]->value = value;
            list->pop_push_front(cacheHashMap[key]);
            INFO("LRUCache", "Shifting node to front for key:" + key);
            fileService->pushKeyFile(key, value);
            INFO("LRUCache", "update successfully!!:" + value);
            cache_mutex.unlock();
            return "update successfully!!:value" + value;
        }

        add(key,value);
        INFO("LRUCache", "added successfully!!:value" + value);
        cache_mutex.unlock();
        return "successfully added" + value;
    }

    string del(string key) override {
        cache_mutex.lock();
        if (cacheHashMap.find(key) != cacheHashMap.end()) {
            list->remove(cacheHashMap[key]);
            cacheHashMap.erase(key);

            size--;


            fileService->popKeyFile(key);
            INFO("LRUCache", "successfully deleted for key:" + key);
            cache_mutex.unlock();
            return "successfully deleted for key: " + key;
        } else {
            int val = fileService->popKeyFile(key);
            if (val) {
                INFO("LRUCache", "successfully deleted for key:" + key);
                cache_mutex.unlock();
                return "successfully deleted" + key;
            } else {
                ERROR("LRUCache", "key not found:" + key);
                cache_mutex.unlock();
                return "key not found";
            }
        }
    }
private:
    void add(std::string key, std::string value){
        if (size == capacity) {
            cacheHashMap.erase(list->last()->key);
            list->remove_last();
            size--;
        }

        Node *node = list->push_front(key, value);
        fileService->pushKeyFile(key, value);
        size++;
        node->dirty_type = 1;
        cacheHashMap[key] = node;
    }
};

class LFUCache final : public Cache {
public:
    LFUCache(int cap) {
        size = 0;
        list = new List();
        cacheHashMap = unordered_map<string, Node *>();
        capacity = cap;
        fileService = new FileService();
        unique_lock<mutex> cache_mutex;
    }

    /**
     * Get the value for the given key.
     * @param key
     * @return
     *
     * @ref:
     * *  https://www.geeksforgeeks.org/check-key-present-cpp-map-unordered_map/
     */
    string get(string key) override {
        cache_mutex.lock();
        if (cacheHashMap.find(key) == cacheHashMap.end()) {
            string value = fileService->getValue(key);
            if (value.empty()) {
                ERROR("LFUCache", "key not found:" + key);
                cache_mutex.unlock();
                return "key not found";
            } else {
                put(key, value);
                cache_mutex.unlock();
                return value;
            }
        } else {
            Node *res = cacheHashMap[key];
            res->frequency++;
            INFO("LFUCache", "Shifting node.. for key:" + key);
            list->shift(res);
            cache_mutex.unlock();
            return res->value;
        }
    }


    /**
     * Insert new value to the cachemap.
     * @param key
     * @param value
     * @return
     */
    string put(string key, string value) override {
        cache_mutex.lock();
        if (cacheHashMap.find(key) != cacheHashMap.end()) {
            Node *res = cacheHashMap[key];
            cacheHashMap[key]->dirty_type = 2;
            cacheHashMap[key]->value = value;
            res->frequency++;
            INFO("LFUCache", "Shifting node.. for key:" + key);
            list->shift(res);
            INFO("LFUCache", "update successfully!!:" + value);
            cache_mutex.unlock();
            return "update successfully!!:value" + value;
        }

        if (size == capacity) {
            cacheHashMap.erase(list->last()->key);
            list->remove_last();
            size--;
        }

        Node *node = list->push_rear(key, value);
        fileService->pushKeyFile(key, value);
        size++;
        node->dirty_type = 1;
        cacheHashMap[key] = node;
        INFO("LFUCache", "added successfully!!:value" + value);
        cache_mutex.unlock();
        return "successfully added" + value;
    }

    string del(string key) override {
        cache_mutex.lock();
        if (cacheHashMap.find(key) != cacheHashMap.end()) {
            list->remove(cacheHashMap[key]);
            cacheHashMap.erase(key);

            size--;

            fileService->popKeyFile(key);
            INFO("LFUCache", "successfully deleted for key:" + key);
            cache_mutex.unlock();
            return "successfully deleted: " + key;
        } else {
            int val = fileService->popKeyFile(key);
            if (val) {
                INFO("LFUCache", "successfully deleted for key:" + key);
                cache_mutex.unlock();
                return "successfully deleted: " + key;
            } else {
                ERROR("LFUCache", "key not found:" + key);
                cache_mutex.unlock();
                return "key not found";
            }
        }

    }
};