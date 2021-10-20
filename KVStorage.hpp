#include <iostream>
#include <bits/stdc++.h>
#include <sys/types.h>
#include <unordered_map>
#include <string.h>

#define FILECOUNT 30
#define CONF_FILE_PATH "../../KVServer.conf"
#define CLIENT_FILE_PATH "../KVClient.conf"
#define SIZE 256

class FileMetaData {
public:
    bool deleted;
    unsigned long offset;
    char key[SIZE];
    int val_size;
};

class FileService {
public:
    std::unordered_map<std::string, FileMetaData> fileMetaDataMap;

    FileService() {
        fileMetaDataMap = std::unordered_map<std::string, FileMetaData>();
    }

/**
 * Performs the hashing to get the file path.
 * @param key
 * @return file path
 *
 * @ref
 * https://stackoverflow.com/questions/7666509/hash-function-for-string
 */
    std::string getFilePath(std::string key) {
        int32_t hash = 0;
        for (auto c: key) {
            hash += c;
        }
        hash %= FILECOUNT;
        return std::to_string(hash) + ".txt";
    }


    void writeToFile(std::string path, std::string line) {
        std::fstream file;
        file.open(path, std::ios::out);
        if (file.is_open()) {
            file << line;
            file.close();
        }
    }

/**
 * Read the value from the file.
 * @param key
 * @return
 *
 */
    std::string getValue(std::string key) {
        if (fileMetaDataMap.find(key) != fileMetaDataMap.end()) {
            if (!fileMetaDataMap[key].deleted) {
                char *path = new char[SIZE];
                char *value = new char[SIZE];
                strcpy(path, getFilePath(key).c_str());
                FILE *fp;
                fp = fopen(path, "r");
                if (nullptr == fp) {
                    return "";
                }
                fseek(fp, fileMetaDataMap[key].offset, SEEK_SET);
                fread(value, fileMetaDataMap[key].val_size, 1, fp);
                value[fileMetaDataMap[key].val_size] = '\0';
                return value;
            } else {
                return "";
            }
        } else {
            return "";
        }
    }

    int pushKeyFile(std::string key, std::string value) {
        FILE *fp;
        char *path = new char[SIZE];
        strcpy(path, getFilePath(key).c_str());
        char *k = new char[SIZE];
        char *v = new char[SIZE];
        strcpy(k, key.c_str());
        strcpy(v, value.c_str());


        fp = fopen(path, "a+");
        if (fp != NULL) {
            if (fileMetaDataMap.find(key) == fileMetaDataMap.end()) {
                fwrite(k, 1, strlen(k), fp);
                unsigned long offset = ftell(fp);
                FileMetaData fileMetaData;
                fileMetaData.offset = offset;
                fileMetaData.val_size = strlen(value.c_str());
                strcpy(fileMetaData.key, k);
                fileMetaData.deleted = false;
                fileMetaDataMap[key] = fileMetaData;
                fwrite(v, 1, strlen(value.c_str()), fp);

            } else {
                fwrite(k, 1, strlen(k), fp);
                unsigned long offset = ftell(fp);
                fileMetaDataMap[key].offset = offset;
                fileMetaDataMap[key].val_size = strlen(value.c_str());
                std::cout << strlen(value.c_str());
                fwrite(v, 1, strlen(value.c_str()), fp);
            }
            fflush(fp);
            fclose(fp);
            return 1;
        }
        fflush(fp);
        fclose(fp);
        return 0;
    }

    int popKeyFile(std::string key) {
        if (fileMetaDataMap.find(key) != fileMetaDataMap.end() && !fileMetaDataMap[key].deleted) {
            fileMetaDataMap[key].deleted = true;
            return 1;
        } else {
            return 0;
        }
    }

    std::map<std::string, int> getConfig() {
        std::map<std::string, int> config = std::map<std::string, int>();
        std::fstream file;

        file.open(CONF_FILE_PATH, std::ios::in);
        if (file.is_open()) {
            std::string line, file_key, file_value;
            while (getline(file, line)) {
                std::stringstream stream(line);
                getline(stream, file_key, ' ');
                getline(stream, file_value);
                std::stringstream ss(file_value);
                int val = 0;
                if (file_key == "CACHE_REPLACEMENT_TYPE") {
                    if (file_value == "LRU") {
                        val = 1;
                    } else {
                        val = 2;
                    }
                } else {
                    ss >> val;
                }
                config[file_key] = val;

            }
            file.close();
        }
        return config;
    }


    std::vector<std::vector<std::string>> getClientConfig() {
        std::vector<std::vector<std::string>> file_commands = std::vector<std::vector<std::string>>();
        std::fstream file;
        file.open(CLIENT_FILE_PATH, std::ios::in);
        std::string line, file_key, file_value, file_command;

        while (getline(file, line)) {
            std::vector<std::string> command = std::vector<std::string>();
            std::stringstream stream(line);
            getline(stream, file_command, ' ');
            getline(stream, file_key, ' ');
            getline(stream, file_value);
            command.emplace_back(file_command);
            command.emplace_back(file_key);
            command.emplace_back(file_value);
            file_commands.emplace_back(command);
        }
        file.close();
        return file_commands;
    }

};

