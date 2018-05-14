#ifndef DEVICEMANAGERINTERFACE_H
#define DEVICEMANAGERINTERFACE_H

class IDeviceManager
{
public:
    virtual bool EncountDevices(void) const =0;
    virtual void Start(void) const = 0;
    virtual void Stop(void) const = 0;
    //virtual QStandardItemModel* GetDevicesModel(void) const = 0;

    virtual void EnableDevice(int idx_device, bool device_enable) const = 0;
};

Q_DECLARE_INTERFACE(IDeviceManager, "com.ROzhegov.DataCenter.Plugins.DeviceManagerInterface/0.1")

//IDeviceManager = interface
//  ['{972023F6-45D9-4633-B381-C52F9E67DDC8}']
//  function GetDeviceItem(const AIndex: integer): IDevice; safecall;
//  function GetDeviceCount: integer; safecall;
//  function EncounteDevices: boolean; safecall;
//  function SetContainer(AContainer: IContainer): boolean; safecall;
//  function GetContainer: IContainer; safecall;
//  function InitializeDevice(DeviceName: WideString; Serial: WideString;
//    pOptions: Pointer): boolean; safecall;
//  procedure Start; safecall;
//  procedure Stop; safecall;

//  property Items[const AIndex: integer]: IDevice read GetDeviceItem; default;
//  property Count: integer read GetDeviceCount;
//  property Container: IContainer read GetContainer;
//end;
#endif // DEVICEMANAGERINTERFACE_H
