/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 20013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 *
 * https://github.com/jindw/xmldom
 */


var domParser = require('/ti.xml/dom-parser');
Ti.API.info('loading xml module');
exports.parseString = function(_string) {
    return new domParser.DOMParser().parseFromString(_string,'text/xml');

}
 
exports.serializeToString = function(_xml) {
    return new domParser.XMLSerializer().serializeToString(_xml);
}

exports.apiName = 'Ti.XML';
exports.getApiName = function(){
	return exports.apiName;
}