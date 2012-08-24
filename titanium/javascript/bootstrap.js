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
Ti.BufferStream.demoFunc = function() {
    Ti.API.debug("demoFunc is being run");
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
