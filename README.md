Titanium Mobile BlackBerry
==========================

Titanium Mobile BlackBerry is the Titanium platform support for the latest BlackBerry phone and tablet platform.

Current Status
--------------

* 2013-06-17 - _BETA 3.1.1_

Release Notes
-------------

The Beta release is being made available to encourage developers to start building new applications and port existing Titanium applications to the new BlackBerry 10 Platform. 

In the last few months BlackBerry released its new operating system, BlackBerry 10 as well as the first BlackBerry 10 phone, the Z10. The phone has garnered critical praise for its technical chops, with a fast OS and well-integrated user interface. If you want to try out the Titanium BlackBerry beta but don't have access to a Z10, the simulator that ships with the BlackBerry 10 Native SDK is easy to use and represents the phone nicely.

In this beta release we believe there are the majority of features to get you started, including Alloy support, MapView, WebView, Database, Localization Support, and much, much more. 

The latest release and API status notes are at [Release Notes](https://github.com/appcelerator/titanium_mobile_blackberry/blob/master/CHANGELOG.md).


Folders & Files
---------------

create_sdk - script to build the BlackBerry SDK Drop-in

build_templates - templates for creating the native build drop-in

docs - docs to assist repository and project maintainers

test/unit - platform specific unit tests

test/apps - small focused apps to test platform features

runtime -  the Javascript runtime source

ci.sh - script that integrates with the Titanium build system can be ignored by developers

src - the cpp source files that make up the BlackBerry Titanium SDK


How to get Started with Titanium BlackBerry Development
-------------------------------------------------------

To get started with Titanium BlackBerry development refer to the Titanium Documentation at http://docs.appcelerator.com/titanium/latest/#!/guide/Installing_Platform_SDKs and choose Installing the BlackBerry NDK. 

If you are interested in writing Titanium Applications use the documentation, tutorials and quick start guides located at http://docs.appcelerator.com/titanium. If you are interested in native BlackBerry development to extend or contribute to the Titanium platform use this document.


How to Setup, Build and Test the Titanium BlackBerry SDK
---------------------------------------------------------

Note: The following instructions are for Mac. For Windows you will need cygwin or some other Unix on Windows utility.

- Download the Git/GitHub client. 

- Execute from a command window (Terminal): 

 		git clone --recursive https://github.com/appcelerator/titanium_mobile_blackberry

- BlackBerry has forked the V8 Javascript runtime for BlackBerry 10 and made it available on GitHub (https://github.com/blackberry/v8). To build execute the command:

		source /Applications/bbndk/bbndk-env.sh

The source command setups up the envrironment to do BlackBerry builds.

- To build the V8 binaries change directory to the titanium_mobile_blackberry/runtime folder you cloned above and execute:

		make clean
		make

To build V8 you will need to have Python and Scons available.

-  Launch QNX Momentics IDE. From "File->Import->General->Existing Projects into Workspace" import src/tibb and test/tibbtest projects from titanium_mobile_blackberry. There is more information on using the IDE at http://developer.blackberry.com/native/documentation/bb10/com.qnx.doc.ide.userguide/topic/about_howtouseguide_.html.

-  Set the Build Configuration -> Simulator Debug. 

- Build tibb and test/tibbtest. When the builds are finished "Debug As" C/C++ Application. Also you need to setup the simulator using the Debug Configuration panel. Make sure to have the simulator running, you should see the simulator in the list of debug targets.


How to Update BlackBerry SDK to latest Night Build
-------------------------------------------------- 

To get the latest prepackaged Titanium SDK including BlackBerry follow the steps below.

- Goto http://builds.appcelerator.com.s3.amazonaws.com/index.html.
- Choose "master" in dropdown.
- Choose the desired build and then copy the link. 
- Launch Titanium Studio and goto Help->Install Specific Titanium SDK and in the box paste the link copied from step 3 above. Choose Finish.

Note: When using nightly builds and you have previous projects it is best if you do a project clean and build before running your application. Make sure to select the appropriate SDK in tiapp.xml.  


How to Build and Deploy the Titanium BlackBerry SDK (Native Platform Drop-In)
-----------------------------------------------------------------------------

- To create the the blackberry drop-in, from titanium_mobile_blackberry execute: 

	./create_sdk

This will create a build folder with the blackberry sdk folder in it. The blackberry folder can be dropped into a current Titanium SDK. If and when you are ready to contribute use the instructions at https://help.github.com/articles/using-pull-requests to issue a 'pull request' and make sure you have signed the CLA as described in Contributing below.


Feedback
--------

Google Groups - https://groups.google.com/forum/?fromgroups#!forum/appc-ti-mobile-blackberry


Training Videos
---------------

https://appcelerator.webex.com/appcelerator/lsr.php?AT=pb&SP=EC&rID=63953422&rKey=6202ab1eb2cfb372


Contributing
-------------

Titanium is an open source project.  Titanium wouldn't be where it is now without contributions by the community. Please consider forking this repo to improve, enhance or fix issues. If you feel like the community will benefit from your fork, please open a pull request. 

To protect the interests of the Titanium contributors, Appcelerator, customers and end users we require contributors to sign a Contributors License Agreement (CLA) before we pull the changes into the main repository. Our CLA is simple and straightforward - it requires that the contributions you make to any Appcelerator open source project are properly licensed and that you have the legal authority to make those changes. This helps us significantly reduce future legal risk for everyone involved. It is easy, helps everyone, takes only a few minutes, and only needs to be completed once. 

[You can digitally sign the CLA](http://bit.ly/app_cla) online. Please indicate your email address in your first pull request so that we can make sure that will locate your CLA.  Once you've submitted it, you no longer need to send one for subsequent submissions.


Legal
------

Titanium Mobile BlackBerry is developed by Appcelerator and the community and is Copyright (c) 2012-2013 by Appcelerator, Inc. All Rights Reserved.
Titanium Mobile BlackBerry is made available under the Apache Public License, version 2.  See the [LICENSE](https://github.com/appcelerator/titanium_mobile_blackberry/blob/master/LICENSE) file for more information.
