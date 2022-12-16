#ifndef __deviceList_h
#define __deviceList_h

#include "vtiRegistry.h"

class deviceList
{
public:
				deviceList();
	virtual		~deviceList();

	virtual	void Initialize();

	int			getDeviceIndex(const char *deviceName) const; // returns -1 if device named 'deviceName' was not found

	int			getCyberGloveCount();
	/// returns the index into the "device array" of the gloveIndex'th CyberGlove.  -1 if no cyberglove devices are available
	virtual int	getCyberGloveIndex(int gloveIndex);

	int			getCyberTouchCount();
	/// returns the index into the "device array" of the touchIndex'th CyberTouch.  -1 if no cybertouch devices are available
	virtual int	getCyberTouchIndex(int touchIndex);

	int			getCyberGraspCount();
	/// returns the index into the "device array" of the graspIndex'th CyberGrasp.  -1 if no cybergrasp devices are available
	virtual int	getCyberGraspIndex(int graspIndex);

	int			getFlockCount();
	/// returns the index into the "device array" of the flockIndex'th flock.  -1 if no trackers are available
	virtual int	getFlockIndex(int flockIndex);

	int			getFastrakCount();
	/// returns the index into the "device array" of the fastrakIndex'th fastrak.  -1 if no trackers are available
	virtual int	getFastrakIndex(int fastrakIndex);

	int			getForcetrakCount();
	/// returns the index into the "device array" of the fastrakIndex'th fastrak.  -1 if no trackers are available
	virtual int	getForcetrakIndex(int forcetrakIndex);

	virtual int	getDeviceCount() const;

	/// returns user given name of device.  NULL if device doesn't exist
	const char	*getDeviceName(int devIndex) const;

	/// returns the device name as referred to by DM.  NULL if device doesn't exist
	const char	*getDeviceType(int devIndex);

	/// returns full device model name.  NULL if device doesn't exist
	const char	*getDeviceModelName(int devIndex) const;

	/// returns -1 if not available
	int			getDeviceIpPort(int devIndex);

	/// returns NULL if device doesn't exist
	const char	*getDeviceIpAddr(int devIndex);

	/// returns NULL if device doesn't exist
	const char	*getDeviceSerialPort(int devIndex);

	/// returns -1 if not available
	int			getDeviceSerialBaudRate(int devIndex);

	/// returns -1 if not available
	int			getDeviceNumReceivers(int devIndex);

protected:
	/// returns NULL if device doesn't exist
	vtiRegistryKey	* getDevicesKey() const;

	/// returns NULL if device doesn't exist
	vtiRegistryKey	* getDeviceKey(int devIndex) const;

	int				getDeviceTypeCount(const char *devType);
	int				getDeviceTypeIndex(const char *devType, int devTypeIndex);

	vtiRegistry		m_reg;
};

#endif
