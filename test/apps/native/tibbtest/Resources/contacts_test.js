
function Label(_title, _message) {
    if(typeof _message == 'object') {
        _message = JSON.stringify(_message)
    }
    return Ti.UI.createLabel({
        top: 10,
        left: 10,
        text: _title + ': ' + _message
    });
}

function ContactWindow(_contactId) {

	var contact = Ti.Contacts.getPersonByID(_contactId);
    Ti.API.info(JSON.stringify(contact.address));
    
    var win = Ti.UI.createWindow();
    var scrollView = Ti.UI.createScrollView({
       layout: 'vertical',
       top: 0,
       height: Ti.UI.FILL
    });
    var closeButton = Ti.UI.createButton({
        top: 0,
    	title: 'close'
    });

    scrollView.add(closeButton);
    scrollView.add(Label('address',contact.address));
    scrollView.add(Label('birthday',contact.birthday));
    scrollView.add(Label('created',contact.created));
    scrollView.add(Label('department',contact.department));
    scrollView.add(Label('email',contact.email));
    scrollView.add(Label('firstName', contact.firstName));
    scrollView.add(Label('fullName', contact.fullName));
    scrollView.add(Label('firstPhonetic', contact.firstPhonetic));
    scrollView.add(Label('id', contact.id));
    scrollView.add(Label('image', contact.image));
    scrollView.add(Label('instantMessage', contact.instantMessage));
    scrollView.add(Label('jobTitle', contact.jobTitle));
    scrollView.add(Label('kind', contact.kind));
    scrollView.add(Label('lastName', contact.lastName));
    scrollView.add(Label('lastPhonetic', contact.lastPhonetic));
    scrollView.add(Label('middleName', contact.middleName));
    scrollView.add(Label('middlePhonetic', contact.middlePhonetic));
    scrollView.add(Label('modified', contact.modified));
    scrollView.add(Label('nickname', contact.nickname));
    scrollView.add(Label('note', contact.note));
    scrollView.add(Label('organization', contact.organization));
    scrollView.add(Label('phone', contact.phone));
    scrollView.add(Label('prefix', contact.prefix));
    scrollView.add(Label('recordId', contact.recordId));
    scrollView.add(Label('relatedNames', contact.relatedNames));
    scrollView.add(Label('suffix', contact.suffix));
    scrollView.add(Label('url', contact.url));

    win.add(scrollView);
    
    closeButton.addEventListener('click', function() {
        win.close();
    });
    return win;
}



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
          birthday: new Date(),
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
function MainWindow() {
    
    var allContacts = Ti.Contacts.getAllPeople();
    var createButton = Ti.UI.createButton({
        title: 'create contact',
        top: 0,
        height: Ti.UI.SIZE
    });
    

    var tableData = [];
    for(var i = 0, len = allContacts.length; i < len; i++) {
        tableData.push({
            title: allContacts[i].firstName + ' ' + allContacts[i].lastName,
            contactId: allContacts[i].id
        });
    }

    var win = Ti.UI.createWindow({
    	layout:'vertical'
    });

    createButton.addEventListener('click', function(){
    	alert('creating contact, please look at the phone\'s address book')
    	createContact();
    });
    var v = Ti.UI.createView({
    	top: 0,
    	height: Ti.UI.FILL
    });
    var table = Ti.UI.createTableView({
        data: tableData
    });

    table.addEventListener('click', function(e){
        ContactWindow(e.rowData.contactId).open();
    });
    v.add(table);
    win.add(createButton);
    win.add(v);
    
    return win;
}

MainWindow().open();