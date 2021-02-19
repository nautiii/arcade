/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** DLLoader.hpp
*/

#ifndef DLLOADER_HPP
# define DLLOADER_HPP

#include "ErrorHandling.hpp"
#include "Storage.hpp"

#include <dlfcn.h>

static const char *const CREATE_INSTANCE_FUNCT = "create";

/** 
 * \file DLLoader.hpp
 * \date March 2020
 * \version 0.1
*/

/**
 * \class DLLoader
 * \brief loading dynamic libraries thanks to libdl
*/
template<typename T>
class DLLoader {
    public:
        DLLoader<T>() noexcept;
        DLLoader<T>(const string &);
        ~DLLoader<T>() noexcept;
    public:
        const char *getPath() const noexcept;
        void setPath(const char *) noexcept;
        void load();
        void unload() noexcept;
        T   *getInstance();
        T   *next(Storage &);
        T   *prev(Storage &);
    private:
        char *path; /*!< path to dynamic library */
        void *handler; /*!<  pointer to retrive dlopen() 's return value */
        T    *(*creator)(); /*!< function pointer to retrieve dlsym() 's return value */
};

template<typename T>
DLLoader<T>::DLLoader() noexcept
    : path(nullptr), handler(nullptr), creator(nullptr)
{

}

template<typename T>
DLLoader<T>::DLLoader(const string &str) 
    : path(const_cast<char *>(str.c_str())), handler(nullptr), creator(nullptr)
{
    load();
}

template<typename T>
DLLoader<T>::~DLLoader() noexcept
{
    unload();
}

template<typename T>
const char *DLLoader<T>::getPath() const noexcept
{
    return path;
}

template<typename T>
void DLLoader<T>::setPath(const char *str) noexcept
{
    path = const_cast<char *>(str);
}

template<typename T>
void DLLoader<T>::load()
{
    handler = dlopen(path, RTLD_NOW);
    if (!handler || dlerror()) {
        err.flag = GameError::ERROPEN;
        throw err;
    }
}

template<typename T>
void DLLoader<T>::unload() noexcept
{
    if (handler)
        dlclose(handler);
}

template<typename T>
T *DLLoader<T>::getInstance()
{
    if (handler) {
        creator = reinterpret_cast<T *(*)()>(dlsym(handler, CREATE_INSTANCE_FUNCT));
        if (!creator || dlerror()) {
            err.flag = GameError::ERRSYM;
            err.sym = CREATE_INSTANCE_FUNCT;
            throw err;
        }
        return creator();
    }
    return nullptr;
}

template<typename T>
T *DLLoader<T>::next(Storage &storage)
{
    storage.index = (storage.index + 1 >= storage.dlname.size()) ? 0 : storage.index + 1;
    unload();
    path = const_cast<char *>(storage.dlname[storage.index].c_str());
    load();
    return getInstance();
}

template<typename T>
T *DLLoader<T>::prev(Storage &storage)
{
    storage.index = (storage.index <= 0) ? storage.dlname.size() - 1 : storage.index - 1;
    unload();
    path = const_cast<char *>(storage.dlname[storage.index].c_str());
    load();
    return getInstance();
}

#endif