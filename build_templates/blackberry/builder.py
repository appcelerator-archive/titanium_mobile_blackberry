#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Appcelerator Titanium Mobile
# Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License
# Please see the LICENSE included with this distribution for details.
#
# General builder script for staging, packaging, deploying,
# and debugging Titanium Mobile applications on Blackberry
#
import os, sys, shutil
from optparse import OptionParser

template_dir = os.path.abspath(os.path.dirname(sys._getframe(0).f_code.co_filename))
top_support_dir = os.path.dirname(template_dir) 
sys.path.append(top_support_dir)
sys.path.append(os.path.join(top_support_dir, 'common'))

from tilogger import TiLogger
from tiapp import TiAppXML
from blackberryndk import BlackberryNDK
from blackberry import Blackberry
from deltafy import Deltafy

class Builder(object):
	type2variantCpu = {'simulator' : ('o-g', 'x86'),
	                 'device' : ('o.le-v7-g', 'arm'),
	                 'deploy' : ('o.le-v7', 'arm')}

	def __init__(self, project_dir, type, ndk, useLogFile = False):
		self.top_dir = project_dir.rstrip(os.sep)
		self.type = type
		(self.variant, self.cpu) = Builder.type2variantCpu[type]
		self.ndk = ndk 
		self.project_tiappxml = os.path.join(self.top_dir, 'tiapp.xml')
		self.tiappxml = TiAppXML(self.project_tiappxml)
		self.name = self.tiappxml.properties['name']
		self.buildDir = os.path.join(self.top_dir, 'build', 'blackberry')
		self.project_deltafy = Deltafy(self.top_dir)

		if useLogFile:
			self.tiappxml = TiAppXML(self.project_tiappxml)
		else:
			# hide property output
			with open(os.devnull, 'w') as nul:
				oldStdout = sys.stdout
				sys.stdout = nul
				self.tiappxml = TiAppXML(self.project_tiappxml)
				sys.stdout = oldStdout
		self.name = self.tiappxml.properties['name']
		self.buildDir = os.path.join(self.top_dir, 'build', 'blackberry')

	def getPackage(self):
		return os.path.join(self.buildDir, self.cpu, self.variant, '%s.bar' % self.name)

	def run(self, ipAddress, password = None, debugToken = None):
		# TODO Mac: V8 runtime should be added and possibly a lot of other stuff

		retCode = self.build()
		if retCode != 0:
			return retCode
		info('Running')

		templates = os.path.join(template_dir,'templates')

		# Check if tiapp.xml changed since last run
		bar_descriptor_exists = os.path.exists(os.path.join(self.buildDir, 'bar-descriptor.xml'))
		tiapp_delta = self.project_deltafy.scan_single_file(self.project_tiappxml)
		tiapp_changed = tiapp_delta is not None

		if (tiapp_changed or not bar_descriptor_exists):
			# regenerate bar-descriptor.xml
			# TODO MAC: Add blackberry specific properties. Needs update in tiapp.py script
			print 'Creating bar-descriptor.xml'
			shutil.copy2(os.path.join(templates,'bar-descriptor.xml'), self.buildDir)
			newConfig = {
			'id':self.tiappxml.properties['id'],
			'appname':self.tiappxml.properties['name'],
			'platformversion':self.ndk.version,
			'description':(self.tiappxml.properties['description'] or 'not specified'),
			'version':(self.tiappxml.properties['version'] or '1.0'),
			'author':(self.tiappxml.properties['publisher'] or 'not specified'),
			'category':'core.games',
			'icon':'assets/%s' %(self.tiappxml.properties['icon'] or 'appicon.png'),
			'splashscreen':'assets/default.png'
			}
			try:
				Blackberry.renderTemplate(os.path.join(self.buildDir,'bar-descriptor.xml'), newConfig)
			except Exception, e:
				print >>sys.stderr, e
				sys.exit(1)

		# Change current directory to do relative operations
		os.chdir("%s" % self.buildDir)
		barPath = self.getPackage()
		savePath = os.path.join(self.buildDir, self.cpu, self.variant, self.name)
		retCode = self.ndk.package(barPath, savePath, self.name, self.type, debugToken)
		if retCode != 0:
			return retCode

		retCode = self.ndk.deploy(ipAddress, barPath, password)
		return retCode
	
	def build(self):
		info('Building')

		# Copy the tibbapp sample project
		if not os.path.exists(self.buildDir):
			os.makedirs(self.buildDir)
		sourcePath = os.path.join(template_dir,'tibbapp')
		for file in os.listdir(sourcePath):
			path = os.path.join(sourcePath, file)
			try:
				if os.path.isdir(path):
					dstDir = os.path.join(self.buildDir, file)
					if (os.path.exists(dstDir)):
						shutil.rmtree(dstDir)
					shutil.copytree(path, dstDir)
				else:
					shutil.copy2(path, self.buildDir)
			except Exception, e:
				print >> sys.stderr, e
				sys.exit(1)

		return self.ndk.build(self.buildDir, self.cpu, self.variant, self.name)

	def uninstallApp(self, ipAddress, password = None):
		return self.ndk.uninstallApp(ipAddress, self.getPackage(), password)

	def terminateApp(self, ipAddress, password = None):
		return self.ndk.terminateApp(ipAddress, self.getPackage(), password)

	def isAppRunning(self, ipAddress, password = None):
		return self.ndk.isAppRunning(ipAddress, self.getPackage(), password)

	def printExitCode(self, ipAddress, password = None):
		return self.ndk.printExitCode(ipAddress, self.getPackage(), password)

	def getFile(self, ipAddress, hostFile, deviceFile, password = None):
		return self.ndk.getFile(ipAddress, self.getPackage(), hostFile, deviceFile, password)

	def putFile(self, ipAddress, hostFile, deviceFile, password = None):
		return self.ndk.putFile(ipAddress, self.getPackage(), hostFile, deviceFile, password)

	def appLog(self, ipAddress, password = None):
		return self.ndk.appLog(ipAddress, self.getPackage(), password)

def info(msg):
	log.info(msg)

def debug(msg):
	log.debug(msg)

def warn(msg):
	log.warn(msg)

def trace(msg):
	log.trace(msg)
	
def error(msg):
	log.error(msg)
	
if __name__ == "__main__":

	# Setup script usage using optparse
	parser = OptionParser(usage='<command: build | run | uninstallApp | terminateApp | isAppRunning | printExitCode | getFile | putFile | appLog> -t TYPE -d PROJECT_PATH [-p NDK_PATH] [-i IP_ADDRESS] [-s DEVICE_PASSWORD] [--host_file HOST_FILE] [--device_file DEVICE_FILE]')

	commonGroup = parser.add_option_group('Common options')
	commonGroup.add_option('-t', '--type', choices=['simulator', 'device', 'deploy'], help='simulator | device | deploy', dest='type')
	commonGroup.add_option('-d', '--project_path', help='project directory path', dest='project_path')
	commonGroup.add_option('-p', '--ndk_path', help='blackberry ndk path', dest='ndk_path')

	runEtcGroup = parser.add_option_group('run, uninstallApp, terminateApp, isAppRunning, printExitCode, getFile, putFile, appLog options')
	runEtcGroup.add_option('-i', '--ip_address', help='(simulator | device) ip address', dest='ip_address')
	runEtcGroup.add_option('-s', '--device_password', help='(simulator | device) protection password', dest='device_password')

	runGroup = parser.add_option_group('Run options')
	runGroup.add_option('--debug_token', help='path to debug token file (required for --type device)')

	getPutFileGroup = parser.add_option_group('getFile, putFile options')
	getPutFileGroup.add_option('--host_file', help='file location on host')
	getPutFileGroup.add_option('--device_file', help='file location on device')

	(options, args) = parser.parse_args()
	if len(args) != 1:
		print parser.get_usage()
		sys.exit(1)

	buildUsage = 'Usage: %s build -t TYPE -d PROJECT_PATH [-p NDK_PATH]' %os.path.basename(sys.argv[0])
	runUsage = 'Usage: %s run -t TYPE -d PROJECT_PATH [-p NDK_PATH] -i IP_ADDRESS [-s DEVICE_PASSWORD] [--debug_token DEBUG_TOKEN]' %os.path.basename(sys.argv[0])
	uninstallAppUsage = 'Usage: %s uninstallApp -t TYPE -d PROJECT_PATH [-p NDK_PATH] -i IP_ADDRESS [-s DEVICE_PASSWORD]' %os.path.basename(sys.argv[0])
	terminateAppUsage = 'Usage: %s terminateApp -t TYPE -d PROJECT_PATH [-p NDK_PATH] -i IP_ADDRESS [-s DEVICE_PASSWORD]' %os.path.basename(sys.argv[0])
	isAppRunningUsage = 'Usage: %s isAppRunning -t TYPE -d PROJECT_PATH [-p NDK_PATH] -i IP_ADDRESS [-s DEVICE_PASSWORD]' %os.path.basename(sys.argv[0])
	printExitCodeUsage = 'Usage: %s printExitCode -t TYPE -d PROJECT_PATH [-p NDK_PATH] -i IP_ADDRESS [-s DEVICE_PASSWORD]' %os.path.basename(sys.argv[0])
	getFileUsage = 'Usage: %s getFile -t TYPE -d PROJECT_PATH [-p NDK_PATH] -i IP_ADDRESS [-s DEVICE_PASSWORD] --host_file HOST_FILE --device_file DEVICE_FILE' %os.path.basename(sys.argv[0])
	putFileUsage = 'Usage: %s putFile -t TYPE -d PROJECT_PATH [-p NDK_PATH] -i IP_ADDRESS [-s DEVICE_PASSWORD] --host_file HOST_FILE --device_file DEVICE_FILE' %os.path.basename(sys.argv[0])
	appLogUsage = 'Usage: %s appLog -t TYPE -d PROJECT_PATH [-p NDK_PATH] -i IP_ADDRESS [-s DEVICE_PASSWORD]' %os.path.basename(sys.argv[0])

	type = options.type and options.type.decode('utf-8')
	projectPath = options.project_path and options.project_path.decode('utf-8')
	ndkPath = options.ndk_path and options.ndk_path.decode('utf-8')
	ipAddress = options.ip_address and options.ip_address.decode('utf-8')
	devicePassword = options.device_password and options.device_password.decode('utf-8')
	debugToken = options.debug_token and options.debug_token.decode('utf-8')
	hostFile = options.host_file and options.host_file.decode('utf-8')
	deviceFile = options.device_file and options.device_file.decode('utf-8')

	useLogFile = False
	if args[0] == 'build':
		if type == None or projectPath == None:
			parser.error(buildUsage)
			sys.exit(1)
		useLogFile = True
	elif args[0] == 'run':
		if type == None or projectPath == None or ipAddress == None or (type == 'device' and debugToken == None):
			if type == 'device' and debugToken == None:
				print "--debug_token is required for --type device"
			parser.error(runUsage)
			sys.exit(1)
		useLogFile = True
	elif args[0] in ['uninstallApp', 'terminateApp', 'isAppRunning', 'printExitCode', 'appLog']:
		if type == None or projectPath == None or ipAddress == None:
			if args[0] == 'uninstallApp':
				parser.error(uninstallAppUsage)
			elif args[0] == 'terminateApp':
				parser.error(terminateAppUsage)
			elif args[0] == 'isAppRunning':
				parser.error(isAppRunningUsage)
			elif args[0] == 'printExitCode':
				parser.error(printExitCodeUsage)
			elif args[0] == 'appLog':
				parser.error(appLogUsage)
			sys.exit(1)
	elif args[0] in ['getFile', 'putFile']:
		if type == None or projectPath == None or ipAddress == None or hostFile == None or deviceFile == None:
			if args[0] == 'getFile':
				parser.error(getFileUsage)
			elif args[0] == 'putFile':
				parser.error(putFileUsage)
			sys.exit(1)
	else:
		print parser.get_usage()
		sys.exit(1)

	if useLogFile:
		log = TiLogger(os.path.join(os.path.abspath(os.path.expanduser(projectPath)), 'build_blackberry.log'))
	else:
		log = TiLogger(None, level = TiLogger.INFO)
	log.debug(" ".join(sys.argv))
	try:
		bbndk = BlackberryNDK(ndkPath, log = log)
	except Exception, e:
		print >>sys.stderr, e
		sys.exit(1)

	builder = Builder(projectPath, type, bbndk, useLogFile = useLogFile)

	retCode = 1
	if (args[0] == 'build'):
		retCode = builder.build()
	elif (args[0] == 'run'):
		retCode = builder.run(ipAddress, devicePassword, debugToken)
	elif (args[0] == 'uninstallApp'):
		retCode = builder.uninstallApp(ipAddress, devicePassword)
	elif (args[0] == 'terminateApp'):
		retCode = builder.terminateApp(ipAddress, devicePassword)
	elif (args[0] == 'isAppRunning'):
		retCode = builder.isAppRunning(ipAddress, devicePassword)
	elif (args[0] == 'printExitCode'):
		retCode = builder.printExitCode(ipAddress, devicePassword)
	elif (args[0] == 'getFile'):
		retCode = builder.getFile(ipAddress, hostFile, deviceFile, devicePassword)
	elif (args[0] == 'putFile'):
		retCode = builder.putFile(ipAddress, hostFile, deviceFile, devicePassword)
	elif (args[0] == 'appLog'):
		retCode = builder.appLog(ipAddress, devicePassword)
	sys.exit(retCode)
