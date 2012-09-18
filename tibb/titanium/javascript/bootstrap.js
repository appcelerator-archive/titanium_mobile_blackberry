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
