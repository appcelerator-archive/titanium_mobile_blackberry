/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
Ti = Ti || {};
Ti.include = Ti.include || function (id) { Ti.globalInclude(id, "app/native/assets/") };
var global = {};

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
	}
}
Ti.UI.createSearchBar = function(args) {
	args = args || {};
	Ti.API.error('Ti.UI.createSearchBar() NOT SUPPORTED IN BB10, using textField instead');
	return Ti.UI.createTextField(args);
} 
Ti.UI.createWebView = Ti.UI.BlackBerry.createWebView;
Ti.UI.createButton = Ti.UI.BlackBerry.createButton;
Ti.UI.createWindow = Ti.UI.BlackBerry.createWindow;
Ti.UI.createTabGroup = Ti.UI.BlackBerry.createTabGroup;
Ti.UI.createTab = Ti.UI.BlackBerry.createTab;
Ti.UI.createAlertDialog = Ti.UI.BlackBerry.createAlertDialog;

Titanium = Ti;