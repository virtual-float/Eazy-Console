/**
 * @file system.hxx
 * @brief Includes all other main header files
 * @author Krystian Turek
 * 
 * @date February 19th, 2025
 */
#pragma once
#ifndef SYSTEM_HXX_INCLUDED
#define SYSTEM_HXX_INCLUDED

#if __cplusplus >= 201703L  // Support for C++17 or latest only

#ifdef __WIN32 or __WIN64
#include "command.hxx"
#endif // Win32 and Win64 supports

#endif // C++17 or latest
#endif // SYSTEM_HXX_INCLUDEDss