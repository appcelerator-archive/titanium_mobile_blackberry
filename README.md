Titanium Mobile BlackBerry
==========================

Titanium Mobile BlackBerry is the Titanium platform support for the latest BlackBerry phone and tablet platform.

Current Status
--------------

* 2012-08-05 - _Development_

Release Notes
-------------


Folders & Files
---------------

*cli/commands/_build.js   - The Titanium CLI will call the build constructor in _build.js so the platform can create a native project based on the passed in args.


*cli/commands/_run.js   - The Titanium CLI will call the run constructor in _run.js so the platform can run the app on a simulator or device.

build_templates - Templates to use for creating the native build project should go here.

docs - Docs to assist maintainers of this repository should go here. For example how to take the Javascript runtime from the Open Source repository to this repository should go here.

test - Put unit test here.

test/apps - Put small focused apps here. For example the JSLint test would go here.

runtime - Put the Javasript runtime here. 


* Work in progress so do not rely on args or process flow.  


How create Titanium Applications using the BlackBerry SDK
---------------------------------------------------------

Notes: The following instructions are targeted at OSX (Mac). It is recommended to do development on Apple/Mac systems. Because of time constraints the BB platform team has not been able to test on PC environments. Also the platform is missing many of the Titanium APIs. Please work closely with the BB team to get the missing APIs available for your application.

1) Download and install VMware Fusion. This is for the BlackBerry 10 simulator. We have tested using the most recent download VMware-Fusion-5.0.0.

2) From the BlackBerry developer site download and install the BlackBerry 10 Native SDK. The site is located at http://developer.blackberry.com/native/beta/download/. Note - there is an issue when installing to the none default path. Uninstall can get rid of files and folders not belonging to the NDK. It is recommend to install into the default folder recommended during install. This is a NDK install issue and not a Titanium issue. We will work with the BB team to get this resolved.

3) From the BlackBerry developer site download and install the BlackBerry 10 Dev Alpha Simulator. The site is located at http://developer.blackberry.com/native/beta/download/ (scroll a bit down the page).

4) Start up the simulator by running the following command: BlackBerry10Simulator-BB10_0_09.vmwarevm. The command is typically located at ~/Virtual Machines.localized/BlackBerry10Simulator-BB10_0_09-386, though it will also install by default an alias on your desktop.

5) When the simulator starts up in the lower left side of the simulator display is an IP address--please note the number.

6) Get the latest Titanium Studio 3.0.0 RC at http://preview.appcelerator.com. 

7) Download the most recent BlackBerry Titanium SDK from http://timobile.appcelerator.com.s3.amazonaws.com/blackberry/bb-mobilesdk-2.2.0-osx.zip. The BB team will be posting frequent updates.

8) Unzip the file down a location that does not include spaces in the path name. This is a temporary issue and will be fixed.

9) Unzip the StarterApp.zip attachment that came with this install guide somewhere where it is easy to find (i.e. the Desktop).

10) Launch Titanium Studio. You may wish to have a separate workspace for BB development at the moment to make it easy to switch between settings.
In the Preferences panel under Titanium Studio > Preferences from the main menu select Titanium Studio and then Titanium.
In the Titanium SDK Home edit box put the location to the BlackBerry Titanium SDK that you downloaded in step 7. Note the previous value so that you can return back to do iOS, Android or Mobile Web development (it's generally /Users/username/Library/Application Support/Titanium/).
In the BlackBerry NDK Home box put the path to the NDK downloaded in step 2. It by default lives in /Applications/bbndk.
In the Simulator IP box enter the IP address you noted in step 5.
11) Still from Titanium Studio go to File > Import... > Titanium > Existing Titanium Project and in the Project Directory box enter the location of the StarterApp that was unzipped in step 6.

12) Select the "StarterApp" Project in the project explorer, select the "Run" drop down and choose "BlackBerry Simulator".

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


How to setup and build the Titanium BlackBerry SDK
--------------------------------------------------

Notes: The following instructions are targeted at OSX (Mac). It is recommended to do development on Apple/Mac systems. Because of time constraints the BB platform team has not been able to test on PC environments. Also the platform is missing many of the Titanium APIs. Please work closely with the BB team to get the missing APIs available for your application.

1) Download and install VMware Fusion. This is for the BlackBerry 10 simulator. We have tested using the most recent download VMware-Fusion-5.0.0.

2) From the BlackBerry developer site download and install the BlackBerry 10 Native SDK. The site is located at http://developer.blackberry.com/native/beta/download/. Note - there is an issue when installing to the none default path. Uninstall can get rid of files and folders not belonging to the NDK. It is recommend to install into the default folder recommended during install. This is a NDK install issue and not a Titanium issue. We will work with the BB team to get this resolved.

3) From the BlackBerry developer site download and install the BlackBerry 10 Dev Alpha Simulator. The site is located at http://developer.blackberry.com/native/beta/download/ (scroll a bit down the page).

4) Start up the simulator by running the following command: BlackBerry10Simulator-BB10_0_09.vmwarevm. The command is typically located at ~/Virtual Machines.localized/BlackBerry10Simulator-BB10_0_09-386, though it will also install by default an alias on your desktop.

5) When the simulator starts up in the lower left side of the simulator display is an IP address--please note the number.

6) Download Git/GitHub client. For 10.6 (snow leopard) version of gihub client download from google groups

7) run git clone --recursive https://github.com/appcelerator/titanium_mobile_blackberry

8) BlackBerry has forked V8 for BB10 and made it available on GitHub (https://github.com/blackberry/v8). To build
the python scons tool is used. To build v8 using scons:
	Download macports
	sudo port install scones
	run source ~/Documents/bbndk/bbndk-env.sh

9) Now from the repo runtime directory run make this will build the BB10 v8 binaries.

10) Launch QNX Momentics IDE import tibb and test/tibbtest PROJECTS from the repo

11) Set the Build Configuration -> Simulator Debug. Also you need to setup the simulator using the Debug Configuration panel and give the target IP of the simulator that was noted in step 5.

12) Build tibb and test/tibbtest and then Debug As C/C++ Application.

