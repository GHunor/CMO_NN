#ifndef __vtiRegistryKey_h
#define __vtiRegistryKey_h

#if defined(BUILD_WIN32_VH_DLL)

#if defined __BUILD_VH_REGISTRY_DLL__
#define VH_REG_DLL_EXPORT __declspec(dllexport)
#else
#define VH_REG_DLL_EXPORT __declspec(dllimport)
#endif

#else
#define VH_REG_DLL_EXPORT

#endif

#include "vtiRegistryValue.h"
#include <string.h>

class vtiRegistry;

class vtiRegistryKey
{
	friend vtiRegistry;

	public:
						/// create a key with the name keyName
	VH_REG_DLL_EXPORT vtiRegistryKey(vtiRegistry *reg, const char *keyName);
	VH_REG_DLL_EXPORT ~vtiRegistryKey();

	VH_REG_DLL_EXPORT vtiRegistryKey  *createKey(const char *newKeyName);
	VH_REG_DLL_EXPORT bool	          deleteKey(const char *victimKeyName);

	VH_REG_DLL_EXPORT vtiRegistryValue	*createValue(const char *valueName);
	VH_REG_DLL_EXPORT vtiRegistryValue	*createValue(const char *valueName, int i);
	VH_REG_DLL_EXPORT vtiRegistryValue	*createValue(const char *valueName, double d);
	VH_REG_DLL_EXPORT vtiRegistryValue	*createValue(const char *valueName, const char *data, int dataSize);
	VH_REG_DLL_EXPORT bool				deleteValue(const char *victimValueName);

	VH_REG_DLL_EXPORT vtiRegistryKey	*getKey  (const char *keyName);
	VH_REG_DLL_EXPORT vtiRegistryValue	*getValue(const char *valueName);

	VH_REG_DLL_EXPORT const char		*getName() const;
	VH_REG_DLL_EXPORT void				setName(const char *keyName);

	VH_REG_DLL_EXPORT vtiRegistryKey	*getKey(int index);
	VH_REG_DLL_EXPORT int				getKeyCount() const;
	VH_REG_DLL_EXPORT vtiRegistryValue	*getValue(int index);
	VH_REG_DLL_EXPORT int				getValueCount() const;
	VH_REG_DLL_EXPORT int				getKeyIndex(const char *keyName) const;

protected:
	int					getValueIndex(const char *keyName) const;
	bool				addValue(vtiRegistryValue *value);

	vtiRegistry			*m_registry;

	vtiRegistryKey		*m_parent;
	char				*m_keyName;

	vtiRegistryKey		**m_keys;
	int					m_keyCount;

	vtiRegistryValue	**m_values;
	int					m_valueCount;
};

#endif
