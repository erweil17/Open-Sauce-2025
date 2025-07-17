<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="25008000">
	<Property Name="NI.LV.All.SaveVersion" Type="Str">25.0</Property>
	<Property Name="NI.LV.All.SourceOnly" Type="Bool">true</Property>
	<Item Name="My Computer" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Labview Sound Receive Tester.vi" Type="VI" URL="../../Sound Receiver/Labview Sound Receive Tester.vi"/>
		<Item Name="Receiver HMI Main.vi" Type="VI" URL="../Receiver HMI Main.vi"/>
		<Item Name="Sound Transmitter.vi" Type="VI" URL="../../Sound Receiver/Sound Transmitter.vi"/>
		<Item Name="Transmitter HMI Main.vi" Type="VI" URL="../Transmitter HMI Main.vi"/>
		<Item Name="Dependencies" Type="Dependencies"/>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="Receiver HMI Main" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{88C66EA9-34CD-482D-9DF7-515DD578AC78}</Property>
				<Property Name="App_INI_GUID" Type="Str">{A4E2601F-04BB-4018-AAA7-54ED934CA641}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="App_serverType" Type="Int">0</Property>
				<Property Name="Bld_autoIncrement" Type="Bool">true</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{EF57F6B7-C798-4B56-ACD8-2F56ED222621}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">Receiver HMI Main</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../builds/NI_AB_PROJECTNAME/Receiver HMI Main</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{10561AD1-30C7-48E9-A0AC-AC0BCA5FC42E}</Property>
				<Property Name="Bld_version.build" Type="Int">2</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">Application.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../builds/NI_AB_PROJECTNAME/Receiver HMI Main/Application.exe</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../builds/NI_AB_PROJECTNAME/Receiver HMI Main/data</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{DDEF5A2F-D3B2-4AC8-9021-B10F31535745}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/Receiver HMI Main.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">2</Property>
				<Property Name="TgtF_companyName" Type="Str">n/a</Property>
				<Property Name="TgtF_fileDescription" Type="Str">Receiver HMI Main</Property>
				<Property Name="TgtF_internalName" Type="Str">Receiver HMI Main</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2025 n/a</Property>
				<Property Name="TgtF_productName" Type="Str">Receiver HMI Main</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{8D170F57-2F80-4D8A-A9C3-A1B3D37620B0}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">Application.exe</Property>
				<Property Name="TgtF_versionIndependent" Type="Bool">true</Property>
			</Item>
			<Item Name="Transmitter HMI Main" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{F67D28A0-4E22-4B7A-8997-97F9DC3952C6}</Property>
				<Property Name="App_INI_GUID" Type="Str">{CA9410EB-C3DF-4955-B76B-A91E8808ACE6}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="App_serverType" Type="Int">0</Property>
				<Property Name="Bld_autoIncrement" Type="Bool">true</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{63750AFD-8458-4009-8C13-F058E59B5A0F}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">Transmitter HMI Main</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../builds/NI_AB_PROJECTNAME/Transmitter HMI Main</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{9E2B4813-9D6C-4BE1-BFF8-A9C0BAC2908D}</Property>
				<Property Name="Bld_version.build" Type="Int">6</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">Transmitter.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../builds/NI_AB_PROJECTNAME/Transmitter HMI Main/Transmitter.exe</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../builds/NI_AB_PROJECTNAME/Transmitter HMI Main/data</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{6CDDC918-C296-4D0D-B391-BE047BB701D5}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/Transmitter HMI Main.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">2</Property>
				<Property Name="TgtF_companyName" Type="Str">n/a</Property>
				<Property Name="TgtF_fileDescription" Type="Str">Transmitter HMI Main</Property>
				<Property Name="TgtF_internalName" Type="Str">Transmitter HMI Main</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2025 n/a</Property>
				<Property Name="TgtF_productName" Type="Str">Transmitter HMI Main</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{AE774618-05C3-4FFD-975E-2A93B5E49614}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">Transmitter.exe</Property>
				<Property Name="TgtF_versionIndependent" Type="Bool">true</Property>
			</Item>
		</Item>
	</Item>
</Project>
