/*
var player = Ti.Media.createSound({url:"sound.wav"});
player.play();
*/

var win = Titanium.UI.createWindow({  
    title:'Audio Test',
    backgroundColor:'#fff',
    layout: 'vertical'
});

var startStopButton = Titanium.UI.createButton({
    title:'Start/Stop Streaming',
    top:10,
    width:200,
    height:40
});

var pauseResumeButton = Titanium.UI.createButton({
    title:'Pause/Resume Streaming',
    top:10,
    width:200,
    height:40,
    enabled:false
});

win.add(startStopButton);
win.add(pauseResumeButton);


var audioPlayer = Ti.Media.createAudioPlayer({ 
    url: 'http://www.villagegeek.com/downloads/webwavs/adios.wav'
});
          
    
startStopButton.addEventListener('click',function() {
    // When paused, playing returns false.
    // If both are false, playback is stopped.
    if (audioPlayer.playing || audioPlayer.paused)
    {
        audioPlayer.stop();
        pauseResumeButton.enabled = false;
        audioPlayer.release();
    }
    else
    {
        audioPlayer.start();
        pauseResumeButton.enabled = true;
    }
});

pauseResumeButton.addEventListener('click', function() {
    if (audioPlayer.paused) {
        audioPlayer.start();
    }
    else {
        audioPlayer.pause();
    }
});

audioPlayer.addEventListener('progress',function(e) {
    Ti.API.info('Time Played: ' + Math.round(e.progress) + ' milliseconds');
});

audioPlayer.addEventListener('change',function(e)
{
    Ti.API.info('State: ' + e.description + ' (' + e.state + ')');
});

win.addEventListener('close',function() {

    audioPlayer.stop();
    audioPlayer.release();
});

win.open();