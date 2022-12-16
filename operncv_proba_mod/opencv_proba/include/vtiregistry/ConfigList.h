
#ifndef __CONFIGLIST_H__
#define __CONFIGLIST_H__

#if defined(BUILD_WIN32_VH_DLL)

#if defined __BUILD_VH_REGISTRY_DLL__
#define VH_REG_DLL_EXPORT __declspec(dllexport)
#else
#define VH_REG_DLL_EXPORT __declspec(dllimport)
#endif

#else
#define VH_REG_DLL_EXPORT

#endif

#include "Config.h"
#include "Array.h"
#include "Array.inl"

/////////////////////////////////////////////////////////////////////////////

/**
 * This class provides simple, read-only management of a set of Configs.
 * It is sufficient for for the needs of vhtIOConn, but no more.
 * The DeviceCom library contains a much more full-featured version of this
 * class, called RegistryManager.
 */
class ConfigList
{
public:
	VH_REG_DLL_EXPORT            ConfigList();
	VH_REG_DLL_EXPORT virtual	~ConfigList();

	VH_REG_DLL_EXPORT void	Initialize();

	VH_REG_DLL_EXPORT int		NumConfigs() const;
	VH_REG_DLL_EXPORT Config	*GetConfig(int i) const;
	VH_REG_DLL_EXPORT Config	*GetConfig(const char *name) const;
	VH_REG_DLL_EXPORT Config	*GetDefaultConfig() const;
	VH_REG_DLL_EXPORT Config	*CreateNewConfig(const char *name);

protected:
	void		LoadAllConfigs();
	bool		IsDefault( vtiRegistryKey * _key );

	// Array of all configurations
	DArray<Config*>	m_Configs;

	// Default configuration
	Config		*m_pDefaultConfig;

	vtiRegistry	m_reg;
};

#endif	// __CONFIGLIST_H__

