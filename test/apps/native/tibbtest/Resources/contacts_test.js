var UI = {};
UI.createElement = function (TiElement, Options) {

    /**
     * Checks wether a key-value pair is an event callback
     * @param  {string}    key    String has to be on[Uppercase]
     * @param  {object}    value    Must be a function to be a callback
     * @return {Boolean}        True or False
     */
    function isCallback(key, value) {
        var begin = key.slice(0,2);    // gets the first two characters
        var next = key.slice(2,3);    // gets the third
        // The first two characters must be "on", the next one must be upper case
        // and the value must be a function
        // For example: onClick: function() { }
        if(begin == 'on' && next == next.toUpperCase() && typeof value == 'function')
            return true;
        return false;
    }

    /**
     * Adds events to Ti.UI.ViewProxy
     * @param {Ti.UI.ViewProxy}    TiElement    Ti.UI.Element
     * @param {String}         EventName    Name of event, ie. onClick
     * @param {Function}         Event         Actual event callback
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
    for(var i = 0, len = subviews.length; i < len; i++) {
        el.add(subviews[i]);
    }
        
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
UI.ScrollView = function(args) { 
    args = args || {};
    return UI.createElement(Ti.UI.createScrollView, args);
};

function Label(_title, _message) {
    if(typeof _message == 'object') {
        _message = JSON.stringify(_message)
    }
    return UI.Label({
        top: 10,
        left: 10,
        text: _title + ': ' + _message
    });
}

function ContactWindow(_contactId) {
    
    var contact = Ti.Contacts.getPersonByID(_contactId);
    Ti.API.info(JSON.stringify(contact.address));
    var win = UI.Window({
        subviews: [
                   UI.Button({
                       title: 'create contact',
                       onClick: createContact,
                       top: 0
                   })
                   /*
                   UI.ScrollView({
                       top: 30,
                       layout: 'vertical',
                       subviews: [
                           Label('address',contact.address),
                           Label('birthday',contact.birthday),
                           Label('created',contact.created),
                           Label('department',contact.department),
                           Label('email',contact.email),
                           Label('firstName', contact.firstName),
                           Label('fullName', contact.fullName),
                           Label('firstPhonetic', contact.firstPhonetic),
                           Label('id', contact.id),
                           Label('image', contact.image),
                           Label('instantMessage', contact.instantMessage),
                           Label('jobTitle', contact.jobTitle),
                           Label('kind', contact.kind),
                           Label('lastName', contact.lastName),
                           Label('lastPhonetic', contact.lastPhonetic),
                           Label('middleName', contact.middleName),
                           Label('middlePhonetic', contact.middlePhonetic),
                           Label('modified', contact.modified),
                           Label('nickname', contact.nickname),
                           Label('note', contact.note),
                           Label('organization', contact.organization),
                           Label('phone', contact.phone),
                           Label('prefix', contact.prefix),
                           Label('recordId', contact.recordId),
                           Label('relatedNames', contact.relatedNames),
                           Label('suffix', contact.suffix),
                           Label('url', contact.url),
                            
                            UI.Button({
                                top: 10,
                                title: 'close',
                                onClick: closeWindow
                            })
                            ]
                   })
                   */
        ]
    });
    
    function createContact(){
        Ti.Contacts.createPerson({
              firstName: 'Paul',
              lastName: 'Dowsett',
              address:{
                work:[
                  {
                    CountryCode: 'gb', // determines how the address is displayed
                    Street: '200 Brook Drive\nGreen Park',
                    City: 'Reading',
                    County: 'Berkshire',
                    Country: 'England',
                    ZIP: 'RG2 6UB'
                  },
                  {
                    CountryCode: 'gb', // determines how the address is displayed
                    Street: '1 St Pauls Road\nClerkenwell',
                    City: 'City of London',
                    State: 'London',
                    Country: 'England',
                    ZIP: 'EC1 1AA'
                  }
                ],
                home:[
                  {
                    CountryCode: 'gb', // determines how the address is displayed
                    Street: '2 Boleyn Court',
                    City: 'London',
                    State: 'Greenwich',
                    Country: 'England',
                    ZIP: 'SE10'
                  }
                ]
              },
              birthday: '2012-01-01T12:00:00.000+0000',
              instantMessage:{
            	  AIM: ['leisureAIM'],
            	  MSN: ['no_paul_here@msn.com', 'lala@lala.com'],
            	  skype: ['pec1985', 'pecdev']
              },
              organization: 'Appcelerator',
              phone:{
                mobile: ['07900 000001', '07900 000002'],
                work: ['+44 (0)118 925 6128', '+44 (0)118 000 0000']
              },
              url:{
                homepage: ['www.google.com'],
                work: ['www.appcelerator.com', 'www.example.com']
              }
            });

    }
    
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