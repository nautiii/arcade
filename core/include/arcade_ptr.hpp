/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** arcade_ptr.hpp
*/

#ifndef ARCADE_PTR_HPP
# define ARCADE_PTR_HPP

/** 
 * \file arcade_ptr.hpp
 * \date March 2020
 * \version 0.1
*/

/**
 * \class arcade_ptr
 * \brief personnal implementation of smart pointers
*/
template<typename T>
class arcade_ptr
{
    public:
        /**
        * \fn arcade_ptr<T> () noexcept
        * \brief default constructor which sets internal pointer to nullptr
        */
        arcade_ptr<T>() noexcept;
        /**
        * \fn arcade_ptr<T> (T *) noexcept
        * \brief constructor which gives ownership of pointer received in parameter to internal pointer
        * \param ptr pointer to handle
        */
        arcade_ptr<T>(T *ptr) noexcept;
        /**
        * \fn ~arcade_ptr<T> () noexcept
        * \brief default destructor which releases internal pointer
        */
        ~arcade_ptr<T>() noexcept;
    public:
        /**
        * \fn T *get() const noexcept
        * \brief getter for internal pointer
        * \return internal pointer
        */
        T *get() const noexcept;
        /**
        * \fn T *operator-> () const noexcept
        * \brief overload of -> operator
        * \return pointer to class
        */
        T *operator ->() const noexcept;
        /**
        * \fn T &operator* () const noexcept
        * \brief overload of * operator
        * \return reference to class
        */
        T &operator *() const noexcept;
    public:
        /**
        * \fn void release () noexcept
        * \brief destroy internal pointer
        */
        void release() noexcept;
        /**
        * \fn void reset (T *) noexcept
        * \brief gives ownership of pointer received in parameter to internal pointer
        * \param ptr new pointer to handle
        */
        void reset(T *ptr) noexcept;
    private:
        T *_ptr; /*!< internal pointer that will take ownership of external pointer */
};

template<typename T>
arcade_ptr<T>::arcade_ptr() noexcept
    : _ptr(nullptr)
{

}

template<typename T>
arcade_ptr<T>::arcade_ptr(T *ptr) noexcept
    : _ptr(move(ptr))
{

}

template<typename T>
arcade_ptr<T>::~arcade_ptr() noexcept
{
    if (_ptr)
        delete _ptr;
}

template<typename T>
T *arcade_ptr<T>::get() const noexcept
{
    return _ptr;
}

template<typename T>
T &arcade_ptr<T>::operator *() const noexcept
{
    return *_ptr;
}

template<typename T>
T *arcade_ptr<T>::operator ->() const noexcept
{
    return _ptr;
}

template<typename T>
void arcade_ptr<T>::release() noexcept
{
    if (_ptr)
        delete _ptr;
}

template<typename T>
void arcade_ptr<T>::reset(T *ptr) noexcept
{
    _ptr = move(ptr);
}

#endif