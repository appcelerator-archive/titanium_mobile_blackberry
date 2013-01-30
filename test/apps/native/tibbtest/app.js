// this sets the background color of the master UIView (when there are no windows/tab groups on it)
//Titanium.UI.setBackgroundColor('#000');


var win = Ti.UI.createWindow({});


var db = Ti.Database.open('mydb1Installed');

db.execute('CREATE TABLE IF NOT EXISTS people (name TEXT, phone_number TEXT, city TEXT)');
db.execute('DELETE FROM people');

var thisName = 'Arthur';
var thisPhoneNo = '1-617-000-0000';
var thisCity = 'Mountain View';
var rows = db.execute('INSERT INTO people (name, phone_number, city) VALUES (?, ?, ?)', thisName, thisPhoneNo, thisCity);


var personArray = ['Paul',300, 'London'];
db.execute('INSERT INTO people (name, phone_number, city) VALUES (?, ?, ?)', personArray);

rows = db.execute('SELECT rowid,name,phone_number,city FROM people');
//db.close();


//Ti.API.info('Row count: ' + rows.rowCount);

//var fieldCount;
//fieldCount = rows.fieldCount;

//Ti.API.info('Field count: ' + fieldCount);

while (rows.isValidRow()){
//  Ti.API.info('Person ---> ROWID: ' + rows.fieldByName('rowid') + ', name:' + rows.field(1) + ', phone_number: ' + rows.fieldByName('phone_number') + ', city: ' + rows.field(3));
  rows.next();
}

rows.close();


/*
 
var win = Ti.UI.createWindow({});
//Clipping.
var parent = Ti.UI.createView({backgroundColor:'red',width:'100',height:'100'})
var child =Ti.UI.createView({backgroundColor:'green',width:150,height:150,left:5,top:5});

//parent.add(child);
win.add(parent);

var basicSwitch = Ti.UI.createSwitch({
	  value:true // mandatory property for iOS 
});
win.add(basicSwitch);


var label2 = Ti.UI.createLabel({
	  color:'blue',
	  text: 'ksskasksaaskjshakhsiuahsiuahaiuhaisuhsaiuhsaiuahsiuashjjjjj',
	  //text: 'A long label with\na few line breaks\nand unicode (UTF8)\nsymbols such as\na white chess piece \u2655\nand the euro symbol \u20ac\nlooks like this!\n',
	  textAlign: Ti.UI.TEXT_ALIGNMENT_LEFT,
	  top: 30,
	  width: 300, height: 200
	});

win.add(label2);

win.open();
*/

/*
//
// create root window
//
var win1 = Titanium.UI.createWindow({  
    backgroundColor:'#F00'
});

var label1 = Ti.UI.createLabel({
	textAlign : 'center',
	font: {fontSize:12},
	color:'green',
	top: 200
});

var label2 = Ti.UI.createLabel({
	textAlign : 'center',
	font: {fontSize:20},
	color:'blue',
	top: 0,
	text: 'ZIndex',
});

win1.add(label1);
win1.add(label2);

var mybutton=Ti.UI.createButton
(
	{top: 100,title: 'Push Me'}
);

mybutton.addEventListener
(
	'click',
	function(e)
	{
		e.source.title='Pushed!';
		testbutton1.zIndex=15;
	}
);

win1.add(mybutton);

var slider1=Ti.UI.createSlider
(
	{
		top: 200,
		min: 0,
		max: 100,
		value: 50,
	}
);

var sliderListener=function(e)
{
	progress1.value=100-e.value;
	label1.text='Slider value: '+e.value;
	label1.top=e.value;
	mybutton.opacity=e.value/100.0;
	mybutton.left=e.value;
	mybutton.top=e.value;
};

slider1.addEventListener('change',sliderListener);
label1.addEventListener('click',function(e)
	{
		label1.text='Label was clicked';
	}
	);


win1.add(slider1);

var progress1=Ti.UI.createProgressBar({
	value:0,
	min: 0,
	max: 100,
	top: 300,
});

win1.add(progress1);

var testbutton1=Ti.UI.createButton
(
	{top: 500,left:0,title: 'Button 1',zIndex:0}
);
win1.add(testbutton1);

var testbutton2=Ti.UI.createButton
(
	{top: 550,left:50,title: 'Button 2',zIndex:20}
);
win1.add(testbutton2);

var testbutton3=Ti.UI.createButton
(
	{top: 600,left:100,title: 'Button 3',zIndex:25}
);
win1.add(testbutton3);

var testbutton4=Ti.UI.createButton
(
	{top: 650,left:150,title: 'Button 4',zIndex:10}
);
win1.add(testbutton4);

// open window
win1.open();

var timer=setInterval(function()
{
	label2.text='ZIndex of button1='+testbutton1.zIndex+', Zindex of button2='+testbutton2.zIndex;
	testbutton1.top=500+Math.floor(Math.random()*500);
	testbutton1.left=Math.floor(Math.random()*500);
	testbutton2.top=500+Math.floor(Math.random()*500);
	testbutton2.left=Math.floor(Math.random()*500);
	testbutton3.top=500+Math.floor(Math.random()*500);
	testbutton3.left=Math.floor(Math.random()*500);
	testbutton4.top=500+Math.floor(Math.random()*500);
	testbutton4.left=Math.floor(Math.random()*500);
},5000
);

*/

/*
var socket = Ti.Network.Socket.createTCP({
    host: 'docs.appcelerator.com', port: 80,
    connected: function (e) {
        Ti.API.info('Socket opened!');
        Ti.Stream.pump(e.socket, readCallback, 1024, true);
        Ti.Stream.write(socket, Ti.createBuffer({
            value: 'GET /titanium/latest/ HTTP/1.1\r\nHost: docs.appcelerator.com\r\n\r\n'
        }), writeCallback);
    },
        error: function (e) {
        Ti.API.info('Error (' + e.errorCode + '): ' + e.error);
    },
});
socket.connect();

function writeCallback(e) {
    Ti.API.info('Successfully wrote to socket.');
}

function readCallback(e) {
    if (e.bytesProcessed == -1)
    {
		Ti.API.error("bytesProcessed == -1");
		return;
    }
    try {
        if(e.buffer) {
            var received = e.buffer.toString();
            Ti.API.info('Received: ' + received);
        } else {
            Ti.API.error('Error: read callback called with no buffer!');
        }
    } catch (ex) {
        Ti.API.error(ex);
    }
}

var h = Ti.Network.createHTTPClient({
	onload : function(e) {
		Ti.API.info("Received text: " + this.responseText);
	},
	onerror : function(e) {
		Ti.API.info(e);
	},
	onreadystatechange: function(e) {
		Ti.API.info("Readystate change: " + this.readyState);		
	}
});
h.enableKeepAlive = true;
h.open("GET", "http://www.xhaus.com/headers");
h.setRequestHeader("TESTTEST", "abcdefg");
h.send();
*/
