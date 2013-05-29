var UI = {};
UI.createElement = function (TiElement, Options) {

	/**
	 * Checks wether a key-value pair is an event callback
	 * @param  {string}	key	String has to be on[Uppercase]
	 * @param  {object}	value	Must be a function to be a callback
	 * @return {Boolean}		True or False
	 */
	function isCallback(key, value) {
		var begin = key.slice(0,2);	// gets the first two characters
		var next = key.slice(2,3);	// gets the third
		// The first two characters must be "on", the next one must be upper case
		// and the value must be a function
		// For example: onClick: function() { }
		if(begin == 'on' && next == next.toUpperCase() && typeof value == 'function')
			return true;
		return false;
	}

	/**
	 * Adds events to Ti.UI.ViewProxy
	 * @param {Ti.UI.ViewProxy}	TiElement	Ti.UI.Element
	 * @param {String} 		EventName	Name of event, ie. onClick
	 * @param {Function} 		Event 		Actual event callback
	 */
	function addEvent(TiElement , EventName, Event) {
		if(!Event) return;
		var name = String(EventName).replace('on', '').toLowerCase();
		TiElement.addEventListener(name, Event);
	}

	// Create the subviews array
	var subviews = [];
	// Create the object to hold the events
	var callbacks = {};
	// Iterate through the arguments to fetch the callbacks and the subviews
	// Once added to the object, delete from the Options object
	// Passing custom functions or Ti.Proxies to Ti.Proxies is bad practice!
	for(var key in Options) {
		if(isCallback(key, Options[key])){
			callbacks[key] = Options[key];
			delete Options[key];
		}
		if(key == 'subviews') {
			subviews = Options[key];
			delete Options[key];				
		}

	}
	// Once the event callbacks are extracted, create the proxy
	var el = TiElement(Options);
	// Add the event listeners to the proxy
	for(var key in callbacks) {
		addEvent(el, key, callbacks[key]);
	}

	// Yes, this is possible too (only in iOS as far as I'm aware)
	// :)
	/*
	if((iPhone || iPad) && subviews.length) {
		el.add(subviews);
	} else {
	*/
		for(var i = 0, len = subviews.length; i < len; i++) {
			el.add(subviews[i]);
		}
		
//	}
	// Null out variables, not sure if necessary, who knows!
	callbacks = null;
	Options = null;
	TiElement = null;
	subviews = null;
	return el;
}

UI.Window = function(args) { 
	args = args || {};
	return UI.createElement(Ti.UI.createWindow, args);
};

UI.TableView = function(args) { 
	args = args || {};
	return UI.createElement(Ti.UI.createTableView, args);
};

UI.Label = function(args) { 
	args = args || {};
	return UI.createElement(Ti.UI.createLabel, args);
};

UI.Button = function(args) { 
	args = args || {};
	return UI.createElement(Ti.UI.createButton, args);
};

function ContactWindow(_contactId) {
	
	var contact = Ti.Contacts.getPersonByID(_contactId);
	
	var win = UI.Window({
		layout: 'vertical',
		subviews: [
				    UI.Label({
				    	top: 10,
				    	height: 15,
				    	width: Ti.UI.FILL,
				    	text: 'First name: ' + contact.firstName
				    }),
				    UI.Label({
				    	top: 10,
				    	height: 15,
				    	width: Ti.UI.FILL,
				    	text: 'Last name: ' + contact.lastName
				    }),
				    UI.Label({
				    	top: 10,
				    	height: 15,
				    	width: Ti.UI.FILL,
				    	text: 'Full name: ' + contact.fullName
				    }),
				    UI.Label({
				    	top: 10,
				    	height: 15,
				    	width: Ti.UI.FILL,
				    	text: 'Email: ' + JSON.stringify(contact.email)
				    }),
				    UI.Button({
				    	title: 'close',
				    	onClick: closeWindow
				    })
		]
	});
	
	function closeWindow() {
		win.close();
	}
	return win;
}


function MainWindow() {
	
	var allContacts = Ti.Contacts.getAllPeople();
	
	var tableData = [];
	for(var i = 0, len = allContacts.length; i < len; i++) {
		tableData.push({
			title: allContacts[i].firstName + ' ' + allContacts[i].lastName,
			contactId: allContacts[i].id
		});
	}
	
	return UI.Window({
		subviews: [
           UI.TableView({
        	   data: tableData,
        	   onClick: function(e){
        		   ContactWindow(e.rowData.contactId).open();
        	   }
           })
       ]
	});
}

MainWindow().open();