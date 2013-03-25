

var win = Titanium.UI.createWindow({  
    title:'Audio Test',
    backgroundColor:'#fff',
    layout: 'vertical'
});

var startStopButton = Titanium.UI.createButton({
    title:'Start/Stop Recording',
    top:10,
    width:200,
    height:40
});

var recPlaybackButton = Titanium.UI.createButton({
    title:'Rec. Playback',
    top:10,
    width:200,
    height:40,
    enabled:true
});

var recSpeedUpButton = Titanium.UI.createButton({
    title:'Rec. Speed-Up',
    top:10,
    width:200,
    height:40,
    enabled:true
});

var tranceItButton = Titanium.UI.createButton({
    title:'Trance It',
    top:10,
    width:200,
    height:40,
    enabled:true
});

win.add(startStopButton);
win.add(recPlaybackButton);
win.add(recSpeedUpButton);
win.add(tranceItButton);

var audioRecorder = Ti.Media.createAudioRecorder({ 
	 url: 'sounds/myrec.m4a'
});

var audioPlayer = Ti.Media.createSound({ 
	 url: 'sounds/bot.mp3'
});

var audioPlayer2 = Ti.Media.createSound({});
          
    
startStopButton.addEventListener('click',function() {
    if (audioRecorder.recording || audioRecorder.paused)
    {
    	audioRecorder.stop();
        audioRecorder.release();
    }
    else
    {
        audioRecorder.start();
    }
});

recPlaybackButton.addEventListener('click', function() {
	
	audioPlayer2.setUrl('sounds/myrec.m4a');
	audioPlayer2.setRepeatMode(true);
	audioPlayer2.play();
});

var inc = 0.0;

recSpeedUpButton.addEventListener('click', function() {
	inc += .1;
	var speed = 1.0 + inc;
	audioPlayer2.setBitRate(speed);
	Ti.API.info('Speed: ' + speed);
});

tranceItButton.addEventListener('click', function() {

	audioPlayer.play();
});

audioPlayer.addEventListener('change',function(e)
{
    Ti.API.info('State: ' + e.description + ' (' + e.state + ')');
});

audioPlayer.addEventListener('completed',function(e)
{
    Ti.API.info('media completed');
});

win.addEventListener('close',function() {

    audioPlayer.stop();
    audioPlayer.release();
});

win.open();