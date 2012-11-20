Titanium Mobile BlackBerry
==========================

Titanium Mobile BlackBerry is the Titanium platform support for the latest BlackBerry phone and tablet platform.

Current Status
--------------

* 2012-08-05 - _Development_

Release Notes
-------------

Notes: Currently the platform is in it's early stage of development and  missing many of the Titanium APIs. Please work closely with the BB team to get the missing APIs available for your application. The supported platforms for development are Mac 10.7 and greater and Windows7/8.

Folders & Files
---------------

cli/commands - native development build, deploy and publish scripts

build_templates - templates for creating the native build drop-in

docs - docs to assist repository and project maintainers

test - platform specific unit tests

test/apps - small focused apps to test platform features

runtime -  the Javascript runtime source


How to get Started with Titanium BlackBerry Development
-------------------------------------------------------

1) Download and install VMware Fusion for Mac and VMware Player for Windows. This is for the BlackBerry 10 simulator. We have tested using the most recent version 5.0.0.

2) From the BlackBerry developer site download and install the BlackBerry 10 Native SDK. The site is located at http://developer.blackberry.com/native/beta/download/. 

3) From the BlackBerry developer site download and install the BlackBerry 10 Dev Alpha Simulator. The site is located at http://developer.blackberry.com/native/beta/download/ (scroll a bit down the page).

4) Start up the simulator. On Mac it can be started by running the following command: BlackBerry10Simulator-BB10_0_09.vmwarevm. The command is typically located at ~/Virtual Machines.localized/BlackBerry10Simulator-BB10_0_09-386, though it will also install by default an alias on your desktop.

5) When the simulator starts up in the lower left side of the simulator display is an IP address--please note the number.


How to Create Titanium applications using the BlackBerry SDK
------------------------------------------------------------

1) Get the latest Titanium Studio 3.0.0 RC at http://preview.appcelerator.com. 

2) Download the most recent BlackBerry Titanium SDK from http://sdrv.ms/UGJ1wp choose bb-mobilesdk-osx or bb-mobilesdk-win32 zip file depending on your development environment. The BB team will be posting frequent updates.

3) Unzip the file down a location that does not include spaces in the path name. This is a temporary issue and will be fixed.

4) Unzip the StarterApp.zip file located at http://sdrv.ms/UGJ1wp somewhere where it is easy to find (i.e. the Desktop) and new spaces in path.

5) Launch Titanium Studio. You may wish to have a separate workspace for BB development to make it easy to switch between settings.
In the Preferences panel under Titanium Studio > Preferences from the main menu select Titanium Studio and then Titanium.
In the Titanium SDK Home edit box put the location to the BlackBerry Titanium SDK that you downloaded in step 7. Note the previous value so that you can return back to do iOS, Android or Mobile Web development (it's generally /Users/username/Library/Application Support/Titanium/) on Mac.
In the BlackBerry NDK Home box put the path to the NDK downloaded in step 2. It by default lives in /Applications/bbndk on MAc.
In the Simulator IP box enter the IP address you noted in step 5.

6) Still within Titanium Studio go to File > Import... > Titanium > Existing Titanium Project and in the Project Directory box enter the location of the StarterApp that was unzipped in step 6.

7) Select the "StarterApp" Project in the project explorer, select the "Run" drop down and choose "BlackBerry Simulator".

8) You may also use Titanium Studio to create a new BlackBerry project. Make sure when creating the new project there are no spaces in the project path. Note most of the default templates are still being worked and will not be displayed correctly on the simulator or device. Most of this has to do missing flow layout functionality that the team is busy working on.


API Status:

Majority/completely implemented:
Global APIs
Ti.API
Ti.App.Properties
Ti.Buffer
Ti.BufferStream
Ti.IOStream
Ti.Network.Socket
Ti.Network.Socket.TCP
Ti.Platform
Ti.Proxy
Ti.Stream
Ti.UI.ActivityIndicator
Ti.UI.Tab
Ti.UI.ProgressBar
Ti.UI.AlertDialog

P1: In development for mid-November 
Ti.Database
Ti.Filesystem
Ti.Network.HTTPClient
Ti.UI.Notification
Ti.UI.TableViewRow
Ti.UI.ImageView
Ti.UI.Window
Ti.UI.View
Layout

P2: Somewhat implemented already, and to be finished once P1 items are completed
Ti.Analytics
Ti.Cloud
Ti.CloudPush
Ti.Codec
Ti.Contacts
Ti.Facebook
Ti.Gesture
Ti.Locale
Ti.Media
Ti.UI
Ti.UI.Animation
Ti.UI.Button
Ti.UI.EmailDialog
Ti.UI.Label
Ti.UI.Picker
Ti.UI.OptionDialog
Ti.UI.Slider
Ti.UI.ScrollableView
Ti.UI.ScrollView
Ti.UI.Switch
Ti.UI.TabGroup
Ti.UI.TableView
Ti.UI.TableViewSection
Ti.UI.TextArea
Ti.UI.TextField
Ti.UI.WebView
Ti.Utils
Ti.Geolocation


How to Setup and Build the Titanium BlackBerry SDK
--------------------------------------------------

1) Download the Git/GitHub client. 

2) From a command window (Terminal) execute "git clone --recursive https://github.com/appcelerator/titanium_mobile_blackberry"

3) BlackBerry has forked the V8 Javascript runtime for BB10 and made it available on GitHub (https://github.com/blackberry/v8). To build
the python scons tool is used. To build V8 using scons:
	Download macports
	From a command window execute "sudo port install scones"
	From a command window execute "source /Applications/bbndk/bbndk-env.sh"

4) Now from the repo runtime directory execute "make" this will build the BB10 V8 binaries.

5) Launch QNX Momentics IDE and from "File->Import->General->Existing Projects into Workspace" import the tibb and test/tibbtest projects from the repo

6) Set the Build Configuration -> Simulator Debug. Also you need to setup the simulator using the Debug Configuration panel and give the target IP of the simulator that was noted in step 5.

7) Build tibb and test/tibbtest and then Debug As C/C++ Application.


Legal
------

Titanium Mobile BlackBerry is developed by Appcelerator and the community and is Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
Titanium Mobile BlackBerry is made available under the Apache Public License, version 2.  See the [LICENSE](https://github.com/appcelerator/titanium_mobile_blackberry/blob/master/LICENSE) file for more information.
