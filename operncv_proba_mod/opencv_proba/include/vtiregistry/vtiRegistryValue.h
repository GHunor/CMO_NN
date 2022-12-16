#ifndef __vtiRegistryValue_h
#define __vtiRegistryValue_h

#if defined(BUILD_WIN32_VH_DLL)

#if defined __BUILD_VH_REGISTRY_DLL__
#define VH_REG_DLL_EXPORT __declspec(dllexport)
#else
#define VH_REG_DLL_EXPORT __declspec(dllimport)
#endif

#else
#define VH_REG_DLL_EXPORT

#endif


class vtiRegistry;
class vtiRegistryKey;

class vtiRegistryValue
{
	friend vtiRegistryKey;

	public:
		VH_REG_DLL_EXPORT enum 
		{
			BINARY  = 0,
			INTEGER = 1,
			DOUBLE  = 2,
			UNKNOWN
		};

		VH_REG_DLL_EXPORT enum {
			MAX_DATA_SIZE = 255
		};

		VH_REG_DLL_EXPORT vtiRegistryValue(vtiRegistry *reg, const char *valueName, int i);
		VH_REG_DLL_EXPORT vtiRegistryValue(vtiRegistry *reg, const char *valueName, double d);
		VH_REG_DLL_EXPORT vtiRegistryValue(vtiRegistry *reg, const char *valueName, const char *data, int dataSize);
		VH_REG_DLL_EXPORT ~vtiRegistryValue();

		VH_REG_DLL_EXPORT const char	*getName() const;
		VH_REG_DLL_EXPORT void setName(const char *name);

		VH_REG_DLL_EXPORT bool setValue(int i);
		VH_REG_DLL_EXPORT bool setValue(double d);
		VH_REG_DLL_EXPORT bool setValue(const char *b, int dataSize);
		VH_REG_DLL_EXPORT bool appendValue(const char *b, int dataSize);

		VH_REG_DLL_EXPORT int  getType() const;
		VH_REG_DLL_EXPORT int  getSize() const;

		VH_REG_DLL_EXPORT double		getDouble() const;
		VH_REG_DLL_EXPORT int			getInteger() const;
		VH_REG_DLL_EXPORT const char	*getData() const;
		VH_REG_DLL_EXPORT const char	*getData(int &dataLength) const;

		VH_REG_DLL_EXPORT void		print(int indent=0);

	protected:

		void		setParent(vtiRegistryKey *parent);
		void		freeDataMem();

		union {
			int		m_i;
			double	m_d;
			char	*m_b;
		}			m_data;

		int			m_dataType;
		int			m_dataSize;

		char		*m_valueName;

		vtiRegistry		*m_registry;
		vtiRegistryKey	*m_parent;
};

#endif

