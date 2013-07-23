var vidWin = Titanium.UI.createWindow({
    title : 'Video View Demo',
    backgroundColor : 'red',
    layout: 'vertical'
});

var startStopButton = Titanium.UI.createButton({
    title:'Start/Stop Streaming',
    top:20,
    width:300
});

var pauseResumeButton = Titanium.UI.createButton({
    title:'Pause/Resume Streaming',
    top:20,
    width:300,
    enabled:false
});

var videoPlayer = Titanium.Media.createVideoPlayer({
    top : 20,
    height : 300,
    width : 300
});

vidWin.add(startStopButton);
vidWin.add(pauseResumeButton);

startStopButton.addEventListener('click',function() {
    // When paused, playing returns false.
    // If both are false, playback is stopped.
    if (videoPlayer.playing || videoPlayer.paused)
    {
        videoPlayer.stop();
        pauseResumeButton.enabled = false;
        videoPlayer.release();
    }
    else
    {
        videoPlayer.start();
        pauseResumeButton.enabled = true;
    }
});

pauseResumeButton.addEventListener('click', function() {
    if (videoPlayer.paused) {
        videoPlayer.start();
    }
    else {
        videoPlayer.pause();
    }
});

videoPlayer.addEventListener('progress',function(e) {
    Ti.API.info('Time Played: ' + Math.round(e.progress) + ' milliseconds');
});

videoPlayer.addEventListener('change',function(e)
{
    Ti.API.info('State: ' + e.description + ' (' + e.state + ')');
    
    // currently blackberry does not support scaling but by hooking this
    // change event and getting the actual video dimensions the developer can scale 
    // or do and boxing that may be necessary
    videoPlayer.width = e.videoWidth/2;
    videoPlayer.height = e.videoHeight/2;
});

videoPlayer.addEventListener('completed',function(e)
{
    Ti.API.info('media completed');
});

vidWin.addEventListener('close',function() {

    videoPlayer.stop();
    videoPlayer.release();
});


videoPlayer.url = 'video/efencefun.mp4';
vidWin.add(videoPlayer);
vidWin.open();
