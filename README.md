Titanium Mobile BlackBerry
==========================

Titanium Mobile BlackBerry is the Titanium platform support for the latest BlackBerry phone and tablet platform.

Current Status
--------------

* 2013-08-15 - _GA 3.1.2_

Release Notes
-------------

The Beta release is being made available to encourage developers to start building new applications and port existing Titanium applications to the new BlackBerry 10 Platform. 

In the last few months BlackBerry released its new operating system, BlackBerry 10 as well as the first BlackBerry 10 phone, the Z10. The phone has garnered critical praise for its technical chops, with a fast OS and well-integrated user interface. If you want to try out the Titanium BlackBerry beta but don't have access to a Z10, the simulator that ships with the BlackBerry 10 Native SDK is easy to use and represents the phone nicely.

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

-  Launch QNX Momentics IDE. From "File->Import->General->Existing Projects into Workspace" import src/tibb and test/native/tibbtest projects from titanium_mobile_blackberry. There is more information on using the IDE at http://developer.blackberry.com/native/documentation/bb10/com.qnx.doc.ide.userguide/topic/about_howtouseguide_.html.

-  Set the Build Configuration -> Simulator Debug. 

- Build src/tibb and test/native/tibbtest. When the builds are finished "Debug As" C/C++ Application. Also you need to setup the simulator using the Debug Configuration panel. Make sure to have the simulator running, you should see the simulator in the list of debug targets.


How to Update BlackBerry SDK to latest Nightly Build
---------------------------------------------------- 

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

How to Create, Test, and Publish BlackBerry Native Modules
----------------------------------------------------------

- Create Native Module:

	By running the module create command will you generate a stub BlackBerry module including documentation that you can use as a starting point to building your own Titanium BlackBerry extension. The project created is to be used by the QNX Momentics IDE (QDE). The IDE should have been installed when you installed the BlackBerry NDK. 

		titanium create -p blackberry --id <MODULE_ID> -n <MODULE_NAME> -t module

-  Build and Extend the Module:

	The QDE is the tool most often used to develop native BlackBerry 10 applications. Although the module stub generated during create has a Makefile that can be utilized by command-line tools, developers often find the Eclipse based IDE easier to use. To get started with BlackBerry 10 module development import the module project created above into the QDE. You will see a CPP source file with the same name as your <MODULE_NAME> this file is the entry point and the startup method is the hook to the BlackBerry SDK. When a module is first "required" into a running Titanium application the startup method is called. BlackBerry uses the V8 JavaScript runtime engine, and the generated stub has some simple example of extending the module by "plugging into" V8. To embedded V8 developers and Node.JS developers the code will be very familiar. Using the stub as a sample add your own BlackBerry 10 extensions and these will be available to Titanium applications. A good resource for how to work with the V8 runtime is the V8 Embedder's Guide https://developers.google.com/v8/embed.
 

- Testing and Debugging the Module:

	Not shipping with the BlackBerry SDK but available from GitHub is an application that the BlackBerry team uses for testing modules and developing the SDK. The app name is tibbtest it is located at https://github.com/appcelerator/titanium_mobile_blackberry/tree/master/test/apps/native/tibbtest like the generated module project tibbtest is a QDE project and should be imported into the QDE. You will also need the BlackBerry SDK located at https://github.com/appcelerator/titanium_mobile_blackberry/tree/master/src/tibb. The tibb project should also be imported into the QDE. The last step is to build and make sure the V8 library is available to the QDE. V8 ships with the Titanium BlackBerry SDK and you can adjust the common.mk in tibb, and tibbtest but it is probably easier to clone the Titanium BlackBerry SDK locally and follow the instructions on how to contribute to the BlackBerry SDK, instruction can be found at https://github.com/appcelerator/titanium_mobile_blackberry#how-to-setup-build-and-test-the-titanium-blackberry-sdk. Once you have your BlackBerry environment setup then:

	1) In the QDE tibbtest project's main.cpp file uncomment the #include "ReplaceWithModuleName.h",  and  tiRegisterModule("ReplaceWithModuleName", (TiModule*) new ReplaceWithModuleName()); lines and replace the ReplaceWithModuleName strings with you module name.

	2) Edit the common.mk with the path to your module library and the library name. There are comments in the file to assist you.

	3) In the tibbtest project edit the app.js JavaScript to "require" in your module and then call your exposed properties methods and hook any callbacks. See the native_module_test.js for an example of using the stub module generated in step one. Make sure to make your module header file available to the tibbtest project, probably easiest to just put a copy in the tibbtest project.

	4) Run the tibbtest application to simulator or device to test out your module. You can set breakpoints in your module to make debugging easier.

- Deploying the Module:

	When you created your module a QDE stub project was created and also templates of the collateral needed when "publishing" manually or to the Appcelerator Marketplace. You should look at the README file and documentation folder that was generated with your module to finish and publish your module. The stepa basically are:

 	1) Copy the module project folder to <PATH_TO_TITANIUM_SDK>/modules/blackberry/<MODULE_NAME>/<VERSION> make sure that the "built" module library is available in the x86 and arm folder.

 	2) In the application that will use the module make sure that there is a module entry:

 		<modules>
			<module platform="blackberry"><MODULE_NAME></module>
		</modules>


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
