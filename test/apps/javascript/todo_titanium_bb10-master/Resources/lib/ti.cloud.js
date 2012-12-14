/**
 * @preserve
 * Titanium Cloud Module
 *
 * This module is used across three distinct platforms (iOS, Android, and Mobile Web), each with their own architectural
 * demands upon it.
 *
 * Appcelerator Titanium is Copyright (c) 2009-2010 by Appcelerator, Inc.
 * and licensed under the Apache Public License (version 2)
 */

defineCloud(exports);

function defineCloud(Cloud) {
/*!
 * BedFrame v0.4 by Dawson Toth
 * A framework for exposing RESTful APIs to Appcelerator Titanium Mobile.
 *
 * This framework is designed for REST APIs with the following characteristics:
 *  1) Contains many different methods, in many different namespaces.
 *  2) Method signatures are all very similar.
 *
 * You probably don't need this framework if:
 *  1) You only want to expose a couple methods.
 *
 * To learn more about this framework, or get the latest version, check out:
 *  https://github.com/dawsontoth/BedFrame
 *
 * NO WARRANTY EXPRESSED OR IMPLIED. USE AT YOUR OWN RISK.
 */

/**
 * This can be used as a module or as an included file. If you are including it (or inlining it) in to another module,
 * then you should replace the below with simply var BedFrame = {}, removing the exports ternary expression.
 */
var BedFrame = {};

/**
 * Default property type that results in only the latest specified value being used (that is, the deepest child's value
 * will be used over any of its parents). Particularly useful for specifying default values that most children use, and
 * then overriding those default values on exceptional children.
 */
BedFrame.PROPERTY_TYPE_ONLY_LATEST = 0;
/**
 * Property type that results in child values equating to their parent value plus their own, separated by a forward
 * slash. Particularly useful for creating a URL hierarchy.
 */
BedFrame.PROPERTY_TYPE_SLASH_COMBINE = 1;
/**
 * Property type that results in a parent value not propogating to its children.
 */
BedFrame.PROPERTY_TYPE_IGNORE = 2;

/**
 * Recursively builds a full API on the target object, as defined in the api object. Properties will be added to the target object,
 * but the object reference itself will not be altered. This means you can safely "build" on a CommonJS exports object.
 *
 * @param target The object that the API will be created in.
 * @param api The specifications for the API you want to expose through objects. Read "THE API OBJECT" in readme.md to find out more.
 */
BedFrame.build = function bedFrameTransformObject(target, api) {
    // Save a reference to the children property of the current segment of the API.
    var children = api.children || [];

    // Iterate over every child to set up its API.
    for (var c in children) {
        // Avoid prototyped members.
        if (!children.hasOwnProperty(c))
            continue;
        // Create a shorter reference to the present child.
        var child = children[c];
        // Determine the present property types, or default to an empty object.
        // (We will pass this variable down in the next step; propertyTypes is itself by default typed ONLY_LATEST).
        var propertyTypes = child.propertyTypes || api.propertyTypes || {};
        // Don't pass down children (that causes an infinite recursion).
        propertyTypes.children = BedFrame.PROPERTY_TYPE_IGNORE;

        // Iterate over every member of the current segment of the API.
        for (var o in api) {
            // Avoid prototyped members and children.
            if (!api.hasOwnProperty(o))
                continue;
            // Based on the property type specified for this API, cascade property down from parent to child.
            switch (propertyTypes[o] || BedFrame.PROPERTY_TYPE_ONLY_LATEST) {
                case BedFrame.PROPERTY_TYPE_ONLY_LATEST:
                    // ONLY_LATEST results in child taking precedence over the parent, completely replacing the value.
                    child[o] = child[o] === undefined ? api[o] : child[o];
                    break;
                case BedFrame.PROPERTY_TYPE_SLASH_COMBINE:
                    // SLASH_COMBINE results in the child ending up with a slash-separated-value from the top most
                    // parent to the present child, where elements without a value are ignored (there won't be any
                    // double slashes in the computed value).
                    var parts = [];
                    if (api[o])
                        parts.push(api[o]);
                    if (child[o])
                        parts.push(child[o]);
                    child[o] = parts.join('/');
                    break;
            }
        }

        // If the current child specifies the method property, and does not have any children, it's an endpoint and
        // needs to be set up as a method. Inject it in to the target.
        if (child.method && !child.children) {
            target[child.method] = (function (child) {
                return function () {
                    // Executors are designed to work based off of their context. Act upon the child, which is a mixed
                    // down result of its parent, and its parent's parent, and so on.
                    return child.executor.apply(child, arguments);
                };
            })(child);
        }
        // Otherwise, inject the new property in to the target, and recurse upon the sub-segment of the API.
        else if (child.property) {
            bedFrameTransformObject(target[child.property] = {}, child);
        }
    }
};
/**
 * Throws an exception if an argument has not been provided, or is not of the expected type.
 * @param name The string display name of the argument (such as 'data')
 * @param arg The actual provided argument
 * @param type The string value of the expected argument type (such as 'object' or 'string').
 */
function requireArgument(name, arg, type) {
    if (arg === undefined) {
        throw 'Argument ' + name + ' was not provided!';
    }
    if (typeof(arg) != type) {
        throw 'Argument ' + name + ' was an unexpected type! Expected: ' + type + ', Received: ' + typeof(arg);
    }
}

/**
 * Calls the ACS REST API with the provided data, executing the provided callback when we get a response.
 * @param data
 * @param callback
 */
function defaultExecutor(data, callback) {
    requireArgument('data', data, 'object');
    requireArgument('callback', callback, 'function');
    propagateRestNames(this);
    if (!this.url) {
        this.url = this.restNamespace + '/' + this.restMethod + '.json';
    }
    var secure = Cloud.useSecure == undefined ? true : Cloud.useSecure;
    if (Cloud.debug) {
        Ti.API.info('ACS Request: { ' +
            'url: "' + this.url + '", ' +
            'verb: "' + this.verb + '", ' +
            'secure: ' + (secure ? 'YES' : 'NO') + ', ' +
            'data: ' + JSON.stringify(data) + ' ' +
            '})');
    }
    ACS.send(this.url, this.verb, data, secure,
        function handleResponse(evt) {
            if (!callback) {
                return;
            }
            var response = evt.response || {};
            if (evt.meta && evt.meta.status == 'ok') {
                response.success = true;
                response.error = false;
                response.meta = evt.meta;
                if (Cloud.debug) {
                    Ti.API.info(JSON.stringify(response));
                }
            }
            else {
                response.success = false;
                response.error = true;
                response.code = evt.meta ? evt.meta.code : evt.statusCode;
                response.message = evt.meta ? evt.meta.message : (evt.message || evt.statusText);
                if (Cloud.debug) {
                    Ti.API.error(response.code + ': ' + response.message);
                }
            }
            callback(response);
        }
    );
}

function dataOptionalExecutor() {
    defaultExecutor.call(this,
        arguments.length == 2 ? arguments[0] : {},
        arguments.length == 2 ? arguments[1] : arguments[0]
    );
}

function dataExcludedExecutor(callback) {
    defaultExecutor.call(this, {}, callback);
}

function classnameRequiredExecutor(data, callback) {
    var savedClassName;
    if (data && typeof(data) == 'object') {
        requireArgument('data.classname', data.classname, 'string');
        propagateRestNames(this);
        this.url = this.restNamespace + '/' + data.classname + '/' + this.restMethod + '.json';
        // We don't want the class name passed as a variable, so delete it from data.
        savedClassName = data.classname;
        delete data.classname;
    }
    defaultExecutor.call(this, data, callback);
    // Now restore it to the data object so that we don't corrupt the object for subsequent calls.
    data.classname = savedClassName;
}

function propagateRestNames(context) {
    if (!context.restNamespace) {
        context.restNamespace = context.property.toLowerCase();
    }
    if (!context.restMethod) {
        context.restMethod = context.method.toLowerCase();
    }
}

function hasStoredSession() {
	Ti.API.warn("Cloud.hasStoredSession has been deprecated. Use Cloud.sessionId property");
	return ACS.hasStoredSession();
}

function retrieveStoredSession() {
	Ti.API.warn("Cloud.retrieveStoredSession has been deprecated. Use Cloud.sessionId property");
	return ACS.retrieveStoredSession();
}

function secureAuthExecutor(data, callback) {
    requireArgument('callback', callback, 'function');

	var options = {};
	options.useSecure = Cloud.useSecure == undefined ? true : Cloud.useSecure;
	options.params = data || {};
	options.params.cb = function handleResponse(evt) {
		if (!callback) {
			return;
		}
		var response = evt || {};
		if (evt && evt.access_token) {
			response.success = true;
			response.error = false;
			if (Cloud.debug) {
				Ti.API.info("ACS Token: " + evt.access_token + " Expires: " + evt.expires_in);
			}
		} else {
			response.success = false;
			response.error = true;
			response.message = "Cancelled";
			if (Cloud.debug) {
				Ti.API.error("ACS " + response.message);
			}
		}
		callback(response);
	};

	ACS.secureSend(this.method, options);
}

function dataOptionalSecureAuthExecutor() {
    secureAuthExecutor.call(this,
        arguments.length == 2 ? arguments[0] : {},
        arguments.length == 2 ? arguments[1] : arguments[0]
    );
}

function checkStatus() {
	return ACS.checkStatus();
}

BedFrame.build(Cloud, {
    verb: 'GET',
    executor: defaultExecutor,
    children: [
	    // Top level methods not associated with a namespace
	    { method: 'hasStoredSession', executor: hasStoredSession },
	    { method: 'retrieveStoredSession', executor: retrieveStoredSession },
        {
            property: 'ACLs',
            children: [
                { method: 'create', verb: 'POST' },
                { method: 'update',  verb: 'PUT' },
                { method: 'show' },
                { method: 'remove', restMethod: 'delete', verb: 'DELETE' },
                { method: 'addUser', restMethod: 'add', verb: 'POST' },
                { method: 'removeUser', restMethod: 'remove', verb: 'DELETE' },
                { method: 'checkUser', restMethod: 'check' }
            ]
        },
        {
            property: 'Chats',
            children: [
                { method: 'create', verb: 'POST' },
                { method: 'query' },
                { method: 'getChatGroups', restMethod: 'get_chat_groups', executor: dataOptionalExecutor }
            ]
        },
        {
            property: 'Checkins',
            children: [
                { method: 'create', verb: 'POST' },
                { method: 'query', executor: dataOptionalExecutor },
                { method: 'show' },
                { method: 'remove', restMethod: 'delete', verb: 'DELETE' }
            ]
        },
        {
            property: 'Clients',
            children: [
                { method: 'geolocate', executor: dataOptionalExecutor }
            ]
        },
        {
            property: 'Objects',
            executor: classnameRequiredExecutor,
            children: [
                { method: 'create', verb: 'POST' },
                { method: 'show' },
                { method: 'update', verb: 'PUT' },
                { method: 'remove', restMethod: 'delete', verb: 'DELETE' },
                { method: 'query' }
            ]
        },
        {
            property: 'Emails',
            restNamespace: 'custom_mailer',
            children: [
                { method: 'send', verb: 'POST', restMethod: 'email_from_template' }
            ]
        },
        {
	        property: 'Events',
	        children: [
		        { method: 'create', verb: 'POST' },
		        { method: 'show' },
		        { method: 'showOccurrences', restMethod: 'show/occurrences' },
		        { method: 'query', executor: dataOptionalExecutor },
		        { method: 'queryOccurrences', restMethod: 'query/occurrences', executor: dataOptionalExecutor },
		        { method: 'search', executor: dataOptionalExecutor},
		        { method: 'searchOccurrences', restMethod: 'search/occurrences', executor: dataOptionalExecutor },
		        { method: 'update', verb: 'PUT' },
		        { method: 'remove', restMethod: 'delete', verb: 'DELETE' }
	        ]
        },
        {
	        property: 'Files',
	        children: [
		        { method: 'create', verb: 'POST' },
		        { method: 'query', executor: dataOptionalExecutor },
		        { method: 'show' },
		        { method: 'update', verb: 'PUT' },
		        { method: 'remove', restMethod: 'delete', verb: 'DELETE' }
	        ]
        },
        {
	        property: "Friends",
	        children: [
		        { method: 'add', verb: 'POST' },
		        { method: 'requests', executor: dataOptionalExecutor },
		        { method: 'approve', verb: 'PUT'},
		        { method: 'remove', verb: 'DELETE'},
		        { method: 'search' }
	        ]
        },
        {
            property: 'KeyValues',
            children: [
                { method: 'set', verb: 'PUT' },
                { method: 'get' },
                { method: 'append', verb: 'PUT' },
                { method: 'increment', restMethod: 'incrby', verb: 'PUT' },
                { method: 'remove', restMethod: 'delete', verb: 'DELETE' }
            ]
        },
        {
	        property: 'Messages',
	        children: [
		        { method: 'create', verb: 'POST' },
		        { method: 'reply', verb: 'POST' },
		        { method: 'show' },
		        { method: 'showInbox', restMethod: 'show/inbox', executor: dataOptionalExecutor },
		        { method: 'showSent', restMethod: 'show/sent', executor: dataOptionalExecutor },
		        { method: 'showThreads', restMethod: 'show/threads', executor: dataOptionalExecutor },
		        { method: 'showThread', restMethod: 'show/thread' },
		        { method: 'remove', restMethod: 'delete', verb: 'DELETE' },
		        { method: 'removeThread', restMethod: 'delete/thread', verb: 'DELETE' }
	        ]
        },
        {
            property: 'Photos',
            children: [
                { method: 'create', verb: 'POST' },
                { method: 'show' },
                { method: 'search' },
                { method: 'query', executor: dataOptionalExecutor },
                { method: 'update', verb: 'PUT' },
                { method: 'remove', restMethod: 'delete', verb: 'DELETE' }
            ]
        },
        {
            property: 'PhotoCollections',
            restNamespace: 'collections',
            children: [
                { method: 'create', verb: 'POST' },
                { method: 'show' },
                { method: 'update', verb: 'PUT' },
                { method: 'search' },
                { method: 'showSubcollections', restMethod: 'show/subcollections' },
                { method: 'showPhotos', restMethod: 'show/photos' },
                { method: 'remove', restMethod: 'delete', verb: 'DELETE' }
            ]
        },
        {
            property: 'Places',
            children: [
                { method: 'create', verb: 'POST' },
                { method: 'search', executor: dataOptionalExecutor },
                { method: 'show' },
                { method: 'update', verb: 'PUT' },
                { method: 'remove', restMethod: 'delete', verb: 'DELETE' },
                { method: 'query', executor: dataOptionalExecutor }
            ]
        },
        {
            property: 'Posts',
            children: [
                { method: 'create', verb: 'POST' },
                { method: 'show' },
                { method: 'query', executor: dataOptionalExecutor },
                { method: 'update', verb: 'PUT' },
                { method: 'remove', restMethod: 'delete', verb: 'DELETE' }
            ]
        },
        {
            property: 'PushNotifications',
            restNamespace: 'push_notification',
            verb: 'POST',
            children: [
                { method: 'subscribe' },
                { method: 'unsubscribe', verb: 'DELETE' },
                { method: 'notify' }
            ]
        },
        {
            property: 'Reviews',
            children: [
                { method: 'create', verb: 'POST' },
                { method: 'show' },
                { method: 'query' },
                { method: 'update', verb: 'PUT' },
                { method: 'remove', restMethod: 'delete', verb: 'DELETE' }
            ]
        },
        {
            property: 'SocialIntegrations',
            restNamespace: 'users',
            children: [
                { method: 'externalAccountLogin', restMethod: 'external_account_login', verb: 'POST' },
                { method: 'externalAccountLink', restMethod: 'external_account_link', verb: 'POST' },
                { method: 'externalAccountUnlink', restMethod: 'external_account_unlink', verb: 'DELETE' },
                { method: 'searchFacebookFriends', restNamespace: 'social', restMethod: 'facebook/search_friends',
                    executor: dataExcludedExecutor
                }
            ]
        },
        {
            property: 'Statuses',
            children: [
                { method: 'create', verb: 'POST' },
                { method: 'search' },
                { method: 'query', executor: dataOptionalExecutor }
            ]
        },
        {
            property: 'Users',
            children: [
                { method: 'create', verb: 'POST' },
                { method: 'login', verb: 'POST' },
                { method: 'show' },
                { method: 'showMe', restMethod: 'show/me', executor: dataExcludedExecutor },
                { method: 'search', executor: dataOptionalExecutor },
                { method: 'query', executor: dataOptionalExecutor },
                { method: 'update', verb: 'PUT' },
                { method: 'logout',
                    executor: function (callback) {
                        defaultExecutor.call(this, {}, function (evt) {
                            ACS.reset();
                            callback(evt);
                        });
                    }
                },
                { method: 'remove', restMethod: 'delete', verb: 'DELETE',
                    executor: function () {
                        var orig = arguments;
                        defaultExecutor.call(this,
                            orig.length == 2 ? orig[0] : {},
                            function (evt) {
                                ACS.reset();
                                (orig.length == 2 ? orig[1] : orig[0])(evt);
                            }
                        );
                    }
                },
                { method: 'requestResetPassword', restMethod: 'request_reset_password' },
	            { method: 'secureCreate', executor: dataOptionalSecureAuthExecutor },
	       	    { method: 'secureLogin', executor: dataOptionalSecureAuthExecutor },
	            { method: 'secureStatus', executor: checkStatus }
            ]
        }
    ]
});
function injectAnalytics(data, url) {
    if (Ti.App.analytics) {
        var obj = data.analytics || {};
        obj.id = Ti.Platform.createUUID();
        if (Ti.Platform.id) {
            obj.mid = Ti.Platform.id;
        }
        obj.aguid = Ti.App.guid;
        obj.event = 'cloud.' + url.replace(/\//g, '.').replace(/\.json/, '');
        obj.deploytype = Ti.App.deployType || 'development';
        obj.sid = Ti.App.sessionId;
        data['ti_analytics'] = JSON.stringify(obj);
    }
}
/**
 * @preserve
 * Copyright 2008 Netflix, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* Here's some JavaScript software for implementing OAuth.

 This isn't as useful as you might hope.  OAuth is based around
 allowing tools and websites to talk to each other.  However,
 JavaScript running in web browsers is hampered by security
 restrictions that prevent code running on one website from
 accessing data stored or served on another.

 Before you start hacking, make sure you understand the limitations
 posed by cross-domain XMLHttpRequest.

 On the bright side, some platforms use JavaScript as their
 language, but enable the programmer to access other web sites.
 Examples include Google Gadgets, and Microsoft Vista Sidebar.
 For those platforms, this library should come in handy.
 */

// The HMAC-SHA1 signature method calls b64_hmac_sha1, defined by
// http://pajhome.org.uk/crypt/md5/sha1.js

/* An OAuth message is represented as an object like this:
 {method: "GET", action: "http://server.com/path", parameters: ...}

 The parameters may be either a map {name: value, name2: value2}
 or an Array of name-value pairs [[name, value], [name2, value2]].
 The latter representation is more powerful: it supports parameters
 in a specific sequence, or several parameters with the same name;
 for example [["a", 1], ["b", 2], ["a", 3]].

 Parameter names and values are NOT percent-encoded in an object.
 They must be encoded before transmission and decoded after reception.
 For example, this message object:
 {method: "GET", action: "http://server/path", parameters: {p: "x y"}}
 ... can be transmitted as an HTTP request that begins:
 GET /path?p=x%20y HTTP/1.0
 (This isn't a valid OAuth request, since it lacks a signature etc.)
 Note that the object "x y" is transmitted as x%20y.  To encode
 parameters, you can call OAuth.addToURL, OAuth.formEncode or
 OAuth.getAuthorization.

 This message object model harmonizes with the browser object model for
 input elements of an form, whose value property isn't percent encoded.
 The browser encodes each value before transmitting it. For example,
 see consumer.setInputs in example/consumer.js.
 */

/* This script needs to know what time it is. By default, it uses the local
 clock (new Date), which is apt to be inaccurate in browsers. To do
 better, you can load this script from a URL whose query string contains
 an oauth_timestamp parameter, whose value is a current Unix timestamp.
 For example, when generating the enclosing document using PHP:

 <script src="oauth.js?oauth_timestamp=<?=time()?>" ...

 Another option is to call OAuth.correctTimestamp with a Unix timestamp.
 */

var OAuth;
if (OAuth == null) OAuth = {};

OAuth.setProperties = function setProperties(into, from) {
    if (into != null && from != null) {
        for (var key in from) {
            into[key] = from[key];
        }
    }
    return into;
};

OAuth.setProperties(OAuth, // utility functions
    {
        percentEncode: function percentEncode(s) {
            if (s == null) {
                return "";
            }
            if (s instanceof Array) {
                var e = "";
                for (var i = 0; i < s.length; ++s) {
                    if (e != "") e += '&';
                    e += OAuth.percentEncode(s[i]);
                }
                return e;
            }
            s = encodeURIComponent(s);
            // Now replace the values which encodeURIComponent doesn't do
            // encodeURIComponent ignores: - _ . ! ~ * ' ( )
            // OAuth dictates the only ones you can ignore are: - _ . ~
            // Source: http://developer.mozilla.org/en/docs/Core_JavaScript_1.5_Reference:Global_Functions:encodeURIComponent
            s = s.replace(/\!/g, "%21");
            s = s.replace(/\*/g, "%2A");
            s = s.replace(/\'/g, "%27");
            s = s.replace(/\(/g, "%28");
            s = s.replace(/\)/g, "%29");
            return s;
        },
        decodePercent: function decodePercent(s) {
            if (s != null) {
                // Handle application/x-www-form-urlencoded, which is defined by
                // http://www.w3.org/TR/html4/interact/forms.html#h-17.13.4.1
                s = s.replace(/\+/g, " ");
            }
            return decodeURIComponent(s);
        },
        /** Convert the given parameters to an Array of name-value pairs. */
        getParameterList: function getParameterList(parameters) {
            if (parameters == null) {
                return [];
            }
            if (typeof parameters != "object") {
                return OAuth.decodeForm(parameters + "");
            }
            if (parameters instanceof Array) {
                return parameters;
            }
            var list = [];
            for (var p in parameters) {
                list.push([p, parameters[p]]);
            }
            return list;
        },
        /** Convert the given parameters to a map from name to value. */
        getParameterMap: function getParameterMap(parameters) {
            if (parameters == null) {
                return {};
            }
            if (typeof parameters != "object") {
                return OAuth.getParameterMap(OAuth.decodeForm(parameters + ""));
            }
            if (parameters instanceof Array) {
                var map = {};
                for (var p = 0; p < parameters.length; ++p) {
                    var key = parameters[p][0];
                    if (map[key] === undefined) { // first value wins
                        map[key] = parameters[p][1];
                    }
                }
                return map;
            }
            return parameters;
        },
        getParameter: function getParameter(parameters, name) {
            if (parameters instanceof Array) {
                for (var p = 0; p < parameters.length; ++p) {
                    if (parameters[p][0] == name) {
                        return parameters[p][1]; // first value wins
                    }
                }
            } else {
                return OAuth.getParameterMap(parameters)[name];
            }
            return null;
        },
        formEncode: function formEncode(parameters) {
            var form = "";
            var list = OAuth.getParameterList(parameters);
            for (var p = 0; p < list.length; ++p) {
                var value = list[p][1];
                if (value == null) value = "";
                if (form != "") form += '&';
                form += OAuth.percentEncode(list[p][0])
                    + '=' + OAuth.percentEncode(value);
            }
            return form;
        },
        decodeForm: function decodeForm(form) {
            var list = [];
            var nvps = form.split('&');
            for (var n = 0; n < nvps.length; ++n) {
                var nvp = nvps[n];
                if (nvp == "") {
                    continue;
                }
                var equals = nvp.indexOf('=');
                var name;
                var value;
                if (equals < 0) {
                    name = OAuth.decodePercent(nvp);
                    value = null;
                } else {
                    name = OAuth.decodePercent(nvp.substring(0, equals));
                    value = OAuth.decodePercent(nvp.substring(equals + 1));
                }
                list.push([name, value]);
            }
            return list;
        },
        setParameter: function setParameter(message, name, value) {
            var parameters = message.parameters;
            if (parameters instanceof Array) {
                for (var p = 0; p < parameters.length; ++p) {
                    if (parameters[p][0] == name) {
                        if (value === undefined) {
                            parameters.splice(p, 1);
                        } else {
                            parameters[p][1] = value;
                            value = undefined;
                        }
                    }
                }
                if (value !== undefined) {
                    parameters.push([name, value]);
                }
            } else {
                parameters = OAuth.getParameterMap(parameters);
                parameters[name] = value;
                message.parameters = parameters;
            }
        },
        setParameters: function setParameters(message, parameters) {
            var list = OAuth.getParameterList(parameters);
            for (var i = 0; i < list.length; ++i) {
                OAuth.setParameter(message, list[i][0], list[i][1]);
            }
        },
        /** Fill in parameters to help construct a request message.
         This function doesn't fill in every parameter.
         The accessor object should be like:
         {consumerKey:'foo', consumerSecret:'bar', accessorSecret:'nurn', token:'krelm', tokenSecret:'blah'}
         The accessorSecret property is optional.
         */
        completeRequest: function completeRequest(message, accessor) {
            if (message.method == null) {
                message.method = "GET";
            }
            var map = OAuth.getParameterMap(message.parameters);
            if (map.oauth_consumer_key == null) {
                OAuth.setParameter(message, "oauth_consumer_key", accessor.consumerKey || "");
            }
            if (map.oauth_token == null && accessor.token != null) {
                OAuth.setParameter(message, "oauth_token", accessor.token);
            }
            if (map.oauth_version == null) {
                OAuth.setParameter(message, "oauth_version", "1.0");
            }
            if (map.oauth_timestamp == null) {
                OAuth.setParameter(message, "oauth_timestamp", OAuth.timestamp());
            }
            if (map.oauth_nonce == null) {
                OAuth.setParameter(message, "oauth_nonce", OAuth.nonce(6));
            }
            OAuth.SignatureMethod.sign(message, accessor);
        },
        setTimestampAndNonce: function setTimestampAndNonce(message) {
            OAuth.setParameter(message, "oauth_timestamp", OAuth.timestamp());
            OAuth.setParameter(message, "oauth_nonce", OAuth.nonce(6));
        },
        addToURL: function addToURL(url, parameters) {
            newURL = url;
            if (parameters != null) {
                var toAdd = OAuth.formEncode(parameters);
                if (toAdd.length > 0) {
                    var q = url.indexOf('?');
                    if (q < 0) newURL += '?';
                    else       newURL += '&';
                    newURL += toAdd;
                }
            }
            return newURL;
        },
        /** Construct the value of the Authorization header for an HTTP request. */
        getAuthorizationHeader: function getAuthorizationHeader(realm, parameters) {
            var header = 'OAuth realm="' + OAuth.percentEncode(realm) + '"';
            var list = OAuth.getParameterList(parameters);
            for (var p = 0; p < list.length; ++p) {
                var parameter = list[p];
                var name = parameter[0];
                if (name.indexOf("oauth_") == 0) {
                    header += ',' + OAuth.percentEncode(name) + '="' + OAuth.percentEncode(parameter[1]) + '"';
                }
            }
            return header;
        },
        /** Generate timestamps starting with the given value. */
        correctTimestamp: function correctTimestamp(timestamp) {
            OAuth.timeCorrectionMsec = (timestamp * 1000) - (new Date()).getTime();
        },
        /** The difference between the correct time and my clock. */
        timeCorrectionMsec: 0,
        timestamp: function timestamp() {
            var t = (new Date()).getTime() + OAuth.timeCorrectionMsec;
            return Math.floor(t / 1000);
        },
        nonce: function nonce(length) {
            var chars = OAuth.nonce.CHARS;
            var result = "";
            for (var i = 0; i < length; ++i) {
                var rnum = Math.floor(Math.random() * chars.length);
                result += chars.substring(rnum, rnum + 1);
            }
            return result;
        }
    });

OAuth.nonce.CHARS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXTZabcdefghiklmnopqrstuvwxyz";

/** Define a constructor function,
 without causing trouble to anyone who was using it as a namespace.
 That is, if parent[name] already existed and had properties,
 copy those properties into the new constructor.
 */
OAuth.declareClass = function declareClass(parent, name, newConstructor) {
    var previous = parent[name];
    parent[name] = newConstructor;
    if (newConstructor != null && previous != null) {
        for (var key in previous) {
            if (key != "prototype") {
                newConstructor[key] = previous[key];
            }
        }
    }
    return newConstructor;
};

/** An abstract algorithm for signing messages. */
OAuth.declareClass(OAuth, "SignatureMethod", function OAuthSignatureMethod() {});

OAuth.setProperties(OAuth.SignatureMethod.prototype, // instance members
    {
        /** Add a signature to the message. */
        sign: function sign(message) {
            var baseString = OAuth.SignatureMethod.getBaseString(message);
            var signature = this.getSignature(baseString);
            OAuth.setParameter(message, "oauth_signature", signature);
            return signature; // just in case someone's interested
        },
        /** Set the key string for signing. */
        initialize: function initialize(name, accessor) {
            var consumerSecret;
            if (accessor.accessorSecret != null
                && name.length > 9
                && name.substring(name.length - 9) == "-Accessor") {
                consumerSecret = accessor.accessorSecret;
            } else {
                consumerSecret = accessor.consumerSecret;
            }
            this.key = OAuth.percentEncode(consumerSecret)
                + "&" + OAuth.percentEncode(accessor.tokenSecret);
        }
    });

/* SignatureMethod expects an accessor object to be like this:
 {tokenSecret: "lakjsdflkj...", consumerSecret: "QOUEWRI..", accessorSecret: "xcmvzc..."}
 The accessorSecret property is optional.
 */
// Class members:
OAuth.setProperties(OAuth.SignatureMethod, // class members
    {
        sign: function sign(message, accessor) {
            var name = OAuth.getParameterMap(message.parameters).oauth_signature_method;
            if (name == null || name == "") {
                name = "HMAC-SHA1";
                OAuth.setParameter(message, "oauth_signature_method", name);
            }
            OAuth.SignatureMethod.newMethod(name, accessor).sign(message);
        },
        /** Instantiate a SignatureMethod for the given method name. */
        newMethod: function newMethod(name, accessor) {
            var impl = OAuth.SignatureMethod.REGISTERED[name];
            if (impl != null) {
                var method = new impl();
                method.initialize(name, accessor);
                return method;
            }
            var err = new Error("signature_method_rejected");
            var acceptable = "";
            for (var r in OAuth.SignatureMethod.REGISTERED) {
                if (acceptable != "") acceptable += '&';
                acceptable += OAuth.percentEncode(r);
            }
            err.oauth_acceptable_signature_methods = acceptable;
            throw err;
        },
        /** A map from signature method name to constructor. */
        REGISTERED: {},
        /** Subsequently, the given constructor will be used for the named methods.
         The constructor will be called with no parameters.
         The resulting object should usually implement getSignature(baseString).
         You can easily define such a constructor by calling makeSubclass, below.
         */
        registerMethodClass: function registerMethodClass(names, classConstructor) {
            for (var n = 0; n < names.length; ++n) {
                OAuth.SignatureMethod.REGISTERED[names[n]] = classConstructor;
            }
        },
        /** Create a subclass of OAuth.SignatureMethod, with the given getSignature function. */
        makeSubclass: function makeSubclass(getSignatureFunction) {
            var superClass = OAuth.SignatureMethod;
            var subClass = function () {
                superClass.call(this);
            };
            subClass.prototype = new superClass();
            // Delete instance variables from prototype:
            // delete subclass.prototype... There aren't any.
            subClass.prototype.getSignature = getSignatureFunction;
            subClass.prototype.constructor = subClass;
            return subClass;
        },
        getBaseString: function getBaseString(message) {
            var URL = message.action;
            var q = URL.indexOf('?');
            var parameters;
            if (q < 0) {
                parameters = message.parameters;
            } else {
                // Combine the URL query string with the other parameters:
                parameters = OAuth.decodeForm(URL.substring(q + 1));
                var toAdd = OAuth.getParameterList(message.parameters);
                for (var a = 0; a < toAdd.length; ++a) {
                    parameters.push(toAdd[a]);
                }
            }
            return OAuth.percentEncode(message.method.toUpperCase())
                + '&' + OAuth.percentEncode(OAuth.SignatureMethod.normalizeUrl(URL))
                + '&' + OAuth.percentEncode(OAuth.SignatureMethod.normalizeParameters(parameters));
        },
        normalizeUrl: function normalizeUrl(url) {
            var uri = OAuth.SignatureMethod.parseUri(url);
            var scheme = uri.protocol.toLowerCase();
            var authority = uri.authority.toLowerCase();
            var dropPort = (scheme == "http" && uri.port == 80)
                || (scheme == "https" && uri.port == 443);
            if (dropPort) {
                // find the last : in the authority
                var index = authority.lastIndexOf(":");
                if (index >= 0) {
                    authority = authority.substring(0, index);
                }
            }
            var path = uri.path;
            if (!path) {
                path = "/"; // conforms to RFC 2616 section 3.2.2
            }
            // we know that there is no query and no fragment here.
            return scheme + "://" + authority + path;
        },
        parseUri: function parseUri(str) {
            /* This function was adapted from parseUri 1.2.1
             http://stevenlevithan.com/demo/parseuri/js/assets/parseuri.js
             */
            var o = {
                key: ["source", "protocol", "authority", "userInfo", "user", "password", "host", "port", "relative", "path", "directory", "file", "query", "anchor"],
                parser: {
                    strict: /^(?:([^:\/?#]+):)?(?:\/\/((?:(([^:@\/]*):?([^:@\/]*))?@)?([^:\/?#]*)(?::(\d*))?))?((((?:[^?#\/]*\/)*)([^?#]*))(?:\?([^#]*))?(?:#(.*))?)/
                }
            };
            var m = o.parser.strict.exec(str);
            var uri = {};
            var i = 14;
            while (i--) uri[o.key[i]] = m[i] || "";
            return uri;
        },
        normalizeParameters: function normalizeParameters(parameters) {
            if (parameters == null) {
                return "";
            }
            var list = OAuth.getParameterList(parameters);
            var sortable = [];
            for (var p = 0; p < list.length; ++p) {
                var nvp = list[p];
                if (nvp[0] != "oauth_signature") {
                    sortable.push([ OAuth.percentEncode(nvp[0])
                        + " " // because it comes before any character that can appear in a percentEncoded string.
                        + OAuth.percentEncode(nvp[1])
                        , nvp]);
                }
            }
            sortable.sort(function (a, b) {
                if (a[0] < b[0]) return  -1;
                if (a[0] > b[0]) return 1;
                return 0;
            });
            var sorted = [];
            for (var s = 0; s < sortable.length; ++s) {
                sorted.push(sortable[s][1]);
            }
            return OAuth.formEncode(sorted);
        }
    });

OAuth.SignatureMethod.registerMethodClass(["PLAINTEXT", "PLAINTEXT-Accessor"],
    OAuth.SignatureMethod.makeSubclass(
        function getSignature(baseString) {
            return this.key;
        }
    ));

OAuth.SignatureMethod.registerMethodClass(["HMAC-SHA1", "HMAC-SHA1-Accessor"],
    OAuth.SignatureMethod.makeSubclass(
        function getSignature(baseString) {
            b64pad = '=';
            var signature = b64_hmac_sha1(this.key, baseString);
            return signature;
        }
    ));
/**
* @preserve
* A JavaScript implementation of the Secure Hash Algorithm, SHA-1, as defined
* in FIPS PUB 180-1
* Version 2.1a Copyright Paul Johnston 2000 - 2002.
* Other contributors: Greg Holt, Andrew Kepert, Ydnar, Lostinet
* Distributed under the BSD License
* See http://pajhome.org.uk/crypt/md5 for details.
*/

/*
* Configurable variables. You may need to tweak these to be compatible with
* the server-side, but the defaults work in most cases.
*/
var b64pad = ""; /* base-64 pad character. "=" for strict RFC compliance   */
var chrsz = 8; /* bits per input character. 8 - ASCII; 16 - Unicode      */

/*
* These are the functions you'll usually want to call
* They take string arguments and return either hex or base-64 encoded strings
*/
function b64_hmac_sha1(key, data) { return binb2b64(core_hmac_sha1(key, data));}

/*
* Calculate the SHA-1 of an array of big-endian words, and a bit length
*/
function core_sha1(x, len) {
   /* append padding */
   x[len >> 5] |= 0x80 << (24 - len % 32);
   x[((len + 64 >> 9) << 4) + 15] = len;

   var w = Array(80);
   var a = 1732584193;
   var b = -271733879;
   var c = -1732584194;
   var d = 271733878;
   var e = -1009589776;

   for (var i = 0; i < x.length; i += 16) {
       var olda = a;
       var oldb = b;
       var oldc = c;
       var oldd = d;
       var olde = e;

       for (var j = 0; j < 80; j++) {
           if (j < 16) w[j] = x[i + j];
           else w[j] = rol(w[j - 3] ^ w[j - 8] ^ w[j - 14] ^ w[j - 16], 1);
           var t = safe_add(safe_add(rol(a, 5), sha1_ft(j, b, c, d)),
               safe_add(safe_add(e, w[j]), sha1_kt(j)));
           e = d;
           d = c;
           c = rol(b, 30);
           b = a;
           a = t;
       }

       a = safe_add(a, olda);
       b = safe_add(b, oldb);
       c = safe_add(c, oldc);
       d = safe_add(d, oldd);
       e = safe_add(e, olde);
   }
   return Array(a, b, c, d, e);

}

/*
* Perform the appropriate triplet combination function for the current
* iteration
*/
function sha1_ft(t, b, c, d) {
   if (t < 20) return (b & c) | ((~b) & d);
   if (t < 40) return b ^ c ^ d;
   if (t < 60) return (b & c) | (b & d) | (c & d);
   return b ^ c ^ d;
}

/*
* Determine the appropriate additive constant for the current iteration
*/
function sha1_kt(t) {
   return (t < 20) ? 1518500249 : (t < 40) ? 1859775393 :
       (t < 60) ? -1894007588 : -899497514;
}

/*
* Calculate the HMAC-SHA1 of a key and some data
*/
function core_hmac_sha1(key, data) {
   var bkey = str2binb(key);
   if (bkey.length > 16) bkey = core_sha1(bkey, key.length * chrsz);

   var ipad = Array(16), opad = Array(16);
   for (var i = 0; i < 16; i++) {
       ipad[i] = bkey[i] ^ 0x36363636;
       opad[i] = bkey[i] ^ 0x5C5C5C5C;
   }

   var hash = core_sha1(ipad.concat(str2binb(data)), 512 + data.length * chrsz);
   return core_sha1(opad.concat(hash), 512 + 160);
}

/*
* Add integers, wrapping at 2^32. This uses 16-bit operations internally
* to work around bugs in some JS interpreters.
*/
function safe_add(x, y) {
   var lsw = (x & 0xFFFF) + (y & 0xFFFF);
   var msw = (x >> 16) + (y >> 16) + (lsw >> 16);
   return (msw << 16) | (lsw & 0xFFFF);
}

/*
* Bitwise rotate a 32-bit number to the left.
*/
function rol(num, cnt) {
   return (num << cnt) | (num >>> (32 - cnt));
}

/*
* Convert an 8-bit or 16-bit string to an array of big-endian words
* In 8-bit function, characters >255 have their hi-byte silently ignored.
*/
function str2binb(str) {
   var bin = Array();
   var mask = (1 << chrsz) - 1;
   for (var i = 0; i < str.length * chrsz; i += chrsz)
       bin[i >> 5] |= (str.charCodeAt(i / chrsz) & mask) << (32 - chrsz - i % 32);
   return bin;
}

/*
* Convert an array of big-endian words to a base-64 string
*/
function binb2b64(binarray) {
   var tab = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
   var str = "";
   for (var i = 0; i < binarray.length * 4; i += 3) {
       var triplet = (((binarray[i >> 2] >> 8 * (3 - i % 4)) & 0xFF) << 16)
           | (((binarray[i + 1 >> 2] >> 8 * (3 - (i + 1) % 4)) & 0xFF) << 8 )
           | ((binarray[i + 2 >> 2] >> 8 * (3 - (i + 2) % 4)) & 0xFF);
       for (var j = 0; j < 4; j++) {
           if (i * 8 + j * 6 > binarray.length * 32) str += b64pad;
           else str += tab.charAt((triplet >> 6 * (3 - j)) & 0x3F);
       }
   }
   return str;
}
//if you want to use three-legged OAuth, always pass OAuth key to the key argument
function Cocoafish(key, secret, baseURL, authBaseURL) {

	//a flag indicating whether 3-legged oauth will be used
	var threeLegged = false;

	if (!secret) {
	    this.appKey = key;
	} else {
	    this.oauthKey = key;
	    this.oauthSecret = secret;
	}
	if (baseURL) {
	    this.apiBaseURL = baseURL;
	} else {
	    this.apiBaseURL = com.cocoafish.sdk.url.baseURL;
	}
	if (authBaseURL) {
		this.authBaseURL = authBaseURL;
	} else {
		this.authBaseURL = com.cocoafish.sdk.url.authBaseURL;
	}

	this.useThreeLegged = function(isThreeLegged) {
		threeLegged = isThreeLegged;
		if(!this.oauthKey) //If three-legged OAuth is used the passed in 'key' should be OAuth key
			this.oauthKey = this.appKey;
	};

	this.isThreeLegged = function() {
		return threeLegged;
	};

	return this;
}

Cocoafish.prototype.sendRequest = function (url, method, data, useSecure, callback) {
	var authType = com.cocoafish.js.sdk.utils.getAuthType(this);
	if (authType == com.cocoafish.constants.unknown) {
	    callback(com.cocoafish.constants.noAppKeyError);
	    return;
	}

	//build request url
	var reqURL = '';
	if (useSecure) {
	    reqURL += com.cocoafish.sdk.url.https;
	} else {
	    reqURL += com.cocoafish.sdk.url.http;
	}
	reqURL += this.apiBaseURL + "/" + com.cocoafish.sdk.url.version + "/" + url;

	if (authType == com.cocoafish.constants.app_key) {
	    reqURL += com.cocoafish.constants.keyParam + this.appKey;
	} else {
		//For both 2-legged and 3-legged oauth there should be an OAuth key
        reqURL += com.cocoafish.constants.oauthKeyParam + this.oauthKey;
	}

	if (data == null)
	    data = {};

	var apiMethod = method ? method.toUpperCase() : com.cocoafish.constants.get_method;

	data[com.cocoafish.constants.suppressCode] = 'true';
	if(!this.isThreeLegged()) {
		var sessionId = com.cocoafish.js.sdk.utils.getCookie(com.cocoafish.constants.sessionId);
		if (!sessionId)
			sessionId = this.session_id;

		if (sessionId) {
			if(reqURL.indexOf("?") != -1) {
				reqURL += "&" + com.cocoafish.constants.sessionId + '=' + sessionId;
			} else {
				reqURL += "?" + com.cocoafish.constants.sessionId + '=' + sessionId;
			}
		}
	}

    if(this.isThreeLegged()) {
        if(!this.accessToken) {
            var session = this.getSession();
            if(session) {
                this.accessToken = session.access_token;;
            }
        }

        //alert('sendRequest -> url: ' + url + ' access token: ' + this.accessToken);
        if(this.accessToken) {
            data[com.cocoafish.constants.accessToken] = this.accessToken;
        }
    }

	injectAnalytics(data, url);
	data = com.cocoafish.js.sdk.utils.cleanInvalidData(data);

	var fileInputObj = com.cocoafish.js.sdk.utils.getFileObject(data);
	if (fileInputObj) {
	    //send request with file
	    try {
	        var binary;
	        if (fileInputObj.toString().match(/TiFilesystemFile/)) {
	            binary = fileInputObj.read();
	        } else {
	            binary = fileInputObj;
	        }

	        if (!binary) {
	            callback(com.cocoafish.constants.fileLoadError);
	            return;
	        }

	        if (data[com.cocoafish.constants.file]) {
	            delete data[com.cocoafish.constants.file];
	            data[com.cocoafish.constants.file] = binary;
	        } else if (data[com.cocoafish.constants.photo]) {
	            delete data[com.cocoafish.constants.photo];
	            data[com.cocoafish.constants.photo] = binary;
	        }
	    } catch (e) {
	        callback(com.cocoafish.constants.fileLoadError);
	        return;
	    }

	    var header = {};
	    if ((authType == com.cocoafish.constants.oauth) || (authType == com.cocoafish.constants.three_legged_oauth)) {
	        var message = {
	            method: apiMethod,
	            action: reqURL,
	            parameters: []
	        };
	        com.cocoafish.js.sdk.utils.populateOAuthParameters(message.parameters, this.oauthKey);
		    if(this.oauthSecret) {
	            OAuth.completeRequest(message, {consumerSecret: this.oauthSecret});
		    }
	        header[com.cocoafish.constants.oauth_header] = OAuth.getAuthorizationHeader("", message.parameters);
	    }
	    //send request
	    com.cocoafish.js.sdk.utils.sendAppceleratorRequest(reqURL, apiMethod, data, header, callback, this);
	} else {
	    //send request without file
	    var header = {};
		if ((authType == com.cocoafish.constants.oauth) || (authType == com.cocoafish.constants.three_legged_oauth)) {
	        var message = {
	            method: apiMethod,
	            action: reqURL,
	            parameters: []
	        };
	        for (var prop in data) {
	            if (!data.hasOwnProperty(prop)) {
	                continue;
	            }
	            message.parameters.push([prop, data[prop]]);
	        }
	        com.cocoafish.js.sdk.utils.populateOAuthParameters(message.parameters, this.oauthKey);
			if(this.oauthSecret) {
	            OAuth.completeRequest(message, {consumerSecret: this.oauthSecret});
			}
	        header[com.cocoafish.constants.oauth_header] = OAuth.getAuthorizationHeader("", message.parameters);
	    }
	    com.cocoafish.js.sdk.utils.sendAppceleratorRequest(reqURL, apiMethod, data, header, callback, this);
	}
};


//authorization request needs to be sent explicitly
//options expected: redirectUri, useSecure, params
//params option is an object containing arguments for popup window or iframe
Cocoafish.prototype.sendAuthRequest = function(options) {

  //send a request to authorization server
  //authorization server will redirect browser for login
  //if logged in authorizations server will redirect browser back to original auth url
  //after authorized authorization server will redirect browser back to redirectUri
  //app can then send API request using access token obtained from authorization server
  var authType = com.cocoafish.js.sdk.utils.getAuthType(this);
  if(authType !== com.cocoafish.constants.three_legged_oauth) {
      alert('wrong authorization type!');
      return;
  }

  options = options || {};

  var isSecure = false;
  if(typeof(options.useSecure) == 'boolean') {
      isSecure = options.useSecure;
  }

  //build request url
  var reqURL = '';
  if(isSecure) {
      reqURL += com.cocoafish.sdk.url.https;
  } else {
      reqURL += com.cocoafish.sdk.url.http;
  }
  reqURL += this.authBaseURL;
  reqURL += '/oauth/authorize';
  reqURL += com.cocoafish.constants.clientIdParam + this.oauthKey;
  reqURL += com.cocoafish.constants.responseTypeParam + 'token';

	var params = options.params || {};
	params.action = 'login';
	params.url = reqURL;

	var that = this;
	var cb = params.cb;
	if(cb) delete params.cb;
	com.cocoafish.js.sdk.ui(params, function(data) {
		that.saveSession(data);
		cb && cb(data);
	});
};


//signing up request needs to be sent explicitly
//options expected: redirectUri, useSecure, params
//params option is an object containing arguments for popup window or iframe
Cocoafish.prototype.signUpRequest = function(options) {

  //send a request to authorization server
  //authorization server will redirect browser for signup
  //if signed up successfully authorizations server will redirect browser back to auth url
  //after authorized authorization server will redirect browser back to redirectUri
  //app can then send API request using access token obtained from authorization server
  var authType = com.cocoafish.js.sdk.utils.getAuthType(this);
  if(authType !== com.cocoafish.constants.three_legged_oauth) {
      alert('wrong authorization type!');
      return;
  }

  options = options || {};

  var isSecure = false;
  if(typeof(options.useSecure) == 'boolean') {
      isSecure = options.useSecure;
  }

  //build request url
  var reqURL = '';
  if(isSecure) {
      reqURL += com.cocoafish.sdk.url.https;
  } else {
      reqURL += com.cocoafish.sdk.url.http;
  }
  reqURL += this.authBaseURL;
  reqURL += '/users/sign_up';
  reqURL += com.cocoafish.constants.clientIdParam + this.oauthKey;

	var params = options.params || {};
	params.action = 'signup';
	params.url = reqURL;

	var that = this;
	var cb = params.cb;
	if(cb) delete params.cb;
	com.cocoafish.js.sdk.ui(params, function(data) {
		that.saveSession(data);
		cb && cb(data);
	});
};


//Default implementation to store session in cookies.
//Developers can override this for custom implementation.
//data object should contain the following properties. The properties will also be added to the SDK object.
//	access_token
//	expires_in
Cocoafish.prototype.saveSession = function(data) {
    //TODO check validity of the access token
    if(!data || !data.access_token) {
        this.authorized = false;
        return false;
    }
    com.cocoafish.js.sdk.utils.setCookie(com.cocoafish.constants.accessToken, data.access_token);
    com.cocoafish.js.sdk.utils.setCookie(com.cocoafish.constants.expiresIn, data.expires_in);
    this.accessToken = data.access_token;
    this.expiresIn = data.expires_in;

    //alert('Cocoafish saveSession called with: ' + data.access_token + ' ' + data.expires_in);
    this.authorized = true;
    return true;
};

//Default implementation to restore session from cookie
//Developers can override this for custom implementation.
//will return an data object containing the following properties. The properties will also be added to the SDK object.
//	access_token
//	expires_in
Cocoafish.prototype.getSession = function() {
    var data = {};
    data.access_token = com.cocoafish.js.sdk.utils.getCookie(com.cocoafish.constants.accessToken);
    data.expires_in = com.cocoafish.js.sdk.utils.getCookie(com.cocoafish.constants.expiresIn);
    //TODO check validity of the access token
    if(!data.access_token) {
        this.authorized = false;
        return false;
    }

    this.accessToken = data.access_token;
    this.expiresIn = data.expires_in;

    this.authorized = true;
    //alert('Cocoafish getSession called to get: ' + data.access_token + ' ' + data.expires_in);
    return data;
};

//Default implementation to clear session from cookie.
//Developers can override this for custom implementation.
Cocoafish.prototype.clearSession = function() {
    com.cocoafish.js.sdk.utils.setCookie(com.cocoafish.constants.accessToken, '');
    com.cocoafish.js.sdk.utils.setCookie(com.cocoafish.constants.expiresIn, '');
    delete this.accessToken;
    delete this.expiresIn;
    this.authorized = false;
    //alert('Cocoafish clearSession called');
};



//check the current session status: logged-in? just-authenticated? need-to-login?
Cocoafish.prototype.checkStatus = function() {
    if(this.getSession()) {
    	return true;
    } else {
     	return false;
    }
};


var com = {};
com.cocoafish = {};
com.cocoafish.constants = {};
com.cocoafish.js = {};
com.cocoafish.js.sdk = {};
com.cocoafish.js.sdk.utils = {};

com.cocoafish.sdk = {};
com.cocoafish.sdk.url = {};//REST APIs

//Protocols
com.cocoafish.sdk.url.http = 'http://';
com.cocoafish.sdk.url.https = 'https://';

//URL
com.cocoafish.sdk.url.baseURL = 'api.cloud.appcelerator.com';
com.cocoafish.sdk.url.authBaseURL = 'secure-identity.cloud.appcelerator.com';
com.cocoafish.sdk.url.version = 'v1';

//HTTP methods
com.cocoafish.constants.get_method = 'GET';
com.cocoafish.constants.post_method = 'POST';
com.cocoafish.constants.put_method = 'PUT';
com.cocoafish.constants.delete_method = 'DELETE';

//Authentication Types
com.cocoafish.constants.app_key = 1;
com.cocoafish.constants.oauth = 2;
com.cocoafish.constants.three_legged_oauth = 3;
com.cocoafish.constants.unknown = -1;

//Others
com.cocoafish.constants.keyParam = '?key=';
com.cocoafish.constants.oauthKeyParam = '?oauth_consumer_key=';
com.cocoafish.constants.clientIdParam = '?client_id=';
com.cocoafish.constants.redirectUriParam = '&redirect_uri=';
com.cocoafish.constants.responseTypeParam = '&response_type=';
com.cocoafish.constants.accessToken = 'access_token';
com.cocoafish.constants.expiresIn = 'expires_in';
com.cocoafish.constants.appKey = 'app_key';
com.cocoafish.constants.json='json';
com.cocoafish.constants.sessionId = '_session_id';
com.cocoafish.constants.sessionCookieName = 'Cookie';
com.cocoafish.constants.responseCookieName = 'Set-Cookie';
com.cocoafish.constants.file = 'file';
com.cocoafish.constants.suppressCode = 'suppress_response_codes';
com.cocoafish.constants.response_wrapper = 'response_wrapper';
com.cocoafish.constants.photo = 'photo';
com.cocoafish.constants.method = '_method';
com.cocoafish.constants.name = 'name';
com.cocoafish.constants.value = 'value';
com.cocoafish.constants.oauth_header = 'Authorization';
com.cocoafish.constants.noAppKeyError = {'meta': {'status': 'fail', 'code': 409, 'message': 'Application key is not provided.'}};
com.cocoafish.constants.fileLoadError = {'meta': {'status': 'fail', 'code': 400, 'message': 'Unable to load file'}};
com.cocoafish.js.sdk.utils.getSessionParams = function() {
	var sessionParam = null;
	var sessionId = com.cocoafish.js.sdk.utils.getCookie(com.cocoafish.constants.sessionId);
	if (sessionId) {
		sessionParam = com.cocoafish.constants.sessionId + '=' + sessionId;
	}
	return sessionParam;
};

if (!com.cocoafish.js.sdk.utils.cookieMap) {
  Ti.API.info('creating cookies!!!!!');
  com.cocoafish.js.sdk.utils.cookieMap = [];
  com.cocoafish.js.sdk.utils.cookieMap[com.cocoafish.constants.sessionId] = 'sessionId';
  com.cocoafish.js.sdk.utils.cookieMap[com.cocoafish.constants.accessToken] = 'accessToken';
  com.cocoafish.js.sdk.utils.cookieMap[com.cocoafish.constants.expiresIn] = 'expiresIn';
}

com.cocoafish.js.sdk.utils.getCookie = function( name ) {
	var friendlyName = com.cocoafish.js.sdk.utils.cookieMap[name];
	return (friendlyName && Cloud[friendlyName]) || null;
};

com.cocoafish.js.sdk.utils.setCookie = function( name, value, expires, path, domain, secure ) {
	var friendlyName = com.cocoafish.js.sdk.utils.cookieMap[name];
	if (friendlyName) {
		if (value === '') {
			delete Cloud[friendlyName];
		} else {
			Cloud[friendlyName] = value;
		}
	}
};

com.cocoafish.js.sdk.utils.deleteCookie = function( name, path, domain ) {
	var friendlyName = com.cocoafish.js.sdk.utils.cookieMap[name];
	if (friendlyName) {
		delete Cloud[friendlyName];
	}
};

com.cocoafish.js.sdk.utils.getAuthType = function (obj) {
    if (obj) {
        if(obj.isThreeLegged()) {
            return com.cocoafish.constants.three_legged_oauth;
        } else if(obj.appKey) {
            return com.cocoafish.constants.app_key;
        } else if (obj.oauthKey && obj.oauthSecret) {
            return com.cocoafish.constants.oauth;
        }
    }
    return com.cocoafish.constants.unknown;
};

com.cocoafish.js.sdk.utils.getFileObject = function (data) {
    if (data) {
        for (var prop in data) {
            if (!data.hasOwnProperty(prop)) {
                continue;
            }
            if (prop == com.cocoafish.constants.photo || prop == com.cocoafish.constants.file) {
                return data[prop];
            }
        }
    }
    return null;
};

com.cocoafish.js.sdk.utils.cleanInvalidData = function (data) {
    if (data) {
        for (var prop in data) {
            if (!data.hasOwnProperty(prop)) {
                continue;
            }
            if (data[prop] == null) {
                delete data[prop];
            }
         // We need to stringify the data items passed in since ti.cloud allows the
         // caller to pass json objects in for the values rather than being restricted
         // to string values. Therefore we need to convert objects to strings here.
            if (typeof(data[prop]) == 'object') {
                // Check that we haven't received a blob or file.
             // [MOD-817] -- don't check for empty dictionary string "{}" of the stringified value
             if (prop == com.cocoafish.constants.photo || prop == com.cocoafish.constants.file) {
              continue;
             }
                // Otherwise, carry on with the stringification!
                data[prop] = JSON.stringify(data[prop]);
            }
            // If we receive a boolean, convert it to the equivalent integer. This helps Oauth behave itself.
            if (data[prop] === true || data[prop] === false) {
                data[prop] = data[prop] ? 1 : 0;
            }
        }
        return data;
    } else {
        return {};
    }
};

com.cocoafish.js.sdk.utils.uploadMessageCallback = function (event) {
    if (event && event.data) {
        return JSON.parse(event.data);
    } else {
        return {};
    }
};

com.cocoafish.js.sdk.utils.getOAuthParameters = function (parameters) {
    var urlParameters = '';
    if (parameters) {
        var list = OAuth.getParameterList(parameters);
        for (var p = 0; p < list.length; ++p) {
            var parameter = list[p];
            var name = parameter[0];
            if (name.indexOf("oauth_") == 0 && name != "oauth_token") {
                urlParameters += '&' + OAuth.percentEncode(name) + '=' + OAuth.percentEncode(parameter[1]);
            }
        }
    }
    if (urlParameters.length > 0) {
        urlParameters = urlParameters.substring(1);
    }
    return urlParameters;
};

com.cocoafish.js.sdk.utils.populateOAuthParameters = function (parameters, oauthKey) {
    if (parameters && oauthKey) {
        parameters.push(["oauth_version", "1.0"]);
        parameters.push(["oauth_consumer_key", oauthKey]);
        parameters.push(["oauth_signature_method", "HMAC-SHA1"]);
        parameters.push(["oauth_nonce", OAuth.nonce(15)]);
    }
};

com.cocoafish.js.sdk.utils.sendAppceleratorRequest = function (url, method, data, header, callback, sdk) {
	Ti.API.info('url: ' + url);
	Ti.API.info('headers: ' + JSON.stringify(header));
    var xhr = Ti.Network.createHTTPClient({
        timeout: 60 * 1000,
        onsendstream: function (e) {
            Cloud.onsendstream && Cloud.onsendstream({
                url: url,
                progress: e.progress
            });
        },
        ondatastream: function (e) {
            Cloud.ondatastream && Cloud.ondatastream({
                url: url,
                progress: e.progress
            });
        },
        onerror: function (e) {
            var retVal = {};
            var json = this.responseText;
            try {
                json = json.trim();
                if (json && json.length > 0) {
                    retVal = JSON.parse(json);
                }
            } catch (err) {
                retVal = err;
            }
            retVal.message || (retVal.message = e.error);
            retVal.error = true;
            retVal.statusText = this.statusText;
            retVal.status = this.status;
            if (retVal.meta) {
                retVal.metaString = JSON.stringify(retVal.meta);
            }
            callback(retVal);
        },
        onload: function () {
            var json = this.responseText;
            Ti.API.info('responseText = ' + json);
            var data = JSON.parse(json);
            if (data && data.meta) {
                data.metaString = JSON.stringify(data.meta);
	            if(data.meta.session_id) {
		            var sessionId = data.meta.session_id;
	                com.cocoafish.js.sdk.utils.setCookie(com.cocoafish.constants.sessionId, sessionId);
		            sdk.session_id = sessionId;
	            }
            }
            callback(data);
        }
    });

    // for GET request only
    var requestURL = url;
    if ((method.toUpperCase() == com.cocoafish.constants.get_method) || (method.toUpperCase() == com.cocoafish.constants.delete_method)) {
        var params = '';
        for (var prop in data) {
            if (!data.hasOwnProperty(prop)) {
                continue;
            }
            params += '&' + prop + '=' + OAuth.percentEncode(data[prop]);
        }
        if (params.length > 0) {
            if (url.indexOf('?') > 0) {
                requestURL += params;
            } else {
                requestURL += '?' + params.substring(1);
            }
            data = {};
        }
    }

    if (Cloud.debug) {
        Ti.API.info(method + ': ' + requestURL);
        Ti.API.info('header: ' + JSON.stringify(header));
        Ti.API.info('data: ' + JSON.stringify(data));
    }

    // open the client
    xhr.open(method, requestURL);

    // set headers
	// MOD-831 -- MobileWeb does not support setting Accept-Encoding header
	if (Ti.Platform.osname != 'mobileweb') {
        //xhr.setRequestHeader('Accept-Encoding', 'gzip,deflate');
	}
	// Do NOT remove these header settings on MobileWeb -- nothing will work if you do
    if (header) {
        for (var prop in header) {
            if (!header.hasOwnProperty(prop)) {
                continue;
            }
            xhr.setRequestHeader(prop, header[prop]);
        }
    }

    // send the data
    xhr.send(data);
};

/**
 * Decode a query string into a parameters object.
 *
 * @access private
 * @param   str {String} the query string
 * @return     {Object} the parameters to encode
 */
com.cocoafish.js.sdk.utils.decodeQS = function(str) {
    var
        decode = decodeURIComponent,
        params = {},
        parts  = str.split('&'),
        i,
        pair;

    for (i=0; i<parts.length; i++) {
        pair = parts[i].split('=', 2);
        if (pair && pair[0]) {
            params[decode(pair[0])] = decode(pair[1]);
        }
    }

    return params;
};


/**
 * Generates a weak random ID.
 *
 * @access private
 * @return {String} a random ID
 */
com.cocoafish.js.sdk.utils.guid = function() {
    return 'f' + (Math.random() * (1<<30)).toString(16).replace('.', '');
};

/**
 * Copies things from source into target.
 *
 * @access private
 * @param target    {Object}  the target object where things will be copied
 *                            into
 * @param source    {Object}  the source object where things will be copied
 *                            from
 * @param overwrite {Boolean} indicate if existing items should be
 *                            overwritten
 * @param tranform  {function} [Optional], transformation function for
 *        each item
 */
com.cocoafish.js.sdk.utils.copy = function(target, source, overwrite, transform) {
  for (var key in source) {
    if (overwrite || typeof target[key] === 'undefined') {
      target[key] = transform ? transform(source[key]) :  source[key];
    }
  }
  return target;
};
var ACS = {};
ACS.session = null;

ACS.fetchSetting = function(key, def) {
    var value;
    var deployType = Ti.App.deployType.toLowerCase() == 'production' ? 'production' : 'development';
    if ((value = Ti.App.Properties.getString(key + '-' + deployType)) && value != 'undefined') {
        return value;
    }
    if ((value = Ti.App.Properties.getString(key)) && value != 'undefined') {
        return value;
    }
    return def;
}

ACS.fetchSession = function() {
	var apiKey = ACS.fetchSetting('acs-api-key', null);
	var baseURL = ACS.fetchSetting('acs-base-url', com.cocoafish.sdk.url.baseURL);
	var authBaseURL = ACS.fetchSetting('acs-authbase-url', com.cocoafish.sdk.url.authBaseURL);
	var consumerKey = ACS.fetchSetting('acs-oauth-key', null);
	var consumerSecret = ACS.fetchSetting('acs-oauth-secret', null);
	if (consumerKey && consumerSecret) {
	    return new Cocoafish(consumerKey, consumerSecret, baseURL, authBaseURL);
	}
	if (apiKey) {
	    return new Cocoafish(apiKey, null, baseURL, authBaseURL);
	}

	throw 'ACS CREDENTIALS NOT SPECIFIED!';
}

ACS.getSession = function() {
	if (ACS.session == null) {
	    ACS.session = ACS.fetchSession();
	}
	return ACS.session;
}

ACS.send = function (url, method, data, useSecure, callback) {
	ACS.getSession().sendRequest(url, method, data, useSecure, callback);
};

ACS.hasStoredSession = function() {
	// Deprecated
	return !!(com.cocoafish.js.sdk.utils.getCookie(com.cocoafish.constants.sessionId));
};

ACS.retrieveStoredSession = function() {
	// Deprecated
	return com.cocoafish.js.sdk.utils.getCookie(com.cocoafish.constants.sessionId);
};

ACS.reset = function () {
	com.cocoafish.js.sdk.utils.deleteCookie(com.cocoafish.constants.sessionId);
	if (ACS.session) {
		ACS.session.clearSession();
		ACS.session = null;
	}
};

ACS.secureSend = function (method, options) {
	var session = ACS.getSession();
	session.useThreeLegged(true);

	if (method === 'secureCreate') {
		session.signUpRequest(options);
	} else if (method === 'secureLogin') {
		session.sendAuthRequest(options);
	}
}

ACS.checkStatus = function () {
	return ACS.getSession().checkStatus();
}
/**
 * Internal UI functions.
 *
 * @static
 * @access private
 */

com.cocoafish.js.sdk.UIManager = {
	redirect_uri: 'acsconnect://success',

	displayModal: function(call) {
		if (Cloud.debug) {
            Ti.API.info('ThreeLegged Request url: ' + call.url);
		}

		var modal = Ti.UI.createWindow({
			modal: true,
			title: call.params.title || "Appcelerator Cloud Service"
		});

		var webView = Ti.UI.createWebView({
			url: call.url,
			scalesPageToFit: false,
			showScrollbars: true
		});

		var loading = Ti.UI.createLabel({
			text: 'Loading, please wait...',
			color: 'black',
			width: Ti.UI.SIZE || 'auto',
			height: Ti.UI.SIZE || 'auto',
			zIndex: 100
		});

		var response;

		function checkResponse(e) {
			var re = /^acsconnect:\/\/([^#]*)#(.*)/;
			var result = re.exec(decodeURIComponent(e.url));
			if (result && result.length == 3) {
				var data = null;
				if (result[1] == 'success') {
					data = com.cocoafish.js.sdk.utils.decodeQS(result[2]);
				} else if (result[1] != 'cancel') {
					return;
				}
				// We received either a 'success' or 'cancel' response
				webView.removeEventListener('beforeload', checkResponse);
				webView.removeEventListener('load', checkResponse);

				response = data;
				modal && modal.close();
			}

			if (loading && (e.type == 'load')) {
				modal.remove(loading);
				loading = null;
			}
		}

		webView.addEventListener('beforeload', checkResponse);
		webView.addEventListener('load', checkResponse);
		modal.addEventListener('close', closeHandler);

		if (Ti.Platform.osname != 'android') {
			var closeButton = Ti.UI.createButton({
				title: 'close',
				width: '50%',
				height: '20%'
			});
			closeButton.addEventListener('click', function(){
				modal.close();
			});
			modal.rightNavButton = closeButton;
		}

		function closeHandler(e) {
			if (call) {
				call.cb && call.cb(response);
				webView = modal = loading = call = response = null;
			}
		};

		modal.add(webView);
		modal.add(loading);

		modal.open();
	},

	processParams: function(params, cb) {
		// the basic call data
		var call = {
			cb     : cb,
			url    : params.url + com.cocoafish.constants.redirectUriParam + com.cocoafish.js.sdk.UIManager.redirect_uri,
			params : params
		};

		return call;
	}
};

/**
 * Method for triggering UI interaction with Authorization Server.
 */
com.cocoafish.js.sdk.ui = function(params, cb) {
	if (Ti.Platform.osname === "mobileweb") {
		// We are not supporting MobileWeb at this time.
		alert("Three Legged OAuth is not currently supported on MobileWeb");
		return;
	}
	if (!params.action) {
        alert('"action" is a required parameter for com.cocoafish.js.sdk.ui().');
        return;
    }
    var call = com.cocoafish.js.sdk.UIManager.processParams(params, cb);
    if (call) {
	    com.cocoafish.js.sdk.UIManager.displayModal(call);
    }
};

	return Cloud;
}
