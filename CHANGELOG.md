Release Notes
=============

New Features in this Release (3.1.0.v20130320125153)
----------------------------------------------------

WED MAR 20, 2013 12:51:53 PM PST

* Media - Audio and Sound Support including Data Streaming and File-system Data
* Titanium Studio Console Logging Support
* TextArea 
* ScrollView
* Map Annotation
* Tab Active Support
* Locale Support


Notes on Upgrading BlackBerry Golden Release for Map Annotation Support
-----------------------------------------------------------------------

This release has added support for Map Annotations. For developers using the Golden Release build or prior builds there are a few important steps that must be followed to make sure your application builds and runs. This only applies to the BlackBerry 10 release not the BlackBerry 10 Beta.

1) Download and install the latest BlackBerry SDK/NDK from http://developer.blackberry.com/native/downloads/#blackberry10.

2) Make sure to follow the instructions to upgrade the Golden Release builds. We have tested build 10.0.9.2372 but any later builds should be fine. The instructions are located at http://developer.blackberry.com/native/downloads/bb10/releasenotes_nativesdk.html. 

3) Download and install the simulator that matches the build number you downloaded. A list of simulators can be found at http://developer.blackberry.com/native/downloads/bb10allsimversions/

4) Edit the bbndk_env.sh file so the QNX_TARGET matched the updated build for example QNX_TARGET_VERSION=${QNX_TARGET_VERSION:=10_0_9_2372}. You can find the file at the root of the BlackBerry NDK folder. On OSX it's typically /Applications/bbndk/bbndk-env.sh, on Windows it's c://bbndk/bbndk-env.bat.


Notes on Application Orientation
--------------------------------

By default your application is fixed in portrait mode. You enable you app to auto rotate to the device orientation add the following to the tiapp.xml file in the project directory:

				<blackberry>
				    <orientation>auto</orientation>
				</blackberry>

The orientation element can be:

				- auto (allows full programatic control, empty orientation modes array = all orientations supported)
				- landscape
				- portrait
				- default (lock in the device's preferred orientation; phones -> portrait, tablets -> landscape)

Notes on Project Creation
-------------------------

When selecting multiple deploy targets, do not select Android. If Android is selected the BlackBerry project is not created. You can after project creation add Adroid using tiapp.xml.


New Features in this Release (3.1.0.v20130305173300)
----------------------------------------------------

TUE MAR 05, 2013 5:33:00 PM PST

* Maps Support  
* Keyboard Type Support  
* Orientation
* Support All Default Studio Templates
* Relative CommonJS Support and Scoping 
* Overlapping Window Support


Notes on Maps Support
---------------------

* Ti.Map.View has been added along with Ti.Map.Annotation. However, in this release Annotations will not work because support for Annotations is not available in the BlackBerry Golden Master build for the Z10. We are working with BlackBerry to get clarity on this issue.

New Features in this Release (3.1.0.v20130213122031)
----------------------------------------------------

* Database 
* WebView 
* 2.0 Layout Engine
* Touch Events
* Simple TableViewRow

Notes on Ti.UI.FILL
-------------------

When using Ti.UI.FILL on root windows, there is a pixel shift towards bottom on top and right on left side. This only appears on the simulator. This is a visual issue and does not effect application functionality.


Previous Releases
-----------------

* HTTPClient
* TCPSocket
* Window 
* AlertDialog
* View
* Button
* TextField 
* Label 
* TableView 
* ProgressBar
* Slider
* Titanium Studio Integration (Project creation, Deploy Simulator/Device, BlackBerry World Publish)


Remaining Functionality for Beta Release
----------------------------------------

* TableViewSection (TIMOB-8840)
* Geolocation (TIMOB-12234)
* Additional Window/TabGroup/ImageView/Blob and Network functionality (TIMOB-9605, TIMOB-9604, TIMOB-10275, TIMOB-10873, TIMOB-10083, TIMOB-10871)


Additional Functionality for GA Release
---------------------------------------

* Facebook (TIMOB-12225)
* Toolbar (TIMOB-12516)
* Filesystem (TIMOB-8580)
* XML (TIMOB-8592)
* ScrollableView (TIMOB-8831)
* Accelerometer (TIMOB-12233)
* Analytics (TIMOB-12236)
* Additional Media APIs
* Native modules (TIMOB-12224)
* VideoPlayer (TIMOB-12230)
* Contacts (TIMOB-12235)
* Search Bar (TIMOB-8833)


To get the latest Preview Release build, go to http://builds.appcelerator.com.s3.amazonaws.com/index.html and in the branch drop-down choose "master" then select the listed build. Subsequent builds will continue to be updated but the Preview Release has been tested to ensure basic functionality is working as expected. To see how to integrate the nightly with Titanium Studio visit http://preview.appcelerator.com/studio/bb. 


The TIMOB-* entries refer to tickets in our Jira bug and feature tracking system. The tickets are public and can be viewed at  https://jira.appcelerator.org/browse/TIMOB- ticket number.


