/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */

/*

  Author(s): Peter Kazanzides
  Created on: 2007-01-16 

  (C) Copyright 2007-2007 Johns Hopkins University (JHU), All Rights
  Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---
*/

#include <string>

#include <cisstCommon/cmnPortability.h>
#include <cisstCommon/cmnLogger.h>
#include <cisstOSAbstraction/osaDynamicLoader.h>

const char UNIX_SEP = '/';  // path separator for UNIX
const char DOS_SEP = '\\';  // path separator for DOS/Windows

#if (CISST_OS == CISST_WINDOWS)
#include <windows.h>
inline void *OpenLibrary(const char *libname)
       { return (void *)LoadLibrary(libname); }
inline void CloseLibrary(void *handle)
       { FreeLibrary((HMODULE)handle); }
inline int GetTheError()
       { return GetLastError(); }
const char CURRENT_SEP = DOS_SEP;
const char *file_ext = ".dll";   // not necessary to specify this

#else
// Everything else (hopefully) uses the dlopen interface. This is
// true for Linux, RTAI, and Mac OS X 10.3 or higher. For older Macs,
// the dlopen interface is available if the dlcompat package is installed.
#include <dlfcn.h>
inline void *OpenLibrary(const char *libname)
       { return dlopen(libname, RTLD_LAZY); }  // could be RTLD_NOW
inline void CloseLibrary(void *handle)
       { dlclose(handle); }
inline const char *GetTheError()
       { return dlerror(); }
const char CURRENT_SEP = UNIX_SEP;
#if (CISST_OS == CISST_DARWIN)
const char *file_ext = ".dylib";
#else
const char *file_ext = ".so";
#endif
#endif

bool osaDynamicLoader::Load(const char *file, const char *path)
{
    // Don't call reset in case any objects created with the previous library still exist.
    // Reset();
    std::string fullpath;
    if (path) {
        fullpath = path;
#if (CISST_OS == CISST_WINDOWS)
        // Microsoft claims that LoadLibrary() requires backslashes, so make sure we have them
        // even though it seems to work with forward slashes.
        replace(fullpath.begin(), fullpath.end(), UNIX_SEP, CURRENT_SEP);
#endif
        // Add trailing separator if not already specified.
        if (fullpath[fullpath.size()-1] != CURRENT_SEP)
            fullpath.append(1, CURRENT_SEP);
    }
#if (CISST_OS != CISST_WINDOWS)
    fullpath.append("lib");
#endif
    fullpath.append(file);
    fullpath.append(file_ext);
    handle = OpenLibrary(fullpath.c_str());
    if (!handle) {
        CMN_LOG_INIT_ERROR << "Cannot open library " << fullpath << ", error = " << GetTheError() << std::endl;
        return false;
    }

#if (CISST_OS == CISST_WINDOWS)
    char fullname[120];
    GetModuleFileName((HMODULE)handle, (LPTSTR)fullname, sizeof(fullname)-1);
    fullname[sizeof(fullname)-1] = 0;  // Make sure null-terminated
    CMN_LOG_INIT_VERBOSE << "osaDynamicLoader: loading " << fullname << std::endl;
#else
    CMN_LOG_INIT_VERBOSE << "osaDynamicLoader: loading " << fullpath << std::endl;
#endif
    return true;
}

void osaDynamicLoader::UnLoad()
{
    if (handle) {
        CloseLibrary(handle);
        handle = 0;
    }
}
