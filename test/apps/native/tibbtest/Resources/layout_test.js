function Log(str) {
    Ti.API.info(str);
}
var Test = [];
// 1
Test.push(function(){
    var win = Ti.UI.createWindow();
 
    var view = Ti.UI.createView({
        backgroundColor: 'blue',
        height: Ti.UI.SIZE
    });
 
    var label = Ti.UI.createLabel({
        text: 'hello world',
        backgroundColor: 'red',
        height: Ti.UI.SIZE,
        top: 10,
        bottom: 10
    });
 
    view.add(label);
    win.add(view);
    Log('====================================');
    Log('Test #1');
    Log('You should see:');
    Log('Blue view width FILL and height the same as label plus 5 on top and bottom');
    Log('Label width SIZE and height SIZE inside blue view');
    Log('====================================');
    return win;
});
// 2
Test.push(function(){
    var win = Ti.UI.createWindow();
 
    var view = Ti.UI.createView({
        backgroundColor: 'blue',
        height: Ti.UI.SIZE
    });
 
    var label = Ti.UI.createLabel({
        text: 'hello world',
        backgroundColor: 'red',
        top: 10,
        bottom: 10
    });
 
    view.add(label);
    win.add(view);
 
    Log('====================================');
    Log('Test #2');
    Log('You should see:');
    Log('Blue view width FILL and height FILL');
    Log('Label width SIZE margin of 10 on top and bottom of blue view');
    Log('====================================');
 
    return win;
});
// 3
Test.push(function(){
    var win = Ti.UI.createWindow();
 
    var view = Ti.UI.createView({
        backgroundColor: 'blue',
        width: Ti.UI.SIZE,
    });
 
    var label = Ti.UI.createLabel({
        text: 'hello world',
        backgroundColor: 'red',
        width: Ti.UI.SIZE,
        left: 5, right: 5
    });
 
    view.add(label);
    win.add(view);
 
    Log('====================================');
    Log('Test #3');
    Log('You should see:');
    Log('Blue view width SIZE and height FILL');
    Log('Width of blue view should be the width of the label plus 5 on each side')
    Log('Label width SIZE margin of 5 on left and right of blue view');
    Log('====================================');
 
    return win;
});
// 4
Test.push(function(){
    var win = Ti.UI.createWindow();
 
    var label = Ti.UI.createLabel({
        text: 'hello world',
        backgroundColor: 'red',
        right: 10,
        left: 10
    });
    win.add(label);
 
    Log('====================================');
    Log('Test #4');
    Log('You should see:');
    Log('Label of height SIZE and margin of 5 on left and right of window');
    Log('====================================');
 
    return win;
});
// 5
Test.push(function(){
    var win = Ti.UI.createWindow();
 
    var label = Ti.UI.createLabel({
        text: 'hello world',
        backgroundColor: 'red',
        top: 10,
        bottom: 10
    });
    win.add(label);
    Log('====================================');
    Log('Test #5');
    Log('You should see:');
    Log('Label of width SIZE and margin of 5 on top and bottom of window');
    Log('====================================');
    return win;
});
// 6
Test.push(function(){
    var win = Ti.UI.createWindow();
 
    var view = Ti.UI.createView({
        backgroundColor: 'blue',
        height: Ti.UI.SIZE
    });
 
    var label = Ti.UI.createLabel({
        backgroundColor: 'red',
        height: 30, text: 'Hello World',
        left: 10, right: 10,
        top: 10, bottom: 10
    });
 
    view.add(label);
    win.add(view);
    Log('====================================');
    Log('Test #6');
    Log('You should see:');
    Log('Blue view of width FILL and height of SIZE');
    Log('Label inside has margin all around blue view of 10');
    Log('====================================');
    return win;
});
// 7
Test.push(function(){
    var win = Ti.UI.createWindow();
 
    var view = Ti.UI.createView({
        backgroundColor: 'blue',
        height: Ti.UI.SIZE,
        width: Ti.UI.SIZE
    });
 
    var label = Ti.UI.createLabel({
        text: 'hello world',
        backgroundColor: 'red',
        left:5, right: 5,
        top: 5, bottom: 5,
        width: Ti.UI.SIZE,
        height: Ti.UI.SIZE
    });
 
    view.add(label);
    win.add(view);
    Log('====================================');
    Log('Test #7');
    Log('You should see:');
    Log('Blue view of width SIZE and height of SIZE');
    Log('Label inside has margin all around blue view of 5');
    Log('====================================');
    return win;
});
// 8
Test.push(function(){
    var win = Ti.UI.createWindow();
 
    var view = Ti.UI.createView({
        backgroundColor: 'blue',
        height: Ti.UI.SIZE,
        width: Ti.UI.SIZE
    });
 
    var label = Ti.UI.createLabel({
        text: 'hello world',
        backgroundColor: 'red',
        left:5, right: 5,
        top: 5, bottom: 5
    });
 
    view.add(label);
    win.add(view);
    Log('====================================');
    Log('Test #8');
    Log('You should see:');
    Log('Blue view of width FILL and height of FILL');
    Log('Label inside has margin all around blue view of 5');
    Log('====================================');
    return win;
});
 
//9
Test.push(function(){
    var win = Ti.UI.createWindow();
    var label = Ti.UI.createLabel({
        text: 'width 200, height 100',
        width: 200,
        height: 100,
        backgroundColor: 'red'
    });
    win.add(label);
    Log('====================================');
    Log('Test #8');
    Log('You should see:');
    Log('Label of height 200 and width 100');
    Log('====================================');
    return win;
});
 
// 10
Test.push(function(){
    var win = Ti.UI.createWindow();
    var button = Ti.UI.createButton({
        title: 'width 300',
        width: 300
    });
    win.add(button);
    Log('====================================');
    Log('Test #9');
    Log('You should see:');
    Log('Button of height SIZE and width 300');
    Log('====================================');
    return win;
})
 
//11
Test.push(function(){
    var win = Ti.UI.createWindow();
    var button = Ti.UI.createButton({
        title: 'width 250 right 5',
        width: 250,
        right: 5
    });
    win.add(button);
    Log('====================================');
    Log('Test #9');
    Log('You should see:');
    Log('Button of height SIZE, width 250 and right 5');
    Log('====================================');
    return win;
})
 
function Button(_params) {
    _params = _params || {};
    var callback = _params.onClick || function(){};
    delete _params.onClick;
    var btn = Ti.UI.createButton(_params);
    btn.addEventListener('click', callback);
    return btn;
}
 
function Window() {
    var win = Ti.UI.createWindow();
    var scrollView = Ti.UI.createScrollView({
        layout: 'vertical'
    });
 
    for(var i = 0, len = Test.length; i < len; i++) {
 
        scrollView.add(Button({
            top: 10,
            bottom: 10,
            height: Ti.UI.SIZE,
            title: 'Test #' + (i + 1),
            test: i,
            onClick: function(){
                var w = Test[this.test]();
                w.backgroundColor = '#DDDDDD';
                w.add(Button({
                    right: 0,
                    top: 0,
                    width: 20,
                    onClick:  function() {
                       w.close();
                    }
                }));
                w.open();
            }
        }));
    }
 
    win.add(scrollView);
    return win;
}
 
Window().open();