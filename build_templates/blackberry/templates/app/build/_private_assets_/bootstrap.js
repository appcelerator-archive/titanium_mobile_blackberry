/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
Ti = Ti || {};
Ti.include = function () {
    var args = Array.prototype.slice.call(arguments);
    for(var i = 0, len = args.length; i < len; i++) {
        Ti.globalInclude([args[i]], "app/native/assets/");
    }
};
var global = this;
//var require;

alert = function(msg) {
    Ti.UI.createAlertDialog({message: (msg || '').toString()}).show();
}
Ti.XML = require('ti.xml/module');
// TODO: move to its own file when we can include from the framework dir
//Ti.include("bufferstream.js");
Ti.BufferStream.prototype = {};

Ti.BufferStream.prototype.isReadable = function() {
    return (this.mode === Ti.Stream.MODE_READ);
}

Ti.BufferStream.prototype.isWriteable = function() {
    return (this.mode === Ti.Stream.MODE_WRITE || this.mode === Ti.Stream.MODE_APPEND);
}

Ti.BufferStream.prototype.read = function(buffer, offset, length) {
    if (!this.isReadable())
    {
        throw "Stream is not readable";
    }

    if (this.pos == this.source.length)
    {
        return -1;
    }

    if (offset === undefined && length === undefined)
    {
        offset = 0;
        length = buffer.length;
    }
    else if (offset === undefined || length === undefined)
    {
        throw "Missing argument";
    }

    // read until:
    // - the end of this stream is reached
    // - a total of length bytes have been read from the stream
    var copyLength = Math.min(this.source.length - this.pos, length);
    // - the end of the buffer is reached
    copyLength = Math.min(buffer.length - offset, copyLength);

    var numCopied = buffer.copy(this.source, offset, this.pos, copyLength);
    this.pos += numCopied;
    return numCopied;
};

Ti.BufferStream.prototype.write = function(buffer, offset, length) {
    if (!this.isWriteable())
    {
        throw "Stream is not writeable";
    }

    if (offset === undefined && length === undefined)
    {
        offset = 0;
        length = buffer.length;
    }
    else if (offset === undefined || length === undefined)
    {
        throw "Missing argument";
    }

    var numCopied = 0;
    if (this.mode === Ti.Stream.MODE_WRITE)
    {
        // write until:
        // - the end of this stream is reached
        // - length bytes have been written
        // - the stream returns an error
        var copyLength = Math.min(buffer.length - offset, length);
        numCopied = this.source.copy(buffer, this.pos, offset, copyLength);
    }
    else if(this.mode === Ti.Stream.MODE_APPEND)
    {
        numCopied = this.source.append(buffer, offset, length);
    }
    else
    {
        throw "Unknown open mode: " + this.mode;
    }
    this.pos += numCopied;
    return numCopied;
};

Ti.Stream.pump = function(inputStream, handler, maxChunkSize, isAsync)
{
    if (isAsync === undefined)
    {
        isAsync = false;
    }
    var buffer = Ti.createBuffer({ length: maxChunkSize });
    var pumpCallBackArgs  = {
        buffer: buffer,
        bytesProcessed: -1,
        errorDescription: '',
        errorState: 0,
        source: inputStream,
        totalBytesProcessed: 0,
    };

    var readHelper = function() {
        buffer.clear();
        pumpCallBackArgs.bytesProcessed = -1;
        try
        {
            pumpCallBackArgs.bytesProcessed = inputStream.read(buffer, 0, maxChunkSize);
        }
        catch(err)
        {
            pumpCallBackArgs.errorDescription = err;
            pumpCallBackArgs.errorState = 1;
        }
        if (pumpCallBackArgs.bytesProcessed >= 0)
        {
            pumpCallBackArgs.totalBytesProcessed += pumpCallBackArgs.bytesProcessed;
        }
        handler(pumpCallBackArgs);
    };

    if (isAsync)
    {
        var pumpHelper = function()
        {
            readHelper();
            if (pumpCallBackArgs.bytesProcessed >= 0)
            {
                setTimeout(pumpHelper, 1);
            }
        };
        setTimeout(pumpHelper, 1);
    }
    else
    {
        do
        {
            readHelper();
        } while (pumpCallBackArgs.bytesProcessed >= 0);
    }
};

// Global.console
console = { };
['debug', 'error', 'info', 'warn'].forEach(function(level) {
    console[level] = function() {
        var msg = Array.prototype.map.call(arguments, function(m) {
            if (typeof(m) === 'object') {
                return m.hasOwnProperty('toString') ? m.toString() : JSON.stringify(m);
            }
            return m === null ? 'null' : m === void 0 ? 'undefined' : m;
        }).join(' ');
        Ti.API.log(level.toUpperCase(), msg);
    }
});
console.log = console.info;
Ti.UI = Ti.UI || {};
Ti.UI.iPhone = Ti.UI.iPhone || {
        SystemButton: {
            REFRESH: 0,
            FLEXIBLE_SPACE: 0,
            INFO_DARK: 0,
            DISCLOSURE: 0
        },
        StatusBar: {
            OPAQUE_BLACK:0,
        },
        SystemButtonStyle: {
            BORDERED: 0,
            PLAIN: 0,
            DONE: 0,
            BAR: 0
        },
        AnimationStyle: {
            FLIP_FROM_LEFT: 0
        },
        ActivityIndicatorStyle: {
            DARK: 0,
        },
        RowAnimationStyle: {
            LEFT: 0,
            UP: 0,
            DOWN: 0,
            RIGHT: 0
        },
        TableViewStyle: {
            GROUPED: 0,
            PLAIN: 0
        },
        TableViewCellSelectionStyle: {
            NONE: 0
        },
        TableViewSeparatorStyle: {
            NONE: 0
        },
        TableViewScrollPosition: {
            TOP: 0
        }
};


Ti.UI.create2DMatrix = function(){
    Ti.API.error('Ti.UI.create2DMatrix NOT SUPPORTED IN BB10');
    return {
            scale: function(){},
            transform: 0,
            duration: 0,
            rotate: function(){}
    };
};
Ti.UI.createSearchBar = function(args) {
    args = args || {};
    Ti.API.warn('Ti.UI.createSearchBar() is not supported in BB10, using textField instead');
    return Ti.UI.createTextField(args);
};
Ti.UI.backgroundColor = undefined;
Ti.UI.setBackgroundColor = function(_color){Ti.UI.backgroundColor = _color;};
Ti.UI.getBackgroundColor = function(){ return Ti.UI.backgroundColor;};
Ti.UI.createWindow = function(_args){
    _args = _args || {};
    if(_args.backgroundColor != undefined || Ti.UI.backgroundColor != undefined) {
        _args.backgroundColor = _args.backgroundColor || Ti.UI.backgroundColor;
    }
    return Ti.UI.BlackBerry.createWindow(_args);
}
Ti.UI.createWebView = Ti.UI.BlackBerry.createWebView;
Ti.UI.createButton = Ti.UI.BlackBerry.createButton;
Ti.UI.createTabGroup = Ti.UI.BlackBerry.createTabGroup;
Ti.UI.createTab = Ti.UI.BlackBerry.createTab;
Ti.UI.createAlertDialog = Ti.UI.BlackBerry.createAlertDialog;
Ti.UI.createTableView = Ti.UI.BlackBerry.createTableView;
Ti.UI.createTableViewRow = Ti.UI.BlackBerry.createTableViewRow;
Ti.UI.createTableViewSection = Ti.UI.BlackBerry.createTableViewSection;
Ti.UI.createScrollableView = Ti.UI.BlackBerry.createScrollableView;
Ti.UI.createScrollView = Ti.UI.BlackBerry.createScrollView;
Ti.UI.createView = Ti.UI.BlackBerry.createView;
Ti.UI.createImageView = Ti.UI.BlackBerry.createImageView;
Ti.UI.createLabel = Ti.UI.BlackBerry.createLabel;
Ti.UI.createTextField = Ti.UI.BlackBerry.createTextField;
Ti.UI.createTextArea = Ti.UI.BlackBerry.createTextArea;
Ti.UI.createSwitch = Ti.UI.BlackBerry.createSwitch;
Ti.UI.createSlider = Ti.UI.BlackBerry.createSlider;
Ti.UI.createImageButton = Ti.UI.BlackBerry.createImageButton;
Ti.UI.createProgressBar = Ti.UI.BlackBerry.createProgressBar;
Ti.UI.createActivityIndicator = Ti.UI.BlackBerry.createActivityIndicator;
Ti.UI.createEmailDialog = Ti.UI.BlackBerry.createEmailDialog;
Ti.UI.createOptionDialog = Ti.UI.BlackBerry.createOptionDialog;
Ti.UI.createNavigationGroup = Ti.UI.BlackBerry.createNavigationWindow;
Ti.UI.createNavigationWindow = Ti.UI.BlackBerry.createNavigationWindow;
Ti.UI.createAnimation = Ti.UI.BlackBerry.createAnimation;

Ti.UI.KEYBOARD_DEFAULT = Ti.UI.BlackBerry.KEYBOARD_DEFAULT;
Ti.UI.KEYBOARD_ASCII = Ti.UI.BlackBerry.KEYBOARD_ASCII;
Ti.UI.KEYBOARD_EMAIL = Ti.UI.BlackBerry.KEYBOARD_EMAIL;
Ti.UI.KEYBOARD_NAMEPHONE_PAD = Ti.UI.BlackBerry.KEYBOARD_NAMEPHONE_PAD;
Ti.UI.KEYBOARD_NUMBERS_PUNCTUATION = Ti.UI.BlackBerry.KEYBOARD_NUMBERS_PUNCTUATION;
Ti.UI.KEYBOARD_PHONE_PAD = Ti.UI.BlackBerry.KEYBOARD_PHONE_PAD;
Ti.UI.KEYBOARD_URL = Ti.UI.BlackBerry.KEYBOARD_URL;
Ti.UI.KEYBOARD_CHAT = Ti.UI.BlackBerry.KEYBOARD_CHAT;
Ti.UI.WEBVIEW_NAVIGATION_TYPE_LINK_CLICKED = Ti.UI.BlackBerry.WEBVIEW_NAVIGATION_TYPE_LINK_CLICKED;
Ti.UI.WEBVIEW_NAVIGATION_TYPE_FORM_SUBMIT = Ti.UI.BlackBerry.WEBVIEW_NAVIGATION_TYPE_FORM_SUBMIT;
Ti.UI.WEBVIEW_NAVIGATION_TYPE_BACK_FORWARD = Ti.UI.BlackBerry.WEBVIEW_NAVIGATION_TYPE_BACK_FORWARD;
Ti.UI.WEBVIEW_NAVIGATION_TYPE_RELOAD = Ti.UI.BlackBerry.WEBVIEW_NAVIGATION_TYPE_RELOAD;
Ti.UI.WEBVIEW_NAVIGATION_TYPE_FORM_RESUBMIT = Ti.UI.BlackBerry.WEBVIEW_NAVIGATION_TYPE_FORM_RESUBMIT;
Ti.UI.WEBVIEW_NAVIGATION_TYPE_OTHER = Ti.UI.BlackBerry.WEBVIEW_NAVIGATION_TYPE_OTHER;
Ti.UI.WEBVIEW_NAVIGATION_TYPE_OPEN_WINDOW = Ti.UI.BlackBerry.WEBVIEW_NAVIGATION_TYPE_OPEN_WINDOW;
Ti.UI.LANDSCAPE_LEFT = Ti.UI.BlackBerry.LANDSCAPE_LEFT;
Ti.UI.LANDSCAPE_RIGHT = Ti.UI.BlackBerry.LANDSCAPE_RIGHT;
Ti.UI.PORTRAIT = Ti.UI.BlackBerry.PORTRAIT;
Ti.UI.UPSIDE_PORTRAIT = Ti.UI.BlackBerry.UPSIDE_PORTRAIT;
Ti.UI.ACTION_BAR_PLACEMENT_ON_BAR = Ti.UI.BlackBerry.ACTION_BAR_PLACEMENT_ON_BAR;
Ti.UI.ACTION_BAR_PLACEMENT_IN_OVERFLOW = Ti.UI.BlackBerry.ACTION_BAR_PLACEMENT_IN_OVERFLOW;
Ti.UI.ACTION_ABR_PLACEMENT_DEFAULT = Ti.UI.BlackBerry.ACTION_ABR_PLACEMENT_DEFAULT;
Ti.UI.OVER_SCROLL_ALWAYS = Ti.UI.BlackBerry.OVER_SCROLL_ALWAYS;
Ti.UI.OVER_SCROLL_IF_CONTENT_SCROLLS = Ti.UI.BlackBerry.OVER_SCROLL_IF_CONTENT_SCROLLS;
Ti.UI.OVER_SCROLL_NEVER = Ti.UI.BlackBerry.OVER_SCROLL_NEVER;
Ti.UI.TEXT_ALIGNMENT_LEFT = Ti.UI.BlackBerry.TEXT_ALIGNMENT_LEFT;
Ti.UI.TEXT_ALIGNMENT_CENTER = Ti.UI.BlackBerry.TEXT_ALIGNMENT_CENTER;
Ti.UI.TEXT_ALIGNMENT_RIGHT = Ti.UI.BlackBerry.TEXT_ALIGNMENT_RIGHT;
Ti.UI.TEXT_ALIGNMENT_DEFAULT = Ti.UI.BlackBerry.TEXT_ALIGNMENT_DEFAULT;

Titanium = Ti;
