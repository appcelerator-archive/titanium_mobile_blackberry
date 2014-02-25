#!/bin/bash
source "/Applications/Momentics.app/bbndk-env_10_2_0_1155.sh";
make -j3 Simulator-Debug;
blackberry-nativepackager -package build/APP_NAME.bar bar-descriptor.xml -configuration Simulator-Debug;
blackberry-deploy -installApp -launchApp -device 192.168.228.129 -password "" build/APP_NAME.bar;

