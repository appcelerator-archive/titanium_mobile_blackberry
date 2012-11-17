#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Appcelerator Titanium Mobile
# Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License
# Please see the LICENSE included with this distribution for details.
#
# General script for interacting with a Blackberry device
#
import os, platform, subprocess, sys
from optparse import OptionParser

template_dir = os.path.abspath(os.path.dirname(sys._getframe(0).f_code.co_filename))
top_support_dir = os.path.dirname(template_dir)
sys.path.append(top_support_dir)
sys.path.append(os.path.join(top_support_dir, 'common'))

from tilogger import TiLogger
from tiapp import TiAppXML
from blackberryndk import BlackberryNDK
from builder import Builder

class DeviceManagement(object):
	def __init__(self, ndk):
		self.ndk = ndk

if __name__ == "__main__":

	# Setup script usage
	parser = OptionParser(usage='Usage: %s [--device DEVICE] [--device-password DEVICE_PASSWORD] [--ndk-path NDK_PATH]' % os.path.basename(sys.argv[0]))

	commonGroup = parser.add_option_group('Common options')
	commonGroup.add_option('--device', help = 'hostname or the IP address of the target device or simulator')
	commonGroup.add_option('--device-password', help = 'password for device')
	commonGroup.add_option('-p', '--ndk-path', help = 'blackberry ndk path')

	# Parse input and call apropriate function
	(options, args) = parser.parse_args()

	device = options.device and options.device.decode('utf-8')
	devicePassword = options.device_password and options.device_password.decode('utf-8')
	ndkPath = options.ndk_path and options.ndk_path.decode('utf-8')

	log = TiLogger(None, level = TiLogger.INFO)
	try:
		bbndk = BlackberryNDK(ndkPath, log = log)
	except Exception, e:
		print >>sys.stderr, e
		sys.exit(1)
	deviceManagement = DeviceManagement(bbndk)

	try:
		retCode = 1
		sys.exit(retCode)
	except Exception, e:
		print >>sys.stderr, e
		sys.exit(1)
