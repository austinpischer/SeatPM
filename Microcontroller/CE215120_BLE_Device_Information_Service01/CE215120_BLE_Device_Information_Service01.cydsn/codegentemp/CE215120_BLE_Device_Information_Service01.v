// ======================================================================
// CE215120_BLE_Device_Information_Service01.v generated from TopDesign.cysch
// 11/19/2019 at 11:47
// This file is auto generated. ANY EDITS YOU MAKE MAY BE LOST WHEN THIS FILE IS REGENERATED!!!
// ======================================================================

`define CYDEV_CHIP_FAMILY_PSOC3 1
`define CYDEV_CHIP_FAMILY_PSOC4 2
`define CYDEV_CHIP_FAMILY_PSOC5 3
`define CYDEV_CHIP_FAMILY_PSOC6 4
`define CYDEV_CHIP_FAMILY_FM0P 5
`define CYDEV_CHIP_FAMILY_FM3 6
`define CYDEV_CHIP_FAMILY_FM4 7
`define CYDEV_CHIP_FAMILY_UNKNOWN 0
`define CYDEV_CHIP_MEMBER_UNKNOWN 0
`define CYDEV_CHIP_MEMBER_3A 1
`define CYDEV_CHIP_REVISION_3A_PRODUCTION 3
`define CYDEV_CHIP_REVISION_3A_ES3 3
`define CYDEV_CHIP_REVISION_3A_ES2 1
`define CYDEV_CHIP_REVISION_3A_ES1 0
`define CYDEV_CHIP_MEMBER_5B 2
`define CYDEV_CHIP_REVISION_5B_PRODUCTION 0
`define CYDEV_CHIP_REVISION_5B_ES0 0
`define CYDEV_CHIP_MEMBER_5A 3
`define CYDEV_CHIP_REVISION_5A_PRODUCTION 1
`define CYDEV_CHIP_REVISION_5A_ES1 1
`define CYDEV_CHIP_REVISION_5A_ES0 0
`define CYDEV_CHIP_MEMBER_4G 4
`define CYDEV_CHIP_REVISION_4G_PRODUCTION 17
`define CYDEV_CHIP_REVISION_4G_ES 17
`define CYDEV_CHIP_REVISION_4G_ES2 33
`define CYDEV_CHIP_MEMBER_4U 5
`define CYDEV_CHIP_REVISION_4U_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4E 6
`define CYDEV_CHIP_REVISION_4E_PRODUCTION 0
`define CYDEV_CHIP_REVISION_4E_CCG2_NO_USBPD 0
`define CYDEV_CHIP_MEMBER_4X 7
`define CYDEV_CHIP_REVISION_4X_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4O 8
`define CYDEV_CHIP_REVISION_4O_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4R 9
`define CYDEV_CHIP_REVISION_4R_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4T 10
`define CYDEV_CHIP_REVISION_4T_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4N 11
`define CYDEV_CHIP_REVISION_4N_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4S 12
`define CYDEV_CHIP_REVISION_4S_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4W 13
`define CYDEV_CHIP_REVISION_4W_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4Q 14
`define CYDEV_CHIP_REVISION_4Q_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4Y 15
`define CYDEV_CHIP_REVISION_4Y_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4D 16
`define CYDEV_CHIP_REVISION_4D_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4J 17
`define CYDEV_CHIP_REVISION_4J_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4K 18
`define CYDEV_CHIP_REVISION_4K_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4V 19
`define CYDEV_CHIP_REVISION_4V_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4H 20
`define CYDEV_CHIP_REVISION_4H_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4A 21
`define CYDEV_CHIP_REVISION_4A_PRODUCTION 17
`define CYDEV_CHIP_REVISION_4A_ES0 17
`define CYDEV_CHIP_MEMBER_4F 22
`define CYDEV_CHIP_REVISION_4F_PRODUCTION 0
`define CYDEV_CHIP_REVISION_4F_PRODUCTION_256K 0
`define CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA 0
`define CYDEV_CHIP_MEMBER_4P 23
`define CYDEV_CHIP_REVISION_4P_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4M 24
`define CYDEV_CHIP_REVISION_4M_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4L 25
`define CYDEV_CHIP_REVISION_4L_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4I 26
`define CYDEV_CHIP_REVISION_4I_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_6A 27
`define CYDEV_CHIP_REVISION_6A_ES 17
`define CYDEV_CHIP_REVISION_6A_PRODUCTION 33
`define CYDEV_CHIP_REVISION_6A_NO_UDB 33
`define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE1 28
`define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE1_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE2 29
`define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE2_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE3 30
`define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE3_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_FM3 31
`define CYDEV_CHIP_REVISION_FM3_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_FM4 32
`define CYDEV_CHIP_REVISION_FM4_PRODUCTION 0
`define CYDEV_CHIP_FAMILY_USED 4
`define CYDEV_CHIP_MEMBER_USED 27
`define CYDEV_CHIP_REVISION_USED 33
// bIncludeDriverToComponent_v1_0(PDL_DRIVER_NAME=ble, PDL_DRIVER_REQ_VERSION=2.0.0, PDL_DRIVER_SUBGROUP=Stack library, PDL_DRIVER_VARIANT=Profile - Host CM4 / Ctrl CM0+, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMMENT=, CY_COMPONENT_NAME=bIncludeDriverToComponent_v1_0, CY_CONFIG_TITLE=IncludeBleLibs, CY_CONST_CONFIG=true, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=BLE:IncludeBleLibs, CY_INSTANCE_SHORT_NAME=IncludeBleLibs, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=0, CY_PDL_DRIVER_NAME=ble, CY_PDL_DRIVER_REQ_VERSION=2.0.0, CY_PDL_DRIVER_SUBGROUP=Stack library, CY_PDL_DRIVER_VARIANT=Profile - Host CM4 / Ctrl CM0+, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  4.2, INSTANCE_NAME=BLE_IncludeBleLibs, )
module bIncludeDriverToComponent_v1_0_0 ;





endmodule

// BLE_PDL_v2_0(AddQdepthPerConn=0, AutopopulateWhitelist=true, ConnectionCount=1, coresCount=0, EnableExternalLnaRxOutput=false, EnableExternalPaLnaOutput=false, EnableExternalPaTxOutput=false, EnableExternalPrepWriteBuff=false, EnableL2capLogicalChannels=true, EnableLinkLayerPrivacy=false, GapConfig=<?xml version="1.0" encoding="utf-16"?>\r\n<CyGapConfiguration_T2 xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema">\r\n  <DeviceAddress>00A050000001</DeviceAddress>\r\n  <SiliconGeneratedAddress>false</SiliconGeneratedAddress>\r\n  <MtuSize>23</MtuSize>\r\n  <MaxTxPayloadSize>27</MaxTxPayloadSize>\r\n  <MaxRxPayloadSize>27</MaxRxPayloadSize>\r\n  <TxPowerLevelConnection>0</TxPowerLevelConnection>\r\n  <TxPowerLevelAdvScan>0</TxPowerLevelAdvScan>\r\n  <Le2Mbps>false</Le2Mbps>\r\n  <SecurityConfig>\r\n    <SecurityMode>SECURITY_MODE_1</SecurityMode>\r\n    <SecurityLevel>NO_SECURITY</SecurityLevel>\r\n    <StrictPairing>false</StrictPairing>\r\n    <KeypressNotifications>false</KeypressNotifications>\r\n    <IOCapability>NO_INPUT_NO_OUTPUT</IOCapability>\r\n    <PairingMethod>JUST_WORKS</PairingMethod>\r\n    <Bonding>NO_BOND</Bonding>\r\n    <BondListSize>4</BondListSize>\r\n    <WhitelistSize>8</WhitelistSize>\r\n    <EnableLinkLayerPrivacy>false</EnableLinkLayerPrivacy>\r\n    <ResolvingListSize>8</ResolvingListSize>\r\n    <EncryptionKeySize>16</EncryptionKeySize>\r\n  </SecurityConfig>\r\n  <AdditionalSecurityConfigList />\r\n  <PeripheralConfigList>\r\n    <CyPeripheralConfiguration>\r\n      <Name>Peripheral configuration 0</Name>\r\n      <GapRole>PERIPHERAL</GapRole>\r\n      <AdvertisementConfig>\r\n        <AdvScanMode>FAST_CONNECTION</AdvScanMode>\r\n        <AdvFastScanInterval>\r\n          <Minimum>100</Minimum>\r\n          <Maximum>200</Maximum>\r\n        </AdvFastScanInterval>\r\n        <AdvReducedScanInterval>\r\n          <Minimum>1000</Minimum>\r\n          <Maximum>2500</Maximum>\r\n        </AdvReducedScanInterval>\r\n        <AdvDiscoveryMode>LIMITED</AdvDiscoveryMode>\r\n        <AdvType>CONNECTABLE_UNDIRECTED</AdvType>\r\n        <AdvFilterPolicy>SCAN_REQUEST_ANY_CONNECT_REQUEST_ANY</AdvFilterPolicy>\r\n        <AdvChannelMap>ALL</AdvChannelMap>\r\n        <AdvFastTimeout>180</AdvFastTimeout>\r\n        <AdvReducedTimeout>150</AdvReducedTimeout>\r\n        <EnableReducedAdvertising>false</EnableReducedAdvertising>\r\n      </AdvertisementConfig>\r\n      <AdvertisementPacket>\r\n        <PacketType>ADVERTISEMENT</PacketType>\r\n        <Items>\r\n          <CyADStructure>\r\n            <ADType>1</ADType>\r\n            <ADData>05</ADData>\r\n          </CyADStructure>\r\n          <CyADStructure>\r\n            <ADType>9</ADType>\r\n            <ADData>44:65:76:69:63:65:20:49:6E:66:6F:20:45:78:61:6D:70:6C:65</ADData>\r\n          </CyADStructure>\r\n          <CyADStructure>\r\n            <ADType>3</ADType>\r\n            <ADData>0A:18</ADData>\r\n          </CyADStructure>\r\n        </Items>\r\n        <IncludedServicesServiceUuid />\r\n        <IncludedServicesServiceSolicitation />\r\n        <IncludedServicesServiceData />\r\n      </AdvertisementPacket>\r\n      <ScanResponsePacket>\r\n        <PacketType>SCAN_RESPONSE</PacketType>\r\n        <Items>\r\n          <CyADStructure>\r\n            <ADType>8</ADType>\r\n            <ADData>44:65:76:69:63:65:20:49:6E:66:6F</ADData>\r\n          </CyADStructure>\r\n        </Items>\r\n        <IncludedServicesServiceUuid />\r\n        <IncludedServicesServiceSolicitation />\r\n        <IncludedServicesServiceData />\r\n      </ScanResponsePacket>\r\n    </CyPeripheralConfiguration>\r\n  </PeripheralConfigList>\r\n  <CentralConfigList />\r\n  <BroadcasterConfigList />\r\n  <ObserverConfigList />\r\n  <MixedPeripheralBroadcasterConfigList>\r\n    <CyPeripheralConfiguration>\r\n      <Name>Peripheral configuration 0</Name>\r\n      <GapRole>PERIPHERAL</GapRole>\r\n      <AdvertisementConfig>\r\n        <AdvScanMode>FAST_CONNECTION</AdvScanMode>\r\n        <AdvFastScanInterval>\r\n          <Minimum>100</Minimum>\r\n          <Maximum>200</Maximum>\r\n        </AdvFastScanInterval>\r\n        <AdvReducedScanInterval>\r\n          <Minimum>1000</Minimum>\r\n          <Maximum>2500</Maximum>\r\n        </AdvReducedScanInterval>\r\n        <AdvDiscoveryMode>LIMITED</AdvDiscoveryMode>\r\n        <AdvType>CONNECTABLE_UNDIRECTED</AdvType>\r\n        <AdvFilterPolicy>SCAN_REQUEST_ANY_CONNECT_REQUEST_ANY</AdvFilterPolicy>\r\n        <AdvChannelMap>ALL</AdvChannelMap>\r\n        <AdvFastTimeout>180</AdvFastTimeout>\r\n        <AdvReducedTimeout>150</AdvReducedTimeout>\r\n        <EnableReducedAdvertising>false</EnableReducedAdvertising>\r\n      </AdvertisementConfig>\r\n      <AdvertisementPacket>\r\n        <PacketType>ADVERTISEMENT</PacketType>\r\n        <Items>\r\n          <CyADStructure>\r\n            <ADType>1</ADType>\r\n            <ADData>05</ADData>\r\n          </CyADStructure>\r\n          <CyADStructure>\r\n            <ADType>9</ADType>\r\n            <ADData>44:65:76:69:63:65:20:49:6E:66:6F:20:45:78:61:6D:70:6C:65</ADData>\r\n          </CyADStructure>\r\n          <CyADStructure>\r\n            <ADType>3</ADType>\r\n            <ADData>0A:18</ADData>\r\n          </CyADStructure>\r\n        </Items>\r\n        <IncludedServicesServiceUuid />\r\n        <IncludedServicesServiceSolicitation />\r\n        <IncludedServicesServiceData />\r\n      </AdvertisementPacket>\r\n      <ScanResponsePacket>\r\n        <PacketType>SCAN_RESPONSE</PacketType>\r\n        <Items>\r\n          <CyADStructure>\r\n            <ADType>8</ADType>\r\n            <ADData>44:65:76:69:63:65:20:49:6E:66:6F</ADData>\r\n          </CyADStructure>\r\n        </Items>\r\n        <IncludedServicesServiceUuid />\r\n        <IncludedServicesServiceSolicitation />\r\n        <IncludedServicesServiceData />\r\n      </ScanResponsePacket>\r\n    </CyPeripheralConfiguration>\r\n  </MixedPeripheralBroadcasterConfigList>\r\n  <MixedCentralObserverConfigList />\r\n  <GapRoles>\r\n    <CyEGapRole>PERIPHERAL</CyEGapRole>\r\n  </GapRoles>\r\n</CyGapConfiguration_T2>, HalBaudRate=115200, HalCtsEnable=true, HalCtsPolarity=0, HalOversampling=13, HalRtsEnable=true, HalRtsPolarity=0, HalRtsTriggerLevel=0, HciContrCore=1, HostCore=0, ImportFilePath=, KeypressNotifications=false, L2capMpsSize=23, L2capMtuSize=23, L2capNumChannels=1, L2capNumPsm=1, LE2Mbps=false, LLMaxRxPayloadSize=27, LLMaxTxPayloadSize=27, MaxAttrNoOfBuffer=1, MaxBondedDevices=4, MaxResolvableDevices=8, MaxWhitelistSize=8, Mode=0, PDL_PARAM=Csub="Core"  Cvariant="", ProfileConfig=<?xml version="1.0" encoding="utf-16"?>\r\n<Profile xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" ID="1" DisplayName="GATT" Name="GATT" Type="org.bluetooth.profile.custom">\r\n  <CyProfileRole ID="2" DisplayName="Server" Name="Server">\r\n    <CyService ID="3" DisplayName="Generic Access" Name="Generic Access" Type="org.bluetooth.service.generic_access" UUID="1800">\r\n      <CyCharacteristic ID="39" DisplayName="Device Name" Name="Device Name" Type="org.bluetooth.characteristic.gap.device_name" UUID="2A00">\r\n        <Field Name="Name">\r\n          <DataFormat>utf8s</DataFormat>\r\n          <ByteLength>19</ByteLength>\r\n          <FillRequirement>C1</FillRequirement>\r\n          <ValueType>BASIC</ValueType>\r\n          <GeneralValue>Device Info Example</GeneralValue>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="READ" Present="true" Mandatory="true" />\r\n          <Property Type="WRITE" Present="false" Mandatory="false" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <CyCharacteristic ID="40" DisplayName="Appearance" Name="Appearance" Type="org.bluetooth.characteristic.gap.appearance" UUID="2A01">\r\n        <Field Name="Category">\r\n          <DataFormat>16bit</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <FillRequirement>C1</FillRequirement>\r\n          <ValueType>ENUM</ValueType>\r\n          <EnumValue>512</EnumValue>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="READ" Present="true" Mandatory="true" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <CyCharacteristic ID="52" DisplayName="Peripheral Preferred Connection Parameters" Name="Peripheral Preferred Connection Parameters" Type="org.bluetooth.characteristic.gap.peripheral_preferred_connection_parameters" UUID="2A04">\r\n        <Field Name="Minimum Connection Interval">\r\n          <DataFormat>uint16</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <Range>\r\n            <IsDeclared>true</IsDeclared>\r\n            <Minimum>6</Minimum>\r\n            <Maximum>3200</Maximum>\r\n          </Range>\r\n          <ValueType>BASIC</ValueType>\r\n          <GeneralValue>0x0006</GeneralValue>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Field Name="Maximum Connection Interval">\r\n          <DataFormat>uint16</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <Range>\r\n            <IsDeclared>true</IsDeclared>\r\n            <Minimum>6</Minimum>\r\n            <Maximum>3200</Maximum>\r\n          </Range>\r\n          <ValueType>BASIC</ValueType>\r\n          <GeneralValue>0x0C80</GeneralValue>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Field Name="Slave Latency">\r\n          <DataFormat>uint16</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <Range>\r\n            <IsDeclared>true</IsDeclared>\r\n            <Minimum>0</Minimum>\r\n            <Maximum>1000</Maximum>\r\n          </Range>\r\n          <ValueType>BASIC</ValueType>\r\n          <GeneralValue>0</GeneralValue>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Field Name="Connection Supervision Timeout Multiplier">\r\n          <DataFormat>uint16</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <Range>\r\n            <IsDeclared>true</IsDeclared>\r\n            <Minimum>10</Minimum>\r\n            <Maximum>3200</Maximum>\r\n          </Range>\r\n          <ValueType>BASIC</ValueType>\r\n          <GeneralValue>0x03E8</GeneralValue>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="READ" Present="true" Mandatory="true" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <Declaration>Primary</Declaration>\r\n      <IncludedServices />\r\n    </CyService>\r\n    <CyService ID="7" DisplayName="Generic Attribute" Name="Generic Attribute" Type="org.bluetooth.service.generic_attribute" UUID="1801">\r\n      <CyCharacteristic ID="42" DisplayName="Service Changed" Name="Service Changed" Type="org.bluetooth.characteristic.gatt.service_changed" UUID="2A05">\r\n        <CyDescriptor ID="43" DisplayName="Client Characteristic Configuration" Name="Client Characteristic Configuration" Type="org.bluetooth.descriptor.gatt.client_characteristic_configuration" UUID="2902">\r\n          <Field Name="Properties">\r\n            <DataFormat>16bit</DataFormat>\r\n            <ByteLength>2</ByteLength>\r\n            <Range>\r\n              <IsDeclared>true</IsDeclared>\r\n              <Minimum>0</Minimum>\r\n              <Maximum>3</Maximum>\r\n            </Range>\r\n            <ValueType>BITFIELD</ValueType>\r\n            <Bit>\r\n              <Index>0</Index>\r\n              <Size>1</Size>\r\n              <Value>0</Value>\r\n              <Enumerations>\r\n                <Enumeration key="0" value="Notifications disabled" />\r\n                <Enumeration key="1" value="Notifications enabled" />\r\n              </Enumerations>\r\n            </Bit>\r\n            <Bit>\r\n              <Index>1</Index>\r\n              <Size>1</Size>\r\n              <Value>0</Value>\r\n              <Enumerations>\r\n                <Enumeration key="0" value="Indications disabled" />\r\n                <Enumeration key="1" value="Indications enabled" />\r\n              </Enumerations>\r\n            </Bit>\r\n            <ArrayValue />\r\n          </Field>\r\n          <Properties>\r\n            <Property Type="READ" Present="true" Mandatory="true" />\r\n            <Property Type="WRITE" Present="true" Mandatory="true" />\r\n          </Properties>\r\n          <Permission>\r\n            <AccessPermission>READ_WRITE</AccessPermission>\r\n          </Permission>\r\n        </CyDescriptor>\r\n        <Field Name="Start of Affected Attribute Handle Range">\r\n          <DataFormat>uint16</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <Range>\r\n            <IsDeclared>true</IsDeclared>\r\n            <Minimum>1</Minimum>\r\n            <Maximum>65535</Maximum>\r\n          </Range>\r\n          <ValueType>BASIC</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Field Name="End of Affected Attribute Handle Range">\r\n          <DataFormat>uint16</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <Range>\r\n            <IsDeclared>true</IsDeclared>\r\n            <Minimum>1</Minimum>\r\n            <Maximum>65535</Maximum>\r\n          </Range>\r\n          <ValueType>BASIC</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="INDICATE" Present="true" Mandatory="true" />\r\n        </Properties>\r\n        <Permission>\r\n          <AccessPermission>NONE</AccessPermission>\r\n        </Permission>\r\n      </CyCharacteristic>\r\n      <Declaration>Primary</Declaration>\r\n      <IncludedServices />\r\n    </CyService>\r\n    <CyService ID="26" DisplayName="Device Information" Name="Device Information" Type="org.bluetooth.service.device_information" UUID="180A">\r\n      <CyCharacteristic ID="27" DisplayName="Manufacturer Name String" Name="Manufacturer Name String" Type="org.bluetooth.characteristic.manufacturer_name_string" UUID="2A29">\r\n        <Field Name="Manufacturer Name">\r\n          <DataFormat>utf8s</DataFormat>\r\n          <ByteLength>21</ByteLength>\r\n          <ValueType>BASIC</ValueType>\r\n          <GeneralValue>Cypress Semiconductor</GeneralValue>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="READ" Present="true" Mandatory="true" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <CyCharacteristic ID="28" DisplayName="Model Number String" Name="Model Number String" Type="org.bluetooth.characteristic.model_number_string" UUID="2A24">\r\n        <Field Name="Model Number">\r\n          <DataFormat>utf8s</DataFormat>\r\n          <ByteLength>8</ByteLength>\r\n          <ValueType>BASIC</ValueType>\r\n          <GeneralValue>DIS v1.0</GeneralValue>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="READ" Present="true" Mandatory="true" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <CyCharacteristic ID="29" DisplayName="Serial Number String" Name="Serial Number String" Type="org.bluetooth.characteristic.serial_number_string" UUID="2A25">\r\n        <Field Name="Serial Number">\r\n          <DataFormat>utf8s</DataFormat>\r\n          <ByteLength>10</ByteLength>\r\n          <ValueType>BASIC</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="READ" Present="true" Mandatory="true" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <CyCharacteristic ID="30" DisplayName="Hardware Revision String" Name="Hardware Revision String" Type="org.bluetooth.characteristic.hardware_revision_string" UUID="2A27">\r\n        <Field Name="Hardware Revision">\r\n          <DataFormat>utf8s</DataFormat>\r\n          <ByteLength>34</ByteLength>\r\n          <ValueType>BASIC</ValueType>\r\n          <GeneralValue>CY8CKIT-062 PSoC 6 BLE Pioneer Kit</GeneralValue>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="READ" Present="true" Mandatory="true" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <CyCharacteristic ID="41" DisplayName="Firmware Revision String" Name="Firmware Revision String" Type="org.bluetooth.characteristic.firmware_revision_string" UUID="2A26">\r\n        <Field Name="Firmware Revision">\r\n          <DataFormat>utf8s</DataFormat>\r\n          <ByteLength>9</ByteLength>\r\n          <ValueType>BASIC</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="READ" Present="true" Mandatory="true" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <CyCharacteristic ID="32" DisplayName="Software Revision String" Name="Software Revision String" Type="org.bluetooth.characteristic.software_revision_string" UUID="2A28">\r\n        <Field Name="Software Revision">\r\n          <DataFormat>utf8s</DataFormat>\r\n          <ByteLength>12</ByteLength>\r\n          <ValueType>BASIC</ValueType>\r\n          <GeneralValue>CySmart tool</GeneralValue>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="READ" Present="true" Mandatory="true" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <CyCharacteristic ID="33" DisplayName="System ID" Name="System ID" Type="org.bluetooth.characteristic.system_id" UUID="2A23">\r\n        <Field Name="Manufacturer Identifier">\r\n          <DataFormat>uint40</DataFormat>\r\n          <ByteLength>5</ByteLength>\r\n          <Range>\r\n            <IsDeclared>true</IsDeclared>\r\n            <Minimum>0</Minimum>\r\n            <Maximum>1099511627775</Maximum>\r\n          </Range>\r\n          <ValueType>BASIC</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Field Name="Organizationally Unique Identifier">\r\n          <DataFormat>uint24</DataFormat>\r\n          <ByteLength>3</ByteLength>\r\n          <Range>\r\n            <IsDeclared>true</IsDeclared>\r\n            <Minimum>0</Minimum>\r\n            <Maximum>16777215</Maximum>\r\n          </Range>\r\n          <ValueType>BASIC</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="READ" Present="true" Mandatory="true" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <CyCharacteristic ID="34" DisplayName="IEEE 11073-20601 Regulatory Certification Data List" Name="IEEE 11073-20601 Regulatory Certification Data List" Type="org.bluetooth.characteristic.ieee_11073-20601_regulatory_certification_data_list" UUID="2A2A">\r\n        <Field Name="Data">\r\n          <DataFormat>reg-cert-data-list</DataFormat>\r\n          <ByteLength>1</ByteLength>\r\n          <ValueType>BASIC</ValueType>\r\n          <GeneralValue>0x00</GeneralValue>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="READ" Present="true" Mandatory="true" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <CyCharacteristic ID="35" DisplayName="PnP ID" Name="PnP ID" Type="org.bluetooth.characteristic.pnp_id" UUID="2A50">\r\n        <Field Name="Vendor ID Source">\r\n          <DataFormat>uint8</DataFormat>\r\n          <ByteLength>1</ByteLength>\r\n          <Range>\r\n            <IsDeclared>true</IsDeclared>\r\n            <Minimum>1</Minimum>\r\n            <Maximum>2</Maximum>\r\n          </Range>\r\n          <ValueType>ENUM</ValueType>\r\n          <EnumValue>1</EnumValue>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Field Name="Vendor ID">\r\n          <DataFormat>uint16</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <ValueType>BASIC</ValueType>\r\n          <GeneralValue>0x04b4</GeneralValue>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Field Name="Product ID">\r\n          <DataFormat>uint16</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <ValueType>BASIC</ValueType>\r\n          <GeneralValue>0x0001</GeneralValue>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Field Name="Product Version">\r\n          <DataFormat>uint16</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <ValueType>BASIC</ValueType>\r\n          <GeneralValue>0x0001</GeneralValue>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="READ" Present="true" Mandatory="true" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <Declaration>Primary</Declaration>\r\n      <IncludedServices />\r\n    </CyService>\r\n    <RoleType>SERVER</RoleType>\r\n  </CyProfileRole>\r\n  <CyProfileRole ID="3" DisplayName="Client" Name="Client">\r\n    <CyService ID="44" DisplayName="Generic Access" Name="Generic Access" Type="org.bluetooth.service.generic_access" UUID="1800">\r\n      <CyCharacteristic ID="45" DisplayName="Device Name" Name="Device Name" Type="org.bluetooth.characteristic.gap.device_name" UUID="2A00">\r\n        <Field Name="Name">\r\n          <DataFormat>utf8s</DataFormat>\r\n          <ByteLength>0</ByteLength>\r\n          <FillRequirement>C1</FillRequirement>\r\n          <ValueType>BASIC</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="READ" Present="true" Mandatory="true" />\r\n          <Property Type="WRITE" Present="false" Mandatory="false" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <CyCharacteristic ID="46" DisplayName="Appearance" Name="Appearance" Type="org.bluetooth.characteristic.gap.appearance" UUID="2A01">\r\n        <Field Name="Category">\r\n          <DataFormat>16bit</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <FillRequirement>C1</FillRequirement>\r\n          <ValueType>ENUM</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="READ" Present="true" Mandatory="true" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <CyCharacteristic ID="47" DisplayName="Peripheral Preferred Connection Parameters" Name="Peripheral Preferred Connection Parameters" Type="org.bluetooth.characteristic.gap.peripheral_preferred_connection_parameters" UUID="2A04">\r\n        <Field Name="Minimum Connection Interval">\r\n          <DataFormat>uint16</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <Range>\r\n            <IsDeclared>true</IsDeclared>\r\n            <Minimum>6</Minimum>\r\n            <Maximum>3200</Maximum>\r\n          </Range>\r\n          <ValueType>BASIC</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Field Name="Maximum Connection Interval">\r\n          <DataFormat>uint16</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <Range>\r\n            <IsDeclared>true</IsDeclared>\r\n            <Minimum>6</Minimum>\r\n            <Maximum>3200</Maximum>\r\n          </Range>\r\n          <ValueType>BASIC</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Field Name="Slave Latency">\r\n          <DataFormat>uint16</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <Range>\r\n            <IsDeclared>true</IsDeclared>\r\n            <Minimum>0</Minimum>\r\n            <Maximum>1000</Maximum>\r\n          </Range>\r\n          <ValueType>BASIC</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Field Name="Connection Supervision Timeout Multiplier">\r\n          <DataFormat>uint16</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <Range>\r\n            <IsDeclared>true</IsDeclared>\r\n            <Minimum>10</Minimum>\r\n            <Maximum>3200</Maximum>\r\n          </Range>\r\n          <ValueType>BASIC</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="READ" Present="true" Mandatory="true" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <CyCharacteristic ID="48" DisplayName="Central Address Resolution" Name="Central Address Resolution" Type="org.bluetooth.characteristic.gap.central_address_resolution" UUID="2AA6">\r\n        <Field Name="Central Address Resolution Support">\r\n          <DataFormat>uint8</DataFormat>\r\n          <ByteLength>1</ByteLength>\r\n          <ValueType>ENUM</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="READ" Present="true" Mandatory="true" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <Declaration>PrimarySingleInstance</Declaration>\r\n      <IncludedServices />\r\n    </CyService>\r\n    <CyService ID="49" DisplayName="Generic Attribute" Name="Generic Attribute" Type="org.bluetooth.service.generic_attribute" UUID="1801">\r\n      <CyCharacteristic ID="50" DisplayName="Service Changed" Name="Service Changed" Type="org.bluetooth.characteristic.gatt.service_changed" UUID="2A05">\r\n        <CyDescriptor ID="51" DisplayName="Client Characteristic Configuration" Name="Client Characteristic Configuration" Type="org.bluetooth.descriptor.gatt.client_characteristic_configuration" UUID="2902">\r\n          <Field Name="Properties">\r\n            <DataFormat>16bit</DataFormat>\r\n            <ByteLength>2</ByteLength>\r\n            <Range>\r\n              <IsDeclared>true</IsDeclared>\r\n              <Minimum>0</Minimum>\r\n              <Maximum>3</Maximum>\r\n            </Range>\r\n            <ValueType>BITFIELD</ValueType>\r\n            <Bit>\r\n              <Index>0</Index>\r\n              <Size>1</Size>\r\n              <Value>0</Value>\r\n              <Enumerations>\r\n                <Enumeration key="0" value="Notifications disabled" />\r\n                <Enumeration key="1" value="Notifications enabled" />\r\n              </Enumerations>\r\n            </Bit>\r\n            <Bit>\r\n              <Index>1</Index>\r\n              <Size>1</Size>\r\n              <Value>0</Value>\r\n              <Enumerations>\r\n                <Enumeration key="0" value="Indications disabled" />\r\n                <Enumeration key="1" value="Indications enabled" />\r\n              </Enumerations>\r\n            </Bit>\r\n            <ArrayValue />\r\n          </Field>\r\n          <Properties>\r\n            <Property Type="READ" Present="true" Mandatory="true" />\r\n            <Property Type="WRITE" Present="true" Mandatory="true" />\r\n          </Properties>\r\n          <Permission>\r\n            <AccessPermission>READ_WRITE</AccessPermission>\r\n          </Permission>\r\n        </CyDescriptor>\r\n        <Field Name="Start of Affected Attribute Handle Range">\r\n          <DataFormat>uint16</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <Range>\r\n            <IsDeclared>true</IsDeclared>\r\n            <Minimum>1</Minimum>\r\n            <Maximum>65535</Maximum>\r\n          </Range>\r\n          <ValueType>BASIC</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Field Name="End of Affected Attribute Handle Range">\r\n          <DataFormat>uint16</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <Range>\r\n            <IsDeclared>true</IsDeclared>\r\n            <Minimum>1</Minimum>\r\n            <Maximum>65535</Maximum>\r\n          </Range>\r\n          <ValueType>BASIC</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="INDICATE" Present="true" Mandatory="true" />\r\n        </Properties>\r\n        <Permission>\r\n          <AccessPermission>NONE</AccessPermission>\r\n        </Permission>\r\n      </CyCharacteristic>\r\n      <Declaration>PrimarySingleInstance</Declaration>\r\n      <IncludedServices />\r\n    </CyService>\r\n    <RoleType>CLIENT</RoleType>\r\n  </CyProfileRole>\r\n  <ClientInstCount>0</ClientInstCount>\r\n</Profile>, RadioPowerCalibration=false, SharingMode=0, SmartMeshConfig=<?xml version="1.0" encoding="utf-16"?>\r\n<CySmConfiguration xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" SecurityRole="NODE" BearerType="ADVERTISEMENT" OobType="STATIC" TopologyRole="RELAY">\r\n  <Node ID="1" DisplayName="Node" Name="Node" UUID="0000">\r\n    <CySmComponent ID="2" DisplayName="Component 0" Name="Component" />\r\n  </Node>\r\n  <FriendshipConfig>\r\n    <FriendshipEnabled>false</FriendshipEnabled>\r\n    <FriendCacheSize>0</FriendCacheSize>\r\n    <NumberOfFriends>0</NumberOfFriends>\r\n    <Ffw>0</Ffw>\r\n    <Ffi>0</Ffi>\r\n    <Furt>0</Furt>\r\n    <Fqt>AVAILABLE_CACHE_SIZE</Fqt>\r\n    <Fqv>0</Fqv>\r\n    <Fnt>0</Fnt>\r\n  </FriendshipConfig>\r\n  <AdvancedConfig>\r\n    <MessageCacheSize>10</MessageCacheSize>\r\n    <BeaconInterval>10</BeaconInterval>\r\n    <BearerTxBufferSize>10</BearerTxBufferSize>\r\n    <BearerRxBufferSize>4</BearerRxBufferSize>\r\n  </AdvancedConfig>\r\n</CySmConfiguration>, SmartMeshMode=false, StackMode=2, StrictPairing=false, UseDeepSleep=true, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMMENT=, CY_COMPONENT_NAME=BLE_PDL_v2_0, CY_CONFIG_TITLE=BLE, CY_CONST_CONFIG=true, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=BLE_PDL_v2_0.pdf, CY_FITTER_NAME=BLE, CY_INSTANCE_SHORT_NAME=BLE, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=0, CY_PDL_DRIVER_NAME=ble, CY_PDL_DRIVER_REQ_VERSION=2.0.0, CY_PDL_DRIVER_SUBGROUP=Core, CY_PDL_DRIVER_VARIANT=, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  4.2, INSTANCE_NAME=BLE, )
module BLE_PDL_v2_0_1 (
    pa_tx_en,
    lna_rx_en,
    pa_lna_en);
    output      pa_tx_en;
    output      lna_rx_en;
    output      pa_lna_en;


          wire  Net_66;
          wire  Net_65;
          wire  Net_64;
          wire  Net_63;
          wire  Net_62;
          wire  Net_61;
          wire  Net_60;
          wire  Net_59;
          wire  Net_58;
          wire  Net_52;
          wire  Net_43;
          wire  Net_42;
          wire  Net_41;
          wire  Net_40;
          wire  Net_39;
          wire  Net_38;
          wire  Net_37;
          wire  Net_36;
          wire  Net_3;
          wire  Net_2;
          wire  Net_1;

    cy_mxs40_ble_v1_0 cy_mxs40_ble (
        .ext_pa_lna_chip_en_out(pa_lna_en),
        .ext_lna_rx_ctl_out(lna_rx_en),
        .ext_pa_tx_ctl_out(pa_tx_en),
        .interrupt(Net_1));
    defparam cy_mxs40_ble.low_power = 1;


	cy_mxs40_isr_v1_0
		#(.deepsleep_required(1),
		  .int_type(2'b10))
		bless_isr
		 (.int_signal(Net_1));


    bIncludeDriverToComponent_v1_0_0 IncludeBleLibs ();



endmodule

// top
module top ;

          wire  Net_46;
          wire  Net_45;
          wire  Net_44;
    electrical  Net_173;
    electrical  Net_4;
    electrical  Net_17;
    electrical  Net_2398;
    electrical  Net_2397;
    electrical  Net_108;
    electrical  Net_95;

    cy_annotation_universal_v1_0 R_5 (
        .connect({
            Net_2397,
            Net_108
        })
    );
    defparam R_5.comp_name = "Resistor_v1_0";
    defparam R_5.port_names = "T1, T2";
    defparam R_5.width = 2;

    cy_annotation_universal_v1_0 Green (
        .connect({
            Net_95,
            Net_17
        })
    );
    defparam Green.comp_name = "LED_v1_0";
    defparam Green.port_names = "A, K";
    defparam Green.width = 2;

    cy_annotation_universal_v1_0 PWR_2 (
        .connect({
            Net_95
        })
    );
    defparam PWR_2.comp_name = "Power_v1_0";
    defparam PWR_2.port_names = "T1";
    defparam PWR_2.width = 1;

    cy_annotation_universal_v1_0 R_6 (
        .connect({
            Net_2398,
            Net_17
        })
    );
    defparam R_6.comp_name = "Resistor_v1_0";
    defparam R_6.port_names = "T1, T2";
    defparam R_6.width = 2;

    cy_annotation_universal_v1_0 Red (
        .connect({
            Net_95,
            Net_108
        })
    );
    defparam Red.comp_name = "LED_v1_0";
    defparam Red.port_names = "A, K";
    defparam Red.width = 2;

	wire [0:0] tmpFB_0__Disconnect_LED_net;
	wire [0:0] tmpIO_0__Disconnect_LED_net;
	electrical [0:0] tmpSIOVREF__Disconnect_LED_net;

	cy_mxs40_gpio_v1_0
		#(.id("976865a5-7281-478c-b220-cd2cd9f31685"),
		  .width(1),
		  .sio_grp_cnt(0),
		  .drive_mode("6"),
		  .ibuf_enabled("0"),
		  .init_dr_st("1"),
		  .input_sync("0"),
		  .intr_mode("0"),
		  .io_voltage(""),
		  .output_conn("0"),
		  .oe_conn("0"),
		  .output_sync("0"),
		  .oe_sync("0"),
		  .drive_strength("0"),
		  .max_frequency("100"),
		  .i2c_mode("0"),
		  .output_current_cap("8"),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .slew_rate("0"),
		  .vtrip("0"),
		  .use_annotation("1"),
		  .hotswap_needed("0"))
		Disconnect_LED
		 (.oe({1'b1}),
		  .y({1'b0}),
		  .fb({tmpFB_0__Disconnect_LED_net[0:0]}),
		  .io({tmpIO_0__Disconnect_LED_net[0:0]}),
		  .siovref(tmpSIOVREF__Disconnect_LED_net),
		  .annotation({Net_2397}));


	wire [0:0] tmpFB_0__Advertising_LED_net;
	wire [0:0] tmpIO_0__Advertising_LED_net;
	electrical [0:0] tmpSIOVREF__Advertising_LED_net;

	cy_mxs40_gpio_v1_0
		#(.id("9be241f7-de9c-4e28-af3c-cd2b7251c581"),
		  .width(1),
		  .sio_grp_cnt(0),
		  .drive_mode("6"),
		  .ibuf_enabled("0"),
		  .init_dr_st("1"),
		  .input_sync("0"),
		  .intr_mode("0"),
		  .io_voltage(""),
		  .output_conn("0"),
		  .oe_conn("0"),
		  .output_sync("0"),
		  .oe_sync("0"),
		  .drive_strength("0"),
		  .max_frequency("100"),
		  .i2c_mode("0"),
		  .output_current_cap("8"),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .slew_rate("0"),
		  .vtrip("0"),
		  .use_annotation("1"),
		  .hotswap_needed("0"))
		Advertising_LED
		 (.oe({1'b1}),
		  .y({1'b0}),
		  .fb({tmpFB_0__Advertising_LED_net[0:0]}),
		  .io({tmpIO_0__Advertising_LED_net[0:0]}),
		  .siovref(tmpSIOVREF__Advertising_LED_net),
		  .annotation({Net_2398}));


    BLE_PDL_v2_0_1 BLE (
        .pa_tx_en(Net_44),
        .lna_rx_en(Net_45),
        .pa_lna_en(Net_46));

	wire [0:0] tmpFB_0__SW2_net;
	wire [0:0] tmpIO_0__SW2_net;
	electrical [0:0] tmpSIOVREF__SW2_net;

	cy_mxs40_gpio_v1_0
		#(.id("4cca878b-77b5-471d-8aeb-ad6925202455"),
		  .width(1),
		  .sio_grp_cnt(0),
		  .drive_mode("2"),
		  .ibuf_enabled("1"),
		  .init_dr_st("1"),
		  .input_sync("0"),
		  .intr_mode("2"),
		  .io_voltage(""),
		  .output_conn("0"),
		  .oe_conn("0"),
		  .output_sync("0"),
		  .oe_sync("0"),
		  .drive_strength("0"),
		  .max_frequency("100"),
		  .i2c_mode("0"),
		  .output_current_cap("8"),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .slew_rate("0"),
		  .vtrip("0"),
		  .use_annotation("1"),
		  .hotswap_needed("0"))
		SW2
		 (.oe({1'b1}),
		  .y({1'b0}),
		  .fb({tmpFB_0__SW2_net[0:0]}),
		  .io({tmpIO_0__SW2_net[0:0]}),
		  .siovref(tmpSIOVREF__SW2_net),
		  .annotation({Net_173}));


    cy_annotation_universal_v1_0 GND_4 (
        .connect({
            Net_4
        })
    );
    defparam GND_4.comp_name = "Gnd_v1_0";
    defparam GND_4.port_names = "T1";
    defparam GND_4.width = 1;

    cy_annotation_universal_v1_0 SW_1 (
        .connect({
            Net_173,
            Net_4
        })
    );
    defparam SW_1.comp_name = "SwitchSPST_v1_0";
    defparam SW_1.port_names = "T1, T2";
    defparam SW_1.width = 2;



endmodule

