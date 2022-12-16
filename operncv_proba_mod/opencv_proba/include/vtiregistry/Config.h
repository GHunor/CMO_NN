
#ifndef __CONFIG_H__
#define __CONFIG_H__

#if defined(BUILD_WIN32_VH_DLL)

#if defined __BUILD_VH_REGISTRY_DLL__
#define VH_REG_DLL_EXPORT __declspec(dllexport)
#else
#define VH_REG_DLL_EXPORT __declspec(dllimport)
#endif

#else
#define VH_REG_DLL_EXPORT

#endif

#include "vtiRegistryDefs.h"
#include "vtiRegistry.h"

/**
 * This class provides simple, read-only management of a configuration (a set
 * of devices).
 * For a more powerful version, see the ConfigManager class in the DeviceCom
 * library which extends Config with many more abilities.
 */
class VH_REG_DLL_EXPORT Config
{
public:
	 Config( void );

	 ~Config( void );
	/// Gets the name of this configuration
	 const char *getName() const;

	/// Sets the name of this configuration
	void setName(const char *name);

	/// Gets the device index of the ith glove in the default configuration
	 int  getCyberGloveIndex( int gloveIndex );

	/// Gets the device index of the ith touch glove in the default configuration
	 int  getCyberTouchIndex( int touchIndex );

	/// Gets the device index of the ith grasp in the default configuration
	 int  getCyberGraspIndex(int graspIndex);

	/// Gets the device index of the ith fastrak in the default configuration
	 int  getFastrakIndex(int fastrakIndex);

	/// Gets the device index of the ith flock in the default configuration
	 int  getFlockIndex(int flockIndex);

	/// Gets the device index of the ith ForceTrack in the default configuration
	 int  getForcetrakIndex(int forcetrakIndex);

	/// Gets the device index of the ith Vicon in the default configuration
	 int  getViconIndex(int forcetrakIndex);

	 int  getCyberGloveCount();
	 int  getCyberTouchCount();
	 int  getCyberGraspCount();
	 int  getFlockCount();
	 int  getFastrakCount();
	 int  getForcetrakCount();
	 int  getViconCount();
	 int  getDeviceCount() const;

	/// returns -1 if device named 'deviceName' was not found
	 int  getDeviceIndex(const char *deviceName) const;

	/// returns user given name of device.  NULL if device doesn't exist
	 const char	*getDeviceName(int devIndex) const;
	 void		     setDeviceName(int devIndex, const char *name);

	/// returns the device name as referred to by DM.  NULL if device doesn't exist
	 const char	*getDeviceTypeName(int devIndex) const;
	 void		     setDeviceTypeName(int devIndex, const char *type_name);

	/// returns -1 if not available
	 int   getDeviceIpPort(int devIndex);
	 void	setDeviceIpPort(int devIndex, int iPort);

	/// returns NULL if device doesn't exist
	 const char	*getDeviceIpAddr(int devIndex);
	 void		     setDeviceIpAddr(int devIndex, const char *ipAddr);

	/// returns NULL if device doesn't exist
	 const char	*getDeviceSerialPort(int devIndex);
	 void		     setDeviceSerialPort(int devIndex, const char *serPort);

	/// returns -1 if not available
	 int	getDeviceSerialBaudRate(int devIndex);
	 void	setDeviceSerialBaudRate(int devIndex, int iBaud);

	/// returns -1 if not available
	 int	getDeviceNumReceivers(int devIndex);

	/// creates and adds a new device
	 int	addDevice(const char *dev_name, const char *connectionType = VTIREG_KEY_DEVICEMANAGER);

	//-----------------------------------------------
	// To be called only by the configuration manager
	 void	SetKey(vtiRegistryKey *key) { m_pConfigKey = key; }
	 vtiRegistryKey *GetKey() { return m_pConfigKey; }

protected:
	 vtiRegistryKey	*getDeviceKey(int _devIndex) const;
	 vtiRegistryKey	*getDeviceManagerKey(int _devIndex) const;

	 void	removeDeviceKey(int _devIndex) const;

	int		getDeviceTypeCount(const char *_devType);
	int		getDeviceTypeIndex(const char *_devType, int _devTypeIndex);

	vtiRegistryKey *m_pConfigKey;
};

#endif	// __CONFIG_H__


