#include <iostream>
#include <utility>
#include <string.h>
#include <map>


#include "Node.hpp"

/**
 * LRU Cache with size, capacity and hashMap that holds the list of multiple key cache list.
 *
 *
 * @ref:
 * https://tech.ebayinc.com/engineering/high-throughput-thread-safe-lru-caching/
 */

using namespace std;

class LRUCache {
private:
    int size;
    int capacity;
    int policy_type;
    List *list;
    unordered_map<string, Node*> cacheHashMap;


public:
    unordered_map<string, Node*> getMap(){
        return cacheHashMap;
    }

    void setMap( const unordered_map<string, Node*> map){
         cacheHashMap = map;
    }

    LRUCache(int cap) {
        size = 0;
        list = new List();
        cacheHashMap = unordered_map<string, Node *>();
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
    string get(string key) {
        if (cacheHashMap.find(key) == cacheHashMap.end()) {
//            string value = getValueFromFile(key);
            string value = "";
            if (value.empty()) {
                return "key not found";
            } else {
                put(key, value);
                return value;
            }
        } else {
            string val = cacheHashMap[key]->value;
            list->pop_push_front(cacheHashMap[key]);
            return  val;
        }
    }


    /**
     * Insert new value to the cachemap.
     * @param key
     * @param value
     * @return
     */
    string put(string key, string value) {
        if (cacheHashMap.find(key) != cacheHashMap.end()) {
            cacheHashMap[key]->dirty_type = 2;
            cacheHashMap[key]->value = value;
            list->pop_push_front(cacheHashMap[key]);
            return "update successfully!!:value" +value;
        }

        if(size == capacity){
           cacheHashMap.erase(list->last()->key);
           list->remove_last();
           size--;
        }

        Node *node= list->push_front(key, value);
//        putKVFile(key, value);
        size++;
        node->dirty_type=1;
        cacheHashMap[key] = node;
        return "successfully added" + value;
    }

    string del(string key){
        if(cacheHashMap.find(key) != cacheHashMap.end()){
            list->remove(cacheHashMap[key]);
            cacheHashMap.erase(key);

            size --;

//            int val = delFromFile(key);
            return "successfully deleted"+ key;
        } //else{
//            int val = delFromFile(key);
//            if(val){
//                return "successfully deleted"+ key;
//            }
//            else{
//                return "key not found";
//            }
//        }
        else
            return "Not Found";
    }
};

