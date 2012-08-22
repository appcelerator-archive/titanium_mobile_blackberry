/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

alert = function(msg)
{
    Ti.UI.createAlertDialog({message: msg}).show();
}

L = function(key, hint)
{
	return key;
}

// TODO: move to its own file when we can include from the framework dir
//Ti.include("bufferstream.js");
Ti.BufferStream.prototype = {};
Ti.BufferStream.prototype.read = function(buffer, offset, length) {
    if(this.pos == this.source.length)
    {
        return -1;
    }

    if (offset === undefined)
    {
        offset = 0;
    }

    if (length === undefined)
    {
        length = buffer.length;
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
