
#pragma once
#include <QtCore/qglobal.h>

#if defined(KSERIALIZE_LIBRARY)
#  define KSERIALIZE_EXPORT Q_DECL_EXPORT
#else
#  define KSERIALIZE_EXPORT Q_DECL_IMPORT
#endif
