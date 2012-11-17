#!/usr/bin/python
#
# An autodetection utility for the Blackberry NDK
#
# WARNING: the paths to qde, project and project name must not contain any
#          spaces for the tools to work correctly

import os, sys, platform, subprocess, pprint, shutil
from optparse import OptionParser

class Device:
	''' TODO Mac: Look at how qde works with sim for this class '''
	pass
#	def __init__(self, name, port=-1, emulator=False, offline=False):
#		self.name = name
#		self.port = port
#		self.emulator = emulator
#		self.offline = offline
#
#	def get_name(self):
#		return self.name
#
#	def get_port(self):
#		return self.port
#
#	def is_emulator(self):
#		return self.emulator
#
#	def is_device(self):
#		return not self.emulator
#
#	def is_offline(self):
#		return self.offline

class BlackberryNDK:
	def __init__(self, blackberryNdk, log = None):
		if platform.system() == 'Windows':
			self.packagerProgram = 'blackberry-nativepackager.bat'
			self.deployProgram = 'blackberry-deploy.bat'
		else:
			self.packagerProgram = 'blackberry-nativepackager'
			self.deployProgram = 'blackberry-deploy'

		self.log = log
		self.blackberryNdk = self._findNdk(blackberryNdk)
		if self.blackberryNdk is None:
			raise Exception('No Blackberry NDK directory found')
		self.version = self._findVersion()
		self._sourceEnvironment()
		self.qde = self._findQde()

	def getVersion(self):
		return self.version

	def getBlackberryNdk(self):
		return self.blackberryNdk

	def _findNdk(self, supplied):
		if supplied is not None:
			if os.path.exists(supplied):
				return supplied
			else:
				return None

		if platform.system() == 'Windows':
			default_dirs = ['C:\\bbndk']
		else:
			default_dirs = ['/Applications/bbndk', '/Developer/SDKs/bbndk', '/opt/bbndk', '~/bbndk', '~/opt/bbndk']

		for default_dir in default_dirs:
			if os.path.exists(default_dir):
				return default_dir
		return None

	def _findVersion(self):
		infoPath = os.path.join(self.blackberryNdk, 'install', 'info.txt')
		if os.path.exists(infoPath):
			try:
				f = open(infoPath, 'rU')
				for line in f:
					(key, val) = line.split('=', 1)
					if key == 'host':
						f.close()
						return val.strip()
			except IOError, e:
				print >>sys.stderr, e
		return None

	def _sourceEnvironment(self):
		if platform.system() == 'Windows':
			envFile = os.path.join(self.blackberryNdk, 'bbndk-env.bat')
			command = '%s ' % envFile + '&& set'
		else:
			envFile = os.path.join(self.blackberryNdk, 'bbndk-env.sh')
			command = ['bash', '-c', 'source %s && env' % envFile]

		try:
			proc = subprocess.Popen(command, stdout = subprocess.PIPE)
		except OSError, e:
			print >>sys.stderr, e
			return

		for line in proc.stdout:
			# This leaks memory on mac osx, see man putenv
			(key, _, value) = line.partition("=")
			os.environ[key] = value.strip()
		proc.communicate()
		self.log and self.log.debug('os.environ:\n' + pprint.pformat(dict(os.environ)))

	def _findQde(self):
		cmd = 'qde'
		qnxHost = os.environ.get('QNX_HOST')
		if qnxHost == None:
			return None
		if platform.system() == 'Windows':
			dir = os.path.join(qnxHost, 'usr', 'qde', 'eclipse')
			cmd += '.exe'
		elif platform.system() == 'Darwin':
			dir = os.path.join(qnxHost, 'usr', 'qde', 'eclipse', 'qde.app', 'Contents', 'MacOS')
		elif platform.system() == 'Linux':
			dir = os.path.join(qnxHost, 'usr', 'bin')
		qde = os.path.join(dir, cmd)
		if os.path.exists(qde):
			return qde
		return None

	def _run(self, command, echoCommand = True):
		assert type(command) is list
		try:
			# if no log, don't output
			if self.log == None:
				logfile = os.devnull
			else:
				logfile = self.log.getLogfile()
				if echoCommand:
					self.log.info('Command: ' + ' '.join(command))
			# if no logfile, output to stdout
			if logfile == None:
				subprocess.check_call(command)
				return 0
			else:
				with open(logfile, 'a') as f:
					# Need this write() or else subprocess will overwrite for some reason
					f.write('\n')
					subprocess.check_call(command, stdout = f, stderr = f)
					return 0
		except subprocess.CalledProcessError, cpe:
			print >>sys.stderr, cpe, cpe.output
			return cpe.returncode
		except OSError, e:
			print >>sys.stderr, e
			return e.errno

	def importProject(self, project, workspace = None):
		assert os.path.exists(project)
		if workspace is None:
			workspace = os.path.dirname(project)
		command = [self.qde, '-nosplash', '-application', 'org.eclipse.cdt.managedbuilder.core.headlessbuild', '-consoleLog', '-data', workspace, '-import', project]
		self._run(command)

	def build(self, project, cpu, variant, name):
		assert os.path.exists(project)
		templateDir = os.path.abspath(os.path.dirname(sys._getframe(0).f_code.co_filename))
		tiappName = 'TIAPP_NAME=' + name
		cpuList = 'CPULIST=' + cpu
		bbRoot = 'BB_ROOT=' + templateDir
		variant = 'VARIANTLIST=' + ('g' if variant.endswith('-g') else '')
		oldPath = os.getcwd()
		os.chdir(project)
		command = ['make', tiappName, cpuList, bbRoot, variant]
		retCode = self._run(command)
		os.chdir(oldPath)
		return retCode

	def package(self, package, appFile, projectName, type, debugToken, isUnitTest = False):
		templateDir = os.path.abspath(os.path.dirname(sys._getframe(0).f_code.co_filename))
		buildDir = os.path.abspath(os.path.join(appFile, '..', '..', '..'))
		projectDir = os.path.abspath(os.path.join(buildDir, '..', '..'))

		# Copy the framework's JavaScript
		frameworkDir = os.path.join(buildDir, 'framework')
		if os.path.exists(frameworkDir):
			shutil.rmtree(frameworkDir)
		shutil.copytree(os.path.join(templateDir, 'tibb', 'titanium', 'javascript'), frameworkDir)

		# Copy all needed resources to assets
		assetsDir = os.path.join(buildDir, 'assets')
		resourcesDir = os.path.join(projectDir, 'Resources')
		blackberryResourcesDir = os.path.join(resourcesDir, 'blackberry')
		if os.path.exists(assetsDir):
			shutil.rmtree(assetsDir)
		os.makedirs(assetsDir)
		if os.path.exists(resourcesDir):
			for entry in os.listdir(resourcesDir):
				fullEntry = os.path.join(resourcesDir, entry)
				if os.path.isdir(fullEntry):
					if entry != "android" and entry != "iphone" and entry != "mobileweb" and entry != "blackberry":
						shutil.copytree(fullEntry, os.path.join(assetsDir, entry))
				else:
					shutil.copy2(fullEntry, os.path.join(assetsDir, entry))

		# copy the blackberry dir after so it will overwrite, if necessary
		if os.path.exists(blackberryResourcesDir):
			for root, dirs, files in os.walk(blackberryResourcesDir):
				destRoot = root.replace(blackberryResourcesDir, assetsDir, 1)
				if not os.path.exists(destRoot):
					os.makedirs(destRoot)
				for filename in files:
					fullFilenameSrc = os.path.join(root, filename)
					fullFilenameDest = fullFilenameSrc.replace(blackberryResourcesDir, assetsDir, 1)
					shutil.copy2(fullFilenameSrc, fullFilenameDest)

		# TODO: minimize .js files in Release mode

		command = [self.packagerProgram, '-package', package, 'bar-descriptor.xml', '-e', appFile, projectName, 'assets', 'framework']
		if isUnitTest:
			command.append('icon.png')
		if type != 'deploy':
			command.append('-devMode')
		if debugToken != None:
			command.extend(['-debugToken', debugToken])
		return self._run(command)

	def deploy(self, deviceIP, package, password = None):
		command = [self.deployProgram, '-installApp', '-launchApp', '-device', deviceIP, '-package', package]
		if password != None:
			command.append('-password')
			command.append(password)
		return self._run(command)

	def uninstallApp(self, deviceIP, package, password = None):
		command = [self.deployProgram, '-uninstallApp', '-device', deviceIP, '-package', package]
		if password != None:
			command.append('-password')
			command.append(password)
		return self._run(command)

	def terminateApp(self, deviceIP, package, password = None):
		command = [self.deployProgram, '-terminateApp', '-device', deviceIP, '-package', package]
		if password != None:
			command.append('-password')
			command.append(password)
		return self._run(command)

	def isAppRunning(self, deviceIP, package, password = None):
		command = [self.deployProgram, '-isAppRunning', '-device', deviceIP, '-package', package]
		if password != None:
			command.append('-password')
			command.append(password)
		return self._run(command, echoCommand = False)

	def printExitCode(self, deviceIP, package, password = None):
		command = [self.deployProgram, '-printExitCode', '-device', deviceIP, '-package', package]
		if password != None:
			command.append('-password')
			command.append(password)
		return self._run(command, echoCommand = False)

	def getFile(self, deviceIP, package, hostFile, deviceFile, password = None):
		command = [self.deployProgram, '-getFile', deviceFile, hostFile, '-device', deviceIP, '-package', package]
		if password != None:
			command.append('-password')
			command.append(password)
		return self._run(command)

	def putFile(self, deviceIP, package, hostFile, deviceFile, password = None):
		command = [self.deployProgram, '-putFile', hostFile, deviceFile, '-device', deviceIP, '-package', package]
		if password != None:
			command.append('-password')
			command.append(password)
		return self._run(command)

	def _isAppRunning(self, deviceIP, package, password = None):
		command = [self.deployProgram, '-isAppRunning', '-device', deviceIP, '-package', package]
		if password != None:
			command.append('-password')
			command.append(password)
		output = subprocess.check_output(command)
		return output.find("result::true") != -1

	def _printAppLog(self, deviceIP, package, password = None):
		hostFile = "-"
		deviceFile = "logs/log"
		command = [self.deployProgram, '-getFile', deviceFile, hostFile, '-device', deviceIP, '-package', package]
		if password != None:
			command.append('-password')
			command.append(password)
		return self._run(command)

	def appLog(self, deviceIP, package, password = None):
		import time
		while self._isAppRunning(deviceIP, package, password):
			time.sleep(2)
		self._printAppLog(deviceIP, package, password)

	def buildTibb(self, tibbPath, buildType):
		assert os.path.exists(tibbPath)
		oldPath = os.getcwd()
		os.chdir(tibbPath)
		command = ['make', buildType]
		retCode = self._run(command)
		os.chdir(oldPath)
		return retCode

def __runUnitTests(ipAddress = None):
	# on windows the double dirname need to be done on 2 lines
	baseDir = os.path.abspath(os.path.dirname(sys.argv[0]))
	baseDir = os.path.dirname(baseDir)
	sys.path.append(os.path.join(baseDir, 'common'))
	from tiunittest import UnitTest
	import tempfile
	# if there are spaces in the temp directory, try to use the working directory instead
	if tempfile.gettempdir().find(' ') != -1:
		if os.getcwd().find(' '):
			print 'Please run the unit tests from a directory with no spaces'
			sys.exit(1)
		else:
			tempfile.tempdir = os.getcwd()
			os.environ['TEMP'] = tempfile.tempdir
			os.environ['TMP'] = tempfile.tempdir
			os.environ['TMPDIR'] = tempfile.tempdir
	import shutil

	print '\nRunning Unit Tests...\n'

	with UnitTest('Test source environement..'):
		ndk._sourceEnvironment()
		for key in ['QNX_TARGET', 'QNX_HOST', 'QNX_CONFIGURATION', 'MAKEFLAGS', 'PATH']:
			assert key in os.environ

	with UnitTest('Test find qde..'):
		qde = ndk._findQde()
		assert os.path.exists(qde)

	with UnitTest('Test import project with workspace..'):
		workspace = tempfile.mkdtemp()
		projectSrc = os.path.join(ndk.blackberryNdk, 'target', 'qnx6', 'usr', 'share', 'samples', 'ndk', 'HelloWorldDisplay')
		projectName = 'HelloWorldDisplayMakefile'
		project = os.path.join(workspace, projectName)
		shutil.copytree(projectSrc, project)
		ndk.importProject(project, workspace)
		passed = os.path.exists(os.path.join(workspace, '.metadata'))
		shutil.rmtree(workspace)
		assert passed

	with UnitTest('Test import project no workspace..'):
		workspace = tempfile.mkdtemp()
		projectSrc = os.path.join(ndk.blackberryNdk, 'target', 'qnx6', 'usr', 'share', 'samples', 'ndk', 'HelloWorldDisplay')
		project = os.path.join(workspace, projectName)
		shutil.copytree(projectSrc, project)
		ndk.importProject(project)
		passed = os.path.exists(os.path.join(workspace, '.metadata'))
		assert passed

	with UnitTest('Test build project (x86)..'):
		cpu = 'x86'
		ndk.build(project, cpu, projectName)
		assert os.path.exists(os.path.join(project, 'x86', 'o', projectName))
		assert os.path.exists(os.path.join(project, 'x86', 'o-g', projectName))

	oldDir = os.getcwd()
	os.chdir(project)
	with UnitTest('Test package project..'):
		cpu = 'x86'
		variant = 'o-g'
		barPath = os.path.join(project, cpu, variant, '%s.bar' % projectName)
		savePath = os.path.join(project, cpu, variant, projectName)
		assert 0 == ndk.package(barPath, savePath, os.path.basename(project), 'simulator', None, isUnitTest = True)
		assert os.path.exists(barPath)
	os.chdir(oldDir)

	if ipAddress != None:
		with UnitTest('Test deploy project to simulator..'):
			assert 0 == ndk.deploy(ipAddress, barPath)

	with UnitTest('Test build project (arm)..'):
		cpu = 'arm'
		ndk.build(project, cpu, projectName)
		assert os.path.exists(os.path.join(project, 'arm', 'o.le-v7', projectName))
		assert os.path.exists(os.path.join(project, 'arm', 'o.le-v7-g', projectName))

	shutil.rmtree(workspace)

	print '\nFinished Running Unit Tests'
	UnitTest.printDetails()


if __name__ == "__main__":

	# Setup script usage using optparse
	parser = OptionParser(usage='[ndk_path] [-t] [--ip_address IP ADDRESS]', description='Prints the NDK directory and version')

	parser.add_option('-t', '--test', help='run unit tests', action='store_true', dest='test')
	parser.add_option('--ip_address', help='simulator IP address for unit tests', dest='ip_address')
	(options, args) = parser.parse_args()

	try:
		ndk = BlackberryNDK(args[0].decode('utf-8') if len(args) != 0 else None)
		print "BLACKBERRY_NDK=%s" % ndk.getBlackberryNdk()
		print "BLACKBERRY_NDK_VERSION=%s" % ndk.getVersion()
	except Exception, e:
		print >>sys.stderr, e
		sys.exit(1)

	if options.test:
		__runUnitTests(options.ip_address.decode('utf-8') if options.ip_address != None else None)
