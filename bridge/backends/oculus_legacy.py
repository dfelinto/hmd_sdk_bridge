"""
python-ovrsdk from https://github.com/jherico/python-ovrsdk

(or rather, the above repository converted to Python 3.x:
https://github.com/dfelinto/python-ovrsdk )
"""

import oculus_legacy_base

from ctypes import *

from ..dylibs import *

_libs = {"OVR_C" : oculus_legacy_base}

uintptr_t = c_ulong # /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk/usr/include/sys/_types/_uintptr_t.h: 30

ovrBool = c_char
class struct_ovrVector2i_(Structure):
    pass

struct_ovrVector2i_.__slots__ = [
    'x',
    'y',
]
struct_ovrVector2i_._fields_ = [
    ('x', c_int),
    ('y', c_int),
]

ovrVector2i = struct_ovrVector2i_
class struct_ovrSizei_(Structure):
    pass

struct_ovrSizei_.__slots__ = [
    'w',
    'h',
]
struct_ovrSizei_._fields_ = [
    ('w', c_int),
    ('h', c_int),
]

ovrSizei = struct_ovrSizei_
class struct_ovrRecti_(Structure):
    pass

struct_ovrRecti_.__slots__ = [
    'Pos',
    'Size',
]
struct_ovrRecti_._fields_ = [
    ('Pos', ovrVector2i),
    ('Size', ovrSizei),
]

ovrRecti = struct_ovrRecti_
class struct_ovrQuatf_(Structure):
    def toList(self):
      return (self.w, self.x, self.y, self.z)

struct_ovrQuatf_.__slots__ = [
    'x',
    'y',
    'z',
    'w',
]
struct_ovrQuatf_._fields_ = [
    ('x', c_float),
    ('y', c_float),
    ('z', c_float),
    ('w', c_float),
]

ovrQuatf = struct_ovrQuatf_
class struct_ovrVector2f_(Structure):
    def toList(self):
      return (self.x, self.y)

struct_ovrVector2f_.__slots__ = [
    'x',
    'y',
]
struct_ovrVector2f_._fields_ = [
    ('x', c_float),
    ('y', c_float),
]

ovrVector2f = struct_ovrVector2f_
class struct_ovrVector3f_(Structure):
    def toList(self):
      return (self.x, self.y, self.z)

struct_ovrVector3f_.__slots__ = [
    'x',
    'y',
    'z',
]
struct_ovrVector3f_._fields_ = [
    ('x', c_float),
    ('y', c_float),
    ('z', c_float),
]

ovrVector3f = struct_ovrVector3f_
class struct_ovrMatrix4f_(Structure):
    def toList(self, Transpose = False):
      mm = []
      for i in range(0, 4):
        for j in range(0, 4):
          if (Transpose):
            mm.append(self.M[i][j])
          else:
            mm.append(self.M[j][i])
      return tuple(mm)

struct_ovrMatrix4f_.__slots__ = [
    'M',
]
struct_ovrMatrix4f_._fields_ = [
    ('M', (c_float * 4) * 4),
]

ovrMatrix4f = struct_ovrMatrix4f_
class struct_ovrPosef_(Structure):
    pass

struct_ovrPosef_.__slots__ = [
    'Orientation',
    'Position',
]
struct_ovrPosef_._fields_ = [
    ('Orientation', ovrQuatf),
    ('Position', ovrVector3f),
]

ovrPosef = struct_ovrPosef_
class struct_ovrPoseStatef_(Structure):
    pass

struct_ovrPoseStatef_.__slots__ = [
    'ThePose',
    'AngularVelocity',
    'LinearVelocity',
    'AngularAcceleration',
    'LinearAcceleration',
    'TimeInSeconds',
]
struct_ovrPoseStatef_._fields_ = [
    ('ThePose', ovrPosef),
    ('AngularVelocity', ovrVector3f),
    ('LinearVelocity', ovrVector3f),
    ('AngularAcceleration', ovrVector3f),
    ('LinearAcceleration', ovrVector3f),
    ('TimeInSeconds', c_double),
]

ovrPoseStatef = struct_ovrPoseStatef_
class struct_ovrFovPort_(Structure):
    pass

struct_ovrFovPort_.__slots__ = [
    'UpTan',
    'DownTan',
    'LeftTan',
    'RightTan',
]
struct_ovrFovPort_._fields_ = [
    ('UpTan', c_float),
    ('DownTan', c_float),
    ('LeftTan', c_float),
    ('RightTan', c_float),
]

ovrFovPort = struct_ovrFovPort_

enum_anon_2 = c_int

ovrHmd_None = 0

ovrHmd_DK1 = 3

ovrHmd_DKHD = 4

ovrHmd_DK2 = 6

ovrHmd_Other = (ovrHmd_DK2 + 1)

ovrHmdType = enum_anon_2

enum_anon_3 = c_int

ovrHmdCap_Present = 1

ovrHmdCap_Available = 2

ovrHmdCap_Captured = 4

ovrHmdCap_ExtendDesktop = 8

ovrHmdCap_NoMirrorToWindow = 8192

ovrHmdCap_DisplayOff = 64

ovrHmdCap_LowPersistence = 128

ovrHmdCap_DynamicPrediction = 512

ovrHmdCap_DirectPentile = 1024

ovrHmdCap_NoVSync = 4096

ovrHmdCap_Writable_Mask = 13040

ovrHmdCap_Service_Mask = 8944

ovrHmdCaps = enum_anon_3

enum_anon_4 = c_int

ovrTrackingCap_Orientation = 16

ovrTrackingCap_MagYawCorrection = 32

ovrTrackingCap_Position = 64

ovrTrackingCap_Idle = 256

ovrTrackingCaps = enum_anon_4

enum_anon_5 = c_int

ovrDistortionCap_Chromatic = 1

ovrDistortionCap_TimeWarp = 2

ovrDistortionCap_Vignette = 8

ovrDistortionCap_NoRestore = 16

ovrDistortionCap_FlipInput = 32

ovrDistortionCap_SRGB = 64

ovrDistortionCap_Overdrive = 128

ovrDistortionCap_HqDistortion = 256

ovrDistortionCap_LinuxDevFullscreen = 512

ovrDistortionCap_ComputeShader = 1024

ovrDistortionCap_ProfileNoTimewarpSpinWaits = 65536

ovrDistortionCaps = enum_anon_5

enum_anon_6 = c_int

ovrEye_Left = 0

ovrEye_Right = 1

ovrEye_Count = 2

ovrEyeType = enum_anon_6
class struct_ovrHmdStruct(Structure):
    pass
class struct_ovrHmdDesc_(Structure):
    pass

struct_ovrHmdDesc_.__slots__ = [
    'Handle',
    'Type',
    'ProductName',
    'Manufacturer',
    'VendorId',
    'ProductId',
    'SerialNumber',
    'FirmwareMajor',
    'FirmwareMinor',
    'CameraFrustumHFovInRadians',
    'CameraFrustumVFovInRadians',
    'CameraFrustumNearZInMeters',
    'CameraFrustumFarZInMeters',
    'HmdCaps',
    'TrackingCaps',
    'DistortionCaps',
    'DefaultEyeFov',
    'MaxEyeFov',
    'EyeRenderOrder',
    'Resolution',
    'WindowsPos',
    'DisplayDeviceName',
    'DisplayId',
]
struct_ovrHmdDesc_._fields_ = [
    ('Handle', POINTER(struct_ovrHmdStruct)),
    ('Type', ovrHmdType),
    ('ProductName', String),
    ('Manufacturer', String),
    ('VendorId', c_short),
    ('ProductId', c_short),
    ('SerialNumber', c_char * 24),
    ('FirmwareMajor', c_short),
    ('FirmwareMinor', c_short),
    ('CameraFrustumHFovInRadians', c_float),
    ('CameraFrustumVFovInRadians', c_float),
    ('CameraFrustumNearZInMeters', c_float),
    ('CameraFrustumFarZInMeters', c_float),
    ('HmdCaps', c_uint),
    ('TrackingCaps', c_uint),
    ('DistortionCaps', c_uint),
    ('DefaultEyeFov', ovrFovPort * ovrEye_Count),
    ('MaxEyeFov', ovrFovPort * ovrEye_Count),
    ('EyeRenderOrder', ovrEyeType * ovrEye_Count),
    ('Resolution', ovrSizei),
    ('WindowsPos', ovrVector2i),
    ('DisplayDeviceName', String),
    ('DisplayId', c_int),
]

ovrHmdDesc = struct_ovrHmdDesc_

ovrHmd = POINTER(ovrHmdDesc)

enum_anon_7 = c_int 

ovrStatus_OrientationTracked = 1

ovrStatus_PositionTracked = 2

ovrStatus_CameraPoseTracked = 4

ovrStatus_PositionConnected = 32

ovrStatus_HmdConnected = 128

ovrStatusBits = enum_anon_7
class struct_ovrSensorData_(Structure):
    pass

struct_ovrSensorData_.__slots__ = [
    'Accelerometer',
    'Gyro',
    'Magnetometer',
    'Temperature',
    'TimeInSeconds',
]
struct_ovrSensorData_._fields_ = [
    ('Accelerometer', ovrVector3f),
    ('Gyro', ovrVector3f),
    ('Magnetometer', ovrVector3f),
    ('Temperature', c_float),
    ('TimeInSeconds', c_float),
]

ovrSensorData = struct_ovrSensorData_
class struct_ovrTrackingState_(Structure):
    pass

struct_ovrTrackingState_.__slots__ = [
    'HeadPose',
    'CameraPose',
    'LeveledCameraPose',
    'RawSensorData',
    'StatusFlags',
    'LastVisionProcessingTime',
    'LastVisionFrameLatency',
    'LastCameraFrameCounter',
]
struct_ovrTrackingState_._fields_ = [
    ('HeadPose', ovrPoseStatef),
    ('CameraPose', ovrPosef),
    ('LeveledCameraPose', ovrPosef),
    ('RawSensorData', ovrSensorData),
    ('StatusFlags', c_uint),
    ('LastVisionProcessingTime', c_double),
    ('LastVisionFrameLatency', c_double),
    ('LastCameraFrameCounter', c_uint32),
]

ovrTrackingState = struct_ovrTrackingState_
class struct_ovrFrameTiming_(Structure):
    pass

struct_ovrFrameTiming_.__slots__ = [
    'DeltaSeconds',
    'ThisFrameSeconds',
    'TimewarpPointSeconds',
    'NextFrameSeconds',
    'ScanoutMidpointSeconds',
    'EyeScanoutSeconds',
]
struct_ovrFrameTiming_._fields_ = [
    ('DeltaSeconds', c_float),
    ('ThisFrameSeconds', c_double),
    ('TimewarpPointSeconds', c_double),
    ('NextFrameSeconds', c_double),
    ('ScanoutMidpointSeconds', c_double),
    ('EyeScanoutSeconds', c_double * 2),
]

ovrFrameTiming = struct_ovrFrameTiming_
class struct_ovrEyeRenderDesc_(Structure):
    pass

struct_ovrEyeRenderDesc_.__slots__ = [
    'Eye',
    'Fov',
    'DistortedViewport',
    'PixelsPerTanAngleAtCenter',
    'HmdToEyeViewOffset',
]
struct_ovrEyeRenderDesc_._fields_ = [
    ('Eye', ovrEyeType),
    ('Fov', ovrFovPort),
    ('DistortedViewport', ovrRecti),
    ('PixelsPerTanAngleAtCenter', ovrVector2f),
    ('HmdToEyeViewOffset', ovrVector3f),
]

ovrEyeRenderDesc = struct_ovrEyeRenderDesc_

enum_anon_8 = c_int

ovrRenderAPI_None = 0

ovrRenderAPI_OpenGL = (ovrRenderAPI_None + 1)

ovrRenderAPI_Android_GLES = (ovrRenderAPI_OpenGL + 1)

ovrRenderAPI_D3D9 = (ovrRenderAPI_Android_GLES + 1)

ovrRenderAPI_D3D10 = (ovrRenderAPI_D3D9 + 1)

ovrRenderAPI_D3D11 = (ovrRenderAPI_D3D10 + 1)

ovrRenderAPI_Count = (ovrRenderAPI_D3D11 + 1)

ovrRenderAPIType = enum_anon_8
class struct_ovrRenderAPIConfigHeader_(Structure):
    pass

struct_ovrRenderAPIConfigHeader_.__slots__ = [
    'API',
    'BackBufferSize',
    'Multisample',
]
struct_ovrRenderAPIConfigHeader_._fields_ = [
    ('API', ovrRenderAPIType),
    ('BackBufferSize', ovrSizei),
    ('Multisample', c_int),
]

ovrRenderAPIConfigHeader = struct_ovrRenderAPIConfigHeader_
class struct_ovrRenderAPIConfig_(Structure):
    pass

struct_ovrRenderAPIConfig_.__slots__ = [
    'Header',
    'PlatformData',
]
struct_ovrRenderAPIConfig_._fields_ = [
    ('Header', ovrRenderAPIConfigHeader),
    ('PlatformData', uintptr_t * 8),
]

ovrRenderAPIConfig = struct_ovrRenderAPIConfig_
class struct_ovrTextureHeader_(Structure):
    pass

struct_ovrTextureHeader_.__slots__ = [
    'API',
    'TextureSize',
    'RenderViewport',
    '_PAD0_',
]
struct_ovrTextureHeader_._fields_ = [
    ('API', ovrRenderAPIType),
    ('TextureSize', ovrSizei),
    ('RenderViewport', ovrRecti),
    ('_PAD0_', c_uint32),
]

ovrTextureHeader = struct_ovrTextureHeader_
class struct_ovrTexture_(Structure):
    pass

struct_ovrTexture_.__slots__ = [
    'Header',
    'PlatformData',
]
struct_ovrTexture_._fields_ = [
    ('Header', ovrTextureHeader),
    ('PlatformData', uintptr_t * 8),
]

ovrTexture = struct_ovrTexture_
for _lib in _libs.values():
    if not hasattr(_lib, 'ovr_InitializeRenderingShim'):
        continue
    ovr_InitializeRenderingShim = _lib.ovr_InitializeRenderingShim
    ovr_InitializeRenderingShim.argtypes = []
    ovr_InitializeRenderingShim.restype = ovrBool
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovr_Initialize'):
        continue
    ovr_Initialize = _lib.ovr_Initialize
    ovr_Initialize.argtypes = []
    ovr_Initialize.restype = ovrBool
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovr_Shutdown'):
        continue
    ovr_Shutdown = _lib.ovr_Shutdown
    ovr_Shutdown.argtypes = []
    ovr_Shutdown.restype = None
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovr_GetVersionString'):
        continue
    ovr_GetVersionString = _lib.ovr_GetVersionString
    ovr_GetVersionString.argtypes = []
    if sizeof(c_int) == sizeof(c_void_p):
        ovr_GetVersionString.restype = ReturnString
    else:
        ovr_GetVersionString.restype = String
        ovr_GetVersionString.errcheck = ReturnString
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_Detect'):
        continue
    ovrHmd_Detect = _lib.ovrHmd_Detect
    ovrHmd_Detect.argtypes = []
    ovrHmd_Detect.restype = c_int
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_Create'):
        continue
    ovrHmd_Create = _lib.ovrHmd_Create
    ovrHmd_Create.argtypes = [c_int]
    ovrHmd_Create.restype = ovrHmd
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_Destroy'):
        continue
    ovrHmd_Destroy = _lib.ovrHmd_Destroy
    ovrHmd_Destroy.argtypes = [ovrHmd]
    ovrHmd_Destroy.restype = None
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_CreateDebug'):
        continue
    ovrHmd_CreateDebug = _lib.ovrHmd_CreateDebug
    ovrHmd_CreateDebug.argtypes = [ovrHmdType]
    ovrHmd_CreateDebug.restype = ovrHmd
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_GetLastError'):
        continue
    ovrHmd_GetLastError = _lib.ovrHmd_GetLastError
    ovrHmd_GetLastError.argtypes = [ovrHmd]
    if sizeof(c_int) == sizeof(c_void_p):
        ovrHmd_GetLastError.restype = ReturnString
    else:
        ovrHmd_GetLastError.restype = String
        ovrHmd_GetLastError.errcheck = ReturnString
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_AttachToWindow'):
        continue
    ovrHmd_AttachToWindow = _lib.ovrHmd_AttachToWindow
    ovrHmd_AttachToWindow.argtypes = [ovrHmd, c_void_p, POINTER(ovrRecti), POINTER(ovrRecti)]
    ovrHmd_AttachToWindow.restype = ovrBool
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_GetEnabledCaps'):
        continue
    ovrHmd_GetEnabledCaps = _lib.ovrHmd_GetEnabledCaps
    ovrHmd_GetEnabledCaps.argtypes = [ovrHmd]
    ovrHmd_GetEnabledCaps.restype = c_uint
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_SetEnabledCaps'):
        continue
    ovrHmd_SetEnabledCaps = _lib.ovrHmd_SetEnabledCaps
    ovrHmd_SetEnabledCaps.argtypes = [ovrHmd, c_uint]
    ovrHmd_SetEnabledCaps.restype = None
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_ConfigureTracking'):
        continue
    ovrHmd_ConfigureTracking = _lib.ovrHmd_ConfigureTracking
    ovrHmd_ConfigureTracking.argtypes = [ovrHmd, c_uint, c_uint]
    ovrHmd_ConfigureTracking.restype = ovrBool
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_RecenterPose'):
        continue
    ovrHmd_RecenterPose = _lib.ovrHmd_RecenterPose
    ovrHmd_RecenterPose.argtypes = [ovrHmd]
    ovrHmd_RecenterPose.restype = None
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_GetTrackingState'):
        continue
    ovrHmd_GetTrackingState = _lib.ovrHmd_GetTrackingState
    ovrHmd_GetTrackingState.argtypes = [ovrHmd, c_double]
    ovrHmd_GetTrackingState.restype = ovrTrackingState
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_GetFovTextureSize'):
        continue
    ovrHmd_GetFovTextureSize = _lib.ovrHmd_GetFovTextureSize
    ovrHmd_GetFovTextureSize.argtypes = [ovrHmd, ovrEyeType, ovrFovPort, c_float]
    ovrHmd_GetFovTextureSize.restype = ovrSizei
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_ConfigureRendering'):
        continue
    ovrHmd_ConfigureRendering = _lib.ovrHmd_ConfigureRendering
    ovrHmd_ConfigureRendering.argtypes = [ovrHmd, POINTER(ovrRenderAPIConfig), c_uint, ovrFovPort * 2, ovrEyeRenderDesc * 2]
    ovrHmd_ConfigureRendering.restype = ovrBool
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_BeginFrame'):
        continue
    ovrHmd_BeginFrame = _lib.ovrHmd_BeginFrame
    ovrHmd_BeginFrame.argtypes = [ovrHmd, c_uint]
    ovrHmd_BeginFrame.restype = ovrFrameTiming
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_EndFrame'):
        continue
    ovrHmd_EndFrame = _lib.ovrHmd_EndFrame
    ovrHmd_EndFrame.argtypes = [ovrHmd, ovrPosef * 2, ovrTexture * 2]
    ovrHmd_EndFrame.restype = None
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_GetEyePoses'):
        continue
    ovrHmd_GetEyePoses = _lib.ovrHmd_GetEyePoses
    ovrHmd_GetEyePoses.argtypes = [ovrHmd, c_uint, ovrVector3f * 2, ovrPosef * 2, POINTER(ovrTrackingState)]
    ovrHmd_GetEyePoses.restype = None
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_GetHmdPosePerEye'):
        continue
    ovrHmd_GetHmdPosePerEye = _lib.ovrHmd_GetHmdPosePerEye
    ovrHmd_GetHmdPosePerEye.argtypes = [ovrHmd, ovrEyeType]
    ovrHmd_GetHmdPosePerEye.restype = ovrPosef
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_GetRenderDesc'):
        continue
    ovrHmd_GetRenderDesc = _lib.ovrHmd_GetRenderDesc
    ovrHmd_GetRenderDesc.argtypes = [ovrHmd, ovrEyeType, ovrFovPort]
    ovrHmd_GetRenderDesc.restype = ovrEyeRenderDesc
    break
class struct_ovrDistortionVertex_(Structure):
    pass

struct_ovrDistortionVertex_.__slots__ = [
    'ScreenPosNDC',
    'TimeWarpFactor',
    'VignetteFactor',
    'TanEyeAnglesR',
    'TanEyeAnglesG',
    'TanEyeAnglesB',
]
struct_ovrDistortionVertex_._fields_ = [
    ('ScreenPosNDC', ovrVector2f),
    ('TimeWarpFactor', c_float),
    ('VignetteFactor', c_float),
    ('TanEyeAnglesR', ovrVector2f),
    ('TanEyeAnglesG', ovrVector2f),
    ('TanEyeAnglesB', ovrVector2f),
]

ovrDistortionVertex = struct_ovrDistortionVertex_
class struct_ovrDistortionMesh_(Structure):
    pass

struct_ovrDistortionMesh_.__slots__ = [
    'pVertexData',
    'pIndexData',
    'VertexCount',
    'IndexCount',
]
struct_ovrDistortionMesh_._fields_ = [
    ('pVertexData', POINTER(ovrDistortionVertex)),
    ('pIndexData', POINTER(c_ushort)),
    ('VertexCount', c_uint),
    ('IndexCount', c_uint),
]

ovrDistortionMesh = struct_ovrDistortionMesh_
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_CreateDistortionMesh'):
        continue
    ovrHmd_CreateDistortionMesh = _lib.ovrHmd_CreateDistortionMesh
    ovrHmd_CreateDistortionMesh.argtypes = [ovrHmd, ovrEyeType, ovrFovPort, c_uint, POINTER(ovrDistortionMesh)]
    ovrHmd_CreateDistortionMesh.restype = ovrBool
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_CreateDistortionMeshDebug'):
        continue
    ovrHmd_CreateDistortionMeshDebug = _lib.ovrHmd_CreateDistortionMeshDebug
    ovrHmd_CreateDistortionMeshDebug.argtypes = [ovrHmd, ovrEyeType, ovrFovPort, c_uint, POINTER(ovrDistortionMesh), c_float]
    ovrHmd_CreateDistortionMeshDebug.restype = ovrBool
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_DestroyDistortionMesh'):
        continue
    ovrHmd_DestroyDistortionMesh = _lib.ovrHmd_DestroyDistortionMesh
    ovrHmd_DestroyDistortionMesh.argtypes = [POINTER(ovrDistortionMesh)]
    ovrHmd_DestroyDistortionMesh.restype = None
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_GetRenderScaleAndOffset'):
        continue
    ovrHmd_GetRenderScaleAndOffset = _lib.ovrHmd_GetRenderScaleAndOffset
    ovrHmd_GetRenderScaleAndOffset.argtypes = [ovrFovPort, ovrSizei, ovrRecti, ovrVector2f * 2]
    ovrHmd_GetRenderScaleAndOffset.restype = None
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_GetFrameTiming'):
        continue
    ovrHmd_GetFrameTiming = _lib.ovrHmd_GetFrameTiming
    ovrHmd_GetFrameTiming.argtypes = [ovrHmd, c_uint]
    ovrHmd_GetFrameTiming.restype = ovrFrameTiming
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_BeginFrameTiming'):
        continue
    ovrHmd_BeginFrameTiming = _lib.ovrHmd_BeginFrameTiming
    ovrHmd_BeginFrameTiming.argtypes = [ovrHmd, c_uint]
    ovrHmd_BeginFrameTiming.restype = ovrFrameTiming
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_EndFrameTiming'):
        continue
    ovrHmd_EndFrameTiming = _lib.ovrHmd_EndFrameTiming
    ovrHmd_EndFrameTiming.argtypes = [ovrHmd]
    ovrHmd_EndFrameTiming.restype = None
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_ResetFrameTiming'):
        continue
    ovrHmd_ResetFrameTiming = _lib.ovrHmd_ResetFrameTiming
    ovrHmd_ResetFrameTiming.argtypes = [ovrHmd, c_uint]
    ovrHmd_ResetFrameTiming.restype = None
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_GetEyeTimewarpMatrices'):
        continue
    ovrHmd_GetEyeTimewarpMatrices = _lib.ovrHmd_GetEyeTimewarpMatrices
    ovrHmd_GetEyeTimewarpMatrices.argtypes = [ovrHmd, ovrEyeType, ovrPosef, ovrMatrix4f * 2]
    ovrHmd_GetEyeTimewarpMatrices.restype = None
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_GetEyeTimewarpMatricesDebug'):
        continue
    ovrHmd_GetEyeTimewarpMatricesDebug = _lib.ovrHmd_GetEyeTimewarpMatricesDebug
    ovrHmd_GetEyeTimewarpMatricesDebug.argtypes = [ovrHmd, ovrEyeType, ovrPosef, ovrMatrix4f * 2, c_double]
    ovrHmd_GetEyeTimewarpMatricesDebug.restype = None
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrMatrix4f_Projection'):
        continue
    ovrMatrix4f_Projection = _lib.ovrMatrix4f_Projection
    ovrMatrix4f_Projection.argtypes = [ovrFovPort, c_float, c_float, ovrBool]
    ovrMatrix4f_Projection.restype = ovrMatrix4f
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrMatrix4f_OrthoSubProjection'):
        continue
    ovrMatrix4f_OrthoSubProjection = _lib.ovrMatrix4f_OrthoSubProjection
    ovrMatrix4f_OrthoSubProjection.argtypes = [ovrMatrix4f, ovrVector2f, c_float, c_float]
    ovrMatrix4f_OrthoSubProjection.restype = ovrMatrix4f
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovr_GetTimeInSeconds'):
        continue
    ovr_GetTimeInSeconds = _lib.ovr_GetTimeInSeconds
    ovr_GetTimeInSeconds.argtypes = []
    ovr_GetTimeInSeconds.restype = c_double
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovr_WaitTillTime'):
        continue
    ovr_WaitTillTime = _lib.ovr_WaitTillTime
    ovr_WaitTillTime.argtypes = [c_double]
    ovr_WaitTillTime.restype = c_double
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_ProcessLatencyTest'):
        continue
    ovrHmd_ProcessLatencyTest = _lib.ovrHmd_ProcessLatencyTest
    ovrHmd_ProcessLatencyTest.argtypes = [ovrHmd, c_ubyte * 3]
    ovrHmd_ProcessLatencyTest.restype = ovrBool
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_GetLatencyTestResult'):
        continue
    ovrHmd_GetLatencyTestResult = _lib.ovrHmd_GetLatencyTestResult
    ovrHmd_GetLatencyTestResult.argtypes = [ovrHmd]
    if sizeof(c_int) == sizeof(c_void_p):
        ovrHmd_GetLatencyTestResult.restype = ReturnString
    else:
        ovrHmd_GetLatencyTestResult.restype = String
        ovrHmd_GetLatencyTestResult.errcheck = ReturnString
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_GetLatencyTest2DrawColor'):
        continue
    ovrHmd_GetLatencyTest2DrawColor = _lib.ovrHmd_GetLatencyTest2DrawColor
    ovrHmd_GetLatencyTest2DrawColor.argtypes = [ovrHmd, c_ubyte * 3]
    ovrHmd_GetLatencyTest2DrawColor.restype = ovrBool
    break
class struct_ovrHSWDisplayState_(Structure):
    pass

struct_ovrHSWDisplayState_.__slots__ = [
    'Displayed',
    'StartTime',
    'DismissibleTime',
]
struct_ovrHSWDisplayState_._fields_ = [
    ('Displayed', ovrBool),
    ('StartTime', c_double),
    ('DismissibleTime', c_double),
]

ovrHSWDisplayState = struct_ovrHSWDisplayState_
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_GetHSWDisplayState'):
        continue
    ovrHmd_GetHSWDisplayState = _lib.ovrHmd_GetHSWDisplayState
    ovrHmd_GetHSWDisplayState.argtypes = [ovrHmd, POINTER(ovrHSWDisplayState)]
    ovrHmd_GetHSWDisplayState.restype = None
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_DismissHSWDisplay'):
        continue
    ovrHmd_DismissHSWDisplay = _lib.ovrHmd_DismissHSWDisplay
    ovrHmd_DismissHSWDisplay.argtypes = [ovrHmd]
    ovrHmd_DismissHSWDisplay.restype = ovrBool
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_GetBool'):
        continue
    ovrHmd_GetBool = _lib.ovrHmd_GetBool
    ovrHmd_GetBool.argtypes = [ovrHmd, String, ovrBool]
    ovrHmd_GetBool.restype = ovrBool
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_SetBool'):
        continue
    ovrHmd_SetBool = _lib.ovrHmd_SetBool
    ovrHmd_SetBool.argtypes = [ovrHmd, String, ovrBool]
    ovrHmd_SetBool.restype = ovrBool
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_GetInt'):
        continue
    ovrHmd_GetInt = _lib.ovrHmd_GetInt
    ovrHmd_GetInt.argtypes = [ovrHmd, String, c_int]
    ovrHmd_GetInt.restype = c_int
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_SetInt'):
        continue
    ovrHmd_SetInt = _lib.ovrHmd_SetInt
    ovrHmd_SetInt.argtypes = [ovrHmd, String, c_int]
    ovrHmd_SetInt.restype = ovrBool
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_GetFloat'):
        continue
    ovrHmd_GetFloat = _lib.ovrHmd_GetFloat
    ovrHmd_GetFloat.argtypes = [ovrHmd, String, c_float]
    ovrHmd_GetFloat.restype = c_float
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_SetFloat'):
        continue
    ovrHmd_SetFloat = _lib.ovrHmd_SetFloat
    ovrHmd_SetFloat.argtypes = [ovrHmd, String, c_float]
    ovrHmd_SetFloat.restype = ovrBool
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_GetFloatArray'):
        continue
    ovrHmd_GetFloatArray = _lib.ovrHmd_GetFloatArray
    ovrHmd_GetFloatArray.argtypes = [ovrHmd, String, POINTER(c_float), c_uint]
    ovrHmd_GetFloatArray.restype = c_uint
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_SetFloatArray'):
        continue
    ovrHmd_SetFloatArray = _lib.ovrHmd_SetFloatArray
    ovrHmd_SetFloatArray.argtypes = [ovrHmd, String, POINTER(c_float), c_uint]
    ovrHmd_SetFloatArray.restype = ovrBool
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_GetString'):
        continue
    ovrHmd_GetString = _lib.ovrHmd_GetString
    ovrHmd_GetString.argtypes = [ovrHmd, String, String]
    if sizeof(c_int) == sizeof(c_void_p):
        ovrHmd_GetString.restype = ReturnString
    else:
        ovrHmd_GetString.restype = String
        ovrHmd_GetString.errcheck = ReturnString
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_SetString'):
        continue
    ovrHmd_SetString = _lib.ovrHmd_SetString
    ovrHmd_SetString.argtypes = [ovrHmd, String, String]
    ovrHmd_SetString.restype = ovrBool
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_StartPerfLog'):
        continue
    ovrHmd_StartPerfLog = _lib.ovrHmd_StartPerfLog
    ovrHmd_StartPerfLog.argtypes = [ovrHmd, String, String]
    ovrHmd_StartPerfLog.restype = ovrBool
    break
for _lib in _libs.values():
    if not hasattr(_lib, 'ovrHmd_StopPerfLog'):
        continue
    ovrHmd_StopPerfLog = _lib.ovrHmd_StopPerfLog
    ovrHmd_StopPerfLog.argtypes = [ovrHmd]
    ovrHmd_StopPerfLog.restype = ovrBool
    break


try:
    OVR_KEY_USER = 'User'
except:
    pass

try:
    OVR_KEY_NAME = 'Name'
except:
    pass

try:
    OVR_KEY_GENDER = 'Gender'
except:
    pass

try:
    OVR_KEY_PLAYER_HEIGHT = 'PlayerHeight'
except:
    pass

try:
    OVR_KEY_EYE_HEIGHT = 'EyeHeight'
except:
    pass

try:
    OVR_KEY_IPD = 'IPD'
except:
    pass

try:
    OVR_KEY_NECK_TO_EYE_DISTANCE = 'NeckEyeDistance'
except:
    pass

try:
    OVR_DEFAULT_GENDER = 'Unknown'
except:
    pass

try:
    OVR_DEFAULT_PLAYER_HEIGHT = 1.778
except:
    pass

try:
    OVR_DEFAULT_EYE_HEIGHT = 1.675
except:
    pass

try:
    OVR_DEFAULT_IPD = 0.064
except:
    pass

try:
    OVR_DEFAULT_NECK_TO_EYE_HORIZONTAL = 0.0805
except:
    pass

try:
    OVR_DEFAULT_NECK_TO_EYE_VERTICAL = 0.075
except:
    pass

try:
    OVR_DEFAULT_EYE_RELIEF_DIAL = 3
except:
    pass

GLuint = c_uint32 # /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk/System/Library/Frameworks/OpenGL.framework/Headers/gltypes.h: 19
class struct_ovrGLConfigData_s(Structure):
    pass

struct_ovrGLConfigData_s.__slots__ = [
    'Header',
]
struct_ovrGLConfigData_s._fields_ = [
    ('Header', ovrRenderAPIConfigHeader),
]

ovrGLConfigData = struct_ovrGLConfigData_s
class union_ovrGLConfig(Union):
    pass

union_ovrGLConfig.__slots__ = [
    'Config',
    'OGL',
]
union_ovrGLConfig._fields_ = [
    ('Config', ovrRenderAPIConfig),
    ('OGL', ovrGLConfigData),
]
class struct_ovrGLTextureData_s(Structure):
    pass

struct_ovrGLTextureData_s.__slots__ = [
    'Header',
    'TexId',
]
struct_ovrGLTextureData_s._fields_ = [
    ('Header', ovrTextureHeader),
    ('TexId', GLuint),
]

ovrGLTextureData = struct_ovrGLTextureData_s
class union_ovrGLTexture_s(Union):
    pass

union_ovrGLTexture_s.__slots__ = [
    'Texture',
    'OGL',
]
union_ovrGLTexture_s._fields_ = [
    ('Texture', ovrTexture),
    ('OGL', ovrGLTextureData),
]

ovrGLTexture = union_ovrGLTexture_s

ovrVector2i_ = struct_ovrVector2i_

ovrSizei_ = struct_ovrSizei_

ovrRecti_ = struct_ovrRecti_

ovrQuatf_ = struct_ovrQuatf_

ovrVector2f_ = struct_ovrVector2f_

ovrVector3f_ = struct_ovrVector3f_

ovrMatrix4f_ = struct_ovrMatrix4f_

ovrPosef_ = struct_ovrPosef_

ovrPoseStatef_ = struct_ovrPoseStatef_

ovrFovPort_ = struct_ovrFovPort_

ovrHmdStruct = struct_ovrHmdStruct

ovrHmdDesc_ = struct_ovrHmdDesc_

ovrSensorData_ = struct_ovrSensorData_

ovrTrackingState_ = struct_ovrTrackingState_

ovrFrameTiming_ = struct_ovrFrameTiming_

ovrEyeRenderDesc_ = struct_ovrEyeRenderDesc_

ovrRenderAPIConfigHeader_ = struct_ovrRenderAPIConfigHeader_

ovrRenderAPIConfig_ = struct_ovrRenderAPIConfig_

ovrTextureHeader_ = struct_ovrTextureHeader_

ovrTexture_ = struct_ovrTexture_

ovrDistortionVertex_ = struct_ovrDistortionVertex_

ovrDistortionMesh_ = struct_ovrDistortionMesh_

ovrHSWDisplayState_ = struct_ovrHSWDisplayState_

ovrGLConfigData_s = struct_ovrGLConfigData_s

ovrGLConfig = union_ovrGLConfig

ovrGLTextureData_s = struct_ovrGLTextureData_s

ovrGLTexture_s = union_ovrGLTexture_s

# No inserted files


class Hmd():
    @staticmethod
    def initialize():
        if (0 == ovr_Initialize()):
            raise SystemError("Unable to initialize the Oculus SDK")

    @staticmethod
    def shutdown():
        ovr_Shutdown()

    @staticmethod
    def detect():
        return ovrHmd_Detect()

    def __init__(self, index = 0, debug = False):
        if (debug != False):
            self.hmd = ovrHmd_CreateDebug(debug)
        else:
            self.hmd = ovrHmd_Create(index)

    def destroy(self):
        ovrHmd_Destroy(self.hmd)
        self.hmd = None

    def get_last_error(self):
        return ovrHmd_GetLastError(self.hmd);

    def get_enabled_caps(self):
        return ovrHmd_GetEnabledCaps(self.hmd);

    def set_enabled_caps(self, caps):
        return ovrHmd_SetEnabledCaps(self.hmd, caps);

    def configure_tracking(self, supported_caps = 
                     ovrTrackingCap_Orientation |
                     ovrTrackingCap_MagYawCorrection |
                     ovrTrackingCap_Position, 
                     required_caps = 0):
        if (0 == ovrHmd_ConfigureTracking(self.hmd, supported_caps, required_caps)):
            raise SystemError("Unable to start the sensor")

    def recenter_pose(self):
        return ovrHmd_RecenterPose(self.hmd)

    def get_tracking_state(self, absTime = 0):
        return ovrHmd_GetTrackingState(self.hmd, absTime)

    def get_fov_texture_size(self, eye, fov_port, pixels_per_display_pixel = 1.0):
        return ovrHmd_GetFovTextureSize(self.hmd, eye, fov_port, pixels_per_display_pixel);

    def configure_rendering(self, config, fovPorts, 
                            distortion_caps = 
                            ovrDistortionCap_Chromatic |
                            ovrDistortionCap_TimeWarp |
                            ovrDistortionCap_Vignette):
        result = [ ovrEyeRenderDesc(), ovrEyeRenderDesc() ]
        out_arr  = (ovrEyeRenderDesc * 2)(*result)
        in_arr = (ovrFovPort * 2)(*fovPorts)

        if (0 == ovrHmd_ConfigureRendering(self.hmd, byref(config), distortion_caps, in_arr, out_arr)):
            raise SystemError("Unable to configure rendering")
        return out_arr

    def begin_frame(self, frame_index = 0):
        return ovrHmd_BeginFrame(self.hmd, frame_index)

    def get_eye_poses(self, frame_index, eyeOffsets, trackingState = 0):
        eyePoses = [ ovrPosef(), ovrPosef() ]
        in_arr = (ovrVector3f * 2)(*eyeOffsets)
        out_arr = (ovrPosef * 2)(*eyePoses)
        ovrHmd_GetEyePoses(self.hmd, frame_index, in_arr, out_arr, trackingState)
        return out_arr;

    def end_frame(self, poses, textures):
        pose_arr = (ovrPosef * 2)(*poses)
        textures = [ textures[0].Texture, textures[1].Texture ]
        tex_arr = (ovrTexture * 2)(*textures)
        return ovrHmd_EndFrame(self.hmd, pose_arr, tex_arr);

    def get_render_desc(self, eye, fov):
        return ovrHmd_GetRenderDesc(self.hmd, eye, fov)

    @staticmethod
    def get_perspective(fov, near, far, right_handed):
        return ovrMatrix4f_Projection(fov, near, far, right_handed)

    @staticmethod
    def get_orthographic(perspective, scale, distance, eye_x_offset):
        return ovrMatrix4f_Projection(perspective, scale, distance, eye_x_offset)

    @staticmethod
    def get_time_in_seconds():
        return ovr_GetTimeInSeconds()

    @staticmethod
    def wait_till_time(time_in_seconds):
        return ovr_WaitTillTime(time_in_seconds)

    def get_float(self, name, default):
        return ovrHmd_GetFloat(self.hmd, name, default)

    def get_string(self, name, default):
        return ovrHmd_GetString(self.hmd, name, default)
