# Appcelerator Titanium Mobile
# Copyright (c) 2012 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License
# Please see the LICENSE included with this distribution for details.

from ConfigParser import ConfigParser

def write_app_properties(properties, path):
	"""Writes application properties to an INI file.

	properties - a list of tuples (key, value) for each property
	path - location of file to write properties
	"""
	config = ConfigParser()

	# Keep the property names case sensitive.
	config.optionxform = str

	# Store the application properties under the 'General' section.
	section = 'General'
	config.add_section(section)

	# All property values are expected to be valid JSON.
	for k, v in properties:
		config.set(section, k, v)

	# Dump configuration to the output file.
	with open(path, 'w') as outfile:
		config.write(outfile)

