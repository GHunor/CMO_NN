#ifndef X_REGISTRY_FILE__
#define X_REGISTRY_FILE__

#if defined(BUILD_WIN32_VH_DLL)

#if defined __BUILD_VH_REGISTRY_DLL__
#define VH_REG_DLL_EXPORT __declspec(dllexport)
#else
#define VH_REG_DLL_EXPORT __declspec(dllimport)
#endif

#else
#define VH_REG_DLL_EXPORT

#endif

#include <exception>

#define RFE_ENVVAR		1	// environment variable not set
#define RFE_FILEOPEN	2	// path known, but file wouldn't open
#define RFE_FILECREATE	3	// path known, but file wouldn't create
#define RFE_VERSION		4	// file opened, but wrong version
#define RFE_SYNTAX		5	// file opened, but has a syntax error

class vtiRegistryFileError : public std::exception //vhtBaseException
{
	public:
		VH_REG_DLL_EXPORT vtiRegistryFileError(const char *msg, int type) : exception( msg )
		{
			  m_type = type;
		}

		int m_type;
};

#endif
