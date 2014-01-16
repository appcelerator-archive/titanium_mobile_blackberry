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