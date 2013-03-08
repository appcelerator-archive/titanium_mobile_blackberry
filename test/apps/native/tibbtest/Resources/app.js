
var win = Titanium.UI.createWindow({orientationModes:[Ti.UI.PORTRAIT]});

var mountainView = Titanium.Map.createAnnotation({
    latitude:37.389493,
    longitude:-122.050166,
    title:'Appcelerator Headquarters',
    subtitle:'Mountain View, CA',
    pincolor:Ti.Map.ANNOTATION_GREEN,
    //rightView: 'images/appcelerator_small.png',
    leftView: 'images/appcelerator_small.png'
});

var waitersOnWheels = Titanium.Map.createAnnotation({
    latitude:37.390749,
    longitude:-122.051651,
    title:'Waiters On Wheels',
    subtitle:'Mountain View, CA',
    pincolor:Ti.Map.ANNOTATION_RED,
    //rightView: 'images/appcelerator_small.png',
    leftView: 'images/appcelerator_small.png'
});

var tlBeerGarden = Titanium.Map.createAnnotation({
    latitude:37.39504,
    longitude:-122.02937,
    title:'TL Beer Garden',
    subtitle:'Sunnyvale, CA',
    pincolor:Ti.Map.ANNOTATION_PURPLE,
    //rightView: 'images/appcelerator_small.png',
    leftView: 'images/photo.jpg'
});

var mapview = Titanium.Map.createView({
    region: {latitude:37.390749, longitude:-122.051651},
    annotations:[mountainView, waitersOnWheels]
});

win.add(mapview);

// Handle click events on any annotations on this map.
waitersOnWheels.addEventListener('click', function(evt) {
	
	mapview.addAnnotation(tlBeerGarden);
	
	if (evt.clicksource == 'leftView') {
		Ti.API.info('Annotation ' + evt.clicksource + ', left view clicked.');
	}
	
	if (evt.clicksource == 'rightView') {
        Ti.API.info('Annotation ' + evt.clicksource + ', right view clicked.');
	}
	
});


win.open();
