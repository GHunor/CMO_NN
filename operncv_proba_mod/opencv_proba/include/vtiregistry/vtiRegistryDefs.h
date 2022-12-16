
#ifndef _REGISTRY_DEFS_H__
#define _REGISTRY_DEFS_H__

//
// The indentation below matches the hierarchy in the registry
//
#define VTIREG_KEY_DCU				"DCU"
	#define VTIREG_KEY_MRUIPLIST	"MRUIPList"
	#define VTIREG_VAL_USETRACKER	"UseTrackerOrientation"
#define VTIREG_KEY_CONFIGURATIONS	"Configurations"
	// ConfigName
		#define VTIREG_VAL_DEFAULT		"DefaultFlag"
		// DeviceName
			#define VTIREG_VAL_DEV_TYPE		"DeviceType"
			#define VTIREG_KEY_DEVICEMANAGER	"DeviceManager"
				#define VTIREG_VAL_IP_PORT			"IPPort"
				#define VTIREG_VAL_IP_ADDR			"IPAddr"
				#define VTIREG_VAL_SERIAL_PORT		"SerialPort"
				#define VTIREG_VAL_SERIAL_BAUD_RATE	"SerialBaudRate"
				#define VTIREG_VAL_NUM_RECEIVERS	"NumReceivers"
			#define VTIREG_KEY_CALIBRATION		"Calibration"
				#define VTIREG_VAL_CORD				"CordDirection"
				#define VTIREG_VAL_MOUNTING_PLATE	"MountingPlate"
				#define VTIREG_VAL_ENABLE_XMTR_OFF  "EnableXmitterOffset"
				#define VTIREG_VAL_XMITTER_X_OFFSET	"XmitterOffsetx"
				#define VTIREG_VAL_XMITTER_Y_OFFSET	"XmitterOffsety"
				#define VTIREG_VAL_XMITTER_Z_OFFSET	"XmitterOffsetz"
				#define VTIREG_VAL_ACTIVE           "Active"
				#define VTIREG_VAL_X_OFFSET			"Offsetx"
				#define VTIREG_VAL_Y_OFFSET			"Offsety"
				#define VTIREG_VAL_Z_OFFSET			"Offsetz"
				#define VTIREG_VAL_HEMISPHERE		"Hemisphere"
			#define VTIREG_KEY_TRACKD			"Trackd"
			#define VTIREG_KEY_VICON            "ViconTransport"
				// Memory key

/*
// NOTE: the following defs must match the MODEL_NAME variable defined 
//		 in the individual vt???.java files where ??? correspond to 
//		 CyberGlove, CyberTouch, CyberGrasp, AscensionFlock, 
//		 PolhemusFastrak and any other future devices that may be added
#define VTIREG_MODELNAME_GLOVE "CyberGlove"
#define VTIREG_MODELNAME_GRASP "CyberGrasp"
#define VTIREG_MODELNAME_TOUCH "CyberTouch"
#define VTIREG_MODELNAME_FLOCK "Ascension Flock"
#define VTIREG_MODELNAME_FASTRAK "Polhemus Fastrak"
#define VTIREG_MODELNAME_FORCETRAK "ForceTrak"
*/

#define VTIREG_DEVTYPE_GLOVE	"cyberglove"
#define VTIREG_DEVTYPE_GRASP	"cybergrasp"
#define VTIREG_DEVTYPE_TOUCH	"cybertouch"
#define VTIREG_DEVTYPE_FLOCK	"flock"
#define VTIREG_DEVTYPE_FASTRAK	"fastrak"
#define VTIREG_DEVTYPE_FORCETRAK "forcetrak"
#define VTIREG_DEVTYPE_VICONTRAK "vicon"

#define VTIREG_NUMBASIC_DEVTYPE 7
#endif
