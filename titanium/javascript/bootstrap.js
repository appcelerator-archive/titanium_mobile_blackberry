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
    //this call is always synchronous, ignore last param
    var pumpCallBackArgs  = {
    buffer: undefined,
    bytesProcessed: 0,
    errorDescription: '',
    errorState: 0,
    source: inputStream,
    totalBytesProcessed: 0,
    };
    
    var tmpBuffer = Ti.createBuffer({ length: maxChunkSize });
    try {
        while((size = inputStream.read(tmpBuffer, 0, maxChunkSize)) > 0) {
            pumpCallBackArgs.bytesProcessed = size;
            pumpCallBackArgs.totalBytesProcessed += size;
            pumpCallBackArgs.buffer = tmpBuffer;
            tmpBuffer.clear();
            handler(pumpCallBackArgs);
       }
    }
    catch (e)
    {
        pumpCallBackArgs.errorDescription = e;
    }
    pumpCallBackArgs.bytesProcessed = -1;
    handler(pumpCallBackArgs);
};
