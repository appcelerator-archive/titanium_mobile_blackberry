Titanium Mobile BlackBerry
==========================

Titanium Mobile BlackBerry is the Titanium platform support for the latest BlackBerry phone and tablet platform.

Current Status
--------------

* 2012-08-05 - _Development_

Release Notes
-------------

Notes: Currently the platform is in it's early stage of development and  missing many of the Titanium APIs. Please work closely with the BB team to get the missing APIs available for your application. The supported platforms for development are Mac 10.7 and greater and Windows7/8.

The latest release and API status notes are at [Release Notes](https://github.com/appcelerator/titanium_mobile_blackberry/blob/master/CHANGELOG.md).

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

1) Download and install VMware Fusion for Mac and if doing development on Microsoft Windows VMware Player. This is for the BlackBerry 10 simulator. We have tested using the most recent version 5.0.0.

2) From the BlackBerry developer site download and install the BlackBerry 10 Native SDK. The site is located at http://developer.blackberry.com/native/beta/download/. 

3) From the BlackBerry developer site download and install the BlackBerry 10 Dev Alpha Simulator. The site is located at http://developer.blackberry.com/native/beta/download/ (scroll a bit down the page).

4) Start up the simulator. On Mac it can be started by running the following command: BlackBerry10Simulator-BB10_0_09.vmwarevm. The command is typically located at ~/Virtual Machines.localized/BlackBerry10Simulator-BB10_0_09-386, though it will also install by default an alias on your desktop.

5) When the simulator starts up in the lower left side of the simulator display is an IP address--please note the number.

Note: If you are interested in writing Titanium Applications go to "How to Create Titanium Applications using the BlackBerry SDK" section below. If you are interested in native BlackBerry development to extend or contribute to the Titanium platform go to "How to Setup and Build the Titanium BlackBerry SDK (Native Platform Drop-In)"


How to Create Titanium Applications using the BlackBerry SDK
------------------------------------------------------------

1) Get the latest Titanium Studio at http://preview.appcelerator.com/studio/bb. The Studio team will be posting frequent updates.

2) Download and unzip the most recent BlackBerry Titanium SDK from http://preview.appcelerator.com/studio/bb. The BB team will be posting frequent updates.

3) In the Preferences panel under Titanium Studio > Preferences from the main menu select Titanium Studio and then Titanium. In the Titanium SDK Home box put the path of downloaded BlackBerry Titanium SDK. Goto the BlackBerry tab and in the BlackBerry NDK Home box put the path to the NDK downloaded from step 2 BlackBerry tools setup above. It by default lives in /Applications/bbndk on Mac. In the Simulator IP box enter the IP address you noted in step 5 BlackBerry tools setup above.

4) Use Titanium Studio to create a new BlackBerry project by select File->New. Pick a starter template. When done you can run your newly created project to the BlackBerry simulator by choosing Run As->BlackBerry Simulator.

5) To display Ti.APP.info for your application you need to use the command line / BB tools for now until Studio can read the logs. Here's the steps:

1. telnet <simulator ip>  (you can find the IP in the lower left corner of the simulator window)
2. login: username = devuser password = devuser
3. The log files are located at /accounts/1000/appdata/<your app id>/logs
4. You can use tail -f to stream log updates. Note you will need to re-start tail between application runs. 

6) The easiest way to target running on a device is to use Titanium Studio but you can also use command-line utilities to do the same activities as in Titanium Studio.

- Setup the BlackBerry 10 environment for code signing:

1. Register for a set of signing keys at https://www.blackberry.com/SignedKeys/codesigning.html (note the signing pin number)
2. After receiving the signing certs put them somewhere locally.
3. From a command window run "cd /Applications/bbndk/host_IP_ADDRESS/darwin/x86/usr/bin/
4. From a command window run "./blackberry-signer -register -csjpin SIGNING_PIN -storepass STORAGE_PASSWORD PATH_TO_RDK_KEYS.csj PATH_TO_PBDT_KEYS.csj"
5. From a command window run "./blackberry-debugtokenrequest -storepass STORE_PASSWORD -devicepin DEVICE_PIN debugtoken.bar"
6. From a command window run "./blackberry-deploy -installDebugToken PATH_TO_DEBUG_TOKEN/debugtoken.bar -device DEVICE_IP  -password DEVICE_PASSWORD


- Run the application on the BlackBerry 10 simulator:

PATH_TO_PLATFORM_SDK/blackberry/builder.py run -t simulator -d PATH_TO_PROJECT -p PATH_TO_BB_NDK --ip_address=SIMULATOR_IP --device_password=DEVICE_PASSWORD

- Run on a development device:

PATH_TO_PLATFORM_SDK/blackberry/builder.py run -t device -d PATH_TO_PROJECT -p PATH_TO_BB_NDK --ip_address=DEVICE_IP --device_password=DEVICE_PASSWORD --debug_token PATH_TO_DEBUG_TOKEN/debugtoken.bar 

- Build a release bar file and sign it so it can be published to 'App World' or deployed to device:

PATH_TO_PLATFORM_SDK/blackberry/builder.py" run -t distribute -d PATH_TO_PROJECT -p PATH_TO_BB_NDK --store_password STORE_PASSWORD --output_dir PATH_TO_SIGNED_BAR_FILE


How to Setup, Build and Test the Titanium BlackBerry SDK
---------------------------------------------------------

Note: The following instructions are for Mac. For Windows you will need cygwin or some other Unix on Windows utility.

1) Download the Git/GitHub client. 

2) From a command window (Terminal) execute "git clone --recursive https://github.com/appcelerator/titanium_mobile_blackberry"

3) BlackBerry has forked the V8 Javascript runtime for BlackBerry 10 and made it available on GitHub (https://github.com/blackberry/v8). To build: 

1. From a command window execute "source /Applications/bbndk/bbndk-env.sh"
2. Now from the repo runtime directory execute "make" this will build the BlackBerry 10 V8 binaries. If you get errors execute "make clean" first.

4) Launch QNX Momentics IDE and from "File->Import->General->Existing Projects into Workspace" import the tibb and test/tibbtest projects from the repo

5) Set the Build Configuration -> Simulator Debug. 

6) Build tibb and test/tibbtest. When the builds are finished "Debug As" C/C++ Application. Also you need to setup the simulator using the Debug Configuration panel. Make sure to have the simulator running, you should see the simulator in the list of debug targets.

How to Update BlackBerry SDK to latest Night Build
-------------------------------------------------- 

To get the latest prepackaged Titanium SDK including BlackBerry follow the steps below.

1. Goto http://builds.appcelerator.com.s3.amazonaws.com/index.html.
2. Choose "master" in dropdown.
3. Choose the desired build and then copy the link. 
4. Launch Titanium Studio and goto Help->Install Specific Titanium SDK and in the box past the link copied from step 3 above. Choose Finish.

Note: When using nightly builds and you have previous projects it is best if you do a project clean and build before running your application. Make sure to select the appropriate SDK in tiapp.xml.  

How to Build and Deploy the Titanium BlackBerry SDK (Native Platform Drop-In)
-----------------------------------------------------------------------------

1) To create the the blackberry drop-in, from the repo cli/commands execute "./create_sdk" this will create a build folder with the blackberry sdk folder in it. The blackberry folder can be dropped into a current Titanium SDK. The create_sdk script will call create_sdk.js which is a Node.js module and has a dependency on the wrench module. If you get an error about wrench, execute the command "npm install wrench".

Feedback
--------

Google Groups - https://groups.google.com/forum/?fromgroups#!forum/appc-ti-mobile-blackberry

Training Videos
---------------

https://appcelerator.webex.com/appcelerator/lsr.php?AT=pb&SP=EC&rID=63953422&rKey=6202ab1eb2cfb372

Legal
------

Titanium Mobile BlackBerry is developed by Appcelerator and the community and is Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
Titanium Mobile BlackBerry is made available under the Apache Public License, version 2.  See the [LICENSE](https://github.com/appcelerator/titanium_mobile_blackberry/blob/master/LICENSE) file for more information.
